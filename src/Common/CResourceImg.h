#pragma once

class CResourceImg :
	public IResourceListener
{
	uint32			m_nWidth;
	uint32			m_nHeight;
	uint8			m_nFormat;
	byte*			m_pImageData;

	void			InitImageData( const byte* szBuffer, const uint32 nSize );
public:
	CResourceImg();
	CResourceImg( const byte* szBuffer, const uint32 nSize );
	virtual ~CResourceImg();

	virtual void	OnFileLoaded( const char* szFileName, const byte* szBuffer, const uint32 nSize );

	const byte*		GetImageData() const { return m_pImageData; }
	uint32			GetImageWidth() const { return m_nWidth; }
	uint32			GetImageHeight() const { return m_nHeight; }
	uint8			GetImageFormat() const { return m_nFormat; }
	
};

