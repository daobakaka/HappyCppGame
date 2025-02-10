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

}




#endif // ! SCRIPTMODEL_H

