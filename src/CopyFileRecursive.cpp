// CopyFileRecursive.cpp : Defines the entry point for the console application.


#include "CommandLineParser.h"
#include "RecursiveCopier.h"

using namespace std;



int main(int argc, char* argv[])
{
	
	CommandLineParser parser(argc, argv);
	
	vector<string> srcPaths = parser.getSourcePaths();
	vector<string> types = parser.getFileTypes();
	string destPath = parser.getDestPath();


	RecursiveCopier copier(srcPaths, destPath, types);
	long filesCopied = copier.run();

	cout << "Total files copied: " << filesCopied << endl;

    return 0;
}

