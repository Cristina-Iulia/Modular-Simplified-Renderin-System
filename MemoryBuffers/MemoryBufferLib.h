#pragma once
#ifndef  MEMORY_BUFFERS_LIB
#define MEMORY_BUFFERS_LIB

#include <memory>

#include "ConstantBuffer/ConstantBuffer.h"
#include "VertexBuffer/VertexBuffer.h"
#include "IndexBuffer/IndexBuffer.h"

typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;
typedef std::shared_ptr<IndexBuffer> IndexBufferPtr;
typedef std::shared_ptr<ConstantBuffer> ConstantBufferPtr;

#endif