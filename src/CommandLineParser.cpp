#include "CommandLineParser.h"
using namespace std;

inline vector<string> split_string(string str, const char tok) {
	vector<string> tokens;

	char* strDup = strdup(str.c_str());
	char* begin = strtok(strDup, &tok);
	while (begin) {
		tokens.push_back(string(begin));
		begin = strtok(NULL, &tok);
	}
	return tokens;
}


void CommandLineParser::setupOptions()
{
	desc.add_options()
		("source,s", po::value<string>()->required(), "Comma delimited list of source directories")
		("dest,d", po::value<string>()->required(), "The path of the destination folder")
		("types,t", po::value<string>()->required(), "Comma delimited list of file types to be copied")
		("move,m", po::value<int>()->default_value(0), "If the files should be moved, rather than copied");

}

void CommandLineParser::parse(const int argc, char* argv[])
{
	try {
		po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
		po::notify(vm);
	}
	catch (exception& e) {
		cout << e.what() << endl;
		cout << desc << endl;
		getchar();
		exit(-1);
	}
}

vector<string> CommandLineParser::getSourcePaths()
{
	string pathString = vm["source"].as<string>();
	return split_string(pathString, ',');
}

string CommandLineParser::getDestPath()
{
	return vm["dest"].as<string>();
}

bool CommandLineParser::needMove()
{
	int moveOption = vm["move"].as<int>();
	return moveOption == 1;
}

vector<string> CommandLineParser::getFileTypes()
{
	string fileTypeString = vm["types"].as<string>();
	return split_string(fileTypeString, ',');
}

CommandLineParser::CommandLineParser(const int argc, char** argv)
{
	setupOptions();
	parse(argc, argv);

}


CommandLineParser::~CommandLineParser()
{
}
