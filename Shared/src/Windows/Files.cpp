#include "stdafx.h"
#include "Files.hpp"
#include "Path.hpp"
#include "Log.hpp"
#include "List.hpp"

static Vector<FileInfo> _ScanFiles(const String& rootFolder, String extFilter, bool recurse, bool* interrupt)
{
	Vector<FileInfo> ret;
	if(!Path::IsDirectory(rootFolder))
	{
		Logf("Can't run ScanFiles, \"%s\" is not a folder", Logger::Warning, rootFolder);
		return ret;
	}

	// List of paths to process, subfolders are getting added to this list
	List<String> folderQueue;
	folderQueue.AddBack(rootFolder);

	bool filterByExtension = !extFilter.empty();
	extFilter.TrimFront('.'); // Remove possible leading dot

	// Recursive folder search
	while(!folderQueue.empty() && (!interrupt || !*interrupt))
	{
		String searchPath = folderQueue.front();
		folderQueue.pop_front();

		String searchPathWildcard = searchPath + "\\*";
		WIN32_FIND_DATAA findData;
		HANDLE searchHandle = FindFirstFileA(*searchPathWildcard, &findData);
		if(searchHandle == INVALID_HANDLE_VALUE)
			continue;

		String currentfolder;
		do
		{
			String filename = findData.cFileName;
			/// TODO: Ask windows why
			if(filename == ".")
				continue;
			if(filename == "..")
				continue;

			FileInfo info;
			info.fullPath = Path::Normalize(searchPath + Path::sep + filename);
			info.lastWriteTime = ((uint64)findData.ftLastWriteTime.dwHighDateTime << 32) | (uint64)findData.ftLastWriteTime.dwLowDateTime;
			info.type = FileType::Regular;

			if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if(recurse)
				{
					// Visit sub-folder
					folderQueue.AddBack(info.fullPath);
				}
				else if(!filterByExtension)
				{
					info.type = FileType::Folder;
					ret.Add(info);
				}
			}
			else
			{
				// Check file
				if(filterByExtension)
				{
					String ext = Path::GetExtension(filename);
					if(ext == extFilter)
					{
						ret.Add(info);
					}
				}
				else
				{
					ret.Add(info);
				}
			}
		} while(FindNextFileA(searchHandle, &findData) && (!interrupt || !*interrupt));

		FindClose(searchHandle);
	}

	return move(ret);
}

Vector<FileInfo> Files::ScanFiles(const String& folder, String extFilter /*= String()*/, bool* interrupt)
{
	return _ScanFiles(folder, extFilter, false, interrupt);
}
Vector<FileInfo> Files::ScanFilesRecursive(const String& folder, String extFilter /*= String()*/, bool* interrupt)
{
	return _ScanFiles(folder, extFilter, true, interrupt);
}
