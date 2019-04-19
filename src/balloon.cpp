#include "balloon.h"
#include "main.h"

using namespace std;

Balloon::Balloon(float x, float y, float abs_x, float abs_y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->abs_position = glm::vec3(abs_x, abs_y, 0);
    this->dist_travelled = glm::vec3(0, 0, 0);
    this->velocity = glm::vec3(0.2f, 0.2f, 0);
    this->acceleration = glm::vec3(0, GRAVITY, 0);
    this->rotation = 0;
    sz = BALLOON_SIZE;
    this->visible = true;
    this->box.x = abs_x;
    this->box.y = abs_y;
    this->box.width = 2.25f*sz;
    this->box.height = 2.25f*sz;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int vertices = BALLOON_EDGES;

	GLfloat balloon[9*vertices];
	GLfloat object[] = {
        0,-sz,0,
        -0.10f,-sz-0.10f,0,
        0.10f,-sz-0.10f,0,
        // -sz,sz,0,
        // -sz,-sz,0,
        // sz,sz,0,
        // sz,-sz,0,
        // -sz,-sz,0,
        // sz,sz,0,

    };

	int num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		balloon[i] =0.0f;
		balloon[i+1] =0.0f;
		balloon[i+2] =0.0f;
		balloon[i+3] =sz * cos(angle);
		balloon[i+4] =sz* sin(angle);
		balloon[i+5] =0.0f;
		balloon[i+6] =sz * cos(angle2);
		balloon[i+7] =sz * sin(angle2);
		balloon[i+8] =0.0f;

		num ++;
	}

    this->balloon = create3DObject(GL_TRIANGLES, vertices*3, balloon, color, GL_FILL);
    this->object = create3DObject(GL_TRIANGLES, 1*3, object, COLOR_RED, GL_FILL);
}

void Balloon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->balloon);
    draw3DObject(this->object);
}

void Balloon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Balloon::tick() {
    this->move_forward();
    this->move_y();
    this->gravity_effect();
    this->move_abs();
    this->update_box();

    // cout << this->position.x << " " << this->position.y << "\n";
    // this->move_backward();
}

void Balloon::move_abs() {
    // this->dist_travelled.x += this->velocity.x;
    this->abs_position.x += this->velocity.x;
    this->abs_position.y = this->position.y;
}

float Balloon::get_x() {
    return this->abs_position.x;
}

float Balloon::get_y() {
    return this->position.y;
}

void Balloon::move_forward() {
    this->position.x += this->velocity.x;
}

void Balloon::move_y() {
    this->position.y += this->velocity.y;
}

void Balloon::gravity_effect() {
    this->velocity.y += this->acceleration.y;
}

bounding_box_t Balloon::get_box(){
    return this->box;
}

void Balloon::move_backward() {
    this->position.x -= GAME_SPEED;
}

bool Balloon::get_visibility(){
    return this->visible;
}

void Balloon::collided(){
    this->visible =false;
}

void Balloon::update_box() {
    this->box.x = this->abs_position.x;
    this->box.y = this->abs_position.y;
}

