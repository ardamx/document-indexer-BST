#include "WordBSTIndex.h"

void WordBSTIndex::Insert(std::string word, std::string filename) {
	if (Contains(root, word, filename))
	    return; // If value already exists, don't insert

	if (root == nullptr) {
		root = new WordBTNode(word, filename);
	}

	else {
		WordBTNode* r = root;
		while (r != nullptr) {
			if (r->Word == word) return;
			if (r->Word < word) {
				if (r->rchild == nullptr) {
					r->rchild = new WordBTNode(word, filename);
					break;
				}
				r = r->rchild;
			}
			else if (r->Word > word) {
				if (r->lchild == nullptr) {
					r->lchild = new WordBTNode(word, filename);
					break;
				}
				r = r->lchild;
			}
		}
	}
}

bool WordBSTIndex::Contains(WordBTNode* r, std::string word, std::string filename)
{
	if (r == nullptr) return false;

	if (r->Word == word) {
		r->Count += 1;
		r->FIndex.Insert(filename);
		return true;
	}

	if (r->Word < word)
		return WordBSTIndex::Contains(r->rchild, word, filename);
	return WordBSTIndex::Contains(r->lchild, word, filename);
}


void WordBSTIndex::SelectTop10Asc()
{
	// A max-heap to keep the smallest counts at the top
	std::priority_queue<std::tuple<int, std::string>> top10pq;
	WordBTNode* current = root;

	recursiveAsc(top10pq, current);

	std::vector<std::tuple<std::string, int>> top10;
	while (!top10pq.empty()) {
		auto [count, word] = top10pq.top();
		top10.emplace_back(word, count);
		top10pq.pop();
	}
	std::reverse(top10.begin(), top10.end());

	for (const auto& word : top10) {
		std::cout << std::get<0>(word) << ": " << std::get<1>(word) << std::endl;
	}
}

void WordBSTIndex::recursiveAsc(std::priority_queue<std::tuple<int, std::string>>& top10pq, WordBTNode* current) {
	if (current == nullptr) return;

	recursiveAsc(top10pq, current->lchild);

	top10pq.push(std::make_tuple(current->Count, current->Word));
	if (top10pq.size() > 10) {
		top10pq.pop();
	}

	recursiveAsc(top10pq, current->rchild);
}

void WordBSTIndex::SelectTop10Desc()
{
	// A min-heap to keep the largest counts at the top (with custom comparator)
	std::priority_queue<std::tuple<int, std::string>, std::vector<std::tuple<int, std::string>>, std::greater<>> top10pq;
	WordBTNode* current = root;

	std::cout << "checking..." << std::endl;
	recursiveDesc(top10pq, current);
	std::cout << "done..." << std::endl;

	std::vector<std::tuple<std::string, int>> top10;
	while (!top10pq.empty()) {
		auto [count, word] = top10pq.top();
		top10.emplace_back(word, count);
		top10pq.pop();
	}
	std::reverse(top10.begin(), top10.end());

	for (const auto& word : top10) {
		std::cout << std::get<0>(word) << ": " << std::get<1>(word) << std::endl;
	}
}

void WordBSTIndex::recursiveDesc(std::priority_queue<std::tuple<int, std::string>, std::vector<std::tuple<int, std::string>>, std::greater<>>& top10pq, WordBTNode* current) {
	if (current == nullptr) return;

	recursiveDesc(top10pq, current->lchild);

	top10pq.push(std::make_tuple(current->Count, current->Word));
	if (top10pq.size() > 10) {
		top10pq.pop();
	}

	recursiveDesc(top10pq, current->rchild);
}

void WordBSTIndex::SelectWhere(WordBTNode* r, std::string word)
{
	if (r->Word == word) {
		FileNode* f = r->FIndex.head;
		while (f != nullptr)
		{
			std::cout << f->File << std::endl;
			f = f->next;
		}
		return;
	}

	if (r->Word < word)
		return WordBSTIndex::SelectWhere(r->rchild, word);
	return WordBSTIndex::SelectWhere(r->lchild, word);

}
