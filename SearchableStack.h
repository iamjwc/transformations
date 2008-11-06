////////////////////////////////////////////////////////////////////////////
// Class definition file: SearchableStack.h                               //
//                                                                        //
// This file defines the SearchableStack class template, implemented as a //
// doubly-linked circular list of nodes containing values of type E (the  //
// template's parameterized data-type). Its member functions include      //
// constructors, a destructor, and standard isEmpty, top, pop, push, and  //
// getSize functions. A current pointer is also maintained, allowing for  //
// additional functionality for retrieving or removing the current value, //
// as well as moving the current pointer up and down the list.            //
////////////////////////////////////////////////////////////////////////////

#ifndef SEARCHABLE_STACK_H

#include <stdlib.h>
#include <assert.h>

/////////////////////////////////////////////////////////////
// DECLARATION SECTION FOR SEARCHABLE STACK CLASS TEMPLATE //
/////////////////////////////////////////////////////////////

template <class E> class SearchableStack
{
	public:
		// Class constructors and destructor
		SearchableStack();
		SearchableStack(const SearchableStack<E> &list);
		~SearchableStack();

		// Member functions
		bool isEmpty();
		void push(E item);
		bool pop();
		bool removeCurrent();
		E getTop();
		E getCurrent();
		int getSize();
		SearchableStack<E>& operator ++ ();
		SearchableStack<E>& operator -- ();
		void goToTop() {current = top;}
		void goToBottom() {current = (top == NULL) ? NULL : top->previous;}

    void each( void (*f)( E item ), bool each_in_order = true );
    void each( void (*f)( E item, int i ), bool each_in_order = true );

    void each( bool (*f)( E item ), bool each_in_order = true );
    void each( bool (*f)( E item, int i ), bool each_in_order = true );
	
	protected:
		// Data members

		struct node;
		typedef node *nodePtr;	
		struct node
		{
			E data;
			nodePtr next;
			nodePtr previous;
		};

		nodePtr top;
		nodePtr current;
		int size;

		// Member function
		void* getNode(E item);
};

///////////////////////////////////////////////
// IMPLEMENTATION SECTION FOR CLASS TEMPLATE //
///////////////////////////////////////////////

//////////////////////////////////////////////
// Default constructor: Sets up empty list. //
//////////////////////////////////////////////
template <class E>
SearchableStack<E>::SearchableStack()
{
	top = NULL;
	current = NULL;
	size = 0;
}

////////////////////////////////////////////////
// Copy constructor: Makes deep copy of list. //
////////////////////////////////////////////////
template <class E>
SearchableStack<E>::SearchableStack(const SearchableStack<E> &list)
{
	nodePtr copyPreviousPtr, copyCurrentPtr, origCurrentPtr;
	size = list.size;
	if (list.top == NULL)
	{
		top = NULL;
		current = NULL;
	}
	else
	{
		top = (nodePtr)getNode(list.top->data);
		if (list.current == list.top)
			current = top;
		copyPreviousPtr = top;
		origCurrentPtr = list.top->next;
		while (origCurrentPtr != list.top)
		{
			copyCurrentPtr = (nodePtr)getNode(origCurrentPtr->data);
			if (list.current == origCurrentPtr)
				current = copyCurrentPtr;
			copyPreviousPtr->next = copyCurrentPtr;
			copyCurrentPtr->previous = copyPreviousPtr;
			copyPreviousPtr = copyCurrentPtr;
			origCurrentPtr = origCurrentPtr->next;
		}
		copyPreviousPtr->next = top;
		top->previous = copyPreviousPtr;
	}
}

/////////////////////////////////////////////////////////////
// Destructor: Converts entire list back into free memory. //
/////////////////////////////////////////////////////////////
template <class E>
SearchableStack<E>::~SearchableStack()
{
	nodePtr ptr;
	while (top != NULL)
	{
		ptr = top;
		if (top == top->next)
			top = NULL;
		else
		{
			top = top->next;
			top->previous = ptr->previous;
			top->previous->next = top;
		}
		delete ptr;
	}
}

//////////////////////////////////////////////////////
// Function to determine whether the list is empty. //
//////////////////////////////////////////////////////
template <class E>
bool SearchableStack<E>::isEmpty()
{
	return (size == 0);
}

//////////////////////////////////////////////////////////////
// Function to insert value "item" at the head of the list. //
//////////////////////////////////////////////////////////////
template <class E>
void SearchableStack<E>::push(E item)
{
	size++;
	current = (nodePtr)getNode(item);
	if (top == NULL)
	{
		top = current;
		top->next = top;
		top->previous = top;
	}
	else
	{
		current->next = top;
		current->previous = top->previous;
		top->previous->next = current;
		top->previous = current;
		top = current;
	}
	return;
}

