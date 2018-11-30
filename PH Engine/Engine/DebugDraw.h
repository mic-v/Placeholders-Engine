#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <btBulletDynamicsCommon.h>
#include "Math/math.h"
#include "Shader.h"
#include <vector>

class DebugDraw : public btIDebugDraw
{
public:
	DebugDraw();
	virtual ~DebugDraw();

	struct
	{
		btVector3 p1;
		btVector3 p2;

	} typedef LineValues;

	std::vector<LineValues> lines;

	struct _line {
		btVector3 from;
		btVector3 to;

		_line(btVector3 f, btVector3 t) {
			from = f;
			to = t;
		}
	};

	struct btLine {
		GLfloat vertices[6];
		btLine(const btVector3& f, const btVector3& t) {
			vertices[0] = f.x();
			vertices[1] = f.y();
			vertices[2] = f.z();

			vertices[3] = t.x();
			vertices[4] = t.y();
			vertices[5] = t.z();
		}
	};

	struct _color {
		btVector3 col;

		_color(btVector3 c) {
			col = c;
		}
	};

	std::vector<_line> LINES;
	std::vector<_color> COLORS;
	unsigned int VBO[3];
	unsigned int VB;
	unsigned VAO;

	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

	virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

	virtual void reportErrorWarning(const char* warningString);

	virtual void draw3dText(const btVector3& location, const char* textString);

	virtual void setDebugMode(int debugMode);

	virtual int getDebugMode() const { return _debugMode; }

	virtual void doDraw();

	glm::mat4 projection;
	Shader line;
private:
	int _debugMode;
	

};