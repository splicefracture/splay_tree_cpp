#include "SplayTree.h"
#include <iostream>


/**
 * Construct the tree.
 */
template <class Comparable>
SplayTree<Comparable>::SplayTree( const Comparable & notFound ) :
  root( NULL ), ITEM_NOT_FOUND( notFound )
{
}


/**
 * Copy constructor.
 */
template <class Comparable>
SplayTree<Comparable>::
SplayTree( const SplayTree<Comparable> & rhs ) :
  root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{ 
  *this = rhs;
}


/**
 * Destructor for the tree.
 */
template <class Comparable>
SplayTree<Comparable>::~SplayTree( )
{
  makeEmpty( );
}


/**
 * Insert x into the tree; duplicates are ignored.
 */
template <class Comparable>
void SplayTree<Comparable>::insert( const Comparable & x )
{
  insert( x, root );
}


/**
 * Remove x from the tree. Nothing is done if x is not found.
 */
template <class Comparable>
void SplayTree<Comparable>::remove( const Comparable & x )
{
  remove( x, root );
}


/**
 * Find the smallest item in the tree.
 * Return smallest item or ITEM_NOT_FOUND if empty.
 */
template <class Comparable>
const Comparable & SplayTree<Comparable>::findMin( ) const
{
  return elementAt( findMin( root ) );
}


/**
 * Find the largest item in the tree.
 * Return the largest item of ITEM_NOT_FOUND if empty.
 */
template <class Comparable>
const Comparable & SplayTree<Comparable>::findMax( ) const
{
  return elementAt( findMax( root ) );
}


/**
 * Find item x in the tree.
 * Return the matching item or ITEM_NOT_FOUND if not found.
 */
template <class Comparable>
const Comparable & SplayTree<Comparable>::
find( const Comparable & x ) const
{
  return elementAt( find( x, root ) );
}


/**
 * Make the tree logically empty.
 */
template <class Comparable>
void SplayTree<Comparable>::makeEmpty( )
{
  makeEmpty( root );
}


/**
 * Test if the tree is logically empty.
 * Return true if empty, false otherwise.
 */
template <class Comparable>
bool SplayTree<Comparable>::isEmpty( ) const
{
  return root == NULL;
}


/**
 * Print the tree contents in sorted order.
 */
template <class Comparable>
void SplayTree<Comparable>::printTree( ) const
{
  if( isEmpty( ) )
    cout << "Empty tree" << endl;
  else
    printTree( root );
}


/**
 * Deep copy.
 */
template <class Comparable>
const SplayTree<Comparable> &
SplayTree<Comparable>::
operator=( const SplayTree<Comparable> & rhs )
{
  if( this != &rhs )
    {
      makeEmpty( );
      root = clone( rhs.root );
    }
  return *this;
}


/**
 * Internal method to get element field in node t.
 * Return the element field or ITEM_NOT_FOUND if t is NULL.
 */
template <class Comparable>
const Comparable & SplayTree<Comparable>::
elementAt( SplayNode<Comparable> *t ) const
{
  if( t == NULL )
    return ITEM_NOT_FOUND;
  else
    return t->element;
}


/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Comparable>
void SplayTree<Comparable>::
insert( const Comparable & x, SplayNode<Comparable> * & t ) const
{
  if( t == NULL )
    t = new SplayNode<Comparable>( x, NULL, NULL );
  else if( x < t->element )
  {  
     insert( x, t->left );
     t->left->parent = t;
  }
  else if( t->element < x )
  {
    insert( x, t->right );
    t->right->parent = t;
  }
  else
    ;  // Duplicate; do nothing
}


/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Comparable>
void SplayTree<Comparable>::
remove( const Comparable & x, SplayNode<Comparable> * & t ) const
{
  if( t == NULL )
    return;   // Item not found; do nothing
  if( x < t->element )
    remove( x, t->left );
  else if( t->element < x )
    remove( x, t->right );
  else if( t->left != NULL && t->right != NULL ) // Two children
    {
      t->element = findMin( t->right )->element;
      remove( t->element, t->right );
    }
  else
    {
      SplayNode<Comparable> *oldNode = t;
      t = ( t->left != NULL ) ? t->left : t->right;
      delete oldNode;
    }
}


/**
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
template <class Comparable>
SplayNode<Comparable> *
SplayTree<Comparable>::findMin( SplayNode<Comparable> *t ) const
{
  if( t == NULL )
    return NULL;
  if( t->left == NULL )
    return t;
  return findMin( t->left );
}


/**
 * Internal method to find the largest item in a subtree t.
 * Return node containing the largest item.
 */
template <class Comparable>
SplayNode<Comparable> *
SplayTree<Comparable>::findMax( SplayNode<Comparable> *t ) const
{
  if( t != NULL )
    while( t->right != NULL )
      t = t->right;
  return t;
}


/**
 * Internal method to find an item in a subtree.
 * x is item to search for.
 * t is the node that roots the tree.
 * Return node containing the matched item.
 */
