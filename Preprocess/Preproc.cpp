#include "Preproc.h"

void Preprocessor::init() {
    Inst["#include"] = &Preprocessor::include;
    Inst["#define"] = &Preprocessor::define;
    Inst["#undef"] = &Preprocessor::undef;
    Inst["#ifdef"] = &Preprocessor::ifdef;
    Inst["#ifndef"] = &Preprocessor::ifndef;
    flag = true;
}

Preprocessor::Preprocessor() {
    this->init();
}

void Preprocessor::preprocessing(const std::string& file_name) {
    std::string line;
    this->fin.open(file_name);
    this->fout.open("after_pre.txt");
    if (this->fin.is_open()) {
        while (!fin.eof()) {
            getline(fin, line);
            if (line[0] == '/' && line[1] == '/') {
                continue;
            }
            auto vec = split(line, " ");
            if (vec[0] == "#endif") {
                this->fout << std::endl;
                flag = true;
                continue;
            }
            if (Inst.find(vec[0]) != Inst.end()) {
                (this->*Inst[vec[0]])(vec[1] + " " + vec[2]);
            }else {
                if (flag) {
                    cuts(line);
                    this->fout << line << std::endl;
                }
            }
        }
    }else {
        std::cout << "Eror";
    }
}

void Preprocessor::cuts(std::string& line) {
    for (auto it : Defs) {
        if (line.find(it.first) != std::string::npos) {
            int pos = 0;
            while ((pos = line.find(it.first, pos)) != -1) {
                line.erase(line.begin() + line.find(it.first),line.begin() + line.find(it.first) + it.first.size());
                line.insert(pos, it.second);
            }      
        }
    }
}

void Preprocessor::include(const std::string& path) {
    std::string ptr = "";
    for (int i = 1; path[i] != static_cast<char>(34); ++i) {
        ptr += path[i];
    }
    std::fstream f_include;
    std::string line;
    f_include.open(ptr);
    if (f_include.is_open()) {
        while (!f_include.eof()) {
            getline(f_include, line);
            auto vec = split(line, " ");
            if (Inst.find(vec[0]) != Inst.end()) {
                (this->*Inst[vec[0]])(vec[1] + " " + vec[2]);
            } else {
                this->fout << line << std::endl;
            }
        }
    } else {
        std::cout << "eror";
    }   
}

void Preprocessor::define(const std::string& definition) {
    this->fout << std::endl;
    auto vec = split(definition, " ");
    Defs[vec[0]] = vec[1];
}

void Preprocessor::undef(const std::string& undefintion){
    this->fout << std::endl;
    auto vec = split(undefintion, " ");
    Defs.erase(vec[0]);
}

void Preprocessor::ifdef(const std::string& line) {
    this->fout << std::endl;
    auto vec = split(line, " ");
    if (Defs.find(vec[0]) != Defs.end()) {
        flag = true;
        return;
    }
    flag = false;
}

void Preprocessor::ifndef(const std::string& line) {
    this->fout << std::endl;
    auto vec = split(line, " ");
    if (Defs.find(vec[0]) != Defs.end()) {
        flag = false;
        return;
    }
    flag = true;
}

std::vector<std::string> Preprocessor::split(const std::string& str, std::string spliter) {
    std::vector<std::string> nstr = {};
	std::string tstr = {};
	for (int i = 0; i < str.size(); ++i) {
		if (spliter.find(str[i]) != std::string::npos) {   
            if (tstr != "") {
			    nstr.push_back(tstr);
			    tstr.clear();
			    continue;
            }
            continue;
		}
		tstr.push_back(str[i]);
	}
	nstr.push_back(tstr);
	return nstr;
}