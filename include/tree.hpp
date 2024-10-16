#ifndef TREE_HPP
#define TREE_HPP

class Tree
{
public:
  void draw(double x, double y, double z, double radius, double height);
  void loadTextures();

private:
  int leafTexture, woodTexture;
  void drawTrunk(double radius, double height);
  void drawLeaves(double radius, double height);
};

#endif