#include "Exception.h"

Exception::Exception(const std::string& error, const std::string& file, uint line) :
	mError(error),
	mFile(file),
	mLine(line)
{
}

Exception::Exception(std::string&& error, std::string&& file, uint line) :
	mError(std::forward<std::string>(error)),
	mFile(std::forward<std::string>(file)),
	mLine(line)
{
}

const std::string& Exception::GetError() const
{
	return mError;
}

const std::string& Exception::GetFile() const
{
	return mFile;
}

const uint& Exception::GetLine() const
{
	return mLine;
}