//ALGO2 IS1 223A LAB08
//Vladyslav Zosimchuk
//zv53855@zut.edu.pl

#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <algorithm>

template<typename T>
struct DynamicArray {
    T* arr;
    int size;
    int capacity;

    DynamicArray() : arr(new T[2]()), size(0), capacity(2) {}
    ~DynamicArray() {
        delete[] arr;
    }
};

int findCalls{};

struct Edge {
    int idSrc, idDest;
    float weight;
};

struct Vertex {
    float x, y;
};

struct UnionFind {
    int *parent, *rank;

    explicit UnionFind(const int n) : parent(new int[n]), rank(new int[n]()) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    ~UnionFind() {
        delete[] parent;
        delete[] rank;
    };

    int find(int i) {
        findCalls += 1;
        // path-compression
        if (parent[i] == i) {
            return i;
        }
        int root = find(parent[i]);
        if (root != parent[i]) {
            parent[i] = root;
        }
        return root;

        // no path compression
        // if (i == parent[i]) {
        //     return i;
        // }
        // i = find(parent[i]);
    }

    void unionSets(int i, int j) {
        if ( (i = find(i)) == (j = find(j)) ) {
            return;
        }
        // union-rank
        if (rank[j] > rank[i]) {
            parent[i] = j;
        } else if (rank[i] > rank[j]) {
            parent[j] = i;
        } else if (rank[i] == rank[j]) {
            parent[j] = i;
            ++rank[j];
        }
        // no union-rank
        // parent[i] = j;
    }
};

class Graph {
    DynamicArray<Edge>* edges;
    DynamicArray<Vertex>* vertices;

public:
    Graph() : edges(new DynamicArray<Edge>()), vertices(new DynamicArray<Vertex>()) {}
    ~Graph() {
        delete edges;
        delete vertices;
    }
    int getNumberOfVertices() const;
    const DynamicArray<Edge>* getEdges() const;
    const DynamicArray<Vertex>* getVertices() const;
    void addEdge(int, int, float) const;
    void addVertex(float, float) const;
    void readFile(const std::string&) const;
    Edge* kruskal();
};

void heapSort(Edge*& array, int size);
void bucketSort(DynamicArray<Edge>*&);

int main() {
    std::cout << "g1" << std::endl;
    Graph* input1 = new Graph();
    input1->readFile("/home/marling/Documents/college-CS/semester-3/Algorithms 2/Kruskals_Algoirithm/g1.txt");
    const Edge* MST1 = input1->kruskal();
    delete input1;
    delete[] MST1;

    std::cout << std::endl << "g2" << std::endl;
    Graph* input2 = new Graph();
    input2->readFile("/home/marling/Documents/college-CS/semester-3/Algorithms 2/Kruskals_Algoirithm/g2.txt");
    const Edge* MST2 = input2->kruskal();
    delete input2;
    delete[] MST2;

    std::cout << std::endl << "g3" << std::endl;
    Graph* input3 = new Graph();
    input3->readFile("/home/marling/Documents/college-CS/semester-3/Algorithms 2/Kruskals_Algoirithm/g3.txt");
    const Edge* MST3 = input3->kruskal();
    delete input3;
    delete[] MST3;

    return 0;
}

int Graph::getNumberOfVertices() const {
    return vertices->size;
}

const DynamicArray<Edge>* Graph::getEdges() const {
    return edges;
}

const DynamicArray<Vertex>* Graph::getVertices() const {
    return vertices;
}

void Graph::addEdge(int idSrc, int idDest, float weight) const {
    if (edges->size == edges->capacity) {
        edges->capacity *= 2;
        Edge* newArr = new Edge[edges->capacity]();
        std::copy_n(edges->arr, edges->size, newArr);
        delete[] edges->arr;
        edges->arr = newArr;
    }
    const Edge e = {idSrc, idDest, weight};
    edges->arr[edges->size++] = e;
}

void Graph::addVertex(float x, float y) const {
    if (vertices->size == vertices->capacity) {
        vertices->capacity *= 2;
        Vertex* newArr = new Vertex[vertices->capacity]();
        std::copy_n(vertices->arr, vertices->size, newArr);
        delete[] vertices->arr;
        vertices->arr = newArr;
    }
    const Vertex v = {x, y};
    vertices->arr[vertices->size++] = v;
}

