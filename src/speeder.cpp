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

Speeder::Speeder(float shiny) : shiny(shiny) {}

void Speeder::draw(double x, double y, double z)
{
  double bodyLength = 0.4;
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
  //  Set specular color to white
  float white[] = {1, 1, 1, 1};
  float black[] = {0, 0, 0, 1};
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

  glPushMatrix();

  // White
  glColor3f(1, 1, 1);

  // Draw the body
  glBegin(GL_QUADS);
  // Front
  glNormal3f(0, 0, 1);
  glVertex3f(-bodyLength, 0, bodyWidth);
  glVertex3f(bodyLength, 0, bodyWidth);
  glVertex3f(bodyLength, bodyHeight, bodyWidth);
  glVertex3f(-bodyLength, bodyHeight, bodyWidth);

  // Back
  glNormal3f(0, 0, -1);
  glVertex3f(-bodyLength, 0, -bodyWidth);
  glVertex3f(bodyLength, 0, -bodyWidth);
  glVertex3f(bodyLength, bodyHeight, -bodyWidth);
  glVertex3f(-bodyLength, bodyHeight, -bodyWidth);

  // Left
  glNormal3f(-1, 0, 0);
  glVertex3f(-bodyLength, 0, -bodyWidth);
  glVertex3f(-bodyLength, 0, bodyWidth);
  glVertex3f(-bodyLength, bodyHeight, bodyWidth);
  glVertex3f(-bodyLength, bodyHeight, -bodyWidth);

  // Right
  glNormal3f(1, 0, 0);
  glVertex3f(bodyLength, 0, -bodyWidth);
  glVertex3f(bodyLength, 0, bodyWidth);
  glVertex3f(bodyLength, bodyHeight, bodyWidth);
  glVertex3f(bodyLength, bodyHeight, -bodyWidth);

  // Top
  glNormal3f(0, 1, 0);
  glVertex3f(-bodyLength, bodyHeight, bodyWidth);
  glVertex3f(bodyLength, bodyHeight, bodyWidth);
  glVertex3f(bodyLength, bodyHeight, -bodyWidth);
  glVertex3f(-bodyLength, bodyHeight, -bodyWidth);

  // Bottom
  glNormal3f(0, -1, 0);
  glVertex3f(-bodyLength, 0, -bodyWidth);
  glVertex3f(bodyLength, 0, -bodyWidth);
  glVertex3f(bodyLength, 0, bodyWidth);
  glVertex3f(-bodyLength, 0, bodyWidth);

  glEnd();

  // Gray
  glColor3f(0.4, 0.4, 0.4);

  // Draw the back seat
  glBegin(GL_QUADS);

  // Top
  glNormal3f(-1, 0, 0);
  glVertex3f(-bodyLength * 0.1, bodyHeight, bodyWidth);
  glVertex3f(bodyLength, bodyHeight * 2.5, bodyWidth);
  glVertex3f(bodyLength, bodyHeight * 2.5, -bodyWidth);
  glVertex3f(-bodyLength * 0.1, bodyHeight, -bodyWidth);

  glColor3f(0.4, 0.4, 0.4);
  // Back
  glNormal3f(1, 0, 0);
  glVertex3f(bodyLength, bodyHeight, bodyWidth);
  glVertex3f(bodyLength, bodyHeight * 2.5, bodyWidth);
  glVertex3f(bodyLength, bodyHeight * 2.5, -bodyWidth);
  glVertex3f(bodyLength, bodyHeight, -bodyWidth);

  glEnd();

  glBegin(GL_TRIANGLES);

  glNormal3f(0, 0, 1);
  // Bottom vertex
  glVertex3d(-bodyLength * 0.1, bodyHeight, bodyWidth);

  // Top vertex
  glVertex3d(bodyLength, bodyHeight * 2.5, bodyWidth);

  // Right vertex
  glVertex3d(bodyLength, bodyHeight, bodyWidth);

  glNormal3f(0, 0, -1);
  // Bottom vertex
  glVertex3d(-bodyLength * 0.1, bodyHeight, -bodyWidth);

  // Top vertex
  glVertex3d(bodyLength, bodyHeight * 2.5, -bodyWidth);

  // Right vertex
  glVertex3d(bodyLength, bodyHeight, -bodyWidth);

  glEnd();

  // Draw side panels supports
  glBegin(GL_QUADS);

  // Bottom first support
  glNormal3f(0, 1, 0);
  glVertex3f(bodyLength * 0.2, 0, bodyWidth);
  glVertex3f(bodyLength * 0.9, 0, bodyWidth);
  glVertex3f(bodyLength * 0.9, 0, bodyWidth + 0.08);
  glVertex3f(bodyLength * 0.2, 0, bodyWidth + 0.08);

  // Top first support
  glNormal3f(0, 1, 0);
  glVertex3f(bodyLength * 0.5, bodyHeight, bodyWidth);
  glVertex3f(bodyLength * 0.8, bodyHeight, bodyWidth);
  glVertex3f(bodyLength * 0.8, bodyHeight, bodyWidth + 0.08);
  glVertex3f(bodyLength * 0.5, bodyHeight, bodyWidth + 0.08);

  // Bottom second support
  glNormal3f(0, 1, 0);
  glVertex3f(bodyLength * 0.2, 0, -bodyWidth);
  glVertex3f(bodyLength * 0.9, 0, -bodyWidth);
  glVertex3f(bodyLength * 0.9, 0, -bodyWidth - 0.08);
  glVertex3f(bodyLength * 0.2, 0, -bodyWidth - 0.08);

  // Top second support
  glNormal3f(0, 1, 0);
  glVertex3f(bodyLength * 0.5, bodyHeight, -bodyWidth);
  glVertex3f(bodyLength * 0.8, bodyHeight, -bodyWidth);
  glVertex3f(bodyLength * 0.8, bodyHeight, -bodyWidth - 0.08);
  glVertex3f(bodyLength * 0.5, bodyHeight, -bodyWidth - 0.08);

  glEnd();

  // Panels for the back seat
  glColor3f(.8, .8, .8);

  glBegin(GL_TRIANGLES);
  // First triangle for panel 1

  glNormal3f(0, 0, 1);
  // Bottom vertex
  glVertex3d(-bodyLength * 0.1, -bodyHeight * 0.5, bodyWidth + 0.081);
  // Top vertex
  glVertex3d(bodyLength * 0.75, bodyHeight * 2.2, bodyWidth + 0.081);
  // Right vertex
  glVertex3d(bodyLength, -bodyHeight * 0.5, bodyWidth + 0.081);

  // Second triangle for panel 2

  glNormal3f(0, 0, -1);

  // Bottom vertex
  glVertex3d(-bodyLength * 0.1, -bodyHeight * 0.5, -bodyWidth - 0.081);
  // Top vertex
  glVertex3d(bodyLength * 0.75, bodyHeight * 2.2, -bodyWidth - 0.081);
  // Right vertex
  glVertex3d(bodyLength, -bodyHeight * 0.5, -bodyWidth - 0.081);

  glEnd();

  glPopMatrix();
}

