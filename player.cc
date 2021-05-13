#include "player.h"
#include "cpputils/graphics/image.h"
#include "opponent.h"

void Player::Draw(graphics::Image &game_screen) {
  int x = GetX();
  int y = GetY();
  int width = GetWidth();
  int height = GetHeight();

  graphics::Image player;
  player.Load("player.bmp");
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      game_screen.SetColor(x + i, y + j, player.GetColor(i, j));
    }
  }
}

void PlayerProjectile::Draw(graphics::Image &game_screen) {
  int x = GetX();
  int y = GetY();
  int width = GetWidth();
  int height = GetHeight();

  graphics::Image player_projectile;
  player_projectile.Load("p_pro.bmp");
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      game_screen.SetColor(x + i, y + j, player_projectile.GetColor(i, j));
    }
  }
}
