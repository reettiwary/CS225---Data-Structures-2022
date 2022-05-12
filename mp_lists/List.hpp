/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    //ListNode* head_ = NULL;
    head_ = NULL; //in order to fix the bug we already do have head_ being set to NULL
    
    //ListNode* tail_ = NULL;
    tail_ = NULL; //similar to the head_ idea

    length_ = 0; //here we want our length_ to be set to 0
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  //return List<T>::ListIterator(NULL);
  return List<T>::ListIterator(head_); //we need to be able to access and reference to head_ not NULL
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * var1 = head_; //created a new pointer called var1 to store/point to the head_ and what it "stores"

  ListNode * var2 = var1; //new pointer with the pointer created earlier 

  while(var1 != NULL){ //while loop to access how the dynamically allocated memory at current storage can be destroyed 
    var2 = var2->next; //step by step accessing the next memory stored at var2

    delete var1; //destroying essentially

    var1 = var2; //set the access to the var1 variable
  }

 //testcase is not working  
  //var1 = NULL; 
  //var2 = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata); //new list node created 

//conditional statement so that we can insert a new node into the front of the list 
  if(head_ != NULL){
    newNode -> next = head_; //being able to move in a sense 
    newNode -> prev = NULL; //here we will set prev to NULL since we are worried about the new node at front 

    head_ -> prev = newNode; //so now newNode is essentially taking place 
    head_ = newNode; //now whatever is at newNode is what head_ adopts per say
  }

  else{ //to see what could happen if a new node cannot be truly at a front of a list point to next or prev setting it to NULL
    head_ = newNode; 
    tail_ = newNode;

    //newNode -> next = NULL;

    //newNode -> prev = NULL;
  }

  length_ += 1;
}
  
//  //* if (head_ != NULL) {
//     head_ -> prev = newNode;
//   }
//   if (tail_ == NULL) {
//     tail_ = newNode;
//   }
  

//   length_++;

// }


/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode1 = new ListNode(ndata);

  if(tail_ != NULL){ //we apply the same idea but now with the new node being insert at the back of the list 

    tail_ -> next = newNode1;

    newNode1 -> next = NULL;

    newNode1 -> prev = tail_; //essentially new node can be pointing to the back

   // head_ -> prev = newNode;
    tail_ = newNode1; //new node should be back at list 
  }

  else{
    head_ = newNode1;

    tail_ = newNode1;

    //tail_ -> next = NULL;

    //tail_ -> prev = NULL;
  }

  length_ += 1;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  /*cout<<splitPoint<<endl;*/
  
  ListNode * current = start; //pointer called current storing/accessing start 


//we need to check the segmentation issues because it could be signaling that something is out of length list bounds 
  if(splitPoint > length_ || splitPoint <= 0){
    return start; 
  }

  if(start == NULL){
    return start;
  }

  for (int c = 0; c < splitPoint && current != NULL; c++)  //forloop to be able to access through the linked lists with the notion of what to disconnect with NULL reference 
  {
    current = current->next;
  }

  if (current != NULL && current->prev != NULL) {

      current->prev->next = NULL;

      current->prev = NULL;
  }

  return current;

}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode * one_h = head_;

  ListNode * two_h = head_->next;

  ListNode * three_h = two_h -> next; //wrapped roation to the left on every 3 end of the list with one or two elements 

  ListNode * tail_var;

  int k = (length_ % 3); //modulo for the triple rotate aspect 
  int m = (length_/3); //divide 

  int x;

  if(k == 0){
    x = m;
  }
  else{
    int y = m;
    x = y;
  }

  //would a value less than 0 be affected
  //if(x < 1){
    //return;
  //}

