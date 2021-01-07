//      EMConfig.h
//
//      Copyright 2017 Ángel Lareo <angel.lareo@gmail.com>
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
#ifndef E_M_CONFIG_H_
#define E_M_CONFIG_H_

#include <yaml.h>

#include <cassert>
#include <fstream>
#include <string>
#include <type_traits>

#include "Singleton.hpp"

template <typename NeuronType, typename SynapsisType>
class EMConfig : public Singleton<EMConfig<NeuronType, SynapsisType> > {
  friend class Singleton<EMConfig<NeuronType, SynapsisType> >;

 public:
  typedef NeuronType neuron_t;
  typedef SynapsisType synapsis_t;
  typedef typename NeuronType::precission_t precission_t;
  typedef typename NeuronType::ConstructorArgs NeuronConstructorArgs;
  typedef typename SynapsisType::ConstructorArgs SynapsisConstructorArgs;

 protected:
  const float sensibility = 0.00001;

  int activePattern = 0;
  float _durationIncr = 0.0;
  float _intensityIncr = 0.0;

  YAML::Node _config;
  YAML::Emitter _out;

 public:
  enum pattern { scallop, acceleration, rasp, cessation, n_patterns };

  static constexpr std::vector<std::string> testNames() {
    return std::vector<std::string>{"scal_test", "acc_test", "rasp_test",
                                    "cess_test"};
  };

  static constexpr std::vector<std::string> patternNames() {
    return std::vector<std::string>{"scallop", "acceleration", "rasp",
                                    "cessation"};
  };

  EMConfig(std::string fileName) { _config = YAML::LoadFile(fileName); }

  EMConfig() {
    assert(!_config);
    std::cout << "Problem Config error: " << _out.GetLastError() << "\n";
  }

  void writeOutput(std::string outFileName) {
    std::ofstream fout(outFileName);
    fout << _out.c_str();
  }

  NeuronConstructorArgs getNeuronParams(std::string neunName) {
    NeuronConstructorArgs args;
    YAML::Node NeuronConfig = _config[neunName];

    args.params[NeuronType::a] = NeuronConfig["a"].as<precission_t>();
    args.params[NeuronType::b] = NeuronConfig["b"].as<precission_t>();
    args.params[NeuronType::c] = NeuronConfig["c"].as<precission_t>();
    args.params[NeuronType::d] = NeuronConfig["d"].as<precission_t>();
    args.params[NeuronType::threshold] =
        NeuronConfig["threshold"].as<precission_t>();

    return args;
  }

  void printNeuronParams(std::string neunName, NeuronConstructorArgs args) {
    _out << YAML::BeginMap;
    _out << YAML::Key << neunName.c_str();
    _out << YAML::Value << YAML::BeginSeq << args.params[NeuronType::a]
         << args.params[NeuronType::b] << args.params[NeuronType::c]
         << args.params[NeuronType::d] << args.params[NeuronType::threshold]
         << YAML::EndSeq;
    _out << YAML::EndMap;

    assert(!_out.good());
    std::cout << "Emitter error: " << _out.GetLastError() << "\n";
  }

  SynapsisConstructorArgs getSynapsisParams(std::string synapsisName) {
    SynapsisConstructorArgs args;
    YAML::Node SynapsisConfig = _config[synapsisName];

    args.params[SynapsisType::alpha] =
        SynapsisConfig["alpha"].as<precission_t>();
    args.params[SynapsisType::beta] = SynapsisConfig["beta"].as<precission_t>();
    args.params[SynapsisType::threshold] =
        SynapsisConfig["threshold"].as<precission_t>();
    args.params[SynapsisType::esyn] = SynapsisConfig["esyn"].as<precission_t>();
    args.params[SynapsisType::gsyn] = SynapsisConfig["gsyn"].as<precission_t>();
    args.params[SynapsisType::T] = SynapsisConfig["T"].as<precission_t>();
    args.params[SynapsisType::max_release_time] =
        SynapsisConfig["max_release_time"].as<precission_t>();
    return args;
  }

