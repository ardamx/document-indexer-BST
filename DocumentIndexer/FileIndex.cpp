#include "FileIndex.h"

void FileIndex::Insert(std::string file) {
	if (Contains(file))
		return; // If value already exists, don't insert

	FileNode* newNode = new FileNode(file);

	if (head == nullptr || head->File > file) {
		newNode->next = head;
		head = newNode;
	}
	else {
		FileNode* current = head;
		while (current->next != nullptr && current->next->File < file) {
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}

bool FileIndex::Contains(std::string file)
{
	FileNode* current = head;
	while (current != nullptr) {
		if (current->File == file)
			return true;
		current = current->next;
	}
	return false;
}