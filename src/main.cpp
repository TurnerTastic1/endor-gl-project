#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "scene.hpp"
#include "util.hpp"
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
Scene scene = Scene(DIM, RES);

void display()
{
  scene.draw();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key, int x, int y)
{
  scene.special(key, x, y);
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch, int x, int y)
{
  scene.key(ch, x, y);
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width, int height)
{
  scene.reshape(width, height);
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
    Util::Fatal("Error initializing GLEW\n");
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
