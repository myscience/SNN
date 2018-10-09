#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Core>
#include <vector>
#include <random>

using namespace std;

using Matrix = Eigen::MatrixXd;

#ifndef GENANN_RANDOM
/* We use the following for uniform random numbers between 0 and 1. */
#define GENANN_RANDOM() (((double) rand()) / RAND_MAX)
#endif

#ifndef MAXBUFSIZE
#define MAXBUFSIZE  ((int) 1e6)
#endif

#ifndef DELTA_T
#define DELTA_T ((double) 0.1)
#endif

/* The time of the simulation */
double t = 0.;

/* Gaussian random number generator */
const double mean = 0.0;
const double sigma = 0.1;
std::default_random_engine generator;
std::normal_distribution<double> gaussian(mean, sigma);

/* We use softmax function as a candidate transfer function */
inline double softmax(double u) {
  return log(1 + exp(u));
};

/* We use sigmoid function as a candidate transfer function */
inline double sigmoid(double u) {
  return 1. / (1. + exp(-u));
};

#endif
