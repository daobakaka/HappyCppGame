#include "Controller.h"
using namespace Game;
Controller* Controller::instance = nullptr;  // ����Դ�ļ��г�ʼ����̬��Ա����,������Ҫ�������ⲿ���У������������������������ڵļ��𣬺�������ͬ�⼶��
//�����Ƕ���ָ�뷽����д����������һ��ָ��Controller��ָ�룬��Ҫ��ʾ����
Controller::Controller()
    : position(0.0f, 0.0f, 3.0f),  // λ�ó�ʼ��
    front(0.0f, 0.0f, -1.0f),     // ǰ��������ʼ��
    up(0.0f, 1.0f, 0.0f),        // ��������ʼ��
    pitch(0.0f), yaw(-0.0f),    // ������ƫ���ǳ�ʼ��
    rightMousePressed(false),    // ����Ҽ���ʼ��Ϊδ����
    lastX(0.0), lastY(0.0),     // ����ʼλ��
    tempX(0.0), tempY(0.0),     // ��ʱƫ��λ��
    mouseMovesContinuously(false), // ��갴��ʱ���ƶ���־
    windowWidth(2400), windowHeight(1200),  // ��Ļ�ߴ��ʼ��
    fov(45), aspect(windowWidth/windowHeight), nearPlane(0.1f), farPlane(1000.0f)
{
    view = glm::lookAt(position, position + front, up);
    projection = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);//��ʼ��
    instance = this;  // �����ĳ�ʼ��
}

Controller::~Controller()
{  
}
Controller* Controller::GetInstance() {
    if (instance == nullptr) {
        instance = new Controller();
    }
    return instance;
}

void Controller::ProcessInput(GLFWwindow* window, glm::vec3& objectPosition)
{
    // ��鰴������
    float moveSpeed = 0.1f;  // �����ƶ����ٶ�

    // �������������������
    glm::vec3 right = glm::normalize(glm::cross(front, up));  // ��������

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        objectPosition += front * moveSpeed;  // W��������ǰ������ǰ��
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        objectPosition -= front * moveSpeed;  // S��������ǰ����������
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        objectPosition -= right * moveSpeed;  // A��������������������
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        objectPosition += right * moveSpeed;  // D��������������������
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        objectPosition += up * moveSpeed;  // SPACE���������������������ƶ�
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        objectPosition -= up * moveSpeed;  // X���������������������ƶ�
    }

}

void Controller::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // ������겢ץȡ        
            rightMousePressed = true;
            if (mouseMovesContinuously)
            {
                glfwGetCursorPos(window, &tempX, &tempY);
                mouseMovesContinuously = false;//�����ʱ���¼һ��λ��
                lastX = static_cast<float>(tempX - windowWidth / 2.0);
                lastY = static_cast<float>(windowHeight / 2.0 - tempY); // Y�ᷴ����Ļ�Ϸ��Ǹ�����
            }
        }
        else if (action == GLFW_RELEASE) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // �ָ������
            rightMousePressed = false;
            mouseMovesContinuously = true;//�ɿ�����ʱ��ָ�ֵ
        }
    }
}

void Controller::MouseButtonFun(GLFWwindow* window)//�ֶ����Է�����ȡ��GLAPI����
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // ������겢ץȡ        
        rightMousePressed = true;
        if (mouseMovesContinuously)
        {
            glfwGetCursorPos(window, &tempX, &tempY);
            mouseMovesContinuously = false;//�����ʱ���¼һ��λ��
            lastX = static_cast<float>(tempX - windowWidth / 2.0);
            lastY = static_cast<float>(windowHeight / 2.0 - tempY); // Y�ᷴ����Ļ�Ϸ��Ǹ�����
        }
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // �ָ������       
        rightMousePressed = false;
        mouseMovesContinuously = true;//�ɿ�����ʱ��ָ�ֵ
    }
}

void Controller::ProcessMouseInput(GLFWwindow* window, float& pitch, float& yaw, bool& rightMousePressed)
{

    if (rightMousePressed) {  // ֻ�а�ס�Ҽ�ʱ�Ž�����ת

        yaw = 0;//Ҫ�ȹ��㣬��Ϊ���е���ͼ�����Ѿ����������
        pitch = 0;

        // std::cout << width<< "and" << height << std::endl;

         // ��ȡ��ǰ����λ��
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);//��ȡ��׼����

        if ((xpos - tempX) * (xpos - tempX) + (ypos - tempY) * (ypos - tempY) > 1.0f)//һ�ε���ж�ֻ�в����ʱ�����ƶ���Ҳ��ʱ�ƶ����ʱ���ƶ�
        {

            // ������������Ļ���ĵ�ƫ����,������д��OPENGL��û��ֱ�ӵ�API
            float offsetX = static_cast<float>(xpos - windowWidth / 2.0);  // ����Ļ����Ϊԭ��
            float offsetY = static_cast<float>(windowHeight / 2.0 - ypos); // Y�ᷴ����Ļ�Ϸ��Ǹ�����
            // std::cout << offsetX << "and" << offsetY << std::endl;//�������ֵ��׼ȷ��
              // ������ת��������
            float sensitivity = 0.01f;
            // usingn = (offsetY > 0) ? 1 : -1;

             // ������ת�Ƕ�
            yaw += (offsetX - lastX) * sensitivity;   // ˮƽ��ת����Y����ת
            pitch += (  offsetY-lastY) * sensitivity; // ��ֱ��ת����X����ת
          //  std::cout << pitch << std::endl;//������ ������ÿһ֡����ӡ0��
            // ���Ƹ����Ƕȣ����ⷭת
            if (pitch > 89.0f) pitch = 89.0f;
            if (pitch < -89.0f) pitch = -89.0f;

            // �������λ��
            lastX = offsetX;
            lastY = offsetY;
        }
        // glfwSetCursorPos(window, width / 2.0, height / 2.0); // ÿ���ƶ������λ������Ϊ��Ļ����
    }
}

void Controller::FrameControlMethod(GLFWwindow* window)
{
    MouseButtonFun(window);
    ProcessInput(window, position);
    ProcessMouseInput(window, pitch, yaw, rightMousePressed);
}

glm::mat4 Controller::GetViewMatrix()
{    
    
    glm::mat4 cameraRotation = glm::rotate(glm::mat4(1.0f), glm::radians(3*pitch), glm::vec3(1.0f, 0.0f, 0.0f)); //��������X����ת 
    cameraRotation = glm::rotate(cameraRotation, glm::radians(3*yaw), glm::vec3(0.0f, 1.0f, 0.0f)); // ƫ������Y����ת
  
    if (rightMousePressed)
        front = glm::normalize( glm::vec3(cameraRotation * glm::vec4(front, 0.0f)));//ÿ���������һ��
    return  glm::lookAt(position, position + front, up);
}

glm::mat4 Controller::GetProjectionMatrix()
{
    return projection = glm::perspective(glm::radians(fov), windowWidth / float(windowHeight), nearPlane, farPlane);//���¼���ͶӰ����
}
