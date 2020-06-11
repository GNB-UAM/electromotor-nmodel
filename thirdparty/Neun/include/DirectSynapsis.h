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

$Id: DirectSynapsis.h 184 2007-06-04 11:26:12Z elferdo $
*************************************************************/

#ifndef DIRECTSYNAPSIS_H_
#define DIRECTSYNAPSIS_H_

#include <boost/concept_check.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include "../concepts/NeuronConcept.h"

/**
 * Implements a conductance based synapsis with threshold.
 */
 
template <typename TNode1, typename TNode2, typename precission = double>
class DirectSynapsis {
	BOOST_CLASS_REQUIRE(TNode1, , NeuronConcept);
	BOOST_CLASS_REQUIRE(TNode2, , NeuronConcept);
	BOOST_STATIC_ASSERT(boost::is_floating_point<precission>::value);
	
public:
	enum parameter {g, t, n_parameters};
	
private:
	DirectSynapsis(DirectSynapsis &s)
	{
	}
	
	void operator=(DirectSynapsis &s)
	{
	}

	precission m_parameters[n_parameters];
	
	TNode1 const &m_n1;
	TNode2 &m_n2;
	
	const typename TNode1::variable m_n1_variable;

public:
	DirectSynapsis(TNode1 const &n1, typename TNode1::variable v, TNode2 &n2, precission pg = 1, precission pt = 0) : m_n1(n1), m_n2(n2), m_n1_variable(v)
	{
		m_parameters[g] = pg;
		m_parameters[t] = pt;
	}

	void step(precission h)
	{
		const precission value = m_n1.get_variable(m_n1_variable);
		
		if(value > m_parameters[DirectSynapsis::t]){
			m_n2.add_synaptic_input(m_parameters[g] * value);
		}
	}
};
#endif /*DIRECTSYNAPSIS_H_*/
