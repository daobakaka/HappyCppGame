#ifndef COMPONENT_H
#define COMPONENT_H
namespace Game {
	template <typename T>
	class IComponent
	{
	public:

		virtual bool Interface() = 0;
		virtual ~IComponent() = default; // ������������ȷ���������ܹ���ȷ����
	private:

	};
}






































#endif
