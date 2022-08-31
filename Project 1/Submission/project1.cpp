#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void swap(string *x, string *y) {
  // O(1)
  string temp = *x;
  *x = *y;
  *y = temp;
}

// A function to implement bubble sort
void bubbleSort(string arr[], int const n) {
  // Should be O(N^2)
  int i, j;
  
  for (i = 0; i < n-1; i++)    
    for (j = 0; j < n-i-1; j++)
        if (arr[j] > arr[j+1])
            swap(&arr[j], &arr[j+1]);
}

void heapify(string arr[], int const n, int const i) {
  int largest = i; // Initialize largest as root
  int l = 2 * i + 1; // left = 2*i + 1
  int r = 2 * i + 2; // right = 2*i + 2

  // If left child is larger than root
  if (l < n && arr[l] > arr[largest])
      largest = l;

  // If right child is larger than largest so far
  if (r < n && arr[r] > arr[largest])
      largest = r;

  // If largest is not root
  if (largest != i) {
      swap(arr[i], arr[largest]);

      // Recursively heapify the affected sub-tree
      heapify(arr, n, largest);
  }
}
 
// main function to do heap sort
void heapSort(string arr[], int const n) {
  // Should be O(NLog(N))
  // Build heap (rearrange array)
  // O(Logn)
  for (int i = n / 2 - 1; i >= 0; i--)
      heapify(arr, n, i);

  // One by one extract an element from heap
  // O(N)
  for (int i = n - 1; i > 0; i--) {
      // Move current root to end
      swap(arr[0], arr[i]);

      // call max heapify on the reduced heap
      heapify(arr, i, 0);
  }
}

void merge(string arr[], int const left, int const mid, int const right) {
  auto const leftSize = mid - left + 1;
  auto const rightSize = right - mid;

  auto *leftArray = new string[leftSize],
      *rightArray = new string[rightSize];

  for (auto i = 0; i < leftSize; i++)
    leftArray[i] = arr[left+i];
  for (auto j = 0; j < rightSize; j++)
    rightArray[j] = arr[mid+1+j];

  auto indexOfLeft = 0, 
      indexOfRight = 0;
  int indexOfMergedArray = left;
  while (indexOfLeft < leftSize && indexOfRight < rightSize) {
    if (leftArray[indexOfLeft] <= rightArray[indexOfRight]) {
        arr[indexOfMergedArray] = leftArray[indexOfLeft];
        indexOfLeft++;
    }
    else {
        arr[indexOfMergedArray] = rightArray[indexOfRight];
        indexOfRight++;
    }
    indexOfMergedArray++;
  }
  // Copy the remaining elements of
  // left[], if there are any
  while (indexOfLeft < leftSize) {
    arr[indexOfMergedArray] = leftArray[indexOfLeft];
    indexOfLeft++;
    indexOfMergedArray++;
  }
  // Copy the remaining elements of
  // right[], if there are any
  while (indexOfRight < rightSize) {
    arr[indexOfMergedArray] = rightArray[indexOfRight];
    indexOfRight++;
    indexOfMergedArray++;
  }
}

void mergeSort(string arr[], int const begin, int const end) {
  // O(NLog(N))
  if (begin >= end)
    return;

  auto mid = begin + (end - begin) / 2;
  mergeSort(arr, begin, mid);
  mergeSort(arr, mid+1, end);
  merge(arr, begin, mid, end);
}

int partition(string arr[], int const begin, int const end) {
  string pivot = arr[end];

  int i = begin - 1;

  for (int j = begin; j <= end-1; j++) {
    if (arr[j] < pivot) {
      i++;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i+1], arr[end]);
  return i+1;
}

void quickSort(string arr[], int const begin, int const end) {
  if (begin < end) {
    int pivot = partition(arr, begin, end);

    quickSort(arr, begin, pivot-1);
    quickSort(arr, pivot+1, end);
  }
}

int main(int argc, char *argv[]) {
  // argv[0] is the name of file
  // When measuring time, concerned with the 'real'
  
  // Variables
  ifstream inputFile(argv[1]); // input file
  string sortMethod = argv[2]; // which sort method
  bool print = (argc > 3) ? true : false; // Print after sort or no
  int sizeOf; // size of data

  // Setup
  inputFile >> sizeOf;
  string data[sizeOf]; // input data

  // Load data
  int index = 0;
  while (!inputFile.eof()) {
    string newLine;
    inputFile >> newLine;
    data[index] = newLine;
    index++;
  }
  inputFile.close();

  if (sortMethod == "bubble") { // bubble
    bubbleSort(data, sizeOf);
  }
  else if (sortMethod == "merge") { // merge
    mergeSort(data, 0, sizeOf-1);
  }
  else if (sortMethod == "quick") { // quick
    quickSort(data, 0, sizeOf-1);
  }
  else if (sortMethod == "heap") { // heap
    heapSort(data, sizeOf);
  }
  else { // sys
    sort(data, data+sizeOf);
  }

  if (print)
    for (string line : data) {
      cout << line << endl;
    }

  return 0;
}