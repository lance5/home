#pragma once

class CMatrix
{
public:
	union
	{
		struct 
		{
			float    _11, _12, _13, _14;
			float    _21, _22, _23, _24;
			float    _31, _32, _33, _34;
			float    _41, _42, _43, _44;
		};
		float m[4][4];
	};
	CMatrix()
	{
		Normalize();
	}
	~CMatrix() {}

	float* operator[]( uint32 n ) { return m[n]; }
	const float* operator[]( uint32 n ) const { return m[n]; }

	CMatrix operator*( const CMatrix& a ) const
	{
		CMatrix mat;

		for( uint8 col = 0; col < 4; ++col )
		{
			for( uint8 row = 0; row < 4; ++row )
			{
				mat[col][row] =
					(*this)[row][0] * a[0][col] +
					(*this)[row][1] * a[1][col] +
					(*this)[row][2] * a[2][col] +
					(*this)[row][3] * a[3][col];
					
			}
		}
		return mat;
	}

	void Normalize()
	{
		_11 = 1.0f; _12 = 0.0f; _13 = 0.0f; _14 = 0.0f;
		_21 = 0.0f; _22 = 1.0f; _23 = 0.0f; _24 = 0.0f;
		_31 = 0.0f; _32 = 0.0f; _33 = 1.0f; _34 = 0.0f;
		_41 = 0.0f; _42 = 0.0f; _43 = 0.0f; _44 = 1.0f;
	}

	void SetOffset( const CVector3f& vOffset )
	{
		Normalize();

		_41 = vOffset.x;
		_42 = vOffset.y;
		_43 = vOffset.z;
	}

	void SetRatio( const CVector3f& vRatio )
	{
		Normalize();

		_11 = vRatio.x;
		_22 = vRatio.y;
		_33 = vRatio.z;
		_44 = 1;
	}
};