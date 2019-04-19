#include <unistd.h>
#include "main.h"
#include "timer.h"
#include "player.h"
#include "coin.h"
#include "platform.h"
#include "enemy_fire.h"
#include "background.h"
#include "boomerang.h"
#include "balloon.h"
#include "magnet.h"
#include "powerup.h"
#include "ring.h"
#include "dragon.h"
#include "segmentdisplay.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

int LEVEL;
float GAME_SPEED;
const float GRAVITY = -0.01f;
const float GROUND_LEVEL = -3.5f;
const float TOP_LEVEL = 3;
const float LEFT_BOUNDARY = -3.25f;
const float RIGHT_BOUNDARY = 3.25f;
const float BOTTOM = -4;
const float TOP = 4;
const float LEFT = -4;
const float RIGHT = 4;

const float PLAYER_HEIGHT = 1.0f;
const float PLAYER_WIDTH = 0.6f;

const float DRAGON_HEIGHT = 1.75f;
const float DRAGON_WIDTH = 2.4f;

const float PLATFORM_LENGTH = 1.0f;
const float PLATFORM_HEIGHT = (GROUND_LEVEL-BOTTOM);
int TOTAL_PLATFORM = 1200;
int NO_PLATFORM = 0;

const float COIN_SIZE = 0.125f;
const float COIN_DIST = 0.375f;
const float COIN_HEIGHT_1 = -2.0f;
const float COIN_HEIGHT_2 = 0.0f;
const float COIN_HEIGHT_3 = 2.0f;
const int COIN_EDGES = 50;
int TOTAL_COIN = 400;
int NO_COIN = 0;

const float RING_SIZE = 2.0f;
const float INNER_RING_SIZE = 1.9f;
const float RING_DIST = 30.0f;
const int RING_EDGES = 40;
int TOTAL_RING = 10;

const float POWERUP_SIZE = 0.2f;
const float POWERUP_DIST = 15.0f;
int TOTAL_POWERUP = 20;

const float BALLOON_SIZE = 0.25f;
const int BALLOON_EDGES = 50;
int NO_BALLOON = 0;
float lastTime_balloon = -1.0f;

const float BULLET_SIZE = 0.15f;
const int BULLET_EDGES = 50;
int NO_BULLET = 0;
float lastTime_bullet = -1.0f;

const float MAGNET_SIZE = 0.375f;
const int MAGNET_EDGES = 50;

float lastTime_shield = -30.0f;
// float nowTime_shield = 0.0f;

const float ENEMY_FIRE_LENGTH = 1.0f;
const float ENEMY_FIRE_SIZE = 0.1f;
int TOTAL_ENEMY_FIRE = 50;
const float ENEMY_FIRE_HEIGHT_1 = -2.0f;
const float ENEMY_FIRE_HEIGHT_2 = 0.0f;
const float ENEMY_FIRE_HEIGHT_3 = 2.0f;
float ENEMY_FIRE_DIST;

const float BACKDROP_LENGTH = 4.0f;
const float BACKDROP_DIST = 2.0f;
int TOTAL_BACKDROP = 150;
int NO_BACKDROP = 0;

const float BOOMERANG_FALL = 0.025f;
const float BOOMERANG_HEIGHT = 3.0f;

const int SCORE_FIRE = -10;
const int SCORE_COIN = 5;
const int SCORE_BOOMERANG = -20;
const int SCORE_BALLOON = 10;
const int SCORE_SHIELD = 10;
const int SCORE_DIAMOND = 50;
const int SCORE_BULLET = -50;

float x_coord_backdrop = 0.0f;
float x_coord_coin = 0;
float x_coord_platform = LEFT+PLATFORM_LENGTH/2.0f;
float x_coord_enemy_fire = 1.0f;

float current_ring = 0;

int ticks = 0;
int tick_repeat = 720;

float x_travelled = 0; 

bool trigger = false;
bool shield_trigger = false;
bool in_ring = false;
bool check_win = false;
float nowTime = 0.0f;

/**************************
* Customizable functions *
**************************/

Player barry;
Dragon drogon;
Boomerang boomer;
Magnet magnet;
Segmentdisplay score;

