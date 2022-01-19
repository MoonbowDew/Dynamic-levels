#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(GameObject* gameobj) : FBGameObj(gameobj)
{
    glGenFramebuffers(1, &m_FrameBuffer_ID); // create 1 buffer and assign "buffer" id (id 0l)
    //CreateColorAttachmentTexture(); replaced with FBGameObj
    CreateRenderBuffer();
    //BindRenderBuffer();
    Bind();
    //AttachTexture();
    AttachRenderBuffer();
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_FrameBuffer_ID);
}

//void FrameBuffer::BindRenderBuffer() const
//{
//    glBindRenderbuffer(GL_FRAMEBUFFER, m_FrameBuffer_ID); // select "buffer" id
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, FBGameObj->GetTexture()->GetWidth(), FBGameObj->GetTexture()->GetHeight()); // previous: GL_STENCIL_COMPONENTS
//}

void FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer_ID); // select "buffer" id
}

void FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // select "buffer" id
}

void FrameBuffer::CreateColorAttachmentTexture(const std::string& path)
{

	//stbi_set_flip_vertically_on_load(1);
	//m_LocalImageBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

 //   glGenTextures(1, &m_TextureColorBuffer_ID);
 //   glBindTexture(GL_TEXTURE_2D, m_TextureColorBuffer_ID);
 //   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalImageBuffer);
 //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glBindTexture(GL_TEXTURE_2D, 0); // ??? questionable

	//if (m_LocalImageBuffer)
	//	stbi_image_free(m_LocalImageBuffer);
}

//void FrameBuffer::AttachTexture()
//{
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBGameObj->GetTexture()->GetRendererID(), 0);
//}

void FrameBuffer::CreateRenderBuffer()
{
    glGenRenderbuffers(1, &m_rbo_ID);
}

void FrameBuffer::AttachRenderBuffer()
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo_ID);
}

void FrameBuffer::CheckIfComplete()
{
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR:: Framebuffer is not complete!";
    else std::cout << "Framebuffer is complete! :)";
}