/*************************************************************

Copyright (c) 	2017, Ángel Lareo Fernández
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of the author nor the names of his contributors
      may be used to endorse or promote products derived from this
      software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*************************************************************/

#ifndef ELECTROMOTOR_MODEL_STD_H_
#define ELECTROMOTOR_MODEL_STD_H_

#include <cfloat>
#include <climits>
#include <cmath>
#include <memory>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

#include "ModelOutput.hpp"

// Random initialization time range
#define MIN_TIME_RANDOM_INIT 300
#define MAX_TIME_RANDOM_INIT 500

template <typename ProblemConfigType>
class ElectromotorModelStd {
 public:
  typedef typename ProblemConfigType::neuron_t NeuronType;
  typedef typename ProblemConfigType::synapsis_t SynapsisType;
  typedef typename ProblemConfigType::neuron_t::ConstructorArgs
      NeuronConstructorArgs;
  typedef typename ProblemConfigType::synapsis_t::ConstructorArgs
      SynapsisConstructorArgs;
  typedef typename ProblemConfigType::pattern pattern_t;
  typedef typename ProblemConfigType::neuron_t::parameter NeuronParameter;
  typedef typename ProblemConfigType::synapsis_t::parameter SynapsisParameter;

  static constexpr std::vector<std::string> SynNames() {
    return std::vector<std::string>{"VPd_DP", "VPd_PCN", "DP_CN", "PCN_CN",
                                    "CN_VPd"};
  }

  static constexpr std::vector<std::string> NeuNames() {
    return std::vector<std::string>{"VPd", "DP", "PCN", "CN"};
  }

 private:
  static const short NO_SPK = -1;

  bool simulationPerformed = false;
  std::unique_ptr<ModelOutput> _out;

  std::default_random_engine _getRand;
  std::uniform_int_distribution<int> _timeRange{MIN_TIME_RANDOM_INIT,
                                                MAX_TIME_RANDOM_INIT};

  struct iExtNeurons {
    double VPd;
    double DP;
    double PCN;
  };

  std::vector<int> _simSteps;
  std::vector<iExtNeurons> _iExt;

  double _step;

  double _lastVol2 = 0.0, _lastVol1 = 0.0;
  double _filterTime = 0.0;
  double _vThreshold = 0.0;
  double _lastSpkTime = 0.0;

  std::array<int, 4> _targetSPI;

 public:
  enum synapsis { s1, s2, sA, sB, sBack, n_synapsis };
  enum neuron { VPd, DP, PCN, CN, n_neurons };

  NeuronType _VPd, _DP, _PCN, _CN;
  SynapsisType _s1, _s2, _sA, _sB, _sBack;

  std::vector<SynapsisType*> syns = {&_s1, &_s2, &_sA, &_sB, &_sBack};
  std::vector<NeuronType*> neuns = {&_VPd, &_DP, &_PCN, &_CN};

  ElectromotorModelStd(ProblemConfigType* info)
      : _step(info->getStep()),
        _VPd(info->getNeuronParams(NeuNames()[VPd])),
        _DP(info->getNeuronParams(NeuNames()[DP])),
        _PCN(info->getNeuronParams(NeuNames()[PCN])),
        _CN(info->getNeuronParams(NeuNames()[CN])),
        _s1(_VPd, NeuronType::v, _DP, NeuronType::v,
            info->getSynapsisParams(SynNames()[s1]), 5),
        _s2(_VPd, NeuronType::v, _PCN, NeuronType::v,
            info->getSynapsisParams(SynNames()[s2]), 5),
        _sA(_DP, NeuronType::v, _CN, NeuronType::v,
            info->getSynapsisParams(SynNames()[sA]), 5),
        _sB(_PCN, NeuronType::v, _CN, NeuronType::v,
            info->getSynapsisParams(SynNames()[sB]), 5),
        _sBack(_CN, NeuronType::v, _VPd, NeuronType::v,
               info->getSynapsisParams(SynNames()[sBack]), 5),
        _lastSpkTime(0.0) {}

  ElectromotorModelStd(ProblemConfigType* info, std::string outFileName)
      : ElectromotorModelStd(info) {
    _out = std::make_unique<ModelOutput>(outFileName);
  }

