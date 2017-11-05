#pragma once

#define SAFE_DELETE(ptr) if(ptr){delete ptr;ptr=nullptr;}
#define SAFE_DELETE_GROUP(ptr) if(ptr){delete[] ptr;ptr=nullptr;}

#define Log std::cout
#define ErrLog std::cout<<"ERROR : "
#define Throw(szBuffer) (throw exception(szBuffer))
#define Assert(condition) if(!(condition)){Throw(#condition);}

#define Min( a, b ) ((a)>(b)?(b):(a))
#define Max( a, b ) ((a)>(b)?(a):(b))
#define Limit( nMin, nMax, nValue ) Min(nMax,Max(nMin,nValue))