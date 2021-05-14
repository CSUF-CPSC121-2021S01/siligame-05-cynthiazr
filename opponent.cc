#include "opponent.h"
#include "cpputils/graphics/image.h"

void Opponent::Draw(graphics::Image &game_screen) {
  int x = GetX();
  int y = GetY();
  int width = GetWidth();
  int height = GetHeight();

  graphics::Image opponent;
  opponent.Load("opponent.bmp");
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      game_screen.SetColor(x + i, y + j, opponent.GetColor(i, j));
    }
  }
}

std::unique_ptr<class OpponentProjectile> Opponent::LaunchProjectile() {
  std::unique_ptr<class OpponentProjectile> op_proj;

  if (counter_ >= 10) {
    counter_ = 0;
    op_proj = std::make_unique<class OpponentProjectile>(GetX(), GetY());
    return std::move(op_proj);
  } else {
    counter_++;
    return nullptr;
  }
}

void OpponentProjectile::Draw(graphics::Image &game_screen) {
  int x = GetX();
  int y = GetY();
  int width = GetWidth();
  int height = GetHeight();

  graphics::Image opponent_projectile;
  opponent_projectile.Load("o_pro.bmp");
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      game_screen.SetColor(x + i, y + j, opponent_projectile.GetColor(i, j));
    }
  }
}
