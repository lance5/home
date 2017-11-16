#pragma once
#include "CFileManage.h"

enum EImageFormat
{
	eIF_RED,
	eIF_RGB,
	eIF_RGBA,
	eIF_INVALID,
};

class CResourceImg :
	public IResourceCallback
{
	uint32			m_nWidth;
	uint32			m_nHeight;
	EImageFormat	m_nFormat;
	char*			m_pImageData;
public:
	CResourceImg();
	virtual ~CResourceImg();

	virtual void	OnFileLoaded( const char* szFileName, const byte* szBuffer, const uint32 nSize );

	const char*		GetImageData() const { return m_pImageData; }
	uint32			GetImageWidth() const { return m_nWidth; }
	uint32			GetImageHeight() const { return m_nHeight; }
	EImageFormat	GetImageFormat() const { return m_nFormat; }
};

