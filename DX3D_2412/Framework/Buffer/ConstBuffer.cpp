#include "Framework.h"

ConstBuffer::ConstBuffer(void* data, UINT dataSize)
    : data(data), dataSize(dataSize)
{
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = dataSize;
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    DEVICE->CreateBuffer(&bufferDesc, nullptr, &buffer);
}

ConstBuffer::~ConstBuffer()
{
    buffer->Release();
}

void ConstBuffer::SetVS(UINT slot)
{
    DC->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
    DC->VSSetConstantBuffers(slot, 1, &buffer);
}

void ConstBuffer::SetPS(UINT slot)
{
    DC->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
    DC->PSSetConstantBuffers(slot, 1, &buffer);
}

void ConstBuffer::SetCS(UINT slot)
{
    DC->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
    DC->CSSetConstantBuffers(slot, 1, &buffer);
}

void ConstBuffer::SetGS(UINT slot)
{
    DC->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
    DC->GSSetConstantBuffers(slot, 1, &buffer);
}

void ConstBuffer::SetHS(UINT slot)
{
    DC->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
    DC->HSSetConstantBuffers(slot, 1, &buffer);
}

void ConstBuffer::SetDS(UINT slot)
{
    DC->UpdateSubresource(buffer, 0, nullptr, data, 0, 0);
    DC->DSSetConstantBuffers(slot, 1, &buffer);
}
