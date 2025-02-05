#include "LifecycleManager.h"
#include "MonoBehaviour.h"
#include <iostream>
#include "GameObject.h"
#include "CustomModel.h"
using namespace Game;
template <typename T>
LifecycleManager<T>* LifecycleManager<T>::instance = nullptr;


template <typename T>
void LifecycleManager<T>::RegisterObject(T* object) {
 
           nativeObjects.push_back(object);
           if (object->GetVariant() != 0)
               variantObjects.push_back(object);
}

template<typename T>
std::vector<T*> LifecycleManager<T>::GetNativeObjects()
{
    return nativeObjects;
}

template<typename T>
std::vector<T*> LifecycleManager<T>::GetVariantObjects()
{
    return variantObjects;
}

template<typename T>
LifecycleManager<T>* LifecycleManager<T>::GetInstance()
{
    if (instance == nullptr) {
        instance = new LifecycleManager<T>();
    }
    return instance;
}



//Ŀǰ��û���õ�����ĳ�ʼ����������ʱ�����뷽��
template <typename T>
void LifecycleManager<T>::StartAll() {
    for (T* object : nativeObjects) {
        object->Start();  // ����ÿ������� Start ����
    }
    //for (T* object : variantObjects) {
    //    object->Start();  // ����ÿ���������� Start ����
    //}
}

template <typename T>
void LifecycleManager<T>::UpdateAll(glm::mat4 view, glm::mat4 projection) {
    for (T* object : nativeObjects) {
        object->Update(view, projection);  // ����ÿ������� Update ����
    }
}

template <typename T>
void LifecycleManager<T>::DestroyAll() {
    for (T* object : nativeObjects) {
        object->Destroy();  // ����ÿ������� Destroy ����
    }
    //for (T* object : variantObjects) {
    //    object->Destroy();  // ����ÿ���������� Destory ����
    //}
}

template<typename T>
void LifecycleManager<T>::UpdateAllVariant(glm::mat4 view, glm::mat4 projection)
{
    for (T* object:variantObjects)
    {
        object->UpdateVariant(view,projection);
    }

}









// ��ȷʵ����ģ���࣬�������Ӵ����������Դ�ļ��е�ʵ����ģ�壬��1��T�����һ����������������������
//���ģ������ȫ����ͷ�ļ��У�����Ҫ��ʾʵ���������Զ��ĸ��ݴ���������룡��ͨ������ͷ�ļ��ķ�ʽ���������ꡢ����������ģ�����һЩ������
//��������Ҫ�ڱ���Դ�ļ�ʱΪģ�������ɴ��룬���Է���Դ�ļ�����Ҫ��ʾ������ͷ�ļ���ʵ�ʱ��룬�����CPP����.h��λ��
template class LifecycleManager<MonoBehaviour>;
template class LifecycleManager<GameObject>; // ��ʽʵ���� GameObject
template class LifecycleManager<CustomModel>;//��ʾʵ���� CustomModel

