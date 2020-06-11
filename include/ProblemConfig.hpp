//      problemConfig.h
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
#ifndef PROBLEMCONFIG_H_
#define PROBLEMCONFIG_H_

#include <yaml.h>
#include <string>
#include <fstream>
#include <cassert>

#include "Singleton.hpp"
#include "common.hpp"

//@todo{change double to precission_t}
// template <typename Precission = double>
class ProblemConfig : public Singleton<ProblemConfig> {
  friend class Singleton<ProblemConfig>;
  const float sensibility = 0.00001;

  int activePattern = 0;
  float _durationIncr = 0.0;
  float _intensityIncr = 0.0;

 protected:
  YAML::Node _config;
  YAML::Emitter _out;

 public:
  // typedef Precission precission_t;
  typedef double precission_t;

  enum pattern { scallop, acceleration, rasp, cessation, n_patterns };
  static const std::vector<std::string> testNames;
  static const std::vector<std::string> patternNames;

  ProblemConfig(std::string fileName) { _config = YAML::LoadFile(fileName); }

  ProblemConfig() {
    assert(!_config);
    std::cout << "Problem Config error: " << _out.GetLastError() << "\n";
  }

  void writeOutput(std::string outFileName) {
    std::ofstream fout(outFileName);
    fout << _out.c_str();
  }

  Neuron::ConstructorArgs getNeuronParams(std::string neunName) {
    Neuron::ConstructorArgs args;
    YAML::Node NeuronConfig = _config[neunName];

    args.params[Neuron::a] = NeuronConfig["a"].as<precission_t>();
    args.params[Neuron::b] = NeuronConfig["b"].as<precission_t>();
    args.params[Neuron::c] = NeuronConfig["c"].as<precission_t>();
    args.params[Neuron::d] = NeuronConfig["d"].as<precission_t>();
    args.params[Neuron::threshold] =
        NeuronConfig["threshold"].as<precission_t>();

    return args;
  }

  void printNeuronParams(std::string neunName, Neuron::ConstructorArgs args) {
    _out << YAML::BeginMap;
    _out << YAML::Key << neunName.c_str();
    _out << YAML::Value << YAML::BeginSeq << args.params[Neuron::a]
         << args.params[Neuron::b] << args.params[Neuron::c]
         << args.params[Neuron::d] << args.params[Neuron::threshold]
         << YAML::EndSeq;
    _out << YAML::EndMap;

    assert(!_out.good());
    std::cout << "Emitter error: " << _out.GetLastError() << "\n";
  }

  Synapsis::ConstructorArgs getSynapsisParams(std::string synapsisName) {
    Synapsis::ConstructorArgs args;
    YAML::Node SynapsisConfig = _config[synapsisName];

    args.params[Synapsis::alpha] = SynapsisConfig["alpha"].as<precission_t>();
    args.params[Synapsis::beta] = SynapsisConfig["beta"].as<precission_t>();
    args.params[Synapsis::threshold] =
        SynapsisConfig["threshold"].as<precission_t>();
    args.params[Synapsis::esyn] = SynapsisConfig["esyn"].as<precission_t>();
    args.params[Synapsis::gsyn] = SynapsisConfig["gsyn"].as<precission_t>();
    args.params[Synapsis::T] = SynapsisConfig["T"].as<precission_t>();
    args.params[Synapsis::max_release_time] =
        SynapsisConfig["max_release_time"].as<precission_t>();
    return args;
  }

  void printSynapsisParams(std::string synapsisName,
                           Synapsis::ConstructorArgs args) {
    _out << YAML::BeginMap;
    _out << YAML::Key << synapsisName.c_str();
    _out << YAML::Value << YAML::BeginSeq << args.params[Synapsis::alpha]
         << args.params[Synapsis::beta] << args.params[Synapsis::threshold]
         << args.params[Synapsis::esyn] << args.params[Synapsis::gsyn]
         << args.params[Synapsis::T] << args.params[Synapsis::max_release_time]
         << YAML::EndSeq;
    _out << YAML::EndMap;

    assert(!_out.good());
    std::cout << "Emitter error: " << _out.GetLastError() << "\n";
  }
  
  //@todo: add error control!
  precission_t getNeunInput(std::string neunName, int iPart) {
    precission_t value = _config[neunName + "_in"][iPart].as<precission_t>();
    // if ((iPart > 0) && (iPart < _config["simulation"].size() - 1))
    if (iPart < _config["simulation"].size() - 1)
      return (value * _intensityIncr) + value;
    return value;
  }

  precission_t getNeunInput(ProblemConfig::pattern pattern,
                            std::string neunName, int iPart) {
    precission_t value =
        _config[testNames[pattern]][neunName + "_in"][iPart].as<precission_t>();
    //if ((iPart > 0) && (iPart < _config["simulation"].size() - 1))
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

  int getSimParts(ProblemConfig::pattern pattern) {
    return _config[testNames[pattern]]["simulation"].size();
  }

  precission_t getMaxStep(int iPart) {
    precission_t value = _config["simulation"][iPart].as<precission_t>();
    //if ((iPart > 0) && (iPart < _config["simulation"].size() - 1))
    if (iPart < _config["simulation"].size() - 1)
      return (value * _durationIncr) + value;
    return value;
  }

  precission_t getMaxStep(ProblemConfig::pattern pattern, int iPart) {
    precission_t value =
        _config[testNames[pattern]]["simulation"][iPart].as<precission_t>();
    //if ((iPart > 0) && (iPart < _config["simulation"].size() - 1))
    if (iPart < _config["simulation"].size() - 1)
      return (value * _durationIncr) + value;
    return value;
  }

  precission_t getStep() { return _config["step"].as<precission_t>(); }

  std::vector<std::vector<std::vector<int> > > getPatternIPIs() {
    std::vector<std::vector<std::vector<int> > > patternIPIs;
    for (unsigned int n = 0; n < n_patterns; ++n) {
      std::vector<std::vector<int> > pattern;
      for (unsigned int i = 0; i < _config["targets"][patternNames[n]].size();
           ++i) {
        std::vector<int> patternEx;
        for (unsigned int j = 0;
             j < _config["targets"][patternNames[n]][i].size(); ++j) {
          patternEx.push_back(
              _config["targets"][patternNames[n]][i][j].as<int>());
        }
        pattern.push_back(patternEx);
      }
      patternIPIs.push_back(pattern);
    }
    return patternIPIs;
  }
};

const std::vector<std::string> ProblemConfig::testNames = {
    "scal_test", "acc_test", "rasp_test", "cess_test"};
const std::vector<std::string> ProblemConfig::patternNames = {
    "scallop", "acceleration", "rasp", "cessation"};
#endif