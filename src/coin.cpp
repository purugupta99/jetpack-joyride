#include "coin.h"
#include "main.h"

using namespace std;

Coin::Coin(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    sz = COIN_SIZE;
    this->visible = true;
    this->box.x = x;
    this->box.y = y;
    this->box.width = 2*sz;
    this->box.height = 2*sz;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int vertices = COIN_EDGES;

	GLfloat coin_outer_boundary[9*vertices];
	GLfloat coin_inner_boundary[9*vertices];

	int num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		coin_outer_boundary[i] =0.0f;
		coin_outer_boundary[i+1] =0.0f;
		coin_outer_boundary[i+2] =0.0f;
		coin_outer_boundary[i+3] =sz * cos(angle);
		coin_outer_boundary[i+4] =sz* sin(angle);
		coin_outer_boundary[i+5] =0.0f;
		coin_outer_boundary[i+6] =sz * cos(angle2);
		coin_outer_boundary[i+7] =sz * sin(angle2);
		coin_outer_boundary[i+8] =0.0f;

		num ++;
	}

    num = 0;
    sz = COIN_SIZE/2.0f;
    for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		coin_inner_boundary[i] =0.0f;
		coin_inner_boundary[i+1] =0.0f;
		coin_inner_boundary[i+2] =0.0f;
		coin_inner_boundary[i+3] =sz * cos(angle);
		coin_inner_boundary[i+4] =sz* sin(angle);
		coin_inner_boundary[i+5] =0.0f;
		coin_inner_boundary[i+6] =sz * cos(angle2);
		coin_inner_boundary[i+7] =sz * sin(angle2);
		coin_inner_boundary[i+8] =0.0f;

		num ++;
	}

    this->object = create3DObject(GL_TRIANGLES, vertices*3, coin_outer_boundary, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, vertices*3, coin_inner_boundary, COLOR_CREAM, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
}

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coin::tick() {
    this->rotation += 5.0f;
    this->move_backward();
}

float Coin::get_x() {
    return this->position.x;
}

// void Coin::move_forward() {
//     this->position.x += speed_x;
// }
bounding_box_t Coin::get_box(){
    return this->box;
}

void Coin::move_backward() {
    this->position.x -= GAME_SPEED;
}

bool Coin::get_visibility(){
    return this->visible;
}

void Coin::picked_up(){
    this->visible =false;
}




