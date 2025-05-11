#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

const int dx[] = {1, 0, -1, 0}; // right, up, left, down
const int dy[] = {0, 1, 0, -1};

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

bool is_valid(int x, int y, int rows, int cols, const vector<vector<int>>& grid) {
    return x >= 0 && x < cols && y >= 0 && y < rows && grid[y][x] == 0;
}

// Lee's Algorithm
bool lee(const vector<vector<int>>& grid, Point start, Point end, vector<vector<int>>& dist) {
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<Point> q;
    q.push(start);
    visited[start.y][start.x] = true;
    dist[start.y][start.x] = 0;

    while (!q.empty()) {
        Point p = q.front(); q.pop();
        if (p == end) return true;

        for (int i = 0; i < 4; ++i) {
            int nx = p.x + dx[i], ny = p.y + dy[i];
            if (is_valid(nx, ny, rows, cols, grid) && !visited[ny][nx]) {
                visited[ny][nx] = true;
                dist[ny][nx] = dist[p.y][p.x] + 1;
                q.push({nx, ny});
            }
        }
    }
    return false;
}

// Soukup's Algorithm
bool soukup(const vector<vector<int>>& grid, Point start, Point end, vector<vector<int>>& dist) {
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<Point> q;
    q.push(start);
    visited[start.y][start.x] = true;
    dist[start.y][start.x] = 0;

    while (!q.empty()) {
        Point p = q.front(); q.pop();
        if (p == end) return true;

        int best_dir = -1, min_h = 1e9;
        for (int i = 0; i < 4; ++i) {
            int nx = p.x + dx[i], ny = p.y + dy[i];
            if (is_valid(nx, ny, rows, cols, grid) && !visited[ny][nx]) {
                int h = abs(nx - end.x) + abs(ny - end.y);
                if (h < min_h) {
                    min_h = h;
                    best_dir = i;
                }
            }
        }

        if (best_dir != -1) {
            int nx = p.x + dx[best_dir], ny = p.y + dy[best_dir];
            visited[ny][nx] = true;
            dist[ny][nx] = dist[p.y][p.x] + 1;
            q.push({nx, ny});
        } else {
            for (int i = 0; i < 4; ++i) {
                int nx = p.x + dx[i], ny = p.y + dy[i];
                if (is_valid(nx, ny, rows, cols, grid) && !visited[ny][nx]) {
                    visited[ny][nx] = true;
                    dist[ny][nx] = dist[p.y][p.x] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }

    return false;
}

bool getShortestPath(vector<Point>& path, vector<vector<int>>& dist, vector<vector<int>>& grid, Point start, Point curr) {
    if (curr == start) {
        path.push_back(curr);
        return true;
    }
    for (int i = 0; i < 4; ++i) {
        int nx = curr.x + dx[i], ny = curr.y + dy[i];
        if (is_valid(nx, ny, grid.size(), grid[0].size(), grid) &&
            dist[ny][nx] == dist[curr.y][curr.x] - 1) {
            curr.x = nx;
            curr.y = ny;
            path.push_back(curr);
            if (getShortestPath(path, dist, grid, start, curr)) {    
                return true;
            }
            path.pop_back();
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    string method = "lee";
    if (argc > 1) method = argv[1];

    ifstream in("examples/example1.txt");
    int rows, cols;
    in >> rows >> cols;
    vector<vector<int>> grid(rows, vector<int>(cols));

    for (int i = rows - 1; i >= 0; --i)
        for (int j = 0; j < cols; ++j)
            in >> grid[i][j];

    Point start, end;
    in >> start.x >> start.y >> end.x >> end.y;

    vector<vector<int>> dist(rows, vector<int>(cols, -1));
    bool found = false;

    if (method == "lee") {
        found = lee(grid, start, end, dist);
        cout << "[Lee] ";
    } else if (method == "soukup") {
        found = soukup(grid, start, end, dist);
        cout << "[Soukup] ";
    } else {
        cout << "Unknown method: " << method << endl;
        return 1;
    }

    if (found) {
        cout << "[Lee] Path found with length: " << dist[end.y][end.x] << endl;
        ofstream out("output/output_grid.txt");
        
        // Backtrack shortest path
        vector<Point> path;
        Point curr = end;
        getShortestPath(path, dist, grid, start, curr);

        vector<vector<char>> visual(grid.size(), vector<char>(grid[0].size(), '.'));
        for (int y = 0; y < grid.size(); ++y)
            for (int x = 0; x < grid[0].size(); ++x)
                if (grid[y][x] == 1) visual[y][x] = '#';

        for (const auto& p : path)
            visual[p.y][p.x] = '*';

        visual[start.y][start.x] = 'S';
        visual[end.y][end.x] = 'E';

        cout << "\nVisualized Path Grid:\n";
        for (int y = grid.size()-1; y >= 0; --y) {
            for (int x = 0; x < grid[0].size(); ++x) {
                cout << visual[y][x];
                out << visual[y][x];
            }
            cout << endl;
            out << '\n';
        }
        out.close();
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
