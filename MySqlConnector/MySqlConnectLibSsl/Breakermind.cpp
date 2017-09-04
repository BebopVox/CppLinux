#include "Breakermind.h"
#include <iostream>
// file
#include <fstream>

using namespace std;

Breakermind::Breakermind()
{
	cout << "Class constructor works ..." << endl;
}

void Breakermind::SaveToFile(const char* val){
	ofstream myfile;
  	// myfile.open ("email.txt", ios::out | ios::app | ios::binary);
  	myfile.open ("m2.txt", ios::out | ios::app );
  	myfile << val << " Writing this to a file.Writing this to a file.Writing this to a file. \n " << val << endl;
  	myfile.close();
  	cout << val << " Class methods works File has been saved!\n";  	  	
}
