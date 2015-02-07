/***********************************************************************
* Header:
*    Lesson 08, Binary Sort Tree
*    Brother Helfrich, CS235
* Author:
*    <Jacob Casperson 6 Hrs & Justin Stucki 6 Hrs>
*    The hardest part was getting a correctly working increment operator
* Summary:
*    This header contains the notion of a Binary Search Tree. This supports
*    inserting into the tree, removing a value from the tree, and other basic
*    manipulation methods.
*****************************************************************************/

#include <iostream>
#include <cassert>
using namespace std;

#ifndef BST_H
#define BST_H

template <class T> class BinaryNode;
template <class T> class BSTIterator;

/********************************************
 * BINARY SORT TREE (template) - CLASS DEFINITION
 * A tree with at most two children, sorted in
 * ascending order (left to right)
 ********************************************/
template <class T>
class BST
{
   public:
      //Default Constructor
      BST() throw (const char*) : root(NULL) {}
      //Destructor
      ~BST()  { deleteBinaryTree(root); }  //Calls the tree deleting function
      //Assignment Operator   
      BST &operator = (const BST &rhs) throw (const char*)
      {
         root = copyTree(rhs.root, root);  //Using the deep copy function
         return *this;
      }

      T copyTree(BinaryNode<T>* oldRoot, BinaryNode<T>* root)
         throw (const char*);
      void deleteBinaryTree(BinaryNode<T>* pDeleteMe);
      bool empty() const                          { return root == NULL;    }
      void insert(T insertThis);
      void remove(BSTIterator<T> removeMe);
      void clear()                                { deleteBinaryTree(root); }
      BSTIterator<T> find(T findThis) const ;
      BinaryNode<T>* getRoot() const              { return root;            }

      //Overloaded operator !=
      bool operator <= (const T &rhs) const
      {
         return this <= rhs;
      }
      //Overloaded operator !=
      bool operator > (const T &rhs) const
      {
         return this > rhs;
      }
      //Overloaded operator !=
      bool operator == (const T &rhs) const
      {
         return rhs == this;
      }

      //Iterator pointing to the smallest value in the tree
      BSTIterator<T> begin()
      {
         if (root == NULL)               //HELFRICH: make begin()
            return BSTIterator<T>(NULL); //the same as end()
         BinaryNode<T>* p = root;       
         if (!p)
            return BSTIterator<T>(NULL); //Empty tree
         while (p->pLeft)
            p = p->pLeft;                //Otherwise look for smallest item
         return BSTIterator<T>(p);
      }
      //Iterator pointing to the "past the end" item (NULL)
      BSTIterator<T> end()   { return BSTIterator<T>(NULL);}
      //Iterator pointing to the largest value in the tree
      BSTIterator<T> rbegin()
      {
         BinaryNode<T>* p = root;
         if (!p)
            return BSTIterator<T>(NULL); //Empty tree
         while (p->pRight)
            p = p->pRight;               //Otherwise look for largest item
         return BSTIterator<T>(p);
      }
      //Iterator pointing to the "past the beginning" item (NULL)
      BSTIterator<T> rend()  { return BSTIterator<T>(NULL);}

   private:
      BinaryNode<T>* root;   //Pointer to the root of the tree
};

/********************************************
 * BST - COPY TREE (template)
 * A recursive deep copy function
 ********************************************/
template <class T>
T BST<T>::copyTree(BinaryNode<T>* oldRoot, BinaryNode<T>* root)
throw (const char*)
{
   //If a left node exists to copy
   if (oldRoot->pLeft)
      root->pLeft = new BinaryNode<T>(copyTree(oldRoot->pLeft, root->pLeft));
   //If a right node exists to copy
   if (oldRoot->pRight)
      root->pRight =
         new BinaryNode<T>(copyTree(oldRoot->pRight, root->pRight));
   //Return the data from this "old" node to be
   //assigned to the "new" node on the last recursion
   return oldRoot->data;
}

/********************************************
 * BST - INSERT (template)
 * In order insert function
 ********************************************/
template <class T>
void BST<T>::insert(T insertThis)
{
  
   //If there is no tree, plant the root
   if (root == NULL)
      root = new BinaryNode<T> (insertThis);

   //Otherwise the tree grows
   else
   {
      BinaryNode<T>* current = root; // start at the root
      bool placed = false;
      while (!placed)
      {
         while (!(insertThis > current->data)) //If value is less than or
         {                                   //equal to insertThis
            if (current->pLeft)
               current = current->pLeft;
            else
            {
               current->addLeft(insertThis); //Insert into empty spot
               placed = true;
               break;
            }
         }
         while (insertThis > current->data) //If value is greater than
         {                                  //insertThis
            if (current->pRight)
               current = current->pRight;
            else
            {
               current->addRight(insertThis); //Insert into empty spot
               placed = true;
               break;
            }
         }
      }
   }
}

