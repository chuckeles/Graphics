#pragma once

#include "Exception.h"

template<typename Type>
class Singleton
{

public:
	
	Singleton(Type* object);
	~Singleton();

	Singleton(const Singleton<Type>& other) = delete;
	Singleton(Singleton<Type>&& other) = delete;
	void operator=(const Singleton<Type>& other) = delete;
	void operator=(Singleton<Type>&& other) = delete;

	static Type& GetSingleton();

private:

	static Type* msSingleton;

};

// member definition help macro
#define SINGLETON_DEF(Type) Type* Singleton<Type>::msSingleton = nullptr

// impl
template<typename Type>
Singleton<Type>::Singleton(Type* object)
{
	if (!msSingleton)
		msSingleton = object;
}

template<typename Type>
Singleton<Type>::~Singleton()
{
	if (msSingleton == this)
		msSingleton = 0;
}

template<typename Type>
Type& Singleton<Type>::GetSingleton()
{
	if (msSingleton)
		return *msSingleton;
	else
		THROW_ERROR("No singleton created");
}