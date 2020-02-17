#include "Game.hpp"

Game::Game(uint width, uint height)
{
    //setup
    cam = new Camera({0.0f, 0.0f, 3.0f});
    window_width = width;
    window_height = height;
    tick_count = 0;
    init();
}

Game::~Game()
{
}

void Game::init(){
    std::cout << "Game init()\n";
    game_objects.emplace_back(Entity("assets/katana.obj"));
}

void Game::update(float delta){
    std::cout << "updating game state\n";
}