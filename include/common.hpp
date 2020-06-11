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

#ifndef COMMON_H_
#define COMMON_H_

#include "DiffusionSynapsis.h"
#include "RungeKutta4.h"
#include "IzhikevichModel.h"
#include "IntegratedSystemWrapper.h"

typedef RungeKutta4 Integrator;
// typedef Stepper StepIntegrator;
// typedef DifferentialNeuronWrapper<HindmarshRoseModel<double>, Integrator>
// Neuron;
typedef IntegratedSystemWrapper<IzhikevichModel<double>, Integrator> Neuron;
typedef DiffusionSynapsis<Neuron, Neuron, Integrator> Synapsis;
// typedef DiffusionSynapsis<Neuron, IzNeuron, Integrator> SynapsisN2IzN;
// typedef DiffusionSynapsis<IzNeuron, Neuron, Integrator> SynapsisIzN2N;
#endif