
#include "stdafx.h"
#include<iostream>  
//#include<cstdio>  
//#include<memory>  
#include <Windows.h>
using namespace std;
#pragma warning(disable: 4996)

#include <stdio.h>  //printf

#define Test_Power
#ifdef Test_Power
void IsACadapterConnected();
#endif

//#define Test_Event
#ifdef Test_Event
#define EVENT_NAME TEXT("Global\\PVT_NOTIFY_EVENT")
//#define EVENT_NAME TEXT("Global\\WANGMA_NOTIFY")
void setEventPro();
#endif

//#define ProcessCall
#ifdef ProcessCall
void CallProcess();
#endif

#ifdef Find_Driver

#include <Setupapi.h>
#pragma comment(lib,"Setupapi.lib")
#include <algorithm>

#include "Shlwapi.h" ///pathfileexists
#pragma comment(lib,"Shlwapi.lib")

HKEY findReg();
//HKEY QueryKey(HKEY parent_hKey, LPCSTR lpSubKey);
bool IsDriverInstalled(std::string sINFname);

#define REG_INF_PATH       "DeviceDesc"//"Mfg"
#define NAME_DRIVER_CAT    "LYNXPOINT.CAT"//"UDE.CAT"

bool IsUDEMatch();
bool getConfigTimeStamp(int* nTyear, int* nTmon, int* nTday);
bool getUDEDriverTimeStamp(int* nTyear, int* nTmon, int* nTday);
bool IsDriverInstalled(std::string strInfName, int* nTyear, int* nTmon, int* nTday);
bool IsDriverRegFound(std::string &strINFname);

#include <Setupapi.h>
#pragma comment(lib,"Setupapi.lib")

#define ID_PCI_HARDWARE    "VEN_8086&DEV_8C1A"//"VEN_8086&DEV_0C00"//"VEN_8086&DEV_7360"
#define NAME_DRIVER_CAT    "LYNXPOINT.CAT"//""//"UDE.CAT"
#define REG_KEY_DEVENUM    "SYSTEM\\CurrentControlSet\\Enum\\" 
#define REG_INF_DEVDES       "DeviceDesc"//
#define REG_INF_MFG          "Mfg"


#define BUFFERSIZE        256

#define CONFIG_SEC_TITLE     "BASE_CONFIG"
#define CONFIG_SEC_UDELIMIT   "UDE_LIMIT"
#define CONFIG_SEC_TIMESTAMP  "UDE_TIMESTAMP"
#endif  



#ifdef Killpro

#define FLS_DBDIR	"FirmwareData\\"
#define FLS_DBBKDIR "FirmwareData_bk\\"
#define FLS_PREDBBKDIR "FirmwareData_bk_bk\\"
#define APP_CONFIG	 "config\\"

//#define FLS_DOWNLOAD "Firmware\\Intel\\"  //"download\\"
//#define FLS_FLASH	 "Firmware\\Firmwareflash\\"	// Modem folder,which will be flashed to module      //// "FirmwareFlash\\"
#define FLS_FIRMWARE_PATH    "Firmware\\"
#define FLS_DOWNLOAD         "Intel\\"  //"download\\"
#define FLS_FLASH	          "Firmwareflash\\"	//

#include <TlHelp32.h>
#pragma comment(lib, "Shlwapi.lib")
#include "algorithm"
BOOL  KillProcess(std::string strProcessName)
{
	//char* p_exeName = NULL;
	//char str_exeTemp[MAX_PATH] = { 0 };
    printf("KillProcess %s enter", strProcessName.c_str());

	BOOL b_close = FALSE;
	HANDLE hProcessSnap = INVALID_HANDLE_VALUE;
	HANDLE hProcess = NULL;
	PROCESSENTRY32 pe32 = { 0 };

	std::string strTmpName;
	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printf(("KillProcess::CreateToolhelp32Snapshot (of processes)"));
		goto clearup;
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32))
	{
		printf(("KillProcess::Process32First fail: %d"), GetLastError());
		goto clearup;
	}

	///makelowe
	transform(strProcessName.begin(), strProcessName.end(), strProcessName.begin(), ::tolower);
	// Now walk the snapshot of processes
	// find matched process and shutdown it

	do
	{
		//_strlwr_s(pe32.szExeFile);
		//if (_stricmp(p_exeName, pe32.szExeFile) == 0)
		strTmpName = pe32.szExeFile;
		transform(strTmpName.begin(), strTmpName.end(), strTmpName.begin(), ::tolower);
		if (strTmpName.compare(strProcessName) == 0)
		{
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
			if (hProcess != NULL)
			{
				TerminateProcess(hProcess, 1);
				Sleep(1000);
				CloseHandle(hProcess);

				printf(("KillProcess:: Close process success."));
				b_close = TRUE;
			}
			else
			{
				printf(("KillProcess:: Open Process Fail: %d ."), GetLastError());
			}
			break;
		}

	} while (Process32Next(hProcessSnap, &pe32));


clearup:

	if (INVALID_HANDLE_VALUE != hProcessSnap)
		CloseHandle(hProcessSnap);

	printf("KillProcess done(%s)", b_close ? "TRUE" : "FALSE");
	return b_close;
}
#endif

#ifdef sort_delete_func
void solve(char *str, int len)
{
	int i, hash[256];
	memset(hash, 0, sizeof(hash));

	for (i = 0; i < len; ++i)//hash数组的各值均为0
	{
		if (0 == hash[str[i]])///将待排序字符本身的ASCII码值作为数组下标值，分别将各字符码对应的hash数组的值改为1，
			hash[str[i]] = 1;
	}
	for (i = 0; i < 256; ++i)//依次输出hash数组中为1的各下标对应的char
	{
		if (0 != hash[i])
			putchar(i);
	}
	printf("\n");
}
#endif


//#define test_dll
#ifdef test_dll

#include <Windows.h>

