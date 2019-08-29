#include "XOREncryption.h"

#include <fstream>
#include <iostream>

using namespace std;

XOREncryption::XOREncryption()
{
}


XOREncryption::~XOREncryption()
{
}

std::string XOREncryption::encrypt(const std::string &msg, const std::string  &key)
{
	if(!key.size())
		return msg;

	std::string result = msg;
	for(std::string::size_type i = 0; i < msg.size(); ++i)
		result[i] ^= key[i%key.size()];
	return result;
}

std::string XOREncryption::decrypt(const std::string & msg, const std::string & key)
{
	return encrypt(msg, key);
}

void __write(const std::string& stream, const std::string &fileName)
{
	std::cout << "=============size=" << stream << std::endl;
	FILE *outFile = fopen(fileName.c_str(), "wb");

	int size = stream.size() + 1;
	fwrite(&size, 10, 1, outFile);
	fwrite(stream.data(), size, 1, outFile);

	const char * str = stream.data();
	//outFile.write(str, size);
	fclose(outFile);
}

void XOREncryption::write(const std::string& stream, const std::string &fileName)
{

	std::string ref = stream;
	unsigned int size1 = 124;
	std::ofstream supp_info_output("binary_file", std::ios::out | std::ios::binary); // saving file
	unsigned int stringLength = ref.length();
	supp_info_output.write((char*)(&stringLength), sizeof(stringLength));
	supp_info_output.write(ref.c_str(), ref.length());
	supp_info_output.write((char*)(&size1), sizeof(size1));
	supp_info_output.close();


	std::cout << "=============size=" << stream << std::endl;
	ofstream outFile("deasdf", ios::binary | ios::out);

	int size = stream.size()+500;
	//outFile.write((char*)&size, 10);

	const char * str = stream.data();
	outFile.write(str, size);
	outFile.close();
}

std::string XOREncryption::read(const std::string &fileName)
{
	string data;
	fstream inFile(fileName, ios::in | ios::binary);

	int size = 0;
	inFile.read((char*)&size, 10);
	data.resize(size);
	inFile.read((char*)data.c_str(), size);

	inFile.close();

	return data;
}
