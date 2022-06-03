// Copyright 2022 Tyrina Anastasia
#ifndef MODULES_TASK_1_TYRINA_A_DIJKSTRA_DIJKSTRA_H_
#define MODULES_TASK_1_TYRINA_A_DIJKSTRA_DIJKSTRA_H_

#include <vector>

using VectorInt = std::vector<int>;
using VectorBool = std::vector<bool>;
using Graph = std::vector<std::vector<int>>;

Graph getRandomGraph(int V);
Graph sequentialDijkstra(const Graph& graph, int V);

#endif  // MODULES_TASK_1_TYRINA_A_DIJKSTRA_DIJKSTRA_H_
