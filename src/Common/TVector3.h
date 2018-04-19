#pragma once

template<class DataType>
class TVector3
{
public:
	union
	{
		DataType x, y, z;
		DataType value[3];
	};
	TVector3() : x(), y(), z() {}
	TVector3( DataType a ) : x( a ), y( a ), z( a ) {}
	TVector3( DataType a, DataType b, DataType c ) : x( a ), y( b ), z( c ) {}
	~TVector3() {}

	DataType& operator[]( uint32 n ) { return value[n]; }
	const DataType& operator[]( uint32 n ) const { return value[n]; }
};

typedef TVector3<float> CVector3f;
