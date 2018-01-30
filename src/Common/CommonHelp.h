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
inline void partition( const _DataType* szString, _DataType szChar, 
	std::vector<std::basic_string<_DataType>>& vecResult )
{
	uint32 nStartPos = 0;
	for ( uint32 i = 0; szString[i] != '\0'; ++i )
	{
		if( szString[i] != szChar )
			continue;
		if( i == nStartPos )
			continue;

		string strWord( szString + nStartPos, i - nStartPos );
		nStartPos = i + 1;
		vecResult.push_back( strWord );
	}
	if( szString[nStartPos] == '\0' )
		return;
	vecResult.push_back( string( szString + nStartPos ) );
}