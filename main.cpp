#include <windows.h>  // for MS Windows
#include <GL/glut.h> // GLUT, include glu.h and gl.h
#include <math.h>
#include <iostream>
#include <cstring>
#include <stdlib.h> //random-num

using namespace std;
char text1[] = "PINAK-6";
char text2[] = "VUTU";
char text3[] = "X";

void text(float x, float y, char* st)
{
    int l, i;

    l = strlen(st); // see how many characters are in text string.
    //glColor3f(0.0,1.0,0.7);
    //glDisable(GL_LIGHTING);
    glRasterPos2f(x, y);    // location to start printing text
    for (i = 0; i < l; i++) // loop until i is greater then l
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);
    }
}

void SpecialInput(int key, int x, int y);
int _angle1 = 0;
int _carMove = 0;
int _carangle = 0;
float _angle2 = 1;
int _boatMove = 0;
int _boatUpDown = -5;
int _planeMove = 0;
int _planeMove2 = 0;
bool isDay = true;
bool fullscreen = true;
int ghostmoveX = 0;
int ghostmoveY = 0;
bool isCarMoving = true;





void ghostUpdate(int value)   //I013
{
    ghostmoveX = (rand() / 4) % 500 - 200;
    ghostmoveY = (-rand() / 2) % 500 + 300;
    glutPostRedisplay(); //Notify GLUT that the display has changed
    glutTimerFunc(600, ghostUpdate, 0); //Notify GLUT to call update again in 25 milliseconds

}
void handleKeypress(unsigned char key, int x, int y)
{

    switch (key)
    {

    case 'd':

        //glClearColor(1.0,1.0,1.0,1.0);
        isDay = true;
        // glutDisplayFunc(output);
        //allupdates();
        // glutTimerFunc(10000, daynightmodechanger, 0);

        glutPostRedisplay();
        // glutDisplayFunc(day);
        //day();
        break;
    case 'n':
        //glClearColor(0.0,0.0,0.0,1.0);
        isDay = false;
        //  glutDisplayFunc(output);
        //allupdates();
        //    glutTimerFunc(10000, daynightmodechanger, 0);

        glutPostRedisplay();
        break;
    case 'f': //toggle screenmode
        fullscreen = !fullscreen;
        if (fullscreen)
        {
            glutFullScreen();
        }
        else
        {
            glutReshapeWindow(600, 600);
            glutPositionWindow(0, 0);
        }
        break;
    case 'x':
        isCarMoving = !isCarMoving;
        glutPostRedisplay();
        break;
    case 27:
        glutDestroyWindow ( 1 );
        exit(0);
        break;
    }
}

float TireRotateAngle = 0.0f;
float TruckTireRotateAngle = 0.0f;
int _TruckMoveReverse = 0;

//float TireRotateAngle = 0.0f;
void TruckTire(int xx, int yy, float r) //C029//H103
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(TireRotateAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.0f, -0.0f, 0.0f);
    glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin
    for (int i = 0; i < 200; i++)
    {
        // glColor3ub(255, 215, 0);
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        // float r = 4.0f;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x + xx, y + yy);
    }
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0); //black-rim
    glVertex2f(-0.075, 0);
    glVertex2f(0.075, 0);

    glVertex2f(-0.05, -0.075);
    glVertex2f(0.05, 0.075);

    glVertex2f(0.05, -0.075);
    glVertex2f(-0.05, 0.075);

    glVertex2f(0, -0.1);
    glVertex2f(0, 0.1);

    glEnd();

    glPopMatrix();
}
void TruckScaledTire()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(140.1, 95, 0);
    glScalef(90, 90, 0);
    glColor3ub(0, 0, 0); //black-tire
    TruckTire(0, 0, 0.2);
    glColor3ub(192, 192, 192); //silver-tire-rim
    TruckTire(0, 0, 0.13);
    glColor3ub(211, 211, 255); //grey-tire-rim
    TruckTire(0, 0, 0.09);
    glPopMatrix();
}

void TruckBody()
{

    glColor3f(0, 0, 0.1373); //blue-body
    //glColor3f(0.2, 0.95, 0.4);
    glBegin(GL_POLYGON);
    glVertex2f(150, 152);
    glVertex2f(190, 152);
    glVertex2f(215, 127);
    glVertex2f(240, 127);
    glVertex2f(240, 92);
    glVertex2f(150, 92);
    glEnd();

    glBegin(GL_POLYGON); //trolly
    glVertex2f(150, 129);
    glVertex2f(60, 129);
    glVertex2f(60, 92);
    glVertex2f(150, 92);
    glEnd();
    glBegin(GL_POLYGON);      //trolly-cargo
    glColor3ub(169, 120, 53); //brown
    glVertex2f(70, 129);
    glVertex2f(100, 129);
    glVertex2f(100, 152);
    glVertex2f(70, 152);
    glEnd();

    glColor3ub(9, 12, 53); //black
    text(90.0, 130.0, text3);
    glBegin(GL_POLYGON); //back-light
    glColor3ub(255, 0, 0);
    glVertex2f(110 - 50, 92);
    glVertex2f(115 - 50, 92);
    glVertex2f(115 - 50, 117);
    glVertex2f(110 - 50, 117);
    glEnd();

    glBegin(GL_POLYGON); //window
    glColor3ub(0, 0, 0); //black-window-in=day
    if (!isDay)
        glColor3ub(163, 228, 215); //gray-window-in-night
    glVertex2f(150, 152);
    glVertex2f(190, 152);
    glVertex2f(215, 127);
    glVertex2f(210, 127);
    glVertex2f(150, 127);
    glVertex2f(130, 127);
    glEnd();

    glBegin(GL_POLYGON); //window-Divider
    glColor3ub(192, 192, 192);
    glVertex2f(170, 152);
    glVertex2f(165, 152);
    glVertex2f(165, 127);
    glVertex2f(170, 127);
    glEnd();

    glBegin(GL_POLYGON); //roof-plate
    glColor3ub(168, 169, 173);

    glVertex2f(150, 152);
    glVertex2f(190, 152);
    glVertex2f(185, 157);
    glVertex2f(150, 157);
    glEnd();

    glBegin(GL_POLYGON); //window-holder-front
    glColor3ub(168, 169, 173);
    glVertex2f(190, 152);
    glVertex2f(215, 127);
    glVertex2f(210, 127);
    glVertex2f(185, 152);
    glEnd();

    glBegin(GL_POLYGON); //window-holder-back
    glColor3ub(168, 169, 173);
    glVertex2f(140 + 20 - 10, 157);
    glVertex2f(115 + 20, 127);
    glVertex2f(125 + 20, 127);
    glVertex2f(140 + 20 - 10, 152);
    glEnd();

    glBegin(GL_POLYGON); //foot-holder
    glColor3ub(168, 169, 173);
    glVertex2f(242, 92);
    glVertex2f(60, 92);
    glVertex2f(60, 97);
    glVertex2f(242, 97);

    glEnd();

    glBegin(GL_POLYGON); //mirror
    glColor3f(0, 0, 0.1373);
    //glColor3ub(255,250,0);
    glVertex2f(211.5, 134.5);
    glVertex2f(204.5, 135.5);
    glVertex2f(203.5, 129);
    glVertex2f(210.5, 127);
    glEnd();

    glBegin(GL_POLYGON);      //Yellow-headlight
    glColor3f(1.0, 1.0, 0.0); //body
    //glColor3ub(255,250,0);
    glVertex2f(210.5 + 28, 134.5 - 10);
    glVertex2f(203.5 + 28, 135.5 - 10);
    glVertex2f(203.5 + 28, 129 - 10);
    glVertex2f(210.5 + 28, 127 - 10);
    glEnd();
    if (!isDay)
    {
        glBegin(GL_POLYGON);      //Yellow-headlight
        glColor3f(1.0, 1.0, 1.0); //body
        glVertex2f(210.5 + 28 + 90, 134.5 - 10 - 0);
        glVertex2f(205.5 + 28, 134.5 - 10);
        glColor3f(0.8, 0.9, 0.0);
        glVertex2f(205.5 + 28, 127 - 10);
        glVertex2f(210.5 + 28 + 90, 127 - 10 - 30);
        glEnd();
    }

    glBegin(GL_POLYGON); //window-opener-1
    glColor3ub(192, 192, 192);
    glVertex2f(150 - 15 - 5 + 20, 127 - 5 - 3);
    glVertex2f(155 - 5 - 5 + 20, 127 - 5 - 3);
    glVertex2f(155 - 5 - 5 + 20, 129 - 5);
    glVertex2f(150 - 15 - 5 + 20, 129 - 5);
    glEnd();
    glBegin(GL_POLYGON); //window-opener-2
    glColor3ub(192, 192, 192);
    glVertex2f(150 - 15 + 40, 127 - 5 - 3);
    glVertex2f(155 - 5 + 40, 127 - 5 - 3);
    glVertex2f(155 - 5 + 40, 129 - 5);
    glVertex2f(150 - 15 + 40, 129 - 5);
    glEnd();
}
void TruckThrust()
{
    if (isDay)
    {
        glBegin(GL_POLYGON);
        glColor3ub(168, 169, 173);
        glVertex2f(110 - 50, 92);
        glColor3ub(255, 255, 255);
        glVertex2f(00 - 50, 80);
        glVertex2f(00 - 50, 110);
        glColor3ub(0, 0, 0);
        glVertex2f(110 - 50, 97);
        glEnd();
    }
}
void fullTruck()
{
    //TruckThrust();
    TruckBody();
    // ScaledTire();
    glPushMatrix();
    glTranslatef(65, 0, 0);
    TruckScaledTire();
    glTranslatef(-85, 0, 0);
    TruckScaledTire();
    glPopMatrix();
}
void TruckReverse()
{
    glLineWidth(1);
    //glMatrixMode(GL_MODELVIEW);

    //init();
    //glPushMatrix();

    glTranslatef(-100.5, 0, 0);
    //glTranslatef(_TruckMoveReverse % 500, 0, 0);
    fullTruck();

    // glPopMatrix();

    //glutSwapBuffers();
}
void ScaledTruckReverse()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(500, 140, 0);
    glScalef(-0.5, 0.5, 0);
    TruckReverse();
    glPopMatrix();
}
void MovingScaledTruckReverse()
{
    glMatrixMode(GL_MODELVIEW);

    //init();
    glPushMatrix();
    glTranslatef(500, -80, 0);
    glTranslatef(_TruckMoveReverse % 2000, 0, 0);

    ScaledTruckReverse();
    glPopMatrix();
    //glutSwapBuffers();
}
void TruckTireRotate(int value)   //I010, I022
{
    if (isCarMoving) { TruckTireRotateAngle -= 5.0f; }
    glutPostRedisplay(); //Notify GLUT that the display has changed

    glutTimerFunc(05, TruckTireRotate, 0); //Notify GLUT to call update again in 25 milliseconds
}
void updatePlane2(int value)//I002
{
    _planeMove2 += 10;

    glutPostRedisplay(); //Notify GLUT that the display has changed
    glutTimerFunc(20, updatePlane2, 0);
}
void MoveTruckReverse(int value)   //I010 , I022
{
    if (isCarMoving) {
        _TruckMoveReverse -= 1;
    }


    glutPostRedisplay();
    glutTimerFunc(20, MoveTruckReverse, 0);
}

void CarTire(int xx, int yy, float r) //C028//V048//L066//H102
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(TireRotateAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.0f, -0.0f, 0.0f);
    glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin
    for (int i = 0; i < 200; i++)
    {
        // glColor3ub(255, 215, 0);
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        // float r = 4.0f;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x + xx, y + yy);
    }
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0); //black-rim
    glVertex2f(-0.075, 0);
    glVertex2f(0.075, 0);

    glVertex2f(-0.05, -0.075);
    glVertex2f(0.05, 0.075);

    glVertex2f(0.05, -0.075);
    glVertex2f(-0.05, 0.075);

    glVertex2f(0, -0.1);
    glVertex2f(0, 0.1);

    glEnd();

    glPopMatrix();
}
void ScaledTire()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(140.1, 95, 0);
    glScalef(80, 80, 0);
    glColor3ub(0, 0, 0); //black-tire
    CarTire(0, 0, 0.2);
    glColor3ub(192, 192, 192); //silver-tire-rim
    CarTire(0, 0, 0.13);
    glColor3ub(211, 211, 255); //grey-tire-rim
    CarTire(0, 0, 0.09);
    glPopMatrix();
}

void CarBody()
{

    glColor3f(0.1373, 0.5725, 0.5529); //body
    //glColor3f(0.2, 0.95, 0.4);
    glBegin(GL_POLYGON);
    glVertex2f(140, 152);
    glVertex2f(190, 152);
    glVertex2f(215, 127);
    glVertex2f(240, 127);
    glVertex2f(240, 92);
    glVertex2f(110, 92);
    glVertex2f(110, 127);
    glVertex2f(130, 127);
    glVertex2f(140, 152);
    glEnd();

    glBegin(GL_POLYGON); //back-light
    glColor3ub(255, 0, 0);
    glVertex2f(110, 92);
    glVertex2f(115, 92);
    glVertex2f(115, 117);
    glVertex2f(110, 117);
    glEnd();

    glBegin(GL_POLYGON); //window
    glColor3ub(0, 0, 0); //black-window-in=day
    if (!isDay)
        glColor3ub(163, 228, 215); //gray-window-in-night

    glVertex2f(140, 152);
    glVertex2f(190, 152);
    glVertex2f(215, 127);
    glVertex2f(210, 127);
    glVertex2f(120, 127);
    glVertex2f(130, 127);
    glEnd();

    glBegin(GL_POLYGON); //window-Divider
    glColor3ub(192, 192, 192);
    glVertex2f(170, 152);
    glVertex2f(165, 152);
    glVertex2f(165, 127);
    glVertex2f(170, 127);
    glEnd();

    glBegin(GL_POLYGON); //roof-plate
    glColor3ub(168, 169, 173);

    glVertex2f(140, 152);
    glVertex2f(190, 152);
    glVertex2f(185, 157);
    glVertex2f(140, 157);
    glEnd();

    glBegin(GL_POLYGON); //window-holder-front
    glColor3ub(168, 169, 173);
    glVertex2f(190, 152);
    glVertex2f(215, 127);
    glVertex2f(210, 127);
    glVertex2f(185, 152);
    glEnd();

    glBegin(GL_POLYGON); //window-holder-back
    glColor3ub(168, 169, 173);
    glVertex2f(140, 157);
    glVertex2f(115, 127);
    glVertex2f(125, 127);
    glVertex2f(140, 152);
    glEnd();

    glBegin(GL_POLYGON); //foot-holder
    glColor3ub(168, 169, 173);
    glVertex2f(242, 92);
    glVertex2f(110, 92);
    glVertex2f(110, 97);
    glVertex2f(242, 97);

    glEnd();

    glBegin(GL_POLYGON);      //mirror
    glColor3f(0.3, 0.9, 0.6); //body
    //glColor3ub(255,250,0);
    glVertex2f(211.5, 134.5);
    glVertex2f(204.5, 135.5);
    glVertex2f(203.5, 129);
    glVertex2f(210.5, 127);
    glEnd();

    glBegin(GL_POLYGON);      //Yellow-headlight
    glColor3f(1.0, 1.0, 0.0); //body
    //glColor3ub(255,250,0);
    glVertex2f(210.5 + 28, 134.5 - 10);
    glVertex2f(203.5 + 28, 135.5 - 10);
    glVertex2f(203.5 + 28, 129 - 10);
    glVertex2f(210.5 + 28, 127 - 10);
    glEnd();
    if (!isDay)
    {
        glBegin(GL_POLYGON);      //Yellow-headlight
        glColor3f(1.0, 1.0, 1.0); //body
        glVertex2f(210.5 + 28 + 90, 134.5 - 10 - 0);
        glVertex2f(205.5 + 28, 134.5 - 10);
        glColor3f(0.8, 0.9, 0.0);
        glVertex2f(205.5 + 28, 127 - 10);
        glVertex2f(210.5 + 28 + 90, 127 - 10 - 30);
        glEnd();
    }

    glBegin(GL_POLYGON); //window-opener-1
    glColor3ub(192, 192, 192);
    glVertex2f(150 - 15 - 5, 127 - 5 - 3);
    glVertex2f(155 - 5 - 5, 127 - 5 - 3);
    glVertex2f(155 - 5 - 5, 129 - 5);
    glVertex2f(150 - 15 - 5, 129 - 5);
    glEnd();
    glBegin(GL_POLYGON); //window-opener-2
    glColor3ub(192, 192, 192);
    glVertex2f(150 - 15 + 40, 127 - 5 - 3);
    glVertex2f(155 - 5 + 40, 127 - 5 - 3);
    glVertex2f(155 - 5 + 40, 129 - 5);
    glVertex2f(150 - 15 + 40, 129 - 5);
    glEnd();
}
void CarThrust()
{
    glBegin(GL_POLYGON);
    glColor3ub(168, 169, 173);
    glVertex2f(110, 92);
    glColor3ub(255, 255, 255);
    glVertex2f(00, 80);
    glVertex2f(00, 110);
    glColor3ub(0, 0, 0);
    glVertex2f(110, 97);
    glEnd();
}
void fullCar()
{

    CarBody();
    ScaledTire();
    glPushMatrix();
    glTranslatef(65, 0, 0);
    ScaledTire();
    glPopMatrix();
}
void CarForward()
{
    glLineWidth(1);

    glTranslatef(-450.5, 0, 0);
    fullCar();
}
void ScaledCarForward()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(10, 40, 0);
    glScalef(0.5, 0.5, 0);
    CarForward();
    glPopMatrix();
}
void ScaledCarReverse()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(10, 40, 0);
    glScalef(-0.5, 0.5, 0);
    CarForward();
    glPopMatrix();
}
void MovingScaledCarForward()
{
    glMatrixMode(GL_MODELVIEW);

    //init();
    glPushMatrix();
    // glTranslatef(-100.5, 0, 0);
    glTranslatef((_carMove / 2) % 850, 0, 0);

    ScaledCarForward();
    glPopMatrix();
    //glutSwapBuffers();
}
void MovingScaledCarReverse()
{
    glMatrixMode(GL_MODELVIEW);

    //init();
    glPushMatrix();
    glTranslatef(600.5, 0, 0);
    glTranslatef((-_carMove / 2) % 1000, 0, 0);

    ScaledCarReverse();
    glPopMatrix();
    //glutSwapBuffers();
}
void TireRotate(int value)      //I009,I011
{
    if (isCarMoving) { TireRotateAngle -= 5.0f; }
    glutPostRedisplay(); //Notify GLUT that the display has changed

    glutTimerFunc(05, TireRotate, 0); //Notify GLUT to call update again in 25 milliseconds
}
// void TireRotateReverse(int value)
// {
//     TireRotateAngle= 5.0f;
//     glutPostRedisplay(); //Notify GLUT that the display has changed

//     glutTimerFunc(05, TireRotateReverse, 0); //Notify GLUT to call update again in 25 milliseconds
// }
void MoveCarForward(int value)          //I009,I011
{
    if (isCarMoving) {
        _carMove += 1;
    }

    glutPostRedisplay();
    glutTimerFunc(20, MoveCarForward, 0);
}

