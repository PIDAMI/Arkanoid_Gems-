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
    for (int i = 0; i < (int)BONUS_TYPE::DEFAULT; i++) {
        Texture texture;
        texture.loadFromFile("../resources/" + std::to_string(i) + ".jpg");
        _textures.push_back(texture);
    }
    std::cout << "textures:" << _textures.size() << std::endl;
}


void BonusManager::AddRandomBonus(const sf::Vector2f& pos){
std::shared_ptr <Bonus> bonus;
    switch (rand() % (int)BONUS_TYPE::DEFAULT) {
    case (int)BONUS_TYPE::BAR_CHANGE:
        bonus = std::make_shared <BarChangeBonus>(pos ,
                _textures[(int)BONUS_TYPE::BAR_CHANGE]);
        break;
    case (int)BONUS_TYPE::STICK_BAR:
        bonus = std::make_shared <BarStickBonus>(pos,
            _textures[(int)BONUS_TYPE::STICK_BAR]);
        break;
    case (int)BONUS_TYPE::BOTTOM_REFLECT:
        bonus = std::make_shared <BotReflectBonus>(pos,
            _textures[(int)BONUS_TYPE::BOTTOM_REFLECT]);
        break;
    case (int)BONUS_TYPE::CHANGE_TRAJECTORY:
        bonus = std::make_shared <ChangeTrajectoryBonus>(pos,
            _textures[(int)BONUS_TYPE::CHANGE_TRAJECTORY]); 
        break;
    case (int)BONUS_TYPE::MOVING_BLOCK:
        bonus = std::make_shared <MovingBlockBonus>(pos,
            _textures[(int)BONUS_TYPE::MOVING_BLOCK]);
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








