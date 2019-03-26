#include "PostProcessBuffer.h"

void PostProcessBuffer::init(unsigned width, unsigned height)
{
	SAT_ASSERT(_IsInit == false, "Post Processing Buffer already initalized!");
	if (!_IsInit) {
		for (int i = 0; i < 2; ++i) {
			m_PFramebuffers[i].addColorTarget(m_pFormat);
			m_PFramebuffers[i].init(width, height);
			/*setOpenGLName(GL_TEXTURE, 
				m_PFramebuffers->_Color._Tex[0].getID(), 
				"PostProcessing FBO #" + std::to_string(i));*/
		}

		m_pReadBuffer = &m_PFramebuffers[0];
		m_pWriteBuffer = &m_PFramebuffers[1];
		_IsInit = true;
	}

}

void PostProcessBuffer::setFormat(GLenum format)
{
	m_pFormat = format;
}

void PostProcessBuffer::clear()
{
	for (int i = 0; i < 2; ++i) {
		m_PFramebuffers[i].clear();
	}

}

void PostProcessBuffer::reshape(unsigned int width, unsigned int height)
{
	for (int i = 0; i < 2; ++i) {
		m_PFramebuffers[i].resize(width, height);
		/*setOpenGLName(GL_TEXTURE,
			m_PFramebuffers->_Color._Tex[0].getID(),
			"PostProcessing FBO #" + std::to_string(i));*/
	}
}

void PostProcessBuffer::drawToPost()
{
	SAT_ASSERT(_IsInit == true, "Post Processing Buffer ot initialzed!");
	m_pWriteBuffer->renderToFSQ();
	swap();

}

void PostProcessBuffer::draw()
{
	SAT_ASSERT(_IsInit == true, "Post Processing Buffer ot initialzed!");

	m_pReadBuffer->bindColorAsTexture(0, 0);
	m_pWriteBuffer->renderToFSQ();
	m_pReadBuffer->unbindTexture(0);
	swap();
}

void PostProcessBuffer::drawToScreen()
{
	SAT_ASSERT(_IsInit == true, "Post Processing Buffer ot initialzed!");

	m_pWriteBuffer->unbind();
	m_pReadBuffer->bindColorAsTexture(0, 0);
	FrameBuffer::drawFSQ();
	m_pReadBuffer->unbindTexture(0);
}

void PostProcessBuffer::swap()
{
	std::swap(m_pReadBuffer, m_pWriteBuffer);
}
