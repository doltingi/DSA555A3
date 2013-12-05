#ifndef __A3_HPP__
#define __A3_HPP__

#include "A3Interfaces.hpp"
#include <array>
#include <memory>
#include <string>

class WordNode : public iWordNode {

	char value;
	bool whole;
	std::shared_ptr<WordNode> children[26];
	
public:
	
	/**
	 * Default constructor
	 *
	 */
	WordNode() : iWordNode() {
		whole = true;
		for (int i = 0; i < 26; i++) {
			children[i] = nullptr;
		}
	}

	/**
	 * Returns a pointer to a WordNode instance at the given letter. If none
	 * exist, return nullptr.
	 */
	virtual WordNode* getChild(char letter) {
		return nullptr;
	}

	/**
	 * Recursive helper function that will count the number of immediate children
	 * and add them to the total and return.
	 */
	size_t getTotalNumChildren(WordNode* wNode) const {
		if (!wNode) return 0;
		
		size_t total = 0;

		return total;
	}

	/**
	 * Returns the total number of children that this node and all of its
	 * subtrees contain.
	 */
	virtual size_t getNumChildren() const {
		size_t total = 0;
		
		return total;
	}

	/**
	 * Returns true if this instance is at the end of a whole word.
	 */
	virtual bool isWholeWord() const {
		return whole;
	}

	/**
	 * Virtual destructor that ensures correctly deallocating any memory
	 * that it is responsible for
	 */
	virtual ~WordNode() {
		for (int i = 0; i < 26; i++) {
			children[i].reset();
		}
	}

};

/**
 * This is a implementation of the iDictionaryTree interface, which is
 * responsible for holding a root iWordNode and managing the tree overall.
 */
class DictionaryTree : public iDictionaryTree {

	WordNode* _root;

public:

	/**
	 * Default constructor that will construct this object safely and correctly
	 */
	DictionaryTree() : iDictionaryTree() {
		_root = new WordNode();
	}

	/**
	 * Inserts a whole word into the tree.
	 * If the word is not already in the tree, word node chain is created
	 * and stored appropriately. If already exists, but not marked as a whole
	 * word, it will mark the word as a whole.
	 */
	virtual void insert(const char* word) {
	}

	/**
	 * Attempts to find the node associated with a given word.
	 * If word is found, pointer is returned, and a nullptr is returned otherwise.
	 */
	virtual WordNode* getNodeForWord(const char* word) {
		if (!word) return nullptr;

		WordNode* cur = _root;
		int i = 0;
		do {
			cur = cur->getChild(word[i]);
			i++;
		} while (i < strlen(word) && cur != nullptr);
			

		return (i == strlen(word)) && (cur->isWholeWord()) ?
			_root->getChild(word[0]) : nullptr;
	}

	/**
	 * Returns the root node of the tree.
	 */
	virtual WordNode* getRoot() {
		return _root;
	}

	/**
	 * Virtual destructor that ensures correctly deallocating any memory
	 * that it is responsible for
	 */
	virtual ~DictionaryTree() {
		_root->~WordNode();
	}
};

#endif