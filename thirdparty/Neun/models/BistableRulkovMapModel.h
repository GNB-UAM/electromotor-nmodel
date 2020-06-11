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

$Id: RulkovMapModel.h 184 2007-06-04 11:26:12Z elferdo $
*************************************************************/

#ifndef BISTABLERULKOVMAPMODEL_H_
#define BISTABLERULKOVMAPMODEL_H_

#include <cmath>
#include "../include/NeuronBase.h"

/** (Nikolai F. Rulkov, 2002)
 * alpha = 3
 * mu = 0.001
 * sigma = 0.1
 * betae = 1
 * sigmae = 1
 */
template <typename Precission>
class BistableRulkovMapModel : public NeuronBase<Precission>{
public:
	typedef Precission precission_t;
	
	enum variable {x, y, sigma, n_variables};
	enum parameter {alpha, mu, sigmae, betae, point, n_parameters};

protected:

	Precission f(Precission _alpha, Precission x, Precission y) const
	{
		if(x <= 0){
			return _alpha / (1 - x) + y;
		}
		else if(x < _alpha + y){
			return _alpha + y;
		}
		else{
			return -1;
		}
	}
	
public:
	void eval(const Precission * const vars, Precission * const params, Precission * const incs) const
	{
		incs[x] = f(params[alpha], vars[x], vars[y] + params[betae] * SYNAPTIC_INPUT);
		incs[y] = vars[y] + params[mu] * (-(vars[x] + 1) + vars[sigma] + params[sigmae] * SYNAPTIC_INPUT);
		incs[sigma] = params[point] * (tanh(2 * vars[sigma]) + SYNAPTIC_INPUT);
	}
};

#endif /*BISTABLERULKOVMAPMODEL_H_*/
