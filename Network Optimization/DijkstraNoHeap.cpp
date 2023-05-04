#include <iostream>
#include <limits.h>
#include "GraphUtils.h"
using namespace std;

/*
status array defines the node status
unseed = -1;
fringe = 0;
seen = 1;
*/

bool CheckFringe(int *status,int total) {
    bool exists = false;
    for(int i=0;i<total;i++) {
        if(status[i]==0) {
            exists = true;
            break;
        }
    }
    return exists;
}

int GetMaxFringe(int *bandwidth, int *status, int total) {
    int max_bandwidth = -1, max_fringe = -1;
    for (int i = 0;i<total;i++) {
        if(status[i] == 0 && bandwidth[i] > max_bandwidth) {
            max_bandwidth = bandwidth[i];
            max_fringe = i;
        }
    }
    return max_fringe;
}

int MinValue (int a, int b) {
    if(a<b) {
        return a;
    }
    else {
        return b;
    }
}
void DijkstraMaxBandwidth(Graph *g, int source, int dest) {
    int status[5000],bandwidth[5000],parent[5000];
    for(int i=0;i<g->vertices;i++) {
        status[i] = -1;
        parent[i] = -1;
        bandwidth[i] = -1;
    }
    status[source] = 1;
    Node *temp = g->arrhead[source].head;
    while(temp != NULL) {
        status[temp->index] = 0;
        parent[temp->index] = source;
        bandwidth[temp->index] = temp->weight;
        temp = temp->next;
    }
    int count = 0;
    while(CheckFringe(status,g->vertices)) {
        int maxfringe = GetMaxFringe(bandwidth,status,g->vertices);
        status [maxfringe] = 1;
        Node* temp1 = g->arrhead[maxfringe].head;
        while (temp1 != NULL) {
            if(status[temp1->index] == -1) {
                status[temp1->index] = 0;
                bandwidth[temp1->index] = MinValue(bandwidth[maxfringe],temp1->weight);
                parent[temp1->index] = maxfringe;
            }
            else if ((status[maxfringe] == 0 && (bandwidth[temp1->index] < MinValue(bandwidth[maxfringe],temp1->weight)))) {
                bandwidth[temp1->index] = MinValue(bandwidth[maxfringe],temp1->weight);
                parent[temp1->index] = maxfringe;
            }
            temp1 = temp1->next;
        }
    }
    if (status[dest] != 1) {
        cout << "No path found between source and destination. " << endl;
    }
    else {
        cout << "Maximum bandwidth is: " << bandwidth[dest] << endl;
        cout << "Path from source to destination is as follows: "<< endl;
        int x = dest; 
        cout << x << "(" <<bandwidth[dest] << ")";
        while(x!=source) {
            x=parent[x];
            cout << " <- " << x << "(" << bandwidth[x] << ")" ;
        }
    }
}