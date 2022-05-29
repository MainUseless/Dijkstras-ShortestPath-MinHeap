#include<iostream>
#include"WeightedGraph.h"

//Mostafa Hesham Allam 20206126 s1
//Karim Amr Hamdy lialy 20206138 s1

using namespace std;

int main(){
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