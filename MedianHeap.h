//File: MedianHeap.h 
//Author: Varisara Muangrat
#ifndef MEDIANHEAP_H
#define MEDIANHEAP_H

#include <iostream>
#include <stdexcept>
#include <cmath>
using namespace std;
template<class T> 
class MedianHeap;
template <class T> 
class Heap{
  public: 
  friend class MedianHeap<T>; 
    Heap(int cap,bool (*compare)(const T&,const T&));
    Heap(const Heap<T>& otherH);
    ~Heap();
    const Heap<T>&operator=(const Heap<T>& rhs);
    int getSize(); 
    int getCapacity();
    void insert(const T& item);
    void bubbleUp(int i);  
    T deleteMin();
    void bubbleDown(int index);
    T getLeftChild(int index);
    T getRightChild(int index);
    void dumpHeap();
    T minItem;   //smallest item in the Heap 
    T maxItem;   //largest item in the Heap 

  private:
   bool (*compare) (const T&, const T&); 
   int m_size; 
   int m_capacity;
   T * m_heapArr;
};

template <class T> 
class MedianHeap{
  public: 
    MedianHeap( bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap=100 );
    MedianHeap(const MedianHeap<T>& otherH);
    ~MedianHeap();
    const MedianHeap<T>& operator=(const MedianHeap<T>& rhs);
    int size();
    int capacity();
    void insert(const T& item);
    bool deleteItem();
    T getMedian();
    T getMin();
    T getMax(); 
    void dump();
    int maxHeapSize();
    int minHeapSize();
    T locateInMaxHeap(int pos);
    T locateInMinHeap(int pos);
    bool (*lt) (const T&, const T&);
    bool (*gt) (const T&, const T&);
    bool (*equalTo) (const T&, const T&);
    void rebalance(); //?
  private:
    Heap<T> *minHeap;  //heap objects 
    Heap<T> *maxHeap;
    int m_size; 
    int m_capacity;
    T m_min; //smallest item in medianHeap
    T m_max;
    T m_median;
    T m_maxItem;
    T m_minItem;

}; // end of median heap class

//GENERIC HEAP CLASS IMPLEMENTATION 
template <typename T>
Heap<T>::Heap(int cap, bool (*compareF) (const T&, const T&)){
  //dynamically allocate heap array
  m_heapArr = new T[cap];
  
  m_capacity = cap; 
  m_size = 0; 
  //function ptr 
  compare = compareF; 
}

template <typename T>
 Heap<T>::Heap(const Heap<T>& otherH){
  m_heapArr = new T[otherH.m_capacity];
  //copy elements in heap array 
  for(int i = 0; i < otherH.m_size + 1; i++){
    m_heapArr = otherH.m_heapArr[i];
  }
  m_size = otherH.m_size;
  m_capacity = otherH.m_capacity; 

 }

template <typename T>
Heap<T>::~Heap(){
  //deallocate heap array
  delete m_heapArr;
  m_heapArr = NULL; 
}
template <typename T>
const Heap<T>& Heap<T>::operator=(const Heap<T>& rhs){
  //default
}

template <typename T>
int Heap<T>::getSize(){
  return m_size;
}

template <typename T>
int Heap<T>::getCapacity()
{
  return m_capacity;
}
template <typename T>
T Heap<T>::getLeftChild(int index){
  return  m_heapArr[(2*index)];
}

