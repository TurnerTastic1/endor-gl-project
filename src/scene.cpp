#include <cmath>
#include "scene.hpp"
#include "tree.hpp"
#include "speeder.hpp"
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

// Cosine and Sine in degrees
#define Cos(x) (cos((x) * 3.14159265 / 180))
#define Sin(x) (sin((x) * 3.14159265 / 180))

Scene::Scene(double dim, int res, int fov, double asp) : dim(dim), res(res), fov(fov), asp(asp), th(-105), ph(15), showAxes(false), showcaseSpeeder(false), viewMode(0), moveSpeed(0.7), rotSpeed(0.2) {}

/* Globals */
// Objects
Tree tree = Tree();
Speeder speeder = Speeder();

// Variables
double speederZPos = 1;
double speederXPos = 4;

// Camera parameters
double eyeX = 0, eyeY = 2, eyeZ = 0.0;        // Initial position of the camera
double centerX = 0, centerY = 2, centerZ = 0; // Point the camera is looking at
double upX = 0.0, upY = 1.0, upZ = 0.0;       // Up vector

// Player orientation
double angle = 0.0; // Angle in radians

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

void Scene::toggleViewMode()
{
  viewMode = (viewMode + 1) % 3;
}

void Scene::draw()
{
  // Clear the window and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();

  if (viewMode == 0)
  {
    double cameraX = -2 * dim * Sin(th) * Cos(ph);
    double cameraY = +2 * dim * Sin(ph);
    double cameraZ = +2 * dim * Cos(th) * Cos(ph);
    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, Cos(ph), 0);
  }
  else if (viewMode == 1)
  {
    // Calculate the new center position based on the angle
    centerX = eyeX + sin(angle);
    centerZ = eyeZ - cos(angle);

    // Set the camera view
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
  }
  else
  {
    glRotatef(ph, 1, 0, 0);
    glRotatef(th, 0, 1, 0);
  }

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

  Util::ErrCheck("display");

  //  Flush and swap buffer
  glFlush();
  glutSwapBuffers();
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
  Util::Print("X");
  glRasterPos3d(0.0, len, 0.0);
  Util::Print("Y");
  glRasterPos3d(0.0, 0.0, len);
  Util::Print("Z");
}

void Scene::drawInfo()
{
  //  White
  glColor3f(1, 1, 1);

  glWindowPos2i(5, 5);
  Util::Print("Angle=%d,%d", th, ph);

  glWindowPos2i(5, 25);
  Util::Print("Press 1 to toggle speeder showcase mode");

  glWindowPos2i(5, 45);
  Util::Print("View Mode (m): %s",
              viewMode == 0 ? "Perspective" : viewMode == 1 ? "First person"
                                                            : "Orthographic");
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

void Scene::key(unsigned char ch, int x, int y)
{
  //  Exit on ESC
  if (ch == 27)
    exit(0);
  //  Reset view angle
  else if (ch == 'r' || ch == 'R')
    resetAngles();
  //  Toggle axes
  else if (ch == 'a' || ch == 'A')
    toggleAxes();
  else if (ch == 'm' || ch == 'M')
    toggleViewMode();
  else if (ch == '1')
    toggleShowcaseSpeeder();

  if (viewMode == 1)
  {
    switch (ch)
    {
    case 'w':
      centerY += moveSpeed;
      eyeY += moveSpeed;
      break;
    case 's':
      centerY -= moveSpeed;
      eyeY -= moveSpeed;
      break;
    }
  }

  project();

  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
}

void Scene::special(int key, int x, int y)
{
  if (viewMode == 1)
  {
    switch (key)
    {
    case GLUT_KEY_UP:
      eyeX += moveSpeed * sin(angle);
      eyeZ -= moveSpeed * cos(angle);
      break;
    case GLUT_KEY_DOWN:
      eyeX -= moveSpeed * sin(angle);
      eyeZ += moveSpeed * cos(angle);
      break;
    case GLUT_KEY_LEFT:
      angle -= rotSpeed;
      break;
    case GLUT_KEY_RIGHT:
      angle += rotSpeed;
      break;
    }

    // Calculate the new center position based on the angle
    centerX = eyeX + sin(angle);
    centerZ = eyeZ - cos(angle);
  }
  else
  {
    switch (key)
    {
    case GLUT_KEY_UP:
      adjustAngles(0, 5);
      break;
    case GLUT_KEY_DOWN:
      adjustAngles(0, -5);
      break;
    case GLUT_KEY_LEFT:
      adjustAngles(5, 0);
      break;
    case GLUT_KEY_RIGHT:
      adjustAngles(-5, 0);
      break;
    }
  }

  project();

  //  Tell GLUT it is necessary to redisplay the scene
  glutPostRedisplay();
}

void Scene::reshape(int width, int height)
{
  //  Ratio of the width to the height of the window
  asp = (height > 0) ? (double)width / height : 1;
  //  Set the viewport to the entire window
  glViewport(0, 0, res * width, res * height);
  //  Set projection
  project();
}

void Scene::project()
{
  //  Tell OpenGL we want to manipulate the projection matrix
  glMatrixMode(GL_PROJECTION);
  //  Undo previous transformations
  glLoadIdentity();
  //  Perspective transformation
  if (viewMode == 0 || viewMode == 1)
    gluPerspective(fov, asp, dim / 4, 4 * dim);
  //  Orthogonal projection
  else
    glOrtho(-asp * dim, +asp * dim, -dim, +dim, -dim, +dim);
  //  Switch to manipulating the model matrix
  glMatrixMode(GL_MODELVIEW);
  //  Undo previous transformations
  glLoadIdentity();
}