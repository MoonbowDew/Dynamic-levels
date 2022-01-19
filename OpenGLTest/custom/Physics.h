#pragma once
#include "../custom/GameObject.h"
#include <GLFW/glfw3.h>

    static float velocity = 0.0001f;

    static double lastTime = 0;

    bool CheckCollision(std::shared_ptr <GameObject>& one, std::shared_ptr <GameObject>& two); // AABB - AABB collision

    bool CheckIntersection(std::shared_ptr <GameObject>& one, std::shared_ptr <GameObject>& two); // AABB - AABB intersection

    void Gravity(std::shared_ptr <GameObject>& Dashie, double velocity);