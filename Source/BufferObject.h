#pragma once

typedef unsigned int uint;

class BufferObject
{

public:

	typedef uint ID;
	typedef uint Size;

	enum class Type
	{
		Vertex,
		Color,
		Normal,
		Index
	};


	// generate buffer object
	void Create(Type type);
	// copy data to buffer object
	void Copy(Size size, void* data);
	void Destroy();

	// bind and set pointer to buffer object
	virtual void Bind(Size elementSize = 3);

	const ID& GetID() const;
	const Type& GetType() const;

private:

	ID mID = 0;
	Type mType = Type::Vertex;

};