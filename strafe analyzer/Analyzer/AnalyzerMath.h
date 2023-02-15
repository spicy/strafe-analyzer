#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "AnalyzerEnums.h"
#include "../Interfaces/Interfaces.h"
#include "../math/vector3d.h"
#include "../sdk+/sdk.h"

/// <summary>
/// Subtracts two angles and finds the smallest angle between any two angles
/// Input: two angles, Output: smallest angle between them
/// </summary>
inline double SubtractAngle(double angle1, double angle2)
{
	double temp = angle1 - angle2;

	if (temp > 180)
		temp -= 360;

	if (temp < -180)
		temp += 360;

	return temp;
}
 
/// <summary>
/// Converts a keydirection to radians
/// </summary>
/// <param name="keys"></param>
/// <returns></returns>
static inline double ButtonRadians(KeyDir keys)
{
	switch (keys) {
	case KeyDir::LEFT: return M_PI / 2;
	case KeyDir::RIGHT: return -M_PI / 2;
	case KeyDir::FORWARD: return 0;
	case KeyDir::BACK: return -M_PI;
	case KeyDir::BACK_LEFT: return 3 * M_PI / 4;
	case KeyDir::BACK_RIGHT: return -3 * M_PI / 4;
	case KeyDir::FORWARD_LEFT: return M_PI / 4;
	case KeyDir::FORWARD_RIGHT: return -M_PI;
	default: return 0;
	}
}

/// <summary>
/// Gets the difference between the angle of the mouseDir and Keydir
/// </summary>
/// <param name="mousedir"></param>
/// <param name="keydir"></param>
/// <returns></returns>
static inline double MouseAndKeyPhiDiff(MouseDir mousedir, KeyDir keydir)
{
	return SubtractAngle(ButtonRadians(static_cast<KeyDir>(mousedir)), ButtonRadians(keydir));
}

/// <summary>
/// Normalizes an angle sent to it, Keeps within (-180, 180)
/// Input: an angle, Output: the corrected angle (if even necessary)
/// </summary>
inline double NormalizeAngle(double angle)
{
	double newAngle = angle;
	while (newAngle < -180.0)
	{
		newAngle += 360.0;
	}
	while (newAngle > 180.0)
	{
		newAngle -= 360.0;
	}
	return newAngle;
}


/// <summary>
/// Converts negative radians to their positive counterpart, returns the converted rad
/// </summary>
inline double NegRadianToPos(double radian)
{
	while (radian < 0)
	{
		radian += 2 * M_PI;
	}
	return radian;
}

/// <summary>
/// Converts a (-180, 180) angle to (0, 360), returns the converted angle
/// </summary>
inline double NegAngleToPos(double angle)
{
	while (angle < 0)
	{
		angle += 360.0;
	}
	return angle;
}

#pragma region WorldToScreen
/// <summary>
/// Game seperate world to screen function. Supposed to work in either game (CSS/CSGO)
/// </summary>
inline inline bool screen_transform(const vec3_t& in, vec3_t& out)
{
	static auto& w2sMatrix = Interfaces::engine->world_to_screen_matrix();

	out.x = w2sMatrix.m[0][0] * in.x + w2sMatrix.m[0][1] * in.y + w2sMatrix.m[0][2] * in.z + w2sMatrix.m[0][3];
	out.y = w2sMatrix.m[1][0] * in.x + w2sMatrix.m[1][1] * in.y + w2sMatrix.m[1][2] * in.z + w2sMatrix.m[1][3];
	out.z = 0.0f;

	float w = w2sMatrix.m[3][0] * in.x + w2sMatrix.m[3][1] * in.y + w2sMatrix.m[3][2] * in.z + w2sMatrix.m[3][3];

	if (w < 0.001f) {
		out.x *= 100000;
		out.y *= 100000;
		return false;
	}

	out.x /= w;
	out.y /= w;

	return true;
}

/// <summary>
/// Returns the screen positions of a 3d vector
/// </summary>
inline bool worldToScreen(const vec3_t& in, vec3_t& out)
{
	if (screen_transform(in, out)) {
		int w, h;
		Interfaces::engine->get_screen_size(w, h);

		out.x = (w / 2.0f) + (out.x * w) / 2.0f;
		out.y = (h / 2.0f) - (out.y * h) / 2.0f;

		return true;
	}
	return false;
}

#pragma endregion

/// <summary>
/// Rotates an x,y value about the origin, by phi degrees. Sets the result to the reference 
/// of resultX,Y. Input: phi (radians to rotate counterclockwise), x/y(starting positions),
/// resultX/resultY (ending positions after rotation)
/// </summary>
inline void matrixRotation(double phi, double x, double y, double& resultX, double& resultY)
{
	double tempx, tempy;
	tempx = (x * cos(phi) - y * sin(phi));
	tempy = (x * sin(phi) + y * cos(phi));

	// set the memory address at reference to a value
	resultX = tempx;
	resultY = tempy;
}