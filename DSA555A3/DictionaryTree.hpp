#ifndef __A3_HPP__
#define __A3_HPP__

#include "A3Interfaces.hpp"
#include <array>
#include <string>

class WordNode : public iWordNode {

	char value;
	bool whole;
	WordNode* children[26];
	
public:
	
	/**
	 * Default constructor
	 *
	 */
	WordNode() : iWordNode(), value() {
		whole = false;
		for (int i = 0; i < 26; i++) {
			children[i] = nullptr;
		}
	}

	/**
	 * Returns a pointer to a WordNode instance at the given letter. If none
	 * exist, return nullptr.
	 */
	virtual WordNode* getChild(char letter) {
		return children[letter - 'a'];
	}

	/**
	 * Recursive helper function that will count the number of immediate children
	 * and add them to the total and return.
	 */
	size_t getNumChildWords(WordNode* wNode) const {
		if (!wNode) return 0;
		
		size_t total = 0;

		total += (wNode->whole) ? 1 : 0;

		for (int i = 0; i < 26; i++) {
			total += getNumChildWords(children[i]);
		}

		return total;
	}

	/**
	 * Returns the total number of child words that this node and all of its
	 * subtrees contain, not including this node itself.
	 */
	virtual size_t getNumChildWords() const {
		size_t total = 0;
		for (int i = 0; i < 26; i++) {
			total += getNumChildWords(children[i]);
		}
		return total;
	}

	/**
	 * Returns true if this instance is at the end of a whole word.
	 */
	virtual bool isWholeWord() const {
		return whole;
	}

	void setWhole(bool w) {
		whole = w;
	}

	void setValue(char val) {
		value = val;
	}

	/**
	 * Virtual destructor that ensures correctly deallocating any memory
	 * that it is responsible for
	 */
	virtual ~WordNode() {
		for (int i = 0; i < 26; i++) {
			children[i] = nullptr;
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
	DictionaryTree() : iDictionaryTree(), _root() {}

	/**
	 * Inserts a whole word into the tree.
	 * If the word is not already in the tree, word node chain is created
	 * and stored appropriately. If already exists, but not marked as a whole
	 * word, it will mark the word as a whole.
	 */
	virtual void insert(const char* word) {
		if (!word) return;
		if (!_root) _root = new WordNode();

		for (int i = 0; word[i]; i++) {
			_root = _root->getChild(word[i]);
			if (!_root) {
				_root= new WordNode();
				_root->setValue(word[i]);
			}
		}
		_root->setWhole(true);
	}

	/**
	 * Attempts to find the node associated with a given word.
	 * If word is found, pointer is returned, and a nullptr is returned otherwise.
	 */
	virtual WordNode* getNodeForWord(const char* word) {
		if (!word || !_root) return nullptr;

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