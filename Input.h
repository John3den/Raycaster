#pragma once
#include "Map.h"
#include "glut/glut.h"

typedef struct
{
    int w, a, d, s;
}ButtonKeys; 
extern ButtonKeys Keys;
void ButtonDown(unsigned char key, int x, int y);
void ButtonUp(unsigned char key, int x, int y);