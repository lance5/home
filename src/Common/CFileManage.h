#pragma once
#include "TypeDef.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

enum EImageFormat
{
	eIF_RED,
	eIF_RGB,
	eIF_RGBA,
	eIF_INVALID,
};

class CFileManage
{
	map<string, byte*>		m_mapCache;

	CFileManage();
	~CFileManage();
public:

	static CFileManage&		Inst();
	const byte*				Load( const char* szFileName );
	const byte*				LoadImg( const char* szFileName, uint32& nImageWidth, uint32& nImageHeight, EImageFormat& nImageFormat );

	string					GetFileNameExtend( const char* szFileName );
};

