#include "RecursiveCopier.h"




void RecursiveCopier::checkPathExists(const string & path, const bool isDirectory = false) const
{
	if (!fl::exists(path)) {
    cout << "Path " << path << "does not exist" << endl;
		throw  path + " does not exist";
	}

	if (isDirectory) {
		if (!fl::is_directory(path)) {
			throw path + " is not a directory";
		}
	}
}

RecursiveCopier::RecursiveCopier(const vector<string>& srcPaths, const string & destPath, const vector<string>& fileTypes)
	: srcPaths(srcPaths), destPath(destPath), fileTypes(fileTypes)
{
}

long RecursiveCopier::run()
{
	long filesNum = 0;
	// check if valid src & dest paths
	checkPathExists(destPath, true);
	for (const auto& path : srcPaths)  
		checkPathExists(path, true); 

	// get all files in directory
	cout << "Enumerating files..." << endl;
	list<fl::path> files;
	for (const auto& srcPath : srcPaths)  
		getRecursiveContents(srcPath,files); 

	// filter file list with given types
	/*
	remove_if(files.begin(), files.end(), [this](auto file) -> bool {
		auto foundExtensionIndex = find_if(fileTypes.cbegin(), fileTypes.cend(), 
			[file](auto fileType) -> bool {
				return file.has_extension() ? file.extension().string() == fileType : false;
			});
		return foundExtensionIndex != fileTypes.end();
	});
	*/

	// copy files
	cout << "Copying files..." << endl;
	ud::random_generator rndGen;
	ud::uuid uuid;

	for (const auto& file : files) {
		fl::path destDir = destPath;
		fl::path destFile = destDir / file.filename();

		// if file exist and same size, duplicate, so ignore
		if (fl::exists(destFile) && fl::file_size(file) == fl::file_size(destFile))
			continue;

		// get unique name in case of already existing file
		//while (fl::exists(destFile)) {
			cout << destFile << " already exists";
			//uuid = rndGen();
			//destFile = destDir / ud::to_string(uuid);
			//destFile.replace_extension(file.extension());
      if (fl::exists(destFile))
        destFile = getNextName(destFile);
			cout << " renaming to " << destFile << endl;
      //}

		// copy file
		try {
			fl::copy_file(file, destFile);
			filesNum++;
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}
	return filesNum;
}

fl::path RecursiveCopier::getNextName(fl::path curFileName) const
{
  auto orgFileName = curFileName.stem().string();
  auto ext = curFileName.extension();
  auto parentDir = curFileName.parent_path();
  auto newPath = curFileName;
  stringstream newName;
  int index = 1;

  while(fl::exists(newPath))
  {
    newName.str("");
    newName.clear();
    newName << orgFileName << "_" << index;
    newPath = parentDir / newName.str();
    newPath.replace_extension(ext);
    index++;
  }
  return newPath;
}

void RecursiveCopier::getRecursiveContents(const fl::path dirp, list<fl::path>& dirItems,
		bool filterExts) const
{
	assert(fl::is_directory(dirp));

		auto end = fl::directory_iterator();
		for(auto entry = fl::directory_iterator(dirp); entry != end; entry++)
		{
			if (fl::is_regular_file(*entry)) {

				// don't check for file types
				if (!filterExts) {
					dirItems.push_back(*entry);
					continue;
				}

				// otherwise,
				fl::path file(*entry);

				if (file.has_extension()) {
					// get ext
					string fileExt = file.extension().string();
					fileExt = fileExt.substr(1, fileExt.length());
					// case insensitive compare with given filetypes 
					auto extIndex = find_if(fileTypes.cbegin(), fileTypes.cend(), [&fileExt] (const string type) -> bool {
						string typeLower(type);
						transform(typeLower.begin(), typeLower.end(), typeLower.begin(), ::tolower);

						string fileExtLower(fileExt);
						transform(fileExtLower.begin(), fileExtLower.end(), fileExtLower.begin(), ::tolower);

						return typeLower == fileExtLower;
					});
					if (extIndex != fileTypes.end()) {
						dirItems.push_back(file);
					}
				}
			}
			// call recursively
			else if (fl::is_directory(*entry))
				getRecursiveContents(*entry, dirItems,filterExts);
		}
}

RecursiveCopier::~RecursiveCopier()
{
}
