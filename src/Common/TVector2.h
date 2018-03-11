#pragma once

#include <math.h>

template<class DataType>
class TVector2
{
public:
	union
	{
		DataType x, y;
		DataType value[2];
	};
	TVector2() : x(), y() {}
	TVector2( DataType a, DataType b ) : x( a ), y( b ) {}
	~TVector2() {}

	DataType& operator[]( uint32 n ) { return value[n]; }
	const DataType& operator[]( uint32 n ) const { return value[n]; }

	DataType& operator/( DataType n ) { return TVector2<DataType>( x / n, y / n ); }
	const DataType& operator/( DataType n ) const { return TVector2<DataType>( x / n, y / n ); }

	void operator/=( DataType n ) { return x /= n;y /= n; }

	float Len()
	{
		DataType value = x * x + y * y;
		if ( value = DataType() )
			return DataType();
		return  sqrt( value );
	}

	void Normal()
	{
		DataType len = Len();
		if ( len == DataType() )
			return;
		*this /= len;
	}
};

typedef TVector2<float> CVector2f;