// void MoveCarReverse(int value) {
//     _carMove -= 1;

// glutPostRedisplay();
// glutTimerFunc(20, MoveCarReverse, 0);
// }

void update(int value) //I001, I003-I008, I012, I015-018
{

    _angle1 += 1.0f;
    _boatMove += 1;
    glutPostRedisplay(); //Notify GLUT that the display has changed

    glutTimerFunc(20, update, 0); //Notify GLUT to call update again in 25 milliseconds
}

void BoatUpDownUpdate(int value)   //I014
{

    if (_boatUpDown > 5)
    {
        _boatUpDown = -5;
    }
    else
    {
        _boatUpDown += 1;
    }

    glutPostRedisplay(); //Notify GLUT that the display has changed

    glutTimerFunc(180, BoatUpDownUpdate, 0); //Notify GLUT to call update again in 25 milliseconds
}

void update1(int value)
{

    // std::cout << "updated called";

    _angle2 -= 1.0f;
    glutPostRedisplay(); //Notify GLUT that the display has changed

    glutTimerFunc(20, update, 0); //Notify GLUT to call update again in 25 milliseconds
}

class CityScape
{

public:
    CityScape() {}
    void star() //C018
    {
        glLineWidth(2);
        glBegin(GL_LINES);
        glColor3ub(255, 251, 251); //white-star
        glVertex2f(-0.075, 0);
        glVertex2f(0.075, 0);

        glVertex2f(-0.05, -0.075);
        glVertex2f(0.05, 0.075);

        glVertex2f(0.05, -0.075);
        glVertex2f(-0.05, 0.075);

        glVertex2f(0, -0.1);
        glVertex2f(0, 0.1);

        glEnd();
    }
    void scaledstar()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(05, 490, 0);
        glScalef(15, 15, 0);
        star();
        glPopMatrix();
    }
    void scaledstarLoop()
    {
        scaledstar();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(5, 0, 0);

        for (int i = 0; i < 3; i++)
        {
            glTranslatef(0, -20, 0);
            scaledstar();
            for (int i = 0; i < 40; i++)
            {
                if (i % 2 == 0)
                {
                    glTranslatef(15, -35, 0);
                    scaledstar();
                }
                else
                {
                    glTranslatef(18, 35, 0);
                    scaledstar();
                }
            }
            glTranslatef(-660, -35, 0);
        }
        glPopMatrix();
    }
    void sky() //C017
    {
        {

            glBegin(GL_QUADS);
            glColor3ub(7, 11, 52);
            glVertex2f(0, 300);
            glColor3ub(0, 0, 55);
            glVertex2f(500, 300);
            glColor3ub(43, 47, 19);
            glVertex2f(500, 500);
            glColor3ub(20, 24, 82);
            glVertex2f(0, 500);
            glEnd();
            scaledstarLoop();
        }
    }
    void Road() //C019
    {
        int x = 0, y = 0;
        glColor3ub(15, 15, 10); // Clear the color buffer (background)
        glBegin(GL_POLYGON);    // Draw a Red 1x1 Square centered at origin
        glVertex2f(0, 200);
        glVertex2f(500, 200);
        glVertex2f(500, 80);
        glVertex2f(0, 80);

        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(x, 140);
        glVertex2f(y + 45, 140);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(x + 90, 140);
        glVertex2f(y + 135, 140);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(x + 180, 140);
        glVertex2f(y + 225, 140);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(x + 270, 140);
        glVertex2f(y + 315, 140);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(x + 360, 140);
        glVertex2f(y + 405, 140);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(x + 450, 140);
        glVertex2f(y + 495, 140);
        glEnd();
    }
    void yellow(int x, int y) //C020

    {
        glColor3ub(255, 255, 4);
        glBegin(GL_POLYGON);
        glVertex2f(5 + x, 8 + y);
        glVertex2f(0 + x, 8 + y);
        glVertex2f(0 + x, y);
        glVertex2f(5 + x, y);
        glEnd();
    }
    void Roadside() //C020
    {
        glColor3ub(128, 128, 128);
        glBegin(GL_POLYGON);
        glVertex2f(0, 180);
        glVertex2f(0, 172);
        glVertex2f(500, 172);
        glVertex2f(500, 180);
        glEnd();
        for (int i = 0; i < 500; i++)
        {
            if (i % 10 == 0)
            {
                yellow(i, 172);
            }
        }
    }
    void Roadside2() //C020
    {
        Roadside();
        glPushMatrix();
        glTranslatef(0.0f, -124.0f, 0.0f);
        Roadside();
        glPopMatrix();
    }
    void circle(int xx, int yy, float r)
    {

        glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin
        for (int i = 0; i < 200; i++)
        {
            // glColor3ub(255, 215, 0);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            // float r = 4.0f;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x + xx, y + yy);
        }
        glEnd();
    }
    void Background() //C030
    {
        glColor3ub(210, 0, 105);
        glBegin(GL_POLYGON);
        glVertex2f(0, 180);
        glVertex2f(25, 180);
        glVertex2f(25, 380);
        glVertex2f(0, 380);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(25, 180);
        glVertex2f(45, 180);
        glVertex2f(45, 360);
        glVertex2f(25, 360);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(80, 180);
        glVertex2f(45, 180);
        glVertex2f(45, 390);
        glVertex2f(80, 390);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(80, 180);
        glVertex2f(105, 180);
        glVertex2f(105, 345);
        glVertex2f(80, 345);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(105, 180);
        glVertex2f(125, 180);
        glVertex2f(125, 375);
        glVertex2f(105, 375);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(150, 180);
        glVertex2f(125, 180);
        glVertex2f(125, 420);
        glVertex2f(150, 420);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(150, 180);
        glVertex2f(170, 180);
        glVertex2f(170, 350);
        glVertex2f(150, 350);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(170, 180);
        glVertex2f(195, 180);
        glVertex2f(195, 410);
        glVertex2f(170, 410);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(215, 180);
        glVertex2f(195, 180);
        glVertex2f(195, 380);
        glVertex2f(215, 380);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(215, 180);
        glVertex2f(240, 180);
        glVertex2f(240, 415);
        glVertex2f(215, 415);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(240, 180);
        glVertex2f(265, 180);
        glVertex2f(265, 360);
        glVertex2f(240, 360);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(265, 180);
        glVertex2f(295, 180);
        glVertex2f(295, 425);
        glVertex2f(265, 425);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(295, 180);
        glVertex2f(315, 180);
        glVertex2f(315, 390);
        glVertex2f(295, 390);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(315, 180);
        glVertex2f(340, 180);
        glVertex2f(340, 360);
        glVertex2f(315, 360);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(365, 180);
        glVertex2f(340, 180);
        glVertex2f(340, 390);
        glVertex2f(365, 390);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(395, 180);
        glVertex2f(365, 180);
        glVertex2f(365, 425);
        glVertex2f(395, 425);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(395, 180);
        glVertex2f(415, 180);
        glVertex2f(415, 360);
        glVertex2f(395, 360);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(435, 180);
        glVertex2f(415, 180);
        glVertex2f(415, 400);
        glVertex2f(435, 400);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(435, 180);
        glVertex2f(460, 180);
        glVertex2f(460, 340);
        glVertex2f(435, 340);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(460, 180);
        glVertex2f(485, 180);
        glVertex2f(485, 425);
        glVertex2f(460, 425);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(500, 180);
        glVertex2f(485, 180);
        glVertex2f(485, 380);
        glVertex2f(500, 380);
        glEnd();
    }

    void Building()
    {
        //glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);

        glColor3ub(91, 0, 91);
        glBegin(GL_POLYGON); //repetitive
        glVertex2f(250, 350);
        glVertex2f(200, 350);
        glVertex2f(200, 180);
        glVertex2f(250, 180);
        glEnd();
        glBegin(GL_POLYGON); //repetitive
        glVertex2f(200, 300);
        glVertex2f(175, 300);
        glVertex2f(175, 180);
        glVertex2f(200, 180);
        glEnd();
        glBegin(GL_POLYGON); //repetitive
        glVertex2f(150, 280);
        glVertex2f(175, 280);
        glVertex2f(175, 180);
        glVertex2f(150, 180);
        glEnd();
        glBegin(GL_POLYGON); //repetitive
        glVertex2f(150, 320);
        glVertex2f(100, 320);
        glVertex2f(100, 180);
        glVertex2f(150, 180);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(100, 290);
        glVertex2f(50, 290);
        glVertex2f(50, 180);
        glVertex2f(100, 180);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(0, 320);
        glVertex2f(50, 320);
        glVertex2f(50, 180);
        glVertex2f(0, 180);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(275, 300);
        glVertex2f(325, 300);
        glVertex2f(325, 180);
        glVertex2f(275, 180);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(275, 260);
        glVertex2f(250, 260);
        glVertex2f(250, 180);
        glVertex2f(275, 180);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(325, 260);
        glVertex2f(350, 260);
        glVertex2f(350, 180);
        glVertex2f(325, 180);
        glEnd();

        glPushMatrix();
        glTranslatef(150, 0, 0);
        glBegin(GL_POLYGON); //repetitive
        glVertex2f(250, 350);
        glVertex2f(200, 350);
        glVertex2f(200, 180);
        glVertex2f(250, 180);
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(225, 0, 0);
        glBegin(GL_POLYGON); //repetitive
        glVertex2f(200, 300);
        glVertex2f(175, 300);
        glVertex2f(175, 180);
        glVertex2f(200, 180);
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(275, 0, 0);
        glBegin(GL_POLYGON); //repetitive
        glVertex2f(150, 280);
        glVertex2f(175, 280);
        glVertex2f(175, 180);
        glVertex2f(150, 180);
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(350, 0, 0);
        glBegin(GL_POLYGON); //repetitive
        glVertex2f(150, 320);
        glVertex2f(100, 320);
        glVertex2f(100, 180);
        glVertex2f(150, 180);
        glEnd();
        glPopMatrix();

        //Borders
        glLineWidth(1);
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(250, 350);
        glVertex2f(200, 350);
        glVertex2f(200, 350);
        glVertex2f(200, 180);
        glVertex2f(200, 180);
        glVertex2f(250, 180);
        glVertex2f(250, 180);
        glVertex2f(250, 350);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(200, 300);
        glVertex2f(175, 300);
        glVertex2f(175, 300);
        glVertex2f(175, 180);
        glVertex2f(175, 180);
        glVertex2f(200, 180);
        glVertex2f(200, 180);
        glVertex2f(200, 300);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(150, 280);
        glVertex2f(175, 280);
        glVertex2f(175, 280);
        glVertex2f(175, 180);
        glVertex2f(175, 180);
        glVertex2f(150, 180);
        glVertex2f(150, 180);
        glVertex2f(150, 280);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(150, 320);
        glVertex2f(100, 320);
        glVertex2f(100, 320);
        glVertex2f(100, 180);
        glVertex2f(100, 180);
        glVertex2f(150, 180);
        glVertex2f(150, 180);
        glVertex2f(150, 320);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(100, 290);
        glVertex2f(50, 290);
        glVertex2f(50, 290);
        glVertex2f(50, 180);
        glVertex2f(50, 180);
        glVertex2f(100, 180);
        glVertex2f(100, 180);
        glVertex2f(100, 290);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(0, 320);
        glVertex2f(50, 320);
        glVertex2f(50, 320);
        glVertex2f(50, 180);
        glVertex2f(50, 180);
        glVertex2f(0, 180);
        glVertex2f(0, 180);
        glVertex2f(0, 320);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(275, 300);
        glVertex2f(325, 300);
        glVertex2f(325, 300);
        glVertex2f(325, 180);
        glVertex2f(325, 180);
        glVertex2f(275, 180);
        glVertex2f(275, 180);
        glVertex2f(275, 300);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(275, 260);
        glVertex2f(250, 260);
        glVertex2f(250, 260);
        glVertex2f(250, 180);
        glVertex2f(250, 180);
        glVertex2f(275, 180);
        glVertex2f(275, 180);
        glVertex2f(275, 260);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(325, 260);
        glVertex2f(350, 260);
        glVertex2f(350, 260);
        glVertex2f(350, 180);
        glVertex2f(350, 180);
        glVertex2f(325, 180);
        glVertex2f(325, 180);
        glVertex2f(325, 260);
        glEnd();

        glPushMatrix();
        glTranslatef(150, 0, 0);
        glBegin(GL_LINES); //repetitive
        glVertex2f(250, 350);
        glVertex2f(200, 350);
        glVertex2f(200, 350);
        glVertex2f(200, 180);
        glVertex2f(200, 180);
        glVertex2f(250, 180);
        glVertex2f(250, 180);
        glVertex2f(250, 350);
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(225, 0, 0);
        glBegin(GL_LINES); //repetitive
        glVertex2f(200, 300);
        glVertex2f(175, 300);
        glVertex2f(175, 300);
        glVertex2f(175, 180);
        glVertex2f(175, 180);
        glVertex2f(200, 180);
        glVertex2f(200, 180);
        glVertex2f(200, 300);
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(275, 0, 0);
        glBegin(GL_LINES); //repetitive
        glVertex2f(150, 280);
        glVertex2f(175, 280);
        glVertex2f(175, 280);
        glVertex2f(175, 180);
        glVertex2f(175, 180);
        glVertex2f(150, 180);
        glVertex2f(150, 180);
        glVertex2f(150, 280);
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(350, 0, 0);
        glBegin(GL_LINES); //repetitive
        glVertex2f(150, 320);
        glVertex2f(100, 320);
        glVertex2f(100, 320);
        glVertex2f(100, 180);
        glVertex2f(100, 180);
        glVertex2f(150, 180);
        glVertex2f(150, 180);
        glVertex2f(150, 320);
        glEnd();
        glPopMatrix();
    }

    void Detail_1(float x, float y)
    {
        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(45 + x, 5 + y);
        glVertex2f(0 + x, 5 + y);
        glVertex2f(0 + x, y);
        glVertex2f(45 + x, y);
        glEnd();
    }
    void Detail_2(float x, float y)
    {
        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(55 + x, 10 + y);
        glVertex2f(95 + x, 10 + y);
        glVertex2f(95 + x, y);
        glVertex2f(55 + x, y);
        glEnd();
    }
    void Detail_3(float x, float y)
    {
        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(97 + x, 3 + y);
        glVertex2f(100 + x, 3 + y);
        glVertex2f(100 + x, y);
        glVertex2f(97 + x, y);
        glEnd();
    }

    void Detail_4(float x, float y)
    {
        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(7 + x, y + 180);
        glVertex2f(7 + x, y + 315);
        glVertex2f(x, y + 315);
        glVertex2f(x, y + 180);
        glEnd();
    }
    void Detail_5(float x, float y)
    {
        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(170 + x, 5 + y);
        glVertex2f(155 + x, 5 + y);
        glVertex2f(155 + x, y);
        glVertex2f(170 + x, y);
        glEnd();
    }
    void Detail_6(float x, float y)
    {
        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(3 + x, y + 180);
        glVertex2f(3 + x, y + 295);
        glVertex2f(x, y + 295);
        glVertex2f(x, y + 180);
        glEnd();
    }
    void Detail_7(float x, float y)
    {
        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(222 + x, 5 + y);
        glVertex2f(205 + x, 5 + y);
        glVertex2f(205 + x, y);
        glVertex2f(222 + x, y);
        glEnd();
    }
    void Details()
    {
        glMatrixMode(GL_MODELVIEW);

        //Building_1//C001
        glColor3ub(91, 0, 91);
        glBegin(GL_POLYGON);
        glVertex2f(0, 340);
        glVertex2f(50, 340);
        glVertex2f(50, 330);
        glVertex2f(0, 330);
        glEnd();
        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(0, 320);
        glVertex2f(40, 320);
        glVertex2f(40, 330);
        glVertex2f(0, 330);
        glEnd();
        for (int i = 180; i < 311; i++)
        {
            if (i % 10 == 0)
            {
                Detail_1(0, i);
            }
        }

        //building_2//C002
        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(50, 315);
        glVertex2f(55, 315);
        glVertex2f(55, 290);
        glVertex2f(50, 290);
        glEnd();
        for (int i = 180; i < 281; i++)
        {
            if (i % 15 == 0)
            {
                Detail_2(0, i + 5);
            }
        }

        //Building_3//C003
        glColor3ub(91, 0, 91);
        glBegin(GL_POLYGON);
        glVertex2f(105, 330);
        glVertex2f(120, 330);
        glVertex2f(120, 320);
        glVertex2f(105, 320);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(145, 330);
        glVertex2f(130, 330);
        glVertex2f(130, 320);
        glVertex2f(145, 320);
        glEnd();
        for (int i = 290; i < 320; i++)
        {
            if (i % 5 == 0)
            {
                Detail_3(0, i);
            }
        }
        for (int i = 280; i < 320; i++)
        {
            if (i % 5 == 0)
            {
                Detail_3(53, i);
            }
        }
        for (int i = 100; i < 145; i++)
        {
            if (i % 10 == 0)
            {
                Detail_4(i + 1, 0);
            }
        }
        //Building_4//C004
        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(160, 288);
        glVertex2f(175, 288);
        glVertex2f(175, 280);
        glVertex2f(160, 280);
        glEnd();
        for (int i = 180; i < 275; i++)
        {
            if (i % 10 == 0)
            {
                Detail_5(0, i);
            }
        }
        //Building_5//C005
        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(200, 305);
        glVertex2f(173, 305);
        glVertex2f(173, 300);
        glVertex2f(200, 300);
        glEnd();
        for (int i = 175; i < 200; i++)
        {
            if (i % 5 == 0)
            {
                Detail_6(i + 1, 0);
            }
        }
        //Building_6//C006
        for (int i = 300; i < 350; i++)
        {
            if (i % 5 == 0)
            {
                Detail_3(100, i);
            }
        }
        for (int i = 300; i < 350; i++)
        {
            if (i % 5 == 0)
            {
                Detail_3(153, i);
            }
        }
        for (int i = 180; i < 350; i++)
        {
            if (i % 10 == 0)
            {
                Detail_7(0, i);
            }
        }
        for (int i = 180; i < 350; i++)
        {
            if (i % 10 == 0)
            {
                Detail_7(24, i);
            }
        }

        //Building_7//C013
        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(250, 260);
        glVertex2f(258, 260);
        glVertex2f(258, 295);
        glVertex2f(250, 295);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(253, 185);
        glVertex2f(272, 185);
        glVertex2f(272, 255);
        glVertex2f(253, 255);
        glEnd();

        //Building_8//C008
        glColor3ub(91, 0, 91);
        glBegin(GL_POLYGON);
        glVertex2f(275, 315);
        glVertex2f(325, 315);
        glVertex2f(325, 310);
        glVertex2f(275, 310);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(275, 295);
        glVertex2f(267, 295);
        glVertex2f(267, 285);
        glVertex2f(275, 285);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(275, 270);
        glVertex2f(267, 270);
        glVertex2f(267, 280);
        glVertex2f(275, 280);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(325, 295);
        glVertex2f(333, 295);
        glVertex2f(333, 285);
        glVertex2f(325, 285);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(325, 270);
        glVertex2f(333, 270);
        glVertex2f(333, 280);
        glVertex2f(325, 280);
        glEnd();

        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(280, 300);
        glVertex2f(320, 300);
        glVertex2f(320, 310);
        glVertex2f(280, 310);
        glEnd();
        for (int i = 275; i < 325; i++)
        {
            if (i % 5 == 0)
            {
                Detail_6(i + 1, 0);
            }
        }

        //Building_9//C009
        glPushMatrix();
        glTranslatef(92, 0, 0);
        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(250, 260);
        glVertex2f(258, 260);
        glVertex2f(258, 295);
        glVertex2f(250, 295);
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(75, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2f(253, 185);
        glVertex2f(272, 185);
        glVertex2f(272, 255);
        glVertex2f(253, 255);
        glEnd();
        glPopMatrix();

        //Building_10//C010
        glPushMatrix();
        glTranslatef(203, 0, 0);
        for (int i = 300; i < 350; i++)
        {
            if (i % 5 == 0)
            {
                Detail_3(100, i);
            }
        }
        glPopMatrix();
        glPushMatrix();
        glTranslatef(97, 0, 0);
        for (int i = 300; i < 350; i++)
        {
            if (i % 5 == 0)
            {
                Detail_3(153, i);
            }
        }
        glPopMatrix();
        glPushMatrix();
        glTranslatef(150, 0, 0);
        for (int i = 180; i < 350; i++)
        {
            if (i % 10 == 0)
            {
                Detail_7(0, i);
            }
        }
        glPopMatrix();
        glPushMatrix();
        glTranslatef(150, 0, 0);
        for (int i = 180; i < 350; i++)
        {
            if (i % 10 == 0)
            {
                Detail_7(24, i);
            }
        }
        glPopMatrix();
        //Building_11//C011
        glPushMatrix();
        glTranslatef(227, 0, 0);
        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(200, 305);
        glVertex2f(173, 305);
        glVertex2f(173, 300);
        glVertex2f(200, 300);
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(225, 0, 0);
        for (int i = 175; i < 200; i++)
        {
            if (i % 5 == 0)
            {
                Detail_6(i + 1, 0);
            }
        }
        glPopMatrix();
        //Building_12//C012
        glPushMatrix();
        glTranslatef(275, 0, 0);
        glColor3ub(55, 0, 55);
        glBegin(GL_POLYGON);
        glVertex2f(160, 288);
        glVertex2f(175, 288);
        glVertex2f(175, 280);
        glVertex2f(160, 280);
        glEnd();
        for (int i = 180; i < 275; i++)
        {
            if (i % 10 == 0)
            {
                Detail_5(0, i);
            }
        }
        glPopMatrix();
        //Building_13//C014
        glPushMatrix();
        glTranslatef(350, 0, 0);
        glColor3ub(91, 0, 91);
        glBegin(GL_POLYGON);
        glVertex2f(105, 330);
        glVertex2f(120, 330);
        glVertex2f(120, 320);
        glVertex2f(105, 320);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(145, 330);
        glVertex2f(130, 330);
        glVertex2f(130, 320);
        glVertex2f(145, 320);
        glEnd();
        for (int i = 290; i < 320; i++)
        {
            if (i % 5 == 0)
            {
                Detail_3(0, i);
            }
        }
        for (int i = 100; i < 145; i++)
        {
            if (i % 10 == 0)
            {
                Detail_4(i + 1, 0);
            }
        }
        glPopMatrix();
    }
    void CarTire()
    {
        //Tires

        glBegin(GL_POLYGON); //tire-1
        glLineWidth(7.5);
        for (int i = 0; i < 200; i++)
        {

            glColor3ub(0, 0, 0);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 2.5;
            float x = r * cos(A);
            float y = r * sin(A);
            //glVertex2f(x,y);
            glVertex2f((140 + (x * 5)), (93 + (y * 5)));
        }
        glEnd();
        //Point

        // 140=140+200;

        glBegin(GL_POLYGON);
        glLineWidth(7.5);
        for (int i = 0; i < 200; i++)
        {

            glColor3ub(168, 169, 173); //steel-cover
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 1.5;
            float x = (140 + (r * 5 * cos(A)));
            float y = (93 + (r * 5 * sin(A)));
            glVertex2f(x, y);
        }
        glEnd();
        //140=140+200;

        //points
        glColor3f(1.0, 0.0, 0.0);
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glVertex2f(140.0, 93.0);
        glVertex2f(140.0 + 5, 93.0);
        glVertex2f(140.0 - 5, 93.0);
        glVertex2f(140.0, 93.0 + 10);
        glVertex2f(140.0, 93.0 - 10);
        glEnd();
    }
    void CarBody()
    {

        glColor3f(1.0, 0.5725, 0.5529); //body
        //glColor3ub(252, 186, 3);
        glBegin(GL_POLYGON);
        //glColor3f(1.0, 0.5725, 0.5529);
        glVertex2f(140, 152);
        glVertex2f(190, 152);
        glVertex2f(215, 127);
        glVertex2f(240, 127);
        glVertex2f(240, 92);
        glVertex2f(110, 92);
        glVertex2f(110, 127);
        glVertex2f(130, 127);
        glVertex2f(140, 152);
        glEnd();

        glBegin(GL_POLYGON); //back-light
        glColor3ub(255, 0, 0);
        glVertex2f(110, 92);
        glVertex2f(115, 92);
        glVertex2f(115, 117);
        glVertex2f(110, 117);
        glEnd();

        glBegin(GL_POLYGON); //window
        glColor3ub(0, 0, 0);
        glVertex2f(140, 152);
        glVertex2f(190, 152);
        glVertex2f(215, 127);
        glVertex2f(210, 127);
        glVertex2f(120, 127);
        glVertex2f(130, 127);
        glEnd();

        glBegin(GL_POLYGON); //window-Divider
        glColor3ub(192, 192, 192);
        glVertex2f(170, 152);
        glVertex2f(165, 152);
        glVertex2f(165, 127);
        glVertex2f(170, 127);
        glEnd();

        glBegin(GL_POLYGON); //roof-plate
        glColor3ub(168, 169, 173);

        glVertex2f(140, 152);
        glVertex2f(190, 152);
        glVertex2f(185, 157);
        glVertex2f(140, 157);
        glEnd();

        glBegin(GL_POLYGON); //window-holder-front
        glColor3ub(168, 169, 173);
        glVertex2f(190, 152);
        glVertex2f(215, 127);
        glVertex2f(210, 127);
        glVertex2f(185, 152);
        glEnd();

        glBegin(GL_POLYGON); //window-holder-back
        glColor3ub(168, 169, 173);
        glVertex2f(140, 157);
        glVertex2f(115, 127);
        glVertex2f(125, 127);
        glVertex2f(140, 152);
        glEnd();

        glBegin(GL_POLYGON); //foot-holder
        glColor3ub(168, 169, 173);
        glVertex2f(215, 92);
        glVertex2f(110, 92);
        glVertex2f(110, 97);
        glVertex2f(215, 97);

        glEnd();

        glBegin(GL_POLYGON); //mirror
                             // glColor3f(0.3, 0.9, 0.6); //body
        //glColor3ub(255,250,0);
        glVertex2f(211.5, 134.5);
        glVertex2f(204.5, 135.5);
        glVertex2f(203.5, 129);
        glVertex2f(210.5, 127);
        glEnd();
    }

    void fullCar()
    {

        CarBody();

        // glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();

        glTranslatef(142.5, 95.5, 0);
        glRotatef(-_angle1, 0.0f, 0.0f, 1.0f);
        glTranslatef(-142.5, -95.5, 0);
        CarTire();
        glPopMatrix();
        // glutSwapBuffers();

        glPushMatrix();
        glTranslatef(60, 0, 0);

        glTranslatef(142.5, 95.5, 0);
        glRotatef(-_angle1, 0.0f, 0.0f, 1.0f);
        glTranslatef(-(142.5), -95.5, 0);
        CarTire();
        // CarTire();
        glPopMatrix();
    }
    // void CarForward()
    // {
    //     glMatrixMode(GL_MODELVIEW);

    //     // init();
    //     glPushMatrix();

    //     glTranslatef(-142.5, 0, 0);
    //     glTranslatef((_angle1 / 2) % 500, 0, 0);
    //     fullCar();

    //     glPopMatrix();

    //     glutSwapBuffers();
    // }
    void circle()
    {
        // glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        // glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
        glLineWidth(7.5);
        glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(125, 118, 117);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 30;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x, y);
        }

        //glVertex2f(0.3f,0.4f);
        //glVertex2f(0.1f,0.4f);

        glEnd();
    }
    void Crossing(float x, float y)
    {
        glColor3ub(255, 255, 255); // Clear the color buffer (background)
        glBegin(GL_POLYGON);       // Draw a Red 1x1 Square centered at origin
        glVertex2f(43 + x, 10.2 + y);
        glVertex2f(63 + x, 10.2 + y);
        glVertex2f(63 + x, 14.5 + y);
        glVertex2f(43 + x, 14.5 + y);
        glEnd();
    }
    void cloud()
    {
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
        glTranslatef(20, 95.5, 0);
        circle();

        glTranslatef(15, 2.5, 0);
        circle();

        glTranslatef(20, 5, 0);
        circle();

        glTranslatef(30, 2.5, 0);
        circle();

        glTranslatef(0, -2.5, 0);
        circle();

        glTranslatef(0, -5, 0);
        circle();

        glTranslatef(0, -7.5, 0);
        circle();

        glPopMatrix();

        // glutSwapBuffers();
    }

    void movingCloude() //V504s
    {
        glPushMatrix();
        glTranslatef(60, 400, 0);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(0.5, 0.5, 1);
        cloud();
        glTranslatef(200, 35, 0);
        cloud();
        glTranslatef((_angle1 / 2) % 1000, 0, 0);
        glPushMatrix();
        glTranslatef(-100, 0, 0);
        cloud();
        glTranslatef(200, 35, 0);
        cloud();
        glPopMatrix();
        glPopMatrix();

        glPopMatrix();
        // glutSwapBuffers();
    }

    void plane() //C050s
    {
        glPushMatrix();
        glTranslatef(-142.5, 450, 0);
        glScalef(0.3, 0.4, 1);
        glTranslatef((_angle1) % 2500, 0, 0);
        // glTranslated(a, c, 0.0);
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POLYGON); //rectangular body
        glVertex2f(0.0, 30.0);
        glVertex2f(0.0, 55.0);
        glVertex2f(135.0, 55.0);
        glVertex2f(135.0, 30.0);
        glEnd();
        // glPopMatrix();

        // glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POLYGON); //upper triangle construction plane
        glVertex2f(135.0, 55.0);
        glVertex2f(150.0, 50.0);
        glVertex2f(155.0, 45.0);
        glVertex2f(160.0, 40.0);
        glVertex2f(135.0, 40.0);
        glEnd();
        // glPopMatrix();

        // glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP); //outline of upper triangle plane
        glVertex2f(135.0, 55.0);
        glVertex2f(150.0, 50.0);
        glVertex2f(155.0, 45.0);
        glVertex2f(160.0, 40.0);
        glVertex2f(135.0, 40.0);
        glEnd();
        // glPopMatrix();

        // glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON); //lower triangle
        glVertex2f(135.0, 40.0);
        glVertex2f(160.0, 40.0);
        glVertex2f(160.0, 37.0);
        glVertex2f(145.0, 30.0);
        glVertex2f(135.0, 30.0);
        glEnd();
        // glPopMatrix();

        // glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON); //back wing
        glVertex2f(0.0, 55.0);
        glVertex2f(0.0, 80.0);
        glVertex2f(10.0, 80.0);
        glVertex2f(40.0, 55.0);
        glEnd();
        // glPopMatrix();

        // glPushMatrix();

        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON); //left side wing
        glVertex2f(65.0, 55.0);
        glVertex2f(50.0, 70.0);
        glVertex2f(75.0, 70.0);
        glVertex2f(90.0, 55.0);
        glEnd();
        // glPopMatrix();

        // glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON); //rightside wing
        glVertex2f(70.0, 40.0);
        glVertex2f(100.0, 40.0);
        glVertex2f(80.0, 15.0);
        glVertex2f(50.0, 15.0);

        glEnd();

        glPopMatrix();
    }
    void bench() //C023
    {
        glLineWidth(12);
        float y1 = 45.5;
        float y2 = 47.5;
        //colors
        glPushMatrix();
        // glScalef(-1.0,-1.0,0);
        glPushMatrix();
        glTranslatef(300, 130, 0);
        glScalef(2.5, 1.8, 0);

        glBegin(GL_QUADS); //sitting 2.0
        glColor3ub(204, 102, 0);
        glVertex2f(44, -60);
        glVertex2f(64, -60);
        glVertex2f(64, -58);
        glVertex2f(44, -58);

        glEnd();

        glBegin(GL_QUADS); //sitting 1.0
        glColor3ub(204, 102, 0);
        glVertex2f(45, -58);
        glVertex2f(63, -58);
        glVertex2f(63, -57);
        glVertex2f(45, -57);

        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(102, 51, 0);
        glVertex2f(46, -70);
        glVertex2f(48, -70);
        glVertex2f(48, -60);
        glVertex2f(46, -60);

        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(102, 51, 0);
        glVertex2f(60, -70);
        glVertex2f(62, -70);
        glVertex2f(62, -60);
        glVertex2f(60, -60);

        glEnd();

        glBegin(GL_QUADS); //2
        glColor3ub(204, 102, 0);
        for (int i = 0; i < 3; i++)
        {
            glVertex2f(45.5, -y1);
            glVertex2f(45.5, -y2);
            glVertex2f(62.5, -y2);
            glVertex2f(62.5, -y1);

            y1 += 3;
            y2 += 3;
        }

        glEnd();

        glBegin(GL_QUADS); //1.1
        glColor3ub(102, 51, 0);
        glVertex2f(46.5, -60);
        glVertex2f(48, -60);
        glVertex2f(48, -45);
        glVertex2f(46.5, -45);

        glEnd();

        glBegin(GL_QUADS); //1.2
        glColor3ub(102, 51, 0);
        glVertex2f(60, -60);
        glVertex2f(61.5, -60);
        glVertex2f(61.5, -45);
        glVertex2f(60, -45);
        glEnd();
        glTranslatef(-300, -130, 0);
        glPopMatrix();
        glPopMatrix();
    }
    void bench2() //C023
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(-370, 0, 0);
        bench();
        glTranslatef(370, 0, 0);
        glPopMatrix();
    }
    void footpath()
    {
        glBegin(GL_QUADS);
        glColor3ub(31, 46, 46);
        glVertex2f(0, 48);
        glVertex2f(500, 48);
        glVertex2f(500, 0);
        glVertex2f(0, 0);
        glEnd();
    }
    void traffic() //C025
    {
        glBegin(GL_QUADS);
        glColor3ub(67.0f, 70.0f, 75.0f);
        glVertex2f(250, 20);
        glVertex2f(255, 20);
        glVertex2f(255, 140);
        glVertex2f(250, 140);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(67.0f, 70.0f, 75.0f);
        glVertex2f(250, 140);
        glVertex2f(255, 140);
        glVertex2f(225, 178);
        glVertex2f(220, 178);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(128, 140, 131);
        glVertex2f(230, 165);
        glVertex2f(230, 152);
        glVertex2f(246, 133);
        glVertex2f(246, 146);
        glEnd();

        glColor3ub(255, 0, 0);
        circle(233, 155, 3);
        glColor3ub(255, 255, 0);
        circle(238, 149, 3);
        glColor3ub(0, 255, 0);
        circle(243, 143, 3);
    }
    void StreetLight()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(-100.0f, 40.0f, 0.0f);
        glScalef(0.5, 1, 0);
        glBegin(GL_QUADS);
        glColor3ub(67.0f, 70.0f, 75.0f); //steel-blue-pillar
        glVertex2f(250, 20);
        glVertex2f(255, 20);
        glVertex2f(255, 140);
        glVertex2f(250, 140);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(67.0f, 70.0f, 75.0f); //steel-blue-pillar-base-holder
        glVertex2f(248, 45);
        glVertex2f(257, 45);
        glVertex2f(260, 20);
        glVertex2f(245, 20);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(67.0f, 70.0f, 75.0f); //steel-blue-holder-p1
        glVertex2f(250, 140);
        glVertex2f(255, 140);
        glVertex2f(270, 170);
        glVertex2f(265, 170);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3ub(67.0f, 70.0f, 75.0f); //steel-blue-holder-p2
        glVertex2f(264, 170);
        glVertex2f(310, 170);
        glVertex2f(305, 175);
        glVertex2f(269, 175);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3ub(67.0f, 70.0f, 75.0f); //steel-blue-holder-p3
        glVertex2f(285, 170);
        glVertex2f(285, 165);
        glVertex2f(310, 165);
        glVertex2f(310, 170);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3ub(255.0f, 255.0f, 48); //bright-yellow-light
        if (isDay)
            glColor3ub(255, 255, 250); //bright-white-light
        glVertex2f(285, 165);
        glVertex2f(310, 165);
        glVertex2f(300, 155);
        glVertex2f(290, 158);
        glEnd();

        //  glFlush(); // Render now
        glPopMatrix(); // Render now
    }

    void scaledlight() //C026
    {
        int i;
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(0.6, 0.6, 0.0);
        StreetLight();

        for (i = 1; i < 50;)
        {
            glTranslatef(150, 0, 0);
            StreetLight();
            i += 10;
        }
        glPopMatrix();
    }
    void scaledlight1() //C026
    {
        int i;
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(0.3, 0.3, 0.0);
        glTranslatef(0, 540, 0);
        StreetLight();
        glTranslatef(0, -540, 0);

        for (i = 1; i < 110;)
        {
            glTranslatef(150, 540, 0);
            StreetLight();
            glTranslatef(0, -540, 0);
            i += 10;
        }
        glPopMatrix();
    }
    void trashcan() //C022
    {
        glBegin(GL_QUADS);
        glColor3ub(128, 140, 131);
        glVertex2f(100, 5);
        glVertex2f(110, 5);
        glVertex2f(115, 35);
        glVertex2f(95, 35);
        glEnd();
    }
    void trashbin() //C022_1
    {
        glMatrixMode(GL_MODELVIEW);
        trashcan();
        glPushMatrix();
        glTranslatef(290, 0, 0);
        trashcan();
        glPopMatrix();
    }
    void UmbrellaFrameLeft()
    {
        glBegin(GL_TRIANGLES); //p
        glColor3f(1, 1, 0);    // Yellow
        glVertex2f(250, 120);  // x, y
        glVertex2f(229, 70);   // x, y
        glVertex2f(250, 70);   // x, y
        glEnd();

        glBegin(GL_TRIANGLES); //p
        glColor3f(1, 0, 1);    // Purple
        glVertex2f(249, 120);  // x, y
        glVertex2f(209.0, 80); // x, y
        glVertex2f(230, 70);   // x, y
        glEnd();

        glBegin(GL_TRIANGLES); //p
        glColor3f(0, 1, 1);    // Red
        glVertex2f(249, 120);  // x, y
        glVertex2f(189, 90);   // x, y
        glVertex2f(210, 80);   // x, y
        glEnd();
    }

    void UmbrellaFrameRight()
    {
        glBegin(GL_TRIANGLES); //p
        glColor3f(0, 1, 0);    // Green
        glVertex2f(251, 120);  // x, y
        glVertex2f(251, 70);   // x, y
        glVertex2f(270, 70);   // x, y
        glEnd();

        glBegin(GL_TRIANGLES); //p
        glColor3f(0, 0, 1);    // Blue
        glVertex2f(251, 120);  // x, y
        glVertex2f(271, 70);   // x, y
        glVertex2f(290, 80);   // x, y
        glEnd();

        glBegin(GL_TRIANGLES); //p
        glColor3f(1, 0, 0);    // Red
        glVertex2f(251, 120);  // x, y
        glVertex2f(291, 80);   // x, y
        glVertex2f(310, 90);   // x, y
        glEnd();
    }
    void UmbrellaBody()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(0.6, 1, 0);
        glBegin(GL_POLYGON);  //Handle
        glColor3f(0, 0, 0);   // Red
        glVertex2f(249, 30);  // x, y
        glVertex2f(249, 130); // x, y
        glVertex2f(251, 130); // x, y
        glVertex2f(251, 30);  // x, y
        glEnd();
        UmbrellaFrameRight();
        UmbrellaFrameLeft();
        glPopMatrix();
    }
    void Umbrella() //C024
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(285, -25, 0);
        UmbrellaBody();
        glTranslatef(-285, 25, 0);
        glTranslatef(-85, -25, 0);
        UmbrellaBody();
        glTranslatef(85, 25, 0);
        glPopMatrix();
    }

    void CityView() //C000
    {
        sky();
        Background();
        movingCloude();
        plane();
        Building();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0, -28, 0);
        Road();
        glPopMatrix();
        Crossing(200, 150);
        Crossing(200, 130);
        Crossing(200, 110);
        Crossing(200, 90);
        Crossing(200, 70);
        Crossing(200, 50);
        Details();
        // Roadside();
        Roadside2();
        //CarForward();
        MovingScaledCarForward();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(100, 40, 0);
        MovingScaledTruckReverse();
        glTranslatef(0, 10, 0);
        MovingScaledCarReverse();

        glPopMatrix();
        footpath();
        scaledlight();
        traffic();
        bench();
        bench2();
        scaledlight1();
        // StreetLight();
        //trashcan();
        trashbin();
        Umbrella();
        glFlush(); // Render now
    }
};
/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
class NikliHaor
{
public:
    void Border()
    {
        glBegin(GL_LINES);
        glColor3ub(0, 255, 0);
        glVertex2f(0, 400);
        glVertex2f(500, 400);
        glEnd();
    }
    void Mountain()
    {
        glBegin(GL_POLYGON);
        glColor3ub(107, 107, 71);
        glVertex2f(85, 430);
        glColor3ub(14, 89, 7);
        glVertex2f(100, 455);
        glVertex2f(200, 300);
        glColor3ub(72, 36, 20);
        glVertex2f(170, 300);
        // glVertex2f(0, 300);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3ub(107, 107, 71);
        glVertex2f(0, 350);
        glVertex2f(80, 450);
        glColor3ub(12, 20, 30);
        glVertex2f(140, 380);
        glVertex2f(170, 300);
        glVertex2f(0, 300);
        glEnd();

        glBegin(GL_POLYGON);

        glColor3ub(79, 92, 89);
        glVertex2f(160, 360);
        glColor3ub(14, 89, 7);
        // glColor3ub(90, 113, 125);
        glVertex2f(260, 480);
        glColor3ub(107, 107, 71);
        glVertex2f(330, 360);
        glColor3ub(72, 36, 20);
        glVertex2f(380, 300);
        glColor3ub(12, 20, 30);
        glVertex2f(200, 300);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3ub(107, 107, 71);
        glVertex2f(330, 360);
        glVertex2f(420, 450);
        glVertex2f(500, 370);
        glVertex2f(500, 300);
        glVertex2f(380, 300);
        glEnd();
    }

