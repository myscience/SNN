#include "SNN.h"

int main(int argc, char** argv) {

  Excitatory_Neuron neuron;

  neuron.updateSomaticPotential(DELTA_T);

  return 0;
}