HINSTANCE gdllHandle = NULL;
bool loadIntelDownloadDLL()
{
	bool bRes = false;
	gdllHandle = LoadLibrary(_T("WWANFirmwareFlash.dll"));///unicode may error path,,need x64
	printf("Loadlibrary gdllHandle=%d \r\n", gdllHandle);
	if (NULL != gdllHandle)
	{
		printf("[Infomation] WWANFirmwareFlash.dll load success.\r\n");
		bRes = true;
	}
	else
	{
		printf("[Error] WWANFirmwareFlash.dll load fail. Code %d \r\n",
			GetLastError());

		bRes = false;
	}

	///only start the dll, no need to use it in process
	//FreeLibrary(gdllHandle);

	return bRes;
}
void unloadIntelDownloadDll()
{
	printf("Preprare release gdllHandle=%d \r\n", gdllHandle);
	if (NULL != gdllHandle)
	{
		FreeLibrary(gdllHandle);
		gdllHandle = NULL;
	}
	printf("After release gdllHandle=%d \r\n", gdllHandle);
}

#include <conio.h>//getch
bool bLoop = true;
bool bReleaseOpen = false;
LRESULT CALLBACK WaitESC()
{
	char ch = '0';
	while ((ch = getch()) != 0x1B);
	{
			bLoop = false;
	}
	return FALSE;
}

#endif

#ifdef FILE_Test

#define LOG_NAME "blog.txt"
#define LOG_NAME_BK "blog_bk.txt"
void DeletePreBkPath()
{
	bool bIsBackupNeed = false;

	char str_path[MAX_PATH * 2] = { 0 };
	char str_path_bk[MAX_PATH * 2] = { 0 };

	char str_pathTmp[MAX_PATH * 2] = { 0 };
	char str_runTmpPath[MAX_PATH * 2] = { 0 };

	GetModuleFileNameA(NULL, str_pathTmp, MAX_PATH * 2);

	memcpy(str_runTmpPath, str_pathTmp, MAX_PATH * 2);
	char *pSeperator = strrchr(str_runTmpPath, '\\');
	*(++pSeperator) = '\0';

	//pSeperator = strrchr(str_runTmpPath, '\\');
	//*(++pSeperator) = '\0';
	//m_strFWtoolPath = str_runTmpPath;

	std::string str_file = str_runTmpPath;
	str_file += LOG_NAME;
	memcpy(str_path, str_file.c_str(), str_file.length());

	std::string str_filebk = str_runTmpPath;
	str_filebk += LOG_NAME_BK;
	memcpy(str_path_bk, str_filebk.c_str(), str_filebk.length());

///get file size
	WIN32_FIND_DATA fileInfo;
	HANDLE hFind;
	DWORD fileSize = 0;
	////const char *fileName = 文件的路径及名字;
	hFind = FindFirstFile(str_path, &fileInfo);
	if (hFind != INVALID_HANDLE_VALUE)
		fileSize = fileInfo.nFileSizeLow;
	printf(" File size=%d \r\n", fileSize);

	if (fileSize > 50*1024)
		bIsBackupNeed = true;
		//printf(" File size > 50k");
	FindClose(hFind);

///rename and backup
	if (bIsBackupNeed)
	{
		SHFILEOPSTRUCT sFileOp = { 0 };
		sFileOp.hwnd = NULL;
		sFileOp.wFunc = FO_RENAME;//FO_DELETE;//
		sFileOp.pFrom = str_path;//文件或文件夹路径
		sFileOp.pTo = str_path_bk;
		sFileOp.fFlags = FOF_NO_UI;// FOF_ALLOWUNDO;//此标志使删除文件备份到Windows回收站 
		sFileOp.hNameMappings = NULL;
		sFileOp.lpszProgressTitle = NULL;
		SHFileOperation(&sFileOp);//execute delete

	}
}
#endif
int main(void)
{
	int len;
	char str[1000];

#ifdef sort_delete_func
	while (scanf("%s", str) != EOF)
	{
		len = strlen(str);
		solve(str, len);
	}
#endif

#ifdef ICCID_test

	int nIndex = 0;
	string str_iccid = "893144030143549804F";

	string  str_iccIdTmp1 = "89314403014354980661";
	string 	str_iccIdTmp2 = "89314403014354981661";

	//printf("Please enter range-min:");
	//char cICCIDMin[21] = { 0 };
	//scanf("%s", cICCIDMin);
	//str_iccIdTmp1 = cICCIDMin;
	//printf("Please enter range-max:");
	//char cICCIDMax[21] = { 0 };
	//scanf("%s", cICCIDMax);
	//str_iccIdTmp2 = cICCIDMax;

	//while (1)
	//{ 
	//	printf("Please enter ICCID:");
	//	char cICCID[21] = { 0 };
	//	scanf("%s", cICCID);

	//	str_iccid = cICCID;

	printf(" ICCID length=%d \r\n", str_iccid.length());

	std::string  strTableFront, strTargetFront;

	int nLength = str_iccIdTmp1.length();
	printf("str_iccIdTmp1 nLength=%d \r\n", nLength);

	if (str_iccIdTmp1.compare(str_iccIdTmp2) == 0)//if min equal max
	{
		nIndex = nLength;
		printf("str_iccIdTmp1 is equal str_iccIdTmp2,  nLength=%d ,nIndex=%d \r\n", nLength, nIndex);
	}
	else
	{
		for (int i = 0; i < nLength; i++) //string类的size()/length()方法返回的是字节数，不管是否有汉字
		{
			if (str_iccIdTmp1[i] != str_iccIdTmp2[i])
			{
				nIndex = i;
				break;
			}
		}
	}
	printf("str_iccIdTmp1 nIndex=%d \r\n", nIndex);

	strTableFront = str_iccIdTmp1.substr(0, nIndex);//
	strTargetFront = str_iccid.substr(0, nIndex);
	printf("xml Rang,strTableFront=%s, strTargetFront=%s,nIndex=%d \r\n", strTableFront.c_str(), strTargetFront.c_str(), nIndex);

	if (strTargetFront.compare(strTableFront) == 0)
	{
		int nMin = strtol((str_iccIdTmp1.substr(nIndex)).c_str(), NULL, 16);
		int  nMax = strtol((str_iccIdTmp2.substr(nIndex)).c_str(), NULL, 16);
		int nTarget = strtol((str_iccid.substr(nIndex)).c_str(), NULL, 16);

		printf("nMin=%x,nMax=%x,nTarget=%x \r\n", nMin, nMax, nTarget);

		if ((nTarget >= nMin) && (nTarget <= nMax))
		{
			printf("Success match in range\r\n");
		}
		else
			printf("Not in Range\r\n");
	}
	else
		printf("Not in table\r\n");

	//}


#endif
#ifdef test_dll
	DWORD dwWaitESC = 0;
	HANDLE hWaitESC = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)WaitESC,
		NULL,
		CREATE_SUSPENDED,
		&dwWaitESC);
	ResumeThread(hWaitESC);

	int i = 0;
	while (bLoop & i< 9999)
	{
		printf("Test %d:\r\n",++i);
		loadIntelDownloadDLL();
		Sleep(3000);
		//if (bReleaseOpen)
			unloadIntelDownloadDll();
			Sleep(500);
	}
	printf("!!! Complete, total %d!!!\r\n",i);
