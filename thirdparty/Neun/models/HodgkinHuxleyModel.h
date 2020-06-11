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

$Id: HodgkinHuxleyModel.h 184 2007-06-04 11:26:12Z elferdo $
*************************************************************/

#ifndef HODGKINHUXLEYMODEL_H_
#define HODGKINHUXLEYMODEL_H_

#include <cmath>
#include "../include/NeuronBase.h"

/**
 * (Hodgkin and Huxley, 1952)
 * cm = 1 * 7.854e-3
 * vna = 50
 * vk = -77
 * vl = -54.387
 * gna = 120 * 7.854e-3
 * gk = 36 * 7.854e-3
 * gl = 0.3 * 7.854e-3
 */
 
template <typename Precission>
class HodgkinHuxleyModel : public NeuronBase<Precission>
{
public:
	typedef Precission precission_t;
	
	enum variable {v, h, m, n, n_variables};
	enum parameter {cm, vna, vk, vl, gna, gk, gl, n_parameters};

protected:

	Precission alpha_h(Precission v) const
	{
		return 0.07 * exp((-v - 65) / 20);
	}
	
	Precission beta_h(Precission v) const
	{
		return 1 / (exp((-v - 35) / 10) + 1);
	}
	
	Precission alpha_m(Precission v) const
	{
		return (0.1 * (-v - 40))/(exp((-v - 40) / 10) - 1);
	}
	
	Precission beta_m(Precission v) const
	{
		return 4 * exp((-v - 65) / 18);
	}
		
	Precission alpha_n(Precission v) const
	{
		return (0.01 * (-v - 55)) / (exp((-v - 55) / 10) - 1);
	}
	
	Precission beta_n(Precission v) const
	{
		return 0.125 * exp((-v - 65) / 80);	
	}
	
public:

	void eval(const Precission * const vars, Precission * const params, Precission * const incs) const
	{
		incs[m] = alpha_m(vars[v]) * (1 - vars[m]) - beta_m(vars[v]) * vars[m];
		incs[h] = alpha_h(vars[v]) * (1 - vars[h]) - beta_h(vars[v]) * vars[h];
		incs[n] = alpha_n(vars[v]) * (1 - vars[n]) - beta_n(vars[v]) * vars[n];
		incs[v] = (SYNAPTIC_INPUT - params[gl] * (vars[v] - params[vl]) - params[gna] * pow(vars[m], 3) * vars[h] * (vars[v] - params[vna]) - params[gk] * pow(vars[n], 4) * (vars[v] - params[vk])) / params[cm];			
	}
};

#endif /*HODGKINHUXLEYMODEL_H_*/
