/*************************************************************

Copyright (c) 2016, Angel Lareo Fernandez
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

#include <DifferentialNeuronWrapper.h>
#include <DiffusionSynapsis.h>
#include <HindmarshRoseModel.h>
#include <IntegratedSystemWrapper.h>
#include <IzhikevichModel.h>
#include <RungeKutta4.h>
#include <Stepper.h>

#include <iostream>

using namespace std;

typedef RungeKutta4 Integrator;
typedef IntegratedSystemWrapper<IzhikevichModel<double>, Integrator> IzNeuron;

int main(int argc, char **argv) {
  IzNeuron::ConstructorArgs argsIzN;

  argsIzN.params[IzNeuron::a] = 0.02;
  argsIzN.params[IzNeuron::b] = 0.2;
  argsIzN.params[IzNeuron::c] = -50.0;
  argsIzN.params[IzNeuron::d] = 2;  // 0.05;
  argsIzN.params[IzNeuron::threshold] = 30.0;

  IzNeuron CN(argsIzN);

  const double step = 0.1;

  for (double t = 0; t < 500; t += step) {
    CN.step(step);
    cout << CN.get(IzNeuron::v) << endl;
  }

  for (double t = 0; t < 1500; t += step) {
    CN.add_synaptic_input(4);
    CN.step(step);
    cout << CN.get(IzNeuron::v) << endl;
  }

  for (double t = 0; t < 1600; t += step) {
    CN.add_synaptic_input(8);
    CN.step(step);
    cout << CN.get(IzNeuron::v) << endl;
  }

  return 0;
}
