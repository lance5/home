#pragma once

class CMaterial;

class CRenderModel
{
public:
	enum
	{
		eBufferType_Vertex,
		eBufferType_Normal,
		eBufferType_TexCoord,
		eBufferType_Count,
	};
private:
	uint32							m_nVertexArrays;
	uint32							m_aryVertexBuffer[eBufferType_Count];
	uint32							m_aryBufferElement[eBufferType_Count];

public:
	CRenderModel();
	~CRenderModel();

	template<typename Data>
	void							SetVertexBuffer( uint8 nType, const Data* pData, uint32 nSize );
	template<typename Data>
	void							SetBufferElement( uint8 nType, const Data* pData, uint32 nSize );
};
