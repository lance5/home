#pragma once

class CMaterial;
class CResourceModel
	: public IResourceListener
{
	SModelData							m_modelData;
	std::map<std::string, CMaterial*>	m_mapMaterial;
public:
	CResourceModel();
	~CResourceModel();

	virtual void						OnFileLoaded( const char* szFileName, const byte* szBuffer, const uint32 nSize );
	void								OnLoadMtllib( const char* szFileName, const byte* szBuffer, const uint32 nSize );
};