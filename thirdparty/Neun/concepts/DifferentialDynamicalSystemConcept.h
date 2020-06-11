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

$Id: DifferentialDynamicalSystemConcept.h,v 1.1.2.2 2006/11/28 17:10:04 elferdo Exp $
*************************************************************/

#ifndef DIFFERENTIALDYNAMICALSYSTEMCONCEPT_H_
#define DIFFERENTIALDYNAMICALSYSTEMCONCEPT_H_

#include <boost/concept_check.hpp>
#include "DynamicalSystemConcept.h"

template <typename DifferentialDynamicalSystem>
struct DifferentialDynamicalSystemConcept {
	BOOST_CLASS_REQUIRE(DifferentialDynamicalSystem, , DynamicalSystemConcept);
	
	typename DifferentialDynamicalSystem::precission_t variables[DifferentialDynamicalSystem::n_variables];
	typename DifferentialDynamicalSystem::precission_t increments[DifferentialDynamicalSystem::n_variables];
	typename DifferentialDynamicalSystem::precission_t value;
	
	const DifferentialDynamicalSystem const_system;
		
	void constraints() {
		const_system.eval(variables, increments);
	}
};

/**
 * \class DifferentialDynamicalSystemConcept
 * 
 * A model of this concept must meet the requirements for DynamicalSystemConcept plus:
 * 
 * The following method
 * \li void eval(precission_t [n_variables], precission_t [n_variables]) const

 */
#endif /*DIFFERENTIALDYNAMICALSYSTEMCONCEPT_H_*/
