// Copyright 2022 Tyrina Anastasia
#include "../../../modules/task_3/tyrina_a_dijkstra/dijkstra.h"

#include <omp.h>
#include <tbb/tbb.h>

#include <climits>
#include <iostream>
#include <random>
#include <vector>

Graph getRandomGraph(int V) {
  Graph graph(V, VectorInt(V));
  std::random_device dev;
  std::mt19937 gen(dev());

  for (int i = 0; i < V; ++i) {
    for (int j = i + 1; j < V; ++j) {
      graph[i][j] = gen() % 20;
      graph[j][i] = graph[i][j];
    }
    graph[i][i] = 0;
  }
  return graph;
}

int minDistance(const VectorInt& dist, const VectorBool& sptSet, int V) {
  int min = INT_MAX, min_index = 0;

  for (int v = 0; v < V; v++)
    if (sptSet[v] == false && dist[v] <= min) min = dist[v], min_index = v;

  return min_index;
}

VectorInt dijkstra(const Graph& graph, int src, int V) {
  VectorInt dist(V);
  VectorBool visited(V);

  for (int i = 0; i < V; i++) {
    dist[i] = INT_MAX;
    visited[i] = false;
  }

  dist[src] = 0;

  for (int count = 0; count < V - 1; count++) {
    int u = minDistance(dist, visited, V);

    visited[u] = true;

    for (int v = 0; v < V; v++) {
      if (!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
          dist[u] + graph[u][v] < dist[v]) {
        dist[v] = dist[u] + graph[u][v];
      }
    }
  }

  return dist;
}

VectorInt dijkstra_parallel(const Graph& graph, int src, int V) {
  VectorInt dist(V, INT_MAX);
  VectorBool visited(V, false);

  dist[src] = 0;

  struct vertex {
    int min;
    int min_index;
  };
  vertex current = {INT8_MAX, 0};

  for (int count = 0; count < V - 1; count++) {
    current.min = INT8_MAX;
    current = tbb::parallel_reduce(
        tbb::blocked_range<int>(0, V), current,
        [&](const tbb::blocked_range<int>& range, vertex cur) -> vertex {
          for (int i = range.begin(); i != range.end(); ++i) {
            if (!visited[i] && dist[i] <= cur.min) {
              cur.min = dist[i];
              cur.min_index = i;
            }
          }
          return cur;
        },
        [](vertex a, vertex b) { return a.min < b.min ? a : b; });

    int u = current.min_index;
    visited[u] = true;

    tbb::parallel_for(
        tbb::blocked_range<int>(0, V), [&](tbb::blocked_range<int> r) {
          for (int v = r.begin(); v < r.end(); ++v) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
              dist[v] = dist[u] + graph[u][v];
            }
          }
        });
  }

  return dist;
}

Graph sequentialDijkstra(const Graph& graph, int V) {
  Graph result(V, VectorInt(V));

  for (int src = 0; src < V; ++src) {
    result[src] = dijkstra(graph, src, V);
  }

  return result;
}

Graph parallelDijkstra(const Graph& graph, int V) {
  Graph result(V, VectorInt(V));

  for (int src = 0; src < V; ++src) {
    result[src] = dijkstra_parallel(graph, src, V);
  }

  return result;
}
