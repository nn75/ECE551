#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>
//YOUR CODE GOES HERE
template<typename T>
class LinkedList
{
 private:
  class Node
  {
   public:
    T data;
    Node * next;
    Node * prev;
    Node(T data) : data(data), next(NULL), prev(NULL){};
  };
  Node * head;
  Node * tail;
  class Error : public std::exception
  {
    const char * what() { return "Item not exist"; }
  };

 public:
  LinkedList() {
    head = NULL;
    tail = NULL;
  };
  LinkedList(const LinkedList & rhs) {
    head = NULL;
    tail = NULL;
    Node * s;
    for(s = rhs.head; s!=NULL; s= s->next){
      addBack(s->data);
    }
  };
  LinkedList & operator=(const LinkedList & rhs){
    destructor();
    Node * s;
    for(s = rhs.head; s!=NULL; s= s->next){
      addBack(s->data);
    }
    return *this;
  }
  ~LinkedList() { destructor(); };
  void addFront(const T & item);
  void addBack(const T & item);
  bool remove(const T & item);
  T & operator[](int index);
  const T & operator[](int index) const;
  int find(const T & item);
  int getSize() const;
  void destructor();
};

template<typename T>
void LinkedList<T>::destructor() {
  Node *temp;
  for(Node *s = head; s!=NULL; s=temp){
    temp = s->next;
    delete s;
  }
  head = NULL;
  tail = NULL;
}


//template<typename T>
//LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T> & rhs) {
  //destructor();
  //Node * s = head;
  //Node * p = rhs.head;
  //while (p != NULL) {
  // Node * temp = new Node(0);
  //temp->data = p->data;
  //if (tail == NULL) {
  //  head = temp;
  //  tail = temp;
  // }
  //else {
  //  tail->next = temp;
  //  temp->prev = tail;
  //  tail = temp;
  //}
  //p = p->next;
  //Node * s = rhs.head;
  //while (s != NULL) {
    //addBack(s->data);
    //s=s->next;
  //}
  //return *this;
//}

template<typename T>
void LinkedList<T>::addFront(const T & item) {
  Node * node = new Node(item);
  if (head == NULL) {
    head = node;
    tail = node;
  }
  else {
    head->prev = node;
    node->next = head;
    head = node;
  }
}

template<typename T>
void LinkedList<T>::addBack(const T & item) {
  Node * node = new Node(item);
  if (head == NULL) {
    head = node;
    tail = node;
  }
  else {
    tail->next = node;
    node->prev = tail;
    tail = node;
  }
}

template<typename T>
bool LinkedList<T>::remove(const T & item) {
  Node * s;
  for (s = head; s != NULL && (s->data != item); s = s->next) {
  }
  if (s == NULL) {
    return false;
  }
  if (s == head) {
    if (s == tail) {
      head = NULL;
      tail = NULL;
    }
    else {
      head = s->next;
      s->next->prev = NULL;
    }
  }
  else if (s == tail) {
    s->prev->next = NULL;
    tail = s->prev;
  }
  else {
    s->prev->next = s->next;
    s->next->prev = s->prev;
  }
  delete s;
  return true;
}

template<typename T>
int LinkedList<T>::getSize() const {
  int size = 0;
  for (Node * s = head; s != NULL; s = s->next) {
    size++;
  }
  return size;
}

template<typename T>
int LinkedList<T>::find(const T & item) {
  int index = 0;
  Node *s;
  for (s = head; s != NULL && (s->data != item); s = s->next) {
    index++;
  }
  if (s == NULL) {
    return -1;
  }
  return index;
}

template<typename T>
T & LinkedList<T>::operator[](int index) {
  Node * s = head;
  for (int i = index; (s != NULL) && (i > 0); i--) {
    s = s->next;
  }
  if (s == NULL) {
    throw Error();
  }
  return s->data;
}

template<typename T>
const T & LinkedList<T>::operator[](int index) const {
  Node * s = head;
  for (int i = index; (s != NULL) && (i != 0); i--) {
    s = s->next;
  }
  if (s == NULL) {
    throw Error();
  }
  return s->data;
}

#endif
