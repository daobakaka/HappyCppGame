#include "ScriptModel.h"
using namespace Game;
#pragma region ���Ժ���
void ButterflyScript::UpdateVariant(glm::mat4 view, glm::mat4 projection)
{

    //����Ϳ���д���������֡�任����

    position += glm::vec3(0.0f, 0.01f, 0.00f);

}
#pragma endregion

#pragma region �ο�����
void CoordinateSystemCus::Update(glm::mat4 view, glm::mat4 projection)
{
    //UpdateTransform(); ������Բ��ø���λ����Ϣ�ˣ� �ο�����ϵ����Ҫ�ƶ� 
    DrawLineFixedWidget(view, projection);
}
#pragma endregion

#pragma region ��Դģ��

void LightModel::SteLightParameters(glm::vec3 color, float intensity, glm::vec3 dirction)
{
    myColor = color;
    myIntensity = intensity;
    myDirection = dirction;
}

void LightModel::RenderingTexture()
{
    // 1) ʹ�õ�ǰ LightModel ����ɫ��
    glUseProgram(shaderProgram);

    // 2) ���� baseColor
    GLint baseColorLoc = glGetUniformLocation(shaderProgram, "baseColor");
    glUniform3fv(baseColorLoc, 1, glm::value_ptr(myColor));
    // 3) ���� lightIntensity
    GLint intensityLoc = glGetUniformLocation(shaderProgram, "lightIntensity");
    glUniform1f(intensityLoc, myIntensity);
    //3.1)���� lightDirection
    GLuint dirtionLoc = glGetUniformLocation(shaderProgram, "lightDirction");
    glUniform3fv(dirtionLoc, 1, glm::value_ptr(myDirection));

    // 4) �ҵ� sampler uniform "texture1"
    GLint samplerLoc = glGetUniformLocation(shaderProgram, "texture1");


    // 5) ��������Ԫ (GL_TEXTURE0 + textureOrder)
    glActiveTexture(GL_TEXTURE0 + textureOrder);

    // 6) ������������ (texture) ���õ�Ԫ
    glBindTexture(GL_TEXTURE_2D, texture);

    // 7) ���� sampler uniform "texture1" ʹ�õ� textureOrder ������Ԫ
    glUniform1i(samplerLoc, textureOrder);

}
#pragma endregion

#pragma region �Զ�������

void CustomizeRay::Update(glm::mat4 view, glm::mat4 projection)
{
    UpdateTransform();
    DrawLine(view,projection);
}

bool CustomizeRay::DrawLine(glm::mat4 view, glm::mat4 projection)
{
    
    // ���ǰ����ɫ������
    glUseProgram(shaderProgram);


    // 2) ����������ɫ,�����Ƕ�drawline�ĸ�������������д
    GLint baseColorLoc = glGetUniformLocation(shaderProgram, "baseColor");
    glUniform3fv(baseColorLoc, 1, glm::value_ptr(myColor));

    // ��ȡ shader �� "model"��"view" �� "projection" uniform ������λ��
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    // ����任���� shader������������Ϊ GL_FALSE ��ʾ������Ҫת�ã�
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // �󶨵�ǰģ�͵� VAO
    glBindVertexArray(VAO);

    // ֱ��ʹ�� GL_LINES ģʽ�����߶�
    glDrawElements(GL_LINES, index, GL_UNSIGNED_INT, 0);

    // ��� VAO
    glBindVertexArray(0);


    return true;
}

void CustomizeRay::SetRayPar(glm::vec3 color,float intensity)
{
    myColor = color;
    myIntensity = intensity;
}

#pragma endregion
