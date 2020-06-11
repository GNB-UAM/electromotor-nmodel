/*************************************************************

Copyright (c) 2007, Fernando Herrero Carrón
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

$Id: ModelConcept.h 443 2010-03-04 01:17:25Z elferdo $
*************************************************************/

#ifndef MODELCONCEPT_H_
#define MODELCONCEPT_H_

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

template <typename Model>
struct ModelConcept{

	int value;
	const Model model;

	void constraints() {
		typename Model::precission_t *vars;
		typename Model::precission_t *params;
		typename Model::precission_t *incs;

		typename Model::variable var;
		typename Model::parameter par;

		BOOST_STATIC_ASSERT(boost::is_arithmetic<typename Model::precission_t>::value);

		value = Model::n_variables;
		value = Model::n_parameters;

		model.eval(vars, params, incs);
	}
};


#endif /*MODELCONCEPT_H_*/
