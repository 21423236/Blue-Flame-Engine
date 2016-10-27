#include "DXVertexBuffer.h"

namespace BF
{
	namespace Platform
	{
		namespace API
		{
			namespace DirectX
			{
				using namespace BF::Graphics::API;

				DXVertexBuffer::DXVertexBuffer(DXContext* dxContext, DXShader* dxShader) :
					dxContext(dxContext), dxShader(dxShader), vertexBufferLayout(nullptr), buffer(nullptr), inputLayout(nullptr), hr(0)
				{
				}

				DXVertexBuffer::~DXVertexBuffer()
				{
				}

				void DXVertexBuffer::Create(const void* data, unsigned int size)
				{
					D3D11_BUFFER_DESC bufferDesc;
					ZeroMemory(&bufferDesc, sizeof(bufferDesc));

					bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
					bufferDesc.ByteWidth = size;
					bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
					bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

					hr = dxContext->GetDevice()->CreateBuffer(&bufferDesc, 0, &buffer);

					if (FAILED(hr))
						std::cout << "Could not create a vertex buffer." << std::endl;

					//Map buffer
					D3D11_MAPPED_SUBRESOURCE mappedSubResource;
					ZeroMemory(&mappedSubResource, sizeof(mappedSubResource));

					hr = dxContext->GetContext()->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);

					if (FAILED(hr))
						std::cout << "Could not map vertex buffer." << std::endl;

					memcpy(mappedSubResource.pData, data, size);
					dxContext->GetContext()->Unmap(buffer, 0);
				}

				void DXVertexBuffer::SetLayout(VertexBufferLayout* vertexBufferLayout)
				{
					this->vertexBufferLayout = vertexBufferLayout;

					D3D11_INPUT_ELEMENT_DESC* inputElementDesc = new D3D11_INPUT_ELEMENT_DESC[vertexBufferLayout->GetBufferElement().size()];
					
					for (size_t i = 0; i < vertexBufferLayout->GetBufferElement().size(); i++)
					{
						inputElementDesc[i].SemanticName = vertexBufferLayout->GetBufferElement()[i].name;
						inputElementDesc[i].SemanticIndex = 0;
						inputElementDesc[i].Format = GetDXDataType(vertexBufferLayout->GetBufferElement()[i].dataType);
						inputElementDesc[i].InputSlot = 0;
						inputElementDesc[i].AlignedByteOffset = vertexBufferLayout->GetBufferElement()[i].offset;
						inputElementDesc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
						inputElementDesc[i].InstanceDataStepRate = 0;
					}
					
					dxContext->GetDevice()->CreateInputLayout(inputElementDesc, (unsigned int)vertexBufferLayout->GetBufferElement().size(), dxShader->GetVSData(), dxShader->GetVSsize(), &inputLayout);
					delete[] inputElementDesc;
				}

				void DXVertexBuffer::Bind() const
				{
					unsigned int offset = 0;
					dxContext->GetContext()->IASetInputLayout(inputLayout);
					dxContext->GetContext()->IASetVertexBuffers(0, 1, &buffer, &vertexBufferLayout->GetBufferElement()[0].stride, &offset);
				}

				void DXVertexBuffer::Unbind() const
				{
				}

				DXGI_FORMAT DXVertexBuffer::GetDXDataType(DataType dataType)
				{
					switch (dataType)
					{
						case DataType::Byte:
						{
							break;
						}
						case DataType::Short:
						{
							break;
						}
						case DataType::Int:
						{
							break;
						}
						case DataType::Float:
						{
							return DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
							break;
						}
						case DataType::Float2:
						{
							return DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
							break;
						}
						case DataType::Float3:
						{
							return DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
							break;
						}
						case DataType::Float4:
						{
							return DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
							break;
						}
						case DataType::Double:
						{
							break;
						}
						default:
							break;
					}

					return DXGI_FORMAT();
				}
			}
		}
	}
}