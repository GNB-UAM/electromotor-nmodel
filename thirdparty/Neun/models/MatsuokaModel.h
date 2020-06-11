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

$Id: MatsuokaModel.h 443 2010-03-04 01:17:25Z elferdo $
*************************************************************/

#ifndef MATSUOKAMODEL_H_
#define MATSUOKAMODEL_H_

#include <cmath>
#include "../include/NeuronBase.h"

/** (Matsuoka, )
 *
 * beta = 1
 * t1 = 1
 * t2 = 1
 * c = 1
 */

template <typename Precission>
class MatsuokaModel : public NeuronBase<Precission>
{
public:
	typedef Precission precission_t;

	enum variable {x, v, n_variables};
	enum parameter {beta, t1, t2, c, n_parameters};

	void eval(const Precission * const vars, Precission * const params, Precission * const incs) const
	{
		incs[x] = (-vars[x] - params[beta] * vars[v] + SYNAPTIC_INPUT + params[c]) / params[t1];
		incs[v] = (-vars[v] + ((vars[x] > 0)? vars[x] : 0)) / params[t2];
	}
};

#endif /*MATSUOKAMODEL_H_*/
