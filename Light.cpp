#include "Light.h"
#include <glm/gtc/matrix_transform.hpp>
#include "FileLoadIO.h"
#include "CustomModel.h"
#include "LifecycleManager.h"
#include "ScriptModel.h"
#include "MeshDataManager.h"

using namespace Game;

// ��ʼ����̬����ָ��
LightSpawner* LightSpawner::instance = nullptr;
//����shader
extern const char* noneLightLightVertexShaderSource;
extern const char* noneLightLightFragmentShaderSource;
extern const char* rayVertexShaderSource;
extern const char* rayFragmentShaderSource;
//C++��Դ�ļ��п���ֱ�Ӷ�����ر�����������Ҫ�����н��������������
LifecycleManager<CustomModel>* manager = nullptr;
MeshDataManager* meshData = nullptr;
LightSpawner* LightSpawner::GetInstance() {
    if (instance == nullptr) {
        instance = new LightSpawner();
    }
    return instance;
}

LightSpawner::LightSpawner() {
    // ��ʼ��ȫ��ƽ�й�Ĭ�ϲ���
    manager = LifecycleManager<CustomModel>::GetInstance();
    meshData = MeshDataManager::GetInstance();
    modelIdentification = true;
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
    if (modelIdentification)
    {
        //--ͬʱ����Ӧ��λ�ù���һ�����Դģ��
        auto* pointLightPtr = new LightModel(noneLightLightVertexShaderSource, noneLightLightFragmentShaderSource, ModelDic["baseSphere"], false);
        pointLightPtr->SetVariant(ModelClass::PointLight);
        pointLightPtr->Initialize(position, glm::quat(glm::vec3(0, 0, 1.5f)), glm::vec3(0.3f));
        manager->RegisterObject(pointLightPtr);
        pointLightPtr->AttachTexture(TextureDic["light"][0]);
        //����ķ��������õƹ����
        pointLightPtr->SteLightParameters(color, intensity);
    }

   
    return pointLight;
}

CustomParallelLight LightSpawner::SpawParallelLight(glm::vec3 direction, glm::vec3 color, float intensity) {
   
    
    parallelLight.direction = glm::normalize(direction);
    parallelLight.color = color;
    parallelLight.intensity = intensity;

    if (modelIdentification)
    {
        //--ƽ�й���ȫ�ֹ��գ�λ�������壬���ƹ�Դ������λ����������ģ�ʹ��棬����0.1��ͷ��ʾ�Ƿ��壬Ӧ�޾���˥��
        auto* pointLightPtr = new LightModel(noneLightLightVertexShaderSource, noneLightLightFragmentShaderSource, ModelDic["testMonkey"], false);
        pointLightPtr->SetVariant(ModelClass::ParallelLight);
        pointLightPtr->Initialize(glm::vec3(0), glm::vec3(0), glm::vec3(0.3f));
        manager->RegisterObject(pointLightPtr);
        pointLightPtr->AttachTexture(TextureDic["light"][0]);
        //����ķ��������õƹ����
        pointLightPtr->SteLightParameters(color, intensity);

    }


    return parallelLight;
}

CustomFlashLight LightSpawner::SpawFlashLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float intensity, float cutoff) {
    CustomFlashLight flashLight;
    flashLight.position = position;
    flashLight.direction = -glm::normalize(direction);
    flashLight.color = color;
    flashLight.intensity = intensity;
    flashLight.cutoff = cutoff;
    if (flashLights.size()<4)
    {
        flashLights.push_back(flashLight);
    }
    if (modelIdentification)
    {
        //�����ֵ�Ͳ��������
        glm::vec3 defaultDown = glm::vec3(0.0f, -1.0f, 0.0f);  // Բ׶����Ĭ�ϳ��� Y,����������������ķ���
        glm::vec3 dirNorm = glm::normalize(direction);

        float dotVal = glm::dot(defaultDown, dirNorm);
        glm::quat finalRotation;
        const float epsilon = 1e-6f;

        if (dotVal > 1.0f - epsilon) {
            // �� defaultDown ����ͬ�� => ����ת
            finalRotation = glm::quat(1, 0, 0, 0);
        }
        else if (dotVal < -1.0f + epsilon) {
            // ���� => ������ˮƽ����ת180��
            finalRotation = glm::angleAxis(glm::pi<float>(), glm::vec3(1, 0, 0));
        }
        else {
            float angle = acos(dotVal);
            glm::vec3 axis = glm::normalize(glm::cross(defaultDown, dirNorm));
            finalRotation = glm::angleAxis(angle, axis);
        }



        //--ͬʱ����Ӧ��λ�ù���һ���ֵ�Ͳģ��
        auto* pointLightPtr = new LightModel(noneLightLightVertexShaderSource, noneLightLightFragmentShaderSource, ModelDic["baseCone"], false);
        pointLightPtr->SetVariant(ModelClass::FlashLight);
        pointLightPtr->Initialize(position, finalRotation, glm::vec3(0.3f));
        manager->RegisterObject(pointLightPtr);
        pointLightPtr->AttachTexture(TextureDic["light"][0]);
        //����ķ��������õƹ����
        pointLightPtr->SteLightParameters(color, intensity);

        //--�����ֵ�Ͳ�ο�����-------------
        //��������Զ��嶥�㣬���������㣬���ڸ������߳���
        GLfloat customizeRayLength[6] = { 0,0,0,0,-intensity,0 };
        GLuint  customizeRayIndecis[2] = { 0,1 };
        auto* rayCus = new CustomizeRay(rayVertexShaderSource, rayFragmentShaderSource, customizeRayLength, customizeRayIndecis, 6, 2, false);
        rayCus->SetVariant(ModelClass::Ray);
        rayCus->Initialize(position, finalRotation);
        manager->RegisterObject(rayCus);
        rayCus->SetRayPar(color, intensity);
    }
    return flashLight;
}

void Game::LightSpawner::ParalletLightController(glm::vec3 dirction, glm::vec3 color, float intensity)
{
    // 2) �������Ƕ�(��)תΪ����
    glm::vec3 radIncrements = glm::radians(dirction);

    // 3) ������ת����(��ʼΪ��λ����)
    glm::mat4 rotMat(1.0f);

    // ����˳������X��תpitch������Y��תyaw������Z��תroll
    rotMat = glm::rotate(rotMat, radIncrements.x, glm::vec3(1, 0, 0));
    rotMat = glm::rotate(rotMat, radIncrements.y, glm::vec3(0, 1, 0));
    rotMat = glm::rotate(rotMat, radIncrements.z, glm::vec3(0, 0, 1));

    // 4) �����������ת������Ե�ǰ��� direction
    //    parallelLight.direction����֡(���ʼ)�ĳ����������ۼ���ת
    glm::vec4 oldDir(parallelLight.direction, 0.0f);
    glm::vec4 newDir = rotMat * oldDir;

    // 5) д�ز���һ��
    parallelLight.direction = glm::normalize(glm::vec3(newDir));
   /* parallelLight.color = color;
    parallelLight.intensity = intensity;*/

}

void Game::LightSpawner::PointLightController(glm::vec3 color, float intensity, int lightNumber)
{
    pointLights[lightNumber].color = color;
    pointLights[lightNumber].intensity = intensity;
}

void Game::LightSpawner::FlashLightController(glm::vec3 dirction, glm::vec3 color, float intensity, float cutoff,int lightNumber)
{
    flashLights[lightNumber].direction = dirction;
    flashLights[lightNumber].color = color;
    flashLights[lightNumber].cutoff = cutoff;
    flashLights[lightNumber].intensity = intensity;

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