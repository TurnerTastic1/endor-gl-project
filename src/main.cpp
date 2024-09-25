#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "scene.hpp"
#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
// Tell Xcode IDE to not gripe about OpenGL deprecation
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif
//  Default resolution
//  For Retina displays compile with -DRES=2
#ifndef RES
#define RES 1
#endif

// Globals
const int DIM = 10;
Scene scene = Scene(DIM);

/*
 *  Check for OpenGL errors
 */
void ErrCheck(const char *where)
{
  int err = glGetError();
  if (err)
    fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), where);
}

/*
 *  Print message to stderr and exit
 */
void Fatal(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  exit(1);
}

void display()
{
  scene.draw();

  ErrCheck("display");
  glFlush();
  glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key, int x, int y)
{
  //  Right arrow key - increase angle by 5 degrees
  if (key == GLUT_KEY_RIGHT)
    scene.adjustAngles(5, 0);
  //  Left arrow key - decrease angle by 5 degrees
  else if (key == GLUT_KEY_LEFT)
    scene.adjustAngles(-5, 0);
  //  Up arrow key - increase elevation by 5 degrees
  else if (key == GLUT_KEY_UP)
    scene.adjustAngles(0, 5);
  //  Down arrow key - decrease elevation by 5 degrees
  else if (key == GLUT_KEY_DOWN)
    scene.adjustAngles(0, -5);
  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch, int x, int y)
{
  //  Exit on ESC
  if (ch == 27)
    exit(0);
  //  Reset view angle
  else if (ch == 'r' || ch == 'R')
    scene.resetAngles();
  //  Toggle axes
  else if (ch == 'a' || ch == 'A')
    scene.toggleAxes();
  else if (ch == '1')
    scene.toggleShowcaseSpeeder();

  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width, int height)
{
  //  Set the viewport to the entire window
  glViewport(0, 0, RES * width, RES * height);
  //  Tell OpenGL we want to manipulate the projection matrix
  glMatrixMode(GL_PROJECTION);
  //  Undo previous transformations
  glLoadIdentity();
  //  Orthogonal projection
  const double dim = DIM;
  double asp = (height > 0) ? (double)width / height : 1;
  glOrtho(-asp * dim, +asp * dim, -dim, +dim, -dim, +dim);
  //  Switch to manipulating the model matrix
  glMatrixMode(GL_MODELVIEW);
  //  Undo previous transformations
  glLoadIdentity();
}

void idle()
{
  scene.idle();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc, char *argv[])
{
  //  Initialize GLUT and process user parameters
  glutInit(&argc, argv);
  //  Request double buffered, true color window with Z buffering at 600x600
  glutInitWindowSize(800, 800);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  //  Create the window
  glutCreateWindow("HW3 Turner Naef");
#ifdef USEGLEW
  //  Initialize GLEW
  if (glewInit() != GLEW_OK)
    Fatal("Error initializing GLEW\n");
#endif
  //  Tell GLUT to call "display" when the scene should be drawn
  glutDisplayFunc(display);
  //  Tell GLUT to call "reshape" when the window is resized
  glutReshapeFunc(reshape);
  //  Tell GLUT to call "special" when an arrow key is pressed
  glutSpecialFunc(special);
  //  Tell GLUT to call "key" when a key is pressed
  glutKeyboardFunc(key);
  //  Pass control to GLUT so it can interact with the user
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
