// #include <GL/glut.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>


#include <iostream>
using namespace std;

#define zero 0.0
#define one 1.0

int a, b, c, d, type;

void dda(int x1, int y1, int x2, int y2, int type) {
    float step, x, y, k, Xin, Yin;
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);

    Xin = dx / step;
    Yin = dy / step;

    x = x1;
    y = y1;

    glPointSize(1.0f);
    if (type == 4)
        glPointSize(10.0f);

    glBegin(GL_POINTS);
    glVertex2i(x1, y1);

    int j = 0;
    for (k = 1; k <= step; k++) {
        x += Xin;
        y += Yin;

        if (type == 1 || type == 4)
            glVertex2i((int)x, (int)y);

        if (type == 2 && j % 4 == 0)
            glVertex2i((int)x, (int)y);

        if (type == 3 && j < 5)
            glVertex2i((int)x, (int)y);

        j = (j + 1) % 10;
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(one, zero, zero);
    dda(-350, 0, 350, 0, 1);
    dda(0, -350, 0, 350, 1);
    glFlush();
}

void init() {
    glClearColor(0.6, 0.6, 0.6, 0.0);
    gluOrtho2D(-350, 350, -350, 350);
}

int cnt = 0;
int oldx, oldy, newx, newy;

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
        int viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        int winWidth = viewport[2];
        int winHeight = viewport[3];

        int xi = x - winWidth / 2;
        int yi = winHeight / 2 - y;

        cnt = (cnt + 1) % 2;

        if (cnt == 1) {
            oldx = xi;
            oldy = yi;
        } else {
            newx = xi;
            newy = yi;
        }

        glPointSize(5.0f);
        glBegin(GL_POINTS);
        glVertex2i(xi, yi);
        glEnd();
        glFlush();

    }
}

void menu(int option) {
    dda(oldx, oldy, newx, newy, option);
    glFlush();
}

int main(int a, char** b) {
    glutInit(&a, b);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutCreateWindow("DDA Line Drawing");
    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutCreateMenu(menu);
    glutAddMenuEntry("Simple", 1);
    glutAddMenuEntry("Dotted", 2);
    glutAddMenuEntry("Dashed", 3);
    glutAddMenuEntry("Solid", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
}

// g++ main.cpp -o firstOpenGlApp -lglut -lGLU -lGL
// /firstOpenGlApp