vector<Powerup> powerup_vector;
vector<Background> backdrop_vector;
vector<Platform> platform_vector;
vector<Coin> coin_vector;
vector <Enemy_Fire> enemy_fire_vector;
vector <Balloon> balloon_vector;
vector <Bullet> bullet_vector;
vector <Ring> ring_vector;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for(int i=0;i<TOTAL_BACKDROP;i++)
    {
        if(abs(backdrop_vector[i].get_x()) < 7.0f){
            backdrop_vector[i].draw(VP);
        }
    }
    
    for(int i=0;i<TOTAL_PLATFORM;i++)
    {
        if(abs(platform_vector[i].get_x()) < 5.0f){
            platform_vector[i].draw(VP);
        }
    }
    
    if(magnet.get_visibility()){
        magnet.draw(VP);
    }

    for(int i=0;i<TOTAL_RING;i++)
    {
        if(ring_vector[i].get_visibility() && abs(ring_vector[i].get_x()) < 5.0f){
            ring_vector[i].draw(VP);
        }
    }

    barry.draw(VP,trigger);
    if(drogon.get_visibility()){
        drogon.draw(VP);
    }

    for(int i=0;i<TOTAL_COIN;i++)
    {
        if(coin_vector[i].get_visibility() && abs(coin_vector[i].get_x()) < 5.0f){
            coin_vector[i].draw(VP);
        }
    }

    for(int i=0;i<TOTAL_POWERUP;i++)
    {
        if(powerup_vector[i].get_visibility() && abs(powerup_vector[i].get_x()) < 5.0f){
            powerup_vector[i].draw(VP);
        }
    }

    if(boomer.get_visibility()){
        boomer.draw(VP);
    }

    // int temp_balloon = NO_BALLOON;
    for(int i=0;i<NO_BALLOON;i++)
    {
        // if(abs(platform_vector[i].get_x()) < 5.0f){
        //     platform_vector[i].draw(VP);
        // }
        if(balloon_vector[i].get_visibility()){
            balloon_vector[i].draw(VP);
        }

        if(balloon_vector[i].get_y() < BOTTOM)
        {
            balloon_vector.erase(balloon_vector.begin() + i);
            NO_BALLOON--;
            // temp_balloon--;
        }
    }

    for(int i=0;i<NO_BULLET;i++)
    {
        // if(abs(platform_vector[i].get_x()) < 5.0f){
        //     platform_vector[i].draw(VP);
        // }
        if(bullet_vector[i].get_visibility()){
            bullet_vector[i].draw(VP);
        }

        if(bullet_vector[i].get_y() < LEFT)
        {
            bullet_vector.erase(bullet_vector.begin() + i);
            NO_BALLOON--;
            // temp_balloon--;
        }
    }
    // NO_BALLOON = temp_balloon;
    
    // vector <Coin> ::iterator low;
    // low=lower_bound (coin_vector.begin(), coin_vector.end(), 0);
    // cout << low - coin_vector.begin() << "\n";

    for(int i=0;i<TOTAL_ENEMY_FIRE;i++)
    {
        if(enemy_fire_vector[i].get_visibility() && abs(enemy_fire_vector[i].get_x()) < 5.0f){
            enemy_fire_vector[i].draw(VP);
        }
    }

    score.draw(VP);

}

void tick_input(GLFWwindow *window) {

    // nowTime_balloon = glfwGetTime();
    // nowTime_shield = glfwGetTime();
    nowTime = glfwGetTime();
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int balloon_throw  = glfwGetKey(window, GLFW_KEY_B);
    int shield_initiate  = glfwGetKey(window, GLFW_KEY_S);
    int time_balloon = (nowTime - lastTime_balloon > 1.0f);
    int time_shield = (nowTime - lastTime_shield > 30.0f);
    if (right) {
        // cout << "FORWARD\n";
        barry.move_forward();
    }
    if(left) {
        // cout << "BACKWARD\n";
        barry.move_backward();
    }
    if(up && !in_ring) {
        // cout << "UP\n";
        trigger = true;
        barry.move_up();
    }
    else{
        trigger = false;
    }
    if(shield_initiate && time_shield){
        shield_trigger = true;
        lastTime_shield = nowTime;
    }

    if(nowTime - lastTime_shield > 10.0f){
        shield_trigger = false;
    }

    if(balloon_throw && time_balloon ){
        // cout << "balloon thrown\n";
        balloon_vector.push_back(Balloon(barry.get_x(),barry.get_y(),barry.get_abs_x(),barry.get_abs_y(),COLOR_BLUE));
        NO_BALLOON++;
        lastTime_balloon = nowTime;
    }
}

