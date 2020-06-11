/*************************************************************

Copyright (c)   2020, Ángel Lareo Fernández
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

#include "emmodelGAFit.h"

using namespace std;

static void show_usage(string name) {
  std::cerr
      << "Usage: " << name << " <option(s)> SOURCES" << endl
      << "Options:\n"
      << "\t-h,--help\t\tShow this message.\n"
      << "\t-i,--input\t\tInput file.\n"
      << "\t-o,--output\t\tOutput file\n"
      << "\t-g,--generations\tNumber of generations.\n"
      << "\t-e,--econv\t\tStop convergence value.\n"
      << "\t-s,--statistics\t\tStatistics output file.\n"
      << "\t-n,--number\t\tNumber of individuals per generation.\n"
      << "\t-a,--alpha\t\tManual limits [-a,a] for alpha parameter.\n"
      << "\t-b,--beta\t\tManual limits [-b,b] for beta parameter.\n"
      << "\t-t,--gsyn\t\tManual limits [-t,t] for the conductivity parameter.\n"
      << "\t-m,--maxreleasetime\tManual limits [-m,m] for maximum release time "
         "parameter.\n"
      << "\t-p,--percentage\tPercentual limits from the initial value for "
         "each parameter.\n"
      << "\t-q,--printEachGen\tPrint bestGA each q generations" << endl;
}

int length = 20;  // Number of alleles static const std::vector < std::string >

std::vector<float> limits = {4.5, 0.05, 0.45, 70};
float percentage = 0.0;
bool isLimited = true;

int populationSize = 110;
int nGenerations = 100;
float pConv = 0.0;
bool endsDueToPConv = false;

string inputFilename, outputFilename, statisticsFilename;
int printEachGens = 0, lastPrintedGen = 0;

const int MAXGENS = 5000;

int main(int argc, char** argv) {
  int c;

  while ((c = getopt(argc, argv, "hi:o:g:n:s:a:b:t:m:p:e:q:")) !=
         -1) {  //@todo: use long options
    switch (c) {
      case 'h':
        show_usage(argv[0]);
        break;
      case 'i':
        inputFilename = optarg;
        break;
      case 'o':
        outputFilename = optarg;
        break;
      case 'g':
        nGenerations = atoi(optarg);
        // if (generations > MAXGENS) generations = MAXGENS;
        break;
      case 'n':
        populationSize = atoi(optarg);
        break;
      case 's':
        statisticsFilename = optarg;
        break;
      case 'a': /*alpha*/
        limits[0] = atof(optarg);
        break;
      case 'b': /*betha*/
        limits[1] = atof(optarg);
        break;
      case 't': /*gsyn*/
        limits[2] = atof(optarg);
        break;
      case 'm': /*max_release_time*/
        limits[3] = atof(optarg);
        break;
      case 'p':
        percentage = atof(optarg) / 100;
        break;
      case 'e':
        pConv = atof(optarg);
        break;
      case 'q':
        printEachGens = atoi(optarg);
        break;
    }
  }

  testFile(inputFilename);
  ProblemConfig* info = ProblemConfig::get_instance(inputFilename);

  GASteadyStateGA ga(createGenome());

  runGA(ga);

  /* Printing Result */
  printResult((GARealGenome&)ga.statistics().bestIndividual());

  ProblemConfig::destroy_instance();
  return 0;
}

void runGA(GASteadyStateGA& ga) {
  unsigned int seed = time(NULL);

  ga.parameters(createParameterList());

  if (endsDueToPConv) {
    ga.pConvergence(pConv);
    ga.terminator(GATerminateUponScore);
  } else
    ga.terminator(GATerminateUponGeneration);

  ga.pReplacement(0.9);

  // GANoScaling scalSch; ga.scaling(scalSch);
  // GARankSelector rankSelect; ga.selector(rankSelect);

  if (testFile(statisticsFilename))
    ga.set(gaNscoreFilename, statisticsFilename.c_str());

  ga.evolve(seed);
}

GARealGenome createGenome() {
  GARealAlleleSet alleles(-1, 1, GAAllele::EXCLUSIVE, GAAllele::INCLUSIVE);
  GARealGenome genome(length, alleles, Objective);

  genome.initializer(GARealUniformInitializer);
  genome.crossover(GARealOnePointCrossover);
  genome.mutator(GARealSwapMutator);

  return genome;
}

