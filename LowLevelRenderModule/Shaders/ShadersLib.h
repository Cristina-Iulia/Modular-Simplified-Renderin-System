#pragma once

#ifndef  SHADERS_LIB
#define  SHADERS_LIB

#include <memory>

#include "VertexShader/VertexShader.h"
#include "PixelShader/PixelShader.h"

typedef std::shared_ptr<VertexShader> VertexShaderPtr;
typedef std::shared_ptr<PixelShader> PixelShaderPtr;

#endif