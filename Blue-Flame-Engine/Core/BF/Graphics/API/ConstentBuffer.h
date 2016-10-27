#pragma once
#ifdef BF_PLATFORM_WINDOWS
	#include "BF/Platform/API/DirectX/DXConstentBuffer.h"
#endif
#if defined (BF_PLATFORM_WINDOWS) || defined (BF_PLATFORM_LINUX) || defined (BF_PLATFORM_WEBGL)
	#include "BF/Platform/API/OpenGL/GLConstentBuffer.h"
#endif

#include "Shader.h"

namespace BF
{
	namespace Graphics
	{
		namespace API
		{
			class BF_API ConstentBuffer
			{
				private:
					Context* context;
					Shader* shader;
#ifdef BF_PLATFORM_WINDOWS
					Platform::API::DirectX::DXConstentBuffer* dxConstentBuffer;
#endif
#if defined (BF_PLATFORM_WINDOWS) || defined (BF_PLATFORM_LINUX) || defined (BF_PLATFORM_WEBGL)
					Platform::API::OpenGL::GLConstentBuffer* glConstentBuffer;
#endif
				public:
					ConstentBuffer(Context* context, Shader* shader);
					~ConstentBuffer();

					void Create(void* data, unsigned int size, unsigned int bindingIndex);
					void Update(void* data, unsigned int size);
			};
		}
	}
}