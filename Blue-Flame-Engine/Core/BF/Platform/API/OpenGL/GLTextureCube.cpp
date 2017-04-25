#include "GLTextureCube.h"
#include "BF/Platform/API/OpenGL/GLError.h"

namespace BF
{
	namespace Platform
	{
		namespace API
		{
			namespace OpenGL
			{
				using namespace std;
				using namespace BF::Graphics::API;

				GLTextureCube::GLTextureCube()
				{
				}

				GLTextureCube::~GLTextureCube()
				{
				}

				void GLTextureCube::Create(vector<Texture::TextureData>& textureData, Texture::Format format, Texture::Wrap wrap, Texture::Filter filter)
				{
					GLCall(glGenTextures(1, &textureID));
					GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, textureID));

					for (GLuint i = 0; i < textureData.size(); i++)
						GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GetGLTextureFormat(format), textureData[i].width, textureData[i].height, 0, GetGLTextureFormat(format), GL_UNSIGNED_BYTE, textureData[i].buffer));

					GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GetGLTextureWrap(wrap)));
					GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GetGLTextureWrap(wrap)));
					GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GetGLTextureWrap(wrap)));

					switch (filter)
					{
						case Texture::Filter::Point:
						{
							GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
							GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

							break;
						}
						case Texture::Filter::Bilinear:
						{
							GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
							GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

							break;
						}
						case Texture::Filter::Trilinear:
							break;
						case Texture::Filter::AnisotropicX2:
							break;
						case Texture::Filter::AnisotropicX4:
							break;
						case Texture::Filter::AnisotropicX8:
							break;
						case Texture::Filter::AnisotropicX16:
							break;
						default:
							break;
					}
					
					GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
				}

				void GLTextureCube::Bind() const
				{
					GLCall(glActiveTexture(GL_TEXTURE0 + 0));
					GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, textureID));
				}

				void GLTextureCube::Unbind() const
				{
					GLCall(glActiveTexture(GL_TEXTURE0 + 0));
					GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
				}

				int GLTextureCube::GetGLTextureFormat(Texture::Format format) const
				{
					switch (format)
					{
						case Texture::Format::R8: return GL_RED;
						case Texture::Format::R8G8: return GL_RG;
						case Texture::Format::R8G8B8: return GL_RGB;
						case Texture::Format::R8G8B8A8: return GL_RGBA;
						default: return GL_RGBA;
					}
				}

				int GLTextureCube::GetGLTextureWrap(Texture::Wrap wrap) const
				{
					switch (wrap)
					{
						case Texture::Wrap::Repeat: return GL_REPEAT;
						case Texture::Wrap::MirroredReapeat: return GL_MIRRORED_REPEAT;
						case Texture::Wrap::ClampToEdge: return GL_CLAMP_TO_EDGE;
						
#if defined (BF_PLATFORM_WINDOWS) || defined (BF_PLATFORM_LINUX)
						case Texture::Wrap::ClampToBorder: return GL_CLAMP_TO_BORDER;
#endif

						default: return GL_REPEAT;
					}
				}
			}
		}
	}
}