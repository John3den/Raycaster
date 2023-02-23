#include "Render.h"
#include "Input.h"
#include "Map.h"
#include "Trig.h"
#include "Vector.h"

#include <Textures/piercer.ppm>
#include <Textures/wall1.ppm>
#include <Textures/floor.ppm>
#include <Textures/door.ppm>

float playerAngle=90;
Vector2 player, playerDirection;
float frame1=0, frame2=0, fps=0;

void DrawPlayer2D()
{
    glColor3f(1, 1, 0);
    glPointSize(8);
    glLineWidth(4);
    glBegin(GL_POINTS);
    glVertex2i(player.x, player.y);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(player.x, player.y);
    glVertex2i(player.x + playerDirection.x * 20, player.y + playerDirection.y * 20);
    glEnd();
}

void Resize(int w, int h)
{
    glutReshapeWindow(960, 640);
}

void Display()
{
    frame2 = glutGet(GLUT_ELAPSED_TIME); 
    fps = (frame2 - frame1); 
    frame1 = glutGet(GLUT_ELAPSED_TIME);

    if (Keys.a == 1)
    { 
        playerAngle += 0.2 * fps; 
        playerAngle = ClampAngle(playerAngle);
        playerDirection.x = cos(DegreeToRadians(playerAngle));
        playerDirection.y = -sin(DegreeToRadians(playerAngle));
    }
    if (Keys.d == 1) 
    { 
        playerAngle -= 0.2 * fps;
        playerAngle = ClampAngle(playerAngle);
        playerDirection.x = cos(DegreeToRadians(playerAngle));
        playerDirection.y = -sin(DegreeToRadians(playerAngle));
    }

    int xo = 0;
    if (playerDirection.x < 0)
    {
        xo = -20;
    }
    else 
    { 
        xo = 20;
    }
    int yo = 0; 
    if (playerDirection.y < 0)
    { 
        yo = -20;
    }
    else 
    { 
        yo = 20;
    }
    int ipx = player.x / 64.0, ipx_add_xo = (player.x + xo) / 64.0, ipx_sub_xo = (player.x - xo) / 64.0;
    int ipy = player.y / 64.0, ipy_add_yo = (player.y + yo) / 64.0, ipy_sub_yo = (player.y - yo) / 64.0;
    if (Keys.w == 1)
    {
        if (map[ipy * MAPSIZEX + ipx_add_xo] == 0) { player.x += playerDirection.x * 0.2 * fps; }
        if (map[ipy_add_yo * MAPSIZEX + ipx] == 0) { player.y += playerDirection.y * 0.2 * fps; }
    }
    if (Keys.s == 1)
    {
        if (map[ipy * MAPSIZEX + ipx_sub_xo] == 0) { player.x -= playerDirection.x * 0.2 * fps; }
        if (map[ipy_sub_yo * MAPSIZEX + ipx] == 0) { player.y -= playerDirection.y * 0.2 * fps; }
    }

    glutPostRedisplay();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawMap2D();
    DrawPlayer2D();
    DrawRays2D();

    int x, y;
    for (int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 32; x++)
        {
            int pixel = (y * 32 + x) * 3;
            int red = Piercer[pixel + 0];
            int green = Piercer[pixel + 1];
            int blue = Piercer[pixel + 2];
            if (!IsChroma(red, green, blue))
            {
                glPointSize(8); 
                glColor3ub(red, green, blue); 
                glBegin(GL_POINTS); 
                glVertex2i(x * 8 + 720, y * 8 + 400); 
                glEnd();
            }

        }
    }

    glutSwapBuffers();
}

