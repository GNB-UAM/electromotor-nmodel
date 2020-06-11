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

$Id: ModelArchetype.h 184 2007-06-04 11:26:12Z elferdo $
*************************************************************/

#ifndef MODELARCHETYPE_H_
#define MODELARCHETYPE_H_

class ModelArchetype
{
public:
	//@todo Check Precission concept
	enum variable {x, y, n_variables = 1};
	enum parameter {alpha, beta, n_parameters = 1};
	
	typedef double precission_t;
	
		
	void eval(precission_t * const vars, precission_t * const params, precission_t *incs) const
	{
	}
};

#endif /*MODELARCHETYPE_H_*/
