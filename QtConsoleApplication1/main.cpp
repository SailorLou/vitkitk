#include <QtCore/QCoreApplication>

#include <QSettings>
#include <QTextStream>
#include <fstream>
#include <iostream>
#include <string>
#include <QIODevice>
#include <QDebug>
#include <sstream>
#include <QFile>
#include "Test.h"
#include "Base64.h"
#include "Vigenere.h"
#include <QDataStream>

#include "XOREncryption.h"
#include "modes.h"
#include "Hex.h"
//#include "filters"

#include "aes.h"
using namespace CryptoPP;

static std::string s_key = "ring";
static QString s_sperator = "\t\n";

bool IniReadFunc(QIODevice &device, QSettings::SettingsMap &settingsMap)
{
	QString currentSection;

	QString data = device.readAll();

	std::string en = decrypt(data.toStdString(), s_key);
	data = QString(decrypt(data.toStdString(), s_key).c_str());

	QStringList keyValueList = data.split(s_sperator);
	for(auto var: keyValueList)
	{
		int pos =var.indexOf("=");
		if(pos < 0)
			continue;

		QString key = var.mid(0, pos);
		QString value = var.mid(pos+1, var.size()-pos-1);
		if(key.isEmpty())
			continue;

		settingsMap[key] = QVariant(value);
	}

	return true;
}

bool initWriteFunc(QIODevice &device, const QSettings::SettingsMap &map)
{
	QString data;
	QMapIterator<QString, QVariant> it(map);
	while(it.hasNext())
	{
		it.next();
		QString value = it.key() + it.value().toString();
		if(data.isEmpty())
		{
			data = it.key() + it.value().toString();
		}
		else
		{
			data.append(s_sperator + value);
		}
	}

	data = QString(encrypt(data.toStdString(), s_key).c_str());
	device.write(data.toUtf8());

	return true;
}

string readFileIntoString(char * filename)
{
	ifstream ifile(filename);

	ostringstream buf;
	char ch;
	while(buf&&ifile.get(ch))
		buf.put(ch);

	return buf.str();
}

std::string ECB_AESEncryptStr(std::string sKey, const char *plainText)
{
	std::string outstr;

	//Ìîkey
	SecByteBlock key(AES::MAX_KEYLENGTH);
	memset(key, 0x30, key.size());
	sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);


	AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);

	ECB_Mode_ExternalCipher::Encryption ecbEncryption(aesEncryption);
	StreamTransformationFilter ecbEncryptor(ecbEncryption, new HexEncoder(new StringSink(outstr)));
	ecbEncryptor.Put((byte *)plainText, strlen(plainText));
	ecbEncryptor.MessageEnd();

	return outstr;
}



std::string ECB_AESDecryptStr(std::string sKey, const char *cipherText)
{
	std::string outstr;

	//Ìîkey
	SecByteBlock key(AES::MAX_KEYLENGTH);
	memset(key, 0x30, key.size());
	sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);

	ECB_Mode<AES >::Decryption ecbDecryption((byte *)key, AES::MAX_KEYLENGTH);

	HexDecoder decryptor(new StreamTransformationFilter(ecbDecryption, new StringSink(outstr)));
	decryptor.Put((byte *)cipherText, strlen(cipherText));
	decryptor.MessageEnd();

	return outstr;
}


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	std::string settingName = "settings.ini";
	std::cout << "===================================settings===============================================" << endl;
	std::string setings = readSettings(settingName);
	std::cout << setings << endl;

	//XOREncryption::write(setings, "xor.ini");
	//std::string xor = XOREncryption::read("xor.ini");
	//std::cout << "===================================xor===============================================" << endl;
	//std::cout << xor << endl;

	std::cout << "======================================AES encrypt=============================================" << endl;

	std::string aes= ECB_AESEncryptStr(s_key, setings.c_str());
	std::cout << aes << std::endl;

	std::cout << "======================================AES decrypt=============================================" << endl;
	std::string aesDeC = ECB_AESDecryptStr(s_key, aes.c_str());
	std::cout << aesDeC << std::endl;

	std::cout << "======================================read encrypt =============================================" << endl;
	QSettings::Format format = QSettings::registerFormat("ini", IniReadFunc, initWriteFunc);
	QSettings settings("encr.ini", format);
	QStringList keys = settings.allKeys();
	for(auto var : keys)
	{
		qDebug() << var << "=" << settings.value(var).toString() << endl;
	}

	std::cout << "======================================decrypt =============================================" << endl;

	std::string de = decrypt(readFileIntoString("encr.ini"), s_key);
	std::cout << de << endl;
	return a.exec();
}

std::string readSettings(const std::string &fileName)
{
	ifstream ifile(fileName);

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
			buffer.append(s_sperator.toStdString() + line);
		}
	}
	ifile.close();

	return buffer;
}
void writeSettings(const std::string & content,const std::string &fileName)
{
	QFile file(fileName.c_str());
	file.open(QIODevice::WriteOnly);
	file.write(QString(content.c_str()).toUtf8());
	file.close();

	//std::ofstream	OsWrite(fileName);
	//OsWrite << content;
	//OsWrite << std::endl;
	//OsWrite.close();
}


std::string encrypt(std::string msg, std::string & key)
{

	std::string b64_str = base64_encode(msg);
	std::string vigenere_msg = encrypt_vigenere(b64_str, key);
	// std::cout << vigenere_msg << std::endl;
	return vigenere_msg;

	// Side effects if the following is not written:
	// In my case, division by 0.
	// In the other case, stuck in an infinite loop.
	//if (!key.size())
	//    return msg;
	//
	//for (std::string::size_type i = 0; i < msg.size(); ++i)
	//    msg[i] ^= key[i%key.size()];
	//return msg;
}

// Rewritten to use const& on both parameters
std::string decrypt(std::string & msg, std::string & key)
{
	std::string newKey = extend_key(msg, key);
	std::string b64_encoded_str = decrypt_vigenere(msg, newKey);
	std::string b64_decode_str = base64_decode(b64_encoded_str);
	return b64_decode_str;
	//return encrypt(msg, key); // lol
}
