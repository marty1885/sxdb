#include <sxdb.h>

#include <vector>
#include <string>
#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

using namespace Sxdb;
using namespace std;

int main()
{
	//Cteate a SXDB document
	DbDoc doc;
	//Add some valeus
	//format "DbDoc::addData(name,value);"
	doc.addData("Int1",0);
	doc.addData("Int2",12);
	doc.addData("Double1",123.2);
	doc.addData("Str1","Hello World");

	//Add a int arrat
	//format "DbDoc::addXXXAyyar(name,size_of_array);" where XXX stands for the data type(Int/Double/String)
	doc.addIntArray("IntArr1",4);
	doc.addDoubleArray("DoubleArr1",7);
	doc.addStringArray("StrArr1",3);

	//To change data value. use setData(name,value). obvious right?
	doc.setData("Int1",99);

	//To cange a array. use getXXXArrayData(name,value)
	vector<int> vec;
	vec.resize(7);
	doc.setIntArrayData("IntArr1",vec);

	//Print what we have just create out.
	//DbDoc::getXXXData(name) is how you read the data. XXX stands for the type you want to read
	cout << "Int1 = " << doc.getIntData("Int1") << endl
		<< "Double1 = " << doc.getDoubleData("Double1") << endl
		<< "Str1 = " << doc.getStringData("Str1") << endl
		//To read arrays back. use getXXXArrayData(name); this will return a std::vector<type>.
		<< "IntArr1.size() = " << doc.getIntArrayData("IntArr1").size() << endl 
		<< "DoubleArr1.size() = " << doc.getDoubleArrayData("DoubleArr1").size() << endl
		<< "StrArr1.size() = " << doc.getStringArrayData("StrArr1").size() << endl;

	//Save it
	//DbDoc::safe(file_path");
	doc.safe("testDoc.xml");

	DbDoc doc2;
	//You can also load from a file too!!
	doc2.load("testDoc.xml");

	//Print what we have loaded.
	cout << "========doc2========" << endl;
	cout << "Int1 = " << doc2.getIntData("Int1") << endl
		<< "Double1 = " << doc2.getDoubleData("Double1") << endl
		<< "Str1 = " << doc2.getStringData("Str1") << endl
		<< "IntArr1.size() = " << doc2.getIntArrayData("IntArr1").size() << endl 
		<< "DoubleArr1.size() = " << doc2.getDoubleArrayData("DoubleArr1").size() << endl
		<< "StrArr1.size() = " << doc2.getStringArrayData("StrArr1").size() << endl;


	return 0;
}
