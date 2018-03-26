#pragma once

class CMatrix
{
public:
	union
	{
		float	_11, _12, _13, _14,
			_21, _22, _23, _24,
			_31, _32, _33, _34,
			_41, _42, _43, _44;
		float value[4][4];
	};
	CMatrix()
	{
		Normalize();
	}
	~CMatrix() {}

	float* operator[]( uint32 n ) { return value[n]; }
	const float* operator[]( uint32 n ) const { return value[n]; }

	void Normalize()
	{
		_11 = 1.0f; _12 = 0.0f; _13 = 0.0f; _14 = 0.0f;
		_21 = 0.0f; _22 = 1.0f; _23 = 0.0f; _24 = 0.0f;
		_31 = 0.0f; _32 = 0.0f; _33 = 1.0f; _34 = 0.0f;
		_41 = 0.0f; _42 = 0.0f; _43 = 0.0f; _44 = 1.0f;
	}

	void SetOffset( CVector3f& vOffset )
	{
		Normalize();

		_41 = vOffset.x;
		_42 = vOffset.y;
		_43 = vOffset.z;
	}
};