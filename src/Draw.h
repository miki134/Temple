#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Draw
{
public:
    static void rotatingTwoToruses(float angle);
    static void rotatingSolarSystem(float angle);
    static void rotatingTwoTorusesWithSquares(float angle);
    static void rotatingTwoTorusesWithSquaresScaled(float angle);
    static void rotatingSixToruses(float angle);
    static void rotatingSixTorusesVertical(float angle);
    static void car(float angle);
    static void carWithTurningWeels(GLFWwindow* window, float angle, float turn, float wheelAngle);
};

