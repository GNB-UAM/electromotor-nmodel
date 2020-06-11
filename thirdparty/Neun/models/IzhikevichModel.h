/*************************************************************

Copyright (c) 2016, Ángel Lareo Fernández
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

$Id: HindmarshRoseModel.h 203 2007-06-26 14:46:34Z elferdo $
*************************************************************/

#ifndef IZHIKEVICHMODEL_H_
#define IZHIKEVICHMODEL_H_

#include <cmath>
#include "../include/NeuronBase.h"

/**
 * (Izhikevich, 2006)
 */

template <typename Precission>
class IzhikevichModel : public NeuronBase<Precission> {
 public:
  typedef Precission precission_t;

  enum variable { v, u, n_variables };
  enum parameter { a, b, c, d, threshold, n_parameters };

  struct ConstructorArgs {
    Precission params[n_parameters];
  };

 protected:
  Precission m_variables[n_variables];
  Precission m_parameters[n_parameters];

 public:
  IzhikevichModel(ConstructorArgs const &args) {
    std::copy(args.params, args.params + n_parameters, m_parameters);
    m_variables[v] = -65;
    m_variables[u] = m_parameters[b] * m_variables[v];
  }

  IzhikevichModel(ConstructorArgs const &&args) {
    std::copy(args.params, args.params + n_parameters, m_parameters);
    m_variables[v] = -65;
    m_variables[u] = m_parameters[b] * m_variables[v];
  }

  void restart() {
    m_variables[v] = -65;
    m_variables[u] = m_parameters[b] * m_variables[v];
  }

  void pre_step(Precission h) {}

  void eval(const Precission *const vars, Precission *const params,
            Precission *const incs) const {
    incs[v] =
        0.04 * vars[v] * vars[v] + 5 * vars[v] + 140 - vars[u] + SYNAPTIC_INPUT;
    // incs[v] = v + 0.5*(0.04 * vars[v] * vars[v] + 5 * vars[v] + 140 - vars[u]
    // + SYNAPTIC_INPUT);  incs[v] = v + 0.5*(0.04 * vars[v] * vars[v] + 5 *
    // vars[v] + 140 - vars[u] + SYNAPTIC_INPUT);
    incs[u] = params[a] * (params[b] * vars[v] - vars[u]);
  }

  void post_step(Precission h) {
    if (m_variables[v] > m_parameters[threshold]) {
      m_variables[v] = m_parameters[c];
      m_variables[u] += m_parameters[d];
    }
  }
};

#endif /*IZHIKEVICHMODEL_H_*/
