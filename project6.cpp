//===============================================================================================
//  Hyeonseo Lee
//  Oct 11, 2024
//  project6.cpp
//  This program is designed to help scuba divers find the optimal combination of weights to counteract buoyancy during dives. Given an inventory of weights and a desired weight total, the program aims to identify two weights whose sum comes closest to the desired weight.
//===============================================================================================
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
vector<int> findCloestWeight(int desiredWeight, int weight[], int size);
void selectionSort (int array[], int size);
vector<int> findSingleWeight(int desiredWeight, int weight[], int size);
vector<int> findTwoWeights(int desiredWeight, int weight[], int size);
vector<int> findThreeWeights(int desiredWeight, int weight[], int size);
vector<int> findCloestPair(int desiredWeight, int weight[], int size);
void printResult (int desiredWeight, vector<int> result);

int main()
{
  int desiredWeight;
  cin >> desiredWeight;
  if ((desiredWeight >= INT_MAX) || (desiredWeight <= 0))
  {
    cout << "The value of the desired weight is invalid." << endl;
    return 1;
  }
  int size = 0;
  cin >> size;
  if (size <= 0)
  {
    cout << "The size of the array is invalid" << endl;
    return 1;
  }
  
  int weight[size];
  
  for (int i = 0; i < size; i++)
  {
    cin >> weight[i];
    if (weight[i] <= 0)
    {
      cout << "The value of the weight is invalid" << endl;
      return 1;
    }
  }
  
  selectionSort(weight, size);
  
  vector<int> result;
  result = findCloestWeight(desiredWeight, weight, size);
  printResult(desiredWeight, result);
  return 0;

}

//===============================================================================================
//  selectionSort
//  This function sorts the array by using selection sort method. During each iteration, it finds the smallest number in the unsorted portion of the array and swaps it with the current position. This process repeats until the array is fully sorted.
//  Parameters:
//    array[]: an array of n integers. Values in the array are all > 0.
//    size: the size of the array where size > 0.
//  Return Value:
//    The array that is sorted
//===============================================================================================
void selectionSort (int array[], int size)
{
  int minIndex;
  int minValue;
  
  for (int start = 0; start < (size - 1); start++)
  {
    minIndex = start;
    minValue = array[start];
    for (int index = start + 1; index < size; index++)
    {
      if (array[index] < minValue)
      {
        minValue = array[index];
        minIndex = index;
      }
    }
    swap(array[minIndex], array[start]);
  }
}

//===============================================================================================
// findCloestWeight
// This function searches for a combination of weights that most closely matches a desired weight.
// Parameters:
//    desiredWeight: the value that represents the target weight where desiredWeight > 0
//    weight[]: a collection of integers representing the available weights in the dive shop's inventory
//    size: the size of the weight[] array where size > 0
// Return value:
//    It returns an integer vector containing a combination of weights that most closely matches the desired weight.
//===============================================================================================
vector<int> findCloestWeight(int desiredWeight, int weight[], int size)
{
  vector<int> result;
  result = findSingleWeight(desiredWeight, weight, size);
  if (result.size() == 0)
  {
    result = findTwoWeights(desiredWeight, weight, size);
    if (result.size() == 0)
    {
      result = findThreeWeights(desiredWeight, weight, size);
      if (result.size() == 0)
      {
        result = findCloestPair(desiredWeight, weight, size);
      }
    }
  }
  return result;
}

//===============================================================================================
// findsingleWeight
// This function is designed to find the weights from an inventory that exactly matches a specified desired weight.
// Parameters:
//    desiredWeight: the value that represents the target weight where desiredWeight > 0
//    weight[]: a collection of integers representing the available weights in the dive shop's inventory
//    size: the size of the weight[] array where size > 0
// Return value:
//  It returns the integer vector containing a matching value if one is found; otherwise, it will return an empty vector.
//===============================================================================================
vector<int> findSingleWeight(int desiredWeight, int weight[], int size)
{
  vector<int> result;
  for (int i = 0; i < size; i++)
  {
    if (desiredWeight == weight[i])
    {
      result.push_back(weight[i]);
      return result;
    }
  }
  return result;
}

