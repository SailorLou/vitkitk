#pragma once
#include <string>
class XOREncryption
{
public:
	XOREncryption();
	~XOREncryption();

	static std::string encrypt(const std::string &msg, const std::string & key);
	static std::string decrypt(const std::string & msg, const std::string & key);

	static void write(const std::string& stream, const std::string &fileName);
	static std::string read(const std::string &fileName);
};

