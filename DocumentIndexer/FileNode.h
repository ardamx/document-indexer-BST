#pragma once

#include <string>
#include <vector>

class FileNode
{
public:
	FileNode(std::string file);

	std::string File;
	FileNode* next;
};

