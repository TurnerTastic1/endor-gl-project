#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <cmath>
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

// Cosine and Sine in degrees
#define Cos(x) (cos((x) * 3.14159265 / 180))
#define Sin(x) (sin((x) * 3.14159265 / 180))

/*
 *  Check for OpenGL errors
 */
void Util::ErrCheck(const char *where)
{
  int err = glGetError();
  if (err)
    fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), where);
}

/*
 *  Convenience routine to output an error message and exit  - from ex9
 */
void Util::Fatal(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  exit(1);
}

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192 //  Maximum length of text string
void Util::Print(const char *format, ...)
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

/*
 *  Draw vertex in polar coordinates with normal
 */
void Util::Vertex(double th, double ph)
{
  double x = Sin(th) * Cos(ph);
  double y = Cos(th) * Cos(ph);
  double z = Sin(ph);
  //  For a sphere at the origin, the position
  //  and normal vectors are the same
  glNormal3d(x, y, z);
  glVertex3d(x, y, z);
}