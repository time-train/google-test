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
	T_EMTest * m_EMTest = addFunc(add,1,2,3);//addFunc的作用是将我们要赋的值add，1,2,3通过addFunc函数赋到结构体变量名m_EMTest，这样就可以让下面测试runEMTest函数使用m_EMTest
	runEMTest(m_EMTest);//runEMTest的作用是实现一个功能：表明是功能是数字相加，相加的两个数分别是1和2。其结果判断是否等于3.
}

/*所以这个工程google主要分四大部分
* 1.设定主函数（这个肯定要的）
* 2.设置我们项目功能是将两个数字相加，那么int add(int a, int b)
* 3.由于是测试框架，所以我们的目的是测试我们要相加的数字和是否等于我们要测试的那个数（即1,2相加是否等于3（addFunc(add,1,2,3)））
*	所以我们要设置一个结构体，将数字赋值进去T_EMTest（变量类型）和T_EMTest *addFunc(int (*TestEMFunc)(int, int), int a, int b, int output)
* 4.此时，我们得到了结构体变量的变量名m_EMTest所有的数据。
* 5.用runEMTest进行对比测试，打印结果
*/