#endif

#ifdef system_path
	TCHAR szPath[MAX_PATH];
	DWORD ret;
	 GetWindowsDirectory(szPath, MAX_PATH);
	if (!ret) {
		printf("GetWindowsDirectory fail (%ld)\n", GetLastError());
		return FALSE;
	}
	printf("GetWindowsDirectory -> %s\n", szPath);

	std::string m_str_flsDataPath;

	// umdf download new firmware packet path
	std::string m_str_umdfDownPath;

	// service run path
	std::string m_str_runPath;

	// fls and nvm back path
	std::string m_str_flsBackPath;

	// flash path
	std::string m_str_flashPath;

	// config path
	std::string m_str_configPath;

	// prebk path
	std::string m_str_preBkPath;

	// reg path

	std::string m_str_regPath;

	char str_FWTmp[MAX_PATH] = { 0 };
	GetSystemDirectory(str_FWTmp, MAX_PATH);

	char* p_last = strrchr(str_FWTmp, '\\');
	std::string strMonitorPath;
	if (NULL != p_last)
	{
		*(++p_last) = '\0';

		strMonitorPath=(str_FWTmp);

		strMonitorPath += FLS_FIRMWARE_PATH;

		m_str_umdfDownPath = strMonitorPath + FLS_DOWNLOAD;
		m_str_flashPath = strMonitorPath + FLS_FLASH;//To be flashed to module
	}

	printf("strMonitorPath:%s\r\n,m_str_umdfDownPath -> %s\r\n,m_str_umdfDownPath -> %s\r\n ", strMonitorPath.c_str(), m_str_umdfDownPath.c_str(), m_str_flashPath.c_str());
#endif

#ifdef FILE_Test
	DeletePreBkPath();
#endif 
#ifdef Killpro
	KillProcess("FwUpdatePro.exe");
#endif


#ifdef Find_Driver
	//findReg();


	if (IsUDEMatch())
	{
		printf(">>>MachCheck is pass\r\n");
	}
	else
		printf(">>>MachCheck is not pass\r\n");

#endif

#ifdef ProcessCall
	CallProcess();
#endif

#ifdef Test_Event
	setEventPro();
#endif

#ifdef Test_Power
	IsACadapterConnected();
	getchar();//暂停程序
	IsACadapterConnected();
#endif

	getchar();//暂停程序
	return 0;
}

#ifdef ProcessCall

#define path1   "C:\\Program Files (x86)\\Intel_XMM7360\\L850_FWUpdateTool.exe" 
#define param   "    -disablewindow  -updatemode=force "
#define path   "\"C:\\Program Files (x86)\\Intel_XMM7360\\L850_FWUpdateTool.exe\"   -disablewindow  -updatemode=force " 
//#define path "C:\\Program Files (x86)\\Intel_XMM7360\\L850_FWUpdateTool.exe   -disablewindow  -updatemode=force " 

