#include "dragon.h"
#include "main.h"

using namespace std;

Dragon::Dragon(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->abs_position = glm::vec3(0, 0, 0);
    this->dist_travelled = glm::vec3(0, 0, 0);
    this->velocity = glm::vec3(0.1f, 0.05f, 0);
    this->acceleration = glm::vec3(0, 0, 0);
    this->rotation = 0;

    height = DRAGON_HEIGHT;
    width = DRAGON_WIDTH;
    this->center = glm::vec3(width/2.0f + 0.1f, height/2.0f, 0);
    this->box.x = x;
    this->box.y = y;
    this->box.width = width/1.25f;
    this->box.height = height/1.25f;

    this->visible = false;
    this->lives = 5;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    GLfloat face[] = {
        0,1.5f,-1.0f,
        0.1f,1.5f,-1.0f,
        0.1f,1.6f,-1.0f,
        0.3,1.5f,-1.0f,
        0.1f,1.5f,-1.0f,
        0.1f,1.6f,-1.0f,
        0.3,1.5f,-1.0f,
        0.3f,1.6f,-1.0f,
        0.1f,1.6f,-1.0f,
        0.3,1.65f,-1.0f,
        0.3f,1.6f,-1.0f,
        0.1f,1.6f,-1.0f,
        0.3f,1.5f,-1.0f,
        0.4f,1.5f,-1.0f,
        0.3f,1.65f,-1.0f,
        0.4f,1.65f,-1.0f,
        0.4f,1.5f,-1.0f,
        0.3f,1.65f,-1.0f,
        0.4f,1.65f,-1.0f,
        0.4f,1.75f,-1.0f,
        0.3f,1.65f,-1.0f,
        0.4f,1.5f,-1.0f,
        0.6f,1.5f,-1.0f,
        0.4f,1.75f,-1.0f,
        0.6f,1.75f,-1.0f,
        0.6f,1.5f,-1.0f,
        0.4f,1.75f,-1.0f,
        0.6f,1.75f,-1.0f,
        0.6f,1.5f,-1.0f,
        0.7f,1.75f,-1.0f,
        0.4f,1.75f,-1.0f,
        0.75f,1.9f,-1.0f,
        0.7f,1.75f,-1.0f,
        0.0f,1.5f,-1.0f,
        0.6f,1.5f,-1.0f,
        0.0f,1.45f,-1.0f,

    };

    GLfloat torso[] = {
        0.6f,1.5f,-1.0f,
        0.7f,1.5f,-1.0f,
        0.7f,1.7f,-1.0f,
        0.8f,1.5f,-1.0f,
        0.7f,1.5f,-1.0f,
        0.7f,1.7f,-1.0f,
        0.8f,1.5f,-1.0f,
        0.8f,1.7f,-1.0f,
        0.7f,1.7f,-1.0f,
        0.8f,1.5f,-1.0f,
        0.8f,1.7f,-1.0f,
        1.0f,1.7f,-1.0f,
        1.3f,1.5f,-1.0f,
        0.8f,1.5f,-1.0f,
        1.0f,1.7f,-1.0f,
        1.3f,1.5f,-1.0f,
        0.8f,1.5f,-1.0f,
        0.8f,1.3f,-1.0f,
        1.3f,1.5f,-1.0f,
        1.3f,1.3f,-1.0f,
        0.8f,1.3f,-1.0f,
        1.3f,1.5f,-1.0f,
        1.3f,1.3f,-1.0f,
        1.5f,1.3f,-1.0f,
        1.2f,1.3f,-1.0f,
        0.8f,1.3f,-1.0f,
        1.2f,1.0f,-1.0f,
        1.2f,1.3f,-1.0f,
        1.5f,1.0f,-1.0f,
        1.2f,1.0f,-1.0f,
        1.2f,1.3f,-1.0f,
        1.5f,1.0f,-1.0f,
        1.5f,1.3f,-1.0f,
        1.5f,1.2f,-1.0f,
        1.7f,1.2f,-1.0f,
        1.5f,1.3f,-1.0f,
        1.5f,1.2f,-1.0f,
        1.7f,1.2f,-1.0f,
        1.5f,1.0f,-1.0f,
        1.7f,1.0f,-1.0f,
        1.7f,1.2f,-1.0f,
        1.5f,1.0f,-1.0f,
    };

    GLfloat wing[] = {
        1.2f,1.0f,-1.0f,
        1.2f,0.9f,-1.0f,
        1.0f,0.9f,-1.0f,
        1.2f,1.0f,-1.0f,
        1.2f,0.9f,-1.0f,
        1.5f,1.0f,-1.0f,
        1.2f,0.9f,-1.0f,
        1.5f,0.9f,-1.0f,
        1.5f,1.0f,-1.0f,
        1.6f,1.0f,-1.0f,
        1.5f,0.9f,-1.0f,
        1.5f,1.0f,-1.0f,
        1.0f,0.9f,-1.0f,
        1.0f,0.7f,-1.0f,
        0.6f,0.7f,-1.0f,
        1.0f,0.9f,-1.0f,
        1.0f,0.7f,-1.0f,
        1.5f,0.7f,-1.0f,
        1.0f,0.9f,-1.0f,
        1.5f,0.9f,-1.0f,
        1.5f,0.7f,-1.0f,
        1.6f,0.7f,-1.0f,
        1.5f,0.9f,-1.0f,
        1.5f,0.7f,-1.0f,
        0.6f,0.7f,-1.0f,
        0.8f,0.7f,-1.0f,
        0.8f,0.5f,-1.0f,
        1.6f,0.5f,-1.0f,
        0.8f,0.7f,-1.0f,
        0.8f,0.5f,-1.0f,
        1.6f,0.5f,-1.0f,
        0.8f,0.7f,-1.0f,
        1.6f,0.7f,-1.0f,
        1.6f,0.5f,-1.0f,
        1.7f,0.5f,-1.0f,
        1.6f,0.7f,-1.0f,
        0.8f,0.5f,-1.0f,
        1.1f,0.3f,-1.0f,
        1.1f,0.5f,-1.0f,
        0.8f,0.5f,-1.0f,
        1.1f,0.3f,-1.0f,
        1.1f,0.5f,-1.0f,
        1.5f,0.5f,-1.0f,
        1.1f,0.3f,-1.0f,
        1.1f,0.5f,-1.0f,
        1.5f,0.5f,-1.0f,
        1.1f,0.3f,-1.0f,
        1.5f,0.3f,-1.0f,
        1.5f,0.5f,-1.0f,
        1.7f,0.5f,-1.0f,
        1.5f,0.3f,-1.0f,
        1.1f,0.3f,-1.0f,
        1.2f,0.3f,-1.0f,
        1.2f,0.1f,-1.0f,
        1.5f,0.3f,-1.0f,
        1.2f,0.3f,-1.0f,
        1.2f,0.1f,-1.0f,
        1.5f,0.3f,-1.0f,
        1.5f,0.1f,-1.0f,
        1.2f,0.1f,-1.0f,
        1.5f,0.3f,-1.0f,
        1.5f,0.1f,-1.0f,
        1.6f,0.1f,-1.0f,
        1.2f,0.1f,-1.0f,
        1.6f,0.1f,-1.0f,
        1.7f,0.0f,-1.0f,


    };

    GLfloat legs[] = {
        1.8f,0.9f,-1.0f,
        1.8f,1.0f,-1.0f,
        1.6f,1.0f,-1.0f,
        1.8f,0.9f,-1.0f,
        1.8f,1.0f,-1.0f,
        2.0f,1.0f,-1.0f,
        1.8f,0.9f,-1.0f,
        2.0f,0.9f,-1.0f,
        2.0f,1.0f,-1.0f,
        1.8f,0.9f,-1.0f,
        2.0f,0.9f,-1.0f,
        2.0f,0.8f,-1.0f,
        1.9f,0.9f,-1.0f,
        1.8f,0.7f,-1.0f,
        2.0f,0.8f,-1.0f,

    };

    GLfloat tail[] = {
        1.7f,1.2f,-1.0f,
        1.7f,1.0f,-1.0f,
        1.9f,1.0f,-1.0f,
        1.7f,1.2f,-1.0f,
        1.9f,1.2f,-1.0f,
        1.9f,1.0f,-1.0f,
        2.0f,1.2f,-1.0f,
        1.9f,1.2f,-1.0f,
        1.9f,1.0f,-1.0f,
        2.0f,1.2f,-1.0f,
        1.7f,1.2f,-1.0f,
        2.4f,1.5f,-1.0f,


    };

    for(int i=0;i<12*3*3;i+=3){
        face[i] -= this->center.x;
        face[i+1] -= this->center.y;
    }

    for(int i=0;i<14*3*3;i+=3){
        torso[i] -= this->center.x;
        torso[i+1] -= this->center.y;
    }
    for(int i=0;i<22*3*3;i+=3){
        wing[i] -= this->center.x;
        wing[i+1] -= this->center.y;
    }
    for(int i=0;i<5*3*3;i+=3){
        legs[i] -= this->center.x;
        legs[i+1] -= this->center.y;
    }
    for(int i=0;i<4*3*3;i+=3){
        tail[i] -= this->center.x;
        tail[i+1] -= this->center.y;
    }

    this->face = create3DObject(GL_TRIANGLES, 12*3, face, COLOR_GREEN, GL_FILL);
    this->torso = create3DObject(GL_TRIANGLES, 14*3, torso, COLOR_BLUE, GL_FILL);
    this->wing = create3DObject(GL_TRIANGLES, 22*3, wing, COLOR_DARK_RED, GL_FILL);
    this->legs = create3DObject(GL_TRIANGLES, 5*3, legs, COLOR_BLUE, GL_FILL);
    this->tail = create3DObject(GL_TRIANGLES, 4*3, tail, COLOR_BLUE, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    draw3DObject(this->face);
    draw3DObject(this->torso);
    draw3DObject(this->wing);
    draw3DObject(this->legs);
    draw3DObject(this->tail);
    
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dragon::tick() {
    
    this->move_abs();
    this->move_y();
    this->update_box();

    if(this->lives <= 0){
        this->dead();
    }

    // cout << this->lives << "\n";

    if(this->position.y  > TOP_LEVEL)
    {
        this->velocity.y *= -1;
    }
    
    if (this->position.y  < GROUND_LEVEL)
    {
        this->velocity.y *= -1;
    }
}

void Dragon::move_forward() {
    this->position.x += this->velocity.x;
}

void Dragon::move_backward() {
    this->position.x -= this->velocity.x;
}

void Dragon::move_y() {
        this->position.y += this->velocity.y;   
}

void Dragon::move_abs() {
    this->dist_travelled.x += GAME_SPEED;
    this->abs_position.x = this->position.x + this->dist_travelled.x;
    this->abs_position.y = this->position.y;
}

void Dragon::update_box() {
    this->box.x = this->abs_position.x;
    this->box.y = this->abs_position.y;
}

bool Dragon::get_visibility(){
    return this->visible;
}

float Dragon::get_x() {
    return this->position.x;
}

float Dragon::get_y() {
    return this->position.y;
}

float Dragon::get_z() {
    return this->position.z;
}

float Dragon::get_abs_x() {
    return this->abs_position.x;
}

float Dragon::get_abs_y() {
    return this->abs_position.y;
}

float Dragon::get_abs_z() {
    return this->abs_position.z;
}

bounding_box_t Dragon::get_box(){
    return this->box;
}

void Dragon::collided(){
    this->lives--;
}

void Dragon::birth(){
    this->visible = true;
}

void Dragon::dead(){
    this->visible = false;
}

bool Dragon::touched(){
    if(nowTime - this->before > 1.0f){
        this->before = nowTime;
        return true;
    }
    return false;
}

Bullet::Bullet(float x, float y, float abs_x, float abs_y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->abs_position = glm::vec3(abs_x, abs_y, 0);
    this->dist_travelled = glm::vec3(0, 0, 0);
    this->velocity = glm::vec3(0.3f, 0.2f, 0);
    this->rotation = 0;

    sz = BULLET_SIZE;
    this->visible = true;
    this->box.x = abs_x;
    this->box.y = abs_y;
    this->box.width = 2.0f*sz;
    this->box.height = 2.0f*sz;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int vertices = BULLET_EDGES;

	GLfloat bullet[9*vertices];
	GLfloat bullet_inner[9*vertices];

	int num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		bullet[i] =0.0f;
		bullet[i+1] =0.0f;
		bullet[i+2] =-1.0f;
		bullet[i+3] =sz * cos(angle);
		bullet[i+4] =sz* sin(angle);
		bullet[i+5] =-1.0f;
		bullet[i+6] =sz * cos(angle2);
		bullet[i+7] =sz * sin(angle2);
		bullet[i+8] =-1.0f;

		num ++;
	}

    num = 0;
    sz = BULLET_SIZE/2;
    
	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		bullet_inner[i] =0.0f;
		bullet_inner[i+1] =0.0f;
		bullet_inner[i+2] =-1.0f;
		bullet_inner[i+3] =sz * cos(angle);
		bullet_inner[i+4] =sz* sin(angle);
		bullet_inner[i+5] =-1.0f;
		bullet_inner[i+6] =sz * cos(angle2);
		bullet_inner[i+7] =sz * sin(angle2);
		bullet_inner[i+8] =-1.0f;

		num ++;
	}

    this->bullet = create3DObject(GL_TRIANGLES, vertices*3, bullet, color, GL_FILL);
    this->bullet_inner = create3DObject(GL_TRIANGLES, vertices*3, bullet_inner, COLOR_BLUE, GL_FILL);
}

void Bullet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->bullet);
    draw3DObject(this->bullet_inner);
}

void Bullet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Bullet::tick() {
    this->move_backward();
    
    this->move_abs();
    this->update_box();

    // cout << this->position.x << " " << this->position.y << "\n";
    // this->move_backward();
}

void Bullet::move_abs() {
    // this->dist_travelled.x += this->velocity.x;
    this->abs_position.x -= ( this->velocity.x - GAME_SPEED);
    this->abs_position.y = this->position.y;
}

float Bullet::get_x() {
    return this->position.x;
}

float Bullet::get_y() {
    return this->position.y;
}

void Bullet::move_forward() {
    this->position.x += this->velocity.x;
}


bounding_box_t Bullet::get_box(){
    return this->box;
}

void Bullet::move_backward() {
    this->position.x -= this->velocity.x;
}

bool Bullet::get_visibility(){
    return this->visible;
}

void Bullet::collided(){
    this->visible =false;
}

void Bullet::update_box() {
    this->box.x = this->abs_position.x;
    this->box.y = this->abs_position.y;
}

