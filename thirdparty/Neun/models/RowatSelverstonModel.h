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

$Id: RowatSelverstonModel.h 184 2007-06-04 11:26:12Z elferdo $
*************************************************************/

#ifndef ROWATSELVERSTONMODEL_H_
#define ROWATSELVERSTONMODEL_H_

#include <algorithm>
#include <cmath>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

/** (Rowat and Selverston, 1997)
 * tm = 1
 * sf = 2
 * ts = 2
 * ss = 1
 * af = 1
 * es = 1
 */
template <typename Precission>
class RowatSelverstonModel {
	BOOST_STATIC_ASSERT(boost::is_floating_point<Precission>::value);
	
public:
	typedef Precission precission_t;
	
	enum variable {v = 0, q = 1, n_variables};
	enum parameter {tm, sf, ts, ss, af, es, n_parameters};

	struct ConstructorArgs
	{
	    Precission params[n_parameters];
	};

protected:
	Precission m_variables[n_variables];
	Precission m_parameters[n_parameters];
	Precission m_synaptic_input;

public:
	RowatSelverstonModel(ConstructorArgs const &args) : m_synaptic_input(0)
	{
		std::copy(args.params, args.params + n_parameters, m_parameters);
	}

	void eval(const Precission * const vars, Precission * const incs) const
	{
		incs[v] = -(vars[v] - m_parameters[af] * tanh((m_parameters[sf] / m_parameters[af]) * vars[v]) + vars[q] - m_synaptic_input) / m_parameters[tm];
		incs[q] = (-vars[q] + m_parameters[ss] * (vars[v] - m_parameters[es])) / m_parameters[ts];
	}
};

#endif /*ROWATSELVERSTONMODEL_H_*/
