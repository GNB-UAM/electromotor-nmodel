/*************************************************************

Copyright (c)   2016, Ángel Lareo Fernández
All rights reserved.

Please, if you use this model or the code of the genetic
algorithm, cite in your publication the following paper:
A. Lareo, P. Varona. F. Rodríguez. Modeling the variability
of the electromotor command system of pulse mormyrids.
BioRxiv 10.1101/2020.06.09.142083

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

#include <unistd.h>

#include <fstream>
#include <iostream>
#include <random>

#include "ElectromotorModel.hpp"
#include "ProblemConfig.hpp"
#include "common.hpp"

using namespace std;

static void show_usage(string name) {
  std::cerr << "Usage: " << name << " <option(s)> SOURCES" << endl
            << "Options:\n"
            << "\t-h,--help\t\tShow this message.\n"
            << "\t-i,--input\t\tInput file.\n"
            << "\t-o,--output\t\tOutput file\n"
            << "\t-s\t\t\tPrint synapses" << endl;
}

const std::vector<std::string> ofPos = {"_sca", "_acc", "_rasp", "_cess"};

int main(int argc, char** argv) {
  string inputFilename, outputFilename;
  int c;
  bool printSynapses = false;

  while ((c = getopt(argc, argv, "hi:o:")) != -1) {  //@todo: use long options
    switch (c) {
      case 'h':
        show_usage(argv[0]);
        break;
      case 'i':
        inputFilename += optarg;
        break;
      case 'o':
        outputFilename += optarg;
        break;
    }
  }

  ifstream test(inputFilename);
  if (!test.good()) {
    cerr << "Error: Cannot find config file" << endl;
    show_usage(argv[0]);
    return 0;
  }
  ProblemConfig* info = ProblemConfig::get_instance(inputFilename);

  for (unsigned int n = 0; n < ProblemConfig::n_patterns; ++n) {
    ElectromotorModel emmodel(info, outputFilename + ofPos[n]);
    std::cout << n << " pattern: " << outputFilename + ofPos[n] << std::endl;
    ProblemConfig::pattern pattern = (ProblemConfig::pattern)n;
    emmodel.run(pattern);
  }

  ProblemConfig::destroy_instance();

  return 0;
}
