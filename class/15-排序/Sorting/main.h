#pragma once

#include "vector.h"

// function prototype declarations
int indexOfSmallest(const Vector<int>& elems, int startPoint);
void selectionSort(Vector<int>& v);
void insertionSort(Vector<int>& v);
void mergeSort(Vector<int>& v);
void split(Vector<int>& vec, Vector<int>& left, Vector<int>& right);
void merge(Vector<int>& vec, Vector<int>& v1, Vector<int>& v2);
void swap(Vector<int>& v, int i, int j);