void DrawRays2D()
{
    int mx, my, mp, dof, side; 
    Ray ray;
    Ray backup;
    float  xo, yo, disV, disH;

    ray.angle = ClampAngle(playerAngle + 30);

    for (int i = 0; i < 120; i++)
    {
        int vmt = 0, hmt = 0;
        dof = 0; side = 0; disV = 100000;
        float Tan = tan(DegreeToRadians(ray.angle));
        if (cos(DegreeToRadians(ray.angle)) > 0.001)
        {
            ray.x = (((int)player.x >> 6) << 6) + 64;
            ray.y = (player.x - ray.x) * Tan + player.y; xo = 64;
            yo = -xo * Tan;
        }
        else if (cos(DegreeToRadians(ray.angle)) < -0.001) {
            ray.x = (((int)player.x >> 6) << 6) - 0.0001;
            ray.y = (player.x - ray.x) * Tan + player.y; xo = -64;
            yo = -xo * Tan;
        }
        else 
        { 
            ray.x = player.x;
            ray.y = player.y;
            dof = 8; 
        }

        while (dof < 8)
        {
            mx = (int)(ray.x) >> 6;
            my = (int)(ray.y) >> 6;
            mp = my * MAPSIZEX + mx;
            if (mp > 0 && mp < MAPSIZEX * MAPSIZEY && map[mp]>0)
            {
                vmt = map[mp] - 1;
                dof = 8; 
                disV = cos(DegreeToRadians(ray.angle)) * (ray.x - player.x) - sin(DegreeToRadians(ray.angle)) * (ray.y - player.y);
            }         
            else 
            { 
                ray.x += xo;
                ray.y += yo;
                dof += 1;
            }
        }
        backup.x = ray.x;
        backup.y = ray.y;

        dof = 0; disH = 100000;
        Tan = 1.0 / Tan;
        if (sin(DegreeToRadians(ray.angle)) > 0.001)
        { 
            ray.y = (((int)player.y >> 6) << 6) - 0.0001;
            ray.x = (player.y - ray.y) * Tan + player.x;
            yo = -64; 
            xo = -yo * Tan; }
        else if (sin(DegreeToRadians(ray.angle)) < -0.001)
        { 
            ray.y = (((int)player.y >> 6) << 6) + 64;
            ray.x = (player.y - ray.y) * Tan + player.x;
            yo = 64;
            xo = -yo * Tan; }
        else { ray.x = player.x; ray.y = player.y; dof = 8; }

        while (dof < 8)
        {
            mx = (int)(ray.x) >> 6;
            my = (int)(ray.y) >> 6;
            mp = my * MAPSIZEX + mx;
            if (mp > 0 && mp < MAPSIZEX * MAPSIZEY && map[mp]>0)
            {
                hmt = map[mp] - 1; 
                dof = 8;
                disH = cos(DegreeToRadians(ray.angle)) * (ray.x - player.x) - sin(DegreeToRadians(ray.angle)) * (ray.y - player.y);
            }  
            else 
            { 
                ray.x += xo;
                ray.y += yo;
                dof += 1; 
            }
        }

        float shade = 1;
        glColor3f(0, 0.8, 0);
        if (disV < disH) 
        {
            hmt = vmt;
            shade = 0.5;
            ray.x = backup.x;
            ray.y = backup.y;
            disH = disV;
            glColor3f(0, 0.6, 0); 
        }

        int ca = ClampAngle(playerAngle - ray.angle);
        disH = disH * cos(DegreeToRadians(ca));
        int lineH = (MAPSIZE * 640) / (disH);
        float ty_step = 32.0 / (float)lineH;
        float ty_off = 0;
        if (lineH > 640)
        {
            ty_off = (lineH - 640) / 2.0; 
            lineH = 640; 
        }
        int lineOff = 320 - (lineH >> 1);

        int y;
        float ty = ty_off * ty_step;
        float tx;
        if (shade == 1)
        { 
            tx = (int)(ray.x / 2.0) % 32;
            if (ray.angle > 180) 
            { 
                tx = 31 - tx; 
            }
        }
        else 
        { 
            tx = (int)(ray.y / 2.0) % 32;
            if (ray.angle > 90 && ray.angle < 270)
            {
                tx = 31 - tx;
            } 
        }
        for (y = 0; y < lineH; y++)
        {
            int* tex = wall1;
            if (hmt != 0) tex = door;
            int pixel = ((int)ty * 32 + (int)tx) * 3;
            int red = tex[pixel + 0] * shade;
            int green = tex[pixel + 1] * shade;
            int blue = tex[pixel + 2] * shade;
            glPointSize(8);
            glColor3ub(red, green, blue);
            glBegin(GL_POINTS);
            glVertex2i(i * 8, y + lineOff);
            glEnd();
            ty += ty_step;
        }

        for (y = lineOff + lineH; y < 640; y++)
        {
            float dy = y - (640 / 2.0), deg = DegreeToRadians(ray.angle), raFix = cos(DegreeToRadians(ClampAngle(playerAngle - ray.angle)));
            tx = player.x / 2 + cos(deg) * 158 * 2 * 32 / dy / raFix;
            ty = player.y / 2 - sin(deg) * 158 * 2 * 32 / dy / raFix;

            int pixel = (((int)(ty) & 31) * 32 + ((int)(tx) & 31)) * 3;
            pixel = pixel % (32 * 32);
            int red = floor1[pixel + 0];
            int green = floor1[pixel + 1];
            int blue = floor1[pixel + 2];
            glColor3ub(red, green, blue);
            glPointSize(8); 
            glBegin(GL_POINTS);
            glVertex2i(i * 8, y); 
            glEnd();

            pixel = (((int)(ty) & 31) * 32 + ((int)(tx) & 31)) * 3;
            pixel = pixel % (32 * 32);
            red = floor1[pixel + 0];
            green = floor1[pixel + 1];
            blue = floor1[pixel + 2];
            glColor3ub(red, green, blue);
            glPointSize(8);
            glBegin(GL_POINTS);
            glVertex2i(i * 8, 640 - y);
            glEnd();
        }

        ray.angle = ClampAngle(ray.angle - 0.5);
    }
}