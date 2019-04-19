#include "boomerang.h"
#include "main.h"

using namespace std;

Boomerang::Boomerang(float x, float y, float offset, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->init_position = glm::vec3(x, y, 0);
    this->abs_position = glm::vec3(x, y, 0);
    this->visible = true;
    this->offset = offset;
    this->before = -1.0f;
    
    this->box.x = x;
    this->box.y = y;
    this->box.width = 0.375f;
    this->box.height = 2 * 0.2165f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    GLfloat boomerang[] = {
        0.0f,0.0f,0.0f,
        -0.25f,0.0f,0.0f,
        0.1f,0.2165f,0.0f,
        0.0f,0.0f,0.0f,
        -0.25f,0.0f,0.0f,
        0.125f,-0.2165f,0.0f,
    };
    
    this->boomerang = create3DObject(GL_TRIANGLES, 2*3, boomerang, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->boomerang);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomerang::tick(int ticks) {
    this->rotation += 5.0f;
    this->move_backward();
    this->move_downward();

    this->position.x = this->abs_position.x + 3*this->position.y*this->position.y;

    this->box.x = this->init_position.x + 3*this->position.y*this->position.y + this->offset;
    // this->box.x = this->position.x;
    this->box.y = this->position.y;
    
    // cout << "BOOMER " << " " << this->box.x << " " << this->box.y << "\n"; 

}

// void Boomerang::move_forward() {
//     this->position.x += speed_x;
// }

void Boomerang::move_backward() {
    this->abs_position.x -= GAME_SPEED;
}

void Boomerang::move_downward() {
    this->position.y -= BOOMERANG_FALL;
}

bounding_box_t Boomerang::get_box(){
    return this->box;
}

bool Boomerang::get_visibility(){
    return this->visible;
}

void Boomerang::collided(){
    this->visible =false;
}

float Boomerang::get_x() {
    return this->position.x;
}

bool Boomerang::touched(float now){
    if(now - this->before > 1.0f){
        // cout << now << " " << this->before << "\n";  
        this->before = now;
        return true;
    }

    return false;
}



