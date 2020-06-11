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

$Id: RungeKutta4.h 184 2007-06-04 11:26:12Z elferdo $
*************************************************************/

#ifndef RUNGEKUTTA4_H_
#define RUNGEKUTTA4_H_

#ifndef __AVR_ARCH__
#include <boost/concept_check.hpp>
#include "../concepts/SystemConcept.h"
#else
#endif //__AVR_ARCH__


class RungeKutta4
{
public:
	template <typename TSystem>
	static void step(TSystem &s, typename TSystem::precission_t h, typename TSystem::precission_t * const variables, typename TSystem::precission_t * const parameters)
	{
		using namespace std;

#ifndef __AVR_ARCH__
		boost::function_requires<SystemConcept<TSystem> >();
#endif //__AVR_ARCH__

		typedef typename TSystem::precission_t vars_type[TSystem::n_variables];

		vars_type apoyo, retorno;
		vars_type k[4];

		const int dim = TSystem::n_variables;

		s.eval(variables, parameters, k[0]);

		for (int i = 0; i < dim; ++i) {
			apoyo[i] = variables[i] + k[0][i] * h / 2;
		}

		s.eval(apoyo, parameters, k[1]);

		for (int i = 0; i < dim; ++i) {
			apoyo[i] = variables[i] + k[1][i] * h / 2;
		}

		s.eval(apoyo, parameters, k[2]);

		for (int i = 0; i < dim; ++i) {
			apoyo[i] = variables[i] + k[2][i] * h;
		}

		s.eval(apoyo, parameters, k[3]);

		for(int j = 0; j < dim; ++j){
			variables[j] += h / 6 * (k[0][j] + 2 * k[1][j] + 2 * k[2][j] + k[3][j]);
		}
	}
};

/**
 * @class RungeKutta4
 *
 * @brief Implementation of the 4th order Runge-Kutta integration method.
 *
 * @fn void RungeKutta4::step(double const &t, double const &h, TSystem &s, typename TSystem::variables_list_type &variables, typename TSystem::variables_list_type &increments)
 * @param t Simulation time
 * @param h Increment of simulation time
 * @param s System to be simulated
 * @param[in] variables Array consisting of the variables of the system
 * @param[out] increments Array where the calculated increments will be stored
 *
 * This method implements the following algorithm in "parallel" for all
 * variables of the system:
 *
 *
 * @f$\dot x = f(t, x)@f$
@f$ 		ret=f(t, x)@f$

@f$		k0 = h * ret@f$
@f$		x'=x + k0 * .2@f$

@f$		ret=f(t + h / 5, x')@f$

@f$		k1 = h * ret@f$
@f$		x'=x + k0 * 0.075 + k1 * 0.225@f$

@f$		ret=f(t + h * 0.3, x')		@f$

@f$		k2 = h * ret @f$

@f$		x' = x + k0 * .3 - k1 * 0.9 + k2 * 1.2 @f$

@f$		ret = f(t + h * 0.6, x')@f$

@f$		k3 = h * ret @f$

@f$		x' = x + k0 * 0.075 + k1 * 0.675 - k2 * 0.6 + k3 * 0.75 @f$

@f$		ret=f(t + h * 0.9, x') @f$

@f$		k4 = h * ret @f$

@f$		x' = x + k0 * 0.660493827160493 + k1 * 2.5 - k2 * 5.185185185185185 + k3 * 3.888888888888889 - k4 * 0.864197530864197 @f$

@f$		ret = f(t + h, x') @f$

@f$		k5 = h * ret @f$

@f$		\delta x = k0 * 0.098765432098765 + k2 * 0.396825396825396 + k3 * 0.231481481481481 + k4 * 0.308641975308641 - k5 * 0.035714285714285 @f$

 */

#endif /*RUNGEKUTTA4_H_*/
