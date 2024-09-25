#ifndef SCENE_HPP
#define SCENE_HPP

class Scene
{
public:
  Scene(double dim_);
  void draw();
  void idle();
  void toggleAxes();
  void resetAngles();
  void adjustAngles(int th, int ph);
  void toggleShowcaseSpeeder();

private:
  int th, ph;           //  Azimuth, elevation angle
  double dim;           //  Size of world
  bool showAxes;        //  Toggle for axis display
  bool showcaseSpeeder; // Toggle for speeder showcase mode
  void drawAxes();
  void drawInfo();
  void drawEnviroment();
};

#endif