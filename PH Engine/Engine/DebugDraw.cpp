#include "DebugDraw.h"

DebugDraw::DebugDraw() : _debugMode(0)
{
}

DebugDraw::~DebugDraw()
{
}

void DebugDraw::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color)
{
	LineValues line;
	line.p1 = from;
	line.p2 = to;


	lines.push_back(line);

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

void DebugDraw::doDraw()
{
	glVertexAttribPointer(0,  // the handle for the a_position shader attrib
		3,	// there are 3 values xyz
		GL_FLOAT, // they a float
		GL_FALSE, // don't need to be normalised
		4 * sizeof(float),  // how many floats to the next one(be aware btVector3 uses 4 floats)
		(GLfloat*)&this->lines[0]  // where do they start as an index); // use 3 values, but add stride each time to get to the next
	);

	glEnableVertexAttribArray(0);
	glDrawArrays(GL_LINES, 0, lines.size() * 2);
}

