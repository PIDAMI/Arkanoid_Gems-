#include "Game.h"


using namespace sf;

const unsigned int Game::FRAME_RATE = 100U;
const Vector2u Game::FIELD_SIZE = { 6U, 4U };
const unsigned int Game::BALL_FELLOFF_PENALTY = 3U;
const Vector2u Game::WINDOW_SIZE = { 810U, 600U };

void Game::ShowScore() {
    Text text;

    text.setFont(scoreFont);
    text.setString("Score: " + std::to_string(score));
    text.setCharacterSize((unsigned)(_score_size.x + _score_size.y) / 10);
    text.setStyle(sf::Text::Bold);

    window->draw(text);
}


bool Game::CheckGameOver() {
    if (field->CheckGameEnd()) {
        window->clear();
        ShowScore();

        sf::Text text;
        auto window_size = window->getSize();
        text.setPosition(0.1f * window_size.x, 0.5f * window_size.y);
        text.setFont(scoreFont);
        text.setFillColor(sf::Color::Red);
        text.setString("GAME OVER. PRESS SPACE TO EXIT");
        text.setStyle(sf::Text::Bold);
        text.setCharacterSize(0.03f * (window_size.x + window_size.y) );

        window->draw(text);

        window->display();

        return true;
    }
    return false;
}

void Game::Start() {
    while (window->isOpen()) {

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        // if only blocks left are indestructable, show game over
        // press space to exit
        if (CheckGameOver())
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                //InitObjects();
                //Start();
                break;
            }
            
            else
                continue;


        window->clear();

        
        CheckBallFellDown();
        MoveAll();
        Reflect();

        DrawAll();

        window->display();
    }

}

void Game::BallReflectBlocks() {
    std::vector<std::shared_ptr<Block>> grid = field->GetGrid();
    int i = 0;
    for (auto block : grid) {
       
            if (ball->ReflectFromBlock(*block)) {

                auto blockType = block->GetType();

                if (blockType != TYPE::INDESTRUCTABLE)
                    score += 1;

                if (blockType == TYPE::SPEED_UP) {
                    sf::Vector2f acceleration = block->GetSpeedIncrement();
                    ball->IncreaseSpeed(acceleration);
                }

                if (blockType == TYPE::HAS_BONUS && block->GetHealth() == 1) {
                    auto block_pos = block->getPosition();
                    auto block_size = block->getSize();
                    float bonus_x = block_pos.x + 0.5f * block_size.x;
                    float bonus_y = block_pos.y + 0.5f * block_size.y;

                    _bonuses->AddRandomBonus({ bonus_x,bonus_y });
                }

                field->ReduceHealth(i);

                break;
            }
        
        i++;
    }
}


void Game::DrawAll() {
    field->Draw(window);
    bar->Draw(window);
    ball->Draw(window);
    _bonuses->Draw(window);
    ShowScore();
}



void Game::CheckBallFellDown() {
    
    if (ball->getPosition().y >= WINDOW_SIZE.y &&
        !(ball->IsReflectableByBot())) {

        ball->Respawn();
        bar->Respawn();
        score -= BALL_FELLOFF_PENALTY;
    }


}

void Game::MoveAll() {
    
    ball->Move();
    _bonuses->MoveAll(bar, field, ball);
    bar->Move();
    field->MoveMovingBlocks();
    
}

void Game::Reflect() {
    ball->ReflectWall();
    ball->ReflectBar(bar);
    BallReflectBlocks();
    field->CheckCollisionsBetweenBlocks();

}

void Game::InitObjects(){
    auto window_size = WINDOW_SIZE;
    Vector2f block_size = { (float)window_size.x / FIELD_SIZE.x,
                               0.3f * window_size.y / FIELD_SIZE.y };
    Vector2f field_top_coord = { 0, _score_size.y };
    field = std::make_shared <Field>
        (field_top_coord, FIELD_SIZE, (Vector2f)window_size, block_size);


    Vector2f bar_size = { 0.25f * window_size.x, 0.05f * window_size.y };
    Vector2f bar_start_pos = { 1.5f * bar_size.x, 0.9f * window_size.y };

    bar = std::make_shared <Bar>(bar_size, bar_start_pos);


    float ball_radius = (block_size.x + block_size.y) / 20.f;
    Vector2f ball_start_pos = { bar_start_pos.x + bar_size.x / 2 - ball_radius / 2,
                              bar_start_pos.y - 3 * ball_radius };
    ball = std::make_shared <Ball>(ball_radius, ball_start_pos);

    _bonuses = std::make_shared<BonusManager>();
}

Game::Game() {
    auto window_size = WINDOW_SIZE;
    window = std::make_shared <sf::RenderWindow>
        (sf::VideoMode(window_size.x, window_size.y), "Arkanoid");
    window->setFramerateLimit(FRAME_RATE);

    _score_size = { window_size.x * 0.3f, window_size.y * 0.1f };
    score = 0;
    scoreFont.loadFromFile("Thanks Autumn.ttf");
    InitObjects();
    
   
}
