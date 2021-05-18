#pragma once
#include "Field.h"
#include "Bar.h"
#include "Ball.h"
#include "BonusManager.h"

class Game
{
private:
    const static unsigned int FRAME_RATE;
    const static sf::Vector2u FIELD_SIZE;
    const static unsigned int BALL_FELLOFF_PENALTY;
private:
    unsigned score;

    std::shared_ptr<sf::RenderWindow> window;  
    std::shared_ptr <Field> field;
    std::shared_ptr <Bar> bar; 
    std::shared_ptr <Ball> ball;
    std::shared_ptr <BonusManager> _bonuses;

    sf::Font scoreFont;
    sf::Vector2f _score_size;

private:
    
    void ShowScore();

    
    void Reflect(); // check reflections for all objects
    void BallReflectBricks(); 
    void CheckBallFellDown();

    void MoveAll(); 
    void DrawAll();


    bool CheckGameOver();
public:
    Game(const sf::Vector2u& window_size);
    ~Game() {};
    void Start();


};