    void SmallMountain(int x, int y)
    {
        glBegin(GL_POLYGON);
        glColor3ub(46, 43, 43);
        glVertex2f(0 + x, 370 + y);
        glVertex2f(15 + x, 400 + y);
        glVertex2f(30 + x, 360 + y);
        glVertex2f(0 + x, 350 + y);
        glEnd();
    }

    void outliner()
    {
        glLineWidth(3);
        glBegin(GL_LINES);
        glColor3ub(0, 0, 0);
        glVertex2f(0, 350);
        glVertex2f(80, 450);
        glVertex2f(80, 450);
        glVertex2f(140, 380);
        glVertex2f(140, 380);
        glVertex2f(170, 300);
        glVertex2f(90, 435);
        glVertex2f(100, 455);
        glVertex2f(100, 455);
        glVertex2f(200, 300);
        glVertex2f(260, 480);
        glVertex2f(330, 360);
        glVertex2f(330, 360);
        glVertex2f(380, 300);
        glVertex2f(330, 360);
        glVertex2f(420, 450);
        glVertex2f(420, 450);
        glVertex2f(500, 370);

        glEnd();
    }
    void scaledmountain()//L563
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(.3, .3, 0);
        glTranslatef(1170, 1040, 0);
        Mountain();
        glPopMatrix();
    }

    void circle(int xx, int yy, float r)
    {

        glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin

        for (int i = 0; i < 200; i++)
        {
            // glColor3ub(255, 215, 0);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            // float r = 4.0f;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x + xx, y + yy);
        }
        glEnd();
    }
    void sun()//L568
    {
        if (isDay)
        {
            glColor3ub(252, 186, 3); //midday sun effect
        }
        else
        {
            glColor3ub(228, 228, 228); //moon
        }

        circle(175, 440, 20);
    }
    void star() //L067
    {
        glLineWidth(2);
        glBegin(GL_LINES);
        glColor3ub(255, 251, 251); //white-star
        glVertex2f(-0.075, 0);
        glVertex2f(0.075, 0);

        glVertex2f(-0.05, -0.075);
        glVertex2f(0.05, 0.075);

        glVertex2f(0.05, -0.075);
        glVertex2f(-0.05, 0.075);

        glVertex2f(0, -0.1);
        glVertex2f(0, 0.1);

        glEnd();
    }
    void scaledstar()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(05, 490, 0);
        glScalef(15, 15, 0);
        star();
        glPopMatrix();
    }
    void scaledstarLoop()
    {
        scaledstar();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(5, 0, 0);

        for (int i = 0; i < 3; i++)
        {
            glTranslatef(0, -20, 0);
            scaledstar();
            for (int i = 0; i < 40; i++)
            {
                if (i % 2 == 0)
                {
                    glTranslatef(15, -35, 0);
                    scaledstar();
                }
                else
                {
                    glTranslatef(18, 35, 0);
                    scaledstar();
                }
            }
            glTranslatef(-660, -35, 0);
        }
        glPopMatrix();
    }
    void sky()//L564
    {
        //cloud();
        if (isDay)
        {
            glBegin(GL_QUADS);
            glColor3ub(51, 190, 255);
            glVertex2f(0, 300);
            glColor3ub(107, 207, 255);
            glVertex2f(500, 300);
            glColor3ub(0, 173, 255);
            glVertex2f(500, 500);
            glColor3ub(255, 250, 241);
            glVertex2f(0, 500);

            glEnd();
        }
        else
        {

            glBegin(GL_QUADS);
            glColor3ub(7, 11, 52);
            glVertex2f(0, 300);
            glColor3ub(0, 0, 255);
            glVertex2f(500, 300);
            glColor3ub(43, 47, 119);
            glVertex2f(500, 500);
            glColor3ub(20, 24, 82);
            glVertex2f(0, 500);
            glEnd();
            scaledstarLoop();
        }
    }
    void river()//H561
    {
        glBegin(GL_QUADS);         //uper
        glColor3ub(184, 220, 245); //aqua green
        glVertex2f(0, 400);
        glColor3ub(238, 241, 241); //black haze
        glVertex2f(500, 400);
        glColor3ub(7, 36, 71); //downriver color
        glVertex2f(500, 180);
        glColor3ub(131, 177, 224); //cornflower //white ice
        glVertex2f(0, 180);
        glEnd();

        glBegin(GL_QUADS); // down river
        glColor3ub(7, 36, 71);
        glVertex2f(0, 0);
        glColor3ub(238, 241, 241);
        glVertex2f(500, 0);
        glColor3ub(184, 220, 245);
        glVertex2f(500, 80);
        // glColor3ub(179, 89, 0);
        glVertex2f(0, 80);

        glEnd();

        glBegin(GL_QUADS); //river bank
        glColor3ub(72, 67, 76);
        glVertex2f(0, 80);
        glColor3ub(92, 94, 116);
        glVertex2f(500, 80);
        glColor3ub(52, 35, 36);
        glVertex2f(500, 112);
        glVertex2f(0, 112);
        glEnd();
    }

    void Badh()//H562
    {

        // glColor3b(204, 102, 0); //Badh color
        glBegin(GL_POLYGON);
        glColor3ub(118, 157, 168);
        glVertex2f(0, 122);
        glColor3ub(40, 96, 120);
        glVertex2f(20, 122);
        glColor3ub(63, 51, 48);
        glVertex2f(20, 110);
        glColor3ub(172, 172, 41);
        glVertex2f(0, 110);
        glColor3ub(185, 172, 172);
        glEnd();

        //create border
        glColor3b(0, 0, 0); //border color

        glBegin(GL_LINE_LOOP);
        glVertex2f(0, 122);
        glVertex2f(20, 122);
        glVertex2f(20, 110);
        glVertex2f(0, 110);
        glEnd();
    }

    void fullBath()
    {
        glColor3ub(204, 102, 0);
        //transform Badh to using push matrix and pop matrix
        for (size_t i = 0; i < 25; i++)
        {
            glPushMatrix();
            glTranslatef(0 + (20 * i), 0, 0);
            glColor3ub(204, 90 + (5 * i), 0);
            Badh();
            glPopMatrix();
        }
    }

    void fullBadh3layer()
    {
        for (size_t i = 0; i < 3; i++)
        {
            glPushMatrix();
            glTranslatef(0, 0 + (i * 12), 0);

            fullBath();
            glPopMatrix();
        }
    }

    void circle()
    {
        // glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        // glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
        glLineWidth(7.5);
        glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(203, 203, 203);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 30;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x, y);
        }

        //glVertex2f(0.3f,0.4f);
        //glVertex2f(0.1f,0.4f);

        glEnd();
    }

    void cloud()//L566
    {
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
        glTranslatef(20, 95.5, 0);
        circle();

        glTranslatef(15, 2.5, 0);
        circle();

        glTranslatef(20, 5, 0);
        circle();

        glTranslatef(30, 2.5, 0);
        circle();

        glTranslatef(0, -2.5, 0);
        circle();

        glTranslatef(0, -5, 0);
        circle();

        glTranslatef(0, -7.5, 0);
        circle();

        glPopMatrix();

        // glutSwapBuffers();
    }

    void movingcloud()//L565
    {
        glPushMatrix(); //stationary-cloud
        glTranslatef(10, 405, 0);
        glScalef(0.5, 0.5, 0);
        cloud();
        glTranslatef(500, 0, 0);
        cloud();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(500, 400, 0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(0.5, 0.5, 1);
        glTranslatef(-(_angle1 / 2 % 1000), 0, 0);
        glPushMatrix();
        glTranslatef(-100, 0, 0);
        cloud();
        glTranslatef(200, 35, 0);
        cloud();
        glPopMatrix();
        glPopMatrix();

        glPopMatrix();
        // glutSwapBuffers();
    }
    void TropicalTreeLeafCircle()
    {
        if (isDay)
        {
            glColor3ub(0.0, 255, 0.0); //green-leaf
        }
        else
        {
            glColor3ub(0.0, 25, 0.0); //green-leaf
        }

        glBegin(GL_POLYGON);
        for (int i = 0; i < 200; i++)
        {

            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 15.85;
            float x = 2 * r * cos(A);
            float y = r * sin(A);
            glVertex2f(x, y);
        }

        glEnd();
    }
    void TropicalTreeLeafCircles() //tree2//L074
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(215, 360, 0); //lower-branch
        TropicalTreeLeafCircle();
        glTranslatef(20, -15, 0);
        TropicalTreeLeafCircle();
        glTranslatef(0, 20, 0);
        TropicalTreeLeafCircle();
        glTranslatef(70, 20, 0); //middle-branch
        TropicalTreeLeafCircle();
        glTranslatef(20, 20, 0);
        TropicalTreeLeafCircle();
        glTranslatef(20, -20, 0);
        TropicalTreeLeafCircle();
        glTranslatef(-50, 60, 0); //Upper-branch
        TropicalTreeLeafCircle();
        glTranslatef(-30, 20, 0);
        TropicalTreeLeafCircle();
        glTranslatef(-30, -10, 0); //Upper-branch
        TropicalTreeLeafCircle();
        glTranslatef(-30, -10, 0); //Upper-branch
        TropicalTreeLeafCircle();
        glTranslatef(25, -10, 0); //Upper-branch
        TropicalTreeLeafCircle();

        glPopMatrix();
    }
    void TropicalTreeBranch()
    {
        glColor3ub(128, 0, 0);
        glBegin(GL_POLYGON); //maroon-lower-branch-1
        glVertex2f(240, 300);
        glVertex2f(260, 300);
        glVertex2f(230, 330);
        glVertex2f(235, 335);
        glEnd();

        glBegin(GL_POLYGON); //maroon-lower-branch-2
        glVertex2f(230, 330);
        glVertex2f(235, 335);
        glVertex2f(215, 360);
        glEnd();

        glBegin(GL_POLYGON); //maroon-middle-branch-p-3
        glVertex2f(280, 350);
        glVertex2f(270, 355);
        glVertex2f(320, 390);
        glEnd();

        glBegin(GL_POLYGON); //maroon-middle-branch-p-4
        glVertex2f(260, 390);
        glVertex2f(270, 395);
        glVertex2f(230, 430);
        glEnd();
    }
    void TropicalTreeLog()
    {
        glColor3ub(128, 0, 0);
        glBegin(GL_POLYGON); //maroon-log-p-1
        glVertex2f(250, 250);
        glVertex2f(240, 300);
        glVertex2f(260, 300);
        glVertex2f(270, 250);
        glEnd();
        glBegin(GL_POLYGON); //maroon-log-p-2
        glVertex2f(240, 300);
        glVertex2f(260, 300);
        glVertex2f(280, 350);
        glVertex2f(270, 355);
        glEnd();
        glBegin(GL_POLYGON); //maroon-log-p-3
        glVertex2f(280, 350);
        glVertex2f(270, 355);
        glVertex2f(260, 390);
        glVertex2f(270, 395);
        glEnd();
        glBegin(GL_POLYGON); //maroon-log-p-4
        glVertex2f(260, 390);
        glVertex2f(270, 395);
        glVertex2f(280, 450);
        glVertex2f(275, 435);
        glEnd();
    }
    void TropicalTree()

    {
        TropicalTreeLog();
        TropicalTreeBranch();
        TropicalTreeLeafCircles();
    }
    void ScaledTropicalTree()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(0.5, 0.5, 0);
        glTranslatef(-180, 110, 0);
        TropicalTree();
        glPopMatrix();
    }
    void TropicalTreeLoop()
    {

        glPushMatrix();
        for (int tree = 0; tree < 05; tree++)
        {

            ScaledTropicalTree();
            glTranslatef(100, 0, 0);
        }

        glPopMatrix();
    }

    void circle1(int xx, int yy, float r)
    {

        glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin
        for (int i = 0; i < 200; i++)
        {
            // glColor3ub(255, 215, 0);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            // float r = 4.0f;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x + xx, y + yy);
        }
        glEnd();
    }
    void Roadbody()
    {

        glBegin(GL_POLYGON);
        glColor3ub(204, 122, 0);
        glVertex2f(500, 180);
        glColor3ub(153, 61, 0);
        glVertex2f(500, 145);
        glColor3ub(255, 170, 0);
        glVertex2f(0, 145);
        glColor3ub(179, 89, 0);
        glVertex2f(0, 180);

        glEnd();
    }

    void road()//H560
    {
        /* glMatrixMode(GL_MODELVIEW);
         glPushMatrix();
         glTranslatef(0, 100, 0);*/
        Roadbody();
        /*glTranslatef(0, -100, 0);
        glPopMatrix();*/
    }

    void BoatBodyStick() //boitha
    {
        glBegin(GL_LINES);
        glColor3ub(165, 42, 42); //brown-stick
        glVertex2f(210, 75);
        glVertex2f(220, 10);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3ub(0, 0, 0); //brown-stick
        glVertex2f(218, 20);
        glVertex2f(220, 10);
        glVertex2f(230, 10);
        glEnd();
    }
    void BoatBodyShell() //L067//L068//L069
    {
        glBegin(GL_POLYGON);
        glColor3ub(165, 42, 42); //brown-shell
        glVertex2f(120, 30);
        glVertex2f(200, 30);
        glVertex2f(195, 55);
        glVertex2f(125, 55);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(255, 255, 0); //yellow-shell-stripe-pattern
        glVertex2f(120, 30);
        glVertex2f(200, 30);

        glVertex2f(121, 35);
        glVertex2f(199, 35);

        glVertex2f(122, 40);
        glVertex2f(198, 40);

        glVertex2f(123, 45);
        glVertex2f(197, 45);

        glVertex2f(124, 50);
        glVertex2f(196, 50);

        glVertex2f(125, 55);
        glVertex2f(195, 55);

        glEnd();
    }
    void BoatBody()
    {
        glLineWidth(1);
        glBegin(GL_QUADS);
        glColor3ub(0, 0, 0); //black-base
        glVertex2f(120, 10);
        glVertex2f(200, 10);
        glVertex2f(200, 30);
        glVertex2f(120, 30);
        glEnd();
        glBegin(GL_TRIANGLES); //black-nose-front
        glVertex2f(120, 10);
        glVertex2f(120, 30);
        glVertex2f(80, 40);
        glEnd();
        glBegin(GL_TRIANGLES); //black-nose-back
        glVertex2f(200, 10);
        glVertex2f(200, 30);
        glVertex2f(240, 40);
        glEnd();

        glBegin(GL_POLYGON); //yellow-inside-shape
        glColor3ub(255, 255, 0);
        glVertex2f(240, 40);
        glVertex2f(80, 40);
        glVertex2f(120, 30);
        glVertex2f(200, 30);
        glEnd();

        glBegin(GL_LINES);
        glColor3b(0, 0, 0); //black_stripe
        glVertex2f(205, 30);
        glVertex2f(200, 40);

        glVertex2f(210, 30);
        glVertex2f(205, 40);

        glVertex2f(215, 30);
        glVertex2f(210, 40);

        glVertex2f(220, 30);
        glVertex2f(215, 40);

        glVertex2f(225, 30);
        glVertex2f(220, 40);

        //
        glVertex2f(115, 30);
        glVertex2f(120, 40);

        glVertex2f(110, 30);
        glVertex2f(115, 40);

        glVertex2f(105, 30);
        glVertex2f(110, 40);

        glVertex2f(100, 30);
        glVertex2f(105, 40);

        glVertex2f(95, 30);
        glVertex2f(100, 40);

        glEnd();
        BoatBodyShell();
    }
    void Boatsticks()
    {
        // BoatBodyStick();
        glBegin(GL_LINES);
        glLineWidth(3);
        glColor3ub(32, 12, 2);
        glVertex2f(62, 5);
        glVertex2f(67, 55);
        glEnd();
    }
    void Boats()
    {
        if (isDay)
        {
            glPushMatrix();
            glTranslatef(310, 70, 0);
            glTranslatef(10, 310, 0);
            glTranslatef((-_boatMove / 6) % 500, 0, 0);
            glTranslatef(110, 00, 0);

            glScalef(0.3, 0.3, 0);
            BoatBody();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-40, 60, 0);
            glTranslatef(0, 310, 0);
            glTranslatef(((_boatMove / 4) % 500), 0, 0);
            glScalef(0.3, 0.3, 0);
            BoatBody();
            glTranslatef(-500, 0, 0);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(10, 310, 0);
            glTranslatef(510, 30, 0);
            glTranslatef(-(_boatMove / 6) % 520, 0, 0);
            glScalef(0.6, 0.6, 0);
            BoatBody();
            glPopMatrix();

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glTranslatef(-100, 310, 0);
            glTranslatef((_boatMove / 3) % 500, 0, 0);
            glScalef(0.7, 0.7, 0);
            BoatBody();
            glPopMatrix();
        }
        else
        {
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glTranslatef(20, 175, 0);
            Boatsticks();

            glScalef(0.7, 0.7, 0);
            BoatBody();
            glTranslatef(105, -2, 0);
            //glScalef(0.7,0.7,0);
            BoatBody();
            glLineWidth(8);
            glTranslatef(40, 0, 0);
            Boatsticks();
            glPopMatrix();
        }
    }

    void Container(float x, float y) //L070
    {
        glBegin(GL_POLYGON);
        glVertex2f(x, 125 + y);
        glVertex2f(x, 150 + y);
        glVertex2f(10 + x, 150 + y);
        glVertex2f(10 + x, 125 + y);
        glEnd();
    }

    void Window(float x, float y) //L070
    {
        glBegin(GL_POLYGON);
        glVertex2f(x, 175 + y);
        glVertex2f(x, 170 + y);
        glVertex2f(5 + x, 170 + y);
        glVertex2f(5 + x, 175 + y);
        glEnd();
    }

    void Railing(float x, float y) //L070
    {
        glLineWidth(5);
        glColor3ub(36, 36, 74);
        glBegin(GL_LINES);
        glVertex2f(x, 125 + y);
        glVertex2f(x, 135 + y);
        glEnd();
    }

    void Ship() //L070
    {
        glBegin(GL_QUADS); //chimney
        glColor3ub(0, 0, 100);
        glVertex2f(210, 170);
        glVertex2f(195, 170);
        glVertex2f(198, 210);
        glVertex2f(207, 210);
        glEnd();
        glLineWidth(5);
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(197, 200);
        glVertex2f(208, 200);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(197, 193);
        glVertex2f(208, 193);
        glEnd();
        glBegin(GL_LINES);
        glColor3ub(255, 0, 0);
        glVertex2f(199, 210);
        glVertex2f(206, 210);
        glEnd();

        glBegin(GL_POLYGON); //cabin
        glColor3ub(116, 202, 141);
        glVertex2f(180, 125);
        glVertex2f(180, 180);
        glVertex2f(200, 180);
        glVertex2f(200, 170);
        glVertex2f(220, 170);
        glVertex2f(220, 125);
        glEnd();
        glBegin(GL_POLYGON);
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(255, 0, 0);
            float pi = 3.1416;
            float A = (i * pi) / 200;
            float r = 8;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x + 190, y + 185);
        }

        glEnd();
        glBegin(GL_POLYGON);
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(116, 202, 141);
            float pi = 3.1416;
            float A = (i * pi) / 200;
            float r = 10;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x + 190, y + 179);
        }

        glEnd();

        glBegin(GL_POLYGON); //ship body
        glColor3ub(178, 87, 223);
        glVertex2f(90, 150);
        glVertex2f(120, 150);
        glVertex2f(130, 125);
        glVertex2f(130, 100);
        glVertex2f(100, 100);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(178, 87, 223);
        glVertex2f(130, 125);
        glVertex2f(130, 100);
        glVertex2f(200, 100);
        glVertex2f(200, 125);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3ub(178, 87, 223);
        glVertex2f(200, 150);
        glVertex2f(225, 150);
        glVertex2f(230, 125);
        glVertex2f(220, 100);
        glVertex2f(200, 100);
        glVertex2f(200, 125);
        glVertex2f(205, 150);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(111, 3, 165);
        glVertex2f(100, 100);
        glVertex2f(220, 100);
        glVertex2f(220, 95);
        glVertex2f(100, 95);
        glEnd();

        glColor3ub(255, 0, 0); //Container
        for (int i = 130; i < 171; i++)
        {
            if (i % 20 == 0)
            {
                Container(i, 0);
            }
        }
        glColor3ub(0, 128, 255);
        for (int i = 130; i < 181; i++)
        {
            if (i % 20 == 0)
            {
                Container(i - 10, 0);
            }
        }
        glColor3ub(255, 222, 0);
        for (int i = 130; i < 171; i++)
        {
            if (i % 20 == 0)
            {
                Container(i + 5, 25);
            }
        }
        glColor3ub(9, 255, 0);
        for (int i = 130; i < 171; i++)
        {
            if (i % 20 == 0)
            {
                Container(i - 5, 25);
            }
        }
        glColor3ub(255, 128, 0);
        for (int i = 130; i < 151; i++)
        {
            if (i % 20 == 0)
            {
                Container(i + 10, 50);
            }
        }
        glColor3ub(255, 128, 255);
        for (int i = 130; i < 171; i++)
        {
            if (i % 20 == 0)
            {
                Container(i, 50);
            }
        }

        glColor3ub(0, 0, 0); //windows
        for (int i = 180; i < 200; i++)
        {
            if (i % 10 == 0)
            {
                Window(i + 2, 0);
            }
        }
        for (int i = 180; i < 220; i++)
        {
            if (i % 10 == 0)
            {
                Window(i + 2, -8);
            }
        }
        for (int i = 180; i < 220; i++)
        {
            if (i % 10 == 0)
            {
                Window(i + 2, -16);
            }
        }
        for (int i = 180; i < 200; i++)
        {
            if (i % 10 == 0)
            {
                Window(i + 2, -24);
            }
        }
        for (int i = 180; i < 200; i++)
        {
            if (i % 10 == 0)
            {
                Window(i + 2, -32);
            }
        }
        glBegin(GL_POLYGON); //cabin
        glColor3ub(0, 0, 0);
        glVertex2f(183, 178);
        glVertex2f(197, 178);
        glVertex2f(197, 183);
        glVertex2f(183, 183);
        glEnd();

        glLineWidth(5); //railing
        glColor3ub(36, 36, 74);
        glBegin(GL_LINES);
        glVertex2f(125, 135);
        glVertex2f(200, 135);
        glEnd();
        for (int i = 130; i < 200; i++)
        {
            if (i % 10 == 0)
            {
                Railing(i, 0);
            }
        }
    }

    void scalledship() //L070
    {
        glPushMatrix();
        glTranslatef(100, 0, 0);
        glScalef(1.4, 1.2, 0);
        glTranslatef(120, 100, 0);
        glTranslatef((-_boatMove / 4) % 500, 0, 0);
        Ship();
        glPopMatrix();
    }

    //add method//Launch//L071
    void Boat2Windows()
    {
        if (isDay)
        {
            glColor3ub(22, 22, 0); //yellow-window
        }
        else
        {
            glColor3ub(202, 202, 0); //yellow-window
        }
        glBegin(GL_QUADS);
        glVertex2f(135, 35);
        glVertex2f(150, 35);
        glVertex2f(150, 50);
        glVertex2f(135, 50);
        glEnd();
    }
    void Boat2WindowLoop()
    {
        Boat2Windows();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        for (int windowNo = 0; windowNo < 4; windowNo++)
        {
            glTranslatef(20, 0, 0);
            Boat2Windows();
        }
        glTranslatef(20, 0, 0);
        Boat2Windows();
        glPopMatrix();
    }
    void Boat2Shed()
    {

        glBegin(GL_QUADS);
        glColor3ub(102, 102, 51); //brown-shed
        glVertex2f(120, 30);
        glVertex2f(240, 30);
        glVertex2f(240, 55);
        glVertex2f(130, 55);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(102, 0, 0); //red-shed-ceiling
        glVertex2f(240, 55);
        glVertex2f(130, 55);
        glVertex2f(128, 60);
        glVertex2f(240, 60);
        glEnd();
        Boat2WindowLoop();
    }
    void Boat2BackStick()
    {
        glBegin(GL_LINES);
        glColor3ub(165, 42, 42); //brown-stick
        glVertex2f(210 + 50, 75);
        glVertex2f(220 + 50, 10);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3ub(255, 0, 0); //red-quads
        glVertex2f(218 + 50, 20);
        glVertex2f(220 + 50, 10);
        glVertex2f(230 + 50, 10);
        glVertex2f(280, 20);
        glEnd();
    }
    void Boat2BackBox()
    {
        glBegin(GL_POLYGON);
        glColor3ub(245, 176, 66); //orange-box
        glVertex2f(260 + 5, 40);
        glVertex2f(250 + 5, 30);
        glVertex2f(230 + 5, 30);
        glVertex2f(230 + 5, 70);
        glVertex2f(260 + 5, 70);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3ub(245, 0, 0); //red-box-ceiling
        glVertex2f(230, 70);
        glVertex2f(260 + 5 + 5, 70);
        glVertex2f(260 + 5, 75);
        glVertex2f(230 + 5 + 2, 75);
        glEnd();
    }
    void Boat2Body()
    {
        Boat2BackStick();
        glBegin(GL_QUADS);
        glColor3ub(255, 0, 0); //red-base
        glVertex2f(120, 10);
        glVertex2f(250, 10);
        glVertex2f(250, 30);
        glVertex2f(120, 30);
        glEnd();
        glBegin(GL_TRIANGLES); //black-nose-front
        glVertex2f(120, 10);
        glVertex2f(120, 30);
        glVertex2f(80, 40);
        glEnd();

        glBegin(GL_TRIANGLES); //black-nose-back
        glVertex2f(200 + 50, 10);
        glVertex2f(200 + 50, 30);
        glVertex2f(240 + 50, 40 + 20);
        glEnd();
        glColor3f(0.0, 1.0, 0.7);
        text(130.0, 20.0, text1);
        glBegin(GL_POLYGON); //yellow-inside-shape
        glColor3ub(255, 255, 0);
        glVertex2f(250, 40);
        glVertex2f(80, 40);
        glVertex2f(120, 30);
        glVertex2f(250, 30);
        glEnd();

        Boat2Shed();
        Boat2BackBox();
    }
    void Boat2()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0, 0, 0);
        Boat2Body();
        glPopMatrix();
    }

    void ScaledBoat2()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(450, 0, 0);
        glScalef(1.2, 1.2, 0);
        glTranslatef((-_boatMove / 3) % 750, 0, 0);
        Boat2();
        glPopMatrix();
    }

    void output(void)
    {

        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLineWidth(5);
        sky();
        Border();
        scaledmountain();
        sun();
        movingcloud();
        river();

        road();
        Boats();
        //   tree();
        scalledship();
        TropicalTreeLoop();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0, 70, 0);
        MovingScaledCarForward();
        glPopMatrix();
        fullBadh3layer();
        ScaledBoat2();
        //allupdates();
        //nightEffect();
        // glDisable(GL_LIGHTING);//Enable Light Effect

        glFlush();
    }

    void daynightmodechanger(int val)
    {
        //isDay=false;
        // glutDisplayFunc(output);
        glutPostRedisplay();
        //glutTimerFunc(500, daynightmodechanger, 0);
    }
};
class Village
{
public:
    void TreeBody() //tree-1//V047
    {
        glColor3ub(210.0f, 105.0, 30.0); //RGB chocholate
        glBegin(GL_QUADS);               //body
        glVertex2f(90, (10 + (-10 * 2.0f)));
        glVertex2f(((0.5 * 10) + 100), (10 + (10 * 0.0f)));
        glVertex2f(((0.80 * 10) + 100), (10 + (10 * 8.0f)));
        glVertex2f(((-0.5 * 10) + 100), (10 + (10 * 6.0f)));
        glEnd();

        glColor3ub(139.0, 69.0, 19.0); //RGB_saddle-brown
        glBegin(GL_TRIANGLES);         //Left_Branch
        glVertex2f(((-0.5 * 10) + 100), (10 + (10 * 6.0f)));
        glVertex2f(((-3.5 * 10) + 100), (10 + (10 * 9.0f)));
        glVertex2f(((-0.5 * 10) + 100), (10 + (10 * 5.4f)));
        glEnd();

        glBegin(GL_TRIANGLES); //Right_Branch
        glVertex2f(((0.5 * 10) + 100), (10 + (10 * 5.8f)));
        glVertex2f(((5.0 * 10) + 100), (10 + (10 * 11.5f)));
        glVertex2f(((0.7 * 10) + 100), (10 + (10 * 5.3f)));
        glEnd();

        glColor3ub(139.0, 69.0, 19.0); //RGB_saddle-brown
        glBegin(GL_TRIANGLES);         //Right_root
        glVertex2f(((0.5 * 10) + 100), (10 + (10 * 0.0f)));
        glVertex2f(((0.4 * 10) + 100), (10 + (10 * 1.0f)));
        glVertex2f(((4.0 * 10) + 100), (10 + (10 * 0.0f)));
        glEnd();

        glBegin(GL_TRIANGLES); //Left_root
        glVertex2f(((-0.5 * 10) + 100), (10 + (10 * 0.5f)));
        glVertex2f(((-0.4 * 10) + 100), (10 + (10 * 1.5f)));
        glVertex2f(((-4.0 * 10) + 100), (10 + (10 * 0.0f)));
        glEnd();
    }
    void Leaf()
    {

        glBegin(GL_POLYGON); // Draw a green circle centered at up left
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(54.0f, 128.0f, 45.0f);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 3.5;
            float p = (100 + (10 * ((r * cos(A)) - 5)));
            float q = (10 + (10 * (10 + r * sin(A))));
            glVertex2f(p, q);
        }
        glEnd();

