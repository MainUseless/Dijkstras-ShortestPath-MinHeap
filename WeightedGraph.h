#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H

#include <cctype>
#include <fstream>
#include <iomanip>
#include "MinHeap.h"

class WeightedGraph 
{ 
    int** g; 
    int nVertices;
    //used to get convert from char to corrisponding index 
    int toIndex(char c){
        c=tolower(c);
        return static_cast<int>(c)-static_cast<int>('a');
    }
    //used to convert index to corrisponding char
    char toChar(int index){
        return 'a'+index;
    }
public:
    //returns the number of vertices
    int getNVertices(){return nVertices;};
    //returns weight of the edge connecting the given vertices 
    int getWeight(char ch1,char ch2){
        int i=toIndex(ch1);
        int j=toIndex(ch2);
        return g[i][j];
    };
    // returns the indices of the neighbors of the vertex v as an int array
    int* returnNeighbors(int v){
        int* arr=new int[numNeighbors(v)];
        for(int i=0,k=0;i<nVertices;i++){
            if(g[v][i]!=0){
                arr[k++]=i;
            }
        }
        return arr;
    };
    //returns the number of neighbors of the vertex v 
    int numNeighbors(int v){
        int count=0;
        for(int i=0;i<nVertices;i++){
            if(g[v][i]!=0)
                count++;
        }
        return count;
    };
    //allocates the adjacency matrix & initializes edge weights from the specified file 
    void loadGraphFromFile(std::ifstream& obj){
        obj>>nVertices;

        g=new int*[nVertices];
        for(int i=0 ; i<nVertices ; i++){
            g[i]=new int[nVertices]{0};
        }

        int NOE;
        obj>>NOE;
        for(int i=0 ; i<NOE ; i++){
            int x,y,weight;
            char temp;
            obj>>temp;
            x=toIndex(temp);
            obj>>temp;
            y=toIndex(temp);
            obj>>weight;
            g[x][y]=weight;
            //for undirected graph
            //g[y][x]=weight;
        }
    };
    //find the shortest path from the start vertex to all other vertices,
    //by filling the prev array and the distances array
    void dijkstra(char startVertex, char* prev, Node distances[]){
        MinHeap m;
        //~=infinity
        int x=98765;
        //initialize the distances array with labels and costs(infinity)
        for(int i=0 ; i<nVertices ; i++){
            distances[i].cost=x;
            distances[i].label=toChar(i);
        };

        //sets start vertex cost to 0 and builds heap
        distances[toIndex(startVertex)].cost=0;
        prev[toIndex(startVertex)]=startVertex;
        m.buildMinHeap(distances,nVertices);

        while(m.getSize()>0){
            //the min node in heap
            Node minNode = m.extractMin();

            //number of neighbours and neighbours array of min node
            int NON=numNeighbors(toIndex(minNode.label));
            int*nNodes=returnNeighbors(toIndex(minNode.label));

            for(int i=0;i<NON;i++){
                //new weight (accumilated)
                int weight=getWeight(minNode.label,toChar(nNodes[i]))+minNode.cost;

                //if in heap and weight in heap is > new weight
                if(m.inHeap(toChar(nNodes[i])) && weight<distances[nNodes[i]].cost){
                    m.decreaseKey(toChar(nNodes[i]),weight);
                    distances[nNodes[i]].cost=weight;
                    prev[nNodes[i]]=minNode.label;
                }
            }
        }
    };
    //just prints the 2d array / matrix for testing
    void print(){
        for(int i=0 ; i<nVertices ; i++){
            for(int j=0 ; j<nVertices ; j++)
                std::cout<<std::setw(4)<<g[i][j]<<" ";
            std::cout<<"\n";
        }
    }
};

#endif