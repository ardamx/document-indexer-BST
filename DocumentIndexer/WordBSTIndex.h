#pragma once

#include <algorithm>
#include <iostream>
#include <queue>
#include <functional>

#include "WordBTNode.h"

class WordBSTIndex
{
public:
	WordBSTIndex() : root(nullptr) {}

	WordBTNode* root;

	//MAIN FUNCTIONS
	void Insert(std::string word, std::string filename);
	void SelectTop10Asc(); 	// For BST implementation, converted to recursion
	void SelectTop10Desc(); // For BST implementation, converted to recursion
	void SelectWhere(WordBTNode* r, std::string word);

	//SUB FUNCTIONS
	bool Contains(WordBTNode* r, std::string word, std::string filename);

	// For BST implementation, converted to recursion
	void recursiveDesc(std::priority_queue<std::tuple<int, std::string>, std::vector<std::tuple<int, std::string>>, std::greater<>>& top10pq, WordBTNode* current);
	void recursiveAsc(std::priority_queue<std::tuple<int, std::string>>& top10pq, WordBTNode* current);

};