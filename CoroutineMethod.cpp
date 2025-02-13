#include "CoroutineMethod.h"

// ȫ�ֱ���������ʵ����Ŀ���壩
extern const char* noneLightVertexShaderSource;
extern const char* noneLightcubeFragmentShaderSource;

using namespace Game;

    CoroutineMethod* CoroutineMethod::instance = nullptr;

    CoroutineMethod* CoroutineMethod::GetInstance() {
        if (!instance)
            instance = new CoroutineMethod();
        return instance;
    }
      
    CoroutineMethod::CoroutineMethod() { }

    CoroutineMethod::~CoroutineMethod() { }
    //ԭ���ķ���������Ŀǰ��Ⱦ�������---
    void CoroutineMethod::StartSpawnButterfliesAsync(LifecycleManager<CustomModel>* manager) {
        std::thread([manager]() {
            for (int i = 0; i < 30; i++) {
                CustomModel* model = new CustomModel(
                    noneLightVertexShaderSource,
                    noneLightcubeFragmentShaderSource,
                    ModelDic["butterfly"],
                    true
                );
                manager->RegisterObject(model);
                model->Initialize(
                    glm::vec3(2.0f, 0.0f, i * 0.5f),
                    glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)),
                    glm::vec3(0.1f, 0.1f, 0.1f)
                );
                model->AttachTexture(TextureDic["default"][0],0);
                model->AttachAnimationController(AnimationDic["butterfly"]["fly"]);
                model->AttachPhysicalEngine();
                model->AttachCollider();
                model->SetVariant(ModelClass::ActorButterfly);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            }).detach();
    }
    //һ���������������ķ���
    void CoroutineMethod::AddTimerTask(float intervalSeconds, int repeatCount, std::function<void()> callback) {
        float currentTime = static_cast<float>(glfwGetTime());
        TimerTask task;
        task.interval = intervalSeconds;
        task.repeatCount = repeatCount;
        task.nextTriggerTime = currentTime + intervalSeconds;
        task.callback = callback;
        tasks.push_back(task);
    }
    //��ѭ���и��µķ���
    void CoroutineMethod::CoroutineUpdate() {
        float currentTime = static_cast<float>(glfwGetTime());
        for (auto& task : tasks) {
            if (currentTime >= task.nextTriggerTime) {
                task.callback();
                if (task.repeatCount > 0)
                    task.repeatCount--;
                task.nextTriggerTime += task.interval;
            }
        }
        tasks.erase(
            std::remove_if(tasks.begin(), tasks.end(), [](const TimerTask& t) {
                return t.repeatCount == 0;
                }),
            tasks.end()
        );
    }

    //��ʵ�������������ͨ�����ã�ת����ͨ�õĳ�ʼ������
    void CoroutineMethod::StartSpawnButterfliesByTimer(LifecycleManager<CustomModel>* manager, GLuint textureName, int order) {
        // �ظ� 5 �Ρ�ÿ�μ�� 1 ��
        AddTimerTask(1.0f, 20, [manager, textureName,order]() {
             int counter = 0;
            std::cout << "[TimerTask] ������������ #" << counter << std::endl;
            counter++;

            CustomModel* model = new CustomModel(
                noneLightVertexShaderSource,
                noneLightcubeFragmentShaderSource,
                ModelDic["butterfly"],
                true
            );
            manager->RegisterObject(model);
            model->Initialize(
                glm::vec3(2.0f, 0.0f, counter * 0.5f),
                glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)),
                glm::vec3(0.1f, 0.1f, 0.1f)
            );
            model->AttachTexture(textureName,order);
            model->AttachAnimationController((AnimationDic["butterfly"]["fly"]));
            model->AttachPhysicalEngine();
            model->AttachCollider();
            model->SetVariant(ModelClass::ActorButterfly);
            });
    }
  

    

    