void CallProcess()
{
	printf("RunOnekeyTool Enter >>:\r\n");
	BOOL b_run = FALSE;
	DWORD dwExitCode = 0;

	//std::string str_exeName = CGlobalEnv::GetInstance()->GetFWtoolPath();

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	//// 
	//char str_debug[MAX_PATH] = { 0 };
	//sprintf_s(str_debug, "%s  -disablewindow  -updatemode=force ", str_exeName.c_str());

	
#if 1
	printf("[Info][RunOnekeyTool] RunOnekeyTool cmdline = [%s] \r\n", path1);
	BOOL b_create = CreateProcess(path1, param, NULL, NULL, FALSE, 0, NULL, NULL,
		&si, &pi);
#else
	printf("[Info][RunOnekeyTool] RunOnekeyTool cmdline = [%s] \r\n", path);
	BOOL b_create = CreateProcess(NULL, path, NULL, NULL, FALSE, 0, NULL, NULL,
		&si, &pi);
#endif

	if (b_create)
	{
		DWORD dw_wait = WaitForSingleObject(pi.hProcess, 120000);
		if (WAIT_TIMEOUT == dw_wait)
		{
			TerminateProcess(pi.hProcess, 0);
		}
		else
		{
			GetExitCodeProcess(pi.hProcess, &dwExitCode);
			printf("[Info][CRegistryHelper::RunOnekeyTool] GetExitCodeProcess = %d.\r\n", dwExitCode);

			if( 0 == dwExitCode )
				b_run = TRUE;
		}

		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
	else 
	{
		printf(	"[Error][RunOnekeyTool] CreateProcess fail with %d.\r\n",GetLastError());
	}

	printf("<< RunOnekeyTool done \r\n");
}
#endif

#ifdef Find_Driver
HKEY findReg()
{
	printf( "[Info]findReg Enter: >> \r\n");
	HDEVINFO hDeviceInfo;
	PSP_DEVINFO_DATA DeviceInfoDataDetail = NULL;
	SP_DEVINFO_DATA DeviceInfoData;
	BOOL bResult;
	HRESULT ErrorCode = 0;

	HKEY hReskey = NULL;

	hDeviceInfo = SetupDiGetClassDevs(
		NULL,
		"PCI",
		NULL,
		DIGCF_PRESENT | DIGCF_ALLCLASSES);

	if (INVALID_HANDLE_VALUE == hDeviceInfo)
	{
		ErrorCode = GetLastError();
		return 0;
	}

	SP_DEVINFO_DATA sDevInfoData;
	sDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	std::string strText;
	char szDIS[MAX_PATH]; // Device Identification Strings   
	DWORD nSize = 0;

	BOOL RetCode = FALSE;

	//RetCode = SetupDiEnumDeviceInfo(hDeviceInfo, 0, &sDevInfoData);
	//ErrorCode = GetLastError();

	for (int i = 0; SetupDiEnumDeviceInfo(hDeviceInfo, i, &sDevInfoData); i++)
	{
		nSize = 0;
		if (!SetupDiGetDeviceInstanceId(hDeviceInfo, &sDevInfoData, szDIS, sizeof(szDIS), &nSize))
		{
			ErrorCode = GetLastError();
			continue;
		}

		std::string strDIS_upper(szDIS);  //
		transform(strDIS_upper.begin(), strDIS_upper.end(), strDIS_upper.begin(), ::toupper);

		//HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\PCI\VEN_8086&DEV_0C00&SUBSYS_061C1028&REV_06
		if (strDIS_upper.find(ID_PCI_HARDWARE) != std::string::npos)
		{
			printf("[Info]SetupDiGetDeviceInstanceId to find %s \r\n", szDIS);
			std::string temp = szDIS;
			//"PCI\\VEN_8086&DEV_0C00&SUBSYS_061C1028&REV_06\\3&11583659&0&00"	
			///If multi instance exist????? how to enum?

			std::string regName = REG_KEY_DEVENUM + temp;

			printf("[Info]PCI-7360 found, findReg to find %s \r\n", regName.c_str());

			///to read the key value
			long lRet = 0;
			char     szValue[256] = { 0 };
			DWORD    sz_regType = REG_SZ;
			DWORD	 dw_dataLen = sizeof(szValue);
			HKEY hy = NULL;

			lRet= RegOpenKeyEx(HKEY_LOCAL_MACHINE, regName.c_str(), 0, KEY_QUERY_VALUE, &hy);
			if (lRet == ERROR_SUCCESS)
			{
				lRet = RegQueryValueEx(hy, REG_INF_PATH, NULL, &sz_regType, (LPBYTE)&szValue, &dw_dataLen);

				if (lRet == ERROR_SUCCESS)
				{
					printf("Read %s= %s \r\n", REG_INF_PATH,szValue);
					int i = 1, j = 0;
					char  szValue2[256] = { 0 };
					while (szValue[i] != ',')
					{
						szValue2[j] = szValue[i];
						i++;
						j++;
					}
					szValue2[j] = '\0';
					printf("Get driverName={%s}\r\n", szValue2);

					IsDriverInstalled(szValue2);
					break;
				}
				else
				{
					printf("[Error] RegQueryValueEx(REG_INF_PATH) fail, code=%d \r\n", GetLastError());
				}
			}
			else
			{
				printf("[Error] RegOpenKeyEx(InstancePath) fail(), code=%d \r\n", GetLastError());
			}

			  if (NULL != hy)
				  RegCloseKey(hy);
			////to enum chid key.... No use here
			//HKEY hkey = QueryKey(HKEY_LOCAL_MACHINE, regName.c_str());

			//if (hkey)
			//{
			//	printf("[Info]GNSS port reg found OK.\r\n");
			//	hReskey = hkey;
			//	break;
			//}
		}
	}

	SetupDiDestroyDeviceInfoList(hDeviceInfo);
	printf("[Info]findReg Done << \r\n");
	return hReskey;
}

#define MAX_KEY_LENGTH 1024
HKEY QueryKey(HKEY parent_hKey, LPCSTR lpSubKey)
{
	static int deep = 0;
	deep++;
	HKEY result = 0, hKey = 0, child_result = 0;

	printf("\r\n [Info]QueryKey Enter,lpSubKey=%s ,deep=%d \r\n", lpSubKey, deep);

	if (RegOpenKeyEx(parent_hKey,
		lpSubKey,
		0,
		KEY_READ,
		&hKey) != ERROR_SUCCESS
		)
	{
		deep--;
		printf("RegOpenKeyEx fail to exit, deep=%d \r\n", lpSubKey, deep);
		return 0;
	}

	CHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name  
	DWORD    cbName;                   // size of name string   
	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name   
	DWORD    cchClassName = MAX_PATH;  // size of class string   
	DWORD    cSubKeys = 0;               // number of subkeys   
	DWORD    cbMaxSubKey;              // longest subkey size   
	DWORD    cchMaxClass;              // longest class string   
	DWORD    cValues;              // number of values for key   
	DWORD    cchMaxValue;          // longest value name   
	DWORD    cbMaxValueData;       // longest value data   
	DWORD    cbSecurityDescriptor; // size of security descriptor   
	FILETIME ftLastWriteTime;      // last write time   

	DWORD i, retCode;

	// Get the class name and the value count.   
	retCode = RegQueryInfoKey(
		hKey,                    // key handle   
		achClass,                // buffer for class name   
		&cchClassName,           // size of class string   
		NULL,                    // reserved   
		&cSubKeys,               // number of subkeys   
		&cbMaxSubKey,            // longest subkey size   
		&cchMaxClass,            // longest class string   
		&cValues,                // number of values for this key   
		&cchMaxValue,            // longest value name   
		&cbMaxValueData,         // longest value data   
		&cbSecurityDescriptor,   // security descriptor   
		&ftLastWriteTime);       // last write time   

	if (cSubKeys)
	{
		for (i = 0; i<cSubKeys; i++)
		{
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, i,
				achKey,
				&cbName,
				NULL,
				NULL,
				NULL,
				&ftLastWriteTime);

			if (retCode != ERROR_SUCCESS)
			{
				deep--;
				result = 0;
				goto lret;
			}
			printf("[Info]RegEnumKeyEx ,find %s.\r\n", achKey);

			DWORD nTest = 0;
			//read_reg(hKey);


			//if (strcmp("GNSS", achKey))
			//{
			//	//m_p_log->WriteToLog(normallog, "[Info]RegEnumKeyEx ,find %s.", achKey);
			//	child_result = QueryKey(hKey, achKey);
			//	if (child_result)
			//	{
			//		printf("[Info]RegEnumKeyEx find child-gnss key.");
			//		result = child_result;
			//		goto lret;
			//	}

			//}
			//else
			//{
			//	printf("[Info]RegEnumKeyEx find gnss key.");
			//	result = hKey;
			//	goto lret;
			//}
		}
	}

lret:
	deep--;
	if (result != hKey)
		RegCloseKey(hKey);

	printf("[Info]QueryKey Done.\r\n");
	return result;
}

