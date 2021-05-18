#include "BonusManager.h"
#include <string>

using namespace sf;

void BonusManager::Draw(sf::RenderWindow& window) {
     for (const auto& b : bonusesArray) 
         window.draw(*b); ;

}


void BonusManager::LoadTexture(int n) {
    for (int i = _textures.size(); i < n; i++) {
        Texture texture;
        texture.loadFromFile(std::to_string(i) + ".png");
        _textures.push_back(texture);
    }
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
        bonus = std::make_shared <BarChangeBonus>(pos,
            _textures[(int)BONUS_TYPE::CHANGE_TRAJECTORY]); 
        break;
    case (int)BONUS_TYPE::MOVING_BLOCK:
        bonus = std::make_shared <MovingBlockBonus>(pos,
            _textures[(int)BONUS_TYPE::BOTTOM_REFLECT]);
        break;
    }
    bonusesArray.push_back(bonus);
}

void BonusManager::MoveAll(std::shared_ptr <Bar> bar, std::shared_ptr <Field> field,
                        std::shared_ptr <Ball> ball, float window_height) {

    for (int i = 0; i < bonusesArray.size(); i++) {
        bonusesArray[i]->Move();

        if (bonusesArray[i]->IsContactedWithBar(*bar)) {
            bonusesArray[i]->Activate(field, ball, bar);
            bonusesArray.erase(bonusesArray.begin() + i);
            break;
        }

        if (bonusesArray[i]->getPosition().y >= window_height) {
            bonusesArray.erase(bonusesArray.begin() + i);
            break;
        }

      
    }
}








