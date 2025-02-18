#include "Graph.h"
#include <iostream>
#include <cstdlib>
#include <climits>

#define INF INT_MAX

Graph::Graph(Edge *edges_array, int num_nodes, int num_edges) : num_nodes(num_nodes), num_edges(num_edges)
{

    adjMatrix = (int **)malloc(num_nodes * sizeof(int *));
    for (int i = 0; i < num_nodes; ++i)
    {
        adjMatrix[i] = (int *)malloc(num_nodes * sizeof(int));
        for (int j = 0; j < num_nodes; ++j)
        {
            if (i == j)
            {
                adjMatrix[i][j] = 0;
            }
            else
            {
                adjMatrix[i][j] = INF;
            }
        }
    }
    for (int i = 0; i < num_edges; ++i)
    {
        int u = edges_array[i].node1;
        int v = edges_array[i].node2;
        int len = edges_array[i].length;
        adjMatrix[u][v] = len;
        adjMatrix[v][u] = len;
    }
}

Graph::~Graph()
{
    for (int i = 0; i < num_nodes; ++i)
    {
        free(adjMatrix[i]);
    }
    free(adjMatrix);
}

int *Graph::dijkstra(int source)
{
    int *distances = (int *)malloc(num_nodes * sizeof(int));
    bool *visited = (bool *)malloc(num_nodes * sizeof(bool));

    for (int i = 0; i < num_nodes; ++i)
    {
        distances[i] = INF;
        visited[i] = false;
    }

    distances[source] = 0;

    for (int i = 0; i < num_nodes; ++i)
    {
        int minDistance = INF;
        int minNode = -1;

        for (int j = 0; j < num_nodes; ++j)
        {
            if (!visited[j] && distances[j] < minDistance)
            {
                minDistance = distances[j];
                minNode = j;
            }
        }

        if (minNode == -1)
            break;

        visited[minNode] = true;

        for (int j = 0; j < num_nodes; ++j)
        {
            if (adjMatrix[minNode][j] != INF && distances[minNode] + adjMatrix[minNode][j] < distances[j])
            {
                distances[j] = distances[minNode] + adjMatrix[minNode][j];
            }
        }
    }

    for (int i = 0; i < num_nodes; ++i)
    {
        if (distances[i] == INF)
            distances[i] = -1;
    }

    free(visited);
    return distances;
}

void Graph::findConnectedComponents(bool *visited, int *componentIds, int componentId, int node)
{
    visited[node] = true;
    componentIds[node] = componentId;

    for (int i = 0; i < num_nodes; ++i)
    {
        if (adjMatrix[node][i] != INF && !visited[i])
        {
            findConnectedComponents(visited, componentIds, componentId, i);
        }
    }
}

int *Graph::get_centroids()
{
    bool *visited = (bool *)malloc(num_nodes * sizeof(bool));
    int *componentIds = (int *)malloc(num_nodes * sizeof(int));
    int componentId = 0;

    for (int i = 0; i < num_nodes; ++i)
    {
        visited[i] = false;
        componentIds[i] = -1;
    }

    for (int i = 0; i < num_nodes; ++i)
    {
        if (!visited[i])
        {
            findConnectedComponents(visited, componentIds, componentId, i);
            componentId++;
        }
    }

    int *centroids = (int *)malloc((componentId + 1) * sizeof(int));
    centroids[0] = componentId;

    for (int i = 0; i < componentId; ++i)
    {
        int minSum = INF;
        int centroid = -1;

        for (int j = 0; j < num_nodes; ++j)
        {
            if (componentIds[j] == i)
            {
                int sumOfDistances = calculateSumOfDistances(i, j, componentIds);
                if (sumOfDistances < minSum)
                {
                    minSum = sumOfDistances;
                    centroid = j;
                }
            }
        }

        centroids[i + 1] = centroid;
    }

    quickSort(centroids, 1, componentId);

    free(visited);
    free(componentIds);

    return centroids;
}

int Graph::calculateSumOfDistances(int componentId, int node, int *componentIds)
{
    int *distances = dijkstra(node);
    int sum = 0;

    for (int i = 0; i < num_nodes; ++i)
    {
        if (componentIds[i] == componentId)
        {
            sum += distances[i];
        }
    }

    free(distances);
    return sum;
}

int Graph::get_centroid_of_connected_component_containing(int node)
{
    bool *visited = (bool *)malloc(num_nodes * sizeof(bool));
    int *componentIds = (int *)malloc(num_nodes * sizeof(int));
    int componentId = 0;

    for (int i = 0; i < num_nodes; ++i)
    {
        visited[i] = false;
        componentIds[i] = -1;
    }

    for (int i = 0; i < num_nodes; ++i)
    {
        if (!visited[i])
        {
            findConnectedComponents(visited, componentIds, componentId, i);
            componentId++;
        }
    }

    int targetComponentId = componentIds[node];
    int *centroids = get_centroids();
    int centroid = -1;

    for (int i = 1; i <= centroids[0]; ++i)
    {
        if (componentIds[centroids[i]] == targetComponentId)
        {
            centroid = centroids[i];
            break;
        }
    }

    free(visited);
    free(componentIds);
    free(centroids);

    return centroid;
}

int *Graph::nodes_in_connected_component_with_centroid(int centroid_node)
{
    int centroid = get_centroid_of_connected_component_containing(centroid_node);

    if (centroid != centroid_node)
    {
        int *result = (int *)malloc(1 * sizeof(int));
        result[0] = 0;
        return result;
    }

    bool *visited = (bool *)malloc(num_nodes * sizeof(bool));
    int *componentIds = (int *)malloc(num_nodes * sizeof(int));
    int componentId = 0;

    for (int i = 0; i < num_nodes; ++i)
    {
        visited[i] = false;
        componentIds[i] = -1;
    }

    for (int i = 0; i < num_nodes; ++i)
    {
        if (!visited[i])
        {
            findConnectedComponents(visited, componentIds, componentId, i);
            componentId++;
        }
    }

    int targetComponentId = componentIds[centroid_node];
    int size = 0;

    for (int i = 0; i < num_nodes; ++i)
    {
        if (componentIds[i] == targetComponentId)
        {
            size++;
        }
    }

    int *result = (int *)malloc((size + 1) * sizeof(int));
    result[0] = size;

    int index = 1;
    for (int i = 0; i < num_nodes; ++i)
    {
        if (componentIds[i] == targetComponentId)
        {
            result[index++] = i;
        }
    }

    quickSort(result, 1, size);

    free(visited);
    free(componentIds);

    return result;
}

void Graph::quickSort(int *arr, int left, int right)
{
    if (left < right)
    {
        int pivotIndex = partition(arr, left, right);
        quickSort(arr, left, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, right);
    }
}

int Graph::partition(int *arr, int left, int right)
{
    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; ++j)
    {
        if (arr[j] <= pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;

    return i + 1;
}