//bool read_reg(HKEY hkey)
//{
//	printf("[Info]read_reg enter");
//
//	long lRet;
//	HKEY hKey = NULL;
//	TCHAR tchData[64];
//	DWORD dwSize = 8;
//	bool result = false;
//	lRet = RegOpenKeyEx(
//		hkey,
//		"GNSS\\function0",
//		0,
//		KEY_QUERY_VALUE,
//		&hKey
//		);    //打开注册表
//
//	char     szValue[125] = { 0 };
//	DWORD    sz_regType = REG_SZ;
//	DWORD	 dw_dataLen = sizeof(szValue);
//
//	if (lRet == ERROR_SUCCESS)//读操作成功
//	{
//		//lRet = RegGetValue(
//		//	hKey,
//		//	"DeviceDesc",
//		//	NULL,
//		//	NULL,
//		//	(LPBYTE)&out_ret,
//		//	&dwSize
//		//	);    //如果打开成功，则读
//
//		RegQueryValueEx(hKey, "Mfg", NULL, &sz_regType, (LPBYTE)&szValue, &dw_dataLen);
//
//		if (lRet == ERROR_SUCCESS)
//		{
//			printf("Read DeviceDesc %s", szValue);
//			result = true;
//		}
//		else
//		{
//			printf("[Error] RegQueryValueEx(GNSS\\function0\Enabled) fail, code=%d ", GetLastError());
//		}
//	}
//	else
//	{
//		printf("[Error] RegOpenKeyEx(GNSS\\function0) fail, code=%d ", GetLastError());
//	}
//
//	if (NULL != hKey)
//		RegCloseKey(hKey);
//
//	printf("[Info]read_reg done");
//	return result;
//}


bool IsDriverInstalled(std::string strInfName)
{
	printf("To check UDE driver \r\n");
	bool m_bIsDriverInstalled = false;

	HINF hInf = NULL;
	INFCONTEXT curContext, nextContext;

	CHAR szBuffer[MAX_PATH] = { 0 };
	std::string sINFname;
	if (0 == GetWindowsDirectory(szBuffer, sizeof(szBuffer)))//fail return 0
	{
		//memcpy(szBuffer, "C:\\windows\\inf\\oem",);
		//sINFname = "C:\\windows\\inf\\oem";
		sINFname = "C:\\windows\\inf\\";
	}
	else
	{
		sINFname = szBuffer;
		//sINFname += "\\inf\\oem";
		sINFname += "\\inf\\";
	}

	printf("System INF Path = %s ,INF = %s\r\n", sINFname.c_str(), strInfName.c_str());




	UINT errorLine;
	//for (int i = 3; i < 300; i++)
	{
		//int i = 32;
		CHAR szBuffer[MAX_PATH] = { 0 };
		CHAR buffer[MAX_PATH*2] = { 0 };
		std::string strContext;

		/// *****
		//sprintf(szBuffer, "%s%d.inf", sINFname.c_str(), i);
		sprintf(szBuffer, "%s%s", sINFname.c_str(), strInfName.c_str());

		printf(">>Open INF = %s \r\n", szBuffer);///open directly
		hInf = SetupOpenInfFile(szBuffer, "System", INF_STYLE_WIN4, &errorLine);
		if (hInf == INVALID_HANDLE_VALUE)
		{
			return false;
			//continue;//return;
		}
		///the flashusb.inf contain onlye one key in manufacture
		SetupFindFirstLine(hInf, "Version", "CatalogFile", &curContext);//to get manufacture first key............section=5,line=0
		SetupGetLineText(&curContext, NULL, NULL, NULL, buffer, BUFFERSIZE, NULL);

		printf("SetupGetLineText= %s \r\n", buffer);

		strContext = buffer;
		transform(strContext.begin(), strContext.end(), strContext.begin(), ::toupper);

		printf("strContext= %s \r\n", strContext.c_str());
		//if (tempStr.Find(L"UDE.CAT") >= 0)//if (tempStr.Find(L"{36FC9E60-C465-11CF-8056-444553540000}") >= 0)//USB generic GUID,cannot used
		if (strContext.find(NAME_DRIVER_CAT) != std::string::npos)
		{
			std::string strVer;
			memset(buffer,0,MAX_PATH * 2);
			//std::string strVER;
			SetupFindFirstLine(hInf, "Version", "DriverVer", &curContext);//
			SetupGetLineText(&curContext, NULL, NULL, NULL, buffer, BUFFERSIZE, NULL);//to get the fist key info....IMC_FLASH,ntamd64
			strVer = buffer;
			printf("Find driver, DriverVer:%s \r\n",  buffer);

			//DriverVer=03/12/2018,0.9.3.36
			std::string str_IMEIcode;
			std::string::size_type size_start;
			std::string::size_type size_end;

			size_start = strVer.find('/');		//size_end = str_response.rfind("\"");
			std::string sMon = strVer.substr(0, size_start);
			strVer = strVer.substr(size_start + 1, strVer.length() - size_start - 1);

			size_start = strVer.find('/');
			std::string sDay = strVer.substr(0, size_start);
			strVer = strVer.substr(size_start + 1, strVer.length() - size_start - 1);

			size_start = strVer.find(',');
			std::string sYear = strVer.substr(0, size_start);

			char *stop = NULL;
			//  i = static_cast<int>(strtol(s.c_str(), &end, 16));
			int nMon = static_cast<int>(strtol(sMon.c_str(), &stop, 10));
			int nDay = static_cast<int>(strtol(sDay.c_str(), &stop, 10));
			int nYear = static_cast<int>(strtol(sYear.c_str(), &stop, 10));

			printf("Driver Mon:%ws(%d) / Day:%ws(%d)  /Year:%ws(%d) \r\n", sMon, nMon, \
				sDay, nDay, sYear, nYear);


			m_bIsDriverInstalled = true;
		}
		SetupCloseInfFile(hInf);
	}


	if (!m_bIsDriverInstalled)
		printf("No UDE driver installed!\r\n");

	return m_bIsDriverInstalled;
}