template <typename T>
T Heap<T>::getRightChild(int index){ 
  return m_heapArr[(2*index + 1)];
}
/*
template <typename T>
void Heap<T>::bubbleUp(int index){
  int tmp;
      if (index != 1) {  //less than or equal to , inverts the greater than
            if (!compare(m_heapArr[index],m_heapArr[index/2])) { //parent >index 
                  tmp = m_heapArr[index/2];
                  m_heapArr[index/2] = m_heapArr[index];
                  m_heapArr[index] = tmp;
                  bubbleUp(index/2);
            }
      }
}
*/
template <typename T>
void Heap<T>::insert(const T& item){   //passes in an item
  //throw exception if full 
 if(m_size == 0){ //check empty
    m_heapArr[1] = item;
    m_size++;
 }
 
  if(m_size == m_capacity){ 
    throw out_of_range ("this heap is full");
  }
  //insert at last index 
  m_heapArr[m_size + 1] = item; 
  m_size++;
  //bubble up 
  bubbleUp(m_size);

}
template <typename T>
void Heap<T>::bubbleUp(int i){ 
  T temp;
  for( ; i > 1 && compare(m_heapArr[i],m_heapArr[ i / 2 ]); i /= 2 ) //compare with parent 
  {
     // swap, from child to parent
     temp = m_heapArr[i]; 
     m_heapArr[ i ] = m_heapArr[ i / 2 ];
     m_heapArr[i/2] = temp; 
  }
}

template <typename T>
T Heap<T>::deleteMin(){ //deletes minimum from the heap 
   T temp = m_heapArr[1];
  if(m_size == 0){ 
    throw out_of_range ("heap is empty");
  }else{
    //new root  
    m_heapArr[1] = m_heapArr[m_size - 1]; 
    m_size--; 
    bubbleDown(1); //doesn't use 0,start at 1 
  }
  return temp;
}
template <typename T>
void Heap<T>::bubbleDown(int index){ 
  int leftChild; //indicies 
  int rightChild; 
  int root; 
  int tmp;
      
  leftChild = getLeftChild(index);
  rightChild = getRightChild(index);
      if (rightChild > m_size) {
            if (leftChild > m_size)
                  return;
            else
                  root = leftChild;
      } else {
            if (compare(m_heapArr[leftChild],m_heapArr[rightChild]))
                  root = rightChild;
            else
                  root = leftChild;
      }
      if (compare(m_heapArr[index], m_heapArr[root])) {
            tmp = m_heapArr[root];
            m_heapArr[root] = m_heapArr[index];
            m_heapArr[index] = tmp;
            bubbleDown(root);
      }
}

template <typename T> //eh
void Heap<T>::dumpHeap(){ //print out array
  for(int i=1;i< m_capacity;i++){
    cout << m_heapArr[i]<< endl;
  }
}
//end of g heap  
//MEDIAN HEAP -------------------

template <typename T>
MedianHeap<T>::MedianHeap(bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap){
  minHeap = new Heap<T>((cap/2 + 1), gt); 
  maxHeap = new Heap<T>((cap/2 + 1), lt); 

   m_capacity = cap;
   m_size = 0;

   this->lt = lt;
   this->gt = gt; 


}
template <typename T>
MedianHeap<T>::MedianHeap(const MedianHeap<T>& otherH){
  //copy over each element in minHeap array
  for(int i = 1; i <= minHeap.m_size; i++){
    minHeap->m_heapArr[i] = otherH.minHeap->m_heapArr[i];
  }
  for(int i = 1; i <= maxHeap.m_size; i++){
    maxHeap->m_heapArr[i] = otherH.maxHeap->m_heapArr[i];
  }
  m_capacity = otherH.m_capacity;
  m_size = otherH.m_size;
  m_min  = otherH.m_min;
  m_median = otherH.m_median;
  m_max = otherH.m_maxItem;

}
template <typename T>
   const MedianHeap<T>& MedianHeap<T>::operator=(const MedianHeap<T>& rhs){
    
    delete minHeap; 
    delete maxHeap;
    minHeap = NULL; 
    maxHeap = NULL; 
    minHeap = new Heap<T>(*rhs.minHeap);
    maxHeap = new Heap<T>(*rhs.maxHeap);
      //member variables 
    m_capacity= rhs.m_capacity;
    m_size = rhs.m_size; 
    m_minItem = rhs.m_minItem;
    m_maxItem = rhs.maxItem;
    m_median = rhs.m_median; 

    //}
} 

template <typename T>
   MedianHeap<T>::~MedianHeap(){
     
     delete maxHeap; 
     delete minHeap; 
     
   }

