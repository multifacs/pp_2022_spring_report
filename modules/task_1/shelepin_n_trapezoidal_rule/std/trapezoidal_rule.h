// Copyright 2022 Shelepin Nikita
#ifndef MODULES_TASK_4_SHELEPIN_N_TRAPEZOIDAL_RULE_TRAPEZOIDAL_RULE_H_
#define MODULES_TASK_4_SHELEPIN_N_TRAPEZOIDAL_RULE_TRAPEZOIDAL_RULE_H_

#include <cmath>
#include <functional>
#include <thread>  // NOLINT
#include <utility>
#include <vector>

double getParallelTrapezoidal(
    const int n, const std::vector<std::pair<double, double>>& limits,
    const std::function<double(std::vector<double>)>& f);

#endif  // MODULES_TASK_4_SHELEPIN_N_TRAPEZOIDAL_RULE_TRAPEZOIDAL_RULE_H_
