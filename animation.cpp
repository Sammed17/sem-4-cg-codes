//#include <GL/glut.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>

#include <math.h>
#include <iostream>

using namespace std;

const float PI = 3.14159265;
float inc = 1.0;       // Increment for angle change
float angle = 135;     // Starting angle for pendulum

void drawCircle(float segments, float radius, float sx, float sy) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * PI * float(i) / float(segments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x + sx, y + sy);
    }
    glEnd();
}

void draw(float x1, float y1, float angle) {
    float segments = 100;
    float radius = 10.0f;

    // Draw clock circle
    glLineWidth(2);
    glColor3f(1, 0, 0);
    drawCircle(segments, radius, x1, y1);

    // Draw minute hand
    glColor3f(1, 1, 0);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x1, y1 + (radius / 3.0f) * 2.0f);
    glEnd();

    // Draw hour hand
    glColor3f(1, 0, 0);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x1 + (radius / 3.0f), y1 + (radius / 3.8f));
    glEnd();

    // Draw pendulum bob
    double radians = angle * PI / 180.0;
    float x2 = x1 + (radius * 3.4f) * cos(radians);
    float y2 = y1 - (radius * 3.4f) * sin(radians); // Negative to swing downward
    float radius2 = radius / 3.0f;
    
    glColor3f(0, 0, 1);
    drawCircle(segments, radius2, x2, y2);

    // Draw pendulum rod
    glColor3f(0.7f, 0.7f, 0.7f);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(x1, y1 - radius); // bottom of clock
    glVertex2f(x2, y2);
    glEnd();
}

void display() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -50.0f); // Move back in Z to see the objects

    draw(0, 0, angle);

    glutSwapBuffers();
}

// Timer function to update the pendulum angle
void timer(int value) {
    angle += inc;

    if (angle > 315) {
        angle = 315;
        inc = -inc;
    }
    if (angle < 225) {
        angle = 225;
        inc = -inc;
    }

    glutPostRedisplay();                 // Request display() update
    glutTimerFunc(40, timer, 0);          // Call timer again after 40 ms
}

void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, (GLfloat)w / (GLfloat)h, 0.5, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pendulum Animation");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);  // Start timer

    glutMainLoop();
    return 0;
}