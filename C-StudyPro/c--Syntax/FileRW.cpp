// FileRW.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <exception>
#include <string>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    const char* pcFileName = "00.log";
    const char* pcText = "Pass\r\n";
    //const char* pcText2 = "\r\n";
#if 1
    /////////////first create and write
    FILE *m_pLog = NULL;
    try{
        m_pLog = _fsopen(pcFileName, "a+", _SH_DENYNO);

        if (NULL != m_pLog)
        {
            fprintf(m_pLog, "------------log start------------------:\n");
            fprintf(m_pLog, "New test content:\n");
            fprintf(m_pLog, "New test content:\n");
            fprintf(m_pLog, "New test content:\n");

            fflush(m_pLog);

            fclose(m_pLog);

            printf("Log file create and wrtie OK!\n");
        }

    }
    catch (exception e)
    {
        printf("Log file create fail!");
    }

    if (NULL != m_pLog)
    {
        fclose(m_pLog);
        m_pLog = NULL; 
    }
#endif

#if 1
    ////////////second open to write a header
    FILE *fp = NULL;
    try
    {
        fp = _fsopen(pcFileName, "rb+", _SH_DENYNO);//read/write...but log file must be exist
        ///must use rb+,binary mode, can read log data fully. 
        //if r+, each '\n' will be ignored by fread funcion

        ////
        fseek(fp, 0L, SEEK_END);///important
        size_t len = ftell(fp);
        if (len == -1L) 
        {
            printf("error\n"); 

        }
        printf("File length :%d bytes\n",len);

        char *pBuf = new char[len];
        memset(pBuf, 0, len);

        fseek(fp, 0L, SEEK_SET);// rewind(fp);///important
        size_t i = fread(pBuf, sizeof(char), len, fp);
        printf("read length:%d bytes\n", i);

        if (NULL != fp)
        {
            fseek(fp, 0L, SEEK_SET);
            //fprintf(fp, pcText);
            //fflush(fp);
           fwrite(pcText, 1, strlen(pcText), fp);
           fwrite(pBuf, 1, len, fp);
            //fseek(fp, 0L, SEEK_CUR);
            fclose(fp);

            printf("Log file create and wrtie OK!\n");
        }

        delete[] pBuf;
    }
    catch (exception e)
    {
        printf("No log file exist.");
    }

    if (NULL != fp)
    {
        fclose(fp);
        fp = NULL;
    }
#endif

	return 0;
}

