#include <iostream>
#include <math.h>
#include <limits.h>
#include "GraphUtils.h"
using namespace std;

HeapEdgeVertex* CreateNewVertex(Edge* e) {
    HeapEdgeVertex* NewVertex = (HeapEdgeVertex*)malloc(sizeof(HeapEdgeVertex));
    NewVertex->source = e->s;
    NewVertex->destination = e->d;
    NewVertex->weight = e->weight;
    return NewVertex;
}

HeapEdge* CreateNewHeap(int size) {
    HeapEdge* NewHeap = (HeapEdge*)malloc(sizeof(HeapEdge));
    NewHeap->curr_size = 0;
    NewHeap->total_size = size;
    NewHeap->arr = (HeapEdgeVertex**)malloc(size*sizeof(HeapEdgeVertex*));
    return NewHeap;
}

Que* CreateQueue(int size) {
    Que* q = (Que*)malloc(sizeof(Que));
    q->total_size = size;
    q->curr_size = 0;
    q->front = 0;
    q->rear = -1;
    q->arr = (int*)malloc(size*sizeof(int));
    return q;
}

void SwapEdges(struct HeapEdgeVertex** a, struct HeapEdgeVertex** b) {
    HeapEdgeVertex *t = *a;
    *a = *b;
    *b = t;
}

void HeapifyQueUp(struct HeapEdge* h, int i) {
    int parent;
    while(i > 0) {
        parent = floor((i-1)/2);
        if(h->arr[i]->weight > h->arr[parent]->weight) {
            SwapEdges(&h->arr[parent],&h->arr[i]);
            i = parent;
        }
        else {
            break;
        }
    }
}

void HeapifyQueDown(struct HeapEdge* h,int i, int size) {
    int max,left_child,right_child;
    max = i;
    left_child = 2*i + 1;
    right_child = 2*i + 2;
    if((left_child < size) && (h->arr[left_child]->weight > h->arr[max]->weight)) {
        max = left_child;
    }
    if((right_child < size) && (h->arr[right_child]->weight > h->arr[max]->weight)) {
        max = right_child;
    }
    if (max != i) {
        SwapEdges(&h->arr[max], &h->arr[i]);
        HeapifyQueDown(h,max,size);
    }
}

void HeapSort(struct HeapEdge* h, int n) {
    for(int i=n/2-1;i>=0;i--) {
        HeapifyQueDown(h,i,n);
    }
    for(int i=n-1;i>0;i--) {
        SwapEdges(&h->arr[0], &h->arr[i]);
        HeapifyQueDown(h,0,i);
    }
}

void InsertEdgeInHeap(struct HeapEdge* h, struct Edge* e) {
    HeapEdgeVertex* NewEdge = CreateNewVertex(e);
    h->curr_size = h->curr_size + 1;
    h->arr[h->curr_size-1] = NewEdge;
}

void MakeSet(int v, int* parent, int* rank) {
    parent[v] = -1;
    rank[v] = 0;
}

void Union(int v1, int v2, int* parent, int* rank) {
    if(rank[v1] > rank[v2]) {
        parent[v2] = v1;
    }
    else if(rank[v2] > rank[v1]) {
        parent[v1] = v2;
    }
    else {
        parent[v1] = v2;
        rank[v2] += 1;
    }
}

int Find(int v, int* parent, int* rank, int n) {
    int w = v;
    Que* find_queue = CreateQueue(n);
    while(parent[w] != -1) {
        Enque(find_queue,w);
        w= parent[w];
    }
    while(!(IsQueEmpty(find_queue))) {
        int x = Deque(find_queue);
        parent[x] = w;
    }
    return w;
}

bool IsQueFull(struct Que* que) {
    bool cap = false;
    cap = (que->curr_size == que->total_size);
    return cap;
}

bool IsQueEmpty(struct Que* que) {
    bool cap = false;
    cap = (que->curr_size == 0);
    return cap;
}

void Enque(struct Que* que, int element) {
    if(IsQueFull) {
        return;
    }
    que->rear = que->rear+1;
    que->arr[que->rear] = element;
    que->curr_size = que->curr_size + 1;
}

