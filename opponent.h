#include <iostream>
#include <memory>
#include "cpputils/graphics/image.h"
#include "game_element.h"
#ifndef OPPONENT_H
#define OPPONENT_H

class Opponent : public GameElement {
 public:
  // constructor
  Opponent() : Opponent(0, 0) {}
  Opponent(int xpoint, int ypoint) : GameElement(xpoint, ypoint, 50, 50) {}

  // Draw Function
  void Draw(graphics::Image &game_screen) override;

  // Move Function
  void Move(const graphics::Image &image) override {
    SetY(GetY() + 1);
    SetX(GetX() + 1);

    if (IsOutOfBounds(image)) {
      SetIsActive(false);
    } else {
      SetIsActive(true);
    }
  }

  // launch projectile
  std::unique_ptr<class OpponentProjectile> LaunchProjectile();

 private:
  int counter_ = 0;
};

class OpponentProjectile : public GameElement {
 public:
  // constructor
  OpponentProjectile() : OpponentProjectile(0, 0) {}
  OpponentProjectile(int xpoint, int ypoint)
      : GameElement(xpoint, ypoint, 5, 5) {}

  // draw function
  void Draw(graphics::Image &game_screen) override;

  // move function
  void Move(const graphics::Image &image) override {
    SetY(GetY() + 1);
    SetX(GetX() + 1);

    if (IsOutOfBounds(image)) {
      SetIsActive(false);
    } else {
      SetIsActive(true);
    }
  }
};

#endif
