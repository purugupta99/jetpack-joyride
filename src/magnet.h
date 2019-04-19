#include "main.h"
#include "timer.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, color_t color);
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
    Timer counter_5;
    bounding_box_t box;
    bool get_visibility();
    bool check_counter_5();
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
    bool make_invisible();
    float get_x();
    float get_y();
private:
    VAO *magnet;
    VAO *magnet_inner;
    VAO *rods;
    VAO *end_1;
    VAO *end_2;
    VAO *object;
};

#endif // MAGNET_H
