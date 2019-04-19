#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin {
public:
    Coin() {}
    Coin(float x, float y, color_t color);
    glm::vec3 position;
    // glm::vec3 position2;
    bool visible;
    float rotation;
    float length;
    float width;
    float sz;
    bounding_box_t box;
    bool get_visibility();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float get_x();
    void move_forward();
    void move_backward();
    void picked_up();
    bounding_box_t get_box();
private:
    VAO *object;
    VAO *object2;
};

#endif // COIN_H