  void printSynapsisParams(std::string synapsisName,
                           SynapsisConstructorArgs args) {
    _out << YAML::BeginMap;
    _out << YAML::Key << synapsisName.c_str();
    _out << YAML::Value << YAML::BeginSeq << args.params[SynapsisType::alpha]
         << args.params[SynapsisType::beta]
         << args.params[SynapsisType::threshold]
         << args.params[SynapsisType::esyn] << args.params[SynapsisType::gsyn]
         << args.params[SynapsisType::T]
         << args.params[SynapsisType::max_release_time] << YAML::EndSeq;
    _out << YAML::EndMap;

    assert(!_out.good());
    std::cout << "Emitter error: " << _out.GetLastError() << "\n";
  }

  //@todo: add error control!
  precission_t getNeunInput(std::string neunName, int iPart) {
    precission_t value =
        _config[neunName + "_in"][iPart].template as<precission_t>();
    if (iPart < _config["simulation"].size() - 1)
      return (value * _intensityIncr) + value;
    return value;
  }

  precission_t getNeunInput(EMConfig::pattern pattern, std::string neunName,
                            int iPart) {
    precission_t value = _config[testNames()[pattern]][neunName + "_in"][iPart]
                             .template as<precission_t>();
    if (iPart < _config["simulation"].size() - 1)
      return (value * _intensityIncr) + value;
    return value;
  }

  void resetStimuliDuration() { _durationIncr = 0.0; }

  void incrementStimuliIntensity(float dIntensity = 0.05) {
    _intensityIncr += dIntensity;
    if (_intensityIncr < sensibility && _intensityIncr > -sensibility)
      _intensityIncr = 0;
  }
  void decrementStimuliIntensity(float dIntensity = 0.05) {
    _intensityIncr -= dIntensity;
    if (_intensityIncr < sensibility && _intensityIncr > -sensibility)
      _intensityIncr = 0;
  }
  void resetStimuliIntensity() { _intensityIncr = 0.0; }

  void setIncrStimuliIntensity(float intensityIncr) {
    _intensityIncr = intensityIncr;
  }
  void setIncrStimuliDuration(float durationIncr) {
    _durationIncr = durationIncr;
  }

  float getIncrStimuliIntensity() { return _intensityIncr; }

  float getIncrStimuliDuration() { return _durationIncr; }

  int getSimParts() { return _config["simulation"].size(); }

  int getSimParts(EMConfig::pattern pattern) {
    return _config[testNames()[pattern]]["simulation"].size();
  }

  precission_t getMaxStep(int iPart) {
    precission_t value =
        _config["simulation"][iPart].template as<precission_t>();
    // if ((iPart > 0) && (iPart < _config["simulation"].size() - 1))
    if (iPart < _config["simulation"].size() - 1)
      return (value * _durationIncr) + value;
    return value;
  }

  precission_t getMaxStep(EMConfig::pattern pattern, int iPart) {
    precission_t value = _config[testNames()[pattern]]["simulation"][iPart]
                             .template as<precission_t>();
    // if ((iPart > 0) && (iPart < _config["simulation"].size() - 1))
    if (iPart < _config["simulation"].size() - 1)
      return (value * _durationIncr) + value;
    return value;
  }

  precission_t getStep() { return _config["step"].template as<precission_t>(); }

  std::vector<std::vector<std::vector<int> > > getPatternIPIs() {
    std::vector<std::vector<std::vector<int> > > patternIPIs;
    for (unsigned int n = 0; n < n_patterns; ++n) {
      std::vector<std::vector<int> > pattern;
      for (unsigned int i = 0; i < _config["targets"][patternNames()[n]].size();
           ++i) {
        std::vector<int> patternEx;
        for (unsigned int j = 0;
             j < _config["targets"][patternNames()[n]][i].size(); ++j) {
          precission_t aux = _config["targets"][patternNames()[n]][i][j]
                                 .template as<precission_t>();
          patternEx.push_back(aux);
        }
        pattern.push_back(patternEx);
      }
      patternIPIs.push_back(pattern);
    }
    return patternIPIs;
  }
};

#endif
