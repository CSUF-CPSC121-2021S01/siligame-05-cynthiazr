#include "game_element.h"

bool GameElement::IntersectsWith(GameElement* my_element) {
  int x_op = my_element->GetX();
  int y_op = my_element->GetY();
  int width_op = my_element->GetWidth();
  int height_op = my_element->GetHeight();

  int x_p = x_;
  int y_p = y_;
  int width_p = width_;
  int height_p = height_;

  if (x_p < (x_op + width_op)) {
    if ((x_p + width_p) > x_op) {
      if (y_p < (y_op + height_op)) {
        if ((y_p + height_p) > y_op) {
          return true;
        }
      }
    }
  }

  return false;
}

bool GameElement::IsOutOfBounds(const graphics::Image& game_screen) {
  if (GetX() < 0 || GetX() + GetWidth() > game_screen.GetWidth() ||
      GetY() < 0 || GetY() + GetHeight() > game_screen.GetHeight()) {
    return true;
  }

  return false;
}
