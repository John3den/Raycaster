#pragma once
#include <math.h>
#define PI 3.1415

float DegreeToRadians(float a);
float ClampAngle(float a);
float Distance(float ax, float  ay, float  bx, float  by, float  ang);
bool IsChroma(int r, int g, int b);