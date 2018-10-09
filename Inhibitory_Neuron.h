#ifndef __INHIBITORY_NEURON_H__
#define __INHIBITORY_NEURON_H__

#include "Neuron.h"

class Inhibitory_Neuron : public Neuron {
public:
  Inhibitory_Neuron() : Neuron() {

  };

  void updateSomaticPotential(const double dt) override {
    double k1 = somaticUpdate(U);
    double k2 = somaticUpdate(U + 0.5 * k1 * dt);
    double k3 = somaticUpdate(U + 0.5 * k2 * dt);
    double k4 = somaticUpdate(U + k3 * dt);

    U += dt * 1. / 6. * (k1 + 2. *  k2 + 2. * k3 + k4);
  };

  double somaticUpdate(const double U) {
    double g_exc = g_som * (U_up - E_inh) / (E_exc - E_inh);
    double g_inh = -g_som * (U_up - E_exc) / (E_exc - E_inh);
    double I = g_exc * (E_exc - U) + g_inh * (E_inh - U);

    return -g * U + g_D * (V - U) + I + gaussian(generator);
  };

  void forwardPropagation(const double basal_in, const double apical_in) override {
    /* An Interneuron receives two types of inputs: a basal one, which corresponds
       to the inputs coming from neighbours Piramidal neurons, and an "apical"
       one, which corresponds to the fact that Interneuron keep track of upper
       layers' Piramidal neurons somatic potentials */

    U_up = apical_in;
    V = basal_in;

    /* Next we update the somatic potential */
    updateSomaticPotential(DELTA_T);

    /* Next we built our output: just one for Inhibitory neurons, the inibition
       to the right-neighbouring Piramidal neuron. */
    out_IP = W_IP * transfer(U); 
  };

public:
  /* Soma self-conductance. Needed for esponential-decay in membrane potential
     update */
  double g = 1.;

  /* Dendritic to soma conductance */
  double g_D = 1.;

  /* Conductance of soma, needed to scale overall nudging strenght */
  double g_som = 1.;

  /* Dendritic membrane potential */
  double V = 0.;

  /* Excitatory and Inhibitory membrane reversal potential */
  double E_exc = 0.;
  double E_inh = 0.;

  /* Interneurons need to keep record of somatic upper area Piramidal poential */
  double U_up = 0.;

  /* Weight for soma to Piramidal connection */
  double W_IP = 0.;

  /* Output from soma to Piramidal */
  double out_IP = 0.;
};

#endif
