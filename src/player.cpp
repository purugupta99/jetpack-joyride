#include "player.h"
#include "main.h"

using namespace std;

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->abs_position = glm::vec3(0, 0, 0);
    this->dist_travelled = glm::vec3(0, 0, 0);
    this->velocity = glm::vec3(0.1f, 0.02f, 0);
    this->acceleration = glm::vec3(0, 0, 0);
    this->jetpack_acceleration = glm::vec3(0, 0.02f, 0);
    this->rotation = 0;
    this->score = 0;

    this->before = 0;
    this->ring_check = 0;
    height = PLAYER_HEIGHT;
    width = PLAYER_WIDTH;
    this->center = glm::vec3(width/2.0f + 0.1f, height/2.0f, 0);
    this->box.x = x;
    this->box.y = y;
    this->box.width = width;
    this->box.height = height;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -width/2.0f, height/2.0f, 0,
        -width/2.0f, -height/2.0f, 0,
        width/2.0f, -height/2.0f, 0,
        -width/2.0f, height/2.0f, 0,
        width/2.0f, height/2.0f, 0,
        width/2.0f, -height/2.0f, 0,
    };

    GLfloat hair[] = {
        0.6f,1.0f,0,
        0.6f,0.9f,0,
        0.7f,0.95f,0,
        0.3f,1.0f,0,
        0.6f,1.0f,0,
        0.6f,0.9f,0,
        0.3f,1.0f,0,
        0.3f,0.9f,0,
        0.6f,0.9f,0,
        0.3f,0.9f,0,
        0.4f,0.9f,0,
        0.3f,0.7f,0,
        0.3f,0.9f,0,
        0.4f,0.9f,0,
        0.4f,0.7f,0,
    };

    GLfloat face[] = {
        0.4f,0.9f,0,
        0.6f,0.9f,0,
        0.4f,0.8f,0,
        0.6f,0.8f,0,
        0.6f,0.9f,0,
        0.4f,0.8f,0,
        0.4f,0.8f,0,
        0.5f,0.8f,0,
        0.5f,0.7f,0,
        0.6f,0.8f,0,
        0.5f,0.8f,0,
        0.5f,0.7f,0,
        0.6f,0.8f,0,
        0.6f,0.7f,0,
        0.5f,0.7f,0,
    };

    GLfloat torso[] = {
        0.3f,0.6f,0,
        0.4f,0.6f,0,
        0.4f,0.7f,0,
        0.5f,0.7f,0,
        0.4f,0.6f,0,
        0.4f,0.7f,0,
        0.5f,0.7f,0,
        0.4f,0.6f,0,
        0.5f,0.6f,0,
        0.5f,0.7f,0,
        0.6f,0.6f,0,
        0.5f,0.6f,0,
        0.3f,0.6f,0,
        0.6f,0.6f,0,
        0.3f,0.2f,0,
        0.6f,0.2f,0,
        0.6f,0.6f,0,
        0.3f,0.2f,0,
    };

    GLfloat tie[] = {
        0.5f,0.7f,0,
        0.6f,0.6f,0,
        0.5f,0.6f,0,
        0.55f,0.3f,0,
        0.55f,0.5f,0,
        0.6f,0.5f,0,
        0.55f,0.3f,0,
        0.6f,0.3f,0,
        0.6f,0.5f,0,

    };

    GLfloat legs[] = {
        0.4f,0.2f,0,
        0.4f,0.0f,0,
        0.6f,0.2f,0,
        0.6f,0.0f,0,
        0.4f,0.0f,0,
        0.6f,0.2f,0,
    };

    GLfloat boots[] = {
        0.4f,0.1f,0,
        0.4f,0.0f,0,
        0.6f,0.1f,0,
        0.6f,0.0f,0,
        0.4f,0.0f,0,
        0.6f,0.1f,0,
    };

    GLfloat hands[] = {
        0.4f,0.6f,0,
        0.4f,0.5f,0,
        0.7f,0.6f,0,
        0.7f,0.5f,0,
        0.4f,0.5f,0,
        0.7f,0.6f,0,
    };

    GLfloat shield[] = {
        -0.45f,0.5f,0,
        0.45f,0.5f,0,
        0.45f,0.6f,0,
        -0.45f,0.5f,0,
        -0.45f,0.6f,0,
        0.45f,0.6f,0,
        0.35f,0.5f,0,
        0.35f,-0.5f,0,
        0.45f,0.5f,0,
        0.45f,-0.5f,0,
        0.35f,-0.5f,0,
        0.45f,0.5f,0,

        -0.45f,-0.5f,0,
        0.45f,-0.5f,0,
        0.45f,-0.6f,0,
        -0.45f,-0.5f,0,
        -0.45f,-0.6f,0,
        0.45f,-0.6f,0,
        -0.35f,0.5f,0,
        -0.35f,-0.5f,0,
        -0.45f,0.5f,0,
        -0.45f,-0.5f,0,
        -0.35f,-0.5f,0,
        -0.45f,0.5f,0,

    };

    GLfloat jetpack[] = {
        0.1f,0.6f,0,
        0.2f,0.8f,0,
        0.3f,0.6f,0,
        0.1f,0.6f,0,
        0.1f,0.3f,0,
        0.3f,0.6f,0,
        0.3f,0.3f,0,
        0.1f,0.3f,0,
        0.3f,0.6f,0,
    };

    GLfloat jetpack_fire[] = {
        0.3f,0.3f,0,
        0.1f,0.3f,0,
        0.2f,0.0f,0,
    };

    GLfloat jetpack_inner_fire[] = {
        0.25f,0.3f,0,
        0.15f,0.3f,0,
        0.2f,0.15f,0,
    };

    for(int i=0;i<5*3*3;i+=3){
        hair[i] -= this->center.x;
        hair[i+1] -= this->center.y;
    }
    for(int i=0;i<5*3*3;i+=3){
        face[i] -= this->center.x;
        face[i+1] -= this->center.y;
    }
    for(int i=0;i<6*3*3;i+=3){
        torso[i] -= this->center.x;
        torso[i+1] -= this->center.y;
    }
    for(int i=0;i<3*3*3;i+=3){
        tie[i] -= this->center.x;
        tie[i+1] -= this->center.y;
    }
    for(int i=0;i<2*3*3;i+=3){
        legs[i] -= this->center.x;
        legs[i+1] -= this->center.y;
    }
    for(int i=0;i<2*3*3;i+=3){
        boots[i] -= this->center.x;
        boots[i+1] -= this->center.y;
    }
    for(int i=0;i<2*3*3;i+=3){
        hands[i] -= this->center.x;
        hands[i+1] -= this->center.y;
    }
    for(int i=0;i<3*3*3;i+=3){
        jetpack[i] -= this->center.x;
        jetpack[i+1] -= this->center.y;
    }
    for(int i=0;i<1*3*3;i+=3){
        jetpack_fire[i] -= this->center.x;
        jetpack_fire[i+1] -= this->center.y;
    }
    for(int i=0;i<1*3*3;i+=3){
        jetpack_inner_fire[i] -= this->center.x;
        jetpack_inner_fire[i+1] -= this->center.y;
    }

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
    this->hair = create3DObject(GL_TRIANGLES, 5*3, hair, COLOR_BLACK, GL_FILL);
    this->face = create3DObject(GL_TRIANGLES, 5*3, face, COLOR_SKIN, GL_FILL);
    this->torso = create3DObject(GL_TRIANGLES, 6*3, torso, COLOR_BLUE, GL_FILL);
    this->tie = create3DObject(GL_TRIANGLES, 3*3, tie, COLOR_DARK_RED, GL_FILL);
    this->legs = create3DObject(GL_TRIANGLES, 2*3, legs, COLOR_RED, GL_FILL);
    this->boots = create3DObject(GL_TRIANGLES, 2*3, boots, COLOR_BLACK, GL_FILL);
    this->hands = create3DObject(GL_TRIANGLES, 2*3, hands, COLOR_SKIN, GL_FILL);
    this->shield = create3DObject(GL_TRIANGLES, 8*3, shield, COLOR_PURPLE, GL_FILL);
    this->jetpack = create3DObject(GL_TRIANGLES, 3*3, jetpack, COLOR_JETPACK, GL_FILL);
    this->jetpack_fire = create3DObject(GL_TRIANGLES, 1*3, jetpack_fire, COLOR_FIRE, GL_FILL);
    this->jetpack_inner_fire = create3DObject(GL_TRIANGLES, 1*3, jetpack_inner_fire, COLOR_DARK_FIRE, GL_FILL);
}