  ElectromotorModelStd(const ElectromotorModelStd& model)
      : _step(model.getStep()),
        _VPd(model.getNeuronParams(VPd)),
        _DP(model.getNeuronParams(DP)),
        _PCN(model.getNeuronParams(PCN)),
        _CN(model.getNeuronParams(CN)),
        _s1(_VPd, NeuronType::v, _DP, NeuronType::v,
            model.getSynapsisParams(s1), 5),
        _s2(_VPd, NeuronType::v, _PCN, NeuronType::v,
            model.getSynapsisParams(s2), 5),
        _sA(_DP, NeuronType::v, _CN, NeuronType::v, model.getSynapsisParams(sA),
            5),
        _sB(_PCN, NeuronType::v, _CN, NeuronType::v,
            model.getSynapsisParams(sB), 5),
        _sBack(_CN, NeuronType::v, _VPd, NeuronType::v,
               model.getSynapsisParams(sBack), 5),
        _lastSpkTime(0.0) {}

  std::vector<int> run(pattern_t pattern) {
    ProblemConfigType* info = ProblemConfigType::get_instance();

    for (int iPart = 0; iPart < info->getSimParts(pattern); ++iPart) {
      _simSteps.push_back(info->getMaxStep(pattern, iPart));
      iExtNeurons tmpIExtData = {
          info->getNeunInput(pattern, NeuNames()[VPd], iPart),
          info->getNeunInput(pattern, NeuNames()[DP], iPart),
          info->getNeunInput(pattern, NeuNames()[PCN], iPart)};
      _iExt.push_back(std::move(tmpIExtData));
    }

    _randomInitialization();

    return _simPattern();
  }

  NeuronConstructorArgs getNeuronParams(
      const ElectromotorModelStd::neuron n) const {
    NeuronConstructorArgs args;

    for (int i = 0; i < NeuronType::n_parameters; i++) {
      args.params[i] = neuns[n]->get((NeuronParameter)i);
    }

    return args;
  }

  SynapsisConstructorArgs getSynapsisParams(
      const ElectromotorModelStd::synapsis s) const {
    SynapsisConstructorArgs args;

    for (int i = 0; i < SynapsisType::n_parameters; i++) {
      args.params[i] = syns[s]->get((SynapsisParameter)i);
    }

    return args;
  }

  double getStep() const { return _step; }

 private:
  void _printStep() {
    for (auto syn : syns) {
      *_out << syn->get(SynapsisType::i);
    }
    for (auto neun : neuns) {
      *_out << neun->get(NeuronType::v);
    }
    *_out << ModelOutput::endStep;
  }

  int _detectIPI(double voltage, double time) {
    int IPI = NO_SPK;

    bool spk = _detectSpike(voltage, time);
    if (spk == true) {
      IPI = time - _lastSpkTime;
      _lastSpkTime = time;
    }

    return IPI;
  }

  int _detectSpike(double voltage, double time) {
    bool spike = false;

    if ((_lastVol2 < _lastVol1) && (_lastVol1 > voltage) &&
        (_lastVol1 > _vThreshold)) {
      spike = true;
    }

    _lastVol2 = _lastVol1;
    _lastVol1 = voltage;

    return spike;
  }

  void _randomInitialization() {
    int randTime = _timeRange(_getRand);  // RANDOM INITIALIZATION
    for (double t = 0; t < randTime; t += _step) {
      _VPd.add_synaptic_input(_iExt[0].VPd);
      _DP.add_synaptic_input(_iExt[0].DP);
      _PCN.add_synaptic_input(_iExt[0].PCN);

      for (auto s : syns) {
        s->step(_step);
      }
      for (auto n : neuns) {
        n->step(_step);
      }
    }
  }

  std::vector<int> _simPattern() {
    std::vector<int> IPIs;
    int iSubSim = 0, totalt = 0;

    for (int nSubSimSteps : _simSteps) {
      for (double t = 0; t < nSubSimSteps; t += _step) {
        _DP.add_synaptic_input(_iExt[iSubSim].DP);
        _PCN.add_synaptic_input(_iExt[iSubSim].PCN);
        _VPd.add_synaptic_input(_iExt[iSubSim].VPd);
        for (auto s : syns) s->step(_step);
        for (auto n : neuns) n->step(_step);

        if (_out) _printStep();

        int IPI = _detectIPI(_CN.get(NeuronType::v), totalt + t);
        if (IPI > 0) IPIs.push_back(IPI);
      }
      totalt += nSubSimSteps;
      ++iSubSim;
    }

    return IPIs;
  }
};

#endif