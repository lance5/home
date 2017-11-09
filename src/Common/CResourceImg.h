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
	public CResourceType
{
	uint32			m_nWidth;
	uint32			m_nHeight;
	EImageFormat	m_nFormat;
	char*			m_pImageData;

public:
	CResourceImg( const byte* szBuffer, uint32 nSize );
	virtual ~CResourceImg();

	const char*		GetImageData() const { return m_pImageData; }
	uint32			GetImageWidth() const { return m_nWidth; }
	uint32			GetImageHeight() const { return m_nHeight; }
	EImageFormat	GetImageFormat() const { return m_nFormat; }
};

