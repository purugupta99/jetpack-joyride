#include "ring.h"
#include "main.h"

using namespace std;

Ring::Ring(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    sz = RING_SIZE;
    this->visible = true;
    this->box.x = x + RING_SIZE/2.0f;
    this->box.y = y;
    this->box.width = sz;
    this->box.height = 2*sz;
    this->before = -1.0f;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int vertices = RING_EDGES;

	GLfloat ring_outer_boundary[9*vertices];
	GLfloat ring_inner_boundary[9*vertices];

	int num =   -9*vertices/4+1;

	for(int i=0;i<9/2*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		ring_outer_boundary[i] =0.0f;
		ring_outer_boundary[i+1] =0.0f;
		ring_outer_boundary[i+2] =-1.0f;
		ring_outer_boundary[i+3] =sz * cos(angle);
		ring_outer_boundary[i+4] =sz* sin(angle);
		ring_outer_boundary[i+5] =-1.0f;
		ring_outer_boundary[i+6] =sz * cos(angle2);
		ring_outer_boundary[i+7] =sz * sin(angle2);
		ring_outer_boundary[i+8] =-1.0f;

		num ++;
	}

    num = -9 * vertices/4+1;
    sz = INNER_RING_SIZE;
    for(int i=0;i<9/2*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		ring_inner_boundary[i] =0.0f;
		ring_inner_boundary[i+1] =0.0f;
		ring_inner_boundary[i+2] =-1.0f;
		ring_inner_boundary[i+3] =sz * cos(angle);
		ring_inner_boundary[i+4] =sz* sin(angle);
		ring_inner_boundary[i+5] =-1.0f;
		ring_inner_boundary[i+6] =sz * cos(angle2);
		ring_inner_boundary[i+7] =sz * sin(angle2);
		ring_inner_boundary[i+8] =-1.0f;

		num ++;
	}

    this->object = create3DObject(GL_TRIANGLES, vertices/2*3, ring_outer_boundary, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, vertices/2*3, ring_inner_boundary, COLOR_BACKGROUND, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
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

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ring::tick() {
    // this->rotation += 5.0f;
    this->move_backward();
}

float Ring::get_x() {
    return this->position.x;
}

// void Ring::move_forward() {
//     this->position.x += speed_x;
// }
bounding_box_t Ring::get_box(){
    return this->box;
}

void Ring::move_backward() {
    this->position.x -= GAME_SPEED;
}

bool Ring::get_visibility(){
    return this->visible;
}

void Ring::picked_up(){
    this->visible =false;
}

bool Ring::touched(){
    if(nowTime - this->before > 1.0f){
        this->before = nowTime;
        return true;
    }
    return false;
}




