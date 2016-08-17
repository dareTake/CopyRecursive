#ifndef RECURSIVE_COPIER_H
#define RECURSIVE_COPIER_H

#include "boost/filesystem.hpp"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/random_generator.hpp"

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>

namespace fl = boost::filesystem;
namespace ud = boost::uuids;

using namespace std;

class RecursiveCopier
{
private:
	// source paths to copy from
	const vector<string> srcPaths;
	// type of files to copy
	const vector<string> fileTypes;
	// destination path
	const string destPath;

	// file list to copy
	vector<fl::path> filesToCopy;

	// does file exist? , also checks if directory (optional)
	void checkPathExists(const string& path, 
		const bool isDirectory) const;

  // get next filename with _(num) appended to file name
  fl::path getNextName(fl::path curFileName) const;

public:
	~RecursiveCopier();
	// init
	RecursiveCopier(const vector<string>& srcPaths, 
					const string& destPath,
					const vector<string>& fileTypes);
	// execute copy process, return files copied
	long run();

	// get files in directory recursively
	void getRecursiveContents(const fl::path dirp, 
							  list<fl::path>& dirItems,
							  bool filterExts = true) const;
};

#endif

