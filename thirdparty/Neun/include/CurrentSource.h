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

$Id: CurrentSource.h 184 2007-06-04 11:26:12Z elferdo $
*************************************************************/

#ifndef CURRENTSOURCE_H_
#define CURRENTSOURCE_H_

/** @brief Implements a current source to use
 * as a stimulus
 * 
 * Although current can be easily injected to a neuron using
 * add_synaptic_current, this class allows for a uniform implementation
 * using synapses.
 */
class CurrentSource
{
public:

	enum variable {i = 0, n_variables};
	
	typedef double variables_list_type[n_variables];
	
private:
	
	double m_variables[n_variables];
	
public:

	CurrentSource(double pi)
	{
		m_variables[i] = pi;
	}	

	double get_variable(variable var) const
	{
		return m_variables[var];
	}

	void set_variable(variable var, double value)
	{
		m_variables[var] = value;
	}
};


#endif /*CURRENTSOURCE_H_*/
