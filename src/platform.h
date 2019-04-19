#include "main.h"

#ifndef PLATFORM_H
#define PLATFORM_H


class Platform {
public:
    Platform() {}
    Platform(float x, float y, color_t color);
    glm::vec3 position;
    // glm::vec3 position2;
    float rotation;
    float length;
    float width;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move_forward();
    void move_backward();
    float get_x();
private:
    VAO *object;
    VAO *object2;
};

#endif // PLATFORM_H
