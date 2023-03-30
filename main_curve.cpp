/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>


#include<iostream>
#include<vector>


using namespace std;
void init(){
     glClearColor(1,1,1,0);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(-320,320,-320,320);


}

class Point{

public :

    int x,y;
    Point(int x,int y){

    this->x = x;
    this->y = y;
    }

};

void drawCurve(vector<Point> controlPoints)
{
    vector<Point> curve;

    for(float t = 0.1 ; t < 1 ; t += 0.1 )
    {
        float x = (1-t)*(1-t)*(1-t)*controlPoints[0].x + 3*t*(1-t)*(1-t)*controlPoints[1].x + 3*t*t*(1-t)*controlPoints[2].x + t*t*t*controlPoints[3].x;
        float y = (1-t)*(1-t)*(1-t)*controlPoints[0].y + 3*t*(1-t)*(1-t)*controlPoints[1].y + 3*t*t*(1-t)*controlPoints[2].y + t*t*t*controlPoints[3].y;

        curve.push_back(Point((int)x,(int)y));
    }

    glBegin(GL_LINE_STRIP);
    for(int i = 0 ;i< curve.size() ; i++)
        glVertex2d(curve[i].x,curve[i].y);
    glEnd();
    glFlush();


}
vector<Point> controlPoints;

void mouseHandler(int button, int state, int mouse_x, int mouse_y)
{
    static int count = 0;

    glColor3d(1,0,0);

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {


        int x = mouse_x - 320;
        int y = 640 - mouse_y - 320;

        if(count%4 <= 2 )
        {

            controlPoints.push_back(Point(x,y));
            glBegin(GL_POINTS);
            glVertex2d(x,y);
            glEnd();
            glFlush();
            count ++;

        }

        else if(count%4 == 3)
        {
            controlPoints.push_back(Point(x,y));
            glBegin(GL_POINTS);
            glVertex2d(x,y);
            glEnd();
            glFlush();
            count++;

            drawCurve(controlPoints);
            controlPoints.clear();

        }

        glFlush();

    }

    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
    {


    }


}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
      glClearColor(0,0,0,1);

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,640);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("curve");


    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseHandler);


    glClearColor(1,1,1,1);

    glutMainLoop();

    return EXIT_SUCCESS;
}
