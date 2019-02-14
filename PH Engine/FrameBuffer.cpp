#include "FrameBuffer.h"
int Framebuffer:: _MaxColorAttachments = 0;
bool Framebuffer:: _IsInitFrameBuffers = false;
VertexArrayObject Framebuffer::_FullScreenQuad = _FullScreenQuad;

DepthTarget::~DepthTarget()
{
	unload();
}

void DepthTarget::unload()
{
	glDeleteTextures(1, &_Handle);
}

ColorTarget::~ColorTarget()
{
	unload();
}

void ColorTarget::unload()
{
	if (_NumAttachments) {
		glDeleteTextures(_NumAttachments, &_Handle.front());
		_Handle.clear();
		_Format.clear();
		_Buffer.clear();
	}
	_NumAttachments = 0;
}

Framebuffer::Framebuffer()
{
	
}

Framebuffer::~Framebuffer()
{
	unload();
}

void Framebuffer::unload()
{

}

void Framebuffer::init(unsigned width, unsigned height)
{
	_Width = width;
	_Height = height;

	SAT_ASSERT(_Width > 0 && _Height > 0, "width and/or Height is not initialized!");
	SAT_ASSERT(_IsInit == false, "Framebuffer already initialized!");

	glGenFramebuffers(1, &_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

	if (_Depth._IsActive) {
		_ClearFlag |= GL_DEPTH_BUFFER_BIT;

		// Create depth texture
		glGenTextures(1, &_Depth._Handle);
		glBindTexture(GL_TEXTURE_2D, _Depth._Handle);
		//glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, _Width, _Height);
		glTextureStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, _Width, _Height);
		//Set texture parameters for depth
		glTexParameteri(_Depth._Handle, GL_TEXTURE_MIN_FILTER, _Filter);
		glTexParameteri(_Depth._Handle, GL_TEXTURE_MAG_FILTER, _Filter);
		glTexParameteri(_Depth._Handle, GL_TEXTURE_WRAP_S, _Wrap);
		glTexParameteri(_Depth._Handle, GL_TEXTURE_WRAP_T, _Wrap);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			GL_TEXTURE_2D, _Depth._Handle, 0);
	}

	if (_Color._NumAttachments) {
		_ClearFlag |= GL_COLOR_BUFFER_BIT;

		glGenTextures(_Color._NumAttachments, &_Color._Handle.front());
		for (unsigned int i = 0; i < _Color._NumAttachments; ++i) {
			glBindTexture(GL_TEXTURE_2D, _Color._Handle[i]);
			glTextureStorage2D(GL_TEXTURE_2D, 1, _Color._Format[i], _Width, _Height);
			
			//Set texture parameters for color
			glTexParameteri(_Color._Handle[i], GL_TEXTURE_MIN_FILTER, _Filter);
			glTexParameteri(_Color._Handle[i], GL_TEXTURE_MAG_FILTER, _Filter);
			glTexParameteri(_Color._Handle[i], GL_TEXTURE_WRAP_S, _Wrap);
			glTexParameteri(_Color._Handle[i], GL_TEXTURE_WRAP_T, _Wrap);

			glFramebufferTexture2D(GL_FRAMEBUFFER, _Color._Buffer[i],
				GL_TEXTURE_2D, _Color._Handle[i], 0);
		}
	}

	unbind();
	_IsInit = true;
}



	


void Framebuffer::addDepthTarget()
{
	SAT_ASSERT(_IsInit == false, "Framebuffer already initialized!");
	if (!_IsInit) {
		_Depth._IsActive = true;
	}
}

void Framebuffer::addColorTarget(GLenum format)
{
	SAT_ASSERT(_IsInit == false, "Framebuffer already initialized!");
	SAT_ASSERT(_Color._NumAttachments < (unsigned)_MaxColorAttachments, "Maximum number of color attachments for each");
	if (!_IsInit) {
		_Color._Handle.push_back(0);
		_Color._Format.push_back(format);
		_Color._Buffer.push_back(GL_COLOR_ATTACHMENT0 + _Color._NumAttachments);
		_Color._NumAttachments++;
	}
}

void Framebuffer::resize()
{
	unbind();
	delete &DepthTarget();
	delete &Framebuffer();
	initFrameBuffers();
}

void Framebuffer::setViewport() const
{
	glViewport(0, 0, _Width, _Height);
}

void Framebuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
	if (_Color._NumAttachments) {
		glDrawBuffers(_Color._NumAttachments, &_Color._Buffer[0]);
	}
}

void Framebuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}

void Framebuffer::renderToFSQ() const
{
	setViewport();
	bind(); 
	drawFSQ();
	unbind();

}

void Framebuffer::bindColorAsTexture(unsigned colorBuffer, int textureSlot) const
{
	SAT_ASSERT(_IsInit == true, "Framebuffer not initialized!");
	SAT_ASSERT(colorBuffer < _Color._Handle.size(), "Color target doesn't exist!");

	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, _Color._Handle[colorBuffer]);
}

void Framebuffer::bindDepthAsTexture(int textureSlot) const
{
	SAT_ASSERT(_IsInit == true, "Framebuffer not initialized!");
	SAT_ASSERT(_Depth._IsActive, "Depth target doesn't exist!");

	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, _Depth._Handle);
}

void Framebuffer::unbindTexture(int textureSlot) const
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void Framebuffer::clear() const
{
	bind();
	glClear(_ClearFlag);
	unbind();
}

void Framebuffer::initFrameBuffers()
{
	GLfloat VBO_Vertex[] =
	{
		-1, -1, 0,
		1, -1, 0,
		-1, 1, 0,
		1, 1, 0
	};
	float VBO_UV[] =
	{
		0, 0,
		1, 0,
		0, 1,
		1, 1
	};
	VertexBufferData vertexData, uvData;

	vertexData.attributeType = VERTEX;
	vertexData.numElementsPerAttribute = 3;
	vertexData.numElements = 4 * vertexData.numElementsPerAttribute;
	vertexData.sizeOfElement = uvData.sizeOfElement = sizeof(float);
	vertexData.data = VBO_Vertex;

	uvData.attributeType = TEXCOORD;
	uvData.numElementsPerAttribute = 2;
	uvData.numElements = 4 * uvData.numElementsPerAttribute;
	uvData.data = VBO_UV;
	_FullScreenQuad.addVBO(vertexData);
	_FullScreenQuad.addVBO(uvData);
	_FullScreenQuad.setPrimitiveType(GL_TRIANGLE_STRIP);
	_FullScreenQuad.createVAO();
	_IsInitFrameBuffers = true;
	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &_MaxColorAttachments);
	SAT_DEBUG_LOG_SAFE("Maximum Framebuffer Color Attachments: %d", _MaxColorAttachments);
}

void Framebuffer::drawFSQ()
{
	SAT_ASSERT(_IsInitFrameBuffers, "Full Screen Quad not Initialized!");
	_FullScreenQuad.draw();
}
