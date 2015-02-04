/***********************************************************************
* Header:
*    Lesson 05, Node
*    Brother Helfrich, CS235
* Author:
*    Justin Stucki <6 Hrs>
* Summary:
*    This header file contains the notion of a Node and a few maniulator 
*    functions to build, destroy, and find an element within a list.
*    The hardest part were finding a hidden bug in the assigning of pointers
*    when inserting. Everything seemed to work ok, until we found that a
*    pointer to the previous node wasn't updating correctly.
*****************************************************************************/
#include <iostream>

#ifndef NODE_H
#define NODE_H

namespace std   //Added in order to remove "using namespace std" statement
{               //Is this valid, instead of putting "std::" everywhere?

/********************************************
 * NODE (template) - CLASS DEFINITION
 * The building blocks to the list container
 ********************************************/
template <class T>
class Node
{
   public:
      //Default Constructor
      Node<T>() : data(0), pPrev(NULL), pNext(NULL) {}
      //Non-Deafult COnstructor (A)
      Node<T>(T theData) : data(theData), pPrev(NULL), pNext(NULL) {}
      //Non-Default Constructor (B)
      Node<T>(const T &theData, Node<T>* thePrev, Node<T>* theNext)
         : data(theData), pPrev(thePrev), pNext(theNext) {}
      //Copy Constructor
      Node<T>(const Node<T> & rhs) : data(0), pPrev(NULL), pNext(NULL)
      {
         *this = rhs;
      }
      //Overloaded Assignment Operator
      Node<T> & operator = (const Node<T> & rhs)
      {
         data = rhs.data;
         pPrev = rhs.pPrev;
         pNext = rhs.pNext;
         return *this;
      }

      //Friend Overloaded << Operator for display purpose
      friend ostream& operator << (ostream &out, Node<T> *p)
      {
         for (Node<T>* it = p; it != NULL; it = it->pNext)
         {            
            (!it->pPrev) ? : out << ", ";
            out << it->data;
         }
         return out;
      }

      //Variables unique to each node
      T data;            // The data object
      Node<T>* pPrev;     // pointer to previous node
      Node<T>* pNext;     // pointer to next node
};

/********************************************
 * COPY (Template)
 * Stand-alone function that returns a pointer
 * to the head of the new copied list. 
 ********************************************/
template <class T>
Node<T>* copy(Node<T> *p)
{
   //Create a pointer to the new list and an iterator for the new list
   Node<T>* pHeadNew = NULL;
   Node<T>* currentNew = pHeadNew;
   Node<T>* currentOld = p;
   //Loop through old list while inserting onto new list.
   while (currentOld)
   {
      //If first node on new list
      if (!pHeadNew)
      {
         headInsert(currentOld->data, pHeadNew);
         currentNew = pHeadNew;
         currentOld = currentOld->pNext;
      }
      //All other nodes
      else
      {
         insert(currentOld->data, currentNew);
         currentNew = currentNew->pNext;
         currentOld = currentOld->pNext;
      }
   }
   //Return the pointer to the new list
   return pHeadNew;
}

/********************************************
 * FIND (Template)
 * Stand-alone function that returns a pointer
 * to the node that contains the desired value
 ********************************************/
template <class T>
Node<T>* find(Node<T>*p, const T t)
{
   //Declare iterators
   Node<T>* current;
   Node<T>* next;
   //Loop through list comparing for input value
   for (current = p; current && t != current->data; current = next)
      next = current->pNext;
   //Return pointer to located node
   // or NULL if not found
   return current;
}

/********************************************
 * HEAD INSERT (Template)
 * Stand-alone function that acts as a special
 * case of insertion as the first node
 ********************************************/
template <class T>
void headInsert(const T &data, Node<T>* &head)
{
   //pHead now points to a new node pointing to the original first
   head = new Node<T>(data, NULL, head);
   //If there's a following node, update it's pPrev pointer.
   if (head->pNext)
      head->pNext->pPrev = head;
}

/********************************************
 * INSERT (Template)
 * Stand-alone function that inserts a new
 * node after the node to which the pointer
 * points to
 ********************************************/
template <class T>
void insert(const T &data, Node<T>* &afterMe, bool insertHead = false)
{
   //If insertHead flag is set
   if (insertHead)
      headInsert(data, afterMe);

   //If pointer is an empty pointer
   else if (!afterMe)
      afterMe = new Node<T>(data, NULL, NULL);

   //If regular insert
   else
   {
      afterMe->pNext = new Node<T>(data, afterMe, afterMe->pNext);
      if (afterMe->pNext->pNext)
      {
         afterMe->pNext->pPrev = afterMe;
         afterMe->pNext->pNext->pPrev = afterMe->pNext;
      }
   }
}

/********************************************
 * FREEDATA (Template)
 * Stand-alone function that acts as an erase
 * function to release nodes
 ********************************************/
template <class T>
void freeData(Node<T>* &p)
{
   //Loop through list deleting nodes
   // while keeping track of which would come next
   Node<T>* current = p;
   while(!current)
   {
      Node<T>* next = current->pNext;
      delete current;
      current = next;
   }
   //Set the pointer now to empty
   p = NULL;
}

} //End namepace statement
#endif
