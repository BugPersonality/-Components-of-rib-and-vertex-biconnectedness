#include <iostream>
#include<fstream>
#include <vector>
using namespace std;

const int MAX_N = 10; // = max amount of vertices
vector<vector<int>> g(MAX_N);
bool used[MAX_N];
int timer, tin[MAX_N], fup[MAX_N];
int res_matrix[MAX_N][MAX_N];

vector<int> colors(MAX_N);

void IS_CUTPOINT(int a)
{
    cout << a << endl;
}

void dfs (int v, int p = -1)
{
    used[v] = true;
    tin[v] = fup[v] = timer++;
    int children = 0;
    for (size_t i=0; i<g[v].size(); ++i)
    {
        int to = g[v][i];
        if (to == p)  continue;
        if (used[to])
        {
            fup[v] = min (fup[v], tin[to]);
        }
        else
        {
            dfs (to, v);
            fup[v] = min (fup[v], fup[to]);
            if (fup[to] >= tin[v] && p != -1)
                IS_CUTPOINT(v);
            ++children;
        }
    }
    if (p == -1 && children > 1)
    {
        IS_CUTPOINT(v);
    }
}

int maxcolor = 0;

void paint(int vertex, int color, int parent)
{
    for (auto to_vertex : g[vertex])
    {
        if (to_vertex == parent)
        {
            continue;
        }

        if (!used[to_vertex])
        {
            if (fup[to_vertex] >= tin[to_vertex])
            {
                int new_color = ++maxcolor;

                res_matrix[to_vertex][vertex] = new_color;
                res_matrix[vertex][to_vertex] = new_color;

                paint(to_vertex, new_color, vertex);
            }
            else
            {
                res_matrix[to_vertex][vertex] = color;
                res_matrix[vertex][to_vertex] = color;

                paint(to_vertex, color, vertex);
            }
        }
        else if (tin[to_vertex] < tin[vertex])
        {
            res_matrix[to_vertex][vertex] = color;
            res_matrix[vertex][to_vertex] = color;
        }
    }
}

void solve(int n)
{
    for (int i = 0; i < n; i++)
    {
        if (!used[i])
        {
            maxcolor++;
            paint(i, maxcolor, -1);
        }
    }
}

void articulation_point_search(int n)
{
    timer = 0;
    for (int i=0; i<n; ++i)
        used[i] = false;
    dfs (0);
}

int main()
{
    ifstream in;
    ofstream out;
    in.open("C:\\Clion Projects\\Algosiki\\Diskretka\\Secound_graph_in");
    out.open("C:\\Clion Projects\\Algosiki\\Diskretka\\Secound_graph_out");
    int n, m;

    in >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int v, to_v;

        in >> v >> to_v;

        --v;
        --to_v;

        g[v].push_back(to_v);
        g[to_v].push_back(v);
    }

    articulation_point_search(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            res_matrix[i][j] = 0;
        }
    }

    solve(n);

    for (int i = 0; i < g.size(); i++)
    {
        for (auto j : g[i])
        {
            out << "Edge(" << i + 1 << " -> " << j + 1 << ") color = " << res_matrix[i][j] << endl;
        }
        cout << endl;
    }
}