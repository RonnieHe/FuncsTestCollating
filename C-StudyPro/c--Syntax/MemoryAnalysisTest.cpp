// MemoryAnalysisTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}

/*
�����ڴ����ʹ��������·�Ϊ:
Free - û�б�ʹ�õ�
Image - ���ص��ڴ��ģ��(dll,exe��)
MappedFile - �ڴ�ӳ���ļ�
unclassified - ʵ����Ӧ���Ƕ�(heap)
Stack - ��ջ
TEB - �̻߳�����(thread environment block)
PEB - ���̻�����(process environment block)

�ڴ����ʹ�������ֿ��Է�Ϊ:
MEM_IMAGE  - ���ص��ڴ��ģ��(dll, exe��)
MEM_MAPPED - �ڴ�ӳ��
MEM_PRIVATE - ˽��(stack, heap, teb, peb��)

�ڴ����ʹ��״̬�ֿɷ�Ϊ:
MEM_FREE - ����
MEM_COMMIT - �Ѿ��ύ
MEM_RESERVE - ����

����ҳ�������ֿɷ�Ϊֻ�����ɶ�д����ִ�У�дʱ�����ȡ�

��Ӵ����ڴ�Ӧ����: Module(Image), Heap, Stack


////////////
taskmgr.exeģ�����ڴ��з�Ϊ4�飬
��һ����ֻ����, ʵ������PE�ļ�ͷ��
�ڶ����ǿ�ִ�еģ�ʵ���Ͼ��Ǵ���ڣ�.text��;
�������ǿɶ�д��,ʵ�������ݽ�(.Data)�� 
���һ��Ҳ��ֻ����,ʵ������Դ��(.rsrc)��


*/



//ȫ�ֱ����;�̬�����ᱻ���뵽��ִ���ļ������ݽ�(��ֻ���Ϳɶ�д)��, �Ǿ�̬�ľֲ�����������ڶ�ջ(stack)�ϣ���new(malloc)�������ڴ�������ڶ�(heap)�ϡ�
/*
��ַ 400000 - 401000 : PE�ļ�ͷ��������ֻ��
��ַ 401000 - 41d000 : .text, ������ֻ����ִ�У���ʾ�����
��ַ 41d000 -  422000 : .rdata, ������ֻ���� ��ʾֻ������
��ַ 422000 -  426000 : .data, ������д��ʱ��������ʾ�ɶ�д����
��ַ 426000 - 427000 : .rsrc, ������ֻ������ʾ��Դ��

*/
#include <iostream>

using namespace  std;



const char* global_const_string = "hello world \n";

int global_int = 20;

static int global_static_int = 30;


int main()

{

    static int local_static_int = 100;

    int local_int = 200;

    int* pValue = new int(300);



    cout << global_const_string << global_int

        << global_static_int << local_static_int

        << local_int << *pValue;


    delete pValue;


    system("pause");


    return 0;

}
