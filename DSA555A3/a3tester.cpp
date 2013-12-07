#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <cstdlib>
#include <cstdint>
#include "DictionaryTree.hpp"
#include "tester.hpp"

using namespace Testing;
using namespace std;

/**
    Trim functions used to resolve line ending issues when reading words list
    between windows/linux/etc...

    Borrowed from: http://stackoverflow.com/a/217605
*/
// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

void msgEvery(int counter, int num){
    if (counter % num == 0) {
        ss << "Finished " << counter << " tests...";
        write();
    }
}

void msgEvery50000(int counter){ msgEvery(counter, 50000); }
void msgEvery5000(int counter){ msgEvery(counter, 5000); }

bool testPart1AllWordsReturnNull(DictionaryTree& tree, fstream& wordsStream){
    sectionBegin("Part 1");
    h2("All words should return null nodes prior to insertion");
    string word;
    wordsStream.clear();
    wordsStream.seekg(0);
    int counter = 0;
    while (getline(wordsStream, word), !wordsStream.fail()){
        if (!word.size()) continue;

        trim(word);

        SILENT_ASSERT_EQ(tree.getNodeForWord(word.c_str()), 0,
            "tree.getNodeForWord(\"" << word << "\") == 0");
        counter++;
        msgEvery50000(counter);
    }
    ss << "Finished " << counter << " tests";
    write();
    sectionFinish("Part 1");
    return success;
}

bool testPart2NullThenInsertThenNotNull(DictionaryTree& tree, fstream& wordsStream){
    sectionBegin("Part 2");
    h2("All words should return null, then insert, then requesting word should not return null");
    string word;
    wordsStream.clear();
    wordsStream.seekg(0);
    int counter = 0;
    while (getline(wordsStream, word), !wordsStream.fail()){
        if (!word.size()) continue;

        trim(word);
		if (word == "adgar") {
			cout << "hi" << endl;
		}
		cout << "testing the word : " << word << "." << endl;
        iWordNode* wordNode = tree.getNodeForWord(word.c_str());
        SILENT_ASSERT(!wordNode || !wordNode->isWholeWord(),
            "tree.getNodeForWord(\"" << word << "\") == 0 || wordNode->isWholeWord() == false");
        tree.insert(word.c_str());
        wordNode = tree.getNodeForWord(word.c_str());
        SILENT_ASSERT_NE(wordNode, 0,
            "tree.getNodeForWord(\"" << word << "\") != 0");
        SILENT_ASSERT_EQ(wordNode->isWholeWord(), true,
            "wordNode->isWholeWord() == true");
        counter++;
        msgEvery50000(counter);
    }
    ss << "Finished " << counter << " tests";
    write();
    sectionFinish("Part 2");
    return success;
}

bool testPart3NavigateWordManually(DictionaryTree& tree, fstream& wordsStream){
    sectionBegin("Part 3");
    h2("Should be able to navigate through word tree manually for every word");

    iWordNode* root = tree.getRoot();
    ASSERT_NE(root, 0, "tree.getRoot() != 0");

    string word, traversed;
    wordsStream.clear();
    wordsStream.seekg(0);
    int counter = 0;
    while (getline(wordsStream, word), !wordsStream.fail()){
        if (!word.size()) continue;

        trim(word);

        iWordNode* cur = root;
        traversed.clear();
        string::const_iterator begin = word.begin(), end = word.end();
        while (begin != end) {
            SILENT_ASSERT_NE(cur, 0,
                "word:\"" << word << "\" traversed:\"" << traversed << "\" current node != 0");
            char c = *begin++;
            traversed.push_back(c);
            cur = cur->getChild(c);
        }

        // Verify that arrived at whole word node
        SILENT_ASSERT_NE(cur, 0,
            "destination node after manually traversing \"" << word << "\" != 0");
        SILENT_ASSERT_EQ(cur->isWholeWord(), true,
            "destination node after manually traversing \"" << word << "\"->isWholeWord() == true");
        counter++;
        msgEvery50000(counter);
    }
    ss << "Finished " << counter << " tests";
    write();
    sectionFinish("Part 3");
    return success;
}

bool testPart4CountChildWords(DictionaryTree& tree, fstream& wordsStream){
    sectionBegin("Part 4");
    h2("Should be able to get accurate count of number of child words for every word");

    regex reg;
    string word, word2, temp;
    wordsStream.clear();
    wordsStream.seekg(0);
    int counter = 0;
    while (getline(wordsStream, word), !wordsStream.fail()){
        if (!word.size()) continue;
        trim(word);

        temp = word;
        temp.append(".");
        temp.append("*");
        reg.assign(temp);
        fstream::pos_type pos = wordsStream.tellg();

        // Manually count number of child words
        size_t numWords = 0;
        while (getline(wordsStream, word2), trim(word2),
            !wordsStream.fail() && regex_match(word2, reg)) numWords++;

        // Count is correct?
        iWordNode* wordNode = tree.getNodeForWord(word.c_str());
        SILENT_ASSERT_NE(wordNode, 0,
            "tree.getNodeForWord(\"" << word << "\") != 0");
        SILENT_ASSERT_EQ(wordNode->getNumChildWords(), numWords,
            "wordNode(\"" << word << "\")->getNumChildWords == " << numWords);

        wordsStream.clear();
        wordsStream.seekg(pos);
        counter++;
        msgEvery5000(counter);
    }
    ss << "Finished " << counter << " tests";
    write();
    sectionFinish("Part 4");
    return success;
}

int main()
{
    h1("DSA555 A3 Dictionary Tree Tester");
    msg("You can consider your assignment to be successful when");
    msg("you see the success message, otherwise fix it until you see the");
    msg("success message.");

    cout << endl << endl;
    msg("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    msg("!!            WARNING            !!");
    msg("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    msg("Test parts !!3 and 4!! as well as !!TREE DESTRUCTION!!");
    msg("  may be !!EXTREMELY!! slow in !!DEBUG!! mode!");
    msg("Consider compiling and executing in !!RELEASE!! mode!");
    msg("Or in g++ with -O4 option (beside -std=c++0x)");
    cout << endl << endl;

    // Get list of words
    msg("Opening words.txt");
    fstream wordsStream("words.txt", fstream::in);

    if (wordsStream.fail()) {
        ss << "Failed to open words.txt, aborting...";
        err();
        return 1;
    }

    msg("Creating empty dictionary tree...");
    DictionaryTree tree;
//	tree.insert("");
//	tree.insert("aaaa");
//	tree.insert("aaa");

//	WordNode* node = tree.getNodeForWord("a");
//	std::cout << node->isWholeWord() << std::endl;
	//    if (overallSuccess) testPart1AllWordsReturnNull(tree, wordsStream);
    if (overallSuccess) testPart2NullThenInsertThenNotNull(tree, wordsStream);
/*    if (overallSuccess) testPart3NavigateWordManually(tree, wordsStream);
    if (overallSuccess) testPart4CountChildWords(tree, wordsStream); */

//    finish();

    return 0;
}
