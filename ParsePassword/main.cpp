
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

std::string readSettings()
{
	const char* pszSource = "settings.ini";
	ifstream ifile(pszSource);

	std::string buffer;
	std::string line;
	while(ifile)
	{
		std::getline(ifile, line);

		if(buffer.empty())
		{
			buffer.append(line);
		}
		else
		{
			buffer.append("\\n" + line);
		}
	}
	ifile.close();

	return buffer;
}
void writeSettings(const std::string & content,const std::string &fileName)
{
	std::ofstream	OsWrite(fileName);
	OsWrite << content;
	OsWrite << std::endl;
	OsWrite.close();

}


std::string encrypt(std::string msg, std::string const& key)
{
	// Side effects if the following is not written:
	// In my case, division by 0.
	// In the other case, stuck in an infinite loop.
	if(!key.size())
		return msg;

	for(std::string::size_type i = 0; i < msg.size(); ++i)
		msg[i] ^= key[i%key.size()];
	return msg;
}

// Rewritten to use const& on both parameters
std::string decrypt(std::string const& msg, std::string const& key)
{
	return encrypt(msg, key); // lol
}

int main()
{
	const char* pszDestination = "result.ini";
	std::string key = "ring";
	std::string setings = readSettings();
	std::cout << setings << endl;
	std::cout << "===================================================================================" << endl;
	std::string encr = encrypt(setings, key);
	std::cout << encr << endl;
	writeSettings(encr,"encr.ini");
	std::cout << "===================================================================================" << endl;
	std::string de = decrypt(encr, key);
	std::cout << de << endl;
	writeSettings(de, "de.ini");
	getchar();

}