/********************************************
 * BST - REMOVE (template)
 * Removes a node from the tree perseving the order
 ********************************************/
template <class T>
void BST<T>::remove(BSTIterator<T> removeMe) 
{
   //If a node has 2 children
   if (removeMe.p->pRight && removeMe.p->pLeft)
   {
      //Find and recursively remove successor
      BSTIterator<T> successor = removeMe;
      ++successor;
      removeMe.p->data = successor.p->data;
      remove(successor);
   }
   //If a node has 1 or 0 children
   else
   {
      BinaryNode<T>* subTree = removeMe.p->pLeft;
      if (subTree == NULL)                     //If no pLeft
         subTree = removeMe.p->pRight;
      if (removeMe.p->pParent == NULL)         //If no pRight
         root = subTree;
      else if (removeMe.p == removeMe.p->pParent->pLeft)//If there is a child
      {                                                 //and we are left child
         removeMe.p->pParent->pLeft = subTree;
         if (subTree)
            subTree->pParent = removeMe.p->pParent;
      }
      else                                           //If there is a child
      {                                              //and we are right child
         removeMe.p->pParent->pRight = subTree;
         if (subTree)
            subTree->pParent = removeMe.p->pParent;
      }
      delete removeMe.p; //Delete Node
   }
}

/********************************************
 * BST - FIND (template)
 * Searches the tree for a value and returns an
 * iterator to that value or NULL if not found
 ********************************************/
template <class T>
BSTIterator<T> BST<T>::find(const T findThis) const
{
   //If found at root
   if (root->data == findThis)
   {
      BSTIterator<T> itFind(root);
      return itFind;
   }
   else
   {
      BinaryNode<T>* current = root;
      while (1)
      {
         //If last loop now points to findThis
         if (findThis == current->data)
         {
            BSTIterator<T> itFind(current);
            return itFind;
         }
         //If dead end and not found
         else if ((findThis < current->data && !current->pLeft)
                  || (findThis > current->data && !current->pRight))
         {
            BSTIterator<T> itFind(NULL);
            return itFind;
         }
         //While greater - move left
         while (findThis <= current->data)
         {
            if (current->pLeft)
               current = current->pLeft;
            break;
         }
         //While less than - move right
         while (findThis > current->data)
         {
            if (current->pRight)
               current = current->pRight;
            break;
         }
      }
   }
}

/********************************************
 * BINARY NODE (template) - CLASS DEFINITION
 * The building blocks to the binary tree
 ********************************************/
template <class T>
class BinaryNode
{
   public:
      //Default Constructor
      BinaryNode<T>()
         : pLeft(NULL), pRight(NULL), pParent(NULL) {}

      //Non-Deafult COnstructor (A)
      BinaryNode<T>(const T &theData)
         : data(theData), pLeft(NULL), pRight(NULL), pParent(NULL) {}

      //addLeft functions
      BinaryNode<T>* addLeft(const T &insertData) throw (const char*);
      BinaryNode<T>* addLeft (BinaryNode<T>* insertNode);

      //addRight functions
      BinaryNode<T>* addRight(const T &insertData) throw (const char*);
      BinaryNode<T>* addRight(BinaryNode<T>* insertNode);

      //Variables unique to each node
      T data;                  // The data object
      BinaryNode<T>* pParent;  // pointer to parent node (above)
      BinaryNode<T>* pLeft;    // pointer to left child node (below)
      BinaryNode<T>* pRight;   // pointer to right child node (below)
};

/********************************************
 * BINARY NODE - ADD LEFT (template)
 * This function inserts a new node to the
 * left containing the passes data
 ********************************************/
template <class T>
BinaryNode<T>* BinaryNode<T>::addLeft(const T &insertData) throw (const char*)
{
   pLeft = new BinaryNode<T>(insertData);  //Creates the left with data
   pLeft->pParent = this;                  //Child's parent is current node
   return this;
}

/********************************************
 * BINARY NODE - ADD LEFT (template)
 * This function inserts a passed node as the left child
 ********************************************/
template <class T>
BinaryNode<T>* BinaryNode<T>::addLeft (BinaryNode<T>* insertNode)
{
   assert (pLeft != NULL);   
   pLeft = insertNode;    //Sets the left child to passes node
   pLeft->pParent = this; //Child's parent is current node
   return this;
}

/********************************************
 * BINARY NODE - ADD RIGHT (template)
 * This function inserts a new node to the
 * right containing the passes data
 ********************************************/
template <class T>
BinaryNode<T>* BinaryNode<T>::addRight(const T &insertData) throw (const char*)
{
   pRight = new BinaryNode<T>(insertData); //Creates the right with data
   pRight->pParent = this;                 //Child's parent is current node
   return this;
}

/********************************************
 * BINARY NODE - ADD LEFT (template)
 * This function inserts a passed node as the left child
 ********************************************/
