#include "main.h"
#include "timer.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec3 center;
    glm::vec3 abs_position;
    glm::vec3 dist_travelled;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 jetpack_acceleration;
    int score;
    float rotation;
    float height;
    float width;

    float before;
    float ring_check;
    bounding_box_t box;
    void draw(glm::mat4 VP, bool trigger);
    void set_position(float x, float y);
    void tick();
    void move_forward();
    void move_backward();
    void move_up();
    void move_abs();
    void update_box();
    void change_velocity();
    void restore_acceleration();
    void gravity_effect();
    void magnet_effect(float magnet_x, float magnet_y);
    float get_x();
    float get_y();
    float get_z();
    int get_score();
    float get_abs_x();
    float get_abs_y();
    float get_abs_z();
    void inc_score(int increment);
    bool move_along_ring();
    bool ring_timer();
    void initiate_ring_timer(float now_time);
    void inc_velocity();
    void restore_velocity_x(float interval);
    void restore_velocity_y(float interval);
    bounding_box_t get_box();
    
private:
    VAO *object;
    VAO *hair;
    VAO *face;
    VAO *torso;
    VAO *tie;
    VAO *legs;
    VAO *boots;
    VAO *hands;
    VAO *shield;
    VAO *jetpack;
    VAO *jetpack_fire;
    VAO *jetpack_inner_fire;
};

#endif // PLAYER_H
