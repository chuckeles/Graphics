#include "BufferObject.h"

#include <gl\glew.h>
#include <gl\gl.h>

void BufferObject::Create(Type type)
{
	// set type
	mType = type;

	// generate buffer
	glGenBuffers(1, &mID);
}

void BufferObject::Copy(Size size, void* data)
{
	// copy data
	if (mType == Type::Index)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, mID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
}

void BufferObject::Destroy()
{
	// delete buffer and reset id
	glDeleteBuffers(1, &mID);
	mID = 0;
}

void BufferObject::Bind(Size elementSize)
{
	// bind buffer object
	switch (mType)
	{
	case Type::Vertex:
		glBindBuffer(GL_ARRAY_BUFFER, mID);
		glVertexPointer(elementSize, GL_FLOAT, 0, 0);
		break;
	case Type::Color:
		glBindBuffer(GL_ARRAY_BUFFER, mID);
		glColorPointer(elementSize, GL_FLOAT, 0, 0);
		break;
	case Type::Normal:
		glBindBuffer(GL_ARRAY_BUFFER, mID);
		glNormalPointer(GL_FLOAT, 0, 0);
		break;
	case Type::Index:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
		glIndexPointer(GL_UNSIGNED_BYTE, 0, 0);
		break;
	}
}

const BufferObject::ID& BufferObject::GetID() const
{
	return mID;
}

const BufferObject::Type& BufferObject::GetType() const
{
	return mType;
}