#include "mst.h"
#include "binaryHeap.h"   // Custom binary heap
#include "binomialHeap.h" // Custom binomial heap
#include "customErrorClass.h"

// ===== QuickUnion =====
QuickUnion::QuickUnion(int n)
{
    if (n <= 0)
    {
        throw MyException("Invalid number of elements");
    }

    parent.resize(n);
    for (int i = 0; i < n; ++i)
    {
        parent[i] = i;
    }
}

int QuickUnion::find(int x)
{
    if (x < 0 || x >= static_cast<int>(parent.size()))
    {
        throw MyException("Index out of bounds");
    }

    while (x != parent[x])
    {
        x = parent[x];
    }

    return x;
}

void QuickUnion::Union(int x, int y)
{
    if (x < 0 || x >= static_cast<int>(parent.size()) || y < 0 || y >= static_cast<int>(parent.size()))
    {
        throw MyException("Index out of bounds");
    }

    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY)
    {
        parent[rootX] = rootY;
    }
}

// ===== UnionFind =====
UnionFind::UnionFind(int n)
{
    if (n <= 0)
    {
        throw MyException("Invalid number of elements");
    }

    parent.resize(n);
    size.resize(n);
    for (int i = 0; i < n; ++i)
    {
        parent[i] = i;
        size[i] = 1;
    }
}

int UnionFind::find(int x)
{
    if (x < 0 || x >= static_cast<int>(parent.size()))
    {
        throw MyException("Index out of bounds");
    }

    if (x != parent[x])
    {
        parent[x] = find(parent[x]);
    }

    return parent[x];
}

void UnionFind::Union(int x, int y)
{
    if (x < 0 || x >= static_cast<int>(parent.size()) || y < 0 || y >= static_cast<int>(parent.size()))
    {
        throw MyException("Index out of bounds");
    }

    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY)
    {
        return;
    }

    if (size[rootX] < size[rootY])
    {
        parent[rootX] = rootY;
        size[rootY] += size[rootX];
    }
    else
    {
        parent[rootY] = rootX;
        size[rootX] += size[rootY];
    }
}

// ===== MST =====
MST::MST(int vertices)
{
    n = vertices;
}

void MST::addEdge(int u, int v, int weight)
{
    edges.push_back({u, v, weight});
}

int MST::kruskalV1() 
{
    sort(edges.begin(), edges.end(), MST::compareEdges);

    QuickUnion uf(n);
    int cost = 0;

    for (const auto& e : edges)
    {
        int rootU = uf.find(e.src);
        int rootV = uf.find(e.dest);
        if (rootU != rootV)
        {
            uf.Union(e.src, e.dest);
            cost += e.weight;
        }
    }

    return cost;
}

int MST::kruskalV2() 
{
    sort(edges.begin(), edges.end(), MST::compareEdges);

    UnionFind uf(n);
    int cost = 0;

    for (const auto& e : edges)
    {
        int rootU = uf.find(e.src);
        int rootV = uf.find(e.dest);
        if (rootU != rootV)
        {
            uf.Union(e.src, e.dest);
            cost += e.weight;
        }
    }

    return cost;
}

bool MST::compareEdges(const Edge& a, const Edge& b)
{
    return a.weight < b.weight;
}
