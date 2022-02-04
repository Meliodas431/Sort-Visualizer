#pragma once
#include "glm/glm.hpp"

struct Vertex {
	glm::vec2 Position;
	glm::vec2 TexCoords;
	float  TexID;
	glm::vec4 Color;
};