bool IsUDEMatch()
{
	bool bRes = true;
	int nDevYear = 0, nDevMon = 0, nDevDay = 0;
	int nConYear = 0, nConMon = 0, nConDay = 0;

	printf("IsUDEMatch etner");
	if (getConfigTimeStamp(&nConYear, &nConMon, &nConDay))//enalbe and get valid timestamp
	{
		if (getUDEDriverTimeStamp(&nDevYear, &nDevMon, &nDevDay))
		{
			///Compare here.....Driver Timestamp must bigger or equal than Config Timestamp
			printf("Driver timestamp Year:%d Mon:%d Day:%d   \r\n Config timestamp Year:%d Mon:%d Day:%d \r\n ", \
				nDevYear, nDevMon, nDevDay, nConYear, nConMon, nConDay);

			if (nDevYear < nConYear)
			{
				bRes = false;
			}
			else if (nDevYear == nConYear)
			{
				if (nDevMon < nConMon)
				{
					bRes = false;
				}
				else if (nDevMon == nConMon)
				{
					if (nDevDay < nConDay)
					{
						bRes = false;
					}
				}
			}

		}
		else ///cannot get correct UDE info
		{
			bRes = false;
		}

	}

	return bRes;
}

/*
To check if limit is enable or disable;
if enable, to get Year/Mon/Day value

*/
bool getConfigTimeStamp(int* nTyear, int* nTmon, int* nTday)
{
	bool bRes = false;

	char cCurrentPath[MAX_PATH] = { 0 };
	char cConfigFile[MAX_PATH] = { 0 };
	char cKeyValue[MAX_PATH] = { 0 };

	//memset(cCurrentPath, 0x00, sizeof(cCurrentPath));
	//memset(cConfigFile, 0x00, sizeof(cConfigFile));
	//memset(cKeyValue, 0x00, sizeof(cKeyValue));

	GetCurrentDirectory(MAX_PATH, cCurrentPath);
	sprintf(cConfigFile, "%s\\fbconfig.ini", cCurrentPath);

	if (FALSE == PathFileExistsA(cConfigFile))///no config file.
	{
		return bRes;
	}

	int nEnable = GetPrivateProfileInt(CONFIG_SEC_TITLE, CONFIG_SEC_UDELIMIT, 0, cConfigFile);
	if (nEnable == 1)
	{
		GetPrivateProfileString(CONFIG_SEC_TITLE, CONFIG_SEC_TIMESTAMP, "", cKeyValue, sizeof(cKeyValue), cConfigFile);

		printf("Find config Timestamp :%s \r\n", cKeyValue);
		std::string strVer = cKeyValue;


		//DriverVer=03/12/2018,0.9.3.36
		std::string str_IMEIcode;
		std::string::size_type size_start;
		std::string::size_type size_end;

		size_start = strVer.find('/');		//size_end = str_response.rfind("\"");
		std::string sMon = strVer.substr(0, size_start);
		strVer = strVer.substr(size_start + 1, strVer.length() - size_start - 1);

		size_start = strVer.find('/');
		std::string sDay = strVer.substr(0, size_start);
		strVer = strVer.substr(size_start + 1, strVer.length() - size_start - 1);

		size_start = strVer.find(',');
		std::string sYear = strVer.substr(0, size_start);

		char *stop = NULL;
		//  i = static_cast<int>(strtol(s.c_str(), &end, 16));
		int nMon = static_cast<int>(strtol(sMon.c_str(), &stop, 10));
		int nDay = static_cast<int>(strtol(sDay.c_str(), &stop, 10));
		int nYear = static_cast<int>(strtol(sYear.c_str(), &stop, 10));

		printf("Driver Mon:%ws(%d) / Day:%ws(%d)  /Year:%ws(%d) \r\n", sMon, nMon, \
			sDay, nDay, sYear, nYear);

		*nTyear = nYear;
		*nTmon = nMon;
		*nTday = nDay;

		bRes = true;
	}

	return bRes;
}


/*
To get the current UDE driver version, get Year/Mon/Day value
*/

bool getUDEDriverTimeStamp(int* nTyear, int* nTmon, int* nTday)
{
	bool bRes = false;
	std::string strName;
	if (IsDriverRegFound(strName))
	{
		if (IsDriverInstalled(strName, nTyear, nTmon, nTday))
		{
			bRes = true;
		}
	}

	return bRes;
}