int Deque(struct Que* que) {
    if(IsQueEmpty) {
        return -1;
    }
    int element = que->arr[que->front];
    que->front = que->front + 1;
    que->curr_size = que->curr_size - 1;
    return element;
}

struct MSTGraph* createMSTGraph(int vertices) {
    MSTGraph* g_mst = (MSTGraph*)malloc(sizeof(MSTGraph));
    g_mst->vertices = vertices;
    g_mst->array = (AdjList*)malloc(vertices*sizeof(AdjList));
    for(int i=0;i<vertices;i++) {
        g_mst->array[i].head = NULL;
    }
}

void CreateMSTEdge(struct MSTGraph* g_mst,int d, int s, int w) {
    Node* mst_node_d = CreateNode(d,w);
    mst_node_d->next = g_mst->array[s].head;
    g_mst->array[s].head = mst_node_d;
    Node* mst_node_s = CreateNode(s,w);    
    mst_node_s->next = g_mst->array[d].head;
    g_mst->array[d].head = mst_node_s;
}

void PrintMSTGraph(struct MSTGraph* g_mst) {
    for(int i=0;i,g_mst->vertices;i++) {
        Node* temp = g_mst->array[i].head;
        cout << i << ": ";
        while(temp) {
            cout << temp->index << "(" << temp->weight <<"), ";
            temp = temp->next;
        }
        cout << endl;
    }
}

void BreadthFirstSearch(MSTGraph* g_mst,int s,int t) {
    int status[5000];
    int bandwidth[5000];
    int parent[5000];
    for(int i=0;i<g_mst->vertices;i++) {
        status[i] = 0;
        parent[i] = -1;
        bandwidth[i] = INT_MAX;
    }
    
    Que* q = CreateQueue(g_mst->vertices);
    int dest = -1;
    status[s] = 1;
    Enque(q,s);
    while(!IsQueEmpty(q)) {
        int x = Deque(q);
        Node* temp = g_mst->array[x].head;
        while(temp != NULL) {
            if(status[temp->index] == 0) {
                status[temp->index] = 1;
                Enque(q,temp->index);
                bandwidth[temp->index] = temp->weight;
                parent[temp->index] = x;
            }
            if(temp->index == t) {
                dest = t;
                break;
            }
        }
        if (dest == t) {
            break;
        }
    }
    if(status[t] != 1) {
        cout << "Path not found between source and destination." << endl;
    }
    else {
        int x = t;
        int wei = bandwidth[t];
        while(x != s) {
            wei = MinValue(wei,bandwidth[parent[x]]);
            x = parent[x];
        }
        cout << "Maximum Bandwidth is: " << wei << endl;
        x = t;
        cout << x << "(" << bandwidth[x] << ")";
        while (x != s) {
            x = parent[x];
            cout << "<- " << x << "(" << bandwidth[x] << ")";
        }
        cout << endl;
    }
}

void Kruskal(Graph* g,int s, int t) {
    HeapEdge* h = CreateNewHeap(g->num_edges);
    MSTGraph* g_k = createMSTGraph(g->vertices);
    Edge* head = g->edgehead;
    Edge* temp = head;
    while(temp != NULL) {
        InsertEdgeInHeap(h,temp);
        temp = temp->nextEdge;
    }
    HeapSort(h,g->num_edges);
    int* parent = (int*)malloc(g->vertices*sizeof(int));
    int* rank = (int*)malloc(g->vertices*sizeof(int));

    for(int i=0;i<g->vertices;i++) {
        MakeSet(i,parent,rank);
    }

    int j = g->num_edges-1,y=0;
    while(j >= 0 && y <= g->vertices-1) {
        HeapEdgeVertex* curr_hv = h->arr[j];
        int rank1 = Find(curr_hv->source,parent,rank,g->vertices);
        int rank2 = Find(curr_hv->destination,parent,rank,g->vertices);
        cout << rank1 << " " << rank2 << endl;
        if(rank1 != rank2) {
            Union(rank1,rank2,parent,rank);
            CreateMSTEdge(g_k,curr_hv->destination,curr_hv->source,curr_hv->weight);
            y++;
        }
        j--;
    }
    BreadthFirstSearch(g_k,s,t);
}