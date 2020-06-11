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

$Id: DynamicalSystemArchetype.h,v 1.1.2.2 2006/11/28 17:10:04 elferdo Exp $
*************************************************************/

#ifndef DYNAMICALSYSTEMARCHETYPE_H_
#define DYNAMICALSYSTEMARCHETYPE_H_

#include <boost/concept_archetype.hpp>

template <typename Precission, typename Base = boost::null_archetype<> >
struct DynamicalSystemArchetype : public Base
{
	//@todo Check Precission concept
	enum variable {n_variables = 1};
	enum parameter {n_parameters = 1};
	
	typedef Precission precission_t;
	
	precission_t get(variable var) const
	{
		precission_t v(0);
		
		return v;
	}
	
	void set(variable var, precission_t value)
	{
	}
	
	precission_t get(parameter par) const
	{
		precission_t p(0);
		
		return p;
	}
	
	void set(parameter p, precission_t value)
	{
	}
	
	void eval(const precission_t vars[n_variables], precission_t incs[n_parameters]) const
	{
	}
		
	void step(precission_t value)
	{
	}
};

#endif /*DYNAMICALSYSTEMARCHETYPE_H_*/
