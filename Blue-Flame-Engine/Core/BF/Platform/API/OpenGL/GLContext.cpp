#include "GLContext.h"
#include "BF/Engine.h"
#include "BF/Graphics/API/Context.h"
#include "BF/Platform/API/OpenGL/GLError.h"

namespace BF
{
	namespace Platform
	{
		namespace API
		{
			namespace OpenGL
			{
				using namespace BF::Graphics::API;

				GLContext::GLContext() :
					initialized(false)
				{
				}

				GLContext::~GLContext()
				{
				}

				void GLContext::Initialize()
				{
				}

				void GLContext::SetPrimitiveType(PrimitiveType primitiveType)
				{
					switch (primitiveType)
					{
						case PrimitiveType::PointList:
						{
							GL_PRIMITIVE_TYPE = GL_POINTS;
							break;
						}
						case PrimitiveType::LineList:
						{
							GL_PRIMITIVE_TYPE = GL_LINES;
							break;
						}
						case PrimitiveType::LineStrip:
						{
							GL_PRIMITIVE_TYPE = GL_LINE_STRIP;
							break;
						}
						case PrimitiveType::TriangleList:
						{
							GL_PRIMITIVE_TYPE = GL_TRIANGLES;
							break;
						}
						case PrimitiveType::TriangeStrip:
						{
							GL_PRIMITIVE_TYPE = GL_TRIANGLE_STRIP;
							break;
						}
						default:
							break;
					}
				}

				void GLContext::Clear(const Graphics::Color& color)
				{
					GLCall(glClearColor(color.r, color.g, color.b, color.a));
					GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
				}

				void GLContext::Render(GLsizei count)
				{
					GLCall(glDrawElements(GL_PRIMITIVE_TYPE, count, GL_UNSIGNED_INT, nullptr));
				}

				void GLContext::SwapBuffers()
				{
				}

				void GLContext::CleanUp()
				{
				}

				void GLContext::EnableDepthBuffer(bool state)
				{
					if (state)
						GLCall(glEnable(GL_DEPTH_TEST));
					else
						GLCall(glDisable(GL_DEPTH_TEST));
				}

				void GLContext::EnableDepthMask(bool state)
				{
					if (state)
						GLCall(glDepthMask(GL_TRUE));
					else
						GLCall(glDepthMask(GL_FALSE));
				}

				void GLContext::EnableBlending(bool state)
				{
					if (state)
					{
						GLCall(glEnable(GL_BLEND));
						GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
					}
					else
						GLCall(glDisable(GL_BLEND));
				}

				void GLContext::EnableVsync(bool state)
				{
				}

				void GLContext::EnableScissor(bool state)
				{
					if (state)
						glEnable(GL_SCISSOR_TEST);
					else
						glDisable(GL_SCISSOR_TEST);
				}

				void GLContext::SetScissor(const Math::Rectangle& rectangle)
				{
					int height = Engine::GetWindow().GetClientHeight() - rectangle.height - rectangle.y;
					glScissor(rectangle.x, height, rectangle.width, Engine::GetWindow().GetClientHeight() - height - rectangle.y);
				}

				void GLContext::SetViewport(const Math::Rectangle& rectangle)
				{
					if (initialized)
						GLCall(glViewport(rectangle.x, rectangle.y, rectangle.width, rectangle.height));
				}
			}
		}
	}
}