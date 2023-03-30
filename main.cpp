#include <GL/glut.h>
#include <cmath>

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

// Rotation angles of the cylinder
float rotationX = 0.0f;
float rotationY = 0.0f;
float rotationZ = 0.0f;

// Number of sides of the cylinder
const int SIDES = 32;

// Radius and height of the cylinder
const float RADIUS = 0.5f;
const float HEIGHT = 1.0f;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
}

void drawCylinder() {
    // Draw the top of the cylinder
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(1.0,  HEIGHT, 0.0);
    for (int i = 0; i <= SIDES; i++) {
        float theta = 2.0 * M_PI * (float)i / (float)SIDES;
        glVertex3f(1+RADIUS * sin(theta), HEIGHT, RADIUS * cos(theta));
    }
    glEnd();

    // Draw the bottom of the cylinder
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 0.0, 0.0);
    for (int i = SIDES; i >= 0; i--) {
        float theta = 2.0 * M_PI * (float)i / (float)SIDES;
        glVertex3f(1+ RADIUS * sin(theta), 0.0,  RADIUS * cos(theta));
    }
    glEnd();

    // Draw the sides of the cylinder
    glBegin(GL_QUAD_STRIP);
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i <= SIDES; i++) {
        float theta = 2.0 * M_PI * (float)i / (float)SIDES;
        glVertex3f(1+RADIUS * sin(theta), 0, RADIUS * cos(theta));
        glVertex3f(1+RADIUS * sin(theta), HEIGHT, RADIUS * cos(theta));
    }
    glEnd();
}
GLfloat vertices[5][3]={
    {0 ,0 , -2} , { -1 , 2, -1} ,{-2,0,0 } , { - 2, 0 ,-2} ,
  {0,0,0},
};

GLfloat colors[8][3]={
    {0.3, 0.3, 0.7},{1.0, 0.0, 0.0},
    {1.0, 1.0, 0.0},{0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},{1.0, 0.0, 1.0},
    {1.0, 1.0, 1.0},{0.0, 1.0, 1.0}
};



void quad(int a, int b, int c, int d)
{
    glBegin(GL_QUADS);
        glVertex3fv(vertices[a]);
        glVertex3fv(vertices[b]);
        glVertex3fv(vertices[c]);
        glVertex3fv(vertices[d]);
    glEnd();
}

void triangular(int a , int b , int c)
{

    glBegin(GL_TRIANGLES);
        glVertex3fv(vertices[a]);
        glVertex3fv(vertices[b]);
        glVertex3fv(vertices[c]);
    glEnd();

}

void mydraw()
{

    glColor3f(1.0, 0.0, 0.0);
    glColor3fv(colors[0]);     quad(2,3,0,4);
   glColor3fv(colors[1]);     triangular(2,3,1);
    glColor3fv(colors[2]);     triangular(3,0,1);
    glColor3fv(colors[3]);     triangular(0,4,1);
    glColor3fv(colors[4]);     triangular(4,2,1);

}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotationZ , 0 , 0, 1);
    drawCylinder();
    mydraw();
    glutSwapBuffers();
}



void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
        case 'Q':
        case 27:  // Escape key
            exit(0);
            break;
    }
}

static void arrowKey(int key, int x, int y)
{
//    cout << key << "pressed\n";
    switch(key)
    {
        case GLUT_KEY_LEFT:
//            cout << "GLUT_KEY_LEFT" << "Pressed ";
            rotationX -= 5.0f;
            break;

        case GLUT_KEY_RIGHT:
//            cout << "GLUT_KEY_RIGHT" << "Pressed ";
            rotationX += 5.0f;
            break;

        case GLUT_KEY_UP:
 //           cout << "GLUT_KEY_UP" << "Pressed ";
            rotationZ += 5.0f;
            break;

       case GLUT_KEY_DOWN:
 //           cout << "GLUT_KEY_DOWN" << "Pressed ";
            rotationZ -= 5.0f;
            break;

    }

}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        rotationX += 5.0f;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        rotationY += 5.0f;
    }
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Cylinder");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrowKey);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
