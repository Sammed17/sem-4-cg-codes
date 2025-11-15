// #include <GL/glut.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include <iostream>

#define zero 0.0
#define one 1.0

using namespace std;

int oldx, oldy, newx, newy, cnt = 0;

void BresenhamLine(int x1, int y1, int x2, int y2, int type) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int incx = (x2 >= x1) ? 1 : -1;
    int incy = (y2 >= y1) ? 1 : -1;

    dx = abs(dx);
    dy = abs(dy);

    int x = x1, y = y1, e;

    glColor3f(one, one, one);
    glPointSize(type == 4 ? 10.0f : 1.0f);

    glBegin(GL_POINTS);
    glVertex2i(x, y);

    int j = 0;

    if (dx > dy) {
        e = 2 * dy - dx;
        for (int i = 0; i < dx; i++) {
            x += incx;
            if (e >= 0) {
                y += incy;
                e += 2 * (dy - dx);
            } else {
                e += 2 * dy;
            }

            if (type == 1 || type == 4) glVertex2i(x, y);
            if (type == 2 && j % 2 == 0) glVertex2i(x, y);
            if (type == 3 && j < 5) glVertex2i(x, y);

            j = (j + 1) % 10;
        }
    } else {
        e = 2 * dx - dy;
        for (int i = 0; i < dy; i++) {
            y += incy;
            if (e >= 0) {
                x += incx;
                e += 2 * (dx - dy);
            } else {
                e += 2 * dx;
            }

            if (type == 1 || type == 4) glVertex2i(x, y);
            if (type == 2 && j % 2 == 0) glVertex2i(x, y);
            if (type == 3 && j < 5) glVertex2i(x, y);

            j = (j + 1) % 10;
        }
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(one, zero, zero);

    BresenhamLine(-350, 0, 350, 0, 1);
    BresenhamLine(0, 350, 0, -350, 1);

    glFlush();
}

void init() {
    glClearColor(zero, zero, zero, zero);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-350, 350, -350, 350);
}

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

        glColor3f(one, zero, zero);
        glPointSize(5.0f);

        glBegin(GL_POINTS);
        glVertex2i(xi, yi);
        glEnd();

        glFlush();
    }
}

void menu(int type) {
    BresenhamLine(oldx, oldy, newx, newy, type);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Bresenham Line Drawing");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutCreateMenu(menu);
    glutAddMenuEntry("Simple Line", 1);
    glutAddMenuEntry("Dotted Line", 2);
    glutAddMenuEntry("Dashed Line", 3);
    glutAddMenuEntry("Solid Line", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
