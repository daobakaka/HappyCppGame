#include "Light.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace Game;

// ��ʼ����̬����ָ��
LightSpawner* LightSpawner::instance = nullptr;

LightSpawner* LightSpawner::GetInstance() {
    if (instance == nullptr) {
        instance = new LightSpawner();
    }
    return instance;
}

LightSpawner::LightSpawner() {
    // ��ʼ��ȫ��ƽ�й�Ĭ�ϲ���

}

LightSpawner::~LightSpawner() {
    // ������Ҫ�������������
}

CustomPointLight LightSpawner::SpawPointLight(glm::vec3 position, glm::vec3 color, float intensity) {
    CustomPointLight pointLight;
    pointLight.position = position;
    pointLight.color = color;
    pointLight.intensity = intensity;

    // �����ǰ���Դ����δ�ﵽ���ޣ��򱣴浽�ڲ�������
    if (pointLights.size() < 4) {
        pointLights.push_back(pointLight);
    }
    // �������ѡ����Ի�������й�Դ�����ݾ���������
    return pointLight;
}

CustomParallelLight LightSpawner::SpawParallelLight(glm::vec3 direction, glm::vec3 color, float intensity) {
   
    
    parallelLight.direction = glm::normalize(direction);
    parallelLight.color = color;
    parallelLight.intensity = intensity;

    return parallelLight;
}

CustomFlashLight LightSpawner::SpawFlashLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float intensity, float cutoff) {
    CustomFlashLight flashLight;
    flashLight.position = position;
    flashLight.direction = glm::normalize(direction);
    flashLight.color = color;
    flashLight.intensity = intensity;
    flashLight.cutoff = cutoff;
    if (flashLights.size()<4)
    {
        flashLights.push_back(flashLight);
    }
    return flashLight;
}

#pragma region  ��Ⱦ�ű�����

#pragma endregion

/// <summary>
/// ��̬ʵ��ָ��
/// </summary>
LightRender* LightRender::instance = nullptr;

LightRender* LightRender::GetInstance() {
    if (instance == nullptr) {
        instance = new LightRender();
    }
    return instance;
}

LightRender::LightRender() {
    // ���캯��Ϊ��
}

LightRender::~LightRender() {
    // ���б�Ҫ������Դ����
}

void LightRender::RenderLights(GLuint shaderProgram, const Controller* controllerPtr, const Game::LightSpawner* spawnerPtr) {
    if (!controllerPtr || !spawnerPtr) return; // �򵥼��ָ����Ч��

     glUseProgram(shaderProgram);
     // ��ȡ��������ݣ�ֱ���� controller->front
        GLuint viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
        glm::vec3 viewP = glm::vec3(controllerPtr->front); // ���� controller->front ��һ����ֱ��ʹ�õ�����
        glUniform3f(viewPosLoc, viewP.x, viewP.y, viewP.z);


    // 2. ���Դ����
    const auto& pointLights = spawnerPtr->GetPointLights();
    for (int i = 0; i < 4; i++) {
        std::string posName = "lightPos[" + std::to_string(i) + "]";
        std::string colorName = "lightColor[" + std::to_string(i) + "]";
        std::string intensityName = "lightIntensity[" + std::to_string(i) + "]";
        GLuint posLoc = glGetUniformLocation(shaderProgram, posName.c_str());
        GLuint colorLoc = glGetUniformLocation(shaderProgram, colorName.c_str());
        GLuint intensityLoc = glGetUniformLocation(shaderProgram, intensityName.c_str());

        if (i < pointLights.size()) {
            const auto& light = pointLights[i];
            glUniform3fv(posLoc, 1, glm::value_ptr(light.position));
            glUniform3fv(colorLoc, 1, glm::value_ptr(light.color));
            glUniform1f(intensityLoc, light.intensity);
        }
        else {
            glUniform3f(posLoc, 0.0f, 0.0f, 0.0f);
            glUniform3f(colorLoc, 0.0f, 0.0f, 0.0f);
            glUniform1f(intensityLoc, 0.0f);
        }
    }

    // 3. ƽ�й�����
    Game::CustomParallelLight parallelLight = spawnerPtr->GetParallelLight();
    GLint parallelDirLoc = glGetUniformLocation(shaderProgram, "parallelLightDirection");
    GLint parallelColorLoc = glGetUniformLocation(shaderProgram, "parallelLightColor");
    GLint parallelIntensityLoc = glGetUniformLocation(shaderProgram, "parallelLightIntensity");
    glUniform3fv(parallelDirLoc, 1, glm::value_ptr(parallelLight.direction));
    glUniform3fv(parallelColorLoc, 1, glm::value_ptr(parallelLight.color));
    glUniform1f(parallelIntensityLoc, parallelLight.intensity);

    // 4. �ֵ�Ͳ���۹�ƣ�����
    const auto& flashLights = spawnerPtr->GetFlashLights();
    for (int j = 0; j < 4; j++) {
        std::string flashPosName = "flashLightPos[" + std::to_string(j) + "]";
        std::string flashDirName = "flashLightDirection[" + std::to_string(j) + "]";
        std::string flashColorName = "flashLightColor[" + std::to_string(j) + "]";
        std::string flashIntensityName = "flashLightIntensity[" + std::to_string(j) + "]";
        std::string flashCutoffName = "flashLightCutoff[" + std::to_string(j) + "]";
        GLuint flashPosLoc = glGetUniformLocation(shaderProgram, flashPosName.c_str());
        GLuint flashDirLoc = glGetUniformLocation(shaderProgram, flashDirName.c_str());
        GLuint flashColorLoc = glGetUniformLocation(shaderProgram, flashColorName.c_str());
        GLuint flashIntensityLoc = glGetUniformLocation(shaderProgram, flashIntensityName.c_str());
        GLuint flashCutoffLoc = glGetUniformLocation(shaderProgram, flashCutoffName.c_str());

        if (j < flashLights.size()) {
            const auto& flash = flashLights[j];
            glUniform3fv(flashPosLoc, 1, glm::value_ptr(flash.position));
            glUniform3fv(flashDirLoc, 1, glm::value_ptr(flash.direction));
            glUniform3fv(flashColorLoc, 1, glm::value_ptr(flash.color));
            glUniform1f(flashIntensityLoc, flash.intensity);
            glUniform1f(flashCutoffLoc, flash.cutoff);
        }
        else {
            glUniform3f(flashPosLoc, 0.0f, 0.0f, 0.0f);
            glUniform3f(flashDirLoc, 0.0f, 0.0f, 0.0f);
            glUniform3f(flashColorLoc, 0.0f, 0.0f, 0.0f);
            glUniform1f(flashIntensityLoc, 0.0f);
            glUniform1f(flashCutoffLoc, 0.0f);
        }
    }
}