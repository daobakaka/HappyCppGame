//����һ��.inl�ļ�������ļ��Ƕ�ͷ�ļ��Ĳ��䣬Ϊ������ͷ�ļ��Ŀɶ��ԣ���.inl�ļ�������չͷ�ļ��з����Ĳ���ʵ�֣���������������ģ����<T>��

#ifndef InlT_inl
#define InlT_inl
#include <iostream>

inline void InlTest::SayHelloInl() //������������Ϊ���������ԣ����Բ���Ҫ������ص�ͷ�ļ��Ϳ��Ա���ֱ��ʹ��InlTest::SayHelloInl() ���ᱨ��
{
	std::cout << "this is a inl fun " << std::endl;

}

#endif

