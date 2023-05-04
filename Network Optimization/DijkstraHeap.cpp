#include <iostream>
#include <math.h>
#include "GraphUtils.h"
using namespace std;

/*
status array defines the node status
unseed = -1;
fringe = 0;
seen = 1;
*/

HeapNode* CreateMaxHeapNode(int vertex,int bandwidth) {
    HeapNode* newHeapNode = new HeapNode;
    newHeapNode->vertex = vertex;
    newHeapNode->bandwidth = bandwidth;
    return newHeapNode;
}

Heap* createMaxHeap(int size) {
    Heap* MaxHeap = new Heap;
    MaxHeap->curr_size = 0;
    MaxHeap->total_size = size;
    MaxHeap->arr = (HeapNode**)malloc(size*sizeof(size));
    MaxHeap->position = (int*)malloc(size*sizeof(int));
    for(int i=0;i<size;i++) {
        MaxHeap->position[i] = -1; 
    }
    return MaxHeap;
}

void SwapNodes(struct HeapNode** a,struct HeapNode** b) {
    HeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

bool isEmpty(struct Heap* maxHeap) {
    bool size = false;
    size = (maxHeap->curr_size == 0);
    return size;
}

void HeapifyDown(struct Heap* h,int i){
    int max,left_child,right_child;
    max = i;
    left_child = 2*i + 1;
    right_child = 2*i + 2;
    if((left_child < h->curr_size) && (h->arr[left_child]->bandwidth > h->arr[max]->bandwidth)) {
        max = left_child;
    }
    if((right_child < h->curr_size) && (h->arr[right_child]->bandwidth > h->arr[max]->bandwidth)) {
        max = right_child;
    }
    if(max != i) {
        HeapNode* max_node = h->arr[max];
        HeapNode* curr_node = h->arr[i];
        h->position[max_node->vertex] = i;
        h->position[curr_node->vertex] = max;
        SwapNodes(&h->arr[max], &h->arr[i]);
        HeapifyDown(h,max);
    }
}

void HeapifyUp(struct Heap* h,int i) {
    int parent = floor((i-1)/2);
    while(h->arr[parent]->bandwidth < h->arr[i]->bandwidth && i >=2) {
        h->position[h->arr[i]->vertex] = parent;
        h->position[h->arr[parent]->vertex] = i;
        SwapNodes(&h->arr[parent], &h->arr[i]);
        i = parent;
    }

    /*while(i>0){
        parent = floor((i-1)/2);
        if(h->arr[parent]->bandwidth < h->arr[i]->bandwidth && i >=2) {
            h->position[h->arr[i]->vertex] = parent;
            h->position[h->arr[parent]->vertex] = i;
            SwapNodes(&h->arr[parent], &h->arr[i]);
            i = parent;
        }
        else {
            h->position[h->arr[i]->vertex] = i;
            break;
        }
    } */
}

void InsertFringes(struct Heap* h, int index, int bandwidth) {
    HeapNode* fringe = CreateMaxHeapNode(index, bandwidth);
    h->curr_size = h->curr_size + 1;
    h->arr[h->curr_size-1] = fringe;
    h->position[fringe->vertex] = h->curr_size - 1;
    HeapifyDown(h,0);
    //HeapifyUp(h,h->curr_size-1);
}

void updateFringeheap(struct Heap* h,int v,int bandwidth) {
    int updated_index = h->position[v];
    h->arr[updated_index]->bandwidth = bandwidth;
    HeapifyDown(h,0);
}

HeapNode* GetMaxFringe(struct Heap* h) {
    if(isEmpty(h)) {
        return NULL;
    }
    HeapNode* root = h->arr[0];
    HeapNode* last_leaf = h->arr[h->curr_size-1];
    h->arr[0] = last_leaf;
    h->position[root->vertex] = h->curr_size-1;
    h->position[last_leaf->vertex] = 0;
    h->curr_size = h->curr_size - 1;
    HeapifyDown(h,0);
    return root;
}

void DijkstraMaxBandwidthHeap(Graph *g, int source, int dest) {
    int nodes = g->vertices;
    int status[5000];
    int parent[5000];
    int bandwidth[5000];
    Heap* fringeheap = createMaxHeap(g->vertices);
    for(int i=0;i<g->vertices;i++) {
        status[i] = -1;
        parent[i] = -1;
        bandwidth[i] = -1;
    }
    status[source] = 1;
    Node* temp = g->arrhead[source].head;
    while(temp != NULL) {
        status[temp->index] = 0;
        parent[temp->index] = source;
        bandwidth[temp->index] = temp->weight;
        InsertFringes(fringeheap,temp->index,bandwidth[temp->index]);
        temp = temp->next;
    }
    while(!(isEmpty(fringeheap))) {
        HeapNode* temp1 = GetMaxFringe(fringeheap);
        int max_fringe = temp1->vertex;
        status[max_fringe] = 1;
        Node* temp2 = g->arrhead[max_fringe].head;
        while(temp2 != NULL) {
            if(status[temp2->index] == -1) {
                status[temp2->index] = 0;
                bandwidth[temp2->index] = MinValue(bandwidth[max_fringe],temp2->weight);
                parent[temp2->index] = max_fringe;
                InsertFringes(fringeheap,temp2->index,bandwidth[temp2->index]);
            }
            else if((status[max_fringe] == 0) && (bandwidth[temp2->index] < MinValue(bandwidth[max_fringe],temp2->weight))) {
                bandwidth[temp2->index] = MinValue(bandwidth[max_fringe],temp2->weight);
                parent[temp2->index] = max_fringe;
                updateFringeheap(fringeheap,temp2->index,bandwidth[temp2->index]);
            }
            temp2 = temp2->next;
        }
    }
    if(status[dest] != 1) {
        cout << "No path Exists between source and destination..!" << endl;
    }
    else {
        cout << "Maximum bandwidth is: " << bandwidth[dest] << endl;
        cout << "Path from source to destination is as follows: "<< endl;
        int x = dest; 
        cout << x<< "(" <<bandwidth[dest] << ")";
        while(x!=source) {
            x=parent[x];
            cout << " <- " << x << "(" << bandwidth[x] << ")";
        }
    }
}