#pragma once

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
};

typedef TVector2<float> CVector2f;