Edge* Graph::kruskal() {
    UnionFind* uf = new UnionFind(edges->size);
    Edge* result = new Edge[vertices->size - 1]();
    clock_t temp;
    temp = clock();
    bucketSort(edges);
    clock_t sortingTime = clock() - temp;
    float totalWeight{};
    temp = clock();
    for (int eMST = 0, eGraph = 0; eMST < vertices->size - 1, eGraph < edges->size; ++eGraph) {
        Edge next_edge = edges->arr[eGraph];
        int x = uf->find(next_edge.idSrc);
        int y = uf->find(next_edge.idDest);
        if (x != y) {
            result[eMST++] = next_edge;
            totalWeight += next_edge.weight;
            uf->unionSets(x, y);
        }
    }
    clock_t loopTime = clock() - temp;

    std::cout << "The number of edges is: " << vertices->size - 1 << ", the total weight is " << totalWeight << std::endl;
    std::cout << "It took " << sortingTime << " CPU clock ticks to sort all edges of the graph" << std::endl;
    std::cout << "It took " << loopTime << " CPU clock ticks to run the main loop of the algorithm" << std::endl;
    std::cout << "There were " << findCalls << " calls of find function" << std::endl;
    delete uf;
    findCalls = 0;
    return result;
}

void Graph::readFile(const std::string& name) const {
    std::ifstream myFile(name);
    if (myFile.is_open()) {
        int numVertices, numEdges;
        float x, y, weight;
        int idSrc, idDest;
        myFile >> numVertices;
        for(int i = 0; i < numVertices; ++i) {
            myFile >> x >> y;
            addVertex(x, y);
        }
        myFile >> numEdges;
        for (int i = 0; i < numEdges; ++i) {
            myFile >> idSrc >> idDest >> weight;
            addEdge(idSrc, idDest, weight);
        }
        myFile.close();
    } else {
        std::cout << "Unable to open file!" << std::endl;
        exit(1);
    }
}

void bucketSort(DynamicArray<Edge>*& edges) {
    int numBuckets = edges->size / 10;
    Edge** buckets = new Edge*[numBuckets]();
    int* bucketSizes = new int[numBuckets]();
    float max = edges->arr[0].weight;
    for (int i = 1; i < edges->size; ++i) {
        max = std::max(edges->arr[i].weight, max);
    }
    for (int i = 0; i < edges->size; ++i) {
        const unsigned int index = numBuckets * edges->arr[i].weight / (max + 1);
        buckets[index] = static_cast<Edge*>(realloc(buckets[index], (bucketSizes[index] + 1) * sizeof(Edge)));
        buckets[index][bucketSizes[index]++] = edges->arr[i];
    }
    int index = 0;
    for (int i = 0; i < numBuckets; ++i) {
        if (bucketSizes[i] > 0) {
            heapSort(buckets[i], bucketSizes[i]);
            for (int j = 0; j < bucketSizes[i]; ++j) {
                edges->arr[index++] = buckets[i][j];
            }
        }
        free(buckets[i]);
    }
    delete[] buckets;
    delete[] bucketSizes;
}

void heapSort(Edge*& array, int size) {
    for (int i = 1; i < size; ++i) {
        int j = i;
        while (j > 0) {
            int parentIndex = (j - 1) / 2;
            if (array[j].weight > array[parentIndex].weight) {
                std::swap(array[j], array[parentIndex]);
                j = parentIndex;
            } else {
                break;
            }
        }
    }
    for (int i = size - 1; i > 0; --i) {
        std::swap(array[0], array[i]);
        int j = 0;
        int leftChild = 1;
        while (leftChild < i) {
            int rightChild = 2 * j + 2;
            if (rightChild < i && array[rightChild].weight > array[leftChild].weight) {
                leftChild = rightChild;
            }
            if (array[j].weight > array[leftChild].weight) {
                break;
            }
            std::swap(array[j], array[leftChild]);
            j = leftChild;
            leftChild = 2 * j + 1;
        }
    }
}
