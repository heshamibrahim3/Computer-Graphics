#include<Windows.h>
#include<GL/GLU.h>
#include<GL/glut.h>
#include<cmath>
#include <vector>
#include <iostream>
#include <cstdlib>

using std::vector;

const int window_size = 600;

const double point_size = 10.0;
const double curve_width = 5.0;
const double polygon_width = 2.0;
const int num_curve_segments = 100;

vector<vector<GLdouble> > points;
bool point_move;
int selected_points;

vector<GLdouble> new_point;   // Start coords of new point
int newmx, newmy;
bool draw_polygon;
bool draw_point;


void draw_bezier_curve(const vector<vector<GLdouble>>& v, int segs) {

    if (v.size() == 0 || v.size() > 8)
        return;

    vector<GLdouble> a(3 * v.size(), 0.0);
    for (int i = 0; i < v.size(); ++i)
    {
        a[3 * i + 0] = v[i][0];
        a[3 * i + 1] = v[i][1];
    }

    glMap1d(GL_MAP1_VERTEX_3, 0.0, 1.0, 3.0, v.size(), &a[0]);
    glEnable(GL_MAP1_VERTEX_3);

    glMapGrid1d(segs, 0.0, 1.0);
    glEvalMesh1(GL_LINE, 0, segs); //does the drawing
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (draw_point)
    {
        glPointSize(point_size);
        glBegin(GL_POINTS);
        for (int i = 0; i < points.size(); ++i) {
            glColor3d(1.0, 0.0, 0.0);
            glVertex2dv(&points[i][0]);
        }
        glEnd();
    }

    if (points.size() >= 2 && draw_polygon)
    {
        glLineWidth(polygon_width);
        glColor3d(0.0, 0.0, 1.0);
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < points.size(); ++i)
            glVertex2dv(&points[i][0]);
        glEnd();
    }

    // draws the curve
    glColor3d(0.0, 1.0, 0.0);
    glPointSize(curve_width);
    glLineWidth(curve_width);
    draw_bezier_curve(points, num_curve_segments);
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    gluOrtho2D(0., (double)w,
        (double)window_size - h, (double)window_size);
}


void mouse_click(int button, int state, int x, int y)
{
    if (button != GLUT_LEFT_BUTTON)
        return;

    if (state == GLUT_UP)
    {
        point_move = false;
        return;
    }

    int mousex = x;
    int mousey = window_size - y;

    // check if a point is clicked
    int i;
    for (i = 0; i < points.size(); ++i)
    {
        int slop = (point_size / 2) + 2;
        if (mousex >= points[i][0] - slop
            && mousex <= points[i][0] + slop
            && mousey >= points[i][1] - slop
            && mousey <= points[i][1] + slop)
            break;
    }

    // if a point is not clicked create one
    if (i == points.size())
    {
        points.push_back(vector<GLdouble>(2));
        points[i][0] = mousex;
        points[i][1] = mousey;
    }

    selected_points = i;
    newmx = mousex; newmy = mousey;
    new_point = points[i];
    point_move = true;

    glutPostRedisplay();
}


void movement(int x, int y)
{
    if (!point_move) return;

    int mousex = x;
    int mousey = window_size - y;

    points[selected_points][0] = new_point[0] + mousex - newmx;
    points[selected_points][1] = new_point[1] + mousey - newmy;

    glutPostRedisplay();
}

vector<vector<GLdouble>> p;

void init() {
    point_move = false;
    selected_points = -1;
    draw_polygon = true;
    draw_point = true;
    glClearColor(0.0, 0.0, 0.0, 0.0);  //background color
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(window_size, window_size);
    glutInitWindowPosition(500, 100);
    glutCreateWindow("Bezier Curve");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse_click);
    glutMotionFunc(movement);
    glutMainLoop();

    return 0;
} 