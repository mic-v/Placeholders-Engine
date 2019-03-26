#include "FrameBuffer.h"
#include "IO.h"

int FrameBuffer::_MaxColorAttachments;
bool FrameBuffer::_IsInitFrameBuffers;
VertexArrayObject FrameBuffer::_FullScreenQuad;

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
	if (_NumAttachments)
	{
		glDeleteTextures(_NumAttachments, &_Handle[0]);
		_Handle.clear();
		_Format.clear();
		_Buffer.clear();
	}
	_NumAttachments = 0;
}

FrameBuffer::~FrameBuffer()
{
	unload();
}

void FrameBuffer::unload()
{

}

void FrameBuffer::init(unsigned width, unsigned height)
{
	_Width = width;
	_Height = height;

	SAT_ASSERT(_Height > 0 && _Height > 0, "With and/or Height not initialized");
	SAT_ASSERT(_IsInit == false, "Framebuffer already Initialized");

	glGenFramebuffers(1, &_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);

	if (_Depth._isActive)
	{
		_ClearFlag |= GL_DEPTH_BUFFER_BIT;

		// Create Depth Texture
		glGenTextures(1, &_Depth._Handle);
		glBindTexture(GL_TEXTURE_2D, _Depth._Handle);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, _Width, _Height);

		// Set Texture Parameters for Depth
		glTextureParameteri(_Depth._Handle, GL_TEXTURE_MIN_FILTER, _Filter);
		glTextureParameteri(_Depth._Handle, GL_TEXTURE_MAG_FILTER, _Filter);
		glTextureParameteri(_Depth._Handle, GL_TEXTURE_WRAP_S, _Wrap);
		glTextureParameteri(_Depth._Handle, GL_TEXTURE_WRAP_T, _Wrap);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _Depth._Handle, 0);
	}

	if (_Color._NumAttachments)
	{
		_ClearFlag |= GL_COLOR_BUFFER_BIT;

		glGenTextures(_Color._NumAttachments, &_Color._Handle[0]);
		for (unsigned int i = 0; i < _Color._NumAttachments; i++)
		{
			glBindTexture(GL_TEXTURE_2D, _Color._Handle[i]);
			glTexStorage2D(GL_TEXTURE_2D, 1, _Color._Format[i], _Width, _Height);

			// Set Texture Parameters for Each Color Target
			glTextureParameteri(_Color._Handle[i], GL_TEXTURE_MIN_FILTER, _Filter);
			glTextureParameteri(_Color._Handle[i], GL_TEXTURE_MAG_FILTER, _Filter);
			glTextureParameteri(_Color._Handle[i], GL_TEXTURE_WRAP_S, _Wrap);
			glTextureParameteri(_Color._Handle[i], GL_TEXTURE_WRAP_T, _Wrap);

			// Connect the Texture to the FBO
			glFramebufferTexture2D(GL_FRAMEBUFFER, _Color._Buffer[i], GL_TEXTURE_2D, _Color._Handle[i], 0);
		}
	}
	unbind();
	_IsInit = true;
}

void FrameBuffer::addDepthTarget()
{
	SAT_ASSERT(_IsInit == false, "Framebuffer already initialized");
	if (!_IsInit)
	{
		_Depth._isActive = true;
	}
}

void FrameBuffer::addColorTarget(GLenum format)
{
	SAT_ASSERT(_IsInit == false, "Framebuffer already initialized");
	SAT_ASSERT(_Color._NumAttachments < (unsigned)_MaxColorAttachments, "Max Number of Color Attachments reached");
	if (!_IsInit)
	{
		_Color._Handle.push_back(0);
		_Color._Format.push_back(format);
		_Color._Buffer.push_back(GL_COLOR_ATTACHMENT0 + _Color._NumAttachments);
		_Color._NumAttachments++;
	}
}

void FrameBuffer::resize(unsigned width, unsigned height)
{
	SAT_ASSERT(_IsInit, "Framebuffer not initialized!");
	_Width = width;
	_Height = height;
	unload();
	_Depth.unload();
	_Color.unload();
	init(_Width, _Height);
}

void FrameBuffer::setViewport() const
{
	glViewport(0, 0, _Width, _Height);
}

void FrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
	if (_Color._NumAttachments)
		glDrawBuffers(_Color._NumAttachments, &_Color._Buffer[0]);
}

void FrameBuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, GL_NONE);
}

void FrameBuffer::renderToFSQ() const
{
	setViewport();
	bind();
	drawFSQ();
	unbind();
}

void FrameBuffer::bindColorAsTexture(unsigned colorBuffer, int textureSlot) const
{
	SAT_ASSERT(_IsInit == true, "Framebuffer not initialized");
	SAT_ASSERT(colorBuffer < _Color._Handle.size(), "Color Target does not exist");

	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, _Color._Handle[colorBuffer]);
}

void FrameBuffer::bindDepthAsTexture(int textureSlot) const
{
	SAT_ASSERT(_IsInit == true, "Framebuffer not initialized");
	SAT_ASSERT(_Depth._isActive, "Color Target does not exist");

	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, _Depth._Handle);
}

void FrameBuffer::unbindTexture(int textureSlot)
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void FrameBuffer::clear() const
{
	bind();
	glClear(_ClearFlag);
	unbind();
}

void FrameBuffer::initFramBuffers()
{
	float VBO_Vertex[] =
	{
		-1, -1, 0,
		 1, -1, 0,
		-1,  1, 0,
		 1,  1, 0
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
	vertexData.sizeOfElement = sizeof(float);
	vertexData.data = VBO_Vertex;

	uvData.attributeType = TEXCOORD;
	uvData.numElementsPerAttribute = 2;
	uvData.numElements = 4 * uvData.numElementsPerAttribute;
	uvData.sizeOfElement = sizeof(float);
	uvData.data = VBO_UV;

	_FullScreenQuad.addVBO(vertexData);
	_FullScreenQuad.addVBO(uvData);
	_FullScreenQuad.setPrimitiveType(GL_TRIANGLE_STRIP);
	_FullScreenQuad.createVAO();
	_IsInitFrameBuffers = true;
	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &_MaxColorAttachments);
	SAT_DEBUG_LOG_SAFE("Maximum Framebuffer Color Attachements: %d", _MaxColorAttachments);
}

void FrameBuffer::drawFSQ()
{
	SAT_ASSERT(_IsInitFrameBuffers, "Full Screen Quad Not Initialized");
	_FullScreenQuad.draw();
}
