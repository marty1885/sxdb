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
	DbDoc doc;
	doc.addData("Int1",0);
	doc.addData("Int2",12);
	doc.addData("Double1",123.2);
	doc.addData("Str1","Hello World");
	doc.addIntArray("IntArr1",4);
	doc.addDoubleArray("DoubleArr1",7);
	doc.addStringArray("StrArr1",3);

	cout << "Int1 = " << doc.getIntData("Int1") << endl
		<< "Double1 = " << doc.getDoubleData("Double1") << endl
		<< "Str1 = " << doc.getStringData("Str1") << endl
		<< "IntArr1.size() = " << doc.getIntArrayData("IntArr1").size() << endl 
		<< "DoubleArr1.size() = " << doc.getDoubleArrayData("DoubleArr1").size() << endl
		<< "StrArr1.size() = " << doc.getStringArrayData("StrArr1").size() << endl;

	doc.safe("testDoc.xml");

	DbDoc doc2;
	doc2.load("testDoc.xml");

	cout << "========doc2========" << endl;
	cout << "Int1 = " << doc2.getIntData("Int1") << endl
		<< "Double1 = " << doc2.getDoubleData("Double1") << endl
		<< "Str1 = " << doc2.getStringData("Str1") << endl
		<< "IntArr1.size() = " << doc2.getIntArrayData("IntArr1").size() << endl 
		<< "DoubleArr1.size() = " << doc2.getDoubleArrayData("DoubleArr1").size() << endl
		<< "StrArr1.size() = " << doc2.getStringArrayData("StrArr1").size() << endl;


	return 0;
}