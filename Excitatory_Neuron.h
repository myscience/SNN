#ifndef __EXCITATORY_NEURON_H__
#define __EXCITATORY_NEURON_H__

#include "Neuron.h"

class Excitatory_Neuron : public Neuron {
public:
  Excitatory_Neuron () : Neuron() {

  };

  void updateSomaticPotential(const double dt) override {
    /* Here we implement RK-4 integration of the equation:
       C d/dt V_somatic = -g * (V_somatic - V_rest) +
                           g_B * (V_dendritic_Basal - V_somatic) +
                           g_A * (V_dendritic_Apical - V_somatic) +
                           sigma * xi                             */

    double k1 = somaticUpdate(U);
    double k2 = somaticUpdate(U + 0.5 * k1 * dt);
    double k3 = somaticUpdate(U + 0.5 * k2 * dt);
    double k4 = somaticUpdate(U + k3 * dt);

    U += dt * 1. / 6. * (k1 + 2. *  k2 + 2. * k3 + k4);
  };

  double somaticUpdate(const double U) {
    return -g * (U - V_rest) + g_B * (V_b - U) + g_A * (V_a - U) + gaussian(generator);
  };

  void forwardPropagation(const double b_input,const double a_input) override {
    /* First we need to evaluate the input signal from both apical and basal
       dendrites. We assume that the input comes from an output already
       well formed. */
    V_a = a_input;
    V_b = b_input;

    /* Then we perform the somatic potential update */
    updateSomaticPotential(DELTA_T);

    /* Then we construct our output using appropriate weights */
    double U_trans = transfer(U);

    out_PP_up = W_PP_up * U_trans;
    out_PP_down = W_PP_down * U_trans;
    out_PI = W_PI * U_trans;
    out_PI_down = W_PI_down * U_trans;
  };

  virtual ~Excitatory_Neuron() {};

public:
  /* Soma self-conductance. Needed for esponential-decay in membrane potential
     update */
  double g = 1.;

  /* Apical dendritic to soma conductance */
  double g_A = 1.;

  /* Basal dendritic to soma conductance */
  double g_B = 1.;

  /* Dendritic membrane potential: basal and apical for Excitatory Neurons */
  double V_a = 0.; // Apical
  double V_b = 0.; // Basal

  /* Each Neuron keep track of is outgoing weight sinaptic connections and their
     relative updates. */
  double W_PP_up = 0.; // Piramidal to up-Piramidal
  double W_PP_down = 0.; // Piramidal to down-Piramidal
  double W_PI = 0.; // Piramidal to Interneuron
  double W_PI_down = 0.; // Piramidal to down-Interneuron

  /* We separately store the output from soma to Interneuron, from soma to up
   Piramidal, from soma to down Piramidal and from soma to down Interneuron */
  double out_PP_up = 0.;
  double out_PP_down = 0.;
  double out_PI = 0.;
  double out_PI_down = 0.;
};

#endif
