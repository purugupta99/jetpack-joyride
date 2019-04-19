#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, color_t color);
    glm::vec3 position;
    // glm::vec3 position2;
    bool visible;
    float rotation;
    float length;
    float width;
    float before;
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
    bool touched();
    bounding_box_t get_box();
private:
    VAO *object;
    VAO *object2;
};

#endif // RING_H
