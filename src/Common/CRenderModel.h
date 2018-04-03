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
	struct SObjectElement
	{
		uint32						m_Element[eBufferType_Count];
		bool						m_bSmooth;
		CMaterial*					m_Material;
	};

	uint32 m_nVertexArrays;
	uint32 m_nVertexBuffer;
	std::vector<SObjectElement> m_vecElement;

public:
	CRenderModel();
	~CRenderModel();

	template<typename Data>
	void SetVertexBuffer( const Data* aryData[eBufferType_Count],
		const uint32 arySize[eBufferType_Count] );

	template<typename Data>
	void PushObjectData( const Data* aryData[eBufferType_Count],
		const uint32 arySize[eBufferType_Count], 
		CMaterial* pMaterail, bool bSmooth );

	void RenderAllObject();
};
