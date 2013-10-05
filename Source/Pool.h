#pragma once

#include <initializer_list>
#include <memory>
#include <queue>

typedef unsigned int uint;

template<typename Type>
class Pool
{

public:

	typedef std::shared_ptr<Type> TypePtr;
	typedef std::queue<TypePtr> TypeQueue;
	
	Pool();
	template<typename... Args> Pool(uint size, Args&&... args);
	Pool(std::initializer_list<Type>&& list);

	void AddObject(TypePtr object);
	TypePtr GetObject();

	void ClearPool();

	const uint GetSize() const;

private:

	TypeQueue mObjects;

};

// impl
template<typename Type>
Pool<Type>::Pool()
{
}

template<typename Type>
template<typename... Args>
Pool<Type>::Pool(uint size, Args&&... args)
{
	// create size-number of objects
	for (uint i = 0; i < size; ++i)
		mObjects.push(TypePtr(new Type(std::forward<Args>(args)...)));
}

template<typename Type>
Pool<Type>::Pool(std::initializer_list<Type>&& list)
{
	// add objects from initializer list
	for (TypePtr object : list)
		mObjects.push(object);
}

template<typename Type>
void Pool<Type>::AddObject(TypePtr object)
{
	// add new object to the pool
	if (object)
		mObjects.push(object);
}

template<typename Type>
typename Pool<Type>::TypePtr Pool<Type>::GetObject()
{
	// if possible, release an object from the pool
	if (GetSize())
	{
		TypePtr o = mObjects.front();
		mObjects.pop();
		return o;
	}
	else
		return TypePtr();
}

template<typename Type>
void Pool<Type>::ClearPool()
{
	while (!mObjects.empty())
		mObjects.pop();
}

template<typename Type>
const uint Pool<Type>::GetSize() const
{
	return mObjects.size();
}