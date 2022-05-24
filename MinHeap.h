#ifndef MINHEAD_H
#define MINHEAD_H

#include<iostream>

struct Node 
{ 
    char label; 
    int cost;
    Node(){};
}; 

//template<class T>
class MinHeap
{
    Node* heap; //an array of nodes
    int _size; //size of array
    //swaps 2 nodes
    void swap(Node& n1 , Node& n2){
        Node temp = n1;
        n1=n2;
        n2=temp;
    };
public:
    //returns & removes the node with minimum cost
    Node extractMin(){
        Node temp = heap[0];
        heap[0]=heap[--_size];
        minHeapify(0,_size);
        return temp;
    };
    // allocates array then builds a min-heap from anarray of struct Node with the given size
    void buildMinHeap(Node arr[] ,int size){
        _size=size;
        heap=new Node[size];
        for(int i=0 ; i<_size ; i++){
            heap[i]=arr[i];
        }
        for(int i=_size/2-1 ; i>=0; i--){
            minHeapify(i,_size);
        }
    };
    //restores the min-heap property for the “heap” array using the given index and size n
    void minHeapify(int i, int n){
        int smallest=i;
        int l=left(i);
        int r=right(i);

        if(l<n && heap[smallest].cost>heap[l].cost)
            smallest=l;

        if(r<n && heap[smallest].cost>heap[r].cost)
            smallest=r;

        if(smallest!=i){
            swap(heap[smallest],heap[i]);
            minHeapify(smallest,n);
        }
    }
    //decreases the node that has the givenlabel to newCost
    void decreaseKey(char label,int newCost){
        if(!inHeap(label))
            return;
        for(int i=0 ; i<_size ; i++){
            if(heap[i].label==label&&heap[i].cost>newCost){
                heap[i].cost=newCost;
                while(i>0&&heap[i].cost<heap[parent(i)].cost){
                    swap(heap[i],heap[parent(i)]);
                    i=parent(i);
                }
                break;
            }
        }
    };
    //returns the index of the parent of i
    int parent(int i){return (i-1)/2;};
    //returns the index of left child of i
    int left(int i){return i*2+1;};
    //returns the index of right child of i
    int right(int i){return i*2+2;};
    //returns size of the heap
    int getSize(){return _size;};
    //checks if the node with the given label is in the heap
    bool inHeap(char target){
        for(int i=0 ; i<_size ; i++){
            if(heap[i].label==target);
                return true;
        }
        return false ;
    };
    //printing heap
    void print(){
        for(int i=0;i<_size;i++)
            std::cout<<heap[i].cost<<" ";
        std::cout<<'\n'; 
    };
};

#endif