GAParameterList createParameterList() {
  GAParameterList params;

  if (!endsDueToPConv) params.set(gaNnGenerations, nGenerations);

  params.set(gaNpopulationSize, populationSize);

  params.set(gaNscoreFrequency, 1);
  params.set(gaNflushFrequency, 10);
  params.set(gaNselectScores, (int)GAStatistics::AllScores);

  GASteadyStateGA::registerDefaultParameters(params);

  return params;
}

// Objective function
float Objective(GAGenome& g) {
  ProblemConfig* info = ProblemConfig::get_instance();
  GARealGenome& genome = (GARealGenome&)g;
  ElectromotorModelSimulator nmodel(info, std::move(mutateNModel(genome)));

  return nmodel.evaluate();
}

unique_ptr<ElectromotorModel> mutateNModel(GARealGenome& g) {
  ProblemConfig* info = ProblemConfig::get_instance();
  unique_ptr<ElectromotorModel> nmodel =
      std::make_unique<ElectromotorModel>(info);

  int iSyn = 0, iParam = 0;

  for (Synapsis* s : nmodel->syns) {
    iParam = 0;
    for (int paramVal : varParams) {
      double paramNewVal;
      if (isLimited) {
        paramNewVal =
            s->get((Synapsis::parameter)paramVal) +
            (g.gene(iSyn * varParamsNames.size() + iParam) * limits[iParam]);
      } else {
        paramNewVal = s->get((Synapsis::parameter)paramVal) +
                      (g.gene(iSyn * varParamsNames.size() + iParam) *
                       s->get((Synapsis::parameter)paramVal) * percentage);
      }

      if (paramNewVal < 0 &&
          (paramVal == Synapsis::alpha || paramVal == Synapsis::beta ||
           paramVal == Synapsis::max_release_time)) {
        paramNewVal = -paramNewVal;
      }

      if (paramVal == Synapsis::gsyn) {
        if (((s->get((Synapsis::parameter)paramVal) < 0) &&
             (paramNewVal > 0)) ||
            ((s->get((Synapsis::parameter)paramVal) > 0) && (paramNewVal < 0)))
          paramNewVal = -paramNewVal;
      }

      s->set((Synapsis::parameter)paramVal, paramNewVal);
      ++iParam;
    }
    ++iSyn;
  }

  return nmodel;
}

GABoolean GATerminateUponScore(GAGeneticAlgorithm& ga) {
  if (ga.generation() >= MAXGENS) return gaTrue;
  if (ga.statistics().current(GAStatistics::Maximum) > ga.pConvergence())
    return gaTrue;
  else
    return gaFalse;
}

GABoolean GATerminateUponGeneration(GAGeneticAlgorithm& ga) {
  if (ga.generation() >= nGenerations) return gaTrue;
  return gaFalse;
}

GABoolean GATerminateUponGenerationWithStatePrintout(GAGeneticAlgorithm& ga) {
  if (printEachGens > 0 && ga.generation() > lastPrintedGen) {
    lastPrintedGen += printEachGens;
    printResult((GARealGenome&)ga.statistics().bestIndividual());
  }

  if (ga.generation() >= nGenerations)
    return gaTrue;
  else
    return gaFalse;
}

void printResult(GARealGenome& realBestGen) {
  unique_ptr<ElectromotorModel> nmodel = mutateNModel(realBestGen);

  ofstream fOut;
  fOut.open(outputFilename, std::fstream::out | std::fstream::app);
  std::ostream& out = fOut ? fOut : std::cout;

  out << "#n: " << populationSize;

  if (endsDueToPConv)
    out << " pconv: " << pConv;
  else
    out << " g: " << nGenerations;
  out << std::endl;

  if (percentage > 0.0)
    out << "#percentage: " << percentage * 100 << std::endl;
  else
    out << "#lims: [" << limits[0] << ", " << limits[1] << ", " << limits[2]
        << ", " << limits[3] << "]\n"
        << std::endl;

  out << "#The final GA generated:" << std::endl;
  for (unsigned i = 0; i < 5; i++) {
    out << synNames[i] << ":" << std::endl;
    for (unsigned j = 0; j < varParams.size(); j++) {
      out << "  " << varParamsNames[j] << ": "
          << nmodel->syns[i]->get((Synapsis::parameter)varParams[j])
          << std::endl;
    }
    out << "  threshold: 0\n  esyn: -80\n  T: 1.0" << std::endl;
  }
  out << "#Score: " << realBestGen.score() << std::endl;
}