#pragma once

#include <iostream>
#include <exception>

#define SAFE_DELETE(ptr) if(ptr){delete ptr;ptr=nullptr;}
#define SAFE_DELETE_GROUP(ptr) if(ptr){delete[] ptr;ptr=nullptr;}

#define Log std::cout
#define ErrLog std::cout<<"ERROR : "
#define Throw(szBuffer) (throw std::exception(szBuffer))
#define Assert(condition) if(!(condition)){Throw(#condition);}

#define Min( a, b ) ((a)>(b)?(b):(a))
#define Max( a, b ) ((a)>(b)?(a):(b))
#define Limit( nMin, nMax, nValue ) Min(nMax,Max(nMin,nValue))

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