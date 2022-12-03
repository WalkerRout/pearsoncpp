
#include <iostream>
#include <vector>
#include <numeric>
#include <sstream>
#include <fstream>
#include <string_view>
#include <cmath>
#include <assert.h>

// im lazy; loads lines of a file into vectors of doubles
auto load_data(std::string file_name) {
  std::ifstream f(file_name);
  // operator! is overloaded for ifstream, so this actually checks f.bad() and f.fail()
  // this is a pretty terrible use of the overload, but its a script so i am not going
  // to search for a worse looking solution
  if(!f)
    throw std::invalid_argument("Error - file does not exist!");
  
  std::vector<std::vector<double>> vectors;
  std::string line;
  
  while (std::getline(f, line)) {
    std::istringstream ss(line);
    std::vector<double> vec;
    float v;
    // populate new vector
    while (ss >> v) {
      vec.push_back(v);
    }
    vectors.push_back(vec);
  }
  
  f.close();
  
  return vectors;
}

template <typename T>
constexpr inline auto mean(const T &a) noexcept -> double {
  auto sum(std::accumulate(a.begin(), a.end(), 0.0));
  return sum / (double) a.size();
}

template <typename T>
auto pearson_coefficient(const T &x, const T &y) noexcept -> double {
  assert(x.size() == y.size() && "Must be equal length of data points!");

  auto x_mean(mean(x));
  auto y_mean(mean(y));
  
  auto top(0.0);
  auto bot(0.0);

  for(auto i = 0; i < x.size(); ++i) {
    top += (x[i] - x_mean) * (y[i] - y_mean);
  }

  auto part_one(0.0);
  auto part_two(0.0);

  for(auto i = 0; i < x.size(); ++i) {
    part_one += pow(x[i] - x_mean, 2);
    part_two += pow(y[i] - y_mean, 2);
  }

  bot = sqrt(part_one * part_two);

  return top / bot;
} 

auto main(void) -> int {
  std::vector<std::vector<double>> vs;
  try {
    vs = load_data("data.txt");
  } catch(std::invalid_argument e) {
    std::cout << "Aborting - " << e.what() << "\n";
    exit(EXIT_FAILURE);
  }
  
  auto xs(std::move(vs[0]));
  auto ys(std::move(vs[1]));
  // never touch vs againx
  
  std::cout << "Pearson coefficient: " << pearson_coefficient(xs, ys) << "\n";
  
  return 0;
}
