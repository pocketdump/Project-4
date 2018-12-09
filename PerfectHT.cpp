//Find Prime
// File: PerfectHT.cpp
//
// UMBC CMSC 341 Fall 2017 Project 5
//
// Implementation of HashFunction, SecondaryHT & PerfectHT classes.
//
// Version: 2017-11-30
//

#include <stdexcept>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <math.h>

using namespace std ;

#include "PerfectHT.h"
#include "primes.h"


// =====================================================================
// HashFunction class implementation
// =====================================================================


// By default do not print info to screen
//
bool HashFunction::m_debug = false ;


// Constructor.
// The constructor picks the smallest prime # greater than
// or equal to n for the table size.
// Default value of n defined in header.
//
// Initializes other hash function parameters randomly.
//
HashFunction::HashFunction(int n /* =100*/ ) {

   // note: maxPrime defined in prime.h
   //
   if (n > maxPrime) throw out_of_range("HashTable size too big.\n") ;

   m_tsize = findPrime(n) ;
   m_factor = ( rand() % (m_tsize - 1) ) + 1 ;
   m_shift =  rand() % m_tsize ;
   m_multiplier = 33 ;  // magic number from textbook
   m_reboots = 0 ;

}


// Function that maps string to unsigned int.
// Return value can be much larger than table size.
// Uses m_multiplier data member.
// Return value must be unsgined for overflow to work correctly.
//
unsigned int HashFunction::hashCode(const char *str) const {

   unsigned int val = 0 ;

   int i = 0 ;
   while (str[i] != '\0') {
      val = val * m_multiplier + str[i] ;
      i++ ;
   }
   return val ;
}


// Getter for table size
//
int HashFunction::tableSize() const {
   return m_tsize ;
}


// Overloaded () operator that makes this a "functor" class.
// Returns the slot in the hash table for str.
// Uses the MAD method: h(x) = (ax + b) % m where
// the parameters are:
//   a = m_factor
//   b = m_shift
//   m = m_tsize
//
unsigned int HashFunction::operator() (const char *str) const {
   return ( m_factor * hashCode(str) + m_shift ) % m_tsize ;
}


// Pick new parameters for MAD method and the hashCode function.
// Note: can change table size.
//
void  HashFunction::reboot() {

   // Implement the reboot function
   // pick new values for m_factor and m_shift each reboot
   //   make sure you get *different* values
   // change m_multiplier to next odd number  every 3rd reboot
   // increase table size to next prime # every 5th reboot
   int count = 0;
   //pick new values
   int tempShift = rand() % 1+ m_tsize-1;
   int tempfactor = rand()%1 + m_tsize-1;
   int newTemp;
   int newTable;

   //check table size first
   if(count% 5 == 0){ //every 5th reboot; increase tablesize to next prime #
        int newTable = findPrime(m_tsize); //generate a new prime number for t_size
        if(newTable == m_tsize){
            findPrime(newTable); //regenerate size for m_table
        }else if(newTable != m_tsize){
            m_tsize = newTable;    //if it's a new table size, replace
        }
     }else if(count% 3 == 0){ //every 3rd reboot change multiplier
        newTemp = rand()%1 + m_tsize-1;
        m_multiplier = m_multiplier + 2;
        if(newTemp != tempfactor){
            m_factor = tempfactor;
        }
    //regenerate a if it is equal, or same result
    if(tempShift == m_shift && tempfactor == m_factor){
        tempShift = rand() % 1+ m_tsize-1;
        tempfactor = rand()%1 + m_tsize-1;
    }
    else if(tempShift != m_shift && tempfactor != m_factor){
       count++;
       m_shift = tempShift;
    }                              //parameter question: array of characters

   //if flag (boolean m_debug is true then print all values) only when debug mode is true
   //if something = hash(string)
   if(m_debug == true){
       for(int i = 0;i < m_reboots;m_reboots++){
           cout <<" ------------------------------------------"<< endl;
           cout <<" Trial #" << m_reboots <<endl;
           cout <<" Table size:"<< m_tsize;
           //number of non-empty slots = 640
           //average number of items in non-empty slots = 1.5625
           //number of slots with collisions = 271
           //maxCollisionsInOneSlot = 4
           cout <<" ------------------------------------------"<< endl;
       }
   }

}
}



