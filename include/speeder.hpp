#ifndef SPEEDER_HPP
#define SPEEDER_HPP

class Speeder
{
public:
  void draw(double x, double y, double z);

private:
  void drawBody(double bodyLength, double bodyWidth, double bodyHeight);
  void drawBarrels(double barrelRadius, double bodyLength, double barrelLength, double bodyHeight, double bodyWidth);
  void drawBarrelGaurds(double barrelRadius, double barrelStartingPoint, double barrelLength, double bodyHeight, double bodyWidth);
  void drawControls(double bodyLength, double bodyWidth, double bodyHeight);
  void drawPedals(double bodyLength, double bodyWidth, double bodyHeight);
};

#endif