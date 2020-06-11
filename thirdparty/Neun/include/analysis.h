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

$Id: analysis.h 184 2007-06-04 11:26:12Z elferdo $
*************************************************************/

#ifndef ANALYSIS_H_
#define ANALYSIS_H_

template <typename TNeuron>
void advance_until_crossing_threshold(TNeuron &n, typename TNeuron::variable v, typename TNeuron::precission_t h, typename TNeuron::precission_t threshold)
{
	typename TNeuron::precission_t lastx = 0;
	typename TNeuron::precission_t x = 0;
	
	do{
		n.step(h);

		lastx = x;
		
		x = n.get_variable(v);
    }while(!(x >= threshold) || !(lastx < threshold));
}

template <typename TNeuron>
void advance_until_crossing_threshold_adding_input(TNeuron &n, typename TNeuron::variable v, typename TNeuron::precission_t h, typename TNeuron::precission_t input, typename TNeuron::precission_t threshold)
{
	typename TNeuron::precission_t lastx = 0;
	typename TNeuron::precission_t x = 0;
	
	do{
		n.add_synaptic_input(input);
		
		n.step(h);

		lastx = x;
		
		x = n.get_variable(v);
    }while(!(x >= threshold) || !(lastx < threshold));
}

template <typename TNeuron>
unsigned int get_period(TNeuron &n, typename TNeuron::variable v, typename TNeuron::precission_t h, typename TNeuron::precission_t threshold)
{
	typename TNeuron::precission_t lastx;
	typename TNeuron::precission_t x;
	
	unsigned int period = 0;
	 
	do{
		n.step(h);
		
		period++;
		
		lastx = x;
		x = n.get_variable(v);
    }while(!(x >= threshold) || !(lastx < threshold));
    
    return period;
}

template <typename TNeuron>
unsigned int get_period_adding_input(TNeuron &n, typename TNeuron::variable v, typename TNeuron::precission_t h, typename TNeuron::precission_t input, typename TNeuron::precission_t threshold)
{
	typename TNeuron::precission_t lastx;
	typename TNeuron::precission_t x;
	
	unsigned int period = 0;
	 
	do{
		n.add_synaptic_input(input);

		n.step(h);
		
		period++;
		
		lastx = x;
		x = n.get_variable(v);
    }while(!(x >= threshold) || !(lastx < threshold));
    
    return period;
}


#endif /*ANALYSIS_H_*/
