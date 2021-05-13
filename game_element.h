#include <iostream>
#include "cpputils/graphics/image.h"
#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

class GameElement {
 public:
  // default constructor
  GameElement() : GameElement(0, 0, 50, 50) {}
  // non-default constructor
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}
  // accessors
  int GetX() const { return x_; }
  int GetY() const { return y_; }
  int GetWidth() { return width_; }
  int GetHeight() { return height_; }
  bool GetIsActive() { return is_active_; }

  // mutators
  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }
  void SetIsActive(bool active) { is_active_ = active; }

  // member function
  virtual void Draw(graphics::Image& my_image) = 0;

  virtual void Move(const graphics::Image& image) = 0;

  bool IntersectsWith(GameElement* my_element);

  bool IsOutOfBounds(const graphics::Image& my_image);

 private:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active_ = true;
};
#endif
