// Copyright 2022 Tyrina Anastasia
#include "../../../modules/task_4/tyrina_a_dijkstra/dijkstra.h"

#include <omp.h>

#include <climits>
#include <random>
#include <vector>

#include "../../../3rdparty/unapproved/unapproved.h"

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

int minDistanceParallel(const VectorInt& dist, const VectorBool& sptSet, int V) {
  int min1 = INT_MAX, min_index1 = 0;
  int min2 = INT_MAX, min_index2 = 0;

  std::thread thread_1([V, &dist, &sptSet, &min1, &min_index1]() {
    for (int v = 0; v < V / 2; v++)
      if (sptSet[v] == false && dist[v] <= min1) min1 = dist[v], min_index1 = v;
    });

  std::thread thread_2([V, &dist, &sptSet, &min2, &min_index2]() {
    for (int v = V / 2; v < V; v++)
      if (sptSet[v] == false && dist[v] <= min2) min2 = dist[v], min_index2 = v;
    });

  thread_1.join();
  thread_2.join();

  int min_index;

  if (min1 < min2) {
    min_index = min_index1;
  }
  else {
    min_index = min_index2;
  }

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

  for (int count = 0; count < V - 1; count++) {
    int u = minDistanceParallel(dist, visited, V);

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