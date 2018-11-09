#pragma once

#include <glad/glad.h>
#include "Math/math.h"

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Entity.h"
class RendererModule
{
public:
	static void drawEntity(Shader & shader);
private:
	RendererModule() {}
};