#include "platform.h"
#include "main.h"

using namespace std;

Platform::Platform(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    length = PLATFORM_LENGTH;
    width = PLATFORM_HEIGHT;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -length, width/2.0f, 0,
        -length, -width/2.0f, 0,
        length, -width/2.0f, 0,
        -length, width/2.0f, 0,
        length, width/2.0f, 0,
        length, -width/2.0f, 0,
    };

    static const GLfloat sub_design[] = {
        -length/2.0f, width/2.0f, 0,
        -length/2.0f, -width/2.0f, 0,
        length/2.0f, -width/2.0f, 0,
        -length/2.0f, width/2.0f, 0,
        length/2.0f, width/2.0f, 0,
        length/2.0f, -width/2.0f, 0,
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, sub_design, COLOR_LIGHT_BLACK, GL_FILL);
}

void Platform::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Platform::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Platform::tick() {
    this->move_backward();
}

// void Platform::move_forward() {
//     this->position.x += speed_x;
// }

void Platform::move_backward() {
    this->position.x -= GAME_SPEED;
}

float Platform::get_x() {
    return this->position.x;
}