// Set random seed for the random number generator.
// Call once at the start of the main program.
// Uses srand() and rand() from cstdlib which is
// shared with other code. For compatibility with
// C++98, it does not have a private random number
// generator (e.g., mt19337).
//
void HashFunction::setSeed(unsigned int seed) {
   srand(seed) ;
}


// Find the smallest prime number greater than or equal to m.
int BinarySearch(int m);
int HashFunction::findPrime(int m) {

   // Prime numbers are in global array primes[]
   // included from "primes.h"
   //
   // Use binary search!!
   int i = m + 1;
   for(;; i++){
        if(BinarySearch(i)!= -1){
            //found prime number
            i = (BinarySearch(i));
            break;
        }
   }
   return i;
}
int BinarySearch(int m){
   int start = 0; //entire range
   int end = numPrimes -1; //last possible range ,from primes.h
   int middle = (end-start)/2;
   while(m != primes[middle]){
        cout << middle<< endl;
    if(primes[middle] == m){
        //found it at index middle
            cout << middle<< "here is middle"<< endl;
            return primes[middle];
            
    }else if(end == start){ //not in array
            return -1;  //did not find it ( interpret this as not found )
    }else if(m > primes[middle]){
        start = middle;
    }else if(m < primes[middle]){
        end = middle;  //narrow down range
    }
        middle = (end-start)/2; //resetting start/end and /2
   }
}


// =====================================================================
// SecondaryHT class implementation
// =====================================================================


// By default do not print debugging info
bool SecondaryHT::m_debug = false ;


// Create a secondary hash table using the char * strings
// stored in "words". Makes copy of each item in words.
//
SecondaryHT::SecondaryHT(vector<const char *> words) {

   //
   // Keep trying until a table with no collisions is found
   //
   // wrap debugging statements in "if (m_debug) { ... }"
   //
   // remember that calling HashFunction::reboot() can change
   // the table size!
   //
   // use strdup to copy char * strings
   //
   int slot;
   //vector<int>tempI(pow(words.size,2)); //temporary vector
   int tempIsize = 0;
   hash = HashFunction(pow(words.size(),2));
   vector<int>tempI(hash.tableSize(),0);
     //initalize hash function  (size of words vector squared)
     //keep track of what indexes are , use the hash function on it
   //if greater than one call reboot
   for(int i = 0; i < words.size(); i++){  //
        slot = hash(words.at(i)); //returns index
        if(tempI[slot] >= 1){
            hash.reboot();
            tempI.assign(hash.tableSize(),0); //reset vecotr, resize if needed
            i = -1;
        }else{
            tempI.at(i)++; 
        
       }
   }
   tempIsize = hash.tableSize(); //set actual dynamica array to this size

   T2 = new char*[tempIsize];
   //loop through words again , call hash function , use strdup and copy words into array 
   for(int i = 0; i < words.size(); i++){  //i < words.size()
       if(m_attempts == maxAttempts){
           throw very_unlucky ("Too many attempts");
       }
       slot = hash(words.at(i)); //get a key
       if(slot == i){
           hash.reboot();
           //T2[i] = strdup(slot);
           //m_attempts++;
       }else{

           T2[hash(words.at(i))] = strdup(words.at(i));
           m_attempts++;
          // free(T2[i]);
       }
   }
}

// Copy constructor. Remember to strdup.
//
SecondaryHT::SecondaryHT(const SecondaryHT& other) {

    T2 = new char *[other.hash.tableSize()];
    m_attempts = other.m_attempts; 
    m_size = other.m_size;
    for(int i = 0; i < hash.tableSize(); i++){
        if(other.T2[i] == NULL){
            T2[i] = NULL;
        }else{
            T2[i] = strdup(other.T2[i]);
        }
    }
}