void Speeder::drawBarrels(double barrelRadius, double barrelStartingPoint, double barrelLength, double bodyHeight, double bodyWidth)
{
  //  Set specular color to white
  float white[] = {1, 1, 1, 1};
  float black[] = {0, 0, 0, 1};
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

  glPushMatrix();
  glRotated(90, 0, 0, 1);

  double barrelTipLength = barrelLength * 1.1;

  // Draw the first barrel
  glBegin(GL_QUAD_STRIP);
  glColor3f(0.5, 0.5, 0.5);
  for (int angle = 0; angle <= 360; angle += 15)
  {
    double x1 = barrelRadius * Cos(angle) + bodyHeight / 2;
    double z1 = barrelRadius * Sin(angle) - bodyWidth / 2;

    // Compute the normal vector (normalized)
    double nx = Cos(angle);
    double ny = 0;
    double nz = Sin(angle);

    glNormal3f(nx, ny, nz);

    // Barrel 1
    glVertex3d(x1, barrelStartingPoint, z1);
    glVertex3d(x1, barrelLength, z1);
  }

  // Draw the first barrel tip
  glColor3f(0.3, 0.3, 0.3);
  for (int angle = 0; angle <= 360; angle += 15)
  {
    double x1 = barrelRadius * Cos(angle) + bodyHeight / 2;
    double z1 = barrelRadius * Sin(angle) - bodyWidth / 2;

    // Compute the normal vector (normalized)
    double nx = Cos(angle);
    double ny = 0;
    double nz = Sin(angle);

    glNormal3f(nx, ny, nz);

    // Barrel 1
    glVertex3d(x1, barrelLength, z1);
    glVertex3d(x1, barrelTipLength, z1);
  }
  glEnd();

  // Draw the second barrel
  glBegin(GL_QUAD_STRIP);
  glColor3f(0.5, 0.5, 0.5);
  for (int angle = 0; angle <= 360; angle += 15)
  {
    double x1 = barrelRadius * Cos(angle) + bodyHeight / 2;
    double z1 = barrelRadius * Sin(angle) + bodyWidth / 2;

    // Compute the normal vector (normalized)
    double nx = Cos(angle);
    double ny = 0;
    double nz = Sin(angle);

    glNormal3f(nx, ny, nz);

    // Barrel 2
    glVertex3d(x1, barrelStartingPoint, z1);
    glVertex3d(x1, barrelLength, z1);
  }

  // Draw the second barrel tip
  glColor3f(0.3, 0.3, 0.3);
  for (int angle = 0; angle <= 360; angle += 15)
  {
    double x1 = barrelRadius * Cos(angle) + bodyHeight / 2;
    double z1 = barrelRadius * Sin(angle) + bodyWidth / 2;

    // Compute the normal vector (normalized)
    double nx = Cos(angle);
    double ny = 0;
    double nz = Sin(angle);

    glNormal3f(nx, ny, nz);

    // Barrel 1
    glVertex3d(x1, barrelLength, z1);
    glVertex3d(x1, barrelTipLength, z1);
  }
  glEnd();

  // Draw the caps of the barrels
  glColor3f(0.7, 0, 0.3);
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0, 1, 0);
  glVertex3d(bodyHeight / 2, barrelTipLength, bodyWidth / 2);
  for (int angle = 0; angle <= 360; angle += 15)
  {
    double x1 = barrelRadius * Cos(angle) + bodyHeight / 2;
    double z1 = barrelRadius * Sin(angle) + bodyWidth / 2;
    glVertex3d(x1, barrelTipLength, z1);
  }

  glEnd();

  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0, 1, 0);
  glVertex3d(bodyHeight / 2, barrelTipLength, -bodyWidth / 2);
  for (int angle = 0; angle <= 360; angle += 15)
  {
    double x1 = barrelRadius * Cos(angle) + bodyHeight / 2;
    double z1 = barrelRadius * Sin(angle) - bodyWidth / 2;
    glVertex3d(x1, barrelTipLength, z1);
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

  glNormal3f(0, 0, 1);
  // Bottom vertex
  glVertex3d(-barrelLength * .85, 0, z1Far);

  glVertex3d(-barrelLength * .85, bodyHeight * 1.2, z1Close);

  glVertex3d(-barrelLength - (barrelRadius * 4), bodyHeight * 1.2, z1Close);
  glEnd();

  // Second triangle on Barrel 1
  glBegin(GL_TRIANGLES);

  glNormal3f(0, 0, -1);
  // Bottom vertex
  glVertex3d(-barrelLength * .85, 0, -z1Far);

  glVertex3d(-barrelLength * .85, bodyHeight * 1.2, -z1Close);

  glVertex3d(-barrelLength - (barrelRadius * 4), bodyHeight * 1.2, -z1Close);
  glEnd();

  glPopMatrix();
}

