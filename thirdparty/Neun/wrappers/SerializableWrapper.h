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

$Id$
*************************************************************/

#ifndef SERIALIZABLEWRAPPER_H_
#define SERIALIZABLEWRAPPER_H_

#include <iostream>

#include <boost/concept_check.hpp>
#include "../concepts/SystemConcept.h"

template <typename System>
class SerializableWrapper : public System{
	BOOST_CLASS_REQUIRE(System, , SystemConcept);

public:

	typedef typename System::precission_t precission_t;
	typedef typename System::variable variable;
	typedef typename System::parameter parameter;
	typedef typename System::ConstructorArgs ConstructorArgs;

	SerializableWrapper(ConstructorArgs const &args) : System(args)
	{
	}

	SerializableWrapper(ConstructorArgs &&args) : System(args)
	{
	}

	void save(std::ostream &os) const
	{
		for(int i = 0; i < System::n_variables; i++){
			os << System::m_variables[i] << " ";
		}
	}

	void load(std::istream &is)
	{
		for(int i = 0; i < System::n_variables; i++){
			is >> System::m_variables[i];
		}
	}
};

#endif /*SERIALIZABLEWRAPPER_H_*/