        glBegin(GL_POLYGON); // Draw a green circle centered at upper left
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(54.0f, 128.0f, 45.0f);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 3.5;
            float p = (100 + (10 * ((r * cos(A)) - 4)));
            float q = (10 + (10 * (13 + r * sin(A))));
            glVertex2f(p, q);
        }
        glEnd();

        glBegin(GL_POLYGON); // Draw a green circle centered at up Right
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(54.0f, 128.0f, 45.0f);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 3.5;
            float p = (100 + (10 * ((r * cos(A)) + 5)));
            float q = (10 + (10 * (10 + r * sin(A))));
            glVertex2f(p, q);
        }

        glEnd();

        glBegin(GL_POLYGON); // Draw a green circle centered at upper left
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(54.0f, 128.0f, 45.0f);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 3.5;
            float p = (100 + (10 * ((r * cos(A)) - 4)));
            float q = (10 + (10 * (13 + r * sin(A))));
            glVertex2f(p, q);
        }
        glEnd();

        glBegin(GL_POLYGON); // Draw a green circle centered at upper right
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(54.0f, 128.0f, 45.0f);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 3.5;
            float p = (100 + (10 * ((r * cos(A)) + 4)));
            float q = (10 + (10 * (13 + r * sin(A))));
            glVertex2f(p, q);
        }
        glEnd();

        glBegin(GL_POLYGON); // Draw a green circle centered at up middle
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(54.0f, 128.0f, 45.0f);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 5.5;
            float p = (100 + (10 * (r * cos(A))));
            float q = (10 + (10 * (13 + r * sin(A))));
            glVertex2f(p, q);
        }

        glEnd();
    }
    void Tree()
    {

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(200, 380, 0);
        glScalef(0.25, 0.25, 0);
        TreeBody();
        Leaf();
        for (int treeNo = 1; treeNo < 9; treeNo++)
        {
            glTranslatef(120 + (treeNo * 10), 0, 0);
            TreeBody();
            Leaf();
        }

        glPopMatrix();
    }

    void Mountain() //V054 -V057
    {
        glBegin(GL_POLYGON); //V054
        glColor3ub(107, 107, 71);
        glVertex2f(85, 430);
        glColor3ub(14, 89, 7);
        glVertex2f(100, 455);
        glVertex2f(200, 300);
        glColor3ub(72, 36, 20);
        glVertex2f(170, 300);
        // glVertex2f(0, 300);
        glEnd();

        glBegin(GL_POLYGON); //V055
        glColor3ub(107, 107, 71);
        glVertex2f(0, 350);
        glVertex2f(80, 450);
        glColor3ub(12, 20, 30);
        glVertex2f(140, 380);
        glVertex2f(170, 300);
        glVertex2f(0, 300);
        glEnd();

        glBegin(GL_POLYGON); //V056

        glColor3ub(79, 92, 89);
        glVertex2f(160, 360);
        glColor3ub(14, 89, 7);
        // glColor3ub(90, 113, 125);
        glVertex2f(260, 480);
        glColor3ub(107, 107, 71);
        glVertex2f(330, 360);
        glColor3ub(72, 36, 20);
        glVertex2f(380, 300);
        glColor3ub(12, 20, 30);
        glVertex2f(200, 300);
        glEnd();

        glBegin(GL_POLYGON); //V057
        glColor3ub(107, 107, 71);
        glVertex2f(330, 360);
        glVertex2f(420, 450);
        glVertex2f(500, 370);
        glVertex2f(500, 300);
        glVertex2f(380, 300);
        glEnd();
    }

    void SmallMountain(int x, int y)
    {
        glBegin(GL_POLYGON);
        glColor3ub(46, 43, 43);
        glVertex2f(0 + x, 370 + y);
        glVertex2f(15 + x, 400 + y);
        glVertex2f(30 + x, 360 + y);
        glVertex2f(0 + x, 350 + y);
        glEnd();
    }

    void outliner() //V059
    {
        glLineWidth(3);
        glBegin(GL_LINES);
        glColor3ub(0, 0, 0);
        glVertex2f(0, 350);
        glVertex2f(80, 450);
        glVertex2f(80, 450);
        glVertex2f(140, 380);
        glVertex2f(140, 380);
        glVertex2f(170, 300);
        glVertex2f(90, 435);
        glVertex2f(100, 455);
        glVertex2f(100, 455);
        glVertex2f(200, 300);
        glVertex2f(260, 480);
        glVertex2f(330, 360);
        glVertex2f(330, 360);
        glVertex2f(380, 300);
        glVertex2f(330, 360);
        glVertex2f(420, 450);
        glVertex2f(420, 450);
        glVertex2f(500, 370);

        glEnd();
    }

    void scaledmountain()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(.5, .5, 0);
        glTranslatef(500, 502, 0);
        Mountain();
        glPopMatrix();
    }

    void Roadbody() //V041
    {
        //int x = 0, y = 0;

        glBegin(GL_POLYGON);
        glColor3ub(204, 122, 0);
        glVertex2f(500, 180);
        glColor3ub(153, 61, 0);
        glVertex2f(500, 150);
        glColor3ub(255, 170, 0);
        glVertex2f(0, 150);
        glColor3ub(179, 89, 0);
        glVertex2f(0, 180);

        glEnd();
    }
    void road() //V041
    {

        Roadbody();
    }
    void circle(int xx, int yy, float r) //V036
    {

        glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin
                             // glColor3ub(252, 186, 3);     //midday sun color palatte
        for (int i = 0; i < 200; i++)
        {
            // glColor3ub(255, 215, 0);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            // float r = 4.0f;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x + xx, y + yy);
        }
        glEnd();
    }

    void river() //V049
    {
        glLineWidth(2.5);
        glBegin(GL_LINES);
        glColor3ub(128, 150, 0);
        glVertex2f(0, 400);
        glVertex2f(500, 400);
        glEnd();

        glColor3ub(60, 188, 255);

        glBegin(GL_POLYGON);
        glVertex2f(0, 140);
        glVertex2f(200, 130);
        glVertex2f(500, 110);
        glVertex2f(500, 0);
        glVertex2f(0, 0);
        glEnd();

        glLineWidth(5);
        glBegin(GL_LINES);
        glColor3ub(255, 128, 0);
        glVertex2f(0, 140);
        glVertex2f(200, 130);
        glVertex2f(200, 130);
        glVertex2f(500, 110);
        glEnd();

        glBegin(GL_QUADS); //riverbank
        glColor3ub(11, 20, 9);
        glVertex2f(0, 150);
        glColor3ub(160, 137, 98);
        glVertex2f(0, 141);
        glColor3ub(75, 101, 54);
        glVertex2f(500, 112);
        glColor3ub(92, 52, 20);
        glVertex2f(500, 150);
        glEnd();
    }
    void star() //V040
    {
        glLineWidth(2);
        glBegin(GL_LINES);
        glColor3ub(255, 251, 251); //white-star
        glVertex2f(-0.075, 0);
        glVertex2f(0.075, 0);

        glVertex2f(-0.05, -0.075);
        glVertex2f(0.05, 0.075);

        glVertex2f(0.05, -0.075);
        glVertex2f(-0.05, 0.075);

        glVertex2f(0, -0.1);
        glVertex2f(0, 0.1);

        glEnd();
    }
    void scaledstar() //V040
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(05, 490, 0);
        glScalef(15, 15, 0);
        star();
        glPopMatrix();
    }
    void scaledstarLoop() //V040
    {
        scaledstar();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(5, 0, 0);

        for (int i = 0; i < 3; i++)
        {
            glTranslatef(0, -20, 0);
            scaledstar();
            for (int i = 0; i < 40; i++)
            {
                if (i % 2 == 0)
                {
                    glTranslatef(15, -35, 0);
                    scaledstar();
                }
                else
                {
                    glTranslatef(18, 35, 0);
                    scaledstar();
                }
            }
            glTranslatef(-660, -35, 0);
        }
        glPopMatrix();
    }
    void sky() //village sunset //V038-V039
    {

        glBegin(GL_QUADS); //V038
        if (isDay)
        {

            glColor3ub(247, 191, 190);
            glVertex2f(0, 400);
            glColor3ub(244, 107, 105);
            glVertex2f(500, 400);
            glColor3ub(239, 88, 86);
            glVertex2f(500, 500);
            glColor3ub(247, 65, 59);
            glVertex2f(0, 500);
            glEnd();
        }
        else
        { //V039
            glColor3ub(0, 0, 0);
            glVertex2f(0, 400);

            glVertex2f(500, 400);

            glVertex2f(500, 500);

            glVertex2f(0, 500);
            glEnd();
            scaledstarLoop();
        }
    }
    void sunmoon() //V036-V037
    {
        if (isDay)
        {
            glColor3ub(255, 51, 51); //midday sun effect
                                     //glColor3ub(128, 128, 128);
            circle(150, 400, 20);
        }
        else //V037
        {
            glColor3ub(255, 255, 255);
            circle(140, 440, 25);
        }
    }
    void BoatBodyStick() //boitha
    {
        glBegin(GL_LINES);
        glColor3ub(165, 42, 42); //brown-stick
        glVertex2f(210, 75);
        glVertex2f(220, 10);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3ub(0, 0, 0); //brown-stick
        glVertex2f(218, 20);
        glVertex2f(220, 10);
        glVertex2f(230, 10);
        glEnd();
    }
    void BoatBodyShell() //V051
    {
        glBegin(GL_POLYGON);
        glColor3ub(165, 42, 42); //brown-shell
        glVertex2f(120, 30);
        glVertex2f(200, 30);
        glVertex2f(195, 55);
        glVertex2f(125, 55);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(255, 255, 0); //yellow-shell-stripe-pattern
        glVertex2f(120, 30);
        glVertex2f(200, 30);

        glVertex2f(121, 35);
        glVertex2f(199, 35);

        glVertex2f(122, 40);
        glVertex2f(198, 40);

        glVertex2f(123, 45);
        glVertex2f(197, 45);

        glVertex2f(124, 50);
        glVertex2f(196, 50);

        glVertex2f(125, 55);
        glVertex2f(195, 55);

        glEnd();
    }
    void BoatBody()
    {
        glBegin(GL_QUADS);
        glColor3ub(0, 0, 0); //black-base
        glVertex2f(120, 10);
        glVertex2f(200, 10);
        glVertex2f(200, 30);
        glVertex2f(120, 30);
        glEnd();
        glBegin(GL_TRIANGLES); //black-nose-front
        glVertex2f(120, 10);
        glVertex2f(120, 30);
        glVertex2f(80, 40);
        glEnd();
        glBegin(GL_TRIANGLES); //black-nose-back
        glVertex2f(200, 10);
        glVertex2f(200, 30);
        glVertex2f(240, 40);
        glEnd();

        glBegin(GL_POLYGON); //yellow-inside-shape
        glColor3ub(255, 255, 0);
        glVertex2f(240, 40);
        glVertex2f(80, 40);
        glVertex2f(120, 30);
        glVertex2f(200, 30);
        glEnd();

        glBegin(GL_LINES);
        glColor3b(0, 0, 0); //black_stripe
        /*
        for(int i=0;i<4;i++)
        {
            int x1=205,y1=30,x2=200,y2=40,dx=5,dy=5;
        }*/

        glVertex2f(205, 30);
        glVertex2f(200, 40);

        glVertex2f(210, 30);
        glVertex2f(205, 40);

        glVertex2f(215, 30);
        glVertex2f(210, 40);

        glVertex2f(220, 30);
        glVertex2f(215, 40);

        glVertex2f(225, 30);
        glVertex2f(220, 40);

        //
        glVertex2f(115, 30);
        glVertex2f(120, 40);

        glVertex2f(110, 30);
        glVertex2f(115, 40);

        glVertex2f(105, 30);
        glVertex2f(110, 40);

        glVertex2f(100, 30);
        glVertex2f(105, 40);

        glVertex2f(95, 30);
        glVertex2f(100, 40);

        glEnd();
        BoatBodyShell();
        BoatBodyStick();
    }
    void Boat()
    {
        BoatBody();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(180, -25, 0);

        glRotatef(isDay ? _boatUpDown : 0, 0, 0, 1);
        glTranslatef(-180, 0, 0);
        glTranslatef(10, 110, 0);
        glScalef(0.8, 0.8, 0);
        BoatBody();
        glPopMatrix();
    }

    void House1()//V031
    {

        glColor3ub(149, 160, 125); //body

        //triangle
        glBegin(GL_POLYGON);
        glVertex2f(50, 250);
        glVertex2f(125, 350);
        glVertex2f(200, 250);
        glEnd();

        //hut // roof
        // glColor3ub(76, 92, 85);
        glColor3ub(204, 68, 0); // komlar choto vai
        glBegin(GL_POLYGON);
        glVertex2f(125, 350);
        glVertex2f(263, 370);
        glVertex2f(400, 350);
        glColor3ub(179, 60, 0);
        glVertex2f(500, 250);
        glVertex2f(210, 230);
        glEnd();

        //hut       //western part
        glColor3ub(92, 92, 61);
        glBegin(GL_POLYGON);
        glVertex2f(75, 250);
        glVertex2f(220, 250);
        //glColor3ub(134, 89, 45);
        glColor3ub(166, 197, 103);
        glVertex2f(225, 100);
        glVertex2f(79, 100);
        // glVertex2f(200, 250);
        glEnd();

        //hut   //front door
        glColor3ub(200, 165, 130);
        //glColor3ub(124, 188, 108);
        glBegin(GL_POLYGON);
        glVertex2f(220, 250);
        glColor3ub(157, 147, 92);
        glVertex2f(459, 250);
        glVertex2f(460, 100);
        glVertex2f(225, 100);
        // glVertex2f(200, 250);
        glEnd();
    }
    void h1win11()
    {
        glPushMatrix();
        glTranslatef(-40, -25, 0);
        glBegin(GL_QUADS);
        int j = 0;
        if (isDay)
            glColor3ub(40, 40, 40);
        else
            glColor3ub(255, 255, 102);
        for (int i = 1; i < 3; i++)
        {

            glVertex2f(282 + j, 417);
            glVertex2f(292 + j, 417);
            glVertex2f(292 + j, 407);
            glVertex2f(282 + j, 407);
            j += 12;
        }
        glEnd();
        glPopMatrix();

        glBegin(GL_QUADS);
        glVertex2f(217, 390);
        glVertex2f(224, 391);
        glVertex2f(224, 375);
        glVertex2f(217, 374);
        glEnd();
    }
    void Hut() //V032
    {
        glBegin(GL_QUADS);
        glColor3ub(159, 90, 20);
        glVertex2f(30, 150);
        glVertex2f(90, 150);
        glColor3ub(125, 65, 6);
        glVertex2f(110, 220);
        glVertex2f(50, 220);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3ub(159, 90, 20);
        glVertex2f(130, 154);
        glColor3ub(125, 65, 6);
        glVertex2f(90, 150);
        glColor3ub(228, 193, 113);
        glVertex2f(110, 220);
        glEnd();

        glLineWidth(10);
        glBegin(GL_LINES);
        glColor3ub(125, 65, 6);
        glVertex2f(110, 220);
        glVertex2f(130, 154);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(159, 90, 20);
        glVertex2f(35, 150);
        glVertex2f(90, 150);
        glColor3ub(228, 193, 113);
        glVertex2f(90, 70);
        glVertex2f(35, 80);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(159, 90, 20);
        glVertex2f(130, 154);
        glVertex2f(90, 150);
        glColor3ub(228, 193, 113);
        glVertex2f(90, 70);
        glVertex2f(130, 80);
        glEnd();

        glLineWidth(0.5);
        glBegin(GL_LINES); //BORDER
        glColor3ub(0, 0, 0);
        glVertex2f(90, 150);
        glVertex2f(90, 70);
        //glVertex2f(90, 70);
        //glVertex2f(130, 80);
        glVertex2f(130, 80);
        glVertex2f(130, 154);
        glEnd();

        glBegin(GL_QUADS); //window
        if (isDay)
            glColor3ub(62, 62, 40);
        else
            glColor3ub(243, 237, 65);
        glVertex2f(45, 150);
        glVertex2f(80, 150);
        glVertex2f(80, 95);
        glVertex2f(45, 100);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(253, 151, 49);
        glVertex2f(45, 150);
        glColor3ub(193, 127, 60);
        glVertex2f(80, 150);
        glColor3ub(94, 49, 5);
        glVertex2f(75, 120);
        glColor3ub(112, 69, 25);
        glVertex2f(40, 123);
        glEnd();

        glLineWidth(8); // lower shed
        glBegin(GL_LINES);
        glColor3ub(125, 65, 6);
        glVertex2f(131, 75);
        glVertex2f(90, 66);
        glEnd();

        glBegin(GL_QUADS); //door
        if (isDay)
            glColor3ub(102, 0, 0);
        glVertex2f(125, 154);
        glVertex2f(95, 150);
        glVertex2f(95, 70);
        glVertex2f(126, 78);
        glEnd();

        glLineWidth(0.5);
        glBegin(GL_LINES); //BORDER
        glColor3ub(0, 0, 0);
        glVertex2f(90, 70);
        glVertex2f(130, 80);
        glEnd();

        glLineWidth(5); //bamboo
        glBegin(GL_LINES);
        glColor3ub(151, 105, 31);
        glVertex2f(115, 112);
        glVertex2f(115, 60);
        glEnd();
        // glLineWidth(10);
        glBegin(GL_LINES);
        glColor3ub(151, 105, 31);
        glVertex2f(144, 115);
        glVertex2f(144, 70);
        glEnd();

        glBegin(GL_QUADS); //shed
        glColor3ub(253, 151, 49);
        glVertex2f(125, 154);
        glColor3ub(193, 127, 60);
        glVertex2f(95, 150);
        glColor3ub(94, 49, 5);
        glVertex2f(115, 110);
        glColor3ub(112, 69, 25);
        glVertex2f(145, 115);
        glEnd();

        glLineWidth(13);
        glBegin(GL_QUADS);
        glColor3ub(125, 65, 6);
        glVertex2f(35, 79);
        glVertex2f(90, 69);
        glVertex2f(90, 60);
        glVertex2f(35, 70);
        glEnd();

        //BORDERS

        glLineWidth(0.5);

        glBegin(GL_LINES); //roof
        glColor3ub(0, 0, 0);
        glVertex2f(30, 150);
        glVertex2f(90, 150);
        glVertex2f(90, 150);
        glVertex2f(110, 220);
        glVertex2f(110, 220);
        glVertex2f(50, 220);
        glVertex2f(50, 220);
        glVertex2f(30, 150);
        glEnd();

        glBegin(GL_LINES); //roof
        glColor3ub(0, 0, 0);
        glVertex2f(130, 154);
        glVertex2f(90, 150);
        glVertex2f(90, 150);
        glVertex2f(110, 220);
        glEnd();

        glBegin(GL_LINES); //body
        glColor3ub(0, 0, 0);
        glVertex2f(90, 150);
        glVertex2f(90, 70);
        glVertex2f(90, 70);
        glVertex2f(35, 80);
        glVertex2f(35, 80);
        glVertex2f(35, 150);
        glEnd();

        glBegin(GL_LINES); //shed
        glColor3ub(0, 0, 0);
        glVertex2f(80, 150);
        glVertex2f(75, 120);
        glVertex2f(75, 120);
        glVertex2f(40, 123);
        glVertex2f(40, 123);
        glVertex2f(45, 150);
        glEnd();

        glBegin(GL_LINES); //shed
        glColor3ub(0, 0, 0);
        glVertex2f(95, 150);
        glVertex2f(115, 110);
        glVertex2f(115, 110);
        glVertex2f(145, 115);
        glVertex2f(145, 115);
        glVertex2f(125, 154);
        glEnd();
    }
    void farmhouse() //V033
    {
        glBegin(GL_POLYGON); //front 2nd floor
        glColor3ub(255, 26, 26);
        glVertex2f(360, 440);
        glVertex2f(380, 420);
        glVertex2f(380, 402);
        // glColor3ub(125, 65, 6);
        glVertex2f(342, 404);
        glVertex2f(342, 425);
        glEnd();

        glBegin(GL_QUADS); //side 2nd floor
        glColor3ub(255, 26, 26);
        glVertex2f(380, 422);
        glVertex2f(417, 422);
        // glColor3ub(125, 65, 6);
        glVertex2f(417, 402);
        glVertex2f(380, 402);
        glEnd();

        glBegin(GL_POLYGON); //front 1st floor
        glColor3ub(255, 26, 26);
        glVertex2f(343, 404);
        glVertex2f(380, 402);
        glVertex2f(390, 392);
        // glColor3ub(125, 65, 6);
        glVertex2f(390, 352);
        glVertex2f(333, 354);
        glVertex2f(333, 394);
        glEnd();

        glBegin(GL_QUADS); //side 1st floor
        glColor3ub(255, 26, 26);
        glVertex2f(390, 392);
        glVertex2f(427, 392);
        // glColor3ub(125, 65, 6);
        glVertex2f(427, 352);
        glVertex2f(390, 352);
        glEnd();

        glBegin(GL_QUADS); //top roof
        glColor3ub(153, 0, 0);
        glVertex2f(360, 440);
        glVertex2f(400, 440);
        // glColor3ub(125, 65, 6);
        glVertex2f(420, 420);
        glVertex2f(380, 420);
        glEnd();

        glBegin(GL_QUADS); //lower roof
        glColor3ub(153, 0, 0);
        glVertex2f(380, 402);
        glVertex2f(420, 402);
        glVertex2f(430, 392);
        // glColor3ub(125, 65, 6);
        glVertex2f(390, 392);

        glEnd();

        glBegin(GL_QUADS); // windows
        if (isDay)
        {
            glColor3ub(55, 55, 55);
        }
        else
        {
            glColor3ub(255, 255, 77);
        }
        glVertex2f(345, 424);
        glVertex2f(358, 424);
        glVertex2f(358, 409);
        glVertex2f(345, 409);

        glVertex2f(362, 424);
        glVertex2f(375, 424);
        glVertex2f(375, 409);
        glVertex2f(362, 409);

        int j = 0;
        for (int i = 1; i < 4; i++)
        {

            glVertex2f(382 + j, 417);
            glVertex2f(392 + j, 417);
            glVertex2f(392 + j, 407);
            glVertex2f(382 + j, 407);
            j += 12;
        }

        glVertex2f(392, 382);
        glVertex2f(407, 382);
        glVertex2f(407, 362);
        glVertex2f(392, 362);

        glVertex2f(410, 382);
        glVertex2f(410, 362);
        glVertex2f(425, 362);
        glVertex2f(425, 382);

        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(255, 26, 26);
        glVertex2f(360, 440);
        glVertex2f(380, 420);
        glVertex2f(380, 402);
        glEnd();

        glLineWidth(4);
        glBegin(GL_LINES);
        glColor3ub(153, 0, 0);
        glVertex2f(360, 438);
        glVertex2f(340, 425);
        glEnd();

        glLineWidth(2);
        glBegin(GL_LINE_STRIP);
        glColor3ub(255, 255, 255);
        glVertex2f(344, 399);
        glVertex2f(362, 353);
        glVertex2f(344, 354);
        glVertex2f(362, 398);
        glVertex2f(362, 354);
        glVertex2f(379, 398);
        glVertex2f(362, 398);
        glVertex2f(378, 353);
        glVertex2f(378, 398);
        glVertex2f(362, 398);
        glVertex2f(344, 399);
        glVertex2f(344, 354);
        glEnd();
        glLineWidth(1); //border
        glBegin(GL_LINES);
        glColor3ub(38, 38, 38);
        glVertex2f(380, 420);
        glVertex2f(380, 352);
        glVertex2f(390, 392); //side 1st
        glVertex2f(390, 352);
        glVertex2f(427, 392);
        // glColor3ub(125, 65, 6);
        glVertex2f(427, 352);
        glVertex2f(390, 352);
        glVertex2f(427, 352);
        // front 1st
        glVertex2f(343, 404);
        glVertex2f(380, 402);
        glVertex2f(390, 392);
        // glColor3ub(125, 65, 6);
        glVertex2f(390, 352);
        glVertex2f(390, 352);
        glVertex2f(333, 354);
        glVertex2f(333, 354);
        glVertex2f(333, 394);
        glVertex2f(333, 394);
        glVertex2f(343, 404);
        glVertex2f(342, 404);
        glVertex2f(342, 425);
        glVertex2f(342, 404);
        glVertex2f(342, 354);

        glEnd();
    }
    void Houses() //V033
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(200, 360, 0);
        glScalef(0.15, 0.15, 0);
        House1();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(400, 250, 0);
        glScalef(0.58, 0.4, 0);
        Hut();
        glPopMatrix();
        farmhouse();
        h1win11();
    }
    void wellcircle()
    {
        // glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        // glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
        glLineWidth(7.5);
        glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin
        for (int i = 0; i < 200; i++)
        {
            //glColor3f(1.0, 1.0, 1.0);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 50;
            float x = r * cos(A);
            float y = r / 2 * sin(A);
            glVertex2f(x, y);
        }

        //glVertex2f(0.3f,0.4f);
        //glVertex2f(0.1f,0.4f);

        glEnd();
    }
    void PlaceCircles()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(210, 200, 0);
        glColor3ub(255, 0, 0);
        wellcircle();
        glTranslatef(0, -60, 0);
        glColor3ub(255, 255, 0);
        wellcircle();
        glTranslatef(0, 60, 0);
        glScalef(0.85, 0.85, 0);
        glColor3ub(153, 206, 255); //water
        wellcircle();
        glPopMatrix();
    }
    void Well()
    {
        glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex2f(160, 200);
        glVertex2f(260, 200);
        glVertex2f(260, 140);
        glVertex2f(160, 140);
        glEnd();
        PlaceCircles();

        glLineWidth(2);
        glBegin(GL_LINES); //bamboo
        glColor3ub(98, 52, 18);
        glVertex2f(160 + 4, 200);
        glVertex2f(160 + 4, 200 + 120);

        glVertex2f(260 - 4, 200);
        glVertex2f(260 - 4, 200 + 120);

        glVertex2f(160 - 4, 260);
        glVertex2f(260 + 4, 260);
        glEnd();

        glBegin(GL_QUADS); //Shade
        glColor3ub(98, 52, 18);
        glVertex2f(160 - 20, 200 + 120);

        glVertex2f(260 + 20, 200 + 120);

        glVertex2f(260, 200 + 120 + 70);

        glVertex2f(160, 200 + 120 + 70);
        glEnd();
    }
    void scaledwell() //V501s
    {
        glPushMatrix();
        glTranslatef(170, 250, 0);
        glScalef(0.25, 0.2, 0);
        Well();
        glPopMatrix();
    }

    void field() //V042//V043//V044//V045
    {
        glBegin(GL_POLYGON);
        glColor3ub(51, 150, 51);
        glVertex2f(0, 400);
        //  glColor3ub(236, 217, 14);
        glColor3ub(179, 0, 0);
        glVertex2f(200, 400);
        glColor3ub(136, 159, 40);
        glVertex2f(180, 185);
        glColor3ub(204, 204, 0);
        glVertex2f(0, 185);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(107, 232, 23);
        glVertex2f(195, 340);
        glVertex2f(200, 400);
        glVertex2f(500, 400);
        glVertex2f(500, 300);

        glColor3ub(186, 159, 4);
        glVertex2f(195, 340);
        glVertex2f(500, 300);
        glVertex2f(500, 200);
        glVertex2f(187, 250);

        glColor3ub(0, 125, 12);
        glVertex2f(187, 250);
        glVertex2f(182, 182);
        glVertex2f(500, 182);
        glVertex2f(500, 250);
        glEnd();

        glBegin(GL_LINES); //field divider
        glColor3ub(99, 66, 0);
        for (int i = 0; i < 5; i++)
        {
            glVertex2f(40 + (i * 40), 400);
            glVertex2f(36 + (36 * i), 185);
        }
        glEnd();
        glLineWidth(12);
        glBegin(GL_LINES);
        glColor3ub(0, 125, 12);
        glVertex2f(187, 250);
        glVertex2f(181, 182);
        glVertex2f(500, 182);
        glVertex2f(500, 250);
        glEnd();

        glLineWidth(8);
        glBegin(GL_LINES);
        glColor3ub(99, 66, 0);
        glVertex2f(0, 183);
        glVertex2f(180, 183);
        glLineWidth(6);
        glVertex2f(180, 182);
        glVertex2f(500, 182);
        glEnd();

        /*   glFlush();*/
    }

    void Wave(float waveX, float waveY, float waveA, float waveB) //V050
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef((_angle1 % 20), 0.0f, 0.0f);
        float pi = 3.1416;
        float r = 50;
        for (int waveCol = 0; waveCol < 10; waveCol++)
        {

            for (int waveRow = 0; waveRow < 10; waveRow++)
            {
                glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin
                for (int i = 0; i < 200; i++)
                {
                    glColor3ub(66, 135, 245);

                    float A = (i * pi) / 200;

                    float x = (waveX + (waveA * r * 2 * cos(A)));
                    float y = (waveY + (waveB * r * sin(A)));
                    glVertex2f(x, y);
                }
                glEnd();
                waveX = (waveX + 100) * waveA;
            }
            waveY = 0;
        }
        glPopMatrix();
    }
    void River() //V052s
    {

        float waveX = 00, waveY = 0;  //Position
        float waveA = 1, waveB = 0.5; //Scale

        //for(int waveRow=0;waveRow<5;)
        {
            Wave(waveX, waveY, waveA, waveB);
            Wave(.1, 40, 1, 1);
            // Wave(.1, 20, 1, 1);
            //waveY=waveY+100;
        }
        // glEnd();
    }
    void Corn() //V046
    {
        glBegin(GL_TRIANGLES);
        glColor3f(1, 1, 0);             //yellow//Corn
        glVertex2f(92.5 - 5, 180 + 40); //top-leaf-mid
        glVertex2f(100, 275 + 90 + 40);
        glVertex2f(107.5 + 5, 180 + 40);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0, 1, 0); //green//Corn-stick
        glVertex2f(98, 275 - 80 + 20 + 20);
        glVertex2f(102, 275 - 80 + 20 + 20);
        glVertex2f(102 + 5, 275 - 200 + 20);
        glVertex2f(98 - 5, 275 - 200 + 20);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(210, 105, 30);
        glVertex2f(100, 275 + 80 + 40); //brown-divider
        glVertex2f(100, 180 + 40);

        glVertex2f(92.5, 180 + 40); //brown-left
        glVertex2f(100, 275 + 80 + 40);

        glVertex2f(107.5, 180 + 40); ////brown-right
        glVertex2f(100, 275 + 80 + 40);

        glVertex2f(92.5 + 5, 285 + 40);
        glVertex2f(107.5 - 5, 285 + 40);

        glVertex2f(92.5 + 2, 275 + 40);
        glVertex2f(107.5 - 2, 275 + 40);

        glVertex2f(92.5 + 2, 265 + 40);
        glVertex2f(107.5 - 2, 265 + 40);

        glVertex2f(92.5 + 2, 255 + 40);
        glVertex2f(107.5 - 2, 255 + 40);

        glVertex2f(92.5 + 2, 245 + 40);
        glVertex2f(107.5 - 2, 245 + 40);

        glVertex2f(92.5 + 2, 235 + 40);
        glVertex2f(107.5 - 2, 235 + 40);

        glEnd();

        glColor3f(0, 1, 0);
        glBegin(GL_TRIANGLES);
        glVertex2f(87.5 + 8, 100 + 80 + 40); //Corn-leaf-left
        glVertex2f(75 + 8, 225 + 80 + 40);
        glVertex2f(100 + 8, 100 + 80 + 40);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(112.5 - 8, 100 + 80 + 40); //Corn-leaf-right
        glVertex2f(125 - 8, 225 + 80 + 40);
        glVertex2f(100 - 8, 100 + 80 + 40);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(87.5, 100 + 50); //mid-leaf-left
        glVertex2f(75 - 10, 225 + 50 + 50);
        glVertex2f(100, 100 + 50);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(112.5, 100 + 50); //mid-leaf-right
        glVertex2f(125 + 10, 225 + 50 + 50);
        glVertex2f(100, 100 + 50);
        glEnd();
    }
    void CornLeaf()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glColor3ub(0, 255, 0);
        glScalef(0.2f, 0.1f, 0.0f);
        glBegin(GL_TRIANGLES); //low-leaf-left
        glVertex2f(75 + 10, 100);
        glVertex2f(50 + 10, 175 + 85);
        glVertex2f(100 + 10, 100);
        glEnd();
        glBegin(GL_TRIANGLES); //low-leaf-right
        glVertex2f(125 - 10, 100);
        glVertex2f(150 - 10, 175 + 85);
        glVertex2f(100 - 10, 100);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(87.5, 100); //mid-leaf-left
        glVertex2f(75, 225 + 112);
        glVertex2f(100, 100);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(112.5, 100); //mid-leaf-right
        glVertex2f(125, 225 + 112);
        glVertex2f(100, 100);
        glEnd();

        Corn();
        glPopMatrix();
    }
    void CornLeafloop()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        for (int col = 0; col < 10; col++)
        {

            glTranslatef(-15.0f, 360.0f, 0.0f); //for once
            CornLeaf();
            for (int time = 0; time < 12; time++)
            {
                glTranslatef(15.0f, 0.0f, 0.0f);
                CornLeaf();
                //  glTranslatef(0, -100, 0);
            }
            glTranslatef(-166.0f, -380.0f, 0.0f); //for once
        }
        glPopMatrix();
    }
    void Face() //V058
    {
        glBegin(GL_POLYGON);
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(160, 82, 45); //brown-pitcher
            float pi = 3.1416;
            float A = (2 * pi * i) / 200;
            float r = 25.5;
            float x = 250 + r * cos(A);
            float y = 250 + r * sin(A);
            glVertex2f(x, y);
        }
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(160, 82, 45); //brown-pitcher-neck
        glVertex2f(240, 220);
        glVertex2f(260, 220);
        glVertex2f(260, 240);
        glVertex2f(240, 240);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3ub(0, 0, 0); //black_eyes
        if (!isDay)
        {
            glColor3ub(255, 0, 0); //red_eyes
        }
        glVertex2f(250, 250);
        glVertex2f(240, 245);
        glVertex2f(235, 270);
        glEnd();
        glBegin(GL_TRIANGLES);
        glColor3ub(0, 0, 0); //black_eyes
        if (!isDay)
        {
            glColor3ub(255, 0, 0); //red_eyes
        }
        glVertex2f(250, 250);
        glVertex2f(260, 245);
        glVertex2f(265, 270);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255); //white_mouth

        glVertex2f(240, 238);
        glVertex2f(250, 235);
        glVertex2f(260, 238);
        glEnd();
    }
    void Skeleton()
    {

        glBegin(GL_POLYGON);         // Each set of 4 vertices form a quad
        glColor3f(0.0f, 0.0f, 0.0f); // black-backbone
        glVertex2f(248.0f, 40.0f);   // x, y
        glVertex2f(248.0f, 230.0f);  // x, y
        glVertex2f(252.0f, 230.0f);  // x, y
        glVertex2f(252.0f, 40.0f);   // x, y
        glEnd();
        Face();
        glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 0.0f); // yellow
        glVertex2f(160.0f, 190.0f);  // x, y
        glVertex2f(340.0f, 190.0f);  // x, y
        glVertex2f(340.0f, 170.0f);  // x, y
        glVertex2f(160.0f, 170.0f);  // x, y

        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.0f, 1.0f, 0.0f); // green-color
        glVertex2f(235.0f, 215.0f);  // x, y
        glVertex2f(265.0f, 215.0f);  // x, y
        glVertex2f(265.0f, 200.0f);
        glVertex2f(235.0f, 200.0f); // x, y
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.0f, 1.0f, 1.0f); // cyan-left-sleeves
        glVertex2f(220.0f, 200.0f);  // x, y
        glVertex2f(200.0f, 200.0f);  // x, y
        glVertex2f(200.0f, 160.0f);
        glVertex2f(220.0f, 160.0f); // x, y
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.0f, 1.0f, 1.0f); // cyan-right-sleeves
        glVertex2f(280.0f, 200.0f);  // x, y
        glVertex2f(300.0f, 200.0f);  // x, y
        glVertex2f(300.0f, 160.0f);
        glVertex2f(280.0f, 160.0f); // x, y
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.0f, 1.0f, 1.0f); // cyan
        glVertex2f(285, 200);        // x, y
        glVertex2f(215, 200);        // x, y
        glVertex2f(215, 100);
        glVertex2f(285, 100); // x, y
        glEnd();
        glColor3b(0, 0, 0);
        text(210.0, 140.0, text2);
    }

    void GhostEffect()
    {
        //for (int i = 0; i < 20; i++)
        glTranslatef(ghostmoveX, ghostmoveY, 0);
    }
    void ScareCrow() //V058
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(20, 300, 0);
        glScalef(.25, 0.25, 0);
        if (!isDay) //ghosteffect
        {
            GhostEffect();
        }
        Skeleton();

        glPopMatrix();
    }

    void blades()
    {
        glBegin(GL_POLYGON); //blade
        glColor3ub(255, 255, 255);
        glVertex2f(257, 370);
        glVertex2f(267, 430);
        glVertex2f(284, 490);
        glVertex2f(280, 430);
        glVertex2f(261, 363);
        glEnd();
    }
    void windmill()
    {
        glBegin(GL_QUADS); //body
        glColor3ub(255, 255, 255);
        glVertex2f(250, 50);
        glVertex2f(260, 50);
        glVertex2f(257, 350);
        glVertex2f(253, 350);
        glEnd();

        glPushMatrix();

        glTranslatef(255, 360, 0);
        glRotatef(_angle1, 0.0f, 0.0f, 1.0f);
        glTranslatef(-255, -360, 0);

        blades(); //1st
        glPushMatrix();
        glTranslatef(255, 360, 0);
        glRotatef(120, 0.0f, 0.0f, 1.0f);
        glTranslatef(-255, -360, 0);
        blades(); //2nd
        glPopMatrix();

        glPushMatrix();
        glTranslatef(255, 360, 0);
        glRotatef(240, 0.0f, 0.0f, 1.0f);
        glTranslatef(-255, -360, 0);
        blades(); //3rd blade
        glPopMatrix();

        glPopMatrix();
    }


    void circle1(int xx, int yy, float r)
    {

        glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin
        for (int i = 0; i < 200; i++)
        {
            // glColor3ub(255, 215, 0);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            // float r = 4.0f;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x + xx, y + yy);
        }
        glEnd();
    }
    void scaledmill() //V503s
    {
        glPushMatrix();
        glTranslatef(05, 310, 0);
        glScalef(0.25, 0.25, 0);
        windmill();
        circle1(255, 360, 10);
        glPopMatrix();
    }

    void showvillage(void) //V000
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glLineWidth(5);

        sky();
        sunmoon();
        river();
        road();

        scaledmountain();
        // Grassloop();
        field();
        Tree();
        Houses();
        River();
        Boat();
        CornLeafloop();
        scaledmill();
        ScareCrow();
        scaledwell();
        //CarForward();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0, 80, 0);
        MovingScaledCarForward();
        glPopMatrix();
        glFlush();
    }
};

