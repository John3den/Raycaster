#include "Map.h"

int map[] ={1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,1,
1,0,1,0,0,1,0,1,
1,0,0,0,0,0,0,1,
1,0,0,4,1,1,0,1,
1,0,0,0,0,1,0,1,
1,0,0,0,0,1,0,1,
1,1,1,1,1,1,1,1,};

void DrawMap2D()
{
    int xRelative, yRelative, xAbsolute, yAbsolute;
    for (yRelative = 0; yRelative < MAPSIZEY; yRelative++)
    {
        for (xRelative = 0; xRelative < MAPSIZEX; xRelative++)
        {
            if (map[yRelative * MAPSIZEX + xRelative] > 0) { glColor3f(1, 1, 1); }
            else { glColor3f(0, 0, 0); }
            xAbsolute = xRelative * MAPSIZE; yAbsolute = yRelative * MAPSIZE;
            glBegin(GL_QUADS);
            glVertex2i(0 + xAbsolute + 1, 0 + yAbsolute + 1);
            glVertex2i(0 + xAbsolute + 1, MAPSIZE + yAbsolute - 1);
            glVertex2i(MAPSIZE + xAbsolute - 1, MAPSIZE + yAbsolute - 1);
            glVertex2i(MAPSIZE + xAbsolute - 1, 0 + yAbsolute + 1);
            glEnd();
        }
    }
}