//////////////////////////////////////////////////
// Function to remove the head element from the //
// searchable stack. A boolean is returned to   //
// indicate whether such an element existed.    //
//////////////////////////////////////////////////
template <class E>
bool SearchableStack<E>::pop()
{
	if ( ( size == 0) || (top == NULL) )
		return false;
	else
	{
		current = top;
		if (top->next == top)
		{
			size = 0;
			top = NULL;
		}
		else
		{
			size--;
			top = current->next;
			top->previous = current->previous;
			current->previous->next = top;
		}
		delete current;
		current = top;
		return true;
	}
}

//////////////////////////////////////////////////
// Function to remove the current element from  //
// the searchable stack. A boolean is returned  //
// to indicate whether such an element existed. //
//////////////////////////////////////////////////
template <class E>
bool SearchableStack<E>::removeCurrent()
{
	nodePtr previousPtr;
	if ( ( size == 0) || (current == NULL) )
		return false;
	else if (current == top)
		pop();
	else
	{
		size--;
		current->previous->next = current->next;
		current->next->previous = current->previous;
		delete current;
		current = top;
	}
	return true;
}

////////////////////////////////////////////////////////////////////
// Function getHeadValue returns a copy of the head node's value. //
////////////////////////////////////////////////////////////////////
template <class E>
E SearchableStack<E>::getTop()
{
	assert(top != NULL);
	return top->data;
}

////////////////////////////////////////
// Function getCurrentValue returns a //
// copy of the current node's value.  //
////////////////////////////////////////
template <class E>
E SearchableStack<E>::getCurrent()
{
	assert(current != NULL);
	return current->data;
}

/////////////////////////////////////////
// Function size returns the current   //
// number of nodes in the linked list. //
/////////////////////////////////////////
template <class E>
int SearchableStack<E>::getSize()
{
	return size;
}

///////////////////////////////////////////////////////////////
// The increment operator moves the current pointer one item //
// further down the linked list (if that's possible).        //
///////////////////////////////////////////////////////////////
template <class E>
SearchableStack<E>& SearchableStack<E>::operator ++ ()
{
	if (current != NULL)
		current = current->next;
	return *this;
}

///////////////////////////////////////////////////////////////
// The decrement operator moves the current pointer one item //
// further up the searchable stack (if that's possible).     //
///////////////////////////////////////////////////////////////
template <class E>
SearchableStack<E>& SearchableStack<E>::operator -- ()
{
	if (current != NULL)
		current = current->previous;
	return *this;
}

//////////////////////////////////////////////////////////////////
// Function to generate a new node with the data value provided //
// in parameter item, and returning a pointer to this new node. //
//////////////////////////////////////////////////////////////////
template <class E>
void* SearchableStack<E>::getNode(E item)
{
	nodePtr temp = new node;

	assert(temp != NULL);
	temp->data = item;
	temp->next = NULL;
	temp->previous = NULL;
	return temp;
}


template <class E>
void SearchableStack<E>::each( void (*f)( E item ), bool each_in_order )
{
  if( this->size == 0 ) return;

  if( each_in_order )
    this->goToTop();
  else
    this->goToBottom();

  for( int i = 0, n = this->size; i < n; i++, each_in_order ? this->operator++() : this->operator--() )
    f( this->getCurrent() );
}

template <class E>
void SearchableStack<E>::each( void (*f)( E item, int i ), bool each_in_order )
{
  if( this->size == 0 ) return;

  if( each_in_order )
    this->goToTop();
  else
    this->goToBottom();

  for( int i = 0, n = this->size; i < n; i++, each_in_order ? this->operator++() : this->operator--() )
    f( this->getCurrent(), i );
}

template <class E>
void SearchableStack<E>::each( bool (*f)( E item ), bool each_in_order )
{
  if( this->size == 0 ) return;

  if( each_in_order )
    this->goToTop();
  else
    this->goToBottom();

  bool keep_going = f( this->getCurrent() );

  for( int i = 1, n = this->size; i < n && keep_going; i++, each_in_order ? this->operator++() : this->operator--() )
    keep_going = f( this->getCurrent() );
}

template <class E>
void SearchableStack<E>::each( bool (*f)( E item, int i ), bool each_in_order )
{
  if( this->size == 0 ) return;

  if( each_in_order )
    this->goToTop();
  else
    this->goToBottom();

  int i = 0;
  int n = 0;
  bool keep_going = f( this->getHeadValue(), i );

  for( i = 1, n = this->size; i < n && keep_going; i++, each_in_order ? this->operator++() : this->operator--() )
    keep_going = f( this->getCurrent(), i );
}

#define SEARCHABLE_STACK_H
#endif

