#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <utility>

#include "Window.h"
#include "Object.h"
#include "Shader.h"
#include "Camera.h"
#include "Generator.h"
#include "Gaussian.h"
#include "QRMethod.h"
#include "BackSubstitution.h"
#include "MYMath.h"
#include "Line.h"

class Application{
public:
    Application(Window *wnd_ptr);
    Application();
    ~Application();
    void run();
private:
    Window *m_window;
    Object *m_cube;
    Shader *m_shader;
    Camera *m_camera;
    generator *m_gen;
    Gaussian m_gauss;
    QRMethod m_qr, m_qrO;
    std::vector< std::pair<int, double> > gauT, qrT, qrOT; //Two Norm [degree, err]
    std::vector< std::pair<int, double> > gauI, qrI, qrOI; //Inf Norm [degree, err]
    void Init();
    void Normalization( 
        std::vector< std::pair<int, double> > &m1,
        std::vector< std::pair<int, double> > &m2,
        std::vector< std::pair<int, double> > &m3
    );
    void drawTest();
    void printval(std::string str, std::vector<double> &data);
    void processCamera(float delta_time);
    void processInput();
    void testGen();
    void NewFunction(std::vector<std::pair<int, double>> &gauT);
};