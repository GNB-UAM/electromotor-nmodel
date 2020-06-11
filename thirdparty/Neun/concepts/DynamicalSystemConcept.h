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

$Id: DynamicalSystemConcept.h,v 1.3.2.2 2006/11/28 17:10:04 elferdo Exp $
*************************************************************/

#ifndef DYNAMICALSYSTEMCONCEPT_H_
#define DYNAMICALSYSTEMCONCEPT_H_

template <typename DynamicalSystem>
struct DynamicalSystemConcept {
	
	typename DynamicalSystem::variable v;
	typename DynamicalSystem::parameter p;
	typename DynamicalSystem::precission_t value;
	
	DynamicalSystem system;
	const DynamicalSystem const_system;
	
	int n_variables, n_parameters;
	
	void constraints() {
		value = const_system.get(v);
		value = const_system.get(p);
		
		system.set(v, value);
		system.set(p, value);
		
		system.step(value);
	}
};

/**
 * \class DynamicalSystemConcept
 * 
 * Dynamical systems are a set of variables that evolve with time.
 * 
 * A model of this concept must define:
 * 
 * The following types
 * \li variable
 * \li parameter
 * \li precission_t
 * 
 * The following integers
 * \li n_variables
 * \li n_parameters
 * 
 * And the following methods
 * \li precission_t get_variable(variable) const
 * \li precission_t get_parameter(parameter) const
 * \li void set_variable(variable, precission_t)
 * \li void set_parameter(parameter, precission_t)
 * \li void step(precission_t)
 */
#endif /*DYNAMICALSYSTEMCONCEPT_H_*/
