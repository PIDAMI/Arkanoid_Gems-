#pragma once
#include "Bonus.h"

class BonusManager
{

private:
    std::vector <std::shared_ptr <Bonus>> _bonuses; 
public:
    BonusManager() {};
    ~BonusManager() {}
    // bonus manager is a unique object, no need to make _textures static
    std::vector<sf::Texture> _textures;

    void LoadTexture(); // image files have the same name as their enums val


    //void AddRandomBonus(float x, float y, float radius, float speed);
    void AddRandomBonus(const sf::Vector2f& pos);



    void Draw(sf::RenderWindow& window);

    void MoveAll(std::shared_ptr <Bar> bar, std::shared_ptr <Field> field,
        std::shared_ptr <Ball> ball, float window_height);

};

