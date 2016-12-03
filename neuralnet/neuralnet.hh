#ifndef NEURALNET_HH_VVTZOCE9
#define NEURALNET_HH_VVTZOCE9

#include <vector>

double sigmoid(double x);
double sigmoid_prime(double x);


class Neuralnet
{
private:
  std::size_t _nb_layers;
  std::vector<std::size_t> _sizes;

  std::vector<double> _input;

  std::vector<std::vector<double>> _hidden;
  std::vector<std::vector<double>> _hidden_bias;
  std::vector<std::vector<std::vector<double>>> _hidden_weight;

  std::vector<double> _output;
  std::vector<double> _output_bias;

  std::vector<std::vector<double>> _output_weight;

public:
  Neuralnet(std::vector<std::size_t> sizes);
  ~Neuralnet();

  void feedForward(std::vector<double> pattern);
};

template<typename T> void print_tab(std::vector<T> v);

#endif /* end of include guard: NEURALNET_HH_VVTZOCE9 */
