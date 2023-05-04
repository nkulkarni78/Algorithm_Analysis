#ifndef GraphUtils_H
#define GraphUtils_H

//Declare variables used in graph generation
struct Node {
    int index, weight;
    Node* next;
};

struct Edge {
    int s;
    int d;
    int weight;
    int edge_number = 0;
    Edge* nextEdge;
};

struct AdjList {
    Node* head;
};

struct Graph {
    int vertices;
    int num_edges = 0;
    AdjList* arrhead;
    Edge* edgehead;
};

//Declare the methods being used in graph generation
struct Node* CreateNode(int value, int w);
struct Edge* CreateEdge(int s, int d, int w);
void AddEdgeInGraph(Graph * g, int s, int d);
struct Graph* CreateSparseGraph(int vertices);
struct Graph* CreateDenseGraph(int vertices);
Graph* CreateSparseGraph_Avg(int vertices);
void PrintGraphList(Graph* g);
void PrintGraphEdges(Graph* g);
void SparseGraph2File(Graph* g);
void DenseGraph2File(Graph* g);

//Declare methods being used in Dijkstra without heap;
bool CheckFringe(int *status);
int GetMaxFringe(int *bandwidth, int *status);
int MinValue (int a, int b);
void DijkstraMaxBandwidth(Graph *g, int source, int dest);

//Declare heap and heap vertices
struct HeapNode {
    int vertex, bandwidth;
};

struct Heap {
    int curr_size, total_size, *position;
    HeapNode **arr;
};

//Declare methods used in max heap creation and Dijkstra Heap algorithm
struct HeapNode* CreateMaxHeapNode(int vertex,int bandwidth);
struct Heap* createMaxHeap(int size);
void SwapNodes(struct HeapNode** a,struct HeapNode** b);
bool isEmpty(struct Heap* maxHeap);
void HeapifyDown(struct Heap* h,int i);
void HeapifyUp(struct Heap* h,int i);
void InsertFringes(struct Heap* h, int index, int bandwidth);
void updateFringeheap(struct Heap* h,int v,int bandwidth);
struct HeapNode* GetMaxFringe(struct heap* h);
void DijkstraMaxBandwidthHeap(Graph* g,int s, int t);

//Declare Kruskals heap elements
struct HeapEdgeVertex {
    int source, destination, weight;
};

struct HeapEdge {
    int total_size;
    int curr_size;
    struct HeapEdgeVertex **arr;
};

struct Que {
    int front, rear;
    int curr_size;
    int total_size;
    int* arr;
};

struct MSTGraph{
    int vertices;
    AdjList *array;
};

//Declare methods used in Queue creation and Kruskals algorithm
void SwapEdges(struct HeapEdgeVertex** a, struct HeapEdgeVertex** b);
void HeapifyQueUp(struct HeapEdge* h, int i);
void HeapifyQueDown(struct HeapEdge* h,int i, int size);
void HeapSort(struct HeapEdge* h, int n);
void InsertEdgeInHeap(struct HeapEdge* h, struct Edge* e);
void MakeSet(int v, int* parent, int* rank);
void Union(int v1, int v2, int* parent, int* rank);
int Find(int v, int* parent, int* rank, int n);
bool IsQueFull(struct Que* que);
bool IsQueEmpty(struct Que* que);
void Enque(struct Que* que, int element);
int Deque(struct Que* que);
void BreadthFirstSearch(MSTGraph* g_mst,int s,int t);
void Kruskal(Graph* g_k,int s, int t);
void CreateMSTEdge(struct MSTGraph* g_mst,int d, int s, int w);
struct MSTGraph* createMSTGraph(int vertices);
void PrintMSTGraph(struct MSTGraph* g_mst);
#endif