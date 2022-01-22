#include <stdio.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>

typedef struct
{
	int output;
	int a;
	int b;
	int (*TestEMFunc)(int, int);
}T_EMTest;

T_EMTest *addFunc(int (*TestEMFunc)(int, int), int a, int b, int output)
{
	T_EMTest* m_EMTest = (T_EMTest*)malloc(sizeof(T_EMTest));
	m_EMTest->a = a;
	m_EMTest->b = b;
	m_EMTest->TestEMFunc = TestEMFunc;
	m_EMTest->output = output;
	return m_EMTest;
}

void runEMTest(T_EMTest* p_EMTest)
{
	if (p_EMTest != NULL)
	{
		int count = p_EMTest->TestEMFunc(p_EMTest->a, p_EMTest->b);
		if (count == p_EMTest->output)
		{
			printf("success \n");
		}
		else
		{
			printf("fail %d != %d \n", count, p_EMTest->output);
		}
		free(p_EMTest);
	}
}

int add(int a, int b)
{
	//TODU
	return a + b;
}

void main()
{
	printf("app start \n");
	T_EMTest * m_EMTest = addFunc(add,1,2,3);//addFunc�������ǽ�����Ҫ����ֵadd��1,2,3ͨ��addFunc���������ṹ�������m_EMTest�������Ϳ������������runEMTest����ʹ��m_EMTest
	runEMTest(m_EMTest);//runEMTest��������ʵ��һ�����ܣ������ǹ�����������ӣ���ӵ��������ֱ���1��2�������ж��Ƿ����3.
}

/*�����������google��Ҫ���Ĵ󲿷�
* 1.�趨������������϶�Ҫ�ģ�
* 2.����������Ŀ�����ǽ�����������ӣ���ôint add(int a, int b)
* 3.�����ǲ��Կ�ܣ��������ǵ�Ŀ���ǲ�������Ҫ��ӵ����ֺ��Ƿ��������Ҫ���Ե��Ǹ�������1,2����Ƿ����3��addFunc(add,1,2,3)����
*	��������Ҫ����һ���ṹ�壬�����ָ�ֵ��ȥT_EMTest���������ͣ���T_EMTest *addFunc(int (*TestEMFunc)(int, int), int a, int b, int output)
* 4.��ʱ�����ǵõ��˽ṹ������ı�����m_EMTest���е����ݡ�
* 5.��runEMTest���жԱȲ��ԣ���ӡ���
*/