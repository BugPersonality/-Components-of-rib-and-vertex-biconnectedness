#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

vector<vector<int>> g(6);
bool used[6];
int timer, tin[6], fup[6];
vector<int> colors(6, 0);

void IS_BRIDGE(int a, int b)
{
    cout << a << b << endl;
}

void dfs (int v, int p = -1) {
    used[v] = true;
    tin[v] = fup[v] = timer++;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (to == p)  continue;
        if (used[to])
            fup[v] = min (fup[v], tin[to]);
        else {
            dfs (to, v);
            fup[v] = min (fup[v], fup[to]);
            if (fup[to] > tin[v])
                IS_BRIDGE(v,to);
        }
    }
}

int max_color = 0;

void paint(int vertex, int color)
{
    colors[vertex] = color;

    for (auto u : g[vertex])
    {
        if (colors[u] == 0)
        {
            if (fup[u] > tin[vertex])
            {
                max_color++;
                paint(u, max_color);
            }
            else
            {
                paint(u, color);
            }
        }
    }
}

void solve(int n)
{
    max_color = 0;
    for (int vertex = 0; vertex < n; vertex++)
    {
        if (colors[vertex] == 0)
        {
            max_color++;

            paint(vertex, max_color);
        }
    }
}


void find_bridges(int n) {
    timer = 0;
    for (int i=0; i<n; ++i)
        used[i] = false;
    for (int i=0; i<n; ++i)
        if (!used[i])
            dfs (i);
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

    find_bridges(n);
    solve(n);

    for(int i = 0; i < colors.size(); i++)
    {
        out << "вершина " << i + 1 << " принадлежит компоненте номер: " << colors[i] << endl;
    }
}