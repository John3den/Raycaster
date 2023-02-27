#include <iostream>
#include <stdlib.h>
#include "glut/glut.h"
#include "Trig.h"
#include "Input.h"
#include "Map.h"
#include "Render.h"

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(960, 640);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("UKD");
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, 960, 640, 0);
    player.x = 150; 
    player.y = 400; 
    playerAngle = 90;
    playerDirection.x = cos(DegreeToRadians(playerAngle)); 
    playerDirection.y = -sin(DegreeToRadians(playerAngle));
    glutDisplayFunc(Display);
    glutReshapeFunc(Resize);
    glutKeyboardFunc(ButtonDown);
    glutKeyboardUpFunc(ButtonUp);
    glutMainLoop();
}
