#include "game.h"
#include "cpputils/graphics/image.h"
#include "opponent.h"
#include "player.h"

void Game::UpdateScreen() {
  gamescreen_.DrawRectangle(0, 0, 800, 600, 255, 255, 255);
  graphics::Color black(0, 0, 0);
  graphics::Color red(150, 6, 6);
  gamescreen_.DrawText(0, 0, "Score: " + std::to_string(GetScore()), 21, black);

  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->GetIsActive() == true) {
      opponent_[i]->Draw(gamescreen_);
    }
  }

  for (int i = 0; i < opponentprojectile_.size(); i++) {
    if (opponentprojectile_[i]->GetIsActive() == true) {
      opponentprojectile_[i]->Draw(gamescreen_);
    }
  }

  for (int i = 0; i < playerprojectile_.size(); i++) {
    if (playerprojectile_[i]->GetIsActive() == true) {
      playerprojectile_[i]->Draw(gamescreen_);
    }
  }

  if (player_.GetIsActive() == true) {
    player_.Draw(gamescreen_);
  }

  if (HasLost() == true) {
    gamescreen_.DrawText(gamescreen_.GetWidth() * (0.25),
                         gamescreen_.GetHeight() * (0.5), "GAME OVER", 65, red);
  }
}

void Game::MoveGameElements() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->GetIsActive() == true) {
      opponent_[i]->Move(gamescreen_);
    }
  }

  for (int i = 0; i < opponentprojectile_.size(); i++) {
    if (opponentprojectile_[i]->GetIsActive() == true) {
      opponentprojectile_[i]->Move(gamescreen_);
    }
  }

  for (int i = 0; i < playerprojectile_.size(); i++) {
    if (playerprojectile_[i]->GetIsActive() == true) {
      playerprojectile_[i]->Move(gamescreen_);
    }
  }
}

void Game::FilterIntersections() {
  // check opponent & player
  for (int i = 0; i < opponent_.size(); i++) {
    bool intersect = player_.IntersectsWith(opponent_[i].get());
    if (intersect == true) {
      player_.SetIsActive(false);
      opponent_[i]->SetIsActive(false);
      has_lost_ = true;
    }
  }

  // check opponent projectile & player
  for (int i = 0; i < opponentprojectile_.size(); i++) {
    bool intersect = player_.IntersectsWith(opponentprojectile_[i].get());
    if (intersect == true) {
      player_.SetIsActive(false);
      opponentprojectile_[i]->SetIsActive(false);
      has_lost_ = true;
    }
  }

  // check player projectile & opponent objects
  for (int i = 0; i < playerprojectile_.size(); i++) {
    for (int j = 0; j < opponent_.size(); j++) {
      bool intersect_opponent =
          playerprojectile_[i]->IntersectsWith(opponent_[j].get());
      if (intersect_opponent == true) {
        playerprojectile_[i]->SetIsActive(false);
        opponent_[j]->SetIsActive(false);
        if (player_.GetIsActive() == true) {
          score_++;
        }
      }
    }
  }
}

void Game::OnAnimationStep() {
  if (opponent_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  gamescreen_.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent &mouse_event) {
  if (mouse_event.GetMouseAction() == graphics::MouseAction::kMoved ||
      mouse_event.GetMouseAction() == graphics::MouseAction::kDragged) {
    if (mouse_event.GetX() > 0 && mouse_event.GetY() > 0 &&
        mouse_event.GetX() < gamescreen_.GetWidth() &&
        mouse_event.GetY() < gamescreen_.GetHeight()) {
      player_.SetX(mouse_event.GetX() - player_.GetWidth() * (0.5));
      player_.SetY(mouse_event.GetY() - player_.GetHeight() * (0.5));
    }
  }

  if (mouse_event.GetMouseAction() == graphics::MouseAction::kPressed ||
      mouse_event.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> pl_p = std::make_unique<PlayerProjectile>(
        mouse_event.GetX(), mouse_event.GetY());
    playerprojectile_.push_back(std::move(pl_p));
  }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponent_.size(); i++) {
    std::unique_ptr<OpponentProjectile> temp_op =
        opponent_[i]->LaunchProjectile();
    if (temp_op != nullptr) {
      opponentprojectile_.push_back(std::move(temp_op));
    }
  }
}

void Game::RemoveInactive() {
  for (int i = opponent_.size() - 1; i >= 0; i--) {
    if (!opponent_[i]->GetIsActive()) {
      opponent_.erase(opponent_.begin() + i);
    }
  }

  for (int i = opponentprojectile_.size() - 1; i >= 0; i--) {
    if (!opponentprojectile_[i]->GetIsActive()) {
      opponentprojectile_.erase(opponentprojectile_.begin() + i);
    }
  }

  for (int i = playerprojectile_.size() - 1; i >= 0; i--) {
    if (!playerprojectile_[i]->GetIsActive()) {
      playerprojectile_.erase(playerprojectile_.begin() + i);
    }
  }
}
