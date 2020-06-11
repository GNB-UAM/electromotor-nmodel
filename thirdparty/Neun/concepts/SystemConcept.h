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

$Id: SystemConcept.h 184 2007-06-04 11:26:12Z elferdo $
*************************************************************/

#ifndef SYSTEMCONCEPT_H_
#define SYSTEMCONCEPT_H_

#include <boost/concept_check.hpp>
#include "ModelConcept.h"

template <typename System>
struct SystemConcept {
//	BOOST_CLASS_REQUIRE(System, ,ModelConcept);

	typename System::precission_t value;
	typename System::variable v;
	typename System::parameter p;

	System system;
	const System const_system;

	int n_variables, n_parameters;

	void constraints() {
//		typename System::ConstructorArgs args;
//		args[p] = value;

//		System csystem(args);

		value = const_system.get(v);
		value = const_system.get(p);

		system.set(v, value);
		system.set(p, value);
	}
};

/**
 * \class SystemConcept
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
 * \li precission_t get(variable) const
 * \li precission_t get(parameter) const
 * \li void set(variable, precission_t)
 * \li void set(parameter, precission_t)
 * \li void step(precission_t)
 */
#endif /*DYNAMICALSYSTEMCONCEPT_H_*/
