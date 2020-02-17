#if !defined(GAME_HPP)
#define GAME_HPP

#include "../common.hpp"
#include "../Graphics/Graphics.hpp"
#include "Entity.hpp"

class Game
{
public:
    uint64_t tick_count;
    Camera* cam;
    uint window_width;
    uint window_height;
    std::vector<Entity> game_objects;
    //
    Game(uint width, uint height);
    ~Game();
    void init();
    void update(float delta);
};

#endif // GAME_HPP
