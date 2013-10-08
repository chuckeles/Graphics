#pragma once

class Noncopyable
{

public:

	Noncopyable() = default;
	Noncopyable(const Noncopyable&) = delete;
	void operator=(const Noncopyable&) = delete;

};