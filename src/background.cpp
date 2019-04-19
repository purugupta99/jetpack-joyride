#include "background.h"
#include "main.h"

using namespace std;

Background::Background(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // GLfloat vertex_buffer_data[81*4];
    GLfloat vertex_buffer_data[81*4] = {
        0.0f,0.0f,-1.0f,
        2.0f,0.0f,-1.0f,
        0.0f,2.0f,-1.0f,
        2.0f,2.0f,-1.0f,
        2.0f,0.0f,-1.0f,
        0.0f,2.0f,-1.0f,
        0.5f,2.0f,-1.0f,
        1.0f,2.0f,-1.0f,
        1.0f,2.5f,-1.0f,
        2.0f,2.5f,-1.0f,
        1.0f,2.0f,-1.0f,
        1.0f,2.5f,-1.0f,
        2.0f,2.5f,-1.0f,
        1.0f,2.0f,-1.0f,
        2.0f,2.0f,-1.0f,
        2.0f,2.5f,-1.0f,
        2.5f,2.0f,-1.0f,
        2.0f,2.0f,-1.0f,
        2.0f,1.0f,-1.0f,
        2.5f,2.0f,-1.0f,
        2.0f,2.0f,-1.0f,
        2.0f,1.0f,-1.0f,
        2.5f,2.0f,-1.0f,
        2.5f,1.0f,-1.0f,
        2.0f,1.0f,-1.0f,
        2.0f,0.5f,-1.0f,
        2.5f,1.0f,-1.0f,
    };


    int offset = 9*3*3;
    for(int j=0;j<3;j++)
    {
        if(offset == 9*3*3){
            for(int i=0;i<9*3*3;i+=3){
                vertex_buffer_data[offset+i] = -1*vertex_buffer_data[i];
                vertex_buffer_data[offset+i+1] = vertex_buffer_data[i+1];
                vertex_buffer_data[offset+i+2] = vertex_buffer_data[i+2];
            }
        }else if(offset == 2*9*3*3){
            for(int i=0;i<9*3*3;i+=3){
                vertex_buffer_data[offset+i] = -1*vertex_buffer_data[i];
                vertex_buffer_data[offset+i+1] = -1*vertex_buffer_data[i+1];
                vertex_buffer_data[offset+i+2] = vertex_buffer_data[i+2];
            }
        }else if(offset == 3*9*3*3){
            for(int i=0;i<9*3*3;i+=3){
                vertex_buffer_data[offset+i] = vertex_buffer_data[i];
                vertex_buffer_data[offset+i+1] = -1*vertex_buffer_data[i+1];
                vertex_buffer_data[offset+i+2] = vertex_buffer_data[i+2];
            }
        }
        offset += 9*3*3;
    }

    this->object = create3DObject(GL_TRIANGLES, 36*3, vertex_buffer_data, color, GL_FILL);
}

void Background::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Background::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Background::tick() {
    this->move_backward();
}

// void Background::move_forward() {
//     this->position.x += speed_x;
// }

void Background::move_backward() {
    this->position.x -= GAME_SPEED;
}

float Background::get_x() {
    return this->position.x;
}