bool IsDriverRegFound(std::string &strINFname)
{
	printf("IsDriverRegFound  Enter: >> \r\n");
	HDEVINFO hDeviceInfo;
	PSP_DEVINFO_DATA DeviceInfoDataDetail = NULL;
	//SP_DEVINFO_DATA DeviceInfoData;
	SP_DEVINFO_DATA sDevInfoData;
	sDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	bool bResult = false;

	hDeviceInfo = SetupDiGetClassDevs(
		NULL,
		"PCI",
		NULL,
		DIGCF_PRESENT | DIGCF_ALLCLASSES);

	if (INVALID_HANDLE_VALUE == hDeviceInfo)
	{
		printf("[Error]SetupDiGetClassDevs fail with 0x%x", GetLastError());
		return bResult;
	}

	//char szDIS[MAX_PATH]; // Device Identification Strings   
	DWORD nSize = 0;
	//RetCode = SetupDiEnumDeviceInfo(hDeviceInfo, 0, &sDevInfoData);
	//ErrorCode = GetLastError();

	for (int i = 0; SetupDiEnumDeviceInfo(hDeviceInfo, i, &sDevInfoData); i++)
	{
		nSize = 0;
		char szDIS[MAX_PATH] = { 0 };
		if (!SetupDiGetDeviceInstanceId(hDeviceInfo, &sDevInfoData, szDIS, sizeof(szDIS), &nSize))
		{
			printf("[Error]SetupDiGetDeviceInstanceId fail with 0x%x", GetLastError());
			continue;
		}

		std::string strDIS_upper(szDIS);  //
		transform(strDIS_upper.begin(), strDIS_upper.end(), strDIS_upper.begin(), ::toupper);

		//HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\PCI\VEN_8086&DEV_0C00&SUBSYS_061C1028&REV_06
		if (strDIS_upper.find(ID_PCI_HARDWARE) != std::string::npos)
		{
			printf("[Info]SetupDiGetDeviceInstanceId to find %s \r\n", szDIS);
			std::string temp = szDIS;
			//"PCI\\VEN_8086&DEV_0C00&SUBSYS_061C1028&REV_06\\3&11583659&0&00"	
			///If multi instance exist????? how to enum?

			std::string regName = REG_KEY_DEVENUM + temp;

			printf("[Info]PCI-7360 found, findReg to find %s \r\n", regName.c_str());

			///to read the key value
			long lRet = 0;
			char     szValue[256] = { 0 };
			DWORD    sz_regType = REG_SZ;
			DWORD	 dw_dataLen = sizeof(szValue);
			HKEY hy = NULL;


			lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, regName.c_str(), 0, KEY_QUERY_VALUE, &hy);
			if (lRet == ERROR_SUCCESS)
			{
				std::string strRegINFpath = REG_INF_DEVDES;

				for (int i = 0; i < 2; i++)
				{
					lRet = RegQueryValueEx(hy, strRegINFpath.c_str(), NULL, &sz_regType, (LPBYTE)&szValue, &dw_dataLen);

					if (lRet == ERROR_SUCCESS)
					{
						printf("Read %s= %s \r\n", strRegINFpath.c_str(), szValue);
						//int i = 1, j = 0;
						//char  szValue2[256] = { 0 };
						//while (szValue[i] != ',')
						//{
						//	szValue2[j] = szValue[i];
						//	i++;
						//	j++;
						//}
						//szValue2[j] = '\0';
						//printf("Get driverName={%s}\r\n", szValue2);
						//strINFname = szValue2;
						std::string stTemp = szValue;
						std::string::size_type size_start;
						if (stTemp.find(".inf") != std::string::npos)
						{
							size_start = stTemp.find(".inf");//size_end = str_response.rfind("\"");
							strINFname = stTemp.substr(1, size_start + 3);//deete first char @ and ,if has .inf
							printf("Get driverName={%s}\r\n", strINFname.c_str());
						}
						else
							printf("Cannot inf driverName {%s}\r\n", strINFname.c_str());
						
					}
					else
					{
						printf("[Error] RegQueryValueEx(REG_INF_PATH) fail, code=%d \r\n", GetLastError());
					}

					if (strINFname.find(".inf") != std::string::npos)
					{
						bResult = true;
						break;
					}
					else   ///1. cannot find DeviceDesc  2. no ".inf" in DeviceDesc  3.no ".inf" in Mfg (bResult = flase)
					{
						strRegINFpath = REG_INF_MFG;
						printf("Retry \r\n", strINFname.c_str());
					}
				}////retry mechanism

				if (bResult)
				{
					if (NULL != hy)
						RegCloseKey(hy);
					break;
				}

			}
			else
			{
				printf("[Error] RegOpenKeyEx(InstancePath) fail(), code=%d \r\n", GetLastError());
			}


			if (NULL != hy)
				RegCloseKey(hy);
		}
	}

	SetupDiDestroyDeviceInfoList(hDeviceInfo);

	printf("[Info]findReg Done << \r\n");
	return bResult;
}

