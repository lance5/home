#pragma once

#include "CRenderModel.h"

class CMaterial;

class CDecodeModel
	: public IResourceListener
{
	struct SObjectIndex
	{
		std::string					m_strName;
		bool						m_bSmooth;
		std::vector<SVectexData>	m_vecVectexData;
		CMaterial*					m_Material;

		SObjectIndex() : m_Material( nullptr ) {}
	};

private:
	std::vector<SObjectIndex>		m_vecObject;

public:
	CDecodeModel();
	~CDecodeModel();

	void			FillRenderModel( CRenderModel& model );

	virtual void	OnFileLoaded( const char* szFileName, const byte* szBuffer, const uint32 nSize );
	void			OnLoadMtllib( const char* szFileName, const byte* szBuffer, const uint32 nSize, std::map<std::string, CMaterial*>& mapMaterial );
};