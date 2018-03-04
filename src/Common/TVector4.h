#pragma once

template<class DataType>
class TVector4
{
public:
	union
	{
		DataType x, y, z, w;
		DataType value[4];
	};
	TVector4() : x(), y(), z(), w() {}
	TVector4( DataType a, DataType b, DataType c, DataType d ) 
		: x( a ), y( b ), z( c ), w( d ) {}
	~TVector4() {}

	DataType& operator[]( uint32 n ) { return value[n]; }
	const DataType& operator[]( uint32 n ) const { return value[n]; }
};

typedef TVector4<float> CVector4f;
