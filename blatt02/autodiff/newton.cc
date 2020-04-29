#include <iostream>
#include <functional>

#include "ad.hh"

std::pair<double, int> newton(std::function<Ad::SimpleAd(Ad::SimpleAd)> f, double start)
{
  const double tol = 1e-13;
  const int max_iter = 20;
  int iter = 0;
  double x(start);
  Ad::SimpleAd fx = f(Ad::SimpleAd(x));
  for(; iter < max_iter;++iter){
    // TODO Implement me!
  }
  if(iter >= max_iter)
    throw std::runtime_error("Newton does not converge");
  return { x, iter};
}


int main(){
  auto f = [](Ad::SimpleAd x) { return sin(2*x) + x + 1; };

  // compute f and its derivation at point x0=0
  Ad::SimpleAd x0(0.0);
  Ad::SimpleAd fx0 = f(x0);
  if(fabs(fx0.value()-1) < 1e-8 &&
     fabs(fx0.derivative() - 3) < 1e-8){
    std::cout << "SimpleAd test: success" << std::endl;
  }else{
    std::cout << "SimpleAd test: failed" << std::endl;
    return 1;
  }

  // compute a root of f using newtons method

  /*

  std::cout.precision(17);
  double start = 0.0;
  auto [root, iterations] = newton(f, start);
  std::cout << "Root = " << root << "   Iterations = " << iterations << std::endl;

  if (fabs(root- (-0.3522884564608728)) < 1e-13) {
    std::cout << "success!" << std::endl;
  } else {
    std::cout << "failure!" << std::endl;
  }

  */
  return 0;
}
