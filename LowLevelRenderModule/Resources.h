#pragma once

#ifndef  RENDERER_RESOURCES
#define RENDERER_RESOURCES

#include <memory>

#include "SwapChain/SwapChain.h"
#include "MemoryBuffers/VertexBuffer/VertexBuffer.h"
#include "MemoryBuffers/IndexBuffer/IndexBuffer.h"
#include "Shaders/VertexShader/VertexShader.h"
#include "Shaders/PixelShader/PixelShader.h"
#include "MemoryBuffers/ConstantBuffer/ConstantBuffer.h"


typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;
typedef std::shared_ptr<IndexBuffer> IndexBufferPtr;
typedef std::shared_ptr<VertexShader> VertexShaderPtr;
typedef std::shared_ptr<PixelShader> PixelShaderPtr;
typedef std::shared_ptr<ConstantBuffer> ConstantBufferPtr;

#endif