class Highway
{
    void PointLight(const float x, const float y, const float z, const float amb, const float diff, const float spec)
    {
        glEnable(GL_LIGHTING);
        GLfloat light_ambient[] = { amb, amb, amb, 1.0 };
        GLfloat light_position[] = { -0.9, .9, 0, 0.0 };
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glEnable(GL_LIGHT0); //enable the light after setting the properties
    }
    void Border() // H106
    {
        glBegin(GL_LINES);
        glColor3ub(0, 255, 0);
        glVertex2f(0, 300);
        glVertex2f(500, 300);
        glEnd();
    }
    void Mountain() //H085-088
    {
        glBegin(GL_POLYGON); //H085
        glColor3ub(107, 107, 71);
        glVertex2f(0, 350);
        glVertex2f(80, 450);
        glVertex2f(140, 380);
        glVertex2f(170, 300);
        glVertex2f(0, 300);
        glEnd();

        glBegin(GL_POLYGON); //H086
        glColor3ub(107, 107, 71);
        glVertex2f(85, 430);
        glVertex2f(100, 455);
        glVertex2f(200, 300);
        glVertex2f(170, 300);
        // glVertex2f(0, 300);
        glEnd();

        glBegin(GL_POLYGON); //H087
        glColor3ub(107, 107, 71);
        glVertex2f(160, 360);
        glVertex2f(260, 480);
        glVertex2f(330, 360);
        glVertex2f(380, 300);
        glVertex2f(200, 300);
        glEnd();

        glBegin(GL_POLYGON); //H088
        glColor3ub(107, 107, 71);
        glVertex2f(330, 360);
        glVertex2f(420, 450);
        glVertex2f(500, 370);
        glVertex2f(500, 300);
        glVertex2f(380, 300);
        glEnd();
    }
    void circle()
    {
        // glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        // glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
        glLineWidth(7.5);
        glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(203, 203, 203);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 30;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x, y);
        }

        //glVertex2f(0.3f,0.4f);
        //glVertex2f(0.1f,0.4f);

        glEnd();
    }
    void cloud()
    {
        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
        glTranslatef(20, 95.5, 0);
        circle();

        glTranslatef(15, 2.5, 0);
        circle();

        glTranslatef(20, 5, 0);
        circle();

        glTranslatef(30, 2.5, 0);
        circle();

        glTranslatef(0, -2.5, 0);
        circle();

        glTranslatef(0, -5, 0);
        circle();

        glTranslatef(0, -7.5, 0);
        circle();

        glPopMatrix();

        // glutSwapBuffers();
    }
    void movingCloude() //H505s
    {
        glPushMatrix();
        glTranslatef(60, 400, 0);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(0.5, 0.5, 1);
        cloud();
        glTranslatef(200, 35, 0);
        cloud();
        glTranslatef((_angle1) % 1000, 0, 0);
        glPushMatrix();
        glTranslatef(-100, 0, 0);
        cloud();
        glTranslatef(200, 35, 0);
        cloud();
        glPopMatrix();
        glPopMatrix();

        glPopMatrix();
        // glutSwapBuffers();
    }
    void SmallMountain(int x, int y) //H089-H092
    {
        glBegin(GL_POLYGON);
        glColor3ub(46, 43, 43);
        glVertex2f(0 + x, 370 + y);
        glVertex2f(15 + x, 400 + y);
        glVertex2f(30 + x, 360 + y);
        glVertex2f(0 + x, 350 + y);
        glEnd();
    }

    void outliner() //H107
    {
        glLineWidth(3);
        glBegin(GL_LINES);
        glColor3ub(0, 0, 0);
        glVertex2f(0, 350);
        glVertex2f(80, 450);
        glVertex2f(80, 450);
        glVertex2f(140, 380);
        glVertex2f(140, 380);
        glVertex2f(170, 300);
        glVertex2f(90, 435);
        glVertex2f(100, 455);
        glVertex2f(100, 455);
        glVertex2f(200, 300);
        glVertex2f(260, 480);
        glVertex2f(330, 360);
        glVertex2f(330, 360);
        glVertex2f(380, 300);
        glVertex2f(330, 360);
        glVertex2f(420, 450);
        glVertex2f(420, 450);
        glVertex2f(500, 370);

        glEnd();
    }

    void sun(int xx, int yy, float r)
    {

        glBegin(GL_POLYGON);                                         // Draw a Red 1x1 Square centered at origin
        isDay ? glColor3ub(252, 186, 3) : glColor3ub(244, 244, 244); //midday sun color palatte
        for (int i = 0; i < 200; i++)
        {
            // glColor3ub(255, 215, 0);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            // float r = 4.0f;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x + xx, y + yy);
        }
        glEnd();
    }

    void Plane2() //H104
    {
        glBegin(GL_QUADS); // body
        glColor3ub(255, 255, 255);
        if (!isDay)
            glColor3ub(0, 55, 55);
        glVertex2f(.666f, -.435f);
        glVertex2f(.5f, -.262f);
        glVertex2f(-.6f, -.262f);
        glVertex2f(-.166f, -.435f);
        glEnd();

        glBegin(GL_QUADS); //cockpit
        glColor3ub(0, 0, 0);
        if (!isDay)
            glColor3ub(255, 255, 0);
        glVertex2f(.579f, -.353f);
        glVertex2f(.546f, -.318f);
        glVertex2f(.466f, -.318f);
        glVertex2f(.466f, -.353f);
        glEnd();

        //windows
        glBegin(GL_QUADS);
        glColor3ub(0, 0, 0);
        if (!isDay)
            glColor3ub(255, 255, 0);
        glVertex2f(.308f, -.353f);
        glVertex2f(.308f, -.318f);
        glVertex2f(.278f, -.318f);
        glVertex2f(.278f, -.353f);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(0, 0, 0);
        if (!isDay)
            glColor3ub(255, 255, 0);
        glVertex2f(.258f, -.353f);
        glVertex2f(.258f, -.318f);
        glVertex2f(.218f, -.318f);
        glVertex2f(.218f, -.353f);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(0, 0, 0);
        if (!isDay)
            glColor3ub(255, 255, 0);
        glVertex2f(.188f, -.353f);
        glVertex2f(.188f, -.318f);
        glVertex2f(.158f, -.318f);
        glVertex2f(.158f, -.353f);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(0, 0, 0);
        if (!isDay)
            glColor3ub(255, 255, 0);
        glVertex2f(.128f, -.353f);
        glVertex2f(.128f, -.318f);
        glVertex2f(.098f, -.318f);
        glVertex2f(.098f, -.353f);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(0, 0, 0);
        if (!isDay)
            glColor3ub(255, 255, 0);
        glVertex2f(.078f, -.353f);
        glVertex2f(.078f, -.318f);
        glVertex2f(.048f, -.318f);
        glVertex2f(.048f, -.353f);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(0, 0, 0);
        if (!isDay)
            glColor3ub(255, 255, 0);
        glVertex2f(.018f, -.353f);
        glVertex2f(.018f, -.318f);
        glVertex2f(-.008f, -.318f);
        glVertex2f(-.008f, -.353f);
        glEnd();

        //wings last
        glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex2f(-.464f, -.1f);
        glVertex2f(-.464f, -.262f);
        glVertex2f(-.302f, -.262f);
        glVertex2f(-.398f, -.1f);
        glEnd();

        glBegin(GL_QUADS); //Cross line
        glColor3f(1, 0, 0);
        glVertex2f(-.384f, -.262f);
        glVertex2f(-.464f, -.262f);
        glVertex2f(-.02f, -.435f);
        glVertex2f(.06f, -.435f);
        glEnd();

        //Wings down
        glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex2f(.308f, -.383f);
        glVertex2f(.108f, -.383f);
        glVertex2f(-.278f, -.628f);
        glVertex2f(-.274f, -.628f);
        glEnd();

        //Wings up
        glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex2f(.148f, -.262f);
        glVertex2f(.305f, -.262f);
        glVertex2f(-.108f, -.015f);
        glVertex2f(-.107f, -.01f);
        glEnd();
    }

    void scaledPlane2(float x, float y, float a, float b) //H104
        //void scaledPlane2()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(a, b, 0); //scale:a,b//position:x,y
        //glScalef(0.1,0.1,0);
        glTranslatef(x, y, 0);

        Plane2();
        glPopMatrix();
    }
    void displayPlane2()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef((_planeMove2 / 6) % 800, 0, 0);
        scaledPlane2(1.5, 9.8, 50.1, 50.1); //scale:a,b//position:x,y
        glPopMatrix();
    }

    void sky() //H095
    {
        glBegin(GL_QUADS);
        isDay ? glColor3ub(51, 190, 255) : glColor3ub(7, 11, 52);
        // glColor3ub(7, 11, 52);
        glVertex2f(0, 300);
        glVertex2f(500, 300);
        glVertex2f(500, 500);
        glVertex2f(0, 500);

        glEnd();
    }
    void field() //H099
    {
        glBegin(GL_QUADS); //greeny
        glColor3ub(0, 77, 0);
        glVertex2f(0, 300);
        glColor3ub(255.0, 255.0, 0.0);
        glVertex2f(500, 300);
        glColor3ub(0, 51, 0);
        glVertex2f(500, 200);
        glColor3ub(0, 153, 0);
        glVertex2f(0, 200);
        glEnd();

        glBegin(GL_QUADS); //muddy
        glColor3ub(0, 77, 0);
        glVertex2f(0, 0);
        glColor3ub(103, 146, 125);
        glVertex2f(500, 0);
        glColor3ub(144, 120, 48);
        glVertex2f(500, 80);
        glColor3ub(179, 89, 0);
        glVertex2f(0, 80);

        glEnd();
    }
    void star() //H105
    {
        glLineWidth(2);
        glBegin(GL_LINES);
        glColor3ub(255, 251, 251); //white-star
        glVertex2f(-0.075, 0);
        glVertex2f(0.075, 0);

        glVertex2f(-0.05, -0.075);
        glVertex2f(0.05, 0.075);

        glVertex2f(0.05, -0.075);
        glVertex2f(-0.05, 0.075);

        glVertex2f(0, -0.1);
        glVertex2f(0, 0.1);

        glEnd();
    }
    void scaledstar()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(05, 490, 0);
        glScalef(15, 15, 0);
        star();
        glPopMatrix();
    }
    void scaledstarLoop()
    {
        scaledstar();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(5, 0, 0);

        for (int i = 0; i < 3; i++)
        {
            glTranslatef(0, -20, 0);
            scaledstar();
            for (int i = 0; i < 40; i++)
            {
                if (i % 2 == 0)
                {
                    glTranslatef(15, -35, 0);
                    scaledstar();
                }
                else
                {
                    glTranslatef(18, 35, 0);
                    scaledstar();
                }
            }
            glTranslatef(-660, -35, 0);
        }
        glPopMatrix();
    }
    void Grass() //H098
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glColor3ub(0, 255, 0);
        glScalef(0.2f, 0.1f, 0.0f);
        glBegin(GL_TRIANGLES); //low-leaf-left
        glVertex2f(75, 100);
        glVertex2f(50, 175);
        glVertex2f(100, 100);
        glEnd();
        glBegin(GL_TRIANGLES); //low-leaf-right
        glVertex2f(125, 100);
        glVertex2f(150, 175);
        glVertex2f(100, 100);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(87.5, 100); //mid-leaf-left
        glVertex2f(75, 225);
        glVertex2f(100, 100);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(112.5, 100); //mid-leaf-right
        glVertex2f(125, 225);
        glVertex2f(100, 100);
        glEnd();
        glBegin(GL_TRIANGLES);
        glVertex2f(92.5, 100); //top-leaf-mid
        glVertex2f(100, 275);
        glVertex2f(107.5, 100);
        glEnd();

        glPopMatrix();
    }
    void Road() //H096
    {
        int x = 0, y = 0;
        glColor3ub(15, 15, 10); // Clear the color buffer (background)
        glBegin(GL_POLYGON);    // Draw a Red 1x1 Square centered at origin
        glVertex2f(0, 200);
        glVertex2f(500, 200);
        glVertex2f(500, 80);
        glVertex2f(0, 80);

        glEnd(); //H097
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(x, 140);
        glVertex2f(y + 45, 140);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(x + 90, 140);
        glVertex2f(y + 135, 140);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(x + 180, 140);
        glVertex2f(y + 225, 140);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(x + 270, 140);
        glVertex2f(y + 315, 140);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2f(x + 360, 140);
        glVertex2f(y + 405, 140);
        glEnd();

        glBegin(GL_LINES); //H097
        glColor3ub(255, 255, 255);
        glVertex2f(x + 450, 140);
        glVertex2f(y + 495, 140);
        glEnd();

        glBegin(GL_LINES); //road barrier   //H101
        glColor3ub(96, 97, 101);
        glLineWidth(5);
        glVertex2f(500, 95);
        glVertex2f(0, 95);
        glVertex2f(500, 85);
        glVertex2f(0, 85);
        glVertex2f(500, 75);
        glVertex2f(0, 75);
        glEnd();

        glBegin(GL_LINES); //barrier fench  //H101
        glColor3ub(128, 64, 0);
        glLineWidth(10);
        int j = 0;
        for (int i = 0; i < 20; i++)
        {
            glVertex2f(10 + j, 100);
            glVertex2f(10 + j, 70);
            j += 25;
        }

        glEnd();
    }

    void Grassloop()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        for (int col = 0; col < 6; col++)
        {

            glTranslatef(-10.0f, 0.0f, 0.0f); //for once
            Grass();
            for (int time = 0; time < 32; time++)
            {
                glTranslatef(15.0f, 0.0f, 0.0f);
                Grass();
            }
            glTranslatef(-470.0f, 10.0f, 0.0f); //for once
        }
        glPopMatrix();
    }
    void treeRoot() //H108
    {
        glBegin(GL_QUADS);
        glColor3ub(102, 51, 0);
        // glVertex2f(25,80);
        glVertex2f(30, 200);
        glVertex2f(25, 200);
        glVertex2f(25, 350);
        glVertex2f(30, 350);
        glEnd();
    }

    void treeBody() //H108
    {

        glBegin(GL_QUADS);
        glColor3ub(0, 255, 0);
        glVertex2f(10, 220);
        glVertex2f(27.5, 215);
        glVertex2f(45, 220);
        glVertex2f(27.5, 250);
        glEnd();
    }
    void treeborder() //H108
    {
        glLineWidth(2.5);
        glBegin(GL_LINES);
        glColor3ub(0, 153, 0);
        glVertex2f(10, 220);
        glVertex2f(27.5, 215);
        glVertex2f(27.5, 215);
        glVertex2f(45, 220);
        glVertex2f(45, 220);
        glVertex2f(27.5, 250);
        glVertex2f(27.5, 250);
        glVertex2f(10, 220);
        glEnd();
    }
    void tree() //H108
    {
        treeRoot();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        treeBody();
        treeborder();

        for (int i = 1; i < 7; i++)
        {
            glScalef(0.9, 1, 0);
            glTranslatef(3, 19, 0); // for 0.8 is 6.8
            treeBody();
            treeborder();
            // glTranslatef(-4.8, -5, 0);
        }
        glPopMatrix();

        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2f(27, 363);
        glVertex2f(27, 215);
        glEnd();
    }
    void treeloop() //H108
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(20, 0, 0);
        tree();
        glTranslatef(-20, 0, 0);

        for (int i = 1; i < 8; i++)
        {
            //   glScalef(0.8, 1, 0);
            glTranslatef(80, 0, 0); // for 0.9 is 3.0
            tree();
            glTranslatef(-20, 0, 0);
        }

        glPopMatrix();
    }
    
    void nightEffect()
    {
        glEnable(GL_DEPTH_TEST);
        // glMatrixMode(GL_PROJECTION);
        // glLoadIdentity();
        PointLight(0, 0, 1, .3, 1, 1);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
    }

