#include "ScriptModel.h"
using namespace Game;
void ButterflyScript:: UpdateVariant(glm::mat4 view, glm::mat4 projection)
{

	//这里就可以写变体独立的帧变换方法

	position += glm::vec3(0.0f, 0.01f, 0.00f);
	
}

void CoordinateSystemCus::Update(glm::mat4 view, glm::mat4 projection)
{
	//UpdateTransform(); 这里可以不用更新位置信息了， 参考坐标系不需要移动 
	DrawLineFixedWidget(view,projection);
}
