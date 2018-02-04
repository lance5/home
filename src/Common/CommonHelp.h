#pragma once

#define SAFE_DELETE(ptr) if(ptr){delete ptr;ptr=nullptr;}
#define SAFE_DELETE_GROUP(ptr) if(ptr){delete[] ptr;ptr=nullptr;}

#define Log std::cout
#define ErrLog std::cout<<"ERROR : "
#define Throw(szBuffer) (throw std::exception(szBuffer))
#define Assert(condition) if(!(condition)){Throw(#condition);}

#define Min( a, b ) ((a)>(b)?(b):(a))
#define Max( a, b ) ((a)>(b)?(a):(b))
#define Limit( nMin, nMax, nValue ) Min(nMax,Max(nMin,nValue))

#define ELEM_COUNT(aryBuffer) (sizeof(aryBuffer)/sizeof(aryBuffer[0]))

template<class _Type>
class TConstString
{
	const _Type*		m_szBuffer;
	uint32				m_nSize;
public:
	TConstString() : m_szBuffer( NULL ) , m_nSize( 0 ) {}
	TConstString( const char* szBuffer, uint32 nSize )
		: m_szBuffer( szBuffer )
		, m_nSize( nSize ) {}
	~TConstString() {}

	const _Type*		c_str() const { return m_szBuffer; }
	uint32				size() const { return m_nSize; }
};

typedef TConstString<char>     cstring;

template<class _Type>
inline _Type tolower( _Type c ){ return c >= 'A' && c <= 'Z' ? c - 'A' + 'a' : c; }
template<class _Type>
inline _Type toupper( _Type c ){ return c >= 'a' && c <= 'z' ? c - 'a' + 'A' : c; }
template<class _Type, class _SizeType>
inline void	stringToLower(_Type szBuffer, _SizeType nSize)
{
	for( _SizeType i = 0; i < nSize && szBuffer[i] != '\0'; ++i )
		szBuffer[i] = tolower( szBuffer[i] );
}
template<class _Type, class _SizeType>
inline void	stringToUpper(_Type szBuffer, _SizeType nSize)
{
	for( _SizeType i = 0; i < nSize && szBuffer[i] != '\0'; ++i )
		szBuffer[i] = toupper( szBuffer[i] );
}

template<class _DataType>
inline void partition( const cstring& cstrString, _DataType szChar, 
	std::vector<cstring>& vecResult )
{
	uint32 nStartPos = 0;
	for ( uint32 i = 0; i < cstrString.size(); ++i )
	{
		if( cstrString.c_str()[i] != szChar )
			continue;
		if( i == nStartPos )
			continue;

		cstring strWord( cstrString.c_str() + nStartPos, i - nStartPos );
		nStartPos = i + 1;
		vecResult.push_back( strWord );
	}
	if( cstrString.c_str()[nStartPos] == '\0' )
		return;
	vecResult.push_back( cstring( cstrString.c_str() + nStartPos, cstrString.size() - nStartPos ) );
}