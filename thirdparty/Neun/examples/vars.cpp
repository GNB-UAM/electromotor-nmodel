/*************************************************************

Copyright (c) 2006, Fernando Herrero Carrón 
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

#include <NeuralNetworks/include/HodgkinHuxleyModel.h>
#include <NeuralNetworks/include/DifferentialNeuronWrapper.h>
#include <NeuralNetworks/include/RungeKutta4.h>

typedef RungeKutta4 Integrator;
typedef DifferentialNeuronWrapper<HodgkinHuxleyModel<double>, Integrator> Neuron;

int main(int argc, char **argv) {
	Neuron::ConstructorArgs args;
	
	args.cm = 1 * 7.854e-3;
 	args.vna = 50;
 	args.vk = -77;
	args.vl = -54.387;
	args.gna = 120 * 7.854e-3;
	args.gk = 36 * 7.854e-3;
	args.gl = 0.3 * 7.854e-3;
		
	Neuron n(args);
	
	n.set_variable(Neuron::v, -80);
	n.set_variable(Neuron::m, 0.1);
	n.set_variable(Neuron::n, 0.7);
	n.set_variable(Neuron::h, 0.01);

	const double step = 0.001;

	for (double t = 0; t < 100; t += step){
		n.step(step);
		
		printf("%f %f\n", t, n.get_variable(Neuron::v));
	}

	return 0;
}