void tick_elements(int ticks) {
    for(int i=0;i<TOTAL_BACKDROP;i++)
    {
        if(backdrop_vector[i].get_x() < -8.0f){
            backdrop_vector.erase(backdrop_vector.begin()+i);
            TOTAL_BACKDROP--;
        }
        backdrop_vector[i].tick();
    }
    barry.tick();
    drogon.tick();
    
    for(int i=0; i<NO_BALLOON; i++)
    {
        balloon_vector[i].tick();
    }

    for(int i=0; i<NO_BULLET; i++)
    {
        bullet_vector[i].tick();
    }

    for(int i=0; i<TOTAL_RING; i++)
    {
        if(ring_vector[i].get_x() < -8.0f){
            ring_vector.erase(ring_vector.begin()+i);
            TOTAL_RING--;
        }
        ring_vector[i].tick();
    }

    for(int i=0;i<TOTAL_PLATFORM;i++)
    {
        if(platform_vector[i].get_x() < -6.0f){
            platform_vector.erase(platform_vector.begin()+i);
            TOTAL_PLATFORM--;
        }
        platform_vector[i].tick();
    }
    for(int i=0;i<TOTAL_COIN;i++)
    {
        if(coin_vector[i].get_x() < -5.0f){
            coin_vector.erase(coin_vector.begin()+i);
            TOTAL_COIN--;
        }
        coin_vector[i].tick();
    }

    for(int i=0;i<TOTAL_POWERUP;i++)
    {
        if(powerup_vector[i].get_x() < -6.0f){
            powerup_vector.erase(powerup_vector.begin()+i);
            TOTAL_POWERUP--;
        }
        powerup_vector[i].tick();
    }

    // cout << barry.get_box().x << "\n";
    for(int i=0;i<TOTAL_ENEMY_FIRE;i++)
    {
        if(enemy_fire_vector[i].get_x() < -6.0f){
            enemy_fire_vector.erase(enemy_fire_vector.begin()+i);
            TOTAL_ENEMY_FIRE--;
        }
        enemy_fire_vector[i].tick(ticks);
    }
    boomer.tick(ticks);
    score.update(barry.get_score());

    for(int i=0;i<TOTAL_COIN;i++)
    {
        // cout << barry.get_box().x << " " << coin_vector[i].get_box().x << "\n";
        bool collision = detect_collision(barry.get_box(),coin_vector[i].get_box(), 0);
        // cout << collision << "\n";
        if(coin_vector[i].get_visibility() && collision)
        {
            coin_vector[i].picked_up();
            barry.inc_score(SCORE_COIN);
        }
    }

    for(int i=0;i<NO_BULLET;i++)
    {
        // cout << barry.get_box().x << " " << coin_vector[i].get_box().x << "\n";
        bool collision = detect_collision(barry.get_box(),bullet_vector[i].get_box(), 0);
        // cout << collision << "\n";
        if(bullet_vector[i].get_visibility() && collision && !shield_trigger)
        {
            bullet_vector[i].collided();
            barry.inc_score(SCORE_BULLET);
        }
    }

    for(int i=0;i<TOTAL_RING;i++)
    {
        // cout << barry.get_box().x << " " << coin_vector[i].get_box().x << "\n";
        bool collision = detect_collision(barry.get_box(),ring_vector[i].get_box(), 0);
        // cout << collision << "\n";
        if(ring_vector[i].get_visibility() && collision && ring_vector[i].touched())
        {
            // coin_vector[i].picked_up();
            // barry.inc_score(SCORE_COIN);
            barry.initiate_ring_timer(nowTime);
            current_ring = ring_vector[i].get_x();
            in_ring = true;
            // cout << "Ring Collision\n";
        }
    }

    for(int i=0;i<TOTAL_POWERUP;i++)
    {
        // cout << barry.get_box().x << " " << coin_vector[i].get_box().x << "\n";
        bool collision = detect_collision(barry.get_box(),powerup_vector[i].get_box(), 0);
        // cout << collision << "\n";
        if(powerup_vector[i].get_visibility() && collision)
        {
            powerup_vector[i].picked_up();

            if(powerup_vector[i].get_type() == DIAMOND){
                barry.inc_score(SCORE_DIAMOND);
            }

            if(powerup_vector[i].get_type() == SPEED_UP){
                barry.inc_velocity();
            }
    }

    collision = detect_collision(barry.get_box(),boomer.get_box(),0);
    if(boomer.get_visibility() && collision && !in_ring)
    {
        if(shield_trigger){
            boomer.collided();
            barry.inc_score(SCORE_SHIELD);
        }
        else if(boomer.touched(glfwGetTime())){
            barry.inc_score(SCORE_BOOMERANG);
        }
    }

    for(int i=0;i<TOTAL_ENEMY_FIRE;i++)
    {
        // cout << barry.get_box().x << " " << coin_vector[i].get_box().x << "\n";
        bool collision = detect_collision(barry.get_box(),enemy_fire_vector[i].get_box(),enemy_fire_vector[i].get_rotation());
        // cout << collision << "\n";
        if( enemy_fire_vector[i].get_visibility() && collision && !in_ring)
        {
            if(shield_trigger){
                enemy_fire_vector[i].collided();
                barry.inc_score(SCORE_SHIELD);
            }
            else if(enemy_fire_vector[i].touched(glfwGetTime())){
                barry.inc_score(SCORE_FIRE);
            }
            // cout << "enemy_fire_collided" << "\n";
        }
    }

    // int broken = 0;
    for(int i=0;i<NO_BALLOON;i++)
    {
        for(int j=0;j<TOTAL_ENEMY_FIRE;j++)
        {
            bool collision = detect_collision(balloon_vector[i].get_box(),enemy_fire_vector[j].get_box(),enemy_fire_vector[j].get_rotation());
           
            if(enemy_fire_vector[i].get_visibility() && collision){
                // cout << i << " "<< balloon_vector[i].get_x() << " " << balloon_vector[i].get_box().x << " " << j <<  " " << enemy_fire_vector[j].get_box().x << "\n";
                // balloon_vector[i].collided();
                enemy_fire_vector[j].collided();
                // broken++;
            }
        }
    }

    for(int i=0;i<NO_BALLOON;i++)
    {
        bool collision = detect_collision(balloon_vector[i].get_box(),drogon.get_box(),0);
        
        if(drogon.get_visibility() && collision && drogon.touched()){
            // cout << i << " "<< balloon_vector[i].get_x() << " " << balloon_vector[i].get_box().x << " " << j <<  " " << enemy_fire_vector[j].get_box().x << "\n";
            // balloon_vector[i].collided();
            drogon.collided();
            // broken++;
        }
        
    }

    

    // if(magnet.check_counter_30()){
    //     magnet.make_visible();
    // }

    if(magnet.get_visibility())
    {
        if(magnet.check_counter_5()){
            magnet.make_invisible();
            barry.restore_velocity_y(0.0f);
        }
        if(!in_ring){
            barry.magnet_effect(magnet.get_x(), magnet.get_y());
        }
    }
    
    // barry.inc_score(SCORE_BALLOON * broken);
    // camera_rotation_angle += 1;

    if(check_win){
        if(barry.get_score() <= 0){
            cout << "YOU LOSE\n";
            exit(0);
        }

        if(!drogon.get_visibility()){
            cout << "YOU WIN\n";  
            cout << "Your Final Score: " << barry.get_score();
            exit(0); 
        }
    }
}
}
void coin_initializer(){
    
    int i=0;
    float current = x_coord_coin;
    // while(x_coord_backdrop < current + x_travelled)
    while(i<TOTAL_COIN)
    {
        int random = rand() % 3;
        int random_2 = rand() % 3;

        int diff = TOTAL_COIN - i;

        // if(diff < 10)
        // {

        // }
        if(diff == 10 || diff == 20){
            random = 2;
        }

        float height;
        if(random_2 == 0){
            height = COIN_HEIGHT_1;
        }else if(random_2 == 1){
            height = COIN_HEIGHT_2;
        }else if(random_2 == 2){
            height = COIN_HEIGHT_3;
        }

        if(random == 0)
        {
            //0000000000
            for(int j=0;j<10;j++)
            {
                coin_vector.push_back(Coin(x_coord_coin,height,COLOR_YELLOW));
                x_coord_coin += COIN_DIST;
                i+=1;
            }
        }
        else if(random == 1)
        {
            //0000000000
            //0000000000
            //0000000000
            float temp = x_coord_coin;
            height += COIN_DIST;
            for(int k=0;k<3;k++)
            {
                for(int j=0;j<10;j++)
                {
                    coin_vector.push_back(Coin(x_coord_coin,height,COLOR_YELLOW));
                    x_coord_coin += COIN_DIST;
                    i+=1;
                }
                x_coord_coin = temp;
                height -= COIN_DIST;
            }
        }
        else if(random == 2)
        {
            //0
            // 0
            //  0
            //   0
            //    0
            height = COIN_HEIGHT_3;
            
            for(int j=0;j<10;j++)
            {
                coin_vector.push_back(Coin(x_coord_coin,height,COLOR_YELLOW));
                x_coord_coin += COIN_DIST;
                height -= COIN_DIST;
                i+=1;
            }
        }

        // cout << i << "\n";
        x_coord_coin += 15*COIN_DIST;
    }
}

