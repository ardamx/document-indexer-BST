#pragma once

#include <iostream>
#include "FileNode.h"

class FileIndex
{
public:
	FileIndex() : head(nullptr) {}

	FileNode* head;

	void Insert(std::string file);
	bool Contains(std::string file);
};