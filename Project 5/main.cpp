/*
  Name: CJ Hess
  Date: 4/11/2022
  File: main.cpp
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;


vector<string> greatestScore(string str, int n) {
  // Uses remaining digits to make the biggest possible, but goes left to right ONLY
  // Does not check if you can make something bigger down the line
  // Example: 10391242265 returns 103|9|1|2|4|2|2|6|5| instead of 1|0|3|912|4|2|2|6|5|
  long int score = 0;
  int partSize = str.length() / n;
  int remainingDigits = 0;
  vector<string> innings;

  if (str.length() % n != 0) {
    remainingDigits = str.length() % n;
  }
 
 
  int start = 0;
 
  string inning = "";
  if (str.length() > 9) {
    // More than 9 digits
    // Overhanging digits that can formulate bigger numbers
    while (start < str.length()) {
      // Repeat until we hit the end of the string
      long int value = 0;
      int indexChange = 0;
      for (int i = 1; i <= 17; i++) {
        // max 17 digits per inning, minimum 1
        if (start + i <= str.length() && (str.length() - (start+i) >= (8 - innings.size()))) {
          // If we don't go over the strenght length and us taking i amount of digits doesn't leave us with not enough digits to fill
          // the rest of the innings
          // Then, we grab that substring and see if the value is greater than what we grabbed last time
          inning = str.substr(start, i);
          if (stol(inning) > value) {
            // if it is, adjust value and index  
            value = stol(inning);
            indexChange = i;
          }
        }
      }
      // Push the full inning and change the current index spot by size of the inning string
      start += indexChange;
      innings.push_back(inning);
    }
  }
  else {
    // 9 digits (minimum specified by Blythe)
    // Evenly split 1 digit per inning
    for (int i = 0; i < 9; i++) {
      string inning = str.substr(i,1);
      innings.push_back(inning);
    }
  }
  
  return innings;
}


int main(int argc, char* argv[])
{
  /* 
    Solution Idea 1:
    Find the length of the string, modulo 9, the remainder is the biggest substring of *consecutive numbers* 
     - contains a max of 17 digits, which with mod 9 that shouldn't be an issue.
    So we get something like 8 normal innings, 1 explosive inning
      - Doesn't work, because it doesn't account for some edge cases

    Solution Idea 2:
    Find the length of the string: first divide by 17 - this will represent the number of innings that we will have 
    the most digits. Pull out the biggest number of 17 digits long and adjust the string for X amounts of times.
    THEN, modulo by 9 which will represent how many more digits one inning will have. The rest can be size one

    Solution Idea 3:
    Knapsack - doesnt work cause no value table for corresponding positions etc

    Solution Idea 4:
    Divide by 9, see how many digits per inning. Mod by 9 to see how many additional digits
    This could be most feasible
  */
  string scores = argv[1];
  long int score = 0;
  vector<string> innings = greatestScore(scores, 9);

  for (int i = 0; i < innings.size(); i++) {
    score += stol(innings.at(i));

    cout << innings.at(i);

    if (i != innings.size()-1)
      cout << "|";
    else
      cout << endl;
  }

  cout << "Total Score: " << score << endl;
  return 0;
}
