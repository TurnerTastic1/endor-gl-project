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
// Cosine and Sine in degrees
#define Cos(x) (cos((x) * 3.14159265 / 180))
#define Sin(x) (sin((x) * 3.14159265 / 180))

void Speeder::draw(double x, double y, double z)
{
  double bodyLength = 0.5;
  double bodyWidth = 0.2;
  double bodyHeight = 0.17;
  double barrelLength = 2;
  double barrelRadius = 0.03;
  glPushMatrix();
  //  Offset and scale
  glTranslated(x, y, z);

  drawBody(bodyLength, bodyWidth, bodyHeight);

  drawBarrels(barrelRadius, bodyLength, barrelLength, bodyHeight, bodyWidth);

  drawBarrelGaurds(barrelRadius, bodyLength, barrelLength, bodyHeight, bodyWidth);

  drawControls(bodyLength, bodyWidth, bodyHeight);

  drawPedals(bodyLength, bodyWidth, bodyHeight);

  glPopMatrix();
}

void Speeder::drawBody(double bodyLength, double bodyWidth, double bodyHeight)
{
  glPushMatrix();

  // Red
  glColor3f(1, 1, 1);

  // Draw the body
  glBegin(GL_QUADS);
  // Front
  glVertex3f(-bodyLength, 0, bodyWidth);
  glVertex3f(bodyLength, 0, bodyWidth);
  glVertex3f(bodyLength, bodyHeight, bodyWidth);
  glVertex3f(-bodyLength, bodyHeight, bodyWidth);

  // Back
  glVertex3f(-bodyLength, 0, -bodyWidth);
  glVertex3f(bodyLength, 0, -bodyWidth);
  glVertex3f(bodyLength, bodyHeight, -bodyWidth);
  glVertex3f(-bodyLength, bodyHeight, -bodyWidth);

  // // Blue
  // glColor3f(0, 0, 1);

  // Left
  glVertex3f(-bodyLength, 0, -bodyWidth);
  glVertex3f(-bodyLength, 0, bodyWidth);
  glVertex3f(-bodyLength, bodyHeight, bodyWidth);
  glVertex3f(-bodyLength, bodyHeight, -bodyWidth);

  // Right
  glVertex3f(bodyLength, 0, -bodyWidth);
  glVertex3f(bodyLength, 0, bodyWidth);
  glVertex3f(bodyLength, bodyHeight, bodyWidth);
  glVertex3f(bodyLength, bodyHeight, -bodyWidth);

  // // Yellow
  // glColor3f(1, 1, 0);

  // Top
  glVertex3f(-bodyLength, bodyHeight, bodyWidth);
  glVertex3f(bodyLength, bodyHeight, bodyWidth);
  glVertex3f(bodyLength, bodyHeight, -bodyWidth);
  glVertex3f(-bodyLength, bodyHeight, -bodyWidth);

  // Bottom
  glVertex3f(-bodyLength, 0, -bodyWidth);
  glVertex3f(bodyLength, 0, -bodyWidth);
  glVertex3f(bodyLength, 0, bodyWidth);
  glVertex3f(-bodyLength, 0, bodyWidth);

  glEnd();

  glPopMatrix();
}

void Speeder::drawBarrels(double barrelRadius, double barrelStartingPoint, double barrelLength, double bodyHeight, double bodyWidth)
{
  glPushMatrix();
  glRotated(90, 0, 0, 1);

  // Gray
  glColor3f(0.5, 0.5, 0.5);

  // Draw the first barrel
  glBegin(GL_QUAD_STRIP);
  for (int angle = 0; angle <= 360; angle += 15)
  {
    double x1 = barrelRadius * Cos(angle) + bodyHeight / 2;
    double z1 = barrelRadius * Sin(angle) - bodyWidth / 2;

    // Barrel 1
    glVertex3d(x1, barrelStartingPoint, z1);
    glVertex3d(x1, barrelLength, z1);
  }
  glEnd();

  // Draw the second barrel
  glBegin(GL_QUAD_STRIP);
  for (int angle = 0; angle <= 360; angle += 15)
  {
    double x1 = barrelRadius * Cos(angle) + bodyHeight / 2;
    double z1 = barrelRadius * Sin(angle) + bodyWidth / 2;

    // Barrel 2
    glVertex3d(x1, barrelStartingPoint, z1);
    glVertex3d(x1, barrelLength, z1);
  }
  glEnd();

  glPopMatrix();
}

