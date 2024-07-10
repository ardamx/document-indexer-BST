#pragma once

#include <string>
#include <vector>

#include "FileIndex.h"

class WordBTNode
{
public:
	WordBTNode(std::string word, std::string filename);

	std::string Word;
	int Count;
	WordBTNode* lchild;
	WordBTNode* rchild;

	FileIndex FIndex;
};

