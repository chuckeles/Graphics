#pragma once

#include <string>

typedef unsigned int uint;

// class storing error information
class Exception
{

public:

	Exception(const std::string& error, const std::string& file, uint line);
	Exception(std::string&& error, std::string&& file, uint line);

	const std::string& GetError() const;
	const std::string& GetFile() const;
	const uint& GetLine() const;

private:
	
	const std::string mError;
	const std::string mFile;
	const uint mLine = 0;

};

// for simple error throwing
#define THROW_ERROR(error) throw Exception(error, __FILE__, __LINE__)