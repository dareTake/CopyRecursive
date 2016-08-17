#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include "boost/program_options.hpp"
#include <iostream>
#include <vector>


using namespace std;
namespace po = boost::program_options;

class CommandLineParser final
{
private:
	po::options_description desc{ "Options" };
	po::positional_options_description pdesc;
	po::variables_map vm;

	// setup command line options
	void setupOptions();
	// parse command line
	void parse(const int argc, char* argv[]);

public:
	CommandLineParser(const int argc, char** argv);
	~CommandLineParser();

	// source paths to copy from
	vector<string> getSourcePaths();
	// destination path to copy to
	string getDestPath();
	// should the files be moved ?
	bool needMove();
	// types of files to be copied
	vector<string> getFileTypes();
};

#endif
