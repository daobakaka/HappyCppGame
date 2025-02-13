#pragma once
#include "Cube.h"
using namespace Game;


Cube::Cube(const char* vertexShaderSourceIn, const  char* fragmentShaderSourceIn) {
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceIn, nullptr);
    glCompileShader(vertexShader);
    CheckShaderCompilation(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceIn, nullptr);
    glCompileShader(fragmentShader);
    CheckShaderCompilation(fragmentShader);

    //������Ǵ�������shader  һ������ һ��ƬԪ��Ȼ��Դ��������shader ���б��� glcompileShaer,����һ���Զ����鷽�������shader�����Ƿ�ɹ���nullptr 
    //C�����ַ�����\0��β,�м������1�������ַ����������Դ���� ����ǰ1������ж����Ϊconst GLchar* sources[] = { source1, source2 }; glShaderSource(shader, 2, sources, nullptr);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    CheckShaderProgramLinking(shaderProgram);  // �����ɫ�������Ƿ����ӳɹ�����Ҳ��һ���Զ���ķ������������������shader ���ӵ���Ŀ�У��������ӵ���Ŀ������

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //��һ�����֮�󣬾Ϳ���ʹ�������Ŀ�ˣ�ͬʱҲ����ɾ�������ƬԪ��ɫ����
    
    // 
    // 
    // �����Ͱ�VAO, VBO, EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    //�󶨶��㻺������
    //����������ͼ������Ҫ�� �������� �ͻ���buffer���������㻺�����VBO�������������VAO��Ԫ�ػ������ EBO

    // VBO: Vertex Buffer Object (���㻺�����)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//GL_ARRAY_BUFFER 0x8892 ���黺������Ƕ��嵽�̶����ڴ��ַ���󶨻���
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//GL_STATIC_DRAW 0x88E4   ��̬��������

    // EBO: Element Buffer Object (Ԫ�ػ������)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);// GL_ELEMENT_ARRAY_BUFFER 0x8893  ��Ԫ�ػ�����󣬻��߽�����������󣬴��������������Ϣ
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//GL_STATIC_DRAW 0x88E4   ��̬��������

    //���������Ҫ������ ��������뵽 ��̬����������У��������ܻ��ƣ���������Ͷ������鶼�� cube.h��ͷ�ļ��ж���


    // ���ö�������ָ�룬ʵ���Ͼ��Ǹ��� OpenGL���������д洢�Ķ����������ݰ��� 3 �������� ��λ����Ϣ���洢��ÿ 3 ��������������ɫ��Ϊ6������ʼλ�ã���λ����Ϣ��ƫ���� 0 ��ʼ��
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);//�������ö�����ɫ���� layout(location = 0) ���������ݡ�
    //----
    //���� OpenGL���������д洢�Ķ����������ݰ��� 3 �������� ����ɫ��Ϣ���洢��ÿ 6 �������� ��ƫ�� 3 ��ʼ��λ�á�
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 3 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);//�������ö�����ɫ���� layout(location = 1) ����������
    //��Ӧ�����β���,1���Ƕ����������2����ƬԪ���������,��ı�����ʵ���������滻����ǿ�˴���Ŀɶ���
    
    glBindVertexArray(0);  //1 ���ǰ�󶨵� VAO����ֹ������ VAO �Ĳ���Ҫ�޸� 2 ����VAO �����ñ������� GPU �У�����ֻ�����°󶨼���ʹ��

    //-- //(GLAPIENTRY * PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
        //0 (GLuint index)

        //ָ��Ҫ���õĶ������Ե�λ����������Ӧ������ɫ���е� layout(location = 0)��
        //���λ����������ɫ�������������԰󶨡�
        //3 (GLint size)

        //ÿ���������Ե��������������Ϊ 3����ʾ����� x, y, z ���ꡣ
        //GL_FLOAT(GLenum type)

        //ָ���������Ե��������ͣ�����Ϊ GL_FLOAT����ʾÿ������� 32 λ��������
        //GL_FALSE(GLboolean normalized)

        //ָ�������Ƿ���Ҫ��һ�������Ϊ GL_TRUE�������ݻᱻӳ�䵽[0, 1] ��[-1, 1]��
        //����Ϊ GL_FALSE����ʾ����Ҫ��һ����ֱ��ʹ��ԭʼ���ݡ�
        //6 * sizeof(GLfloat) (GLsizei stride)

        //������stride������ʾ����������������֮��ļ����
        //���������� x, y, z, r, g, b ����������ɣ���˲���Ϊ 6 * sizeof(GLfloat)��
        //(GLvoid*)0 (const void pointer) *

        //ƫ��������ʾ�����ڻ������е���ʼλ�á�
        //����Ϊ 0����ʾ����λ�����Դ����ݵĿ�ͷ��ʼ��
//--������������ɫ����Ӧ

    //��������--1.����shander 2.����shader 3.����shader��Ŀ 4 ����shader��shader��Ŀ������  3.�����ݼ��ص�֡������ 4.����OPENGL/�Կ��� ֡���������ݵĻ��ƹ��� 5 ���VAO����ֹ����

}

 bool Cube::Draw(glm::mat4 view, glm::mat4 projection )//���̳еĴ��鷽����ʵ�֣������ټ�override�ؼ���
 {

     size_t indicesLength = sizeof(indices) / sizeof(indices[0]);

     glUseProgram(shaderProgram);

     GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
     GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
     GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
     //�����Ƕ� ��������� ��������ץȡ����shaderProgram ���棬���������д�ڶ�Ӧ��shader������ж����
     glUniformMatrix4fv(modelLoc, 1, 0, glm::value_ptr(transform));
     glUniformMatrix4fv(viewLoc, 1, 0, glm::value_ptr(view));
     glUniformMatrix4fv(projectionLoc, 1, 0, glm::value_ptr(projection));
     //�����glm��һ�����õ���ѧ�⣬ר������ͼ�εľ������������ͳ��ڹ���� CPU֮���������ݣ�GPU ��������ͼ�Σ�
     // shader�������� ʹ�� gl_Position = projection * view * model * vec4(aPos, 1.0f);������Ⱦ���� 
     glBindVertexArray(VAO);
     //�󶨶����������VAO���������� VAO �����Ķ��㻺�����VBO���������������EBO����
     //���涥�����Ե����ã�����λ�á���ɫ�����ߡ���������ȣ��� VBO �� EBO ���������ڴ洢�������ݺͻ���������
     glDrawElements(GL_TRIANGLES, indicesLength, GL_UNSIGNED_INT, 0);
     //��������洢�� EBO��Element Buffer Object���У�EBO �Ѱ󶨵� VAO�������Σ�36���������޷����������飬��0��ʼ
     glBindVertexArray(0);

     return true;
}

 bool Cube::DrawDynamical(glm::mat4 view, glm::mat4 projection)
 {
     return false;
 }


Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Cube::Update(glm::mat4 view, glm::mat4 projection)
{  

    //����д���ͣ�ֱ�ӷ�װ�˸��±仯��֪ͨCPU��Ⱦ������������������嶨�巽����ֻ��Ҫ�������ű����浥������ĳ������������transform���ɣ��ɹ���ط��͵���
    UpdateTransform();
    Draw(view, projection);
}
//���巽�����������ӱ����������Ϊ
void Cube::UpdateVariant(glm::mat4 view, glm::mat4 projection)
{
    scale = glm::vec3(2.0f, 2.0f, 2.0f);
    position += glm::vec3(0, 0, 0. - 0.01f);
   
}

bool Cube::AttachTexture(GLuint textureName, int order)
{
    return false;
}


