#ifndef PREPROC_H
#define PREPROC_H
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Preprocessor {
public:
    Preprocessor();
    void preprocessing(const std::string&);
private:
    typedef void(Preprocessor::*Func) (const std::string&);
    std::map <std::string, Func> Inst;
    std::map <std::string, std::string> Defs;
private:
    void init();
    std::vector<std::string> split(const std::string& str,  std::string spliter);
    void include(const std::string&);
    void define(const std::string&);
    void undef(const std::string&);
    void ifdef(const std::string&);
    void ifndef(const std::string&);
    void cuts(std::string&);
private:
    std::fstream fin;
    std::fstream fout;
    bool flag;
};

#endif // PREPROC_H