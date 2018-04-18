#include "readFile.h"

readFile::readFile()
{

}

vector<int>readFile::readIn(int filePosition)
{
	vector<int>vert;
	string  path;
	
	path = "TreeFiles/Tree0" + to_string(filePosition) + ".txt";
	//std::cout << path<<std::endl;
	ifstream file(path);
	int counter = 0;
	if (file.is_open()) {
		//while (!file.eof()) {
			std::getline(file, line);
			//vert.push_back(stoi(line));
			//counter++;
		//}
	}
	file.close();
	int start = 0;
	int pos = 100;
	while (pos > 0)
	{

		pos = line.find(",");
		string sub = line.substr(start, pos);
		line = line.substr(pos+1,line.length());
		vert.push_back(stoi(sub));
		counter++;
		//cout << sub;
	}
	
	/*for (int i = 0; i < counter; i++)
	{
		std::cout << vert[i] << std::endl;
	}*/
	return vert;
}