#include <random>
#include <cmath>

#include <iostream>

#include "neuralnet.hh"

double sigmoid(double x)
{
  return 1.0 / (1.0 + std::exp(-x));
}

double sigmoid_prime(double x)
{
  return sigmoid(x) * (1.0 - sigmoid(x));
}

Neuralnet::Neuralnet(std::vector<std::size_t> sizes):
  _nb_layers{sizes.size()}, _sizes{sizes}
{

  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> gaussian_rnd(0, 1);

  print_tab<std::size_t>(_sizes);
  // populate neurons of input layer
  _input.reserve(_sizes[0]);
  for (std::size_t i = 0; i < _sizes[0]; ++i)
    _input.push_back(0);

  //populate neurons of hidden layers
  _hidden.reserve(_nb_layers - 2);
  for (std::size_t i = 1; i < _nb_layers - 1; ++i)
  {
    _hidden[i - 1].reserve(_sizes[i]);
    _hidden.push_back(std::vector<double>());
    for (std::size_t j = 0; j < _sizes[i]; ++j)
      _hidden[i - 1].push_back(0);
  }

  // populate biases of hidden layers
  _hidden_bias.reserve(_nb_layers - 2);
  for (std::size_t i = 1; i < _nb_layers - 1; ++i)
  {
    _hidden_bias.push_back(std::vector<double>());
    _hidden_bias[i - 1].reserve(_sizes[i]);
    for (std::size_t j = 0; j < _sizes[i]; ++j)
      _hidden_bias[i - 1].push_back(gaussian_rnd(gen));
  }

  // populate weights of hidden layers
  _hidden_weight.reserve(_nb_layers - 2);
  for (std::size_t i = 1; i < _nb_layers - 1; ++i)
  {
    _hidden_weight.push_back(std::vector<std::vector<double>>());
    _hidden_weight[i - 1].reserve(_sizes[i]);
    for (std::size_t j = 0; j < _sizes[i]; ++j)
    {
      _hidden_weight[i - 1].push_back(std::vector<double>());
      _hidden_weight[i - 1][j].reserve(_sizes[i - 1]);
      for (std::size_t k = 0; k < _sizes[i - 1]; ++k)
        _hidden_weight[i - 1][j].push_back(gaussian_rnd(gen));
    }
  }

  //pooulate neurons of output layer
  _output.reserve(_sizes[_nb_layers - 1]);
  for (std::size_t i = 0; i < _sizes[_nb_layers - 1]; ++i)
    _output.push_back(0);
  print_tab<double>(_output);
  std::cout << _output.size() << std::endl;

  //pooulate biases of output layer
  _output_bias.reserve(_sizes[_nb_layers - 1]);
  for (std::size_t i = 0; i < _sizes[_nb_layers - 1]; ++i)
    _output_bias.push_back(gaussian_rnd(gen));

  //pooulate weights of output layer
  _output_weight.reserve(_sizes[_nb_layers - 1]);
  for (std::size_t i = 0; i < _sizes[_nb_layers - 1]; ++i)
  {
    _output_weight.push_back(std::vector<double>());
    _output_weight[i].reserve(_sizes[_nb_layers - 2]);
    for (std::size_t j = 0; j < _sizes[_nb_layers - 2]; ++j)
      _output_weight[i].push_back(gaussian_rnd(gen));
  }
}

Neuralnet::~Neuralnet()
{
  _input.clear();

  for (std::size_t i = 1; i < _nb_layers - 1; ++i)
  {
    _hidden[i - 1].clear();
    _hidden_bias[i - 1].clear();
  }
  _hidden.clear();
  _hidden_bias.clear();
  for (std::size_t i = 1; i < _nb_layers - 1; ++i)
  {
    for (std::size_t j = 0; j < _sizes[i]; ++j)
      _hidden_weight[i - 1][j].clear();
    _hidden_weight[i - 1].clear();
  }
  _hidden_weight.clear();

  _output.clear();
  _output_bias.clear();
  for (std::size_t i = 0; i < _sizes[_nb_layers - 1]; ++i)
  {
    _output_weight[i].clear();
  }
  _output_weight.clear();
  
  _sizes.clear();
}

void Neuralnet::feedForward(std::vector<double> pattern)
{
  for (std::size_t i = 0; i < pattern.size(); ++i)
  {
    _input[i] = pattern[i];
  }

  for (std::size_t i = 0; i < _hidden[0].size(); ++i)
  {
    _hidden[0][i] = 0;
    for (std::size_t j = 0; j < _input.size(); ++j)
    {
      _hidden[0][i] += _input[j] * _hidden_weight[0][i][j];
    }
    _hidden[0][i] = sigmoid(_hidden[0][i] + _hidden_bias[0][i]);
  }

  for (std::size_t nb_hidden = 2; nb_hidden < _nb_layers - 1; ++nb_hidden)
  {
    for (std::size_t i = 0; i < _hidden[nb_hidden].size(); ++i)
    {
      _hidden[nb_hidden][i] = 0;
      for (std::size_t j = 0; j < _hidden[nb_hidden - 1].size(); ++j)
      {
        _hidden[nb_hidden][i] += _hidden[nb_hidden - 1][j] * _hidden_weight[nb_hidden][i][j];
      }
      _hidden[nb_hidden][i] = sigmoid(_hidden[nb_hidden][i] + _hidden_bias[nb_hidden][i]);
    }
  }

  for (std::size_t i = 0; i < _output.size(); ++i)
  {
    _output[i] = 0;
    for (std::size_t j = 0; j < _hidden[_hidden.size() - 1].size(); ++j)
    {
      _output[i] += _hidden[_hidden.size() - 1][j] * _output_weight[i][j];
    }
    _output[i] = sigmoid(_output[i] + _output_bias[i]);
  }
  print_tab<double>(_output);
}

template<typename T> void print_tab(std::vector<T> v)
{
  std::cout << "[ ";
  for (auto it : v)
  {
    std::cout << it << ", ";
  }
  std::cout << "]" << std::endl;
}
