/*************************************************************

Copyright (c) 2020, Ángel Lareo Fernández
                                        Alicia Garrido Peña
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

*************************************************************/

#ifndef VAVOULISMODEL_H_
#define VAVOULISMODEL_H_

#include <cmath>
#include "../include/NeuronBase.h"

template <typename Precission>
class VavoulisModel : public NeuronBase<Precission> {
 public:
  typedef Precission precission_t;

  // clang-format off
  enum variable { v, va, p, q, h, n, n_variables };
  enum parameter { t, tau_p, tau_q, g_eca, g_ecs, n_parameters };
  enum type {so, n1m, n2v, n3t, n_types};
  // clang-format on

 protected:
  Precission il(Precission v) const { v + 67; }

  Precission ix(type t, Precission v, Precission p, Precission q) const {
    switch (t) {
      case so:
        return 0;
        break;
      case n1m:
        return 200 * p * p * p * (v + 30);
        break;
      case n2v:
        return 2 * p * p * p * q * (v - 55);
        break;
      case n3t:
        return 3.27 * p * p * p * q * (v - 80);
        break;
      default:
        return 0;
    }
  }

  // iecs(v,va,g_ecs) - ieca(va,v,g_eca)
  Precission iec(Precission v1, Precission v2, Precission g_ec) const {
    return g_ec * (v1 - v2);
  }

  Precission inat(Precission va, Precission h) const {
    Precission minf = 1 / (1 + exp((-34.6 - va) / 9.6));
    return 350 * minf * minf * minf * h * (va - 55);
  }

  Precission ik(Precission va, Precission n) const {
    return 90 * n * n * n * n * (va + 90);
  }

  Precission incr_p(type t, Precission p, Precission v,
                    Precission tau_p) const {
    // switch (t) {
    Precission pinf = 1 / (1 + exp((-61.6 - v) / 5.6));
    return (pinf - p) / tau_p;
  }

  Precission incr_q(type t, Precission q, Precission v,
                    Precission tau_q) const {
    // switch (t) {
    Precission qinf = 1 / (1 + exp((-73.2 - v) / -5.1));
    return (qinf - q) / tau_q;
  }

  Precission incr_h(Precission h, Precission va) const {
    Precission tau_h =
        1.1 + 7.2 * exp(-((-61.3 - va) / 22.7) * ((-61.3 - va) / 22.7));
    Precission hinf = 1 / (1 + exp((-55.2 - v) / -7.1));
    return (hinf - h) / tau_h;
  }

  Precission incr_n(Precission n, Precission va) const {
    Precission tau_n =
        1.1 + 4.6 * exp(-((-61 - va) / 54.3) * ((-61 - va) / 54.3));
    Precission ninf = 1 / (1 + exp((-30 - v) / -17.4));
    return (ninf - n) / tau_n;
  }

  Precission m_variables[n_variables];
  Precission m_parameters[n_parameters];

 public:
  struct ConstructorArgs {
    Precission params[n_parameters];
  };

  VavoulisModel(ConstructorArgs const &args) {
    std::copy(args.params, args.params + n_parameters, m_parameters);
  }

  void eval(const Precission *const vars, Precission *const params,
            Precission *const incs) const {
    incs[v] = -SYNAPTIC_INPUT - il(vars[v]) -
              ix((type)params[t], vars[v], vars[p], vars[q]) -
              iec(vars[v], vars[va], vars[g_ecs]);

    incs[va] = -il(vars[v]) - inat(vars[va], vars[h]) - ik(vars[va], vars[n]) -
               iec(vars[va], vars[v], vars[g_eca]);

    incs[p] = incr_p((type)params[t], vars[p], vars[v], params[tau_p]);
    incs[q] = incr_q((type)params[t], vars[q], vars[v], params[tau_q]);

    incs[h] = incr_h(vars[h], vars[va]);
    incs[n] = incr_n(vars[n], vars[va]);
  }
};

#endif /*VAVOULISMODEL_H_*/
