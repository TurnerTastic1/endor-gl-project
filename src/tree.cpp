#include "tree.hpp"

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
// Cosine and Sine in degrees
#define Cos(x) (cos((x) * 3.14159265 / 180))
#define Sin(x) (sin((x) * 3.14159265 / 180))

/*
 *  Draw vertex in polar coordinates
 */
void Vertex(double th, double ph)
{
  glColor3f(Cos(th) * Cos(th), Sin(ph) * Sin(ph), Sin(th) * Sin(th));
  glVertex3d(Sin(th) * Cos(ph), Sin(ph), Cos(th) * Cos(ph));
}

void Tree::draw(double x, double y, double z, double radius, double height)
{
  glPushMatrix();
  //  Offset and scale
  glTranslated(x, y, z);
  // glScaled(radius, radius, radius);

  drawTrunk(radius, height);
  drawLeaves(radius, height);

  glPopMatrix();
}

void Tree::drawTrunk(double radius, double height)
{
  glPushMatrix();
  int angleIncrement = 15; // Angle increment in degrees

  // Brown
  glColor3f(0.54, 0.27, 0.3);

  // Draw the cylinder (trunk)
  glBegin(GL_QUAD_STRIP);
  for (int angle = 0; angle <= 360; angle += angleIncrement)
  {
    double x1 = radius * Cos(angle);
    double z1 = radius * Sin(angle);

    // Cylinder side: connect vertices on the bottom and top circles
    glVertex3d(x1, 0, z1);      // Bottom circle vertex
    glVertex3d(x1, height, z1); // Top circle vertex
  }
  glEnd();

  glPopMatrix();
}

void Tree::drawLeaves(double radius, double height)
{
  glPushMatrix();
  //  Offset and scale
  glTranslated(0, height, 0);
  // glScaled(radius, radius, radius);

  // Leaves color
  glColor3f(0.3, 0.7, 0.5);

  glBegin(GL_QUADS);

  double leafWidth = radius * 3;
  double leafHeight = height * .7;

  // Front face
  glVertex3f(-leafWidth, 0.0, leafWidth);
  glVertex3f(leafWidth, 0.0, leafWidth);
  glVertex3f(leafWidth, leafHeight, leafWidth);
  glVertex3f(-leafWidth, leafHeight, leafWidth);

  // Back face
  glVertex3f(leafWidth, 0.0, -leafWidth);
  glVertex3f(-leafWidth, 0.0, -leafWidth);
  glVertex3f(-leafWidth, leafHeight, -leafWidth);
  glVertex3f(leafWidth, leafHeight, -leafWidth);

  // Right face
  glVertex3f(leafWidth, 0.0, leafWidth);
  glVertex3f(leafWidth, 0.0, -leafWidth);
  glVertex3f(leafWidth, leafHeight, -leafWidth);
  glVertex3f(leafWidth, leafHeight, leafWidth);

  // Left face
  glVertex3f(-leafWidth, 0.0, -leafWidth);
  glVertex3f(-leafWidth, 0.0, leafWidth);
  glVertex3f(-leafWidth, leafHeight, leafWidth);
  glVertex3f(-leafWidth, leafHeight, -leafWidth);

  // Top face
  glVertex3f(-leafWidth, leafHeight, leafWidth);
  glVertex3f(leafWidth, leafHeight, leafWidth);
  glVertex3f(leafWidth, leafHeight, -leafWidth);
  glVertex3f(-leafWidth, leafHeight, -leafWidth);

  // Bottom face
  glVertex3f(-leafWidth, 0.0, -leafWidth);
  glVertex3f(leafWidth, 0.0, -leafWidth);
  glVertex3f(leafWidth, 0.0, leafWidth);
  glVertex3f(-leafWidth, 0.0, leafWidth);

  glEnd();

  glPopMatrix();
}