//===============================================================================================
// findTwoWeight
// This function is designed to find the optimal combination of two weights from an inventory that closely matches a specified desired weight.
// Parameters:
//    desiredWeight: the value that represents the target weight where desiredWeight > 0
//    weight[]: a collection of integers representing the available weights in the dive shop's inventory
//    size: the size of the weight[] array where size > 0
// Return value:
//  It returns the integer vector containing the two matching values if one is found; otherwise, it will return an empty vector.
//===============================================================================================
vector<int> findTwoWeights(int desiredWeight, int weight[], int size)
{
  vector<int> combination;
  int posL = 0;
  int posR = size - 1;
  while (posL < posR)
  {
    int temp = weight[posL] + weight[posR];
    if (temp == desiredWeight)
    {
      combination.push_back(weight[posL]);
      combination.push_back(weight[posR]);
      posL++;
      posR--;
    }
    else if (temp > desiredWeight)
    {
      posR--;
    }
    else if(temp < desiredWeight)
    {
      posL++;
    }
  }
  vector<int> result;
  if (!combination.empty())
  {
    int absoluteDiff = -1;
    int minDiff = INT_MAX;
    for(int i = 0; i < combination.size(); i += 2)
    {
      absoluteDiff = abs(combination.at(i) - combination.at(i+1));
      if (absoluteDiff < minDiff)
      {
        minDiff = absoluteDiff;
        result.clear();
        result.push_back(combination.at(i));
        result.push_back(combination.at(i+1));
      }
    }
  }
  return result;
}

//===============================================================================================
// findThreeWeight
// This function is designed to find the optimal combination of three weights from an inventory that closely matches a specified desired weight.
// Parameters:
//    desiredWeight: the value that represents the target weight where desiredWeight > 0
//    weight[]: a collection of integers representing the available weights in the dive shop's inventory
//    size: the size of the weight[] array where size > 0
// Return value:
//  It returns the integer vector containing the three matching values if one is found; otherwise, it will return an empty vector.
//===============================================================================================
vector<int> findThreeWeights(int desiredWeight, int weight[], int size)
{
  vector<int> result;
  vector<int> combination;
  for (int i = 0; i < size - 2; i++)
  {
    int posL = i + 1;
    int posR = size - 1;
    while (posL < posR)
    {
      int temp = weight[i] + weight[posL] + weight[posR];
      if (temp == desiredWeight)
      {
        combination.push_back(weight[i]);
        combination.push_back(weight[posL]);
        combination.push_back(weight[posR]);
        return combination;
      }
      else if (temp > desiredWeight)
      {
        posR--;
      }
      else if (temp < desiredWeight)
      {
        posL++;
      }
    }
  }
  return combination;
}

//===============================================================================================
// findCloestPair
// This function returns an integer vector containing two weights from a weight array whose sum is closest to a desired weight.
// Parameters:
//    desiredWeight: the value that represents the target weight where desiredWeight > 0
//    weight[]: a collection of integers representing the available weights in the dive shop's inventory
//    size: the size of the weight[] array where size > 0
// Return value:
//  It returns the integer vector containing the two cloest matching values.
//===============================================================================================
vector<int> findCloestPair(int desiredWeight, int weight[], int size)
{
  vector<int> result;
  int cloestDiff = INT_MAX;
  
  int posL = 0;
  int posR = size - 1;
  
  while (posL < posR)
  {
    int sum = weight[posL] + weight[posR];
    int diff = abs(sum - desiredWeight);
    
    if (diff < cloestDiff)
    {
      result.clear();
      cloestDiff = diff;
      result.push_back(weight[posL]);
      result.push_back(weight[posR]);
    }
    
    if (sum < desiredWeight)
    {
      posL++;
    }
    else
    {
      posR--;
    }
  }
  return result;
}

//===============================================================================================
// printResult
// This function prints the values of vector
// Parameters:
//    desiredWeight: the value that represents the target weight where desiredWeight > 0
//    result: the int vector which contains the result values of weights
//===============================================================================================
void printResult (int desiredWeight, vector<int> result)
{
  cout << desiredWeight << endl;
  int sum = 0;
  for (int i = 0; i < result.size(); i++)
  {
    cout << result.at(i);
    if (i < result.size() - 1)
    {
      cout << ", ";
    }
    sum += result.at(i);
  }
  cout << endl << sum << endl;
}
