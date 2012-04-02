#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "dsexceptions.h"
#include <iostream>       // For NULL

// Splay node and forward declaration because g++ does
// not understand nested classes.
template <class Comparable>
class SplayTree;

template <class Comparable>
class SplayNode
{
   Comparable element;
   SplayNode *left;
   SplayNode *right;
   SplayNode *parent; 
 
   SplayNode( const Comparable & theElement, SplayNode *lt, SplayNode *rt )
      : element( theElement ), left( lt ), right( rt ) {parent = NULL;}
   friend class SplayTree<Comparable>;
};


// SplayTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// Comparable find( x )   --> Return item that matches x
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order

template <class Comparable>
class SplayTree
{
 public:
  explicit SplayTree( const Comparable & notFound );
  SplayTree( const SplayTree & rhs );
  ~SplayTree( );
  
  const Comparable & findMin( ) const;
  const Comparable & findMax( ) const;
  const Comparable & find( const Comparable & x ) const;
  bool isEmpty( ) const;
  void printTree( ) const;
  
  void makeEmpty( );
  void insert( const Comparable & x );
  void remove( const Comparable & x );
  
  const SplayTree & operator=( const SplayTree & rhs );

  Comparable splay(const Comparable& value);

  void PrintLO();

  void inorder();

  int Sremove(const Comparable & value);

 private:
  SplayNode<Comparable> *root;
  const Comparable ITEM_NOT_FOUND;
  
  const Comparable & elementAt( SplayNode<Comparable> *t ) const;
  
  void insert( const Comparable & x, SplayNode<Comparable> * & t ) const;
  void remove( const Comparable & x, SplayNode<Comparable> * & t ) const;
  SplayNode<Comparable> * findMin( SplayNode<Comparable> *t ) const;
  SplayNode<Comparable> * findMax( SplayNode<Comparable> *t ) const;
  SplayNode<Comparable> * find( const Comparable & x, 
SplayNode<Comparable> *t ) const;
  void makeEmpty( SplayNode<Comparable> * & t ) const;
  void printTree( SplayNode<Comparable> *t ) const;
  SplayNode<Comparable> * clone( SplayNode<Comparable> *t ) const;

  Comparable splay(SplayNode <Comparable> *t);

  int isZigZag(SplayNode <Comparable> *t );

  void PrintDepth(SplayNode<Comparable> *t, int depth, int counter);

  int findDepth(SplayNode<Comparable> *t, int depth, int max);

  void PrintLO(SplayNode <Comparable> * t);

  int LRChild(SplayNode <Comparable> *t);

  void rotate(SplayNode <Comparable> *t);

  void inorder(SplayNode<Comparable> *t);

  void insertNode(SplayNode<Comparable> *input, SplayNode<Comparable> *t);

  int Sremove(SplayNode <Comparable> *t);

};

#include "SplayTree.cpp"
#endif
