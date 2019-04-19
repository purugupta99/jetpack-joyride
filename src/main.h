#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>

#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define DIAMOND 1
#define SPEED_UP 2

struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    float x;
    float y;
    float width;
    float height;
};

bool detect_collision(bounding_box_t a, bounding_box_t b, float rotation);

extern float screen_zoom, screen_center_x, screen_center_y;
void reset_screen();

// ---- Colors ----
extern const color_t COLOR_BLACK;
extern const color_t COLOR_WHITE;
extern const color_t COLOR_GRAY;
extern const color_t COLOR_RED;
extern const color_t COLOR_ORANGE_RED;
extern const color_t COLOR_DARK_RED;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLUE;
extern const color_t COLOR_PURPLE;
extern const color_t COLOR_LIGHT_BLACK;
extern const color_t COLOR_TEAL;
extern const color_t COLOR_YELLOW;
extern const color_t COLOR_WOOD;
extern const color_t COLOR_SKIN;
extern const color_t COLOR_JETPACK;
extern const color_t COLOR_CREAM;
extern const color_t COLOR_FIRE;
extern const color_t COLOR_DARK_FIRE;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_BACKDROP;

extern int NO_PLATFORM;
extern const int COIN_EDGES;
extern int NO_COIN;
extern int NO_BACKDROP;

extern int LEVEL;
extern float GAME_SPEED;
extern const float GRAVITY;
extern const float GROUND_LEVEL;
extern const float TOP_LEVEL;
extern const float LEFT_BOUNDARY;
extern const float RIGHT_BOUNDARY;
extern const float TOP;
extern const float BOTTOM;
extern const float RIGHT;
extern const float LEFT;

extern const float PLAYER_HEIGHT;
extern const float PLAYER_WIDTH;

extern const float DRAGON_HEIGHT;
extern const float DRAGON_WIDTH;

extern const float PLATFORM_LENGTH;
extern const float PLATFORM_HEIGHT;

extern const float COIN_SIZE;
extern const float COIN_DIST;
extern const float COIN_HEIGHT_1;
extern const float COIN_HEIGHT_2;
extern const float COIN_HEIGHT_3;

extern const float RING_SIZE;
extern const float INNER_RING_SIZE;
extern const float RING_DIST;
extern const int RING_EDGES;

extern const float POWERUP_SIZE;
extern const float POWERUP_DIST;

extern const float BALLOON_SIZE;
extern const int BALLOON_EDGES;
extern int NO_BALLOON;
extern float lastTime_balloon;

extern const float BULLET_SIZE;
extern const int BULLET_EDGES;
extern int NO_BULLET;
extern float lastTime_bullet;

extern const float MAGNET_SIZE;
extern const int MAGNET_EDGES;
// extern float nowTime_balloon;

extern float nowTime;

extern float lastTime_shield;
// extern float nowTime_shield;

extern const float ENEMY_FIRE_LENGTH;
extern const float ENEMY_FIRE_SIZE;
extern const float ENEMY_FIRE_HEIGHT_1;
extern const float ENEMY_FIRE_HEIGHT_2;
extern const float ENEMY_FIRE_HEIGHT_3;
extern float ENEMY_FIRE_DIST;

extern const float BACKDROP_LENGTH;
extern const float BACKDROP_DIST;

extern float x_coord_backdrop;
extern float x_coord_coin;
extern float x_coord_platform;
extern float x_coord_enemy_fire;

extern int TOTAL_BACKDROP;
extern int TOTAL_COIN;
extern int TOTAL_POWERUP;
extern int TOTAL_PLATFORM;
extern int TOTAL_ENEMY_FIRE;
extern int TOTAL_RING;

extern const float BOOMERANG_FALL;
extern const float BOOMERANG_HEIGHT;

extern const int SCORE_FIRE;
extern const int SCORE_COIN;
extern const int SCORE_BOOMERANG;
extern const int SCORE_BALLOON;
extern const int SCORE_SHIELD;
extern const int SCORE_DIAMOND;
extern const int SCORE_BULLET;

extern float current_ring;

extern int ticks;

extern bool trigger;
extern bool shield_trigger;
extern bool in_ring;
extern bool check_ring;

#endif
