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

$Id: FerdoMapModel.h 184 2007-06-04 11:26:12Z elferdo $
*************************************************************/

#ifndef FERDOMAPMODEL_H_
#define FERDOMAPMODEL_H_

#include <algorithm>
#include <cmath>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

/** (Ferdo, 2007)
 * alpha = 3
 * mu = 0.001
 * sigma = 0.1
 * betae = 1
 * sigmae = 1
 */
template <typename Precission>
class FerdoMapModel {
	BOOST_STATIC_ASSERT(boost::is_floating_point<Precission>::value);
	
public:
	typedef Precission precission_t;
	
	enum variable {x, y, z, n_variables};
	enum parameter {alpha, mu, sigma, betae, sigmae, lambda, gammae, n_parameters};

protected:

	Precission m_variables[n_variables];
	Precission m_parameters[n_parameters];
	Precission m_synaptic_input;

	Precission f(Precission x, Precission y) const
	{
		if(x <= 0){
			return m_parameters[alpha] / (1 - x) + y;
		}
		else if(x < m_parameters[alpha] + y){
			return m_parameters[alpha] + y;
		}
		else{
			return -1;
		}
	}
	
	Precission g(Precission x) const
	{
		if(x <= -1.1){
			return 1;
		} else {
			return 0;
		}
	}
	
public:
	struct ConstructorArgs
	{
		Precission params[n_parameters];
	};
	
	FerdoMapModel(ConstructorArgs const &args) : m_synaptic_input(0)
	{
		std::copy(args.params, args.params + n_parameters, m_parameters);
	}

	void step(Precission h)
	{
		m_variables[x] = f(m_variables[x], m_variables[y] + m_parameters[betae] * m_synaptic_input);
		m_variables[y] = m_variables[y] + m_parameters[mu] * (-(m_variables[x] + 1) + m_parameters[sigma] + m_parameters[sigmae] * m_synaptic_input) + g(m_variables[x]) * m_variables[z];
		m_variables[z] = m_variables[z] - m_parameters[lambda] * m_variables[z] + m_parameters[gammae] * m_synaptic_input;
		
		m_synaptic_input = 0;		
	}
};

#endif /*FERDOMAPMODEL_H_*/
