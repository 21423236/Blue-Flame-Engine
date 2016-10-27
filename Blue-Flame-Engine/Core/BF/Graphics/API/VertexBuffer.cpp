#include "VertexBuffer.h"

namespace BF
{
	namespace Graphics
	{
		namespace API
		{
			VertexBuffer::VertexBuffer(Context* context, Shader* shader) :
				context(context)
			{
#ifdef BF_PLATFORM_WINDOWS
				if (Context::GetRenderAPI() == RenderAPI::DirectX)
					dxVertexBuffer = new Platform::API::DirectX::DXVertexBuffer(context->GetDXContext(), shader->GetDXShader());
#endif
#if defined (BF_PLATFORM_WINDOWS) || defined (BF_PLATFORM_LINUX) || defined (BF_PLATFORM_WEBGL)
				if (Context::GetRenderAPI() == RenderAPI::OpenGL)
					glVertexBuffer = new Platform::API::OpenGL::GLVertexBuffer();
#endif
			}

			VertexBuffer::~VertexBuffer()
			{
			}

			void VertexBuffer::Create(void* data, unsigned int size)
			{
#ifdef BF_PLATFORM_WINDOWS
				if (Context::GetRenderAPI() == RenderAPI::DirectX)
					dxVertexBuffer->Create(data, size);
#endif
#if defined (BF_PLATFORM_WINDOWS) || defined (BF_PLATFORM_LINUX) || defined (BF_PLATFORM_WEBGL)
				if (Context::GetRenderAPI() == RenderAPI::OpenGL)
					glVertexBuffer->Create(data, size);
#endif
			}

			void* VertexBuffer::Map() const
			{
#ifdef BF_PLATFORM_WINDOWS
				//if (Context::GetRenderAPI() == RenderAPI::DirectX)
				//	dxVertexBuffer->Bind();
#endif
#if defined (BF_PLATFORM_WINDOWS) || defined (BF_PLATFORM_LINUX) || defined (BF_PLATFORM_WEBGL)
				if (Context::GetRenderAPI() == RenderAPI::OpenGL)
					return glVertexBuffer->Map();
#endif
				return nullptr;
			}

			void VertexBuffer::Unmap() const
			{
#ifdef BF_PLATFORM_WINDOWS
				//if (Context::GetRenderAPI() == RenderAPI::DirectX)
				//	dxVertexBuffer->Bind();
#endif
#if defined (BF_PLATFORM_WINDOWS) || defined (BF_PLATFORM_LINUX) || defined (BF_PLATFORM_WEBGL)
				if (Context::GetRenderAPI() == RenderAPI::OpenGL)
					glVertexBuffer->Unmap();
#endif
			}

			void VertexBuffer::Bind() const
			{
#ifdef BF_PLATFORM_WINDOWS
				if (Context::GetRenderAPI() == RenderAPI::DirectX)
					dxVertexBuffer->Bind();
#endif
#if defined (BF_PLATFORM_WINDOWS) || defined (BF_PLATFORM_LINUX) || defined (BF_PLATFORM_WEBGL)
				if (Context::GetRenderAPI() == RenderAPI::OpenGL)
					glVertexBuffer->Bind();
#endif
			}

			void VertexBuffer::Unbind() const
			{
#ifdef BF_PLATFORM_WINDOWS
				if (Context::GetRenderAPI() == RenderAPI::DirectX)
					dxVertexBuffer->Unbind();
#endif
#if defined (BF_PLATFORM_WINDOWS) || defined (BF_PLATFORM_LINUX) || defined (BF_PLATFORM_WEBGL)
				if (Context::GetRenderAPI() == RenderAPI::OpenGL)
					glVertexBuffer->Unbind();
#endif
			}
		}
	}
}