#ifndef __A3INTERFACES_HPP__
#define __A3INTERFACES_HPP__
/**
    A3Interfaces.hpp
    Interface definition file for iWordNode and iDictionaryTree.
    Provided by your DSA555 Professor.
 */

/**
    iWordNode
    Interface class for word nodes. Contains the functions required to
    characterize a word node.
 */
class iWordNode
{
public:
    /**
        Returns a pointer to an iWordNode instance at the given letter.
        If none exist, this function should return nullptr.
     */
    virtual iWordNode* getChild(char) = 0;

    /**
        Returns the total number of children that this node and all of its
        subtrees contain.
     */
    virtual size_t getNumChildren() const = 0;

    /**
        Returns true if this instance is at the end of a whole word,
        false otherwise.
     */
    virtual bool isWholeWord() const = 0;

    /**
        Virtual destructor.
     */
    virtual ~iWordNode(){}
};

/**
    iDictionaryTree
    Interface class for dictionary trees. Contains the functions required
    to control a dictionary tree object.
 */
class iDictionaryTree
{
public:
    /**
        Inserts a "whole word" into the tree.
        If the word is not already in the tree, the required word node chain
        is created and stored appropriately.
        If the word is already in the tree but not marked as a whole word,
        it is marked as a whole word.
     */
    virtual void insert(const char* word) = 0;

    /**
        Attempts to find the node associated with a given word.
        A word is found by descending character by character into the word node
        tree from the root.
        If the word is not found in the tree, nullptr is returned.
        If the word is found, a pointer to it is returned.
    */
    virtual iWordNode* getNodeForWord(const char* word) = 0;

    /**
        Simply returns the root node of the tree.
    */
    virtual iWordNode* getRoot() = 0;

    /**
        Virtual destructor.
    */
    virtual ~iDictionaryTree(){}
};

#endif
