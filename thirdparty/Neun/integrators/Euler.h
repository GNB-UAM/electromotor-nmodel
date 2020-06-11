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

$Id: Euler.h 184 2007-06-04 11:26:12Z elferdo $
*************************************************************/

#ifndef EULER_H_
#define EULER_H_

#ifndef __AVR_ARCH__
#include <boost/concept_check.hpp>
#include "../concepts/SystemConcept.h"
#endif //__AVR_ARCH__


class Euler
{
public:
	template <typename TSystem>
	static void step(TSystem &s, typename TSystem::precission_t h, typename TSystem::precission_t * const variables, typename TSystem::precission_t * const parameters)
	{
		using namespace std;

#ifndef __AVR_ARCH__
		boost::function_requires<SystemConcept<TSystem> >();
#endif //__AVR_ARCH__

		typename TSystem::precission_t results[TSystem::n_variables];

		const int dim = TSystem::n_variables;

		s.eval(variables, parameters, results);

		for(int i = 0; i < dim; ++i){
			variables[i] += h * results[i];
		}
	}
};


#endif /*EULER_H_*/
