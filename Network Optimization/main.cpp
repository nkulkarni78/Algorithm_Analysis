#include <iostream>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <cmath>
#include "GraphUtils.h"
using namespace std;

int main() {
    srand(rand()*rand()*(unsigned)time(NULL)+11231);
    Graph* g = new Graph;
    Graph* g2 = new Graph;
    Graph* g_avg = new Graph;
    g = CreateSparseGraph(5000);
    g2 = CreateDenseGraph(5000);
    // Creates a file to store adjacency list of sparse graph;
    SparseGraph2File(g);
    // Creates a file to store adjacency list of dense graph;
    DenseGraph2File(g2);
    for(int i=0;i<1;i++) {
        double start = clock();
        g = CreateSparseGraph(5000);
        double end = clock();
        PrintGraphList(g);
        cout << "Average degree of the graph: " << ceil(double(g->num_edges*2)/double(g->vertices)) << endl;
        cout << "****************************************************************************" << endl;
        cout << "Time taken to create sparse graph is: " << double(end-start)/double(CLOCKS_PER_SEC) *1000 << " ms." <<endl;
        cout << "****************************************************************************" << endl;
        start = clock();
        g_avg = CreateSparseGraph_Avg(5000);
        end = clock();
        PrintGraphList(g_avg);
        cout << "Degree of the graph: " << g_avg->num_edges*2/g->vertices << endl;
        cout << "****************************************************************************" << endl;
        cout << "Time taken to create sparse graph is: " << double(end-start)/double(CLOCKS_PER_SEC) *1000 << " ms." <<endl;
        cout << "****************************************************************************" << endl;
        start = clock();
        g2 = CreateDenseGraph(5000);
        end = clock();
        PrintGraphList(g2);
        cout << "Degree of the graph: " << g2->num_edges*2/g2->vertices << endl;
        cout << "****************************************************************************" << endl;
        cout << "Time taken to create dense graph is: " << double(end-start)/double(CLOCKS_PER_SEC)*1000.00 << " ms." <<endl;
        cout << "****************************************************************************" << endl;
        for(int j=0;j<5;j++) {
            cout << "Running graph algorithms on graph pair: " << i+1<<endl;
            int s = rand()%5000;
            int d = rand()%5000;
            cout << "source: " << s << " dest: " << d << endl;
            start = clock();
            DijkstraMaxBandwidth(g,s,d);
            end = clock();
            cout << endl;
            cout << "************************************************************************" << endl;
            cout << "Time taken (Dijkstra No Heap on Sparse Graph): " << double(end - start)/double(CLOCKS_PER_SEC) <<" seconds"<< endl;
            cout << "************************************************************************" << endl;
            cout << "source: " << s << " dest: " << d << endl;
            start = clock();
            DijkstraMaxBandwidthHeap(g,s,d);
            end = clock();
            cout << endl;
            cout << "************************************************************************" << endl;
            cout << "Time taken (Dijkstra Heap on Sparse Graph): " << double(end - start)/double(CLOCKS_PER_SEC) <<" seconds"<< endl;
            cout << "************************************************************************" << endl;
            start = clock();
            Kruskal(g,s,d);
            end = clock();
            cout << endl;
            cout << "************************************************************************" << endl;
            cout << "Time taken (kruskal on Sparse Graph): " << double(end - start)/double(CLOCKS_PER_SEC) <<" seconds"<< endl;
            cout << "************************************************************************" << endl;
            cout << "source: " << s << " dest: " << d << endl;
            start = clock();
            DijkstraMaxBandwidth(g2,s,d);
            end = clock();
            cout << endl;
            cout << "************************************************************************" << endl;
            cout << "Time taken (Dijkstra No Heap on Dense Graph): " << double(end - start)/double(CLOCKS_PER_SEC) <<" seconds"<< endl;
            cout << "************************************************************************" << endl;
            cout << "source: " << s << " dest: " << d << endl;
            start = clock();
            DijkstraMaxBandwidthHeap(g2,s,d);
            end = clock();
            cout << endl;
            cout << "************************************************************************" << endl;
            cout << "Time taken (Dijkstra Heap on Dense Graph): " << double(end - start)/double(CLOCKS_PER_SEC) <<" seconds"<< endl;
            cout << "************************************************************************" << endl;
            start = clock();
            Kruskal(g,s,d);
            end = clock();
            cout << endl;
            cout << "************************************************************************" << endl;
            cout << "Time taken (Kruskal on Dense Graph): " << double(end - start)/double(CLOCKS_PER_SEC) <<" seconds"<< endl;
            cout << "************************************************************************" << endl;
        }
    }
   return 0;
}