void Player::draw(glm::mat4 VP, bool trigger) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object);
    draw3DObject(this->hair);
    draw3DObject(this->face);
    draw3DObject(this->torso);
    draw3DObject(this->tie);
    draw3DObject(this->legs);
    draw3DObject(this->boots);
    draw3DObject(this->hands);
    if(shield_trigger){
        draw3DObject(this->shield);
    }
    draw3DObject(this->jetpack);
    if(trigger){
        draw3DObject(this->jetpack_fire);
        draw3DObject(this->jetpack_inner_fire);
    }
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick() {
    
    this->move_abs();
    this->update_box();
    
    this->gravity_effect();
    this->restore_velocity_x(5.0f);
    // this->magnet_effect();
    // this->change_velocity();
    if(in_ring)
    {
        if(this->ring_timer()){
            // cout << "not_in_ring\n";
            in_ring = false;
        }
        this->move_along_ring();
    }

    if(this->position.y + this->center.y > TOP_LEVEL)
    {
        // this->position.y = TOP_LEVEL;    for dwindelling effect
        this->position.y = TOP_LEVEL - this->center.y;
    }
    if (this->position.y - this->center.y < GROUND_LEVEL)
    {
        this->position.y = GROUND_LEVEL + this->center.y;
    }
    if (this->position.x < LEFT_BOUNDARY)
    {
        this->position.x = LEFT_BOUNDARY;
    }
    if (this->position.x > RIGHT_BOUNDARY)
    {
        this->position.x = RIGHT_BOUNDARY;
    }
    // cout << this->position.x << " " << this->position.y << " " << this->velocity.y << " " << this->abs_position.x << "\n"; 
    // cout << "BARRY" << " " << this->box.x << " " << this->box.y << "\n"; 
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

void Player::move_forward() {
    this->position.x += this->velocity.x;
}

void Player::move_backward() {
    this->position.x -= this->velocity.x;
}

void Player::gravity_effect() {
    if (this->position.y - this->center.y > GROUND_LEVEL)
    {
        this->velocity.y += GRAVITY;
        this->position.y += this->velocity.y;
    }
    else
    {
        this->velocity.y = 0.02;
    }
}

void Player::move_up() {
    if(this->position.y + this->center.y < TOP_LEVEL)
    {
        this->velocity.y += this->jetpack_acceleration.y;
        this->position.y += this->velocity.y;
    }
}

void Player::move_abs() {
    this->dist_travelled.x += GAME_SPEED;
    this->abs_position.x = this->position.x + this->dist_travelled.x;
    this->abs_position.y = this->position.y;
}

void Player::update_box() {
    this->box.x = this->abs_position.x;
    this->box.y = this->abs_position.y;
}

float Player::get_x() {
    return this->position.x;
}

float Player::get_y() {
    return this->position.y;
}

float Player::get_z() {
    return this->position.z;
}

float Player::get_abs_x() {
    return this->abs_position.x;
}

float Player::get_abs_y() {
    return this->abs_position.y;
}

int Player::get_score() {
    return this->score;
}

float Player::get_abs_z() {
    return this->abs_position.z;
}

void Player::change_velocity(){
    this->velocity.x += this->acceleration.x;
    this->velocity.y += this->acceleration.y;
}

void Player::restore_acceleration() {
    this->acceleration.x = 0;
    this->acceleration.y = 0;
}

void Player::magnet_effect(float magnet_x, float magnet_y) {

    float diff_x = this->position.x - magnet_x;
    float diff_y = this->position.y - magnet_y;

    int acc_x = 1;
    int acc_y = 1;

    if(diff_x > 0){
        acc_x = -1;
    }else{
        acc_x = 1;
    }

    if(diff_y > 0){
        acc_y = -1;
    }else{
        acc_y = 1;
    }

    this->position.x += acc_x * 0.0020f;
}

// void Player::start_ring_timer

bool Player::move_along_ring() {
    // this->position.y += 0.3;
    current_ring -= GAME_SPEED;
    this->position.x = sqrt(abs(RING_SIZE * RING_SIZE - this->position.y * this->position.y)) + current_ring;
    
}

void Player::initiate_ring_timer(float now_time){
    // cout << "timer_initiated\n";
    this->ring_check = now_time;
}

bool Player::ring_timer(){
    if(nowTime - this->ring_check > 1.0f){
        this->ring_check = nowTime;
        return true;
    }
    return false;
}

void Player::inc_score(int increment) {
    this->score += increment;
    // cout << this->score << "\n";
}

void Player::inc_velocity() {
    if(this->velocity.x < 0.2f){
        this->velocity.x += 0.1f;
    }
    this->before = nowTime;
}

void Player::restore_velocity_x(float interval) {
    if(nowTime - this->before > interval){ 
        this->velocity.x = 0.1f;
    }
}

void Player::restore_velocity_y(float interval) {
    if(nowTime - this->before > interval){ 
        this->velocity.y = 0.2f;
    }
}

bounding_box_t Player::get_box(){
    return this->box;
}
