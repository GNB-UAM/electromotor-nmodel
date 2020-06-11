/*************************************************************

Copyright (c) 2006-2010 Fernando Herrero Carrón
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

$Id: DiffusionSynapsis.h 337 2008-01-29 15:46:19Z elferdo $
*************************************************************/

#ifndef DIFFUSIONSYNAPSIS_H_
#define DIFFUSIONSYNAPSIS_H_

#ifndef __AVR_ARCH__
#include <boost/concept_check.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>

#include "../concepts/IntegratorConcept.h"
#include "../concepts/NeuronConcept.h"
#endif  //__AVR_ARCH__

#include "../models/DiffusionSynapsisModel.h"
#include "../wrappers/IntegratedSystemWrapper.h"
#include "../wrappers/SerializableWrapper.h"
#include "../wrappers/SystemWrapper.h"

/**
 * @brief Implements a synapsis based on (Destexhe et al. 1994)
 */
template <typename TNode1, typename TNode2, typename TIntegrator,
          typename precission = double>
class DiffusionSynapsis
    : public SerializableWrapper<
          SystemWrapper<DiffusionSynapsisModel<precission> > > {
 private:
#ifndef __AVR_ARCH__
  BOOST_CLASS_REQUIRE(TNode1, , NeuronConcept);
  BOOST_CLASS_REQUIRE(TNode2, , NeuronConcept);
  BOOST_CLASS_REQUIRE(TIntegrator, , IntegratorConcept);
  BOOST_STATIC_ASSERT(boost::is_floating_point<precission>::value);
#endif  //__AVR_ARCH__

  precission m_release_time;

  TNode1 const &m_n1;
  TNode2 &m_n2;

  precission m_last_value_pre;

  const typename TNode1::variable m_n1_variable;
  const typename TNode2::variable m_n2_variable;

  typedef SerializableWrapper<
      SystemWrapper<DiffusionSynapsisModel<precission> > >
      System;

  const int m_steps;

 public:
  typedef typename System::precission_t precission_t;
  typedef typename System::variable variable;
  typedef typename System::parameter parameter;

  typedef typename System::ConstructorArgs ConstructorArgs;

  /**
   * @param palpha Rise time constant
   * @param pbeta  Decrease time constant
   * @param pthreshold Threshold at which the synapsis activates
   * @param pesyn Inversion potential (with respect to the postsynaptic
   * potential)
   * @param pgsyn Maximum conductance of the synapsis
   * @param pT Concentration of neurotransmitter at release time
   * @param pmax_release_time Width of the pulse at which neurotransmitter is
   * released
   */
  DiffusionSynapsis(TNode1 const &n1, typename TNode1::variable v, TNode2 &n2,
                    typename TNode2::variable v2, ConstructorArgs &args,
                    int steps)
      : m_release_time(0),
        m_n1(n1),
        m_n2(n2),
        m_n1_variable(v),
        m_n2_variable(v2),
        System(args),
        m_steps(steps) {
    System::m_variables[System::r] = 0;
    System::m_variables[System::i] = 0;
  }

  DiffusionSynapsis(TNode1 const &n1, typename TNode1::variable v, TNode2 &n2,
                    typename TNode2::variable v2, ConstructorArgs &&args,
                    int steps)
      : m_release_time(0),
        m_n1(n1),
        m_n2(n2),
        m_n1_variable(v),
        m_n2_variable(v2),
        System(args),
        m_steps(steps) {
    System::m_variables[System::r] = 0;
    System::m_variables[System::i] = 0;
  }

  DiffusionSynapsis(TNode1 const &n1, TNode2 &n2,
                    DiffusionSynapsis const &synapse)
      : m_release_time(synapse.m_release_time),
        m_last_value_pre(synapse.m_last_value_pre),
        m_n1(n1),
        m_n2(n2),
        m_n1_variable(synapse.m_n1_variable),
        m_n2_variable(synapse.m_n2_variable),
        m_steps(synapse.m_steps),
        System(synapse) {}

  void restart() {
    System::m_variables[System::r] = 0;
    System::m_variables[System::i] = 0;
  }

  precission step(precission h) {
    for (int i = 0; i < m_steps; ++i) {
      precission value = m_n1.get(m_n1_variable);

      if ((m_last_value_pre < System::m_parameters[System::threshold]) &&
          (value >= System::m_parameters[System::threshold])) {
        System::m_release = true;

        m_release_time = 0;
      }

      if (System::m_release) {
        m_release_time += h;

        if (m_release_time > System::m_parameters[System::max_release_time]) {
          System::m_release = false;
        }
      }

      TIntegrator::step(*this, h, System::m_variables, System::m_parameters);

      m_last_value_pre = value;
    }

    /* (Destexhe, 1994) */
    System::m_variables[System::i] =
        System::m_parameters[System::gsyn] * System::m_variables[System::r] *
        (m_n2.get(m_n2_variable) - System::m_parameters[System::esyn]);

    m_n2.add_synaptic_input(System::m_variables[System::i]);

    return System::m_variables[System::i];
  }
};

#endif /*DIFFUSIONSYNAPSIS_H_*/
