#include "DebugDraw.h"

DebugDraw::DebugDraw() : _debugMode(0)
{
}

DebugDraw::~DebugDraw()
{
}

void DebugDraw::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color)
{
	btLine line(from, to);
	LINES.push_back(_line(btVector3(from.getX(), from.getY(), from.getZ()), btVector3(to.getX(), to.getY(), to.getZ())));
	COLORS.push_back(_color(btVector3(color.getX(), color.getY(), color.getZ())));

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(2, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, LINES.size() * sizeof(_line), &LINES[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, COLORS.size() * sizeof(_color), &COLORS[0], GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, LINES.size());

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	LINES.clear();
	COLORS.clear();
}

void DebugDraw::drawContactPoint(const btVector3 & PointOnB, const btVector3 & normalOnB, btScalar distance, int lifeTime, const btVector3 & color)
{
	{
		//btVector3 to=pointOnB+normalOnB*distance;
		//const btVector3&from = pointOnB;
		//glColor4f(color.getX(), color.getY(), color.getZ(), 1.0f);   

		//GLDebugDrawer::drawLine(from, to, color);

		//glRasterPos3f(from.x(),  from.y(),  from.z());
		//char buf[12];
		//sprintf(buf," %d",lifeTime);
		//BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
	}
}

void DebugDraw::reportErrorWarning(const char * warningString)
{
	printf(warningString);
}

void DebugDraw::draw3dText(const btVector3 & location, const char * textString)
{
	//glRasterPos3f(location.x(),  location.y(),  location.z());
	//BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),textString);
}

void DebugDraw::setDebugMode(int debugMode)
{
	_debugMode = debugMode;
}