void Speeder::drawControls(double bodyLength, double bodyWidth, double bodyHeight)
{
  //  Set specular color to white
  float white[] = {1, 1, 1, 1};
  float black[] = {0, 0, 0, 1};
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);

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

    // Compute the normal vector (normalized)
    double nx = Cos(angle);
    double ny = 0;
    double nz = Sin(angle);

    glNormal3f(nx, ny, nz);

    // Cylinder side: connect vertices on the bottom and top circles
    glVertex3d(x1 - 0.1, height, z1); // Bottom circle vertex
    glVertex3d(x1, height * 2, z1);   // Top circle vertex
  }
  glEnd();

  // Draw the top cap of the cylinder
  glBegin(GL_TRIANGLE_FAN);
  // Center point of the top circle
  glNormal3f(0, 1, 0);
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

    // Compute the normal vector (normalized)
    double nx = Cos(angle);
    double ny = 0;
    double nz = Sin(angle);

    glNormal3f(nx, ny, nz);

    glVertex3d(x1 + 0.06, controlStickStartingHeight, z1);
    glVertex3d(x1, controlStickFinalHeight, z1);
  }
  glEnd();

  glBegin(GL_QUAD_STRIP);
  for (int angle = 0; angle <= 360; angle += angleIncrement)
  {
    double x1 = controlStickRadius * Cos(angle) - bodyLength + 0.05;
    double z1 = controlStickRadius * Sin(angle) - (controlPanelRadius * 0.7);

    // Compute the normal vector (normalized)
    double nx = Cos(angle);
    double ny = 0;
    double nz = Sin(angle);

    glNormal3f(nx, ny, nz);

    glVertex3d(x1 + 0.06, controlStickStartingHeight, z1);
    glVertex3d(x1, controlStickFinalHeight, z1);
  }
  glEnd();

  // Draw control panel buttons
  double controlPanelButtonRadius = 0.03;
  glColor3f(1, 1, 0);

  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0, 1, 0);
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
  glNormal3f(0, 1, 0);
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
  glNormal3f(0, 1, 0);
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

  // Dark Gray
  glColor3f(0.2, 0.2, 0.2);

  // Draw the pedal extenders
  double pedalRadius = 0.02;
  double pedalStartingHeight = -height;
  double pedalFinalHeight = 0;

  glBegin(GL_QUAD_STRIP);
  for (int angle = 0; angle <= 360; angle += angleIncrement)
  {
    double x1 = pedalRadius * Cos(angle) - bodyLength + 0.05;
    double z1 = pedalRadius * Sin(angle) + (controlPanelRadius * 0.7);

    // Compute the normal vector (normalized)
    double nx = Cos(angle);
    double ny = 0;
    double nz = Sin(angle);

    glNormal3f(nx, ny, nz);

    glVertex3d(x1 + 0.06, pedalStartingHeight, z1);
    glVertex3d(x1, pedalFinalHeight, z1);
  }
  glEnd();

  glBegin(GL_QUAD_STRIP);
  for (int angle = 0; angle <= 360; angle += angleIncrement)
  {
    double x1 = pedalRadius * Cos(angle) - bodyLength + 0.05;
    double z1 = pedalRadius * Sin(angle) - (controlPanelRadius * 0.7);

    // Compute the normal vector (normalized)
    double nx = Cos(angle);
    double ny = 0;
    double nz = Sin(angle);

    glNormal3f(nx, ny, nz);

    glVertex3d(x1 + 0.06, pedalStartingHeight, z1);
    glVertex3d(x1, pedalFinalHeight, z1);
  }
  glEnd();

  glPopMatrix();
}
