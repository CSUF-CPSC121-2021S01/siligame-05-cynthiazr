#include <iostream>
#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameElement {
 public:
  // constructor
  Player() : Player(0, 0) {}
  Player(int xpoint, int ypoint) : GameElement(xpoint, ypoint, 50, 50) {}

  // Draw Function
  void Draw(graphics::Image &game_screen) override;

  // move function
  void Move(const graphics::Image &image) override {}
};

class PlayerProjectile : public GameElement {
 public:
  // constructor
  PlayerProjectile() : PlayerProjectile(0, 0) {}
  PlayerProjectile(int xpoint, int ypoint)
      : GameElement(xpoint, ypoint, 5, 5) {}

  // Draw Function
  void Draw(graphics::Image &game_screen) override;

  // move function
  void Move(const graphics::Image &image) override {
    SetY(GetY() - 3);
    SetX(GetX() - 3);

    if (IsOutOfBounds(image)) {
      SetIsActive(false);
    } else {
      SetIsActive(true);
    }
  }
};
#endif
