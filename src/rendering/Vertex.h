#ifndef VERTEX_H
#define VERTEX_H
#include "math/Vectors.h"

namespace Tactics
{
	struct Vertex
	{
		Vector3 Position;
		Vector2 TexCoords;
		float TexId;
		Vector4 color;
	};
	struct VtxPC
	{
		Vector3 position;
		Vector4 color;
	};

	struct VtxPT
	{
		Vector2 position;
		Vector2 tex_coords;
	};
	struct VertexPositionTexCoordColor
	{
		Vector2 Position;
		Vector2 TexCoords;
		Vector4 Color;
	};
}
#endif