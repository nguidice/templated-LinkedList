#ifndef GLL_CPP //Guard Headers
#define GLL_CPP

#include <iostream>
#include "goofy.h"


 template <typename T> bool GLL<T>::isEmpty(){ //Returns true if the GLL is empty, false if it is not empty
   if (head == nullptr){ //If head = nullptr then the list if empty
     return true;
   }
     return false; //If not it is not empty
   }
 

template <typename T> bool GLL<T>::flush(){ //Empties out the GLL by deleting all of its elements. Basically does what the destructor should do, but allows it to be called from the public interface
     if (head != nullptr){ //Check to see if trying to defrence nullptr
       
       GLLNode<T>* curr = head; //make temp variable = to head
       
       while (curr != nullptr){ //make sure you do not go out of the bounds of the linked list
	  
	 GLLNode<T>* temp = curr; // set temp = curr so curr can be defrenced without losing the location of the linked list
	 curr = curr->next; // increment thrugh the list
	  
	 delete temp; // delete temp everytime curr moves onto the next element "cleaning up" behind it
	  
	 }
       head = nullptr;
       //tail = nullptr;
       return true; //Return true if list is succsfully flushed
     }
     else{
       
       return false; //Return false if tried to derefrence nullptr
       
   }
}
     
     template <typename T> bool GLL<T>::prepend(const T &Data){ //Adds a copy of the item passed as a parameter to the front of the list, Returns false if the item cannot be added to the list
       GLLNode<T>* newGNode = new GLLNode<T>(Data); //Create the new node
       if(head == nullptr){ //Check if head nullptr

	 head = newGNode;
	 tail = newGNode;

	 return true; //Return true
       }
       else {
	 newGNode -> next = head;
	 head -> prev = newGNode;
	 head = newGNode;
	   return true; //Return True
       }
     }
     
     template <typename T> bool GLL<T>::append(const T &Data){ //Adds a copy of the item passed as a parameter to the back of the list  Returns false if the item cannot be added to the list.
       GLLNode<T>* newGNode = new GLLNode<T>(Data);//Create the new node
       if (tail == nullptr){ //Check if tail is nullptr
	 head = newGNode;
	 tail = newGNode;

       return true; //Return true
     }
     else {
       newGNode->prev = tail;
       tail -> next = newGNode;
       tail = newGNode;
       return true; //Return true
       }
     }

     template <typename T> bool GLL<T>::merge(GLL<T> &other){ //Adds the values of the GLL passed (by reference) as a parameter, to the end of the list, leaving "other" empty. Returns true. If an object is merged into itself, then the function should not take any action.
       if(this == &other){ //Check if other is merging into itself
       return true;
        }
       
       if(other.isEmpty()){ //Check if other is empty
	 return true;
       }
       
      if(head == nullptr && tail == nullptr){ //Check if other is empty
	 head = other.head; //Set head to other 
	 tail = other.tail; //set tail to other
 }
      else{ 
	tail->next = other.head;
	other.head->prev = tail;
	tail = other.tail;
      }
        other.head = nullptr;//clear other
	other.tail = nullptr;
        return true;	    
     }
  
    template <typename T> GLL<T>& GLL<T> :: operator+=(const GLL<T> &other){ //Adds copies of the values of the GLL passed (by reference) as a parameter, to the end of the list, leaving "other" intact.
                                     //Returns a reference to the current object (i.e. the object that is called... use "return *this;").
                                     //Calling "list += list;" cannot both add the list to the left hand side and leave that same list in tact,
                                     //so this operation should instead leave list unchanged. You may simply implement this as "if (this == &other) return *this;"
      
      if (this == &other){//Check if the object is adding itself
      return *this;
    }
      GLLNode<T>* temp = other.head; //Set temp to other's head
      while (temp != nullptr){ //While temp is not nullptr
	append(temp->data); //Append temp
	temp = temp -> next; //increament temp
      }
      
      return *this;
    }
  
   template <typename T> GLL<T>& GLL<T> :: operator-=(const GLL&other){ 
    if (this == &other) { // Check if the object is removing itself
        return *this; // If it is, return without doing anything
    }
    
    GLLNode<T>* curr = head;
    while (curr != nullptr) {
        GLLNode<T>* nextGNode = curr->next;
        GLLNode<T>* otherCurr = other.head;
        bool found = false;

        
        while (otherCurr != nullptr) {
            if (curr->data == otherCurr->data) {
	      if (curr == head) { //If curr is head
                    head = curr->next;
                    if (head != nullptr) { //Check that head isnt null
                        head->prev = nullptr;
                    } else {
                        tail = nullptr; 
                    }
                } else if (curr == tail) { //If node is the tail
                    tail = curr->prev;
                    tail->next = nullptr;
                } else {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                }
                delete curr; //Delete curr
                found = true; 
                break;
            }
            otherCurr = otherCurr->next; //Increament otherCurr
        }

        
        if (!found) { //If not found Increament curr
            curr = nextGNode;
        }

       
        if (found) { //If found reset curr
            curr = head;
        }
    }
    return *this;
}

  
   template <typename T> int GLL<T> :: purgeGoofy(){ //Removes all the items from the GLL that are goofy, leaving only non-goofy items. Returns a count of the number of items that were removed.
   int count = 0;
    GLLNode<T> *curr = head;
   

    while (curr != nullptr) {
        if (isGoofy(curr->data)) { //Check that it is goofy
	  GLLNode<T> *temp = curr;
	  curr = curr -> next;
            if (temp == head) { //Check if temp = head
	      head = temp->next;
            }
	    else {
                temp -> prev -> next = temp->next; //Connect temps previous and next
            }
	  if(temp == tail){ //Check if temp = tail 
	    tail = temp -> prev;
	  }
	  else{
	    temp->next->prev = temp->prev; //Connect temps next and previous
	  }
	    delete temp; //Delete temp
            count++; //Increament Count
        }
	else {
            curr = curr->next; //If not goofy iterate to next node
        }
    }
    return count;
}

   template <typename T> int GLL<T> :: keepGoofy(){ //Removes all the items from the GLL that are not goofy, leaving only goofy items. Returns a count of the number of items that were removed.
     int count = 0; //Count to return
    GLLNode<T> *curr = head;
   

    while (curr != nullptr) {
      if (!isGoofy(curr->data)) { //Check that it is not goofy
	  GLLNode<T> *temp = curr;
	  curr = curr -> next;
	  if (temp == head) { //Check if temp = head
	      head = temp->next;
            }
	    else {
	      temp -> prev -> next = temp->next; //Connect temps previous and next
            }
	  if(temp == tail){ //Check if temp = tail 
	    tail = temp -> prev;
	  }
	  else{
	    temp->next->prev = temp->prev; //Connect temps next and previous
	  }
	  delete temp; //Delete temp
	  count++; //Increament Count
        }
	else {
	  curr = curr->next; //If goofy iterate to next node
        }
    }
    return count;
}
   
  
   template <typename T> bool GLL<T> :: demoteGoofy(){ //Moves all goofy items (if any) to the back of the list, so that the list contains all of its non-goofy items first, then it's goofy items.
     if (head == nullptr){ //Check if list is empty
        return false;
     }

    GLLNode<T>* curr = head;
    GLLNode<T>* firstGoofy = nullptr; 
    
    while (curr != nullptr) {
      if(curr == firstGoofy){ //Check to not reiterate through the list
	return true;
	  }
      GLLNode<T>* nextGNode = curr->next;  //Increament through the list
      if (isGoofy(curr->data)) { //Check if curr is goofy
	if (firstGoofy == nullptr){ //Cet first goofy to the first goofy node
	     firstGoofy = curr;
	  }
	if(curr == head){ //Check if curr == head
	    head = nextGNode;
	  }
	  
	else if(curr == tail){
	    return true;
	  } 
	   if(curr->prev != nullptr){ //If curr is head dont access prev as it is nullptr
	    curr->prev->next = curr->next;
            
	  }
	   if (curr->next != nullptr){//If curr is tail dont access next as it is nullptr
	     curr->next->prev = curr->prev;
	   }
	   
	  curr->prev = tail; 
          tail -> next = curr;
          tail = curr;
	  curr -> next = nullptr;
	  
        }
      
	curr = nextGNode; 
    }
    return true;
}

     
   
  
   template <typename T> bool GLL<T> :: reset(){ //Sets a "pointer" within the object to the first node of the linked list. This operation returns true if the list is non-empty, and false otherwise.
     Gptr = head; //Set Gptr to head
     
     if (head == nullptr && tail == nullptr){ //Check if head and tail are nullptr
       return false;
     }
     return true;
     
  }
  
   template <typename T>  bool GLL<T> :: finished(){ //Returns true if there are "no more" items to go through in the list, false if there are more items.
    
     if (Gptr == nullptr){ //Check if Gptr is null
       return true;
     }
     return false;
  }
    
   
template <typename T> T GLL<T> :: proceed(){ //Returns a copy of the "next" object from the linked list. So a call to reset() followed by a call to proceed() returns a copy of the first element of a (non-empty) GLL.
                                             //Subsequent calls to proceed() return the subsequent items in the list.
                          //When it becomes true that the last item was returned on the previous call to proceed(), and no subsequent "reset()" is performed, then proceed() should return an item created with its default constructor.
  
  if(Gptr == nullptr){ //Check to see if Gptr is nullptr
    return T();
  }
  T data = Gptr -> data; //Get data from the current node
  Gptr = Gptr -> next; //Increament Gptr
  return data;
}

#endif  
