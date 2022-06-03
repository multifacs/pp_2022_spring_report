// Copyright 2022 Tyrina Anastasia
#include <gtest/gtest.h>

#include "./dijkstra.h"

TEST(DIJKSTRA_SEQ, TEST_1) {
  int V = 9;
  Graph graph = {{0, 4, 0, 0, 0, 0, 0, 8, 0},  {4, 0, 8, 0, 0, 0, 0, 11, 0},
                 {0, 8, 0, 7, 0, 4, 0, 0, 2},  {0, 0, 7, 0, 9, 14, 0, 0, 0},
                 {0, 0, 0, 9, 0, 10, 0, 0, 0}, {0, 0, 4, 14, 10, 0, 2, 0, 0},
                 {0, 0, 0, 0, 0, 2, 0, 1, 6},  {8, 11, 0, 0, 0, 0, 1, 0, 7},
                 {0, 0, 2, 0, 0, 0, 6, 7, 0}};

  Graph result = sequentialDijkstra(graph, V);
}

TEST(DIJKSTRA_SEQ, TEST_2) {
  int V = 10;
  Graph graph = getRandomGraph(V);
  Graph result = sequentialDijkstra(graph, V);
}

TEST(DIJKSTRA_SEQ, TEST_3) {
  int V = 20;
  Graph graph = getRandomGraph(V);
  Graph result = sequentialDijkstra(graph, V);
}

TEST(DIJKSTRA_SEQ, TEST_4) {
  int V = 30;
  Graph graph = getRandomGraph(V);
  Graph result = sequentialDijkstra(graph, V);
}

TEST(DIJKSTRA_SEQ, TEST_5) {
  int V = 40;
  Graph graph = getRandomGraph(V);
  Graph result = sequentialDijkstra(graph, V);
}
