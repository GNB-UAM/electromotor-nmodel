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

$Id: NeuronBase.h 196 2007-06-08 09:33:27Z elferdo $
*************************************************************/

#ifndef NEURONBASE_H_
#define NEURONBASE_H_

#ifndef __AVR_ARCH__
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#endif  //__AVR_ARCH__
#define SYNAPTIC_INPUT NeuronBase<Precission>::m_synaptic_input

template <typename Precission>
class NeuronBase {
#ifndef __AVR_ARCH__
  BOOST_STATIC_ASSERT(boost::is_floating_point<Precission>::value);
#endif  //__AVR_ARCH__

 protected:
  Precission m_synaptic_input;

 public:
  NeuronBase() : m_synaptic_input(0) {}

  void add_synaptic_input(Precission i) { m_synaptic_input += i; }

  Precission get_synaptic_input() const { return m_synaptic_input; }

  void reset_synaptic_input() { m_synaptic_input = 0; }

  void restart() {}

  void pre_step(Precission h) {}

  void post_step(Precission h) { m_synaptic_input = 0; }
};

#endif /*NEURONBASE_H_*/
