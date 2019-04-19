#include "magnet.h"
#include "main.h"

using namespace std;

Magnet::Magnet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    // this->abs_position = glm::vec3(abs_x, abs_y, 0);
    this->dist_travelled = glm::vec3(0, 0, 0);
    this->velocity = glm::vec3(0.2f, 0.2f, 0);
    this->acceleration = glm::vec3(0, GRAVITY, 0);
    this->rotation = 0;
    this->counter_5 = Timer(5.0f);
    sz = MAGNET_SIZE;
    this->visible = true;
    this->box.x = x;
    this->box.y = y;
    this->box.width = 2.0f*sz;
    this->box.height = 2.0f*sz;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int vertices = MAGNET_EDGES;

	GLfloat magnet[9*vertices];
	GLfloat magnet_inner[9*vertices];
	GLfloat rods[9*4] = {
        -sz,0,0,
        -sz/2,0,0,
        -sz,-sz,0,
        -sz/2,-sz,0,
        -sz/2,0,0,
        -sz,-sz,0,

        sz,0,0,
        sz/2,0,0,
        sz,-sz,0,
        sz/2,-sz,0,
        sz/2,0,0,
        sz,-sz,0,

    };

    GLfloat end_1[9*2] = {
        -sz,-sz/2,0,
        -sz/2,-sz/2,0,
        -sz,-sz,0,
        -sz/2,-sz,0,
        -sz/2,-sz/2,0,
        -sz,-sz,0,
    };

    GLfloat end_2[9*2] = {
        sz,-sz/2,0,
        sz/2,-sz/2,0,
        sz,-sz,0,
        sz/2,-sz,0,
        sz/2,-sz/2,0,
        sz,-sz,0,
    };

	int num = 0;

	for(int i=0;i<9*vertices/2;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		magnet[i] =0.0f;
		magnet[i+1] =0.0f;
		magnet[i+2] =0.0f;
		magnet[i+3] =sz * cos(angle);
		magnet[i+4] =sz* sin(angle);
		magnet[i+5] =0.0f;
		magnet[i+6] =sz * cos(angle2);
		magnet[i+7] =sz * sin(angle2);
		magnet[i+8] =0.0f;

		num ++;
	}

    num = 0;
    sz /= 2;

	for(int i=0;i<9*vertices/2;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		magnet_inner[i] =0.0f;
		magnet_inner[i+1] =0.0f;
		magnet_inner[i+2] =0.0f;
		magnet_inner[i+3] =sz * cos(angle);
		magnet_inner[i+4] =sz* sin(angle);
		magnet_inner[i+5] =0.0f;
		magnet_inner[i+6] =sz * cos(angle2);
		magnet_inner[i+7] =sz * sin(angle2);
		magnet_inner[i+8] =0.0f;

		num ++;
	}

    this->magnet = create3DObject(GL_TRIANGLES, vertices/2*3, magnet, color, GL_FILL);
    this->magnet_inner = create3DObject(GL_TRIANGLES, vertices/2*3, magnet_inner, COLOR_BACKGROUND, GL_FILL);
    this->rods = create3DObject(GL_TRIANGLES, 4*3, rods, COLOR_GRAY, GL_FILL);
    this->end_1 = create3DObject(GL_TRIANGLES, 2*3, end_1, COLOR_RED, GL_FILL);
    this->end_2 = create3DObject(GL_TRIANGLES, 2*3, end_2, COLOR_BLUE, GL_FILL);
    // this->object = create3DObject(GL_TRIANGLES, 1*3, object, COLOR_RED, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->magnet);
    draw3DObject(this->magnet_inner);
    draw3DObject(this->rods);
    draw3DObject(this->end_1);
    draw3DObject(this->end_2);
    // draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    // this->move_forward();
    // this->move_y();
    // this->gravity_effect();
    // this->move_abs();
    // this->update_box();

    // cout << this->position.x << " " << this->position.y << "\n";
    // this->move_backward();
}

void Magnet::move_abs() {
    // this->dist_travelled.x += this->velocity.x;
    this->abs_position.x += this->velocity.x;
    this->abs_position.y = this->position.y;
}

float Magnet::get_x() {
    return this->position.x;
}

float Magnet::get_y() {
    return this->position.y;
}

void Magnet::move_forward() {
    this->position.x += this->velocity.x;
}

void Magnet::move_y() {
    this->position.y += this->velocity.y;
}

void Magnet::gravity_effect() {
    this->velocity.y += this->acceleration.y;
}

bounding_box_t Magnet::get_box(){
    return this->box;
}

void Magnet::move_backward() {
    this->position.x -= GAME_SPEED;
}

bool Magnet::get_visibility(){
    return this->visible;
}

bool Magnet::make_invisible(){
    return this->visible =false;
}

bool Magnet::check_counter_5(){
    // cout << this->counter_5.processTick() << "\n";
    return this->counter_5.processTick();
}

void Magnet::update_box() {
    this->box.x = this->abs_position.x;
    this->box.y = this->abs_position.y;
}

