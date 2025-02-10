#ifndef Custom_Model_H
#define Custom_Model_H
//������--��ʹͷ�ļ������໥������һ��Ҫע��˳�����Ǻܿ��������صı������ĵط�����鲻��������Ҳ��������
//#include "GameObject.h"
#include "AnimationIntergrated.h"

namespace Game {
    class CustomModel : public GameObject
    {
    public:
        CustomModel(const char* vertexShaderSourceIn, const char* fragmentShaderSourceIn, GLfloat* vertices, GLuint* indices, size_t vertexCount, size_t indexCount, bool ifLight = false);
        CustomModel(const char* vertexShaderSourceIn, const char* fragmentShaderSourceIn, GLfloat* vertices, GLuint* indices, size_t vertexCount, size_t indexCount, int ifVaraint, bool ifLight = false);
        //--���·���
        CustomModel(const char* vertexShaderSourceIn, const char* fragmentShaderSourceIn, std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals, bool ifLight = false);
        CustomModel(const char* vertexShaderSourceIn, const char* fragmentShaderSourceIn, std::vector<Vertex>& vertices, std::vector<unsigned int>& finalIndicesm, bool ifLight = false);
        CustomModel(const char* vertexShaderSourceIn, const char* fragmentShaderSourceIn, std::vector<Vertex>& vertices, std::vector<unsigned int>& finalIndices, bool isSkinnedMesh, bool ifLight = false);
        CustomModel(const char* vertexShaderSourceIn, const char* fragmentShaderSourceIn, const ModelData& modelData, bool isSkinnedMesh, bool ifLight = false);
        void UpdateVerticesForAnimation(size_t animationFrame);
        void UpdateVerticesForAnimation(const std::vector<Vertex>& vertex);

        //--�̳�GameObject ������
        virtual bool Draw(glm::mat4 view, glm::mat4 projection) override;//��̬���ƿ���д
        virtual bool DrawLine(glm::mat4 view, glm::mat4 projection);//����������������custom ����ӵ��·���������������ƣ�����д
        virtual bool DrawLineFixedWidget(glm::mat4 view);//��������ϵ�������̶���һ����Ļ���棬������д
        ~CustomModel();
        //--�̳�MonoBehaviour������
        virtual void Update(glm::mat4 view, glm::mat4 projection) override;//�����ƶ�����д
        virtual void UpdateVariant(glm::mat4 view, glm::mat4 projection) override;//�����ƶ�����д
        virtual bool DrawDynamical(glm::mat4 view, glm::mat4 projection) override;//��̬���ƿ���д����IntergtatedAnimatior����
        //--����ģ�飬��Ϊÿ���������Ķ�������Ҳ��᲻һ����Ŀǰ���÷��뷽��
        virtual void AttachAnimationController(AnimationData animaitonData);//���Ӷ������������ɴ���һ��Ĭ�϶���
        virtual void AttachAnimationController(); //���Ӷ�������������Ĭ�ϲ�������ȫ�ڲ����죬����д
        virtual void PlayAnimation(int index, float frame = 0.0167f);//���󲥷Ŷ��������������ⲿ������󣬿���д
        virtual void StopPlayAnimation();//����ֹͣ���Ŷ�������������д
        //
        virtual bool AttachTexture() override;//�������������д
        //
        virtual bool AttachPhysicalEngine();//���������������д
        virtual bool AttachCollider();//������ײ�����д


    private:
#pragma region   �����ʼ��ԭ��{}ֻ��������ʱ���г�ʼ��
        size_t index;
        size_t vertexCount;
        std::vector<Vertex> verticesTras = {};
        //  GLfloat verticesIns[];
          //�����������
        AnimationController* animator = nullptr;
        PhysicalEngine* physicsBody = nullptr;
        CollisionBody* collider = nullptr;
#pragma endregion



        //���� consterxpr  �ƹ���Ч�����飬 static_assert ���� ���б���׶μ��
    public:
        template <typename T>
        T* GetComponent() {
            if constexpr (std::is_same<T, AnimationController>::value) {
                return animator;
            }
            else if constexpr (std::is_same<T, PhysicalEngine>::value) {
                return physicsBody;
            }
            else if constexpr (std::is_same<T, CollisionBody>::value) {
                return collider;
            }
            else {
                static_assert(false, "Unsupported component type");
            }
        }
    };
}
#endif // CUBE_H
