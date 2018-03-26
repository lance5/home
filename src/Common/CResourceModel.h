#pragma once

class CResourceModel
	: public IResourceListener
	, private SModelData
{
public:
	CResourceModel();
	~CResourceModel();

	virtual void						OnFileLoaded( const char* szFileName, const byte* szBuffer, const uint32 nSize );
	void								OnLoadMtllib( const char* szFileName, const byte* szBuffer, const uint32 nSize );
};