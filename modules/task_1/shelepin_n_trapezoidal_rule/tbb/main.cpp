// Copyright 2022 Shelepin Nikita
#include <gtest/gtest.h>
#include <omp.h>

#include "./trapezoidal_rule.h"

TEST(TRAPEZOIDAL_RULE_OMP, TEST_DIM_3_FUNC_5) {
  std::vector<std::pair<double, double>> limits(2);
  limits = {{1, 3}, {5, 8}, {10, 12}};
  int n = 150;

  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        double z = vec[2];
        return (sin(x) - cos(y)) / z * z;
      };

  int runs = 20;

  double seq_time = 0, omp_time = 0, tbb_time = 0, std_time = 0;
  for (int i = 0; i < runs; i++) {
    double start = omp_get_wtime();
    getSeqTrapezoidal(n, limits, f);
    double end = omp_get_wtime();
    seq_time += end - start;

    start = omp_get_wtime();
    Trapezoidal_OMP(n, limits, f);
    end = omp_get_wtime();
    omp_time += end - start;

    start = omp_get_wtime();
    Trapezoidal_TBB(n, limits, f);
    end = omp_get_wtime();
    tbb_time += end - start;

    start = omp_get_wtime();
    Trapezoidal_STD(n, limits, f);
    end = omp_get_wtime();
    std_time += end - start;
  }

  seq_time /= runs;
  omp_time /= runs;
  tbb_time /= runs;
  std_time /= runs;

  std::cout << "\tsequential time: " << seq_time << "\n\n";

  std::cout << "\tOMP time: " << omp_time << "\n";
  std::cout << "\tefficiency: " << seq_time / omp_time << "\n\n";
  
  std::cout << "\tTBB time: " << tbb_time << "\n";
  std::cout << "\tefficiency: " << seq_time / tbb_time << "\n\n";
  
  std::cout << "\tSTD time: " << std_time << "\n";
  std::cout << "\tefficiency: " << seq_time / std_time << "\n";
}
