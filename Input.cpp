#pragma once
#include "Input.h"
#include "Render.h"

ButtonKeys Keys;

void ButtonUp(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        Keys.a = 0;
        break;
    case 'w':
        Keys.w = 0;
        break;
    case 's':
        Keys.s = 0;
        break;
    case 'd':
        Keys.d = 0;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void ButtonDown(unsigned char key, int x, int y)
{
    int ipx;
    int ipy;
    int ipx_add_xo;
    int ipy_add_yo;
    int xo = 0;
    int yo = 0;
    switch (key)
    {
    case 'a':
        Keys.a = 1;
        break;
    case 'w':
        Keys.w = 1;
        break;
    case 's':
        Keys.s = 1;
        break;
    case 'd':
        Keys.d = 1;
        break;
    case 'e':
        if (playerDirection.x < 0)
        {
            xo = -25;
        }
        else
        {
            xo = 25;
        }
        if (playerDirection.y < 0)
        {
            yo = -25;
        }
        else
        {
            yo = 25;
        }
        ipx = player.x / 64.0;
        ipx_add_xo = (player.x + xo) / 64.0;
        ipy = player.y / 64.0;
        ipy_add_yo = (player.y + yo) / 64.0;
        if (map[ipy_add_yo * MAPSIZEX + ipx_add_xo] == 4) 
        {
            map[ipy_add_yo * MAPSIZEX + ipx_add_xo] = 0;
        }
    default:
        break;
    }
    glutPostRedisplay();
}