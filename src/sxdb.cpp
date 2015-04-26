#include <sxdb.h>

#include <vector>
#include <string>
#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

using namespace Sxdb;
using namespace tinyxml2;
using namespace std;

int DbDoc::save(string path)
{
	XMLDocument doc;
	XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"");

	doc.LinkEndChild(decl);
	XMLElement *rootElement = doc.NewElement("XSDB");
	doc.LinkEndChild(rootElement);

	int size = intData.size();
	for(int i=0;i<size;i++)
	{
		char str[20] = {0};
		XMLElement *element = doc.NewElement("int");
		element->SetAttribute("name",intDataName[i].c_str());
		sprintf(str,"%d",intData[i]);
		element->SetText(str);

		rootElement->LinkEndChild(element);
	}

	size = doubleData.size();
	for(int i=0;i<size;i++)
	{
		char str[20] = {0};
		XMLElement *element = doc.NewElement("double");
		element->SetAttribute("name",doubleDataName[i].c_str());
		sprintf(str,"%lf",doubleData[i]);
		element->SetText(str);

		rootElement->LinkEndChild(element);
	}

	size = stringData.size();
	for(int i=0;i<size;i++)
	{
		XMLElement *element = doc.NewElement("string");
		element->SetAttribute("name",stringDataName[i].c_str());
		element->SetText(stringData[i].c_str());

		rootElement->LinkEndChild(element);
	}

	size = intArrayData.size();
	for(int i=0;i<size;i++)
	{
		XMLElement *element = doc.NewElement("int-array");
		element->SetAttribute("name",intArrayDataName[i].c_str());
		vector<int> &vec = intArrayData[i];
		int arrSize = vec.size();
		for(int q = 0;q<arrSize;q++)
		{
			char str[20] = {0};
			XMLElement *elem = doc.NewElement("value");
			sprintf(str,"%d",q);
			elem->SetAttribute("id",str);
			sprintf(str,"%d",vec[q]);
			elem->SetText(str);

			element->LinkEndChild(elem);
		}

		rootElement->LinkEndChild(element);
	}

	size = doubleArrayData.size();
	for(int i=0;i<size;i++)
	{
		XMLElement *element = doc.NewElement("double-array");
		element->SetAttribute("name",doubleArrayDataName[i].c_str());
		vector<double> &vec = doubleArrayData[i];
		int arrSize = vec.size();
		for(int q = 0;q<arrSize;q++)
		{
			char str[20] = {0};
			XMLElement *elem = doc.NewElement("value");
			sprintf(str,"%d",q);
			elem->SetAttribute("id",str);
			sprintf(str,"%f",vec[q]);
			elem->SetText(str);

			element->LinkEndChild(elem);
		}

		rootElement->LinkEndChild(element);
	}
	for(int i=0;i<size;i++)
	{
		XMLElement *element = doc.NewElement("string-array");
		element->SetAttribute("name",stringArrayDataName[i].c_str());
		vector<string> &vec = stringArrayData[i];
		int arrSize = vec.size();
		for(int q = 0;q<arrSize;q++)
		{
			char str[20] = {0};
			XMLElement *elem = doc.NewElement("value");
			sprintf(str,"%d",q);
			elem->SetAttribute("id",str);
			elem->SetText(vec[q].c_str());

			element->LinkEndChild(elem);
		}

		rootElement->LinkEndChild(element);
	}


	doc.SaveFile(path.c_str());
	return 1;
}

int DbDoc::load(string path)
{
	XMLDocument doc;
	doc.LoadFile(path.c_str());
	XMLElement *rootElement = doc.RootElement();
	if(rootElement == NULL)
	{
		cout << "SXDB Failed to load data." << endl;
		return 0;
	}
	XMLElement* element = rootElement->FirstChildElement();
	while(element != NULL)
	{
		if(element->Name() == string("int"))
		{
			intData.push_back(atoi(element->GetText()));
			intDataName.push_back(element->FirstAttribute()->Value());
		}
		else if(element->Name() == string("double"))
		{
			doubleData.push_back(atof(element->GetText()));
			doubleDataName.push_back(element->FirstAttribute()->Value());
		}
		else if(element->Name() == string("string"))
		{
			const char* cstr = element->GetText();
			string str;
			if(cstr == NULL)
				str.append("");
			else
				str.append(element->GetText());
			stringData.push_back(str);
			stringDataName.push_back(element->FirstAttribute()->Value());
		}
		else if(element->Name() == string("int-array"))
		{
			intArrayDataName.push_back(element->FirstAttribute()->Value());
			vector<int> vec;
			XMLElement *elem = element->FirstChildElement();
			while(elem != NULL)
			{
				//XXX:They have to be inorder
				vec.push_back((atoi(elem->GetText())));
				elem = elem->NextSiblingElement();
			}
			intArrayData.push_back(vec);
		}
		else if(element->Name() == string("double-array"))
		{
			doubleArrayDataName.push_back(element->FirstAttribute()->Value());
			vector<double> vec;
			XMLElement *elem = element->FirstChildElement();
			while(elem != NULL)
			{
				//XXX:They have to be inorder
				vec.push_back((atof(elem->GetText())));
				elem = elem->NextSiblingElement();
			}
			doubleArrayData.push_back(vec);
		}
		else if(element->Name() == string("string-array"))
		{
			stringArrayDataName.push_back(element->FirstAttribute()->Value());
			vector<string> vec;
			XMLElement *elem = element->FirstChildElement();
			while(elem != NULL)
			{
				//XXX:They have to be inorder
				if(elem->GetText() == NULL)
					vec.push_back("");
				else
					vec.push_back(elem->GetText());
				elem = elem->NextSiblingElement();
			}
			stringArrayData.push_back(vec);
		}
		element = element->NextSiblingElement();
	}

	return 1;
}

