// Copyright 2022 Tyrina Anastasia
#include <gtest/gtest.h>

#include "../../../3rdparty/unapproved/unapproved.h"
#include "./dijkstra.h"

TEST(DIJKSTRA_STD, TEST_1) {
  int V = 4;
  Graph graph = getRandomGraph(V);
  Graph result_sequential = sequentialDijkstra(graph, V);
  Graph result_parallel = parallelDijkstra(graph, V);
  for (int i = 0; i < V; i++) {
    ASSERT_EQ(result_sequential[i], result_parallel[i]);
  }
}

TEST(DIJKSTRA_STD, TEST_2) {
  int V = 4;
  Graph graph = getRandomGraph(V);
  Graph result_sequential = sequentialDijkstra(graph, V);
  Graph result_parallel = parallelDijkstra(graph, V);
}

TEST(DIJKSTRA_STD, TEST_3) {
  int V = 4;
  Graph graph = getRandomGraph(V);
  Graph result_sequential = sequentialDijkstra(graph, V);
  Graph result_parallel = parallelDijkstra(graph, V);
}

TEST(DIJKSTRA_STD, TEST_4) {
  int V = 4;
  Graph graph = getRandomGraph(V);
  Graph result_sequential = sequentialDijkstra(graph, V);
  Graph result_parallel = parallelDijkstra(graph, V);
}

int V = 20000;

TEST(DIJKSTRA_STD, TEST_TIME) {
  Graph graph = getRandomGraph(V);

  auto t1 = clock();
  dijkstra_parallel(graph, 0, V);
  auto t2 = clock();

  auto t3 = clock();
  dijkstra(graph, 0, V);
  auto t4 = clock();

  printf("sequential time: %f\n", static_cast<float>(t4 - t3) / CLOCKS_PER_SEC);
  printf("parallel time: %f\n", static_cast<float>(t2 - t1) / CLOCKS_PER_SEC);
  printf("eff: %f\n", (static_cast<float>(t4 - t3) / CLOCKS_PER_SEC) /
    (static_cast<float>(t2 - t1) / CLOCKS_PER_SEC));
}