template <class Comparable>
SplayNode<Comparable> *
SplayTree<Comparable>::
find( const Comparable & x, SplayNode<Comparable> *t ) const
{
  if( t == NULL )
    return NULL;
  else if( x < t->element )
    return find( x, t->left );
  else if( t->element < x )
    return find( x, t->right );
  else
    return t;    // Match
}


/**
 * Internal method to make subtree empty.
 */
template <class Comparable>
void SplayTree<Comparable>::
makeEmpty( SplayNode<Comparable> * & t ) const
{
  if( t != NULL )
    {
      makeEmpty( t->left );
      makeEmpty( t->right );
      delete t;
    }
  t = NULL;
}


/**
 * Internal method to print a subtree rooted at t in sorted order.
 */
template <class Comparable>
void SplayTree<Comparable>::printTree( SplayNode<Comparable> *t ) const
{
  if( t != NULL )
    {
      printTree( t->left );
      cout << t->element << endl;
      printTree( t->right );
    }
}


/**
 * Internal method to clone subtree.
 */
template <class Comparable>
SplayNode<Comparable> *
SplayTree<Comparable>::clone( SplayNode<Comparable> * t ) const
{
  if( t == NULL )
    return NULL;
  else
    return new SplayNode<Comparable>( t->element, clone( t->left ), clone( t->right ) );
}


/**
 * External Method used to Splay a node to the root
 */
template <class Comparable>
Comparable SplayTree<Comparable>::splay(const Comparable& value)
{
   if (root == NULL)
   {
      return ITEM_NOT_FOUND;
   }
   else if (root->element == value)
   {
      return value;
   }
   else 
   {
      SplayNode<Comparable> *valPtr = NULL;
      
      while (valPtr != root)
      {
valPtr = find(value, root);

splay( valPtr);
      }
            
      return value;
   }
   return ITEM_NOT_FOUND;
}

/**
 * Internal Method used to splay roots
 */
template <class Comparable>
Comparable SplayTree<Comparable>::splay(SplayNode <Comparable> *t)
{

  
   if (t->parent != NULL)
   {
      int result = isZigZag(t);
 
      // zig zag
      if (result == 1){
 
rotate(t);
root->parent = NULL;
rotate(t);
root->parent = NULL;
      }
      // zig zig
      else if (result == 0){
 
rotate(t->parent);
root->parent = NULL;
rotate(t);
root->parent = NULL;
      }
      else if (result == 2){
rotate(t);
      }
      else{
cout << "not found" << endl;
      }
      
   }
   
   return t->element;
}

template <class Comparable>
int SplayTree<Comparable>::isZigZag(SplayNode<Comparable> *t)
{
   if (t != NULL)
   {
      int tC = LRChild(t);
      int tP = -1;
      if (t->parent != NULL){
 tP = LRChild(t->parent);
      }
      if (tP == -1){
// niether zigs nor zags
return 2;
      }
      else if (tC != tP){
//return zigs and zags
return 1;
      }
      else if (tC == tP){
// return zigs
return 0;
      }
   }
   //error
   return -1;
}
template <class Comparable>
void SplayTree<Comparable>::PrintDepth(SplayNode<Comparable> *t, 
      int depth, int counter)
{
   if (t!=NULL)
   {
      PrintDepth(t->left, depth, counter+1);
      if ( depth == counter){
cout << t->element << " " ;
      }
      PrintDepth(t->right, depth, counter+1);
   }
}
template <class Comparable>
int SplayTree<Comparable>::findDepth(SplayNode<Comparable> *t, 
    int depth, int max)
{
   if (t != NULL)
   {
      if (depth > max) {max = depth;}
      max = findDepth(t->left, depth+1, max);
      max = findDepth(t->right, depth+1, max);
   }
   return max;
}

template <class Comparable>
void SplayTree<Comparable>::PrintLO()
{
   if (root != NULL)
   {
      PrintLO(root);
   }   
}

template <class Comparable>
void SplayTree<Comparable>::PrintLO(SplayNode <Comparable> * t)
{
   int x = findDepth(t,0,0);
   for (int i = 0; i <= x; i++){
      PrintDepth(root,i,0);
      cout << endl;
   }
}

template <class Comparable>
int SplayTree<Comparable>::LRChild(SplayNode <Comparable> *t)
{
   if (t == root){
      //return not a child
    
      return -1;
   }
   else if (t->parent->right == t){ 
      //return right child
    
      return 1;
   } 
   else if (t->parent->left == t){
      //return left child;
    
      return 0;
   }
   return -1;
}

