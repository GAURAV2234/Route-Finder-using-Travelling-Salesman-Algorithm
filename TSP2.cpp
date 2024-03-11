#include <iostream>
#include <vector>
#include <algorithm> // for std::next_permutation
#include <climits> // for INT_MAX
#include <sstream> // for stringstream

using namespace std;

// Number of cities
#define N 10

// Function to calculate the total distance of the tour
int calculateDistance(const int path[], const int dist[N][N]) {
    int totalDistance = 0;
    for (int i = 0; i < N; i++) {
        totalDistance += dist[path[i]][path[(i + 1) % N]];
    }
    return totalDistance;
}

// Utility function to convert path and distances between cities to string
string pathToString(const int path[], const int dist[N][N], const vector<string>& cityNames) {
    stringstream ss;
    for (int i = 0; i < N; i++) {
        int from = path[i];
        int to = path[(i + 1) % N];
        int distance = dist[from][to];
        ss << cityNames[from] << " -> " << cityNames[to] << " (" << distance << " km), ";
    }
    string pathStr = ss.str();
    // Remove the last comma and space
    pathStr = pathStr.substr(0, pathStr.length() - 2);
    return pathStr;
}

int main() {
    // Distance matrix representing the distances between each pair of cities
    int dist[N][N] = {
        {0, 1420, 980, 2050, 1330, 710, 150, 530, 1150, 280},
        {1420, 0, 2150, 1460, 2200, 1580, 1430, 930, 280, 1160},
        {980, 2150, 0, 1860, 350, 570, 840, 1490, 2000, 1260},
        {2050, 1460, 1860, 0, 1660, 1460, 2050, 2060, 1520, 1910},
        {1330, 2200, 350, 1660, 0, 630, 1150, 1820, 2100, 1590},
        {710, 1580, 570, 1460, 630, 0, 560, 1200, 1560, 910},
        {150, 1430, 840, 2050, 1150, 560, 0, 660, 1200, 420},
        {530, 930, 1490, 2060, 1820, 1200, 660, 0, 670, 270},
        {1150, 280, 2000, 1520, 2100, 1560, 1200, 670, 0, 930},
        {280, 1160, 1260, 1910, 1590, 910, 420, 270, 930, 0}
    };

    vector<string> cityNames = {"Mumbai", "Delhi", "Bangalore", "Kolkata", "Chennai", "Hyderabad", "Pune", "Ahmedabad", "Jaipur", "Surat"};
    cout<<"\n\n\t\t\t\t\t\tRoute Finder\n\n";
    cout << "\n\nList of Cities:\n\n\n";
    for (int i = 0; i < N; ++i) {
        cout << i << " for " << cityNames[i] << "\n";
    }
    cout << "\nEnter your chosen city index: ";

    int path[N];
    for (int i = 0; i < N; i++) {
        path[i] = i;
    }

    int start;
    cin >> start;

    swap(path[0], path[start]);

    int minPath[N], minDistance = INT_MAX;
    vector<pair<string, int>> allPaths;

    do {
        int currentDistance = calculateDistance(path, dist);
        string currentPathStr = pathToString(path, dist, cityNames);
        allPaths.push_back(make_pair(currentPathStr, currentDistance));

        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            copy(path, path + N, minPath);
        }

    } while (next_permutation(path + 1, path + N));

    cout << "All possible paths:\n";
    for (const auto& p : allPaths) {
        cout << p.first << " - Total distance: " << p.second << " km\n";
    }

    cout << "\nBest path:\n";
    cout << pathToString(minPath, dist, cityNames) << " - Total distance: " << minDistance << " km\n";

    return 0;
}
