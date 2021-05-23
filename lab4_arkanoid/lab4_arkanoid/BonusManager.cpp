#include "BonusManager.hpp"
#include "Game.hpp"
#include <string>
#include <iostream>
using namespace sf;

void BonusManager::Draw(std::shared_ptr<sf::RenderWindow> window) {
    for (const auto& b : _bonuses)
        b->Draw(window);
}


void BonusManager::LoadTexture() {
    for (int i = 0; i < Bonus::NUM_BONUS_TYPES; i++) {
        Texture texture;
        texture.loadFromFile("../resources/" + std::to_string(i) + ".jpg");
        _textures.push_back(texture);
    }
    std::cout << "textures:" << _textures.size() << std::endl;
}


void BonusManager::AddRandomBonus(const sf::Vector2f& pos){
std::shared_ptr <Bonus> bonus;
    switch (rand() % Bonus::NUM_BONUS_TYPES) {
    case 0:
        bonus = std::make_shared <BarChangeBonus>(pos ,
                _textures[0]);
        break;
    case 1:
        bonus = std::make_shared <BallSpeedBonus>(pos,
            _textures[1]);
        break;
    case 2:
        bonus = std::make_shared <BarStickBonus>(pos,
            _textures[2]);
        break;
    case 3:
        bonus = std::make_shared <BotReflectBonus>(pos,
            _textures[3]);
        break;
    case 4:
        bonus = std::make_shared <ChangeTrajectoryBonus>(pos,
            _textures[4]); 
        break;
    case 5:
        bonus = std::make_shared <MovingBlockBonus>(pos,
            _textures[5]);
        break;
    }
    _bonuses.push_back(bonus);
}



void BonusManager::MoveAll(std::shared_ptr <Bar> bar, std::shared_ptr <Field> field,
                        std::shared_ptr <Ball> ball) {
    int i = 0;
    for (auto& bonus:_bonuses) {
        bonus->Move();

        // bonus is caught
        if (bonus->IsContactedWithBar(*bar)) {
            bonus->Activate(field, ball, bar);
            _bonuses.erase(_bonuses.begin() + i);
            break;
        }

        // bonus fell off
        if (bonus->getPosition().y >= Game::WINDOW_SIZE.y) {
            _bonuses.erase(_bonuses.begin() + i);
            break;
        }

        i++;
    }
}








