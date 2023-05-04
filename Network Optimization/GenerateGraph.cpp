#include <iostream>
#include <random>
#include <fstream>

using namespace std;
static long long int dense_seed = 35982;
static long long edge_count=0;
random_device seed;
random_device rdsparse;

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

Node* CreateNode(int value, int w) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->index = value;
    newNode->weight = w;
    newNode->next = NULL;
    return newNode;
}

Edge* CreateEdge(int s, int d, int w) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->s = s;
    e->d = d;
    e->weight = w;
    e->edge_number = 0;
    e->nextEdge = NULL;
    return e;
}

void AddEdgeInGraph(Graph * g, int s, int d) {
    g->num_edges = g->num_edges+1;
    uniform_int_distribution<int> weights(20,1000);
    int k = weights(seed);
    Node* newNode_d = CreateNode(d,k);
    newNode_d->next = g->arrhead[s].head;
    g->arrhead[s].head = newNode_d;

    Node* newNode_s = CreateNode(s,k);
    newNode_s->next = g->arrhead[d].head;
    g->arrhead[d].head = newNode_s;

    Edge* m = CreateEdge(s,d,k);
    edge_count += 1; 
    m->edge_number = edge_count;
    m->nextEdge = g->edgehead;
    g->edgehead = m;
}

Graph* CreateSparseGraph(int vertices) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->vertices = vertices;
    g->num_edges = 0;
    g->arrhead = (AdjList*)malloc(vertices*sizeof(AdjList));
    g->edgehead = NULL;
    int check=0;

    for(int i=0;i<vertices;i++) {
        g->arrhead[i].head = NULL;
    }
    //Loop to make sure graph is connected 
    for(int i=0;i<vertices;i++) {
        AddEdgeInGraph(g,i%vertices,(i+1)%vertices);
    }

    uniform_int_distribution<int> distribute(0,vertices-1);
    for(int i=0; i<vertices; i++) {
        for (int j=0;j<50;j++) {
            int count_of_nodes=0, count_of_rand_nodes=0;
            int check = 0;
            int x = distribute(seed);
            Node* temp_x = g->arrhead[x].head;
            while(temp_x != NULL) {
                count_of_rand_nodes++;
                temp_x = temp_x->next;
            }
            Node* temp = g->arrhead[i].head;
            while(temp != NULL) {
                if (i == x || temp->index == x) {
                    check = 1;
                    break;
                }
                count_of_nodes++;
                temp = temp->next;
            }
            
            if(check == 0 && count_of_nodes <=5 && count_of_rand_nodes <= 5) {
                AddEdgeInGraph(g,i,x);
            }
            else {
                continue;
            }
        }
    }
    if(g->num_edges < 15000) {
        int balance_edges = 15000 - g->num_edges;
        int balance_arr[100]{0};
        int j = 0;
        for(int i=0;i<vertices;i++) {
            Node* temp = g->arrhead[i].head;
            int count = 0;
            while(temp != NULL) {
                count++;
                temp = temp->next;
            }
            if(count < 6) {
                balance_arr[j] = i;
                j++;
            }
        }
        uniform_int_distribution<int> check_vertices(0,j-1);
        for(int k=0;k<j;k++) {
            int count_of_nodes=0;
            int balance_vertex = balance_arr[k];
            int y = check_vertices(seed);
            int new_vertex = balance_arr[y];
            Node* temp = g->arrhead[new_vertex].head;
            while(temp != NULL) {
                if ( new_vertex == balance_vertex || temp->index == new_vertex) {
                    check = 1;
                    break;
                }
                count_of_nodes++;
                temp = temp->next;
            }
            
            if(check == 0 && count_of_nodes <=6 ) {
                AddEdgeInGraph(g,new_vertex,balance_vertex);
            }
            else {
                continue;
            }
        }
        cout << endl;
    }
    return g;
}
Graph* CreateDenseGraph(int vertices) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->vertices = vertices;
    g->num_edges = 0;
    g->arrhead = (AdjList*)malloc(vertices*sizeof(AdjList));
    for(int i=0;i<vertices;i++) {
        g->arrhead[i].head = NULL;
    }

    for(int i=0;i<vertices;i++) {
        AddEdgeInGraph(g,i%vertices,(i+1)%vertices);
    }

    uniform_int_distribution<int> distribute(0,vertices-1);
    for(int i=0;i<vertices;i++) {
        for(int j=0;j<499;j++) {
            int check = 0;
            int x = distribute(seed);
            Node* temp = g->arrhead[i].head;
            while(temp != NULL) {
                if(i == x || temp->index == x) {
                    check = 1;
                    break;
                }
                temp = temp->next;
            }
            if(check ==0) {
                AddEdgeInGraph(g,i,x);
            }
            else {
                j--;
                continue;
            }
        }
    }
    return g;
}

Graph* CreateSparseGraph_Avg(int vertices) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->vertices = vertices;
    g->num_edges = 0;
    g->arrhead = (AdjList*)malloc(vertices*sizeof(AdjList));
    for(int i=0;i<vertices;i++) {
        g->arrhead[i].head = NULL;
    }

    for(int i=0;i<vertices;i++) {
        AddEdgeInGraph(g,i%vertices,(i+1)%vertices);
    }

    uniform_int_distribution<int> distribute(0,vertices-1);
    for(int i=0;i<vertices;i++) {
        for(int j=0;j<2;j++) {
            int check = 0;
            int x = distribute(seed);
            Node* temp = g->arrhead[i].head;
            while(temp != NULL) {
                if(i == x || temp->index == x) {
                    check = 1;
                    break;
                }
                temp = temp->next;
            }
            if(check ==0) {
                AddEdgeInGraph(g,i,x);
            }
            else {
                j--;
                continue;
            }
        }
    }
    return g;
}

void PrintGraphList(Graph* g) {
    for(int i=0;i<g->vertices;i++) {
        Node* temp = g->arrhead[i].head;
        cout << i << ": ";
        while(temp) {
            cout << temp->index << "(" << temp->weight << ")," ;
            temp = temp->next;
        }
        cout << endl;
    }
}

void PrintGraphEdges(Graph* g) {
    Edge* e = g->edgehead;
    while(e != NULL) {
        cout << e->s << "<--" << e->weight << "-->" << e->d << endl;
        e=e->nextEdge;
    }
}

void SparseGraph2File(Graph* g) {
	int i;
	ofstream file1;
	file1.open("SparseGraph.txt",ios::trunc);
	for(i=0;i<g->vertices;i++) {
		struct Node* temp = g->arrhead[i].head;
		file1<< i << ":" ;
		while(temp!=NULL) {
			file1<< temp->index <<"(" << temp->weight << "),";
			temp=temp->next;
		}
		file1 <<endl;
	}
	file1.close();
}

void DenseGraph2File(Graph* g) {
	int i;
	ofstream file1;
	file1.open("DenseGraph.txt",ios::trunc);
	for(i=0;i<g->vertices;i++) {
		struct Node* temp = g->arrhead[i].head;
		file1<< i << ":" ;
		while(temp!=NULL) {
			file1<< temp->index <<"(" << temp->weight << "),";
			temp=temp->next;
		}
		file1 <<endl;
	}
	file1.close();
}