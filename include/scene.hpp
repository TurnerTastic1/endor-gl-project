#ifndef SCENE_HPP
#define SCENE_HPP

class Scene
{
public:
  Scene(double dim, int res);
  void draw();
  void idle();
  void key(unsigned char ch, int x, int y);
  void special(int key, int x, int y);
  void reshape(int width, int height);

private:
  int th, ph;           //  Azimuth, elevation angle
  double dim;           //  Size of world
  int res;              //  Resolution
  bool showAxes;        //  Toggle for axis display
  bool showcaseSpeeder; // Toggle for speeder showcase mode
  int viewMode;         // Toggle for view mode - 0 for orthographic, 1 for perspective, 2 for first person
  void drawAxes();
  void drawInfo();
  void drawEnviroment();

  void resetAngles();
  void adjustAngles(int th, int ph);

  void toggleAxes();
  void toggleShowcaseSpeeder();
  void toggleViewMode();
};

#endif