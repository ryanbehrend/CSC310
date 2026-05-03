#include "mst.h"
#include "binaryHeap.h"       // Custom binary heap
#include "binomialHeap.h"   // Custom binomial heap

// ===== QuickUnion =====
QuickUnion::QuickUnion(int n) 
{

}

int QuickUnion::find(int x) 
{

}

void QuickUnion::Union(int x, int y) 
{

}

// ===== UnionFind =====
UnionFind::UnionFind(int n) 
{

}

int UnionFind::find(int x) 
{

}

void UnionFind::Union(int x, int y) 
{

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

}

int MST::kruskalV2() 
{

}
