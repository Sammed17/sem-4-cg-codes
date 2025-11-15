#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <iostream>

using namespace std;

float x_start, y_start, x_end, y_end, n;

void getdata() {
    cout << "Enter start point (x1 y1): ";
    cin >> x_start >> y_start;

    cout << "Enter end point (x2 y2): ";
    cin >> x_end >> y_end;

    cout << "Enter number of iterations: ";
    cin >> n;
}

void koch(float x1, float y1, float x2, float y2, float n) {
    float angle = 60 * 3.14159f / 180.0f;

    float x3 = (2 * x1 + x2) / 3;
    float y3 = (2 * y1 + y2) / 3;

    float x4 = (x1 + 2 * x2) / 3;
    float y4 = (y1 + 2 * y2) / 3;

    float x = x3 + (x4 - x3) * 0.5f + (y4 - y3) * 0.8660f;
    float y = y3 - (x4 - x3) * 0.8660f + (y4 - y3) * 0.5f;

    if (n > 0) {
        koch(x1, y1, x3, y3, n - 1);
        koch(x3, y3, x, y, n - 1);
        koch(x, y, x4, y4, n - 1);
        koch(x4, y4, x2, y2, n - 1);
    } 
    else {
        glBegin(GL_LINE_STRIP);
        glVertex2f(x1, y1);
        glVertex2f(x3, y3);
        glVertex2f(x,  y);
        glVertex2f(x4, y4);
        glVertex2f(x2, y2);
        glEnd();
    }
}

void init() {
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    gluOrtho2D(0, 640, 480, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    koch(x_start, y_start, x_end, y_end, n);
    glFlush();
}

int main(int argc, char **argv) {
    getdata();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Koch Curve");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
