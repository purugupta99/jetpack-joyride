#include "enemy_fire.h"
#include "main.h"

using namespace std;

Enemy_Fire::Enemy_Fire(float x, float y, float rotation, bool movable, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->init_position = glm::vec3(x, y, 0);
    this->abs_position = glm::vec3(x, y, 0);
    this->rotation = rotation;
    this->amplitude = 3.25f;
    this->visible = true;
    this->movable = movable;
    this->before = -1.0f;
   
    length = ENEMY_FIRE_LENGTH;
    sz = ENEMY_FIRE_SIZE;

    this->box.x = x;
    this->box.y = y;
    this->box.width = 0.1f;
    this->box.height = length;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int vertices = 60;

    GLfloat fire_beam[] = {
        0.05f,0.5f,-1.0f,
        -0.05f,0.5f,-1.0f,
        -0.05f,-0.5f,-1.0f,
        0.05f,0.5f,-1.0f,
        0.05f,-0.5f,-1.0f,
        -0.05f,-0.5f,-1.0f,
    };

    GLfloat object[] = {
        -0.05f,length/2,0.0f,
        -0.05f,-length/2,0.0f,
        0.05f,length/2,0.0f,
        0.05f,-length/2,0.0f,
        -0.05f,-length/2,0.0f,
        0.05f,length/2,0.0f,
    };

    GLfloat initiator[9*vertices];
    GLfloat terminator[9*vertices];

	int num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
		initiator[i] =0.0f;
		initiator[i+1] =0.5f;
		initiator[i+2] =-1.0f;
		initiator[i+3] =sz * cos(angle);
		initiator[i+4] =sz* sin(angle) + 0.5f;
		initiator[i+5] =-1.0f;
		initiator[i+6] =sz * cos(angle2);
		initiator[i+7] =sz * sin(angle2) + 0.5f;
		initiator[i+8] =-1.0f;

		num ++;
	}

    num = 0;

	for(int i=0;i<9*vertices;i+=9)
	{
		float angle = ((float)num/(float) vertices) * 2*M_PI;
		float angle2 = ((float)(num+1)/(float) vertices) * 2*M_PI;
		
	    terminator[i] =0.0f;
	    terminator[i+1] =-0.5f;
	    terminator[i+2] =-1.0f;
	    terminator[i+3] =sz * cos(angle);
	    terminator[i+4] =sz* sin(angle) - 0.5f;
	    terminator[i+5] =-1.0f;
	    terminator[i+6] =sz * cos(angle2);
	    terminator[i+7] =sz * sin(angle2) - 0.5f;
	    terminator[i+8] =-1.0f;

		num ++;
	}

    this->object = create3DObject(GL_TRIANGLES, 2*3, object, COLOR_WHITE, GL_FILL);
    this->fire_beam = create3DObject(GL_TRIANGLES, 2*3, fire_beam, COLOR_FIRE, GL_FILL);
    this->initiator = create3DObject(GL_TRIANGLES, vertices*3, initiator, COLOR_GRAY, GL_FILL);
    this->terminator = create3DObject(GL_TRIANGLES, vertices*3, terminator, COLOR_GRAY, GL_FILL);
}

void Enemy_Fire::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->fire_beam);
    draw3DObject(this->initiator);
    draw3DObject(this->terminator);
    // draw3DObject(this->object);
}

void Enemy_Fire::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy_Fire::tick(int ticks) {
    this->move_backward();
    if(this->movable)
    {
        if(this->rotation == 0){
            this->position.x = this->abs_position.x;
            this->position.y = this->amplitude * sin(M_PI * (float)ticks / 120.0f);

            this->box.x = this->init_position.x;
            this->box.y = this->init_position.y + this->amplitude * sin(M_PI * (float)ticks / 120.0f);
        
        }else if(this->rotation == 90.0f){

            this->position.x = this->abs_position.x + this->amplitude * sin(M_PI * (float)ticks / 120.0f);
            this->position.y = this->abs_position.y;

            this->box.x = this->init_position.x + this->amplitude * sin(M_PI * (float)ticks / 120.0f);
            this->box.y = this->init_position.y;
  
        }
    }else{
        this->position.x = this->abs_position.x;
        this->position.y = this->abs_position.y;        
    }
}

// void Enemy_Fire::move_forward() {
//     this->position.x += speed_x;
// }

void Enemy_Fire::move_backward() {
    this->abs_position.x -= GAME_SPEED;
}

bounding_box_t Enemy_Fire::get_box(){
    return this->box;
}

bool Enemy_Fire::get_visibility(){
    return this->visible;
}

float Enemy_Fire::get_rotation(){
    return this->rotation;
}

void Enemy_Fire::collided(){
    this->visible =false;
}

bool Enemy_Fire::touched(float now){
    if(now - this->before > 1.0f){
        // cout << now << " " << this->before << "\n";  
        this->before = now;
        return true;
    }
    return false;
}

float Enemy_Fire::get_x() {
    return this->position.x;
}