// Destructor. Use free() to free strings.
//
SecondaryHT::~SecondaryHT() {
     for(int i = 0; i < tableSize(); i++){ //tempIsize
            free(T2[i]);    
            T2[i] = NULL;

     }  
      delete [] T2;
      T2 = NULL;
}



// Assignment operator. Remember to use strdup() and free()
//
const SecondaryHT& SecondaryHT::operator=(const SecondaryHT& rhs) {
    if( this != &rhs){
        return *this;
    }
    m_attempts = rhs.m_attempts;
    m_size = rhs.m_size;   
    //clear T2 
    for(int i = 0; i < hash.tableSize();i++){
        free(T2[i]);
       // T2[i] = NULL;
    }
    T2 = new char*[rhs.hash.tableSize()];
    for(int i = 0; i < hash.tableSize();i++){
        if(rhs.T2[i] == NULL){
            //do nothing
        }else{
            T2[i] = strdup(rhs.T2[i]);
        }
    }
    return *this; 
}


// returns whether given word is in this hash table.
//
bool SecondaryHT::isMember (const char *word) const {

   int slot = hash(word) ;

   assert ( 0 <= slot && slot < hash.tableSize() ) ;

   if (T2[slot] == NULL) return false ;

   if ( strcmp(word, T2[slot]) != 0 ) return false ;

   return true ;
}


// getter. Actually, the hash function has the size.
//
int SecondaryHT::tableSize() const {
   return hash.tableSize() ;
}


// Pretty print for debugging
//
void SecondaryHT::dump() const {
   cout << "=== Secondary Hash Table Dump: ===\n" ;
   cout << "Table size = " << hash.tableSize() << endl ;
   cout << "# of items = " << m_size << endl ;
   cout << "# of attempts = " << m_attempts << endl ;

   for (int i=0 ; i < hash.tableSize() ; i++) {
      cout << "T2[" << i << "] = " ;
      if (T2[i] != NULL) cout << T2[i] ;
      cout << endl ;
   }

   cout << "==================================\n" ;
}



// =====================================================================
// PerfectHT class implementation
// =====================================================================


// by default, do not print debugging info
//
bool PerfectHT::m_debug = false ;


// Create a Perfect Hashing table using the first n strings
// from the words array.
//
PerfectHT::PerfectHT (const char *words[], int n) {

   // Implement constructor for PerfectHT here.
   //
   // You will need an array of vectors of char * strings.
   // Something like;
   //
   //    vector<const char *> *hold = new vector<const char *>[m] ;
   //
   // Each hold[i] is a vector that holds the strings
   // that hashed to slot i. Then hold[i] can be passed
   // to the SecondaryHT constructor.
   //


}


// Copy constructor. Use strdup or SecondaryHT copy constructor.
//
PerfectHT::PerfectHT(const PerfectHT& other) {
}


// Destructor. Remember to use free() for strdup-ed strings.
//
PerfectHT::~PerfectHT() {
}


// Assignment operator. Use strdup() and free() for strings.
//
const PerfectHT& PerfectHT::operator=(const PerfectHT& rhs) {
}


// Returns whether word is stored in this hash table.
//
bool PerfectHT::isMember(const char * str) const {
   int slot = hash(str) ;

   if (PHT1[slot] == NULL && PHT2[slot] == NULL) return false ;

   if (PHT1[slot] != NULL) return strcmp(str,PHT1[slot]) == 0 ;

   return PHT2[slot]->isMember(str) ;
}


// Pretty print for debugging.
//
void PerfectHT::dump() const {
   int m = hash.tableSize() ;

   cout << "------------- PerfectHT::dump()  -------------\n" ;
   cout << "table size = " << hash.tableSize() << endl ;
   cout << endl ;
   for (int j=0 ; j < m ; j++) {
      cout << "[" << j << "]:  " ;
      if (PHT1[j] != NULL) cout << PHT1[j] ;
      if (PHT2[j] != NULL) {
         cout << endl ;
         PHT2[j]->dump() ;
      }
      cout << endl ;
   }

   cout << "----------------------------------------------\n" ;
}
