#pragma once
#include <vector>
#include "VertexBufferObject.h"

//textures
struct DepthTarget
{
	~DepthTarget();
	void unload();
	GLuint _Handle;
	bool _isActive = false;
};

struct ColorTarget
{
	~ColorTarget();
	void unload();
	std::vector<GLuint> _Handle;
	std::vector<GLenum> _Format;
	std::vector<GLenum> _Buffer;
	unsigned _NumAttachments = 0;
};

class FrameBuffer
{
public:
	~FrameBuffer();
	void unload();

	void init(unsigned width, unsigned height);
	void addDepthTarget();
	void addColorTarget(GLenum format);
	void resize(unsigned width, unsigned height);

	void setViewport() const;
	void bind() const;
	void unbind() const;
	void renderToFSQ() const; //Full Screen Quad

	void bindColorAsTexture(unsigned colorBuffer, int textureSlot) const;
	void bindDepthAsTexture(int textureSlot) const;
	void unbindTexture(int textureSlot);

	void clear() const;

	GLuint _FBO;//Our handle to the framebuffer
	bool _IsInit = false; //to see if framebuffer is initialized 

	DepthTarget _Depth;
	ColorTarget _Color;

	unsigned _Width = 0;
	unsigned _Height = 0;

	GLenum _Filter = GL_NEAREST;
	GLenum _Wrap = GL_CLAMP_TO_EDGE;

	GLbitfield _ClearFlag = 0;

	static void initFramBuffers(); //initialize everything from framebuffer class
	static void drawFSQ(); //draw fullscreen quad

private:
	static int _MaxColorAttachments;
	static bool _IsInitFrameBuffers;
	static VertexArrayObject _FullScreenQuad; //vertices 
};
