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

#ifndef ELECTROMOTOR_MODEL_SIMULATOR_H_
#define ELECTROMOTOR_MODEL_SIMULATOR_H_

#include <cfloat>
#include <climits>
#include <cmath>
#include <common.hpp>
#include <exception>
#include <numeric>
#include <utility>
#include <vector>

class ElectromotorModelSimulator {
 private:
  std::unique_ptr<ElectromotorModel> _model;
  bool _evalPerformed = false;

  std::array<float, 4> _fitValues;
  float _eval;

  std::vector<std::vector<std::vector<int> > > patternIPIs;

  static const std::vector<float> _patWeight;

  std::vector<std::vector<int> > _IPIs;
  std::array<int, 4> _targetSPI;

 public:
  ElectromotorModelSimulator(ProblemConfig* info)
      : _model(std::make_unique<ElectromotorModel>(info)),
        patternIPIs(info->getPatternIPIs()) {}

  ElectromotorModelSimulator(ProblemConfig* info,
                             std::unique_ptr<ElectromotorModel> model)
      : _model(std::move(model)), patternIPIs(info->getPatternIPIs()) {}

  float runSimulations() { return evaluate(); }

  float evaluate() {
    for (Synapsis* s : _model->syns) {
      if (s->get(Synapsis::alpha) < 0 || s->get(Synapsis::beta) < 0) return 0;
    }

    ProblemConfig* info = ProblemConfig::get_instance();
    _IPIs.reserve(ProblemConfig::n_patterns);

    _eval = 0.0;
    for (unsigned int n = 0; n < ProblemConfig::n_patterns; ++n) {
      ElectromotorModel model(*_model);
      ProblemConfig::pattern pattern = (ProblemConfig::pattern)n;

      _IPIs.push_back(model.run(pattern));

      if (_IPIs[n].size() < 2) {
        return 0;
      }

      _fitValues[n] = _evalPattern(pattern);
      _eval += _patWeight[n] * _fitValues[n];
    }

    _evalPerformed = true;
    return _eval;
  }

  std::vector<std::vector<int> >& getIPIs() { return _IPIs; }

  std::array<int, 4>& getTargets() { return _targetSPI; }

  float getEval() {
    if (!_evalPerformed) evaluate();
    return _eval;
  }

  std::array<float, 4>& getFitValues() {
    if (!_evalPerformed) evaluate();
    return _fitValues;
  }

 private:
  float _evalPattern(ProblemConfig::pattern pattern) {
    unsigned int len = _IPIs[pattern].size();
    float ret = 0.0, minRet = INT_MAX;

    for (unsigned int patI = 0; patI < patternIPIs[pattern].size(); ++patI) {
      int newMaxX = 1000, interpStep = 20;

      std::vector<int> normIPIs = _normalize(_IPIs[pattern], newMaxX);
      std::vector<int> normPatIPIs =
          _normalize(patternIPIs[pattern][patI], newMaxX);

      std::vector<int> interpIPIs = _interp1(normIPIs, interpStep, newMaxX);
      std::vector<int> interpPattern =
          _interp1(normPatIPIs, interpStep, newMaxX);

      std::vector<int> deltaSimIPIs = _diff(interpIPIs);
      std::vector<int> deltaPattern = _diff(interpPattern);

      ret = _meanSquaredError(deltaSimIPIs, deltaPattern);

      if (ret < minRet) {
        minRet = ret;
        _targetSPI[pattern] = patI;
      }
    }

    return 1.0 / (1.0 + minRet);
  }

  std::vector<int> _normalize(std::vector<int> y, int newMaxX) {
    std::vector<int> y_new;
    y_new.reserve(y.size());
    int maxX = std::accumulate(y.begin(), y.end(), 0) - y[0];
    for (unsigned int i = 0; i < y.size(); ++i)
      y_new.push_back(round((float)(newMaxX * y[i]) / maxX));
    return y_new;
  }

  std::vector<int> _diff(std::vector<int>& x) {
    if (x.size() < 2) return {};
    std::vector<int> x_new;
    x_new.reserve(x.size() - 1);
    for (unsigned int i = 1; i < x.size(); ++i) {
      x_new.push_back(x[i] - x[i - 1]);
    }
    return x_new;
  }

  std::vector<int> _interp1(std::vector<int>& y, const int step,
                            const int maxX) {
    if (y.size() < 1) return {};
    std::vector<int> y_new;
    y_new.reserve(maxX / step);

    int x = 0, resample_x = 0;
    for (int i = 0; i + 1 < y.size(); ++i) {
      int x_new = x + y[i + 1];
      int dx = x_new - x;
      int dy = y[i + 1] - y[i];
      float slope = (float)dy / (float)dx;
      float intercept = (float)y[i] - (float)x * slope;
      while (resample_x < x_new) {
        y_new.push_back(slope * resample_x + intercept);
        resample_x += step;
      }
      x = x_new;
    }
    return y_new;
  }

  float _meanSquaredError(std::vector<int>& a, std::vector<int>& b) {
    float ret = 0.0;
    int size = a.size() < b.size() ? a.size() : b.size();
    for (unsigned int i = 0; i < size; ++i) {
      int iSqDiff = (a[i] - b[i]) * (a[i] - b[i]);
      ret += iSqDiff / (a.size() - 1);
    }
    return ret;
  }

  float _meanAbsoluteError(std::vector<int>& a, std::vector<int>& b) {
    float ret = 0.0;
    for (unsigned int i = 0; i < a.size(); ++i) {
      int iDiff = a[i] - b[i];
      ret += fabs(iDiff);
    }
    ret = ret / (a.size() - 1);
    return ret;
  }
};

const std::vector<float> ElectromotorModelSimulator::_patWeight = {
    1 /*scallop*/, 1 /*acceleration*/, 1 /*rasp*/, 1 /*cessation*/};

#endif