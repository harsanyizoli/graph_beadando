#if !defined(ENTITY_HPP)
#define ENTITY_HPP

#include "../common.hpp"
#include "../Graphics/tinyobjloader.h"

class Entity
{
private:
    /* data */
    glm::vec3 pos;
    glm::vec3 orientation;
    float scale;
    const char* file_name;
    std::string warn;
    std::string err;
    
public:
    Entity(const char* name);
    ~Entity();
    void scale_obj(glm::vec3 ax, float s);
    void rotate(glm::vec3 ax, float degree);
    void move(glm::vec3 pos_to);
};

#endif // ENTITY_HPP
