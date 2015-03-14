#ifndef SXDB_H
#define SXDB_H

#include <tinyxml2.h>
#include <vector>
#include <string>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

namespace Sxdb
{
using namespace tinyxml2;
using namespace std;

class DbDoc
{
public:
	int safe(string path);
	int load(string path);

	void addData(string name, int value);
	int setData(string name, int value);
	int getIntData(string name);
	int removeIntData(string name);

	void addData(string name, double value);
	int setData(string name, double value);
	double getDoubleData(string name);
	int removeDoubleData(string name);

	void addData(string name, string value);
	int setData(string name, string value);
	string getStringData(string name);
	int removeStringData(string name);

	void addIntArray(string name, int size);
	int setIntArrayData(string name, vector<int> value);
	vector<int> getIntArrayData(string name);
	int removeIntArrayData(string name);

	void addDoubleArray(string name, int size);
	int setDoubleArrayData(string name, vector<double> value);
	vector<double> getDoubleArrayData(string name);
	int removeDoubleAarryData(string name);

	void addStringArray(string name, int size);
	int setStringArrayData(string name, vector<string> value);
	vector<string> getStringArrayData(string name);
	int removeStringArrayData(string name);

protected:
	vector<int> intData;
	vector<string> intDataName;

	vector<double> doubleData;
	vector<string> doubleDataName;

	vector<string> stringData;
	vector<string> stringDataName;

	vector<vector<int>> intArrayData;
	vector<string> intArrayDataName;

	vector<vector<double>> doubleArrayData;
	vector<string> doubleArrayDataName;

	vector<vector<string>> stringArrayData;
	vector<string> stringArrayDataName;

	int findNameId(vector<string> list, string target);
};
};

#endif