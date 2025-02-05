#ifndef LIFECYCLE_MANAGER_H
#define LIFECYCLE_MANAGER_H

#include <vector>//����
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>  // ������ת
namespace Game {

    //ģ������������͵�������
    template <typename T>
    class LifecycleManager
    {
    public:
        // ע�� MonoBehaviour �����������ڹ�����
        void RegisterObject(T* object);
        std::vector<T*> GetNativeObjects();
        std::vector<T*> GetVariantObjects();
        static LifecycleManager<T>* GetInstance();
        // ����ѭ���е���ÿ��������������ڷ���
        void StartAll();
        void UpdateAll(glm::mat4 view, glm::mat4 projection);
        void DestroyAll();
        //--
        void UpdateAllVariant(glm::mat4 view, glm::mat4 projection);
    private:
        std::vector<T*> nativeObjects;   // �洢ע��Ķ���
        std::vector<T*> variantObjects;//���������������Ԥ����
        LifecycleManager() {};
        static LifecycleManager<T>* instance;

    public:
        //��������

    };
    
}
#endif // LIFECYCLE_MANAGER_H