void Speeder::drawBarrelGaurds(double barrelRadius, double barrelStartingPoint, double barrelLength, double bodyHeight, double bodyWidth)
{
  glPushMatrix();
  // White
  glColor3f(1, 1, 1);

  // Draw the barrel gaurds
  double z1Close = bodyWidth / 2;
  double z1Far = bodyWidth;

  // First triangle on Barrel 1
  glBegin(GL_TRIANGLES);
  // Bottom vertex
  glVertex3d(-barrelLength * .85, 0, z1Far);

  glVertex3d(-barrelLength * .85, bodyHeight * 1.2, z1Close);

  glVertex3d(-barrelLength - (barrelRadius * 4), bodyHeight * 1.2, z1Close);
  glEnd();

  // Second triangle on Barrel 1
  glBegin(GL_TRIANGLES);
  // Bottom vertex
  glVertex3d(-barrelLength * .85, 0, -z1Far);

  glVertex3d(-barrelLength * .85, bodyHeight * 1.2, -z1Close);

  glVertex3d(-barrelLength - (barrelRadius * 4), bodyHeight * 1.2, -z1Close);
  glEnd();

  glPopMatrix();
}

void Speeder::drawControls(double bodyLength, double bodyWidth, double bodyHeight)
{
  glPushMatrix();
  int angleIncrement = 15; // Angle increment in degrees
  double controlPanelRadius = bodyWidth;
  double height = bodyHeight;

  // Gray
  glColor3f(0.4, 0.4, 0.4);

  // Draw the control base
  glBegin(GL_QUAD_STRIP);
  for (int angle = 0; angle <= 360; angle += angleIncrement)
  {
    double x1 = controlPanelRadius * Cos(angle) - bodyLength;
    double z1 = controlPanelRadius * Sin(angle);

    // Cylinder side: connect vertices on the bottom and top circles
    glVertex3d(x1 - 0.1, height, z1); // Bottom circle vertex
    glVertex3d(x1, height * 2, z1);   // Top circle vertex
  }
  glEnd();

  // Draw the top cap of the cylinder
  glBegin(GL_TRIANGLE_FAN);
  // Center point of the top circle
  glVertex3d(-bodyLength, height * 2, 0.0);
  for (int angle = 0; angle <= 360; angle += angleIncrement)
  {
    double x1 = controlPanelRadius * Cos(angle) - bodyLength;
    double z1 = controlPanelRadius * Sin(angle);
    glVertex3d(x1, height * 2, z1); // Perimeter vertices of the top circle
  }
  glEnd();

  // Draw the bottom cap of the cylinder
  glBegin(GL_TRIANGLE_FAN);
  // Center point of the top circle
  glVertex3d(-bodyLength, height, 0.0);
  for (int angle = 0; angle <= 360; angle += angleIncrement)
  {
    double x1 = controlPanelRadius * Cos(angle) - bodyLength;
    double z1 = controlPanelRadius * Sin(angle);
    glVertex3d(x1 - 0.1, height, z1); // Perimeter vertices of the top circle
  }
  glEnd();

  // Dark Gray
  glColor3f(0.2, 0.2, 0.2);

  // Draw the control sticks
  double controlStickRadius = 0.03;
  double controlStickStartingHeight = height * 2;
  double controlStickFinalHeight = height * 3;

  glBegin(GL_QUAD_STRIP);
  for (int angle = 0; angle <= 360; angle += angleIncrement)
  {
    double x1 = controlStickRadius * Cos(angle) - bodyLength + 0.05;
    double z1 = controlStickRadius * Sin(angle) + (controlPanelRadius * 0.7);

    glVertex3d(x1 + 0.06, controlStickStartingHeight, z1);
    glVertex3d(x1, controlStickFinalHeight, z1);
  }
  glEnd();

  glBegin(GL_QUAD_STRIP);
  for (int angle = 0; angle <= 360; angle += angleIncrement)
  {
    double x1 = controlStickRadius * Cos(angle) - bodyLength + 0.05;
    double z1 = controlStickRadius * Sin(angle) - (controlPanelRadius * 0.7);

    glVertex3d(x1 + 0.06, controlStickStartingHeight, z1);
    glVertex3d(x1, controlStickFinalHeight, z1);
  }
  glEnd();

  // Draw control panel buttons
  double controlPanelButtonRadius = 0.03;
  glColor3f(1, 1, 0);

  glBegin(GL_TRIANGLE_FAN);
  // Center point of the top circle
  glVertex3d(-bodyLength - 0.1, controlStickStartingHeight + 0.001, 0.0);
  for (int angle = 0; angle <= 360; angle += angleIncrement)
  {
    double x1 = controlPanelButtonRadius * Cos(angle) - bodyLength;
    double z1 = controlPanelButtonRadius * Sin(angle);
    glVertex3d(x1 - 0.1, controlStickStartingHeight + 0.001, z1);
  }
  glEnd();

  glColor3f(1, 0, 0);

  glBegin(GL_TRIANGLE_FAN);
  // Center point of the top circle
  glVertex3d(-bodyLength, controlStickStartingHeight + 0.001, 0.0);
  for (int angle = 0; angle <= 360; angle += angleIncrement)
  {
    double x1 = controlPanelButtonRadius * Cos(angle) - bodyLength;
    double z1 = controlPanelButtonRadius * Sin(angle);
    glVertex3d(x1, controlStickStartingHeight + 0.001, z1);
  }
  glEnd();

  glColor3f(0, 1, 0);

  glBegin(GL_TRIANGLE_FAN);
  // Center point of the top circle
  glVertex3d(-bodyLength + 0.1, controlStickStartingHeight + 0.001, 0.0);
  for (int angle = 0; angle <= 360; angle += angleIncrement)
  {
    double x1 = controlPanelButtonRadius * Cos(angle) - bodyLength;
    double z1 = controlPanelButtonRadius * Sin(angle);
    glVertex3d(x1 + 0.1, controlStickStartingHeight + 0.001, z1);
  }
  glEnd();

  glPopMatrix();
}

