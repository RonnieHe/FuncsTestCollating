// Try_Test.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include <iostream>
using namespace std;



#if 0
int _tmain(int argc, _TCHAR* argv[])
{

	//////test 1
	int *pa = new int(5);
	cout << "Poniter pa: " << hex << pa << endl;//
	cout << "Pointer *pa : " << dec << *pa << endl;//
	delete pa;

	int **ppA;
	ppA = new int*[5];//int *a[5]ָ�����飬ÿһ��Ԫ�ض���intָ�����͡�����int (*a)[5]����ָ�룬ָ��int�����ָ��
	for (int i = 0; i < 5; i++)
		ppA[i] = new int[6];


	//release
	for (int i = 0; i < 5; i++)
		delete[] ppA[i];
	delete ppA;
	
	return 0;
}
///��֮һ�仰��������ָ��һ��Ҫ֪��ָ��ָ������
#endif 

class CBB
{
public:
	int m_nVa;
};

#include <stdlib.h>
#include "stdafx.h"
#include <WCHAR.h>

#include <iostream>
using namespace std;
int add_n(int n)
{
	int ni = 200;
	static int i=100; 
	i+=n; 
	return i; 
}


//////////////
struct S1
{
    int i;
    char c;
}s1;

#pragma pack(push) // ����ǰpack����ѹջ����
#pragma pack(1)
struct S2
{
    int i;
    char c;
}s2;
#pragma pack()
#pragma pack(pop) // �ָ���ǰ��pack����
/////////
int main()
{
#if 0
	/////////////////////convert
	const CBB b1 ;
	//b1.m_nVa = 10;//error.....cannot change const object
	//CBB b2 = const_cast <CBB>(b1);
    CBB* b2 = NULL;
        b2= const_cast <CBB *>(&b1);
	b2->m_nVa = 20;
	cout << "const_cast convert variable value:"<<b2->m_nVa << endl;
//////////////////////////////////////////////////////////////////////////////////
	int c[4] = { 1, 2, 3, 4 };
	int *a[4]; //ָ������.....ÿһ��Ԫ�ض���intָ������
	int(*b)[4]; //����ָ��.....ָ��int�����ָ��

	b = &c;	//������c��Ԫ�ظ�������b

	for (int i = 0; i<4; i++)
	{
		a[i] = &c[i];//a��ÿһ������Ӧ��ַ.
	}
	//������½��
	cout << *a[1] << endl; //���2�Ͷ�
	cout << (*b)[2] << endl; //���3�Ͷ�

/////////////////////////////////////////////////////////////////////////////////////

	char *cArr[5] = { "Hello", "Lenovo", "Welcome", "To", "C++language" };
	//char cArr[5] = { 'A','B','C','D','E'};
	char *ppa[5];
	char **ppT = NULL;
	ppT = new char*[10];///must .otherwise,it will crush

	for (int i = 0; i<5; i++)
	{
		cout << cArr[i] << endl; //����õ�ַ�ϵĴ洢����

		ppa[i] = cArr[i];//a��ÿһ������Ӧ��ַ.
		cout << ppa[i] << endl; //����õ�ַ�ϵĴ洢����

		ppT[i] = cArr[i];
		cout << ppT[i] << endl; //����õ�ַ�ϵĴ洢����
	}
	cout << ppa[1] << endl; //����õ�ַ�ϵĴ洢���ݣ�Lenovo

	cout << *ppa[1] << endl; //ֻ������ַ�...��ͬ��ppa[1][0],ֻȡ�õ�ַ��һ���ֽ�����
	cout << *cArr[1] << endl; //ֻ������ַ�
#endif 
    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////
	int na = add_n(3);
	cout << na<< endl;
	na = add_n(3);
	cout << na << endl;

    cout << "S1 sizeof=" << sizeof(s1) << ",S2 (pack(1)) sizeof=" << sizeof(s2) << endl;
    ////////////////
    char acInput[] = "abcdxyzMyNameIsHanmeimei";//,cannot run ok
    char *cInput = "abcdxyzMyNameIsHanmeimei";
    char *pcOutput = new char[100];
    
    printf("source string:%s\n", cInput);//cInput point to first char

    int nTempBuffer[500] = { 0 };
    int i = 0;
#if 1
    while ((*cInput) != '\0')///if cInput is array, *cInput is always equal to 'a'
    {
        nTempBuffer[(*cInput - '0')]++;

        if (nTempBuffer[*cInput - '0'] == 1)
        {
           // pcOutput[i++] = *cInput;
            printf("char %c \n", *cInput);
            *(pcOutput + i) = *cInput;
            i++;
        }

        cInput++;//if cInput is a array,cannot run ok
    }
    pcOutput[i] = '\0';

#else
    int j = 0,k=0;
    while (acInput[j] != '\0')
    {
        nTempBuffer[(acInput[j] - '0')]++;

        if (nTempBuffer[acInput[j] - '0'] == 1)
        {
            // pcOutput[i++] = *cInput;
            printf("char %c \n", acInput[j]);
            *(pcOutput + k) = acInput[j];
            k++;
        }
        j++;
    }
    pcOutput[k] = '\0';
#endif

    printf("source string:%s,\n processed string:%s\n", cInput, pcOutput);////cInput point to '\0'
	return 0;
}
