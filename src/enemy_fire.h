#include "main.h"

#ifndef ENEMY_FIRE_H
#define ENEMY_FIRE_H


class Enemy_Fire {
public:
    Enemy_Fire() {}
    Enemy_Fire(float x, float y, float rotation, bool movable, color_t color);
    glm::vec3 position;
    glm::vec3 init_position;
    glm::vec3 abs_position;

    // glm::vec3 position2;
    bool visible;
    bool movable;
    float rotation;
    float amplitude;
    float length;
    float before;
    float sz;
    bounding_box_t box;
    bool get_visibility();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int ticks);
    void move_forward();
    void move_backward();
    bounding_box_t get_box();
    float get_rotation();
    void collided();
    float get_x();
    bool touched(float now);
private:
    VAO *initiator;
    VAO *terminator;
    VAO *fire_beam;
    VAO *object;
};

#endif // ENEMY_FIRE_H
