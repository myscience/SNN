#ifndef __NEURON_H__
#define __NEURON_H__

/* DESCRIPTION:
   This class is the abstract Neuron of the simulation, it defines the general
   feature a neuron must have.
*/

#include "general.h"

class Neuron {
public:
  /* Default constructor, each inheriting classes will have their own. */
  Neuron () {};

  /* Default destructor, this has to be overridden by the inheriting classes. */
  virtual ~Neuron () {};

  virtual void updateSomaticPotential(const double dt) = 0;

  /* The forward propagation accepts just const double variables: basal and
     apical inputs as it is assumed that the UNIT class has provided a mechanism
     for buffering all incoming inputs, summing them all, and the correctly
     presenting to the Excitatory and Inhibitory Neurons as just double inputs */
  virtual void forwardPropagation(const double basal_in, const double apical_in) = 0;

protected:
  /* Dendritic vector potential can either be basal or apical (in excitatoty
     neurons) or just a single apical value (in inhibitory neurons). Instead
     somatic membran potential is always a single double variable. */
  double U = 0.;

  /* Resting membrane potential */
  double V_rest = 0.;

  /* Membrane capacitance, use for membrane potential update */
  double C = 1.;

  /* Transfer neuron function */
  double (*transfer) (double u);
};

#endif
