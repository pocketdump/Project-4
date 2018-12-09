//File: MedianHeap.h 
//Author: Varisara Muangrat
#ifndef MEDIAN_HEAP
#define MEDIAN_HEAP

#include <iostream>
#include <stdexcept>
using namespace std;

    Heap( bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap=100 );
    Heap(const MedianHeap<T>& otherH);
    ~Heap();
    const MedianHeap<T>& MedianHeap<T>::operator=(const MedianHeap<T>& rhs);
    size();
    capacity();
    insert(const T& item);
    deleteMin();
    bubbleDown(); 
    getLeftChild();
    getRightChild();
    dumpHeap();
    T * m_heapArr;
    T minItem; 
    T maxItem; 
    bool (*compare) (const T&, const T&);

//Median Heap Stuff 
    MedianHeap( bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap=100 );
    MedianHeap(const MedianHeap<T>& otherH);
    ~MedianHeap();
    const MedianHeap<T>& MedianHeap<T>::operator=(const MedianHeap<T>& rhs);
    size();
    capacity();
    insert(const T& item);
    deleteMin();
    bubbleDown():
    getMedian();
    getMin();
    getMax(); 
    dump();
    maxHeapSize();
    minHeapSize();
    locateInMaxHeap(int pos);
    locateInMinHeap(int pos);
    rebalance(); //?

