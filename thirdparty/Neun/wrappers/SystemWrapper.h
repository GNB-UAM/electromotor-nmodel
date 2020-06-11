/*************************************************************

Copyright (c) 2006, Fernando Herrero Carrón
			  2017, Angel Lareo Fernández
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

$Id: SystemWrapper.h 184 2007-06-04 11:26:12Z elferdo $
*************************************************************/

#ifndef SYSTEMWRAPPER_H_
#define SYSTEMWRAPPER_H_

#ifndef __AVR_ARCH__
  #include "../concepts/ModelConcept.h"
  #include <boost/concept_check.hpp>
  #include <algorithm>
#else
  #include "../include/algorithm.h"
#endif //__AVR_ARCH__

/**
 * \brief Adds common code to a model class.
 * \todo Check concepts
 * \param Model The model class to extend.
 * \param Integrator The integrator class to use
 */

template <typename Model>
class SystemWrapper : public Model
{
#ifndef __AVR_ARCH__
	BOOST_CLASS_REQUIRE(Model, , ModelConcept);
#endif //__AVR_ARCH__

protected:

	typename Model::precission_t m_variables[Model::n_variables];
	typename Model::precission_t m_parameters[Model::n_parameters];

public:

	typedef typename Model::precission_t precission_t;
	typedef typename Model::variable variable;
	typedef typename Model::parameter parameter;
//	typedef typename Model::ConstructorArgs ConstructorArgs;

	class ConstructorArgs
	{
	public:
		precission_t params[Model::n_parameters];

	    precission_t &operator[](parameter p)
	    {
	    	return params[p];
	    }
	};


	SystemWrapper(ConstructorArgs const &args)
	{
		std::copy(args.params, args.params + Model::n_parameters, m_parameters);
	}

	SystemWrapper(ConstructorArgs const &&args)
	{
		std::copy(args.params, args.params + Model::n_parameters, m_parameters);
	}

	SystemWrapper(SystemWrapper<Model> const &system)
	{
	  std::copy(system.m_parameters, system.m_parameters + Model::n_parameters, m_parameters);
	  std::copy(system.m_variables, system.m_variables + Model::n_variables, m_variables);
	}

	precission_t get(variable var) const
	{
		return m_variables[var];
	}

	void set(variable var, precission_t value)
	{
		m_variables[var] = value;
	}

	precission_t get(parameter param) const
	{
		return m_parameters[param];
	}

	void set(parameter param, precission_t value)
	{
		m_parameters[param] = value;
	}
};

#endif /*SYSTEMWRAPPER_H_*/
