// Copyright 2022 Tyrina Anastasia
#include <gtest/gtest.h>
#include <omp.h>

#include "./dijkstra.h"

TEST(DIJKSTRA_TBB, TEST_1) {
  int V = 9;
  Graph graph = {{0, 4, 0, 0, 0, 0, 0, 8, 0},  {4, 0, 8, 0, 0, 0, 0, 11, 0},
                 {0, 8, 0, 7, 0, 4, 0, 0, 2},  {0, 0, 7, 0, 9, 14, 0, 0, 0},
                 {0, 0, 0, 9, 0, 10, 0, 0, 0}, {0, 0, 4, 14, 10, 0, 2, 0, 0},
                 {0, 0, 0, 0, 0, 2, 0, 1, 6},  {8, 11, 0, 0, 0, 0, 1, 0, 7},
                 {0, 0, 2, 0, 0, 0, 6, 7, 0}};

  Graph result_sequential = sequentialDijkstra(graph, V);
  Graph result_parallel = parallelDijkstra(graph, V);

  for (int i = 0; i < V; i++) {
    ASSERT_EQ(result_sequential[i], result_parallel[i]);
  }
}

TEST(DIJKSTRA_TBB, TEST_2) {
  int V = 4;
  Graph graph = getRandomGraph(V);
  Graph result_sequential = sequentialDijkstra(graph, V);
  Graph result_parallel = parallelDijkstra(graph, V);

  for (int i = 0; i < V; i++) {
    ASSERT_EQ(result_sequential[i], result_parallel[i]);
  }
}

TEST(DIJKSTRA_TBB, TEST_3) {
  int V = 6;
  Graph graph = getRandomGraph(V);
  Graph result_sequential = sequentialDijkstra(graph, V);
  Graph result_parallel = parallelDijkstra(graph, V);

  for (int i = 0; i < V; i++) {
    ASSERT_EQ(result_sequential[i], result_parallel[i]);
  }
}

TEST(DIJKSTRA_TBB, TEST_4) {
  int V = 8;
  Graph graph = getRandomGraph(V);
  Graph result_sequential = sequentialDijkstra(graph, V);
  Graph result_parallel = parallelDijkstra(graph, V);

  for (int i = 0; i < V; i++) {
    ASSERT_EQ(result_sequential[i], result_parallel[i]);
  }
}

int V = 20000;

TEST(DIJKSTRA_TBB, TEST_TIME) {
  Graph graph = getRandomGraph(V);

  double start = omp_get_wtime();
  dijkstra(graph, 0, V);
  double end = omp_get_wtime();
  double stime = end - start;
  std::cout << "\tsequential time: " << stime << "\n";

  start = omp_get_wtime();
  dijkstra_parallel(graph, 0, V);
  end = omp_get_wtime();
  double ptime = end - start;
  std::cout << "\tparallel time: " << ptime << "\n";

  std::cout << "\tefficiency: " << stime / ptime << "\n";
}
