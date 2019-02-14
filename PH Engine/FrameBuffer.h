#pragma once
#include <vector>
#include "IO.h"
#include "VertexBufferObject.h"



struct DepthTarget {
	DepthTarget() = default;
	~DepthTarget();
	void unload();

	GLuint _Handle;
	bool _IsActive = false;

};

struct ColorTarget {
	ColorTarget() = default;
	~ColorTarget();

	void unload();

	std::vector<GLuint> _Handle; 
	std::vector<GLenum> _Buffer;
	std::vector<GLenum> _Format;
	unsigned _NumAttachments = 0;

};
class Framebuffer
{
public:
	Framebuffer();

	~Framebuffer();

	void unload();

	void init(unsigned width, unsigned height);

	void addDepthTarget();
	void addColorTarget(GLenum format);
	void resize();

	void setViewport() const;
	void bind() const;
	void unbind() const;
	void renderToFSQ() const;

	void bindColorAsTexture(unsigned colorBuffer, int textureSlot) const;
	void bindDepthAsTexture(int textureSlot) const;
	void unbindTexture(int textureSlot) const;

	void clear() const;


	GLuint _FBO; //Out Handle to the framebuffer
	bool _IsInit = false;

	DepthTarget _Depth;
	ColorTarget _Color;

	unsigned _Width = 0;
	unsigned _Height = 0;

	GLenum _Filter = GL_NEAREST;
	GLenum _Wrap = GL_CLAMP_TO_EDGE;

	GLbitfield _ClearFlag = 0;

	//Framebuffer Quad
	static void initFrameBuffers();
	static void drawFSQ(); //Draw Fullscreen Quad

private:
	static int _MaxColorAttachments;
	static bool _IsInitFrameBuffers;
	static VertexArrayObject _FullScreenQuad;

};