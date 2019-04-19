#include "main.h"
#include "timer.h"

#ifndef POWERUP_H
#define POWERUP_H


class Powerup {
public:
    Powerup() {}
    Powerup(float x, float y, int type, color_t color);
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
    int type;
    
    bounding_box_t box;
    bool get_visibility();
    bool check_counter_5();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move_forward();
    void move_backward();
    void move_y();
    void update_box();
    void move_abs();
    void picked_up();
    bounding_box_t get_box();
    bool make_invisible();
    float get_x();
    float get_y();
    int get_type();
private:
    VAO *object;
};

#endif // POWERUP_H
