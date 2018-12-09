//File: p4.h 

#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H

//class declarations 
template <class T>
class MinMaxHeap;

template <class T> //wrapper class 
class MinMaxHeap{
public:
    MinMaxHeap(int capacity);
    MinMaxHeap(const MinMaxHeap<T>& other);
    ~MinMaxHeap();
    operator=(const MinMaxHeap<T>& rhs);
    int size();
    void insert(const T& data);
    T deleteMin();
    T deleteMax();
    void dump(); 
    void locateMin(int pos, T& data, int& index);
    void locateMax(int pos, T& data, int& index);
    //function pointers
    bool (*lessthan)(const T&,const T&);
    bool (*greater)(const T&,const T&); 
    bool (*equalTo)(const T&,const T&);
private: 
    MinMaxHeap *minH;
    MinMaxHeap *maxH;  
    int m_cap;  //capacity 
    int m_size;  
    }

//generic heap class that maintains the heap 
template <class T> 
class Heap{ 
public: 
    void bubbleUp(); 
    void trickleDown(); 
private: 
    int m_hSize; 
    int m_hCap; 
}
#include "MinMaxHeap.cpp"
#endif