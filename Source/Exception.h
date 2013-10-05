#pragma once

#include <string>

// class storing error information
class Exception
{

public:

	Exception(const std::string& error, const std::string& file, int line);
	Exception(std::string&& error, std::string&& file, int&& line);

	const std::string& GetError() const;
	const std::string& GetFile() const;
	const int& GetLine() const;

private:
	
	const std::string mError;
	const std::string mFile;
	const int mLine;

};

// for simple error throwing
#define THROW_ERROR(error) throw Exception(error, __FILE__, __LINE__)