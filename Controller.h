#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
#include "Monster.h"
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace Game {

	class  Controller
	{
	public:

		static Controller* GetInstance();
		// �����״̬
		glm::vec3 position;  // �����λ��
		glm::vec3 front;     // �����ǰ������
		glm::vec3 up;        // �����������
		float pitch, yaw;    // ������ƫ��

		// ͸��ͶӰ����Ĳ���
		float fov;//�ӿ�
		float aspect;//��߱�
		float nearPlane;//������
		float farPlane;//Զ����



		// ���ͼ��̿���
		bool rightMousePressed;
		double lastX, lastY;  // ���λ��
		double tempX, tempY;   // ��ʱƫ��λ��
		bool mouseMovesContinuously;

		// ��Ļ��С
		int windowWidth, windowHeight;

		//��������
		void ProcessInput(GLFWwindow* window, glm::vec3& objectPosition);
		//���ص�ע��
		void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		//����ƶ�����
		void MouseButtonFun(GLFWwindow* window);
		//���������ת�߼�
		void ProcessMouseInput(GLFWwindow* window, float& pitch, float& yaw, bool& rightMousePressed);

		//�ۺϷ���
		void FrameControlMethod(GLFWwindow* window);

		// ��ȡ�������ͼ����
		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();
	private:
		static Controller* instance;
		glm::mat4 view;
		// ͶӰ����
		glm::mat4 projection;
		Controller();
		~Controller();
	};
}

#endif