#ifndef  SCRIPTMODEL_H
#define  SCRIPTMODEL_H
#include "CustomModel.h"

namespace Game
{

	class CustomModel;
	/// <summary>
	/// ��ʼ����ģ��
	/// </summary>
	class ButterflyScript :public CustomModel
	{
	public:
		//����ֱ�Ӽ̳л���Ĺ��캯��
		using CustomModel::CustomModel;
		void UpdateVariant(glm::mat4 view, glm::mat4 projection) override;
	
	private:

	};
	/// <summary>
	/// �ο�����ϵģ��
	/// </summary>
	class CoordinateSystemCus : public CustomModel
	{

	public:
		using CustomModel::CustomModel;

		void Update(glm::mat4 view, glm::mat4 projection) override;

	private:

	};
	/// <summary>
	/// �ƹ��ʶģ��
	/// </summary>
	class LightModel :public CustomModel
	{
	using CustomModel::CustomModel;
	public:
		
		 void SteLightParameters(glm::vec3 color, float intensity,glm::vec3 direction=glm::vec3(0));

		 void RenderingTexture() override;

	private:
		glm::vec3 myColor;
		float myIntensity;
		glm::vec3 myDirection;
	};
	/// <summary>
	/// �Զ�������
	/// </summary>

	class CustomizeRay : public CustomModel
	{
		using CustomModel::CustomModel;
	public:
		void Update(glm::mat4 view, glm::mat4 projection) override;
		bool DrawLine(glm::mat4 view, glm::mat4 projection)override;
		void SetRayPar(glm::vec3 color,float intensity);


	protected:
		glm::vec3 myColor;
		float myIntensity;
		glm::vec3 myDirection;


	};


}




#endif // ! SCRIPTMODEL_H

