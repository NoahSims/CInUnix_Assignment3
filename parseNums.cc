/*
 * Filename      parseNums.cc
 * Date          2/28/2020
 * Author        Noah Sims
 * Email         ngs170000@utdallas.edu
 * Course        CS 3377.501 Spring 2020
 * Version       1.0
 * Copyright 2019, All Rights Reserved
 *
 * Description
 *
 *     This program provides the parseNums function for program3, which takes in a string containing multiple integers
 *     and breaks the string into individual int values which are placed into a given array
 */

#include <iostream>
#include <sstream>
#include "prog3Header.h"

using namespace std;

void parseNums(string str, int nums[], int numsSize)
{
  for(int i = 0; i < numsSize; i++)
  {
    int index = indexOfSpace(str);
    if(index > 0)
    {
      stringstream num(str.substr(0, index));
      num >> nums[i];
      str = str.substr(index + 1, str.length());
    }
    else
    {
      stringstream num(str);
      num >> nums[i];
    }
  }
}

int indexOfSpace(string str)
{
  for(int i = 0; i < str.length(); i++)
  {
    if(str[i] == ' ')
      return i;
  }

  return -1;
}
