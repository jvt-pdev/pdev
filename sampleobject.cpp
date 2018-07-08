
// BEGIN: Generated from SampleObject.definition
#include "sampleobject.h"
#include "standardfilesystem.h"
#include "sstream"

SampleObject::SampleObjectTypeDesc SampleObject::s_Desc;

SampleObject::SampleObjectTypeDesc::SampleObjectTypeDesc() 
{
	m_name = "SampleObject";
	m_memberDesc.push_back(MemberDesc("MyIntVariable", Type_Int, 1, offsetof(SampleObject, m_MyIntVariable)));
	m_memberDesc.push_back(MemberDesc("MyBoolVariable", Type_Bool, 1, offsetof(SampleObject, m_MyBoolVariable)));
	m_memberDesc.push_back(MemberDesc("MyFloatVariable", Type_Float, 1, offsetof(SampleObject, m_MyFloatVariable)));
	m_memberDesc.push_back(MemberDesc("MyDoubleVariable", Type_Double, 1, offsetof(SampleObject, m_MyDoubleVariable)));
	m_memberDesc.push_back(MemberDesc("MyArray", Type_Int, 12, offsetof(SampleObject, m_MyArray)));
}

SampleObject::SampleObject() : m_MyIntVariable(0), m_MyBoolVariable(false), m_MyFloatVariable(0.0f), m_MyDoubleVariable(0.0), m_MyArray{0}
{
}

SampleObject::~SampleObject()
{

}
// END: Generated from SampleObject.definition

// BEGIN: Custom Code
#include <iostream>
void SampleObject::myCustomFunction()
{
	std::cout << "Custom Function!" << std::endl;
}
void SampleObject::Load(StandardFileSystem fs, const char* filename) {
	int count = 0;
	this->m_MyBoolVariable = false;
	
	IFile* openedFile = fs.openFile(filename);
	if (!openedFile)
	{
		std::cout << "Failed to open file" << std::endl;
	}
	size_t size = openedFile->length();
	char* destBuffer = new char[size];

	if (!openedFile->read(destBuffer, size))
	{
		std::cout << "Failed to read from file!" << std::endl;
	}
	else
	{
		std::string dataString(destBuffer);

		std::istringstream is(dataString);
		std::string part;
		while (getline(is, part, '\n'))
		{
			if (part == "true") {
				this->m_MyBoolVariable = true;
			}
			else if (count == 4) {
				std::istringstream ia(part);
				std::string element;
				int i = 0;
				while (getline(ia, element, ' ')) {
					m_MyArray[i] = std::stoi(element);
					i++;
				}
			}
			else
			{
				switch (count) 
				{
					case 0: this->m_MyIntVariable = std::stoi(part);
					case 2: this->m_MyFloatVariable = std::stoi(part);
					case 3: this->m_MyDoubleVariable = std::stoi(part);
				}
			}
			count++;
		}
	}

	// Close the file
	delete openedFile;
}
void SampleObject::Save(StandardFileSystem fs, const char* filename) {
	const char* newline = "\n";
	const char* space = " ";

	if (fs.fileExists(filename))
	{
		fs.deleteFile(filename);
	}

	IFile* createdFile = fs.createFile(filename);
	if (!createdFile)
	{
		std::cout << "Failed to create a file" << std::endl;
		return;
	}

	std::string myInt = std::to_string(this->m_MyIntVariable);
	const char* myIntChar = myInt.c_str();
	std::string myFloat = std::to_string(this->m_MyFloatVariable);
	const char* myFloatChar = myFloat.c_str();
	std::string myDouble = std::to_string(this->m_MyDoubleVariable);
	const char* myDoubleChar = myDouble.c_str();

	const char* myBool = "true\n";

	if (this->m_MyBoolVariable != true) 
	{
		 myBool = "false\n";
	}

	if (!createdFile->write(myIntChar, strlen(myIntChar)))
	{
		std::cout << "Failed to write to file" << std::endl;
	}

	if (!createdFile->write(newline, strlen(newline)))
	{
		std::cout << "Failed to write to file" << std::endl;
	}

	if (!createdFile->write(myBool, strlen(myBool)))
	{
		std::cout << "Failed to write to file" << std::endl;
	}

	if (!createdFile->write(myFloatChar, strlen(myFloatChar)))
	{
		std::cout << "Failed to write to file" << std::endl;
	}

	if (!createdFile->write(newline, strlen(newline)))
	{
		std::cout << "Failed to write to file" << std::endl;
	}

	if (!createdFile->write(myDoubleChar, strlen(myDoubleChar)))
	{
		std::cout << "Failed to write to file" << std::endl;
	}

	if (!createdFile->write(newline, strlen(newline)))
	{
		std::cout << "Failed to write to file" << std::endl;
	}

	for (int count = 0; count < (sizeof(this->m_MyArray) / sizeof(*this->m_MyArray)); count++) {
		std::string myArray = std::to_string(this->m_MyArray[count]);
		const char* myArrayChar = myArray.c_str();
		if (count+1 == (sizeof(this->m_MyArray) / sizeof(*this->m_MyArray))) 
		{
			if (!createdFile->write(myArrayChar, strlen(myArrayChar) + 1))
			{
				std::cout << "Failed to write to file" << std::endl;
			}
		}
		else 
		{
			if (!createdFile->write(myArrayChar, strlen(myArrayChar)))
			{
				std::cout << "Failed to write to file" << std::endl;
			}
			if (!createdFile->write(space, strlen(space)))
			{
				std::cout << "Failed to write to file" << std::endl;
			}

		}
		
	}

	delete createdFile;

}
// END: Custom Code 