template <class T>
BinaryNode<T>* BinaryNode<T>::addRight(BinaryNode<T>* insertNode)
{
   assert (pRight != NULL);
   pRight = insertNode;    //Sets the left child to passes node
   pRight->pParent = this; //Child's parent is current node
   return this;
}

/********************************************
 * BST - DELETE BINARY TREE (template)
 * Recusively deletes the nodes
 ********************************************/
template <class T>
void BST<T>::deleteBinaryTree(BinaryNode<T>* pDeleteMe)
{
    if (pDeleteMe)
   {
      if (pDeleteMe->pLeft)               //Delete left child - if necessary
         deleteBinaryTree(pDeleteMe->pLeft);
      if (pDeleteMe->pRight)              //Delete right child - if necessary
         deleteBinaryTree(pDeleteMe->pRight);
      delete pDeleteMe;                   //Delete parent afterward
   }
   
}

/**************************************************
 * BINARY SEARCH TREE ITERATOR
 * An iterator through BST
 *************************************************/
template <class T>
class BSTIterator
{
  public:
   //Default construtor
  BSTIterator() : p(0x00000000) {}
   //Non-deafult constructor
  BSTIterator(BinaryNode<T>* pointToMe) : p(pointToMe) {}
   //Copy constructor
   BSTIterator(const BSTIterator & rhs) { *this = rhs; }
   //Overloaded operator =
   BSTIterator & operator = (const BSTIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }
   //Overloaded operator !=
   bool operator != (const BSTIterator<T> &rhs) const
   {
      return rhs.p != p;
   }
   //Overloaded operator ==
   bool operator == (const BSTIterator<T> &rhs) const
   {
      return rhs.p == p;
   }
   //Overloaded operator *
   T operator * () const
   {
      return p->data;
   }
   
   BSTIterator<T> & operator ++ ();         //Overloaded operator ++
   BSTIterator<T> operator++(int postfix);  //Overloaded operator ++
   BSTIterator<T> & operator -- ();         //Overloaded operator --
   BSTIterator<T> operator--(int postfix);  //Overloaded operator --

   friend void BST<T>::remove(BSTIterator<T> removeMe);
   
  private:
   BinaryNode<T>* p;
};

/**************************************************
 * BST ITERATOR - OVERLOADED OPERATOR ++
 *************************************************/
template <class T>
BSTIterator<T> & BSTIterator<T>::operator ++ ()
{
   if (p->pRight) // if pRight exists
   {
      p = p->pRight; // doesn't seg fault :D
      while (p->pLeft)
         p = p->pLeft;
   }
   // is left or right child?
   else if (p->pParent && p == p->pParent->pLeft) // if left child
      p = p->pParent;
   // if right child with no children,
   else
   {
      while(p->pParent && p == p->pParent->pRight)
         p = p->pParent;
      if (p->pParent)
         p = p->pParent;
      else
         p = NULL;
   }
   return *this;
}

/**************************************************
 * BST ITERATOR - OVERLOADED OPERATOR ++
 *************************************************/
template <class T>
BSTIterator<T> BSTIterator<T>::operator++(int postfix)
{
   BinaryNode<T>* temp = p; // or this
   // has right child
   if (p->pRight) // if pRight exists
   {
      p = p->pRight; // go to the right
      while (p->pLeft)
         p = p->pLeft;
   }
   // is left child with no children
   else if (p->pParent && p == p->pParent->pLeft)
      p = p->pParent; // ++ up to parent
   // if right child with no children,
   else
   {
      while(p->pParent && p == p->pParent->pRight)
         p = p->pParent;
      if (p->pParent)
         p = p->pParent;
      else
         p = NULL;
   }
   return temp;
}

/**************************************************
 * BST ITERATOR - OVERLOADED OPERATOR --
 *************************************************/
template <class T>
BSTIterator<T> & BSTIterator<T>::operator -- ()
{
   // if we have a left child
   if (p->pLeft)
   {
      p = p->pLeft;
      while (p->pRight)
         p = p->pRight;
   }
   // we will never go to right child
   // if we have no left child
   else if (p->pParent && p == p->pParent->pRight)
      p = p->pParent;
   else if (p->pParent->pParent && p == p->pParent->pLeft
            && p->pParent == p->pParent->pParent->pRight)
      p = p->pParent->pParent;
   else
      p = NULL;
   return *this;
}

/**************************************************
 * BST ITERATOR - OVERLOADED OPERATOR --
 *************************************************/
template <class T>
BSTIterator<T> BSTIterator<T>::operator--(int postfix)
{
   BinaryNode<T>* temp = p;
   // if we have a left child
   if (p->pLeft)
   {
      p = p->pLeft;
      while (p->pRight)
         p = p->pRight;
   }
   // we will never go to right child
   // if we have no left child
   else if (p->pParent && p == p->pParent->pRight)
      p = p->pParent;
   else
      p = NULL;
   return temp;
}

#endif