template <typename T>
int MedianHeap<T>::size(){
  return m_size;
}
template <typename T>
int MedianHeap<T>::capacity(){
  return m_capacity;
}

template <typename T>
void MedianHeap<T>::insert(const T& item) {
  if(m_size > m_capacity){
    throw out_of_range("this heap is full");
  }
  if(m_size == 0){
    minHeap->insert(item);
    m_min = item; 
    m_max = item;  
    m_size++; 
    m_median = item; 
    return;
  }

  //use lt() gt() to update and check items before inserting 
  if(lt(item,m_min)){
    m_min = item; 
  }
  if(gt(item,m_max)){
    m_max = item;
  }
  //insert to heap objects
  if(lt(item, minHeap->m_heapArr[1])){ //compare with very first thing in min  
    maxHeap->insert(item);
    m_size++;
     if(maxHeap->m_size - minHeap->m_size > 1 ) { 
        T temp = maxHeap->deleteMin();
        minHeap->insert(temp);
  }

  }else if(gt(item,maxHeap->m_heapArr[1])){  //m_median
    minHeap->insert(item);
    m_size++;
     }else if(minHeap->m_size - maxHeap->m_size > 1 ) { 
        T temp = minHeap->deleteMin();
        maxHeap->insert(temp);
   }
    
    //if theyre equal select a root, and update the median in all the cases , 
    //its going to be te root in all three cases 
  //check sizes check for rebalancing
 
   //else if(abs(m_min->size == m-m_max->m_size)) > 1){
        
   }
   
  template <typename T>
   T MedianHeap<T>::getMedian(){
     if(maxHeap->getSize() > minHeap->getSize()){
      return maxHeap->m_heapArr[1];  
     }
     if(minHeap->getSize() > minHeap->getSize()){
      return minHeap->m_heapArr[1];  
     }
   }

   template <typename T>
   T MedianHeap<T>::getMin(){}
   
   template <typename T>
   T MedianHeap<T>::locateInMinHeap(int pos){
     return minHeap->m_heapArr[pos];
   }
   template <typename T>
   T MedianHeap<T>::locateInMaxHeap(int pos) {
     return maxHeap->m_heapArr[pos];
   }
   template <typename T>
   int MedianHeap<T>::maxHeapSize(){
     return maxHeap->m_size;
   }

   template <typename T>
   int MedianHeap<T>::minHeapSize(){
     return minHeap->m_size;
   }
   
   //template <typename T>
   //bool MedianHeap<T>::deleteItem(T& givenItem, bool (*equalTo) (const T&, const T&) ) }{
    // this->equalTo; 
     //for(int i = 0; i < maxHeap->m_size; i++){
      // if (equal(givenItem,maxHeap->m_heapArr[index])){
      //   maxHeap->m_heapArr[index] = givenItem;
       //  maxHeap->m_heapArr[index -1];
      //}
   // }
  // }

   template <typename T>
   T MedianHeap<T>::getMax(){}
   
   template <typename T>
   void MedianHeap<T>::dump(){
     cout << "... MedianHeap::dump() ..." << endl; 
     cout << "------------Max Heap------------ "<<endl; 
     cout << "size= "<< m_size << " ,capacity = " << m_capacity;
     for(int i = 1; i <= maxHeap->getSize(); i++){
       cout << "Heap[" << i << "] = (" << maxHeap->m_heapArr[i]<< ")"<<endl; 
     } 
     cout << "------------Min Heap------------"<<endl; 
     cout << "size ="<< m_size << " ,capacity = " << m_capacity; 
     for(int i = 1; i <= maxHeap->getSize(); i++){
       cout << "Heap[" << i << "] = (" << minHeap->m_heapArr[i]<<")"<<endl; 
     } 
     cout << "--------------------------------" << endl;
     cout << "min = " << m_min; 
     cout << "median = "<< m_median;
     cout << "max = " << m_max; 
   }

#endif