//we need to set a for loop to be able to access the whole element so that rotation will not occur on the last 1 or 2 elements 
  for(int y = 0; y < x; y++){

    if(y == 0){ 
      one_h->next = three_h->next;

      three_h->next = one_h;

      one_h->prev = three_h;

      two_h->prev = NULL;

      head_ = two_h;

      tail_var = one_h;
    }

    else{ //if we do not make sure our list elements are accessed and st to which could rotate possibly this does not let the code compile 
      one_h = tail_var->next;

      two_h = tail_var->next->next; //pointing to the next next node 

      three_h = tail_var->next->next->next; //similar idea applied 

      if(three_h->next != NULL){
        one_h->next = three_h->next;
      }
      else{
        one_h->next = NULL;

      }

    //before the output would be <2 3 1 5 6 4, and we would get 2 3 1 4 so we need to make sure that each next prev variable with the pointer reference can allow the rotate
    //aspect workout per say 

      three_h->next = one_h;
      one_h ->prev = three_h;

      two_h ->prev = tail_var;
      tail_var ->next = two_h;
      tail_var = one_h;
    }
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  //if(startPoint == endPoint or startPoint == NULL or endPoint == NULL){
    //return; to see if anything out of the norm could be returned 
  //}

//create a whole lot of pointer variables to be able to allow the reverse aspect occur where the start of an original list can be the end of a new list 
  ListNode * temp;
  ListNode * curr = startPoint;
  ListNode * begin_b = startPoint->prev; 
  ListNode * finish_e = endPoint->next; 
  ListNode * beginning1 = startPoint; 
  ListNode * ending1 = endPoint; 

  while( curr != finish_e){
    temp = curr->prev;
    curr->prev = curr->next;

    curr-> next = temp;
    curr = curr->prev;
  }

  ending1->prev = begin_b; //where the reverse idea poses 
  beginning1->next = finish_e;

  if(begin_b != NULL){
    begin_b->next = ending1;
  }

  if(finish_e != NULL){
    finish_e->prev = beginning1;
  }

  //startPoint = ending1; why reverse should be like the ending is the start 

  //endPoint = beginning1;

  if(head_ == beginning1){
    head_ = ending1;
  }

  if(tail_ == ending1){
    tail_ = beginning1;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2

  if(n >= length_){
    reverse(head_, tail_);
    return;
  }

  //bug testing 
  //if(n <= 1){ 
    //return;
  //}

  int section;
  int a = length_%n;
  int b = length_/n;

  if(a > 0){
    section = (b+1);
  }

  if(a == 0){
    section = b;
  }

  int c = (section + 1);

  for(int z = 1; z < c; z++){
    ListNode * endvar = head_; //both pointers to point to the head_ element 
    ListNode * startvar = head_;

    int d = (z*n) - 1;

    for(int i = 0; i<d; i++){

      if(endvar->next != NULL){
        endvar = endvar->next;
      }
    }

    int e = (z-1)*n;

    for(int j = 0; j<e; j++){
      startvar = startvar->next;
    }

    reverse(startvar, endvar); //by being able to call the reverse function the sections/blocks of size n can be manipulated 
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_); //call to the merge function 

    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {

        while (tail_->next != NULL){
            tail_ = tail_->next;
    }
    }

    length_ = length_ + otherList.length_; //we can merge the lengths of other lists together 

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  //return NULL;

  if(first == NULL){ //set the conditional if the starting node of the first sequence is set to NULL
    return second; //then the starting node of the second sequence is returned 
  }

  if(second == NULL){ //similar to the first conditional we set up repeat with the parameters reversed 
    return first;
  }

 //NULL would be returned either ways 
 // if(second == NULL && first == NULL){ 
 //   return NULL; to see if any other value could be reurned with bugs
 // }

  ListNode * head_var;
  
  if(first->data < second->data){
    head_var = first;
    first = first->next;
  }

  else{
    head_var = second;
    second = second->next;
  }

  ListNode * curr1 = head_var;

  while(first != NULL && second != NULL){

    if(first->data < second->data){

      curr1->next = first;

      first->prev = curr1;

      //first = first->next;

      curr1 = first;

      first = first->next;
    }

    else{ //here repeat the same idea as before where second parameter will take place of the pointer current and next node 
      curr1->next = second;

      second->prev = curr1;

      curr1 = second;

      second = second->next;
    }
  }

  if(first == NULL && second != NULL){ 
    curr1 -> next = second;

    second ->prev = curr1;

    //curr1->next = first;

    //first->prev = curr1;
  }

  if(second == NULL && first != NULL){
    curr1->next = first;

    first->prev = curr1;
  }

  return head_var; //return 
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  //return NULL;

  if(chainLength == 0 || chainLength == 1){ //allows us to go through a chiann with start node and size 
    return start;
  }

  else{ //here the recursive aspect  is references 
    int length1 = (chainLength/2);

    ListNode * mid = split(start, length1); //set the middle aspect 

    ListNode * leftside = mergesort(start, length1);

    int diff = (chainLength - length1);

    ListNode * rightside = mergesort(mid, diff);

    return merge(leftside, rightside); //chain divide conquer aspect is returned 

  }
}
