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
    //just used to get convert from char to index 
    int toIndex(char c){
        c=tolower(c);
        return static_cast<int>(c)-static_cast<int>('a');
    }
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
        for(int i=0,j=0;i<nVertices;i++){
            if(g[v][i]!=0){
                arr[j]=i;
                j++;
            }
        }
        return arr;
    };
    //returns the number of neighbors of the vertex v 
    int numNeighbors(int v){
        int count;
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
            g[y][x]=weight;
        }
    };
    //find the shortest path from the start vertex to all other vertices,
    //by filling the prev array and the distances array
    void dijkstra(char startVertex, char* prev, Node distances[]){
        MinHeap m ;
        int x=10000;
        for(int i=0 ; i<nVertices ; i++){
            distances[i].cost=x;
            distances[i].label=toChar(i);
        };
        distances[toIndex(startVertex)].cost=0;
        m.buildMinHeap(distances,nVertices);
        while(m.getSize()>0){
            Node tempNode = m.extractMin();
            char tempLabel = tempNode.label;
            int nn=numNeighbors(tempLabel);
            int*arr=returnNeighbors(toIndex(tempLabel));
            for(int i=0;i<nn;i++){
                if(arr[i])
        }

    };
    //just prints the 2d array / matrix
    void print(){
        for(int i=0 ; i<nVertices ; i++){
            for(int j=0 ; j<nVertices ; j++)
                std::cout<<std::setw(4)<<g[i][j]<<" ";
            std::cout<<"\n";
        }
    }
};


#endif