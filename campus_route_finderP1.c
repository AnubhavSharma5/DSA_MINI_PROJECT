#include <stdio.h>

#define V 8
const char *places[V] = {"Main Gate", "Library", "Block 1", "Block 2", "Cafeteria", "Auditorium", "Parking", "Computer Lab"};
int graph[V][V] = {
 {0,1,0,0,0,0,1,0}, {1,0,1,0,1,0,0,0},
 {0,1,0,1,0,0,0,1}, {0,0,1,0,0,1,0,0},
 {0,1,0,0,0,1,0,0}, {0,0,0,1,1,0,0,0},
 {1,0,0,0,0,0,0,1}, {0,0,1,0,0,0,1,0}
};

void showPlaces(void) {
    int i;
    printf("\nCampus locations:\n");
    for (i = 0; i < V; i++) printf("%d. %s\n", i + 1, places[i]);
}

void bfs(int source, int destination) {
    int visited[V] = {0}, parent[V], queue[V];
    int front = 0, rear = 0, i, path[V], count = 0, current;
    for (i = 0; i < V; i++) parent[i] = -1;
    visited[source] = 1;
    queue[rear++] = source;
    while (front < rear) {
        int u = queue[front++];
        if (u == destination) break;
        for (i = 0; i < V; i++) {
            if (graph[u][i] && !visited[i]) {
                visited[i] = 1;
                parent[i] = u;
                queue[rear++] = i;
            }
        }
    }
    if (!visited[destination]) { printf("No route found.\n"); return; }
    current = destination;
    while (current != -1) { path[count++] = current; current = parent[current]; }
    printf("Minimum-edge route: ");
    for (i = count - 1; i >= 0; i--) {
        printf("%s", places[path[i]]);
        if (i > 0) printf(" -> ");
    }
    printf("\nNumber of edges: %d\n", count - 1);
}

void dfs(int current, int visited[]) {
    int i;
    visited[current] = 1;
    printf("%s", places[current]);
    for (i = 0; i < V; i++) {
        if (graph[current][i] && !visited[i]) {
            printf(" -> ");
            dfs(i, visited);
        }
    }
}

int main(void) {
    int choice, source, destination, visited[V], i;
    do {
        printf("\n===== CAMPUS ROUTE FINDER =====\n1. Show locations\n2. Find route using BFS\n3. Show reachable locations using DFS\n0. Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1) { printf("Invalid input.\n"); return 0; }
        if (choice == 1) showPlaces();
        else if (choice == 2) {
            showPlaces();
            printf("Enter source number: "); if (scanf("%d", &source) != 1) return 0;
            printf("Enter destination number: "); if (scanf("%d", &destination) != 1) return 0;
            if (source < 1 || source > V || destination < 1 || destination > V) printf("Invalid location number.\n");
            else bfs(source - 1, destination - 1);
        } else if (choice == 3) {
            showPlaces(); printf("Enter starting location number: ");
            if (scanf("%d", &source) != 1) return 0;
            if (source < 1 || source > V) printf("Invalid location number.\n");
            else { for (i = 0; i < V; i++) visited[i] = 0; printf("DFS traversal: "); dfs(source - 1, visited); printf("\n"); }
        } else if (choice == 0) printf("Program ended.\n");
        else printf("Invalid choice. Try again.\n");
    } while (choice != 0);
    return 0;
}
