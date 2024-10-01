#ifndef UTIL_HPP
#define UTIL_HPP

class Util
{
public:
  static void ErrCheck(const char *where);
  static void Fatal(const char *format, ...);
};

#endif