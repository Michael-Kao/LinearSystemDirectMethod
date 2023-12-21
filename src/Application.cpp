#include "Application.h"

Application::Application(Window *wnd_ptr)
    :   m_window(wnd_ptr) {
    Init();
}

Application::Application() {
    m_window = new Window();
    Init();
}

Application::~Application() {
    glfwTerminate();
}

void Application::Init() {
    m_cube = new Object("assets/objfiles/cube.obj");
    m_shader = new Shader("assets/shaders/basic.vs", "assets/shaders/basic.fs");
    m_camera = new Camera();
    m_gen = new generator();
}

void Application::drawTest() {
    m_shader->bind();
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(m_camera->fov), (float)m_window->getWidth() / (float)m_window->getHeight(), 0.1f, 100.0f);
    view       = m_camera->getLookAt();
    m_shader->setMat4("view", view);
    m_shader->setMat4("projection", projection);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-6.5, 0, 6.5));
    m_shader->setMat4("model", model);
    {//Two Norm
        {
            m_shader->setVec4("color", 1, 0, 0, 1);
            Line m_l(gauT);
            m_l.draw();
        }
        {
            m_shader->setVec4("color", 0, 1, 0, 1);
            Line m_l(qrT);
            m_l.draw();
        }
        {
            m_shader->setVec4("color", 0, 0, 1, 1);
            Line m_l(qrOT);
            m_l.draw();
        }
    }
    if(0){//Infinite Norm
        {
            m_shader->setVec4("color", 1, 0, 0, 1);
            Line m_l(gauI);
            m_l.draw();
        }
        {
            m_shader->setVec4("color", 0, 1, 0, 1);
            Line m_l(qrI);
            m_l.draw();
        }
        {
            m_shader->setVec4("color", 0, 0, 1, 1);
            Line m_l(qrOI);
            m_l.draw();
        }
    }
    m_shader->unbind();
}

void Application::processCamera(float delta_time) {
    if(m_window->isPressed(GLFW_KEY_W)){
        m_camera->updateInput(FORWARD, delta_time);
    }
    if(m_window->isPressed(GLFW_KEY_S)){
        m_camera->updateInput(BACKWARD, delta_time);
    }
    if(m_window->isPressed(GLFW_KEY_A)){
        m_camera->updateInput(LEFT, delta_time);
    }
    if(m_window->isPressed(GLFW_KEY_D)){
        m_camera->updateInput(RIGHT, delta_time);
    }
    if(m_window->isPressed(GLFW_KEY_K)){
        m_camera->updateInput(RPITCH, delta_time);
    }
    if(m_window->isPressed(GLFW_KEY_J)){
        m_camera->updateInput(PITCH, delta_time);
    }
    if(m_window->isPressed(GLFW_KEY_L)){
        m_camera->updateInput(YAW, delta_time);
    }
    if(m_window->isPressed(GLFW_KEY_H)){
        m_camera->updateInput(RYAW, delta_time);
    }
}

void Application::processInput() {
    if(m_window->isPressed(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(m_window->getWindow(), true);
    }
}

void Application::printval(std::string str, std::vector<double> &data) {
        std::cout << str << " : \n";
    for(auto v : data) {
        std::cout << v << std::setw(10);
    }
    std::cout << "\n";
}

void Application::testGen() {
    // int degree = 5;
    for(int degree = 5; degree < 15; ++degree) {
        m_gen->gem_ans(degree, 0.0, 0.2);
        m_gauss.UpTriMtx = m_gen->mtxB;
        m_gauss.b = m_gen->yB;
        m_gauss.gaussian_elimination();
        {
            backSub tmp;
            tmp.back_substitution(m_gauss.UpTriMtx, m_gauss.res, m_gauss.b, m_gauss.UpTriMtx.size());
        }
        m_qr.solver(m_gen->mtxB, m_gen->yB);
        m_qrO.solver(m_gen->mtx, m_gen->y);
        printval("Gaussian new system", m_gauss.res);
        printval("QR Method new system", m_qr.res);
        printval("QR Method original system", m_qrO.res);
        std::cout << "------\n";
        std::vector<double> ans(degree + 1, 1.0);
        {
            Math m_math;
            double two = m_math.TwoNorm(ans, m_gauss.res);
            double inf = m_math.InfiniteNorm(ans, m_gauss.res);
            gauT.push_back(std::make_pair(degree, two));
            gauI.push_back(std::make_pair(degree, inf));
            std::cout << "---Gaussian with degree " << degree << " on new system---\n"
                      << "Two Norm : " << two << "\n"
                      << "Inf Norm : " << inf << "\n"
                      << "------\n";
        }
        {
            Math m_math;
            double two = m_math.TwoNorm(ans, m_qr.res);
            double inf = m_math.InfiniteNorm(ans, m_qr.res);
            qrT.push_back(std::make_pair(degree, two));
            qrI.push_back(std::make_pair(degree, inf));
            std::cout << "---QR Method with degree " << degree << " on new system---\n"
                      << "Two Norm : " << two << "\n"
                      << "Inf Norm : " << inf << "\n"
                      << "------\n";
        }
        {
            Math m_math;
            double two = m_math.TwoNorm(ans, m_qrO.res);
            double inf = m_math.InfiniteNorm(ans, m_qrO.res);
            qrOT.push_back(std::make_pair(degree, two));
            qrOI.push_back(std::make_pair(degree, inf));
            std::cout << "---QR Method with degree " << degree << " on original system---\n"
                      << "Two Norm : " << two << "\n"
                      << "Inf Norm : " << inf << "\n"
                      << "------\n";
        }
    }
}

void Application::Normalization(
    std::vector< std::pair<int, double> > &m1,
    std::vector< std::pair<int, double> > &m2,
    std::vector< std::pair<int, double> > &m3
) {
    double max_val, min_val, ratio;
    max_val = -1; min_val = DBL_MAX;
    for(int i = 0; i < m1.size(); ++i) {
        max_val = std::max(max_val, m1[i].second);
        max_val = std::max(max_val, m2[i].second);
        max_val = std::max(max_val, m3[i].second);
        min_val = std::min(min_val, m1[i].second);
        min_val = std::min(min_val, m2[i].second);
        min_val = std::min(min_val, m3[i].second);
    }
    ratio = 1.0 / (max_val - min_val);
    for(int i = 0; i < m1.size(); ++i) {
        m1[i].second = (m1[i].second - min_val) * ratio;
        m2[i].second = (m2[i].second - min_val) * ratio;
        m3[i].second = (m3[i].second - min_val) * ratio;
    }
}

void Application::run() {
    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;

    testGen();

    Normalization(gauT, qrT, qrOT);
    Normalization(gauI, qrI, qrOI);

    while(!m_window->shouldClose()) {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // glViewport(0, 0, m_window->getWidth()/2, m_window->getHeight()/2);
        m_window->setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        m_window->clear();

        processCamera(deltaTime);
        processInput();

        glViewport(0, 0, m_window->getWidth(), m_window->getHeight());
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        drawTest();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glViewport(0, 0, m_window->getWidth() / 2, m_window->getHeight() / 2);
        // drawTest();
        // glViewport(m_window->getWidth() / 2, m_window->getHeight() / 2, m_window->getWidth() / 2, m_window->getHeight() / 2);
        // drawTest();
        // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // glViewport(m_window->getWidth() / 2, 0, m_window->getWidth() / 2, m_window->getHeight() / 2);
        // drawTest();
        // glViewport(0, m_window->getHeight() / 2, m_window->getWidth() / 2, m_window->getHeight() / 2);
        // drawTest();
        m_window->swapBuffers();
    }
}