void platform_initializer(){
    
    float current = x_coord_platform;
    // while(x_coord_platform < current + x_travelled)
    int i=0;
    while(i<TOTAL_PLATFORM)
    {
        // cout << "platform" << "\n";
        platform_vector.push_back(Platform(x_coord_platform,BOTTOM+PLATFORM_HEIGHT/2.0f,COLOR_TEAL));
        x_coord_platform += PLATFORM_LENGTH;
        i++;
    }
}

void backdrop_initializer(){
    
    float current = x_coord_backdrop;
    int i=0;
    // while(x_coord_backdrop < current + x_travelled)
    while(i<TOTAL_BACKDROP)
    {
        backdrop_vector.push_back(Background(x_coord_backdrop,0.0f,COLOR_BACKDROP));
        x_coord_backdrop += 2*BACKDROP_LENGTH + BACKDROP_DIST;
        i++;
    }
}

void enemy_fire_initializer(){
    
    int i=0;
    // while(x_coord_backdrop < current + x_travelled)
    while(i<TOTAL_ENEMY_FIRE)
    {
        // float height;
        bool movable;
        int random = rand() % 4;
        // int random_2 = rand() % 3;
        int random_3 = rand() % 2;

        if(random_3 == 0){
            movable = false;
        }else if(random_3 == 1){
            movable = true;
        }

        // if(random_2 = 0){
        //     height = ENEMY_FIRE_HEIGHT_1;
        // }else if(random_2 = 1){
        //     height = ENEMY_FIRE_HEIGHT_2;
        // }else if(random_2 = 2){
        //     height = ENEMY_FIRE_HEIGHT_3;
        // }

        if(random == 0){
           enemy_fire_vector.push_back(Enemy_Fire(x_coord_enemy_fire,ENEMY_FIRE_HEIGHT_1,-45.0f,false,COLOR_FIRE));
        }else if(random == 1){
           enemy_fire_vector.push_back(Enemy_Fire(x_coord_enemy_fire,ENEMY_FIRE_HEIGHT_3,45.0f,false,COLOR_FIRE));
        }else if(random == 2){
           enemy_fire_vector.push_back(Enemy_Fire(x_coord_enemy_fire,ENEMY_FIRE_HEIGHT_2,0.0f,movable,COLOR_FIRE));
        }else if(random == 3){
           enemy_fire_vector.push_back(Enemy_Fire(x_coord_enemy_fire,ENEMY_FIRE_HEIGHT_2,90.0f,movable,COLOR_FIRE));
        }

        // enemy_fire_vector.push_back(Enemy_Fire(x_coord_enemy_fire,ENEMY_FIRE_HEIGHT_2,90.0f,true,COLOR_FIRE));

        x_coord_enemy_fire += ENEMY_FIRE_DIST;
        i++;
    }
}

