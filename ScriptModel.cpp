#include "ScriptModel.h"
using namespace Game;
void ButterflyScript:: UpdateVariant(glm::mat4 view, glm::mat4 projection)
{

	//����Ϳ���д���������֡�任����

	position += glm::vec3(0.0f, 0.01f, 0.00f);
	
}

void CoordinateSystemCus::Update(glm::mat4 view, glm::mat4 projection)
{
	UpdateTransform();
	DrawLineFixedWidget(view);


}
