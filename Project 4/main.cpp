/*
  Name: CJ Hess
  Date: 3/28/2022
  File: main.cpp
*/
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <algorithm>

using namespace std;

struct Object {
  // Represents one line of input file
  string name;
  double x;
  double y;
};

struct ClosestPair {
  // Represents the distance between two Objects
  double distance;
  Object obj1;
  Object obj2;
};

ClosestPair closestPair; // Global variable to hold the closest pair, used to grab the two Objects at the end

bool sort_obj_x(const Object & obj1, const Object & obj2) {
  // Comparator for sorting
  return obj1.x < obj2.x;
}

bool sort_obj_y(const Object & obj1, const Object & obj2) {
  // Comparator for sorting
  return obj1.y < obj2.y;
}

double distance(Object obj1, Object obj2) {
  // Calculate distance formula
  return sqrt( (obj1.x-obj2.x) * (obj1.x-obj2.x) + (obj1.y-obj2.y) * (obj1.y-obj2.y) );
}

double distancesInArea(Object O[], int n) {
  // Brute forces through objects in a subarea, only used when we have 3 or less
  float min = __FLT_MAX__;
  for (int i = 0; i < n; i++)
    for (int j = i+1; j < n; ++j)
      if (distance(O[i], O[j]) < min) {
        min = distance(O[i], O[j]);
        closestPair.distance = min;
        closestPair.obj1 = O[i];
        closestPair.obj2 = O[j];
      }

  return min;
}

double min(double x, double y) {
  // return the minimum between two doubles
  return (x < y) ? x : y;
}

double stripClosest(Object strip[], int size, double d) {
  // Find the closest once we have our defined strip of
  double min = d;

  // Sort array by y coordinate
  sort(strip, strip+size, sort_obj_y);

  for (int i = 0; i < size; ++i) {
    for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
      if (distance(strip[i], strip[j]) < min) {
        min = distance(strip[i], strip[j]);
        closestPair.distance = min;
        closestPair.obj1 = strip[i];
        closestPair.obj2 = strip[j];
      }      
    }
  }

  return min;
}

double closest(Object O[], int n) {
  // Majority code runner
  // Recursively creates our strip and finds a smallest distance
  // finally returns the minimum between smallest distance in strip
  // and the smallest distance overall.
  if (n <= 3)
    return distancesInArea(O, n);

  int mid = n/2;
  Object midPoint = O[mid];

  double distanceLeft = closest(O, mid);
  double distanceRight = closest(O+mid, n-mid);

  double smallestDistance = min(distanceLeft, distanceRight);

  // Acceptance Strip is certain distance from the mid point of all points
  Object acceptStrip[n];
  int j = 0;
  for (int i = 0; i < n; i++) {
    if (abs(O[i].x - midPoint.x) < smallestDistance) {
      acceptStrip[j] = O[i];
      j++;
    }
  }

  return min(smallestDistance, stripClosest(acceptStrip, j, smallestDistance));
}

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    cout << "Please execute using: ./executable inputFileName" << endl;
  }
  else {
    string fileName = argv[1];
    ifstream inputFile(fileName);
    int numberObjects = 0;
    inputFile >> numberObjects;
    Object objectArr[numberObjects];

    // Load all points into array
    int index = 0;
    while (!inputFile.eof()) {
      Object newObject;
      inputFile >> newObject.name;
      inputFile >> newObject.x;
      inputFile >> newObject.y;
      objectArr[index] = newObject;
      index++;
    }

    // Sort array by x coordinates
    sort(objectArr, objectArr+numberObjects, sort_obj_x);

    // Divide and Conquer
    double min = closest(objectArr, numberObjects);
    cout << "Min Distance: " << min << endl;
    cout << "Between " << closestPair.obj1.name << "(" << closestPair.obj1.x << "," << closestPair.obj1.y << ")"
     << " and " << closestPair.obj2.name << "(" << closestPair.obj2.x << "," << closestPair.obj2.y << ")" << endl;

    inputFile.close();
  }
  return 0;
}