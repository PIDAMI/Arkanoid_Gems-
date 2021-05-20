#pragma once
#include "Field.hpp"
#include "Bar.hpp"
#include "Ball.hpp"
#include "BonusManager.hpp"

class Game
{
private:
    const static unsigned int FRAME_RATE;
    const static sf::Vector2u FIELD_SIZE;
    const static unsigned int BALL_FELLOFF_PENALTY;
public:
    const static sf::Vector2u WINDOW_SIZE;

private:
    int score;

    std::shared_ptr <sf::RenderWindow> window;  
    std::shared_ptr <Field> field;
    std::shared_ptr <Bar> bar; 
    std::shared_ptr <Ball> ball;
    std::shared_ptr <BonusManager> _bonuses;

    sf::Font scoreFont;
    sf::Vector2f _score_size;

private:
    
    void ShowScore();

    void Reflect(); // check reflections for all objects
    void BallReflectBlocks(); 
    void CheckBallFellDown();

    void MoveAll(); 
    void DrawAll();

    void InitObjects();
    bool CheckGameOver();
public:
    Game();
    ~Game() {};
    void Start();


};

