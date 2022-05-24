#include<iostream>
#include"WeightedGraph.h"

using namespace std;

int main(){
    //MinHeap m;
    // Node arr[]={{'n',10},{'s',3},{'a',56},{'k',22},{'x',11},{'b',20}};
    // m.buildMinHeap(arr,6);
    // m.print();
    // m.decreaseKey('a',2);
    // m.print();
    WeightedGraph wg;
    ifstream infile("graph.txt");
    wg.loadGraphFromFile(infile);
    char* p; 
    p = new char[wg.getNVertices()]; 
    Node* n; 
    n=new Node[wg.getNVertices()];
    wg.dijkstra('g',p,n);
    cout<<endl<<"Node\tCost\tPrevious"; 
    for(int i=0;i<wg.getNVertices();i++) { 
        cout<<endl<<n[i].label<<"\t"<<n[i].cost<<"\t"<<p[i]; 
    } 
    infile.close(); 
    return 0;
};