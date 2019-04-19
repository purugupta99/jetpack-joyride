#include "main.h"

#ifndef BALLOON_H
#define BALLOON_H


class Balloon {
public:
    Balloon() {}
    Balloon(float x, float y, float abs_x, float abs_y, color_t color);
    glm::vec3 position;
    glm::vec3 abs_position;
    glm::vec3 dist_travelled;
    glm::vec3 velocity;
    glm::vec3 acceleration;

    // glm::vec3 position2;
    bool visible;
    float rotation;
    float offset;
    float sz;
    bounding_box_t box;
    bool get_visibility();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move_forward();
    void move_backward();
    void move_y();
    void gravity_effect();
    void update_box();
    void move_abs();
    bounding_box_t get_box();
    void collided();
    float get_x();
    float get_y();
private:
    VAO *balloon;
    VAO *object;
};

#endif // BALLOON_H
