#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y, float offset, color_t color);
    glm::vec3 position;
    glm::vec3 init_position;
    glm::vec3 abs_position;

    // glm::vec3 position2;
    bool visible;
    float rotation;
    float offset;
    float before;
    bounding_box_t box;
    bool get_visibility();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int ticks);
    void move_forward();
    void move_backward();
    void move_downward();
    bounding_box_t get_box();
    void collided();
    float get_x();
    bool touched(float now);
private:
    VAO *boomerang;
};

#endif // BOOMERANG_H
