#include "WordBTNode.h"

WordBTNode::WordBTNode(std::string word, std::string filename)
{
	this->Word = word;
	this->Count = 1;
	this->lchild = nullptr;
	this->rchild = nullptr;

	this->FIndex.Insert(filename);
}

//WordBTNode::WordBTNode()
//{
//	this->lchild = nullptr;
//	this->rchild = nullptr;
//}