public:
    void showHighway() //H000
    {
        // glClearColor(1.0, 1.0, 1.0, 1.0);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);
        glLineWidth(5);

        sky();

        sun(175, 440, 20);
        if (!isDay)
        {
            scaledstarLoop();
            // nightEffect(); /* code */
        }
        movingCloude();
        Border();
        SmallMountain(0, 0);    //H089
        SmallMountain(140, 0);  //H090
        SmallMountain(155, -2); //H090
        SmallMountain(310, 05); //H091
        SmallMountain(335, 07); //H092
        //scaledMountain();
        Mountain();
        outliner();
        field();
        Road();

        Grassloop();
        treeloop();
        //CarForward();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0, 20, 0);
        MovingScaledCarForward();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(100, 40, 0);
        MovingScaledTruckReverse();
        glTranslatef(0, 10, 0);
        MovingScaledCarReverse();
        glPopMatrix();
        glPopMatrix();
        displayPlane2();
        glFlush();
        glutSwapBuffers();
    }
};
void show() //H000
{
    glClearColor(0.63f, 0.85f, 0.85f, 0.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(-60, 25, 0);     // Clear the color buffer (background)
    glColor3ub(0, 0, 0);
    char demoText[] = "o Press 'Up Arrow' to nevigate to  Village";
    text(250, 250, demoText);
    char   downText[] ="o  Press 'Down Arrow' to nevigate to Hawor";
    text(250, 250 - 20, downText);

    char leftText[] = "o  Press 'Left Arrow' to nevigate to City";
    text(250, 250 - 40, leftText);
    char rightText[] = "o Press 'Right Arrow' to nevigate to Highway";
    text(250, 250 - 60, rightText);

    char carText[] = "o  Press 'X' to stop and resume all cars";
    text(250, 250 - 100, carText);




    char fullScreen[] = "o  Press 'F' to toggle full screen";
    text(250, 250 - 120, fullScreen);


    char dayNight[] = "o  Press 'd' for day effect and 'n' for night effect";
    text(250, 250 - 140, dayNight);


    char esctxt[] = "o  'ESC' to exit the program";
    text(250, 250 - 160, esctxt);
    glPopMatrix();
    glFlush();
    // Highway obj1;
    // obj1.showHighway();
}
void displayHighway() //H000
{
    Highway obj;
    obj.showHighway();
    //  glutTimerFunc(20, updatePlane2, 0);
}
void redisplayHighway() //H000
{
    //   if (!isDay)
    // {
    //     std::cout << "Night Mode" << std::endl;
    //     /* code */
    //     glutDisplayFunc(displayHighway);
    // }else{
    glutDestroyWindow(1);
    glClearColor(0.63f, 0.85f, 0.85f, 0.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);            // Clear the color buffer (background)
    glutInitWindowSize(1200, 1200);
    glutCreateWindow("Journey By Car Animation"); // Create a window with the given title
    //gluOrtho2D(-500, 1500, -500, 1500);
    gluOrtho2D(0, 500, 0, 500);
    glutFullScreen();
    glutDisplayFunc(displayHighway); // Register display callback handler for window re-paint
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(handleKeypress);
    // }
    // glutPostRedisplay();
}
void displayCity() //C000
{
    CityScape obj;
    obj.CityView();
}
void redisplayCity() //C000
{
    glutDestroyWindow(1);
    glClearColor(0.63f, 0.85f, 0.85f, 0.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);            // Clear the color buffer (background)
    glutInitWindowSize(1200, 1200);
    glutCreateWindow("Journey By Car Animation"); // Create a window with the given title
    gluOrtho2D(0, 500, 0, 500);
    glutFullScreen();
    glutDisplayFunc(displayCity); // Register display callback handler for window re-paint
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(handleKeypress);
}

void displayHaor() //L000
{
    NikliHaor obj;
    obj.output();
}
void redisplayHaor() //L000
{
    glutDestroyWindow(1);
    glClearColor(0.63f, 0.85f, 0.85f, 0.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);            // Clear the color buffer (background)
    glutInitWindowSize(640, 640);
    glutCreateWindow("Journey By Car Animation"); // Create a window with the given title
    gluOrtho2D(0, 500, 0, 500);
    //gluOrtho2D(-1000, 1000, -1000, 1000);
    glutFullScreen();
    glutDisplayFunc(displayHaor); // Register display callback handler for window re-paint
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(handleKeypress);
}
void displayVillage() //V000
{
    Village obj;
    obj.showvillage();
    // Highway obj1;
    //obj1.showHighway();
}
void redisplayVillage() //V000
{
    glutDestroyWindow(1);
    glClearColor(0.63f, 0.85f, 0.85f, 0.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);            // Clear the color buffer (background)
    glutInitWindowSize(640, 640);
    glutCreateWindow("Journey By Car Animation"); // Create a window with the given title
    gluOrtho2D(0, 500, 0, 500);
    glutFullScreen();
    glutDisplayFunc(displayVillage); // Register display callback handler for window re-paint
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(handleKeypress);
}
void SpecialInput(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        //do something here
        redisplayVillage();
        break;
    case GLUT_KEY_DOWN:
        redisplayHaor();
        //glutDisplayFunc(display2);
        break;
    case GLUT_KEY_LEFT:
        redisplayCity();
        break;
    case GLUT_KEY_RIGHT:
        redisplayHighway();

        break;
    }
    glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // Initialize GLUT
    glutInitWindowSize(640, 640);
    glutCreateWindow("Journey By Car Animation"); // Create a window with the given title
    gluOrtho2D(0, 500, 0, 500);
    // gluOrtho2D(-1000, 1000, -1000, 1000);
    glutFullScreen();
    glutDisplayFunc(show);                 // Register display callback handler for window re-paint
    glutTimerFunc(20, update, 0);          //Add a timer
    glutTimerFunc(20, MoveCarForward, 0);  //moves car forward
    glutTimerFunc(20, TireRotate, 0);      //moves tire forward
    glutTimerFunc(20, TruckTireRotate, 0); //Add a timer
    glutTimerFunc(20, MoveTruckReverse, 0);
    glutTimerFunc(20, updatePlane2, 0);
    glutTimerFunc(20, BoatUpDownUpdate, 0);
    glutTimerFunc(20, ghostUpdate, 0);
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(handleKeypress);
    //glLoadIdentity();
    glutMainLoop(); // Enter the event-processing loop
    return 0;
}
