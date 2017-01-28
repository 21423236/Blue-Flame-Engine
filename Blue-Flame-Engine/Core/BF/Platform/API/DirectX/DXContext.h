#pragma once
#include <d3d11.h>
#include "BF/Math/Vector4.h"
#include "BF/Common.h"

namespace BF
{
	namespace Graphics
	{
		namespace API
		{
			enum class PrimitiveType;
		}
	}

	namespace Platform
	{
		namespace API
		{
			namespace DirectX
			{
				class BF_API DXContext
				{
					private:
						ID3D11Device* device;
						ID3D11DeviceContext* context;
						IDXGISwapChain* swapChain;
						ID3D11RenderTargetView* renderTarget;
						ID3D11RasterizerState* rasterizerState;
						ID3D11DepthStencilView* zBuffer;
						ID3D11BlendState *blendState;
						D3D_PRIMITIVE_TOPOLOGY D3DPrimitiveType;
						bool vsync;

					public:
						DXContext();
						~DXContext();

						void Initialize();
						void Clear(const Math::Vector4& Color);
						void SwapBuffers();
						void Draw(unsigned int vertexCount);
						void CleanUp();

						void SetPrimitiveType(Graphics::API::PrimitiveType primitiveType);
						void EnableDepthBuffer(bool state);
						void EnableBlending(bool state);
						void EnableVsync(bool state);

						inline ID3D11Device* GetDevice() const { return device; }
						inline ID3D11DeviceContext* GetContext() const { return context; }
						inline const IDXGISwapChain* GetSwapChain() const { return swapChain; }

					private:
						void CreateDeviceAndSwapChain();
						void CreateBackBuffer();
						void CreateRasterizerState();
						void CreateDepthBuffer();
						void SetViewPort();
				};
			}
		}
	}
}