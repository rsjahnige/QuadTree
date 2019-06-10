/***********************************************
>> File: QuadTree.cpp
>> Author: Ryan Jahnige
>> Class: CMSC 341
>> Description: Implementation of all functions associated
                with QuadTree class
 **********************************************/
#include "Point.h"
#include "BBox.h"
#include "QTQuad.h"
#include "QuadTree.h"
#include <iostream>
#include <vector>

using namespace std;

// Iterator constructor
QuadTree::iterator::iterator()
{
  iter_QTQ = nullptr;
}

// Destructor
QuadTree::iterator::~iterator()
{
  // No dynamically allocated memory within
  // iterator class;
}

// Comparison of 2 iterator objects
// Returns true if one equals the other
bool QuadTree::iterator::operator==(const QuadTree::iterator &other)
{
  if (iter_pt == other.iter_pt && iter_QTQ == other.iter_QTQ)
    {
      return true;
    }
  else
    {
      return false;
    }
}

// Comparison of 2 iterator objects
// Returns true if one doees not equal the other
bool QuadTree::iterator::operator!=(const QuadTree::iterator &other)
{
  if (iter_pt == other.iter_pt && iter_QTQ == other.iter_QTQ)
    {
      return false;
    }
  else
    {
      return true;
    }
}

// Prefix increment of iterator
// Moves current iterator to next non-0 value
QuadTree::iterator& QuadTree::iterator::operator++()
{
  bool result = iter_QTQ -> getNext(iter_pt, iter_QTQ);

  // Has reached the end of the QuadTree
  if (!result)
    {
      iter_pt.m_x = 0;
      iter_pt.m_y = 0;
      iter_QTQ = nullptr;
    }
  
  return *this;
}

// Postfix increment of iterator
QuadTree::iterator QuadTree::iterator::operator++(int dummy)
{
  QuadTree::iterator it;
  it.iter_pt.m_x = iter_pt.m_x;
  it.iter_pt.m_y = iter_pt.m_y;
  it.iter_QTQ = iter_QTQ;

  operator++();
  return it;
}

// Returns location of iterator
Point& QuadTree::iterator::operator*()
{
  return iter_pt;
}

// Overloaded assignment operator for iterator class
const QuadTree::iterator& QuadTree::iterator::operator=(const QuadTree::iterator &rhs)
{
  iter_pt.m_x = rhs.iter_pt.m_x;
  iter_pt.m_y = rhs.iter_pt.m_y;
  iter_QTQ = rhs.iter_QTQ;

  return *this;
}

// Default constructor
QuadTree::QuadTree()
{
  m_root = new QTQuad();
  
  m_bounds.m_bL.m_x = 0;
  m_bounds.m_bL.m_y = 0;
  m_bounds.m_dim = 16;
  
  m_qBounds.m_bL.m_x = 0;
  m_qBounds.m_bL.m_y = 0;
  m_qBounds.m_dim = 16;
}

// Overloaded constructor
QuadTree::QuadTree(const BBox &bounds)
{
  m_root = new QTQuad();
  
  m_bounds.m_bL.m_x = bounds.m_bL.m_x;
  m_bounds.m_bL.m_y = bounds.m_bL.m_y;
  m_bounds.m_dim = bounds.m_dim;
  
  m_qBounds.m_bL.m_x = bounds.m_bL.m_x;
  m_qBounds.m_bL.m_y = bounds.m_bL.m_y;
  m_qBounds.m_dim = bounds.roundUpPow2(bounds.m_dim);
}

// Destructor
QuadTree::~QuadTree()
{ 
  delete m_root;
}

// Retrieves data at point in tree
int QuadTree::get(const Point &pt)
{
  return m_root -> get(pt, m_qBounds);
}

// Sets data at point in tree
void QuadTree::set(const Point &pt, int data)
{
  m_root -> set(pt, data, m_qBounds);

  // Prunning
  if (data == 0)
    {
      QTQuad *temp = m_root -> tryPrune(pt, m_qBounds);

      // So root does not get deleted
      if (temp == m_root)
	{
	  clearAll(); 
	}
      else if (temp != nullptr)
	{
	  delete temp;
	  //temp = nullptr;
	}
    }
}

// Change value of data at a certain point
int QuadTree::increment(const Point &pt, int delta)
{
  int value = m_root -> increment(pt, delta, m_qBounds);
  
  // Prunning
  if (value == 0)
    {
      QTQuad *temp = m_root -> tryPrune(pt, m_qBounds);

      // So root does not get deleted
      if (temp == m_root)
	{
	  clearAll();
	}
      else if (temp != nullptr)
	{
	  delete temp;
	  //temp = nullptr;
	}
    }
  
  return value;
}

// Deletes entire tree except for the root
void QuadTree::clearAll()
{
  m_root -> clearAll();
}

// Finds first non-0 value in QuadTree 
QuadTree::iterator QuadTree::begin()
{
  QuadTree::iterator it;
  bool result = m_root -> getFirst(it.iter_pt, it.iter_QTQ, m_qBounds);

  
  if (!result)
     {
      it.iter_pt.m_x = 0;
      it.iter_pt.m_y = 0;
      it.iter_QTQ = nullptr;
    }
  
  return it;
}

// Sets an end iterator, always the same
QuadTree::iterator QuadTree::end()
{
  QuadTree::iterator it;
  it.iter_pt.m_x = 0;
  it.iter_pt.m_y = 0;
  it.iter_QTQ = nullptr;
  
  return it;
}
 
