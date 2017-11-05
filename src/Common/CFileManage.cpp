#include "CFileManage.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "common.h"

CFileManage::CFileManage()
{
}


CFileManage::~CFileManage()
{
	for( map<string, byte*>::iterator it = m_mapCache.begin(); it != m_mapCache.end(); ++it )
		SAFE_DELETE_GROUP( it->second );
}

CFileManage& CFileManage::Inst()
{
	static CFileManage m_instance;
	return m_instance;
}

const byte* CFileManage::Load( const char * szFileName )
{
	FILE* pFile;
	fopen_s( &pFile, szFileName, "r" );
	vector<byte> vecData;
	char szBuffer;
	while( ( szBuffer = fgetc( pFile ) ) != EOF )
		vecData.push_back( szBuffer );
	uint32 nSize = vecData.size() + 1;
	byte* pDesData = new byte[nSize];
	memcpy( pDesData, &vecData[0], nSize - 1 );
	pDesData[nSize-1] = NULL;
	m_mapCache[string( szFileName )] = pDesData;
	fclose( pFile );
	return pDesData;
}

const byte* CFileManage::LoadImg( const char* szFileName, uint32& nImageWidth, uint32& nImageHeight, EImageFormat& nImageFormat )
{
	int32 nWidth, nHeight, nrChannels;
	unsigned char* pSrcData = stbi_load( szFileName, &nWidth, &nHeight, &nrChannels, 0 );
	if( !pSrcData || nWidth <= 0 || nHeight <= 0 )
		return nullptr;

	nImageWidth = nWidth;
	nImageHeight = nHeight;
	switch( nrChannels )
	{
	case 1:
		nImageFormat = eIF_RED;
		break;
	case 3:
		nImageFormat = eIF_RGB;
		break;
	case 4:
		nImageFormat = eIF_RGBA;
		break;
	}
	uint32 nSize = nWidth*nHeight*nrChannels + 1;
	byte* pDesData = new byte[nSize];
	memcpy( pDesData, pSrcData,  sizeof( byte ) * ( nSize - 1 ) );
	pDesData[nSize-1] = NULL;
	stbi_image_free( pSrcData );

	m_mapCache[string(szFileName)] = pDesData;
	return pDesData;
}

string CFileManage::GetFileNameExtend(const char * szFileName)
{
	uint32 nLastPos = INVALIDU32BYTE;
	for (uint32 i = 0; szFileName[i] != '\0'; ++i)
	{
		if (szFileName[i] == '.')
			nLastPos = i;
		Assert( i < INVALIDU32BYTE );
	}
	if( nLastPos == INVALIDU32BYTE )
		return string();
	return string( szFileName + nLastPos + 1 );
}
