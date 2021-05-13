#include <iostream>
#include <vector>
#include <memory>
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  // default constructor
  Game() : Game(800, 600) {}
  // non-default constructor
  Game(int width, int height) : gamescreen_(width, height) {}
  // accesors
  graphics::Image &GetGameScreen() { return gamescreen_; }
  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return opponent_; }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return opponentprojectile_;
  }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return playerprojectile_;
  }
  Player &GetPlayer() { return player_; }
  int GetScore() { return score_; }
  bool HasLost() { return has_lost_; }

  // member functions
  void CreateOpponents() {
    std::unique_ptr<Opponent> op = std::make_unique<Opponent>(151, 100);
    std::unique_ptr<Opponent> op2 = std::make_unique<Opponent>(300, 50);

    opponent_.push_back(std::move(op));
    opponent_.push_back(std::move(op2));
  }

  void Init() {
    player_.SetX(500);
    player_.SetY(200);

    // add game to derived classes
    gamescreen_.AddMouseEventListener(*this);
    gamescreen_.AddAnimationEventListener(*this);
  }

  void UpdateScreen();

  void Start() { gamescreen_.ShowUntilClosed(); }

  // more functions (milestone 4)
  void MoveGameElements();

  void FilterIntersections();

  void OnAnimationStep();

  void OnMouseEvent(const graphics::MouseEvent &mouse_event);

  // launch projectiles (milestone 5)
  void LaunchProjectiles();

  void RemoveInactive();

 private:
  graphics::Image gamescreen_;
  std::vector<std::unique_ptr<Opponent>> opponent_;
  std::vector<std::unique_ptr<OpponentProjectile>> opponentprojectile_;
  std::vector<std::unique_ptr<PlayerProjectile>> playerprojectile_;
  Player player_;
  int score_;
  bool has_lost_;
};
