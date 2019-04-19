#include "main.h"
#include "timer.h"

#ifndef DRAGON_H
#define DRAGON_H


class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec3 center;
    glm::vec3 abs_position;
    glm::vec3 dist_travelled;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float rotation;
    float height;
    float width;
    float before;
    int lives;
    bool visible;
    
    bounding_box_t box;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move_forward();
    void move_backward();
    void move_y();
    void move_abs();
    void update_box();
    void change_velocity();
    
    float get_x();
    float get_y();
    float get_z();
    float get_abs_x();
    float get_abs_y();
    float get_abs_z();
    bool touched();
    bool get_visibility();

    void birth();    
    void dead();
    void collided();
    bounding_box_t get_box();
    
private:
    VAO *face;
    VAO *torso;
    VAO *wing;
    VAO *legs;
    VAO *tail;
};

class Bullet {
public:
    Bullet() {}
    Bullet(float x, float y, float abs_x, float abs_y, color_t color);
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
    VAO *bullet;
    VAO *bullet_inner;
};

#endif // DRAGON_H
