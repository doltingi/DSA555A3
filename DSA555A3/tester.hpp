#ifndef __TESTER_HPP__
#define __TESTER_HPP__

#include <iostream>
#include <string>
#include <sstream>

namespace Testing {
    static const char* indent = "";
    static std::stringstream ss;
    static bool success = true;
    static bool overallSuccess = true;

    void msg(const std::string& s){
        std::cout << indent << s << std::endl;
    }

    void write(){
        msg(ss.str());
        ss.clear();
        ss.str(std::string());
    }

    void err(){
        std::string m = ss.str();
        ss.clear();
        ss.str(std::string());
        ss << "ERROR! " << m;
        write();
        success = false;
        overallSuccess = false;
    }

    void h1(const std::string& s){
        std::cout << s << ':' << std::endl;
        indent = "  ";
    }

    void h2(const std::string& s){
        std::cout << "  [" << s << "]:" << std::endl;
        indent = "    ";
    }

    void h3(const std::string& s){
        std::cout << "    [" << s << "]:" << std::endl;
        indent = "      ";
    }

    void h4(const std::string& s){
        std::cout << "      [" << s << "]:" << std::endl;
        indent = "        ";
    }

    void h1w(){
        h1(ss.str());
        ss.clear();
        ss.str(std::string());
    }

    void h2w(){
        h2(ss.str());
        ss.clear();
        ss.str(std::string());
    }

    void h3w(){
        h3(ss.str());
        ss.clear();
        ss.str(std::string());
    }

    void h4w(){
        h4(ss.str());
        ss.clear();
        ss.str(std::string());
    }

    void sectionBegin(std::string name){
        success = true;
        ss << name << " Tests";
        h1w();
    }

    void sectionFinish(std::string name){
        ss << "Finished " << name << " tests ";
        if (success) {
            ss << "with no errors! Success!";
        }
        else {
            ss << "with errors... fix them and try again";
            overallSuccess = false;
        }
        h1w();
    }

    void finish(){
        if (overallSuccess) {
            h1("Finished all enabled tests with no errors! Success!");
        }
        else {
            h1("Finished some enabled tests with errors... fix them and try again");
        }

        std::cout << "Done. Type anything to continue..." << std::endl;
        std::string s;
        std::cin >> s;
    }
}

#define ASSERT(test, m) \
    if (!(test)){\
        ss << "Test: [" << m << "], FAILED!"; \
        Testing::err(); \
        return false; \
    } \
    else {\
        ss << "Test: [" << m << "], PASSED!"; \
        Testing::write(); \
    }

#define SILENT_ASSERT(test, m) \
    if (!(test)){ \
        ss << "Test: [" << m << "], FAILED!"; \
        Testing::err(); \
        return false; \
    }

#define _EQ(tester, p1, p2, m) tester((p1) == (p2), m << ", got:" << p1 << ", expected:" << p2)
#define _NE(tester, p1, p2, m) tester((p1) != (p2), m << ", got:" << p1 << ", expected NOT:" << p2)

#define ASSERT_EQ(p1, p2, m) _EQ(ASSERT, p1, p2, m)
#define ASSERT_NE(p1, p2, m) _NE(ASSERT, p1, p2, m)
#define SILENT_ASSERT_EQ(p1, p2, m) _EQ(SILENT_ASSERT, p1, p2, m)
#define SILENT_ASSERT_NE(p1, p2, m) _NE(SILENT_ASSERT, p1, p2, m)

#define TESTER_COMMA() ,
#endif
