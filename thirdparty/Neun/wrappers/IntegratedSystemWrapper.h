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

$Id: IntegratedSystemWrapper.h 196 2007-06-08 09:33:27Z elferdo $
*************************************************************/

#ifndef INTEGRATEDSYSTEMWRAPPER_H_
#define INTEGRATEDSYSTEMWRAPPER_H_

#ifndef __AVR_ARCH__
#include <boost/concept_check.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

#include "../concepts/IntegratableSystemConcept.h"
#include "../concepts/IntegratorConcept.h"
#endif  //__AVR_ARCH__

#include "DynamicalSystemWrapper.h"

/**
 * \brief Adds common code to a model class.
 * \todo Check concepts
 * \param System The model class to extend.
 * \param Integrator The integrator class to use
 */

template <typename System, typename Integrator>
class IntegratedSystemWrapper : public DynamicalSystemWrapper<System> {
#ifndef __AVR_ARCH__
  BOOST_CLASS_REQUIRE(DynamicalSystemWrapper<System>, ,
                      IntegratableSystemConcept);
  BOOST_CLASS_REQUIRE(Integrator, , IntegratorConcept);
#endif  //__AVR_ARCH__

 public:
  typedef typename System::precission_t precission_t;
  typedef typename System::variable variable;
  typedef typename System::parameter parameter;
  typedef typename System::ConstructorArgs ConstructorArgs;

  IntegratedSystemWrapper(ConstructorArgs &&args)
      : DynamicalSystemWrapper<System>(args) {}

  IntegratedSystemWrapper(ConstructorArgs &args)
      : DynamicalSystemWrapper<System>(args) {}

  void restart() { System::restart(); }

  void step(precission_t h) {
    /* Allow system specific step actions */

    System::pre_step(h);

    Integrator::step(*this, h, System::m_variables, System::m_parameters);

    System::post_step(h);
  }

  void add_synaptic_input(precission_t i) { System::m_synaptic_input += i; }

  precission_t get_synaptic_input() const { return System::m_synaptic_input; }
};

#endif /*INTEGRATEDSYSTEMWRAPPER_H_*/
