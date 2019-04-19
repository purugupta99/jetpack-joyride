#include "timer.h"
#include <GLFW/glfw3.h>
// #include <iostream>

Timer::Timer(float interval) {
    prev = glfwGetTime();
    this->interval = interval;
}

bool Timer::processTick() {
    float cur = glfwGetTime();
    // std::cout << cur << " " << prev << " \n";
    if (cur - prev >= interval) {
        prev = cur;
        return true;
    } else
        return false;
}
