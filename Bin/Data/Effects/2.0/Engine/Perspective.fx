#ifndef BE_PERSPECTIVE_H
#define BE_PERSPECTIVE_H

#include "Engine/BindPoints.fx"

/// Perspective constants.
struct PerspectiveLayout
{
	float4x4 ViewProj;		///< View-projection matrix.
	float4x4 ViewProjInv;	///< View-projection matrix inverse.

	float4x4 View;			///< View matrix.
	float4x4 ViewInv;		///< View matrix inverse.

	float4x4 Proj;			///< Projection matrix.
	float4x4 ProjInv;		///< Projection matrix inverse.
	
	float4 CamRight;		///< Camera right.
	float4 CamUp;			///< Camera up.
	float4 CamDir;			///< Camera direction.
	float4 CamPos;			///< Camera position.

	float2 NearFarPlane;	///< Near & far planes.

	float Time;				///< Time.
	float TimeStep;			///< Time Step.
};

#ifdef BE_PERSPECTIVE_SETUP
	cbuffer PerspectiveConstants : bindpoint(b0)
	{
		PerspectiveLayout Perspective;
	}
#else
	cbuffer prebound(PerspectiveConstants) : bindpoint(b0)
	{
		PerspectiveLayout Perspective;
	}
#endif

float3 FromSRGB(float3 c)
{
	return c * c;
}
float4 FromSRGB(float4 c)
{
	c.xyz *= c.xyz;
	return c;
}

float3 ToSRGB(float3 c)
{
	return sqrt(c);
}
float4 ToSRGB(float4 c)
{
	c.xyz = sqrt(c.xyz);
	return c;
}

#endif