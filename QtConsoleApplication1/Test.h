#pragma once

#include <string>
using namespace std;

extern std::string readSettings(const std::string &fileName);
extern void writeSettings(const std::string & content, const std::string &fileName);
extern std::string encrypt(std::string msg, std::string & key);
extern std::string decrypt(std::string & msg, std::string & key);
