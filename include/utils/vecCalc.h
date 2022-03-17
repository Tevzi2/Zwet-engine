#pragma once

#include <core.h>
#include <structs.h>

// funkcije za racunanje z vektorji in matrikami

namespace ZWET
{
	float vecLen(vec3);

	float dotPru(vec3, vec3);

	vec3 normalize(vec3);

	vec3 crossPru(vec3, vec3);

	vec3 vecSub(vec3, vec3);

	vec3 vecAdd(vec3, vec3);

	vec3 vecPru(vec3, float);

	vec3 vecDiv(vec3, float);

	mat4 rotX(float);

	mat4 rotY(float);
	
	mat4 rotZ(float);

	mat4 translationMat(float, float, float);

	mat4 quickInverse(mat4);

	vec3 customVecMultiply(mat4, vec3);

	mat4 matrixPointAt(vec3&, vec3&, vec3&);

	mat4 transposeMat(mat4);

	mat4 createWorldMatrix(vec3, vec3, float);

	mat4 createViewMatrix(mat4, vec3&, vec3&, vec3&, float, float, float);

	mat4 pointAtMatrix(vec3&, vec3&, vec3&);
};