#define FULLPATH_UDE_INI "C:\\Windows\\udeinf.ini"// path must exist "C:\\Windows\\Firmware\\udeinf.ini"
bool IsDriverInstalled(std::string strInfName, int* nTyear, int* nTmon, int* nTday)
{
	printf("To check UDE driver \r\n");
	bool m_bIsDriverInstalled = false;

	HINF hInf = NULL;
	INFCONTEXT curContext, nextContext;

	CHAR szBuffer[MAX_PATH] = { 0 };
	std::string sINFname;
	if (0 == GetWindowsDirectory(szBuffer, sizeof(szBuffer)))//fail return 0
	{
		sINFname = "C:\\windows\\inf\\";
	}
	else
	{
		sINFname = szBuffer;
		sINFname += "\\inf\\";
	}

	printf("System INF Path = %s ,INF = %s\r\n", sINFname.c_str(), strInfName.c_str());


	UINT errorLine;
	CHAR buffer[MAX_PATH ] = { 0 };
	std::string strContext;

	memset(szBuffer, 0, MAX_PATH);
	sprintf(szBuffer, "%s%s", sINFname.c_str(), strInfName.c_str());
	printf("Open INF = %s \r\n", szBuffer);

//////Test copy
	char cCurrentPath[MAX_PATH] = { 0 };
	char cConfigFile[MAX_PATH + 20] = { 0 };
	GetCurrentDirectory(MAX_PATH, cCurrentPath);
	sprintf(cConfigFile, "%s\\DrvINF.ini", cCurrentPath);

	//bool bR = CopyFileA(szBuffer, FULLPATH_UDE_INI, FALSE);
	bool bR = CopyFileA(szBuffer, cConfigFile, FALSE);
	if (bR)
	{
		//GetPrivateProfileString("Version", "DriverVer", 0, buffer, MAX_PATH, FULLPATH_UDE_INI);
		GetPrivateProfileString("Version", "CatalogFile", 0, buffer, MAX_PATH + 20, cConfigFile);
		printf("CopyFile OK, and Get %s CatalogFile=%s \r\n", cConfigFile, buffer);

		memset(buffer, 0, MAX_PATH);

		GetPrivateProfileString("Version", "DriverVer", 0, buffer, MAX_PATH + 20, cConfigFile);
		printf("CopyFile OK, and Get %s DriverVersion=%s \r\n", cConfigFile, buffer);
	}
	else
	{
		printf("CopyFile inf fail, error=%d \r\n", GetLastError());
	}

	Sleep(3000);
	DeleteFileA(cConfigFile);
	memset(buffer, 0, MAX_PATH);
///

	hInf = SetupOpenInfFile(szBuffer, "System", INF_STYLE_WIN4, &errorLine);
	if (hInf == INVALID_HANDLE_VALUE)
	{
		return false;
		//continue;//return;
	}
	///the flashusb.inf contain onlye one key in manufacture
	SetupFindFirstLine(hInf, "Version", "CatalogFile", &curContext);//to get manufacture first key............section=5,line=0
	SetupGetLineText(&curContext, NULL, NULL, NULL, buffer, BUFFERSIZE, NULL);

	printf("SetupGetLineText CatalogFile= %s \r\n", buffer);

	strContext = buffer;
	transform(strContext.begin(), strContext.end(), strContext.begin(), ::toupper);

	printf("strContext= %s \r\n", strContext.c_str());
	//if (tempStr.Find(L"UDE.CAT") >= 0)//if (tempStr.Find(L"{36FC9E60-C465-11CF-8056-444553540000}") >= 0)//USB generic GUID,cannot used
	if (strContext.find(NAME_DRIVER_CAT) != std::string::npos)
	{
		std::string strVer;
		memset(buffer, 0, MAX_PATH );
		//std::string strVER;
		SetupFindFirstLine(hInf, "Version", "DriverVer", &curContext);//
		SetupGetLineText(&curContext, NULL, NULL, NULL, buffer, BUFFERSIZE, NULL);//to get the fist key info....IMC_FLASH,ntamd64
		strVer = buffer;
		printf("SetupGetLineText DriverVer:%s \r\n", buffer);

		//DriverVer=03/12/2018,0.9.3.36
		std::string str_IMEIcode;
		std::string::size_type size_start;
		//std::string::size_type size_end;

		size_start = strVer.find('/');		//size_end = str_response.rfind("\"");
		std::string sMon = strVer.substr(0, size_start);
		strVer = strVer.substr(size_start + 1, strVer.length() - size_start - 1);

		size_start = strVer.find('/');
		std::string sDay = strVer.substr(0, size_start);
		strVer = strVer.substr(size_start + 1, strVer.length() - size_start - 1);

		size_start = strVer.find(',');
		std::string sYear = strVer.substr(0, size_start);

		char *stop = NULL;
		//  i = static_cast<int>(strtol(s.c_str(), &end, 16));
		int nMon = static_cast<int>(strtol(sMon.c_str(), &stop, 10));
		int nDay = static_cast<int>(strtol(sDay.c_str(), &stop, 10));
		int nYear = static_cast<int>(strtol(sYear.c_str(), &stop, 10));

		printf("Driver Mon:%ws(%d) / Day:%ws(%d)  /Year:%ws(%d) \r\n", sMon, nMon, \
			sDay, nDay, sYear, nYear);

		*nTyear = nYear;
		*nTmon = nMon;
		*nTday = nDay;

		m_bIsDriverInstalled = true;
	}

	SetupCloseInfFile(hInf);

	if (!m_bIsDriverInstalled)
		printf("No UDE driver installed!\r\n");

	return m_bIsDriverInstalled;
}
#endif

#ifdef Test_Event
void setEventPro()
{
	printf("setEventPro enter >> \r\n");
	//HANDLE NotIlegalEnrollmentEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, "Global\\Lenovo-Sensor-IlegalEnrollment-Event");
	HANDLE hTriggerEvent = NULL;
	hTriggerEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, EVENT_NAME);
	if (hTriggerEvent == NULL)
	{
		printf("hTriggerEvent == NULL.error=%d\r\n",GetLastError());
	}
	else
		SetEvent(hTriggerEvent);
	printf("wait time 5s ...\r\n");
	Sleep(5000);
	printf("  <<setEventPro end.\r\n");
}
#endif

#ifdef Test_Power
void IsACadapterConnected()
{
	bool res = false;
	//ACLineStatus: Byte;         {0:电源断电; 1:电源正常; 255:电源状态未知}
	//BatteryFlag: Byte;          {1:电量充足; 2:电量低; 4:电池基本耗尽; 8:充电; 128:没有电池; 255:电池状态未知}
	//BatteryLifePercent: Byte;   {0..100:所剩电量百分数; 255:未知}
	//Reserved1: Byte;            {保留, 须为 0}
	//BatteryLifeTime: DWORD;     {电池剩余能量; -1 表示未知}
	//BatteryFullLifeTime: DWORD; {电池总能量; -1 表示未知}

	SYSTEM_POWER_STATUS mPowerStatus;
	BOOL bRes = GetSystemPowerStatus(&mPowerStatus);//succeed nozero return
	printf("****SystemPower,ACLineStatus=%d, \r\n{0:电源断电; 1:电源正常; 255:电源状态未知} \r\n ", mPowerStatus.ACLineStatus);
	printf("****BatteryFlag = %d \r\n{ 1:电量充足; 2:电量低; 4:电池基本耗尽; 8:充电; 128:没有电池; 255:电池状态未知 }\r\n", mPowerStatus.BatteryFlag);
	printf("****SystemPower,BatteryLifePercent=%d%%\r\n", mPowerStatus.BatteryLifePercent);

	printf("****SystemPower,BatteryLifeTime=%d%%,BatteryFullLifeTime=%d\r\n  {电池剩余能量; -1 表示未知}{电池总能量; -1 表示未知}", mPowerStatus.BatteryLifeTime, mPowerStatus.BatteryFullLifeTime);
}
#endif