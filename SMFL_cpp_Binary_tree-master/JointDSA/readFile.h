#pragma once
#include <iostream>
#include <fstream>
#include<vector>
#include<string>
using namespace std;

class readFile
{
private:
	vector<int>vertecies;
	string line;
public:
	readFile();
	vector<int> readIn(int filePosition);
};