void Speeder::drawPedals(double bodyLength, double bodyWidth, double bodyHeight)
{
  glPushMatrix();
  int angleIncrement = 15; // Angle increment in degrees
  double controlPanelRadius = bodyWidth;
  double height = bodyHeight;

  // Gray
  glColor3f(1, 0, 0);

  // Draw the pedal extenders
  double pedalRadius = 0.02;
  double pedalStartingHeight = -height;
  double pedalFinalHeight = 0;

  glBegin(GL_QUAD_STRIP);
  for (int angle = 0; angle <= 360; angle += angleIncrement)
  {
    double x1 = pedalRadius * Cos(angle) - bodyLength + 0.05;
    double z1 = pedalRadius * Sin(angle) + (controlPanelRadius * 0.7);

    glVertex3d(x1 + 0.06, pedalStartingHeight, z1);
    glVertex3d(x1, pedalFinalHeight, z1);
  }
  glEnd();

  glBegin(GL_QUAD_STRIP);
  for (int angle = 0; angle <= 360; angle += angleIncrement)
  {
    double x1 = pedalRadius * Cos(angle) - bodyLength + 0.05;
    double z1 = pedalRadius * Sin(angle) - (controlPanelRadius * 0.7);

    glVertex3d(x1 + 0.06, pedalStartingHeight, z1);
    glVertex3d(x1, pedalFinalHeight, z1);
  }
  glEnd();

  glPopMatrix();

  // Draw pedal platforms
  glPushMatrix();

  glColor3f(0, 1, 0);
  // Draw the pedal platforms
  // Draw the first pedal
  glBegin(GL_QUAD_STRIP);
  // Top
  glVertex3f(-bodyLength - 0.1, pedalFinalHeight, controlPanelRadius * 0.7);
  glVertex3f(-bodyLength - 0.1, pedalFinalHeight, -controlPanelRadius * 0.7);
  glVertex3f(-bodyLength - 0.1, pedalStartingHeight, -controlPanelRadius * 0.7);
  glVertex3f(-bodyLength - 0.1, pedalStartingHeight, controlPanelRadius * 0.7);

  glEnd();

  glPopMatrix();
}
