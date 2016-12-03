#include <iostream>

#include "neuralnet.hh"

int main(void)
{
  std::vector<std::size_t> sizes = std::vector<std::size_t>({2, 2, 1});
  Neuralnet *n = new Neuralnet(sizes);
  std::vector<double> test = std::vector<double>({-1., 1.});
  n->feedForward(test);
  return 0;
}
