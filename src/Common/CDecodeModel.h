#pragma once

class CMaterial;
class CRenderModel;

class CDecodeModel
	: public IResourceListener
{
	struct SObjectIndex
	{
		std::string					m_strName;
		bool						m_bSmooth;
		std::vector<uint32>			m_vecVertexIndex;
		std::vector<uint32>			m_vecNoramIndex;
		std::vector<uint32>			m_vecTexCoordIndex;
		CMaterial*					m_Material;

		SObjectIndex() : m_Material( nullptr ) {}
	};

private:
	std::vector<float>				m_vecVertex;
	std::vector<float>				m_vecNormal;
	std::vector<float>				m_vecTexCoord;
	std::vector<SObjectIndex>		m_vecObject;

public:
	CDecodeModel();
	~CDecodeModel();

	void			FillRenderModel( CRenderModel& model );

	virtual void	OnFileLoaded( const char* szFileName, const byte* szBuffer, const uint32 nSize );
	void			OnLoadMtllib( const char* szFileName, const byte* szBuffer, const uint32 nSize, std::map<std::string, CMaterial*>& mapMaterial );
};