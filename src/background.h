#include "main.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H


class Background {
public:
    Background() {}
    Background(float x, float y, color_t color);
    glm::vec3 position;
    // glm::vec3 position2;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move_forward();
    void move_backward();
    float get_x();
private:
    VAO *object;
};

#endif // BACKGROUND_H
