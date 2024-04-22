//LIST OF THINGS: IS GLLNODE() IMPLEMENTED RIGHT? Maybe it should be a struct??
#ifndef GLL_H //Guard Headers
#define GLL_H

#include <iostream>
using namespace std;

template <typename T> class GLLNode { //Create a templated class for the GLL nodes
 public:
  T data; //data of type T (T being whatever is given due to template)
  GLLNode<T> *prev;
  GLLNode<T> *next; //next and previous linked list pointers

  GLLNode() { //Default Constructor for GLLNode
    data = T(); //Data of the GLL Node (Can't set to any default value because we do not know it's type due to template 
    prev = nullptr; //Pointer to the previous GLLNode set to null 
    next = nullptr; //Pointer to the next GLLNode set to null 
  }

  GLLNode(const T& inData){ //Parameter constructor 
    data = inData;
    prev = nullptr;
    next = nullptr;
  }
};

template <typename T> class GLL { //Create a templated class for the GLL
 private: //Intialize head and tail pointers
  
  GLLNode<T> *head;
  GLLNode<T> *tail;
  GLLNode<T> *Gptr = nullptr;
  
 public:
  GLL(){ //default constructor for GLL
    head = nullptr; //Set pointers to null
    tail = nullptr;
  }

  ~GLL(){ //destructor
    flush();
  }
  
  bool isEmpty(); //Returns true if the GLL is empty, false if it is not empty

  bool flush(); //Empties out the GLL by deleting all of its elements. Basically does what the destructor should do, but allows it to be called from the public interface

  bool prepend(const T &Data); //Adds a copy of the item passed as a parameter to the front of the list, Returns false if the item cannot be added to the list

  bool append(const T &Data); //Adds a copy of the item passed as a parameter to the back of the list  Returns false if the item cannot be added to the list.

  bool merge(GLL &other); //Adds the values of the GLL passed (by reference) as a parameter, to the end of the list, leaving "other" empty. Returns true. If an object is merged into itself, then the function should not take any action. 

  GLL &operator+=(const GLL &other); //Adds copies of the values of the GLL passed (by reference) as a parameter, to the end of the list, leaving "other" intact.
                                     //Returns a reference to the current object (i.e. the object that is called... use "return *this;").
                                     //Calling "list += list;" cannot both add the list to the left hand side and leave that same list in tact,
                                     //so this operation should instead leave list unchanged. You may simply implement this as "if (this == &other) return *this;"

  GLL &operator-=(const GLL &other); //Removes all values that are contained in other, from the list that is called, leaving other intact. Returns a reference to the current object (i.e. the object that is called).
                                    //Passing an object to its own -= operator should not change the object (because it cannot simultaneously remove elements from the list and leave that same list intact.)

  int purgeGoofy(); //Removes all the items from the GLL that are goofy, leaving only non-goofy items. Returns a count of the number of items that were removed.

  int keepGoofy(); //Removes all the items from the GLL that are not goofy, leaving only goofy items. Returns a count of the number of items that were removed.

  bool demoteGoofy(); //Moves all goofy items (if any) to the back of the list, so that the list contains all of its non-goofy items first, then it's goofy items.

  bool reset(); //Sets a "pointer" within the object to the first node of the linked list. This operation returns true if the list is non-empty, and false otherwise.

  bool finished(); //Returns true if there are "no more" items to go through in the list, false if there are more items.

  T proceed(); //Returns a copy of the "next" object from the linked list. So a call to reset() followed by a call to proceed() returns a copy of the first element of a (non-empty) GLL.
               //Subsequent calls to proceed() return the subsequent items in the list.
               //When it becomes true that the last item was returned on the previous call to proceed(), and no subsequent "reset()" is performed, then proceed() should return an item created with its default constructor.

};

  
  



#include "GLL.cpp" //"copies" GLL.cpp into .h file
  
#endif
