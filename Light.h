#ifndef LIGHT_H
#define LIGHT_H

#include <vector>
#include <glm/glm.hpp>
#include "GameObject.h"

namespace Game {

    // 定义点光源结构体
    struct CustomPointLight {
        glm::vec3 position;
        glm::vec3 color;       // RGB 光源颜色
        float intensity;
    };

    // 定义平行光（方向光），全局只有一个
    struct CustomParallelLight {
        glm::vec3 direction;   // 光线方向
        glm::vec3 color;
        float intensity;
    };

    // 定义手电筒光（聚光灯）
    struct CustomFlashLight {
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 color;
        float intensity;
        float cutoff;        // 聚光角度
    };

    class LightSpawner {
    public:
        // 获取单例实例
        static LightSpawner* GetInstance();

        // 创建点光源（按值传参），并存储到内部容器中
        CustomPointLight SpawPointLight(glm::vec3 position = glm::vec3(0.0f),
            glm::vec3 color = glm::vec3(1.0f),
            float intensity = 1.0f);

        // 初始化或更新全局平行光
        CustomParallelLight SpawParallelLight(glm::vec3 direction = glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3 color = glm::vec3(1.0f),
            float intensity = 10.0f);


        // 创建手电筒光（聚光灯），默认位置为 (1, 1, 1)，默认方向指向原点
        CustomFlashLight SpawFlashLight(
            glm::vec3 position = glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3 direction = glm::vec3(-0.57735f, -0.57735f, -0.57735f), // 指向原点的归一化向量
            glm::vec3 color = glm::vec3(1.0f, .0f, .0f),//默认红色
            float intensity = 10.0f,
            float cutoff = cos(glm::radians(12.5f))
        );

        // 获取所有点光源的容器,前置const 防止拷贝，后置const 确保外部对象调用该方法，对象本身可以是const类型，拓宽范围
        const std::vector<CustomPointLight>& GetPointLights() const { return pointLights; }

        // 获取全局平行光数据
        const CustomParallelLight& GetParallelLight() const { return parallelLight; }

        // 获取所有手电筒光的容器
        const std::vector<CustomFlashLight>& GetFlashLights() const { return flashLights; }

    private:
        LightSpawner();
        ~LightSpawner();
        LightSpawner(const LightSpawner&) = delete;
        LightSpawner& operator=(const LightSpawner&) = delete;

        // 内部容器
        std::vector<CustomPointLight> pointLights;
        CustomParallelLight parallelLight;
        std::vector<CustomFlashLight> flashLights;

        static LightSpawner* instance;
    };

    class LightRender {
    public:
        static LightRender* GetInstance();

        // RenderLights: 将所有光源参数传入 shaderProgram 中，
        // controllerPtr 为控制器指针，spawnerPtr 为 LightSpawner 指针
        void RenderLights(GLuint shaderProgram, const Controller* controllerPtr, const Game::LightSpawner* spawnerPtr);

    private:
        LightRender();
        ~LightRender();
        LightRender(const LightRender&) = delete;
        LightRender& operator=(const LightRender&) = delete;

        static LightRender* instance;

    };



} // namespace Game

#endif // LIGHT_H