void boomerang_initializer(float offset){
    boomer = Boomerang(RIGHT, BOOMERANG_HEIGHT, offset, COLOR_WOOD);
    // boomer = Boomerang(0, 0, COLOR_WOOD);
}

void magnet_initializer(){

    int random = rand() % 2;
    if(random == 0){
        magnet = Magnet(2.0f, 3.0f, COLOR_GRAY);
    }
    else if(random == 1){
        magnet = Magnet(-2.0f, 3.0f, COLOR_GRAY);
    }
    // boomer = Boomerang(0, 0, COLOR_WOOD);
}

void powerup_initializer(){
    float x_coord_powerup = 3.0f;
    for(int i=0;i<TOTAL_POWERUP;i++){
        int random = rand() % 3;
        int powerup_selector = rand() % 2 + 1;

        float height;
        if(random == 0){
            height = COIN_HEIGHT_1;
        }else if(random == 1){
            height = COIN_HEIGHT_2;
        }else if(random == 2){
            height = COIN_HEIGHT_3;
        }

        powerup_vector.push_back(Powerup(x_coord_powerup, height, powerup_selector, COLOR_RED));
        x_coord_powerup += POWERUP_DIST;
    }
}

void ring_initializer(){
    float x_coord_ring = 4.5f;
    float height = 0.0f;
    for(int i=0;i<TOTAL_RING;i++){
        ring_vector.push_back(Ring(x_coord_ring, height, COLOR_GREEN));
        x_coord_ring += RING_DIST;
    }

}

void bullet_initializer(){
    // cout << bullet_vector.size() << "\n";
    for(int i =0;i<bullet_vector.size();i++)
    {
        // cout << i << " " << bullet_vector[i].get_x() << " " << bullet_vector[i].get_y() << "\n";  
    }
    bullet_vector.push_back(Bullet(drogon.get_x()-1.2f,drogon.get_y()+0.5f,drogon.get_abs_x(),drogon.get_abs_y(),COLOR_FIRE));
    NO_BULLET++;
}

bool sortFunc(Coin a, Coin b) 
{ 
    return a.get_x() < b.get_x(); 
} 

void erase_vector(){
    platform_vector.clear();
    backdrop_vector.clear();
    coin_vector.clear();
}
/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    

    barry = Player(0, GROUND_LEVEL+PLAYER_HEIGHT/2.0f, COLOR_GREEN);
    drogon = Dragon(2.6,0,COLOR_RED);
    
    platform_initializer();
    backdrop_initializer();
    coin_initializer();
    enemy_fire_initializer();
    boomerang_initializer(0.0f);
    powerup_initializer();
    ring_initializer();

    score = Segmentdisplay(0,3.5);
    score.update(0);

    sort(coin_vector.begin(),coin_vector.end(),sortFunc);
    
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable( GL_BLEND );

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    cout << "Enter Level to Play the Game [[1],2]: ";
    cin >> LEVEL;

    if(LEVEL != 1 && LEVEL != 2){
        LEVEL = 1;
    }

    if(LEVEL == 1){
        GAME_SPEED = 0.05f;
        ENEMY_FIRE_DIST = 7.0f;
        TOTAL_COIN = 400;
    } else if (LEVEL == 2){
        GAME_SPEED = 0.10f;
        ENEMY_FIRE_DIST = 4.0f;
        TOTAL_COIN = 200;
    }

    cout << GAME_SPEED << "\n";

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            // NO_BACKDROP = backdrop_vector.size();
            // NO_PLATFORM = platform_vector.size();
            // NO_COIN = coin_vector.size();

            tick_elements(ticks);
            tick_input(window);

            ticks += 1;
            if(ticks % tick_repeat == 0){
                boomerang_initializer((float)ticks * GAME_SPEED);
            }
            if(ticks % 60 == 0 && drogon.get_visibility()){
                bullet_initializer();
            }
            if(ticks % 1200 == 0){
                magnet_initializer();
            }
            if(LEVEL == 1){
                if(ticks == 2400){
                    drogon.birth();
                    check_win = true;
                }
            }
            else if(LEVEL == 2){
                if(ticks == 1800){
                    drogon.birth();
                    check_win = true;
                }
            }
            
            usleep(10000);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b, float rotation) {
    if(rotation == 0)
    {
        return (abs(a.x - b.x) * 2 < (a.width + b.width)) && (abs(a.y - b.y) * 2 < (a.height + b.height));
    }
    else if (rotation > 0)
    {
        float b_x_new = b.x - cos(rotation * M_PI / 180.0f) * (a.y-b.y);
        float b_width_new = abs(cos(rotation * M_PI / 180.0f) * b.width);
        return (abs(a.x - b_x_new) * 2 < (a.width + b.width)) && (abs(a.y - b.y) * 2 < (a.height + b.height));
    }
    else if (rotation < 0)
    {
        float b_x_new = b.x + cos(rotation * M_PI / 180.0f) * (a.y-b.y);
        float b_width_new = abs(cos(rotation * M_PI / 180.0f) * b.width);
        return (abs(a.x - b_x_new) * 2 < (a.width + b.width)) && (abs(a.y - b.y) * 2 < (a.height + b.height));
   }
}


void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
