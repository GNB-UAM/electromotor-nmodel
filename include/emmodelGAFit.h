/*************************************************************

Copyright (c)   2020, Ángel Lareo Fernández
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
#ifndef EMMODEL_GAFIT_HPP
#define EMMODEL_GAFIT_HPP

#define INSTANTIATE_REAL_GENOME
#include <ga/GARealGenome.h>
#include <ga/ga.h>
#include <ga/std_stream.h>

#include <fstream>
#include <iostream>

#include "ElectromotorModelSimulator.hpp"
#include "ProblemConfig.hpp"

float Objective(GAGenome&);
std::unique_ptr<ElectromotorModel> mutateNModel(GARealGenome& g);
void printResult(GARealGenome& realBestGen);

GARealGenome createGenome();
GAParameterList createParameterList();
void runGA(GASteadyStateGA& ga);

GABoolean GATerminateUponScore(GAGeneticAlgorithm& ga);
GABoolean GATerminateUponGeneration(GAGeneticAlgorithm& ga);
GABoolean GATerminateUponGenerationWithStatePrintout(GAGeneticAlgorithm& ga);

static const std::vector<std::string> synNames = {"VPd_DP", "VPd_PCN", "DP_CN",
                                                  "PCN_CN", "CN_VPd"};
static const std::vector<std::string> varParamsNames = {"alpha", "beta", "gsyn",
                                                        "max_release_time"};
static const std::vector<int> varParams = {Synapsis::alpha, Synapsis::beta,
                                           Synapsis::gsyn,
                                           Synapsis::max_release_time};

bool testFile(std::string fileName) {
  if (!fileName.empty()) return false;
  std::ifstream test(fileName);
  if (!test.good()) {
    std::cerr << "Error: Cannot find config file" << std::endl;
    return false;
  }
  return true;
}

#endif  // EMMODEL_GAFIT_HPP