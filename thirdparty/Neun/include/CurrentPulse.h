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

$Id: CurrentPulse.h 184 2007-06-04 11:26:12Z elferdo $
*************************************************************/

#ifndef CURRENTPULSE_H_
#define CURRENTPULSE_H_

#include <boost/concept_check.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

#include "../concepts/NeuronConcept.h"

template <typename Neuron, typename precission = double>
class CurrentPulse
{
	BOOST_CLASS_REQUIRE(Neuron, ,NeuronConcept);
	BOOST_STATIC_ASSERT(boost::is_floating_point<precission>::value);
	
public:
	enum variable {i, n_variables};
	
private:
	precission m_variables[n_variables];
	
	precission m_local_time;
	
	const precission m_activation_time;
	const precission m_length;
	const precission m_amplitude;
	
	Neuron &m_neuron;
	
public:
	CurrentPulse(Neuron &neuron, precission activation_time, precission length, precission amplitude) : m_neuron(neuron), m_activation_time(activation_time), m_length(length), m_amplitude(amplitude), m_local_time(0)
	{
	}
	
	void step(precission h)
	{
		m_local_time += h;
		
		if((m_activation_time < m_local_time) && (m_local_time < m_activation_time + m_length))
		{
			m_neuron.add_synaptic_input(m_amplitude);
			
			m_variables[i] = m_amplitude;
		} else {
			m_variables[i] = 0;
		}
	}
	
	precission get_variable(variable var) const
	{
		return m_variables[var];
	}

	void set_variable(variable var, precission value)
	{
		m_variables[var] = value;
	}	
};

#endif /*CURRENTPULSE_H_*/
