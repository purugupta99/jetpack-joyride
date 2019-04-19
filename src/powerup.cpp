#include "powerup.h"
#include "main.h"

using namespace std;

/* type:
        1 : DIAMOND
        2 : SPEED_UP    
*/

Powerup::Powerup(float x, float y, int type, color_t color) {
    this->position = glm::vec3(x, y, 0);
    // this->abs_position = glm::vec3(abs_x, abs_y, 0);
    this->dist_travelled = glm::vec3(0, 0, 0);
    this->velocity = glm::vec3(0.2f, 0.2f, 0);
    this->acceleration = glm::vec3(0, GRAVITY, 0);
    this->rotation = 0;
    this->type = type;

    sz = POWERUP_SIZE;
    this->visible = true;
    this->box.x = x;
    this->box.y = y;
    this->box.width = 2*sz;
    this->box.height = 2*sz;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    if(type == DIAMOND){
        GLfloat object[9*5] = {
            -0.1f,0.1f,0,
            0.1f,0.1f,0,
            -0.1f,0,0,
            0.1f,0,0,
            0.1f,0.1f,0,
            -0.1f,0,0,
            0.1f,0,0,
            0.1f,0.1f,0,
            0.2f,0,0,
            -0.1f,0.1f,0,
            -0.2f,0,0,
            -0.1f,0,0,
            0.2f,0,0,
            -0.2f,0,0,
            0,-0.1732f,0,
        };
        this->object = create3DObject(GL_TRIANGLES, 5*3, object, COLOR_RED, GL_FILL);
    }else if(type == SPEED_UP){
        GLfloat object[9*3] = {
            -0.2f,0,0,
            0.2f,0,0,
            0.0f,0.1732f,0,
            -0.1f,0,0,
            0.1f,0,0,
            -0.1f,-0.2,0,
            0.1f,-0.2f,0,
            0.1f,0,0,
            -0.1f,-0.2,0,
        };
        this->object = create3DObject(GL_TRIANGLES, 3*3, object, COLOR_GREEN, GL_FILL);
    }
    
    // this->object = create3DObject(GL_TRIANGLES, 1*3, object, COLOR_RED, GL_FILL);
}

void Powerup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    
    // draw3DObject(this->object);
}

void Powerup::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Powerup::tick() {
    // this->move_forward();
    // this->move_y();
    // this->gravity_effect();
    // this->move_abs();
    // this->update_box();

    // cout << this->position.x << " " << this->position.y << "\n";
    this->rotation += 5.0f;

    this->move_backward();
}

void Powerup::move_abs() {
    // this->dist_travelled.x += this->velocity.x;
    this->abs_position.x += this->velocity.x;
    this->abs_position.y = this->position.y;
}

float Powerup::get_x() {
    return this->position.x;
}

float Powerup::get_y() {
    return this->position.y;
}

void Powerup::move_forward() {
    this->position.x += this->velocity.x;
}

void Powerup::move_y() {
    this->position.y += this->velocity.y;
}

void Powerup::picked_up(){
    this->visible =false;
}

bounding_box_t Powerup::get_box(){
    return this->box;
}

void Powerup::move_backward() {
    this->position.x -= GAME_SPEED;
}

bool Powerup::get_visibility(){
    return this->visible;
}

bool Powerup::make_invisible(){
    return this->visible =false;
}

int Powerup::get_type(){
    // cout << this->counter_5.processTick() << "\n";
    return this->type;
}

void Powerup::update_box() {
    this->box.x = this->abs_position.x;
    this->box.y = this->abs_position.y;
}