void DbDoc::addData(string name, int value)
{
	intData.push_back(value);
	intDataName.push_back(name);
}

int DbDoc::setData(string name, int value)
{
	int index = findNameId(intDataName,name);
	if(index == -1)
		return -1;
	intData[index] = value;
	return 1;
}

int DbDoc::getIntData(string name)
{
	int index = findNameId(intDataName,name);
	if(index == -1)
		return -1;
	return intData[index];
}

int DbDoc::removeIntData(string name)
{
	int index = findNameId(intDataName,name);
	if(index == -1)
		return -1;
	intData.erase(intData.begin() + index);
	return 1;
}


void DbDoc::addData(string name, double value)
{
	doubleData.push_back(value);
	doubleDataName.push_back(name);
}

int DbDoc::setData(string name, double value)
{
	int index = findNameId(doubleDataName,name);
	if(index == -1)
		return  0;
	doubleData[index] = value;
	return 1;
}

double DbDoc::getDoubleData(string name)
{
	int index = findNameId(doubleDataName,name);
	if(index == -1)
		return  -1;
	return doubleData[index];
}

int DbDoc::removeDoubleData(string name)
{
	int index = findNameId(doubleDataName,name);
	if(index == -1)
		return -1;
	doubleData.erase(doubleData.begin() + index);
	return 1;
}

void DbDoc::addData(string name, string value)
{
	stringData.push_back(value);
	stringDataName.push_back(name);
}

int DbDoc::setData(string name, string value)
{
	int index = findNameId(stringDataName,name);
	if(index == -1)
		return  -1;
	stringData[index] = value;
	return 1;
}

string DbDoc::getStringData(string name)
{
	int index = findNameId(stringDataName,name);
	if(index == -1)
		return  "String Dosn't exist";
	return stringData[index];
}

int DbDoc::removeStringData(string name)
{
	int index = findNameId(stringDataName,name);
	if(index == -1)
		return -1;
	stringData.erase(stringData.begin() + index);
	return 1;
}

void DbDoc::addIntArray(string name, int size)
{
	vector<int> vec(size);
	intArrayData.push_back(vec);
	intArrayDataName.push_back(name);
}

int DbDoc::setIntArrayData(string name,vector<int> value)
{
	int index = findNameId(intArrayDataName,name);
	if(index == -1)
		return  -1;
	intArrayData[index] = value;
	return 1;
}

vector<int> DbDoc::getIntArrayData(string name)
{
	int index = findNameId(intArrayDataName,name);
	if(index == -1)
		return  vector<int>(0);
	return intArrayData[index];
}

int DbDoc::removeIntArrayData(string name)
{
	int index = findNameId(intArrayDataName,name);
	if(index == -1)
		return -1;
	intArrayData.erase(intArrayData.begin() + index);
	return 1;
}

void DbDoc::addDoubleArray(string name, int size)
{
	vector<double> vec(size);
	doubleArrayData.push_back(vec);
	doubleArrayDataName.push_back(name);
}

int DbDoc::setDoubleArrayData(string name,vector<double> value)
{
	int index = findNameId(doubleArrayDataName,name);
		return  -1;
	doubleArrayData[index] = value;
	return 1;
}

vector<double> DbDoc::getDoubleArrayData(string name)
{
	int index = findNameId(doubleArrayDataName,name);
	if(index == -1)
		return  vector<double>(0);
	return doubleArrayData[index];
}

int DbDoc::removeDoubleAarryData(string name)
{
	int index = findNameId(doubleArrayDataName,name);
	if(index == -1)
		return -1;
	doubleArrayData.erase(doubleArrayData.begin() + index);
	return 1;
}

void DbDoc::addStringArray(string name, int size)
{
	vector<string> vec(size);
	stringArrayData.push_back(vec);
	stringArrayDataName.push_back(name);
}

int DbDoc::setStringArrayData(string name,vector<string> value)
{
	int index = findNameId(stringArrayDataName,name);
	if(index == -1)
		return  -1;
	stringArrayData[index] = value;
	return 1;
}

vector<string> DbDoc::getStringArrayData(string name)
{
	int index = findNameId(stringArrayDataName,name);
	if(index == -1)
		return  vector<string>(0);
	return stringArrayData[index];
}

int DbDoc::removeStringArrayData(string name)
{
	int index = findNameId(stringArrayDataName,name);
	if(index == -1)
		return -1;
	stringArrayData.erase(stringArrayData.begin() + index);
	return 1;
}

int DbDoc::findNameId(vector<string> list, string target)
{
	int size = list.size();
	int index = -1;
	for(int i=0;i<size;i++)
	{
		if(list[i] == target)
		{
			index = i;
			break;
		}
	}
	return index;
}
