#include "DXIndexBuffer.h"

namespace BF
{
	namespace Platform
	{
		namespace API
		{
			namespace DirectX
			{
				DXIndexBuffer::DXIndexBuffer(DXContext* dxContext) : 
					dxContext(dxContext), buffer(nullptr), hr(0), count(0)
				{
				}

				DXIndexBuffer::~DXIndexBuffer()
				{
				}

				void DXIndexBuffer::Create(const unsigned int* const indices, unsigned int count)
				{
					this->count = count;

					D3D11_BUFFER_DESC bufferDesc;
					ZeroMemory(&bufferDesc, sizeof(bufferDesc));

					bufferDesc.Usage = D3D11_USAGE_DEFAULT;
					bufferDesc.ByteWidth = count * sizeof(unsigned int);
					bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
					bufferDesc.CPUAccessFlags = 0;
					bufferDesc.MiscFlags = 0;

					D3D11_SUBRESOURCE_DATA subData;
					ZeroMemory(&subData, sizeof(subData));

					subData.pSysMem = indices;
					subData.SysMemPitch = 0;
					subData.SysMemSlicePitch = 0;

					hr = dxContext->GetDevice()->CreateBuffer(&bufferDesc, &subData, &buffer);

					if (FAILED(hr))
					{
						//print error
					}
				}

				void DXIndexBuffer::Bind() const
				{
					dxContext->GetContext()->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
				}

				void DXIndexBuffer::Unbind() const
				{
				}
			}
		}
	}
}