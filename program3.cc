/*
 * Filename      program3.cc
 * Date          2/28/2020
 * Author        Noah Sims
 * Email         ngs170000@utdallas.edu
 * Course        CS 3377.501 Spring 2020
 * Version       1.0
 * Copyright 2019, All Rights Reserved
 *
 * Description
 *
 *     This program utilizes the gawk program to sum the columns of numbers from a given text file
 */

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "prog3Header.h"

using namespace std;

#define BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
  const string GAWK_WD = "/home/011/n/ng/ngs170000/CS3377/assignments/hw3/bin/gawk";
  FILE* gawkOutput;
  char tmpbuffer[BUFFER_SIZE];
  char* line_p;

  string gawkcmd1 = GAWK_WD + " --version";
  string gawkcmd2 = GAWK_WD + " -f gawk.code numbers.txt";

  cout << endl;
  cout << "gawk at: " << GAWK_WD << endl;
  cout << "Shellcmd1: " << gawkcmd1 << endl;
  cout << "Shellcmd2: " << gawkcmd2 << endl;

  gawkOutput = popen(gawkcmd1.c_str(), "r");
  
  if(!gawkOutput)
    return -1;

  cout << endl;
  cout << "The first call to gawk returned:" << endl;
  cout << endl;

  line_p = fgets(tmpbuffer, BUFFER_SIZE, gawkOutput);
  while(line_p != NULL)
  {
    printf("\t%s", line_p);
    line_p = fgets(tmpbuffer, BUFFER_SIZE, gawkOutput);
  }
  
  pclose(gawkOutput);

  gawkOutput = popen(gawkcmd2.c_str(), "r");

  if(!gawkOutput)
    return -1;

  cout << endl;
  cout << "The second call to gawk returned: ";

  line_p = fgets(tmpbuffer, BUFFER_SIZE, gawkOutput);
  if(line_p != NULL)
  {
    cout << line_p << endl;
    int nums[2];
    parseNums(line_p, nums, 2);
    cout << "The sum of Column 1 is: " << nums[0] << endl;
    cout << "The sum of Column 4 is: " << nums[1] << endl;
    int sum = nums[0] + nums[1];
    cout << "The sum of the two numbers is: " << sum << endl;
  }

  pclose(gawkOutput);

  cout << endl;

  return 0;
}