// rotates a node about it's parent
template <class Comparable>
void SplayTree<Comparable>::rotate(SplayNode <Comparable> *t)
{

   if (t != NULL && t->parent != NULL)
   {
      int tLR = LRChild(t);

      //t is a left child
      if (tLR == 0){
if (t->right != NULL){
   
   int zig = isZigZag(t);

   if (root == t->parent){
      root = t;
   }
   
            //zigs and zags
            if (zig == 1){
               SplayNode<Comparable> *gPtr = t->parent->parent;
               t->parent->left = NULL;
               t->parent->parent->right = t;
               insertNode(t->parent, t->right);
               t->parent = gPtr;
            }
            //zigs
   else if (zig == 0){


      SplayNode<Comparable> *gPtr = t->parent->parent;
      t->parent->left = NULL;
      t->parent->parent->left = t;
      insertNode(t->parent, t->right);
      t->parent = gPtr;

   }
   else if (zig == 2){
      
      SplayNode<Comparable> *rCPtr = t->right;

      t->parent->parent = t;
      t->right = t->parent;
      t->right->left = rCPtr;
      t->right->left->parent = t->left;

   }
        
}
else{

   int zig = isZigZag(t);

   if (root == t->parent){
      root = t;
   }

            if (zig == 1){

               t->parent->left = NULL;
               t->right = t->parent;
               t->parent = t->parent->parent;
               t->parent->right->parent = t;
               t->parent->right = t;
            }
            //zigs
            else if (zig == 0){

               t->parent->left = NULL;
               t->parent->parent->left = t;
               t->right  = t->parent;
               t->parent = t->right->parent;
               t->right->parent = t;
            }
            else if (zig == 2){

      SplayNode<Comparable> *rCPtr = t->right;

               t->parent->parent = t;
               t->right = t->parent;
               insertNode(rCPtr, t->right);

      }

}
      }
      //t is a right child
      if (tLR == 1){
//t has a left child
if (t->left != NULL){
       
   int zig = isZigZag(t);
   
   if (root == t->parent){
      root = t;
   }

   //zigs and zags
   if (zig == 1){
      SplayNode<Comparable> *gPtr = t->parent->parent;
               t->parent->right = NULL;
               t->parent->parent->left = t;
               insertNode(t->parent, t->left);
               t->parent = gPtr;
   }
   //zigs
    else if (zig == 0){
SplayNode<Comparable> *gPtr = t->parent->parent;
t->parent->right = NULL;
t->parent->parent->right = t;
insertNode(t->parent, t->left);
t->parent = gPtr;

    }
    else if (zig == 2){
SplayNode<Comparable> *rCPtr = t->left;

t->parent->parent = t;
t->left = t->parent;
t->left->right = rCPtr;
t->left->right->parent = t->right;
    }
}
//t does not have a left child
else{
   int zig = isZigZag(t);
   
   if (root == t->parent){
      root = t;
   }
       
   //zigs and zags
            if (zig == 1){

      t->parent->right = NULL;
      t->left = t->parent;
      t->parent = t->parent->parent;
               t->parent->left->parent = t;           
               t->parent->left = t;
            }
            //zigs
            else if (zig == 0){
  
      t->parent->right = NULL;
      t->parent->parent->right = t;
      t->left  = t->parent;
      t->parent = t->left->parent;
      t->left->parent = t;       
            }
   else if (zig == 2){

      t->left = t->parent;
               t->left->parent = t;
               t->left->right = NULL;

   }
   
}
      }
   }   
}

template <class Comparable>
void SplayTree<Comparable>::inorder()
{
   if (root != NULL)
      inorder(root);
}


template <class Comparable>
void SplayTree<Comparable>::inorder(SplayNode<Comparable> *t)
{
   if (t != NULL)
   {
      inorder(t->left);
      cout << t->element << " ";
      inorder(t->right);
   }
}


template <class Comparable>
void SplayTree<Comparable>::insertNode(SplayNode<Comparable> *input,
      SplayNode<Comparable> *t)
{

   if (t == NULL)
   {
      root = input;
   }
   if( input->element < t->element )
   {
      if (t->left != NULL){
         insertNode( input, t->left );
      }
      else{
t->left = input;
t->left->parent = t;
      }
   }
   else if( t->element < input->element )
   {
      if (t->right != NULL){
         insertNode( input, t->right );
      }
      else{
         t->right = input;
         t->right->parent = t;
      }
   }
   else
      ;  // NO Duplicates already; still do nothing
}


template <class Comparable>
int SplayTree<Comparable>::Sremove(const Comparable & value)
{


      SplayNode <Comparable> *lRoot = root->left;
      SplayNode <Comparable> *rRoot = root->right;
      SplayNode <Comparable> *min = findMin(lRoot);

      SplayTree <Comparable> lTree(ITEM_NOT_FOUND);
      

      lTree.insertNode(lRoot, NULL);

      lTree.splay(min->element);

      root = NULL;

      lTree.insertNode(rRoot, lRoot->right);

      *this = lTree;
      return value;

}


template <class Comparable>
int SplayTree<Comparable>::Sremove(SplayNode <Comparable> *t)
{
   if (t->parent != NULL)
   {
      int result = isZigZag(t);

      // zig zag
      if (result == 1){

         rotate(t);
         rotate(t);
      }
      // zig zig
      else if (result == 0){

         rotate(t->parent);
         rotate(t);
      }
      else if (result == 2){
         rotate(t);
      }
      else{
         cout << "not found" << endl;
      }

   }

   return t->element;
}
