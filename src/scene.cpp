#include "scene.hpp"
#include "tree.hpp"
#include "speeder.hpp"

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

#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <cmath>
// Cosine and Sine in degrees
#define Cos(x) (cos((x) * 3.14159265 / 180))
#define Sin(x) (sin((x) * 3.14159265 / 180))

Scene::Scene(double dim_) : th(-105), ph(15), dim(dim_), showAxes(false), showcaseSpeeder(false) {}

/* Globals */
// Objects
Tree tree = Tree();
Speeder speeder = Speeder();

// Variables
double speederZPos = 1;
double speederXPos = 4;

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192 //  Maximum length of text string
void Print(const char *format, ...)
{
  char buf[LEN];
  char *ch = buf;
  va_list args;
  //  Turn the parameters into a character string
  va_start(args, format);
  vsnprintf(buf, LEN, format, args);
  va_end(args);
  //  Display the characters one at a time at the current raster position
  while (*ch)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch++);
}

void Scene::idle()
{
  if (showcaseSpeeder)
  {
    return;
  }
  double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
  speederZPos = fmod(25 * t, 360);

  if (speederXPos <= -4)
    speederXPos = 4;
  else
    speederXPos = speederXPos - 0.01;

  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
}

void Scene::toggleShowcaseSpeeder()
{
  showcaseSpeeder = !showcaseSpeeder;
  resetAngles();
}

void Scene::draw()
{
  // Clear the window and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  glRotatef(ph, 1, 0, 0);
  glRotatef(th, 0, 1, 0);

  if (showcaseSpeeder)
  {
    glScaled(4, 4, 4);
    speeder.draw(0, 0, 0);
  }
  else
  {
    // Draw scene
    tree.draw(3, 0, 4.5, 0.5, 1.5);

    // Rotating trees
    glPushMatrix();

    glRotated(30, 0, 1, 0);
    tree.draw(5.5, 0, 7.5, 0.3, 1.2);
    tree.draw(-2, 0, -6, 0.5, 2.4);

    glPopMatrix();

    tree.draw(-5.5, 0, 5, 0.5, 1.5);
    tree.draw(-1, 0, 6, 1, 3);

    // speeder.draw(1.7 * Cos(speederPos) * 2, .5, 1.7 * Sin(2 * speederPos) * 2);
    speeder.draw(speederXPos, .5, 1.7 * Sin(speederZPos) * 2);
    speeder.draw(speederXPos + 3.5, .5, 2 * Sin(speederZPos) * 2);

    // Draw enviroment
    drawEnviroment();
  }

  // Draw axes if enabled
  drawAxes();
  // Draw screen info
  drawInfo();
}

void Scene::drawEnviroment()
{
  // Draw ground
  glBegin(GL_QUADS);

  // Draw the path
  glColor3f(0.4, 0.27, 0.2);
  glVertex3d(-dim, -0.01, -4);
  glVertex3d(-dim, -0.01, 4);
  glVertex3d(dim, -0.01, 4);
  glVertex3d(dim, -0.01, -4);

  // Draw the grass
  glColor3f(0.2, 0.5, 0.4);
  glVertex3d(-dim, -0.01, -dim);
  glVertex3d(-dim, -0.01, -4);
  glVertex3d(dim, -0.01, -4);
  glVertex3d(dim, -0.01, -dim);

  glVertex3d(-dim, -0.01, dim);
  glVertex3d(-dim, -0.01, 4);
  glVertex3d(dim, -0.01, 4);
  glVertex3d(dim, -0.01, dim);

  glEnd();
}

void Scene::drawAxes()
{
  if (!showAxes)
    return;
  const double len = showcaseSpeeder ? dim * 0.2 : dim * 0.9; // Length of axes

  //  White
  glColor3f(1, 1, 1);

  glBegin(GL_LINES);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(len, 0.0, 0.0);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, len, 0.0);
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 0.0, len);
  glEnd();

  // Label axes
  glRasterPos3d(len, 0.0, 0.0);
  Print("X");
  glRasterPos3d(0.0, len, 0.0);
  Print("Y");
  glRasterPos3d(0.0, 0.0, len);
  Print("Z");
}

void Scene::drawInfo()
{
  //  White
  glColor3f(1, 1, 1);

  glWindowPos2i(5, 5);
  Print("Angle=%d,%d", th, ph);

  glWindowPos2i(5, 25);
  Print("Press 1 to toggle speeder showcase mode");
}

void Scene::toggleAxes()
{
  showAxes = !showAxes;
}

void Scene::resetAngles()
{
  th = -105;
  ph = 15;
}

void Scene::adjustAngles(int t, int p)
{
  th = (th + t) % 360;
  ph = (ph + p) % 360;
}
