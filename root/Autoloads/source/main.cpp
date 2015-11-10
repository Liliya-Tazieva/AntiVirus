#include "widget.h"
#include "ask_window.h"
#include <QApplication>
#include <fstream>
#include <iostream>
#include <QStringList>
#include <QSettings>
#include <QVector>
#include <QString>
#include <String>
#include "Windows.h"
#include <QDebug>

using namespace std;

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383


typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

LPFN_ISWOW64PROCESS fnIsWow64Process;

BOOL IsWow64()  //another msdn example function. Thank you so much, Microsoft.
{
    BOOL bIsWow64 = FALSE;

    //IsWow64Process is not available on all supported versions of Windows.
    //Use GetModuleHandle to get a handle to the DLL that contains the function
    //and GetProcAddress to get a pointer to the function if available.

    fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
        GetModuleHandle(TEXT("kernel32")),"IsWow64Process");

    if(NULL != fnIsWow64Process)
    {
        if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64))
        {
            //handle error
        }
    }
    return bIsWow64;
}

LONG GetStringRegKey(HKEY hKey, char* strValueName, std::string &strValue, const std::string &strDefaultValue)
{
    strValue = strDefaultValue;
    char szBuffer[512];
    DWORD dwBufferSize = sizeof(szBuffer);
    ULONG nError;
    nError = RegQueryValueExA(hKey, strValueName, 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
    if (ERROR_SUCCESS == nError)
    {
        strValue = szBuffer;
    }
    return nError;
}
void QueryKeyA(HKEY hKey,QStringList* l2)
{






    l2->clear();

    char    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string
    char    achClass[MAX_PATH] = "";  // buffer for class name
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

    char  achValue[MAX_VALUE_NAME];
    DWORD cchValue = MAX_VALUE_NAME;

    // Get the class name and the value count.
    retCode = RegQueryInfoKeyA(
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



    //We dont need subkeys

    // Enumerate the key values.

    if (cValues)
    {
        //printf("\nNumber of values: %d\n", cValues);
        qDebug()<<cValues;
        for (i = 0, retCode = ERROR_SUCCESS; i<cValues; i++)
        {
            cchValue = MAX_VALUE_NAME;
            achValue[0] = '\0';
            retCode = RegEnumValueA(hKey, i,
                achValue,
                &cchValue,
                NULL,
                NULL,
                NULL,
                NULL);

            if (retCode == ERROR_SUCCESS)
            {
              // std::string t1(*achValue);

                std::string strValueOfBinDir;
                GetStringRegKey(hKey, achValue, strValueOfBinDir, "err~");
               QString temps=QString::fromLocal8Bit(achValue);
               temps=temps+'~';
               QString temps1=QString::fromStdString(strValueOfBinDir);
                l2->push_back(temps.append(temps1));

              // qDebug()<<achValue;
              //  _tprintf(TEXT("(%d) %s\n"), i + 1, achValue);
            }
        }
    }
   // qDebug()<<l2;
}

void QueryKey(HKEY hKey)//not used, it's just msdn example that is untouched
{
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
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

    TCHAR  achValue[MAX_VALUE_NAME];
    DWORD cchValue = MAX_VALUE_NAME;

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

    // Enumerate the subkeys, until RegEnumKeyEx fails.

    if (cSubKeys)
    {
       // printf("\nNumber of subkeys: %d\n", cSubKeys);

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
            if (retCode == ERROR_SUCCESS)
            {
               // _tprintf(TEXT("(%d) %s\n"), i + 1, achKey);
            }
        }
    }

    // Enumerate the key values.

    if (cValues)
    {
        //printf("\nNumber of values: %d\n", cValues);
        qDebug()<<cValues;
        for (i = 0, retCode = ERROR_SUCCESS; i<cValues; i++)
        {
            cchValue = MAX_VALUE_NAME;
            achValue[0] = '\0';
            retCode = RegEnumValue(hKey, i,
                achValue,
                &cchValue,
                NULL,
                NULL,
                NULL,
                NULL);

            if (retCode == ERROR_SUCCESS)
            {
              // std::string t1(*achValue);
               qDebug()<<*achValue;
              //  _tprintf(TEXT("(%d) %s\n"), i + 1, achValue);
            }
        }
    }
}


/*void MainWindow::handleResults(const QString &){}*/




//function creates list of add programms in directories
QVector<QStringList> Compare(QVector<QStringList> c,QVector<QStringList> m)
{
    for (int i=0;i<10;i++)
    {
        int l=c[i].length();
        for(int jc=0;jc<l;jc++)
            for(int jm=0;jm<m[i].length();jm++)
                if(c[i][jc]==m[i][jm])
                    m[i].removeAt(jm);
    }
    return m;
}

void monitor(QVector<QStringList> &List){


    HKEY hTestKey;
    //win32 first:
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        TEXT("SOFTWARE\\Microsoft\\windows\\currentVersion\\run"),
        0,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
        )
    QueryKeyA(hTestKey,&List[0]);
    RegCloseKey(hTestKey);

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce"),
        0,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
        )
    QueryKeyA(hTestKey,&List[1]);
    RegCloseKey(hTestKey);

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx"),
        0,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
        )
    QueryKeyA(hTestKey,&List[2]);
    RegCloseKey(hTestKey);

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices"),
        0,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
        )
    QueryKeyA(hTestKey,&List[3]);
    RegCloseKey(hTestKey);

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce"),
        0,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
        )
    QueryKeyA(hTestKey,&List[4]);
    RegCloseKey(hTestKey);


    //I know that it is a bad practice to make big try/catches, but 32/64 check looks reaaly scary,
    //so I'll just try/catch the whole piece just to be sure that it won't break anything down (it never does, through)
    boolean ww=false;
    try{
        ww =IsWow64();
        if(ww){
            //win 64 then
            if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                TEXT("SOFTWARE\\Microsoft\\windows\\currentVersion\\run"),
                0,
                KEY_READ | KEY_WOW64_64KEY,
                &hTestKey) == ERROR_SUCCESS
                )
            QueryKeyA(hTestKey,&List[5]);
            RegCloseKey(hTestKey);

            if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce"),
                0,
                KEY_READ | KEY_WOW64_64KEY,
                &hTestKey) == ERROR_SUCCESS
                )
            QueryKeyA(hTestKey,&List[6]);
            RegCloseKey(hTestKey);

            if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx"),
                0,
                KEY_READ | KEY_WOW64_64KEY,
                &hTestKey) == ERROR_SUCCESS
                )
            QueryKeyA(hTestKey,&List[7]);
            RegCloseKey(hTestKey);

            if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices"),
                0,
                KEY_READ | KEY_WOW64_64KEY,
                &hTestKey) == ERROR_SUCCESS
                )
            QueryKeyA(hTestKey,&List[8]);
            RegCloseKey(hTestKey);

            if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce"),
                0,
                KEY_READ | KEY_WOW64_64KEY,
                &hTestKey) == ERROR_SUCCESS
                )
            QueryKeyA(hTestKey,&List[9]);
            RegCloseKey(hTestKey);
        }
    }catch(std::exception e){
        qDebug()<<"Whoops";
    }
    //---------------

}

void ask_window::invoke(){

    QVector<QStringList> List;
   for(int i=0;i<10;i++){
       QStringList q=QStringList();
       List.push_back(q);
   }


    monitor(List);
    QVector<QStringList> Difference=Compare(c,List);

     //std::ofstream fout0; fout0.open("log_rtd.txt", std::ios::app);
    // for (int i=0;i<List.size();i++)
    //  for (int ii=0;ii<List[i].size();ii++)
    //       fout0 << List[i][ii].toStdString() << std::endl;
     //fout0.close();

    qDebug()<<List;
    qDebug()<<Difference;
    for(int ii=0;ii<Difference.length();ii++)
        if(Difference.at(ii).length()!=0){
            qDebug()<<Difference.at(ii).at(0);
            qDebug()<<"the difference it is,  open the window here we must";
            break;
        }
   // std::ofstream fout; fout.open("log_rtp.txt", std::ios::app); fout <<"ping"<< std::endl;         fout.close();
};

int main(int argc, char *argv[])
{
    // system("pause");

    QApplication a(argc, argv);
    ask_window w;
    for(int i=0;i<10;i++){
       QStringList q=QStringList();
       w.c.push_back(q);
    }
    monitor(w.c);
    w.activate();
   /* std::ofstream fout0; fout0.open("log_rtd.txt", std::ios::app);
    for (int i=0;i<w.c.size();i++)
     for (int ii=0;ii<w.c[i].size();ii++){
         fout0 << i << std::endl;
          fout0 << w.c[i][ii].toStdString() << std::endl;

     }

    fout0 <<"----" << std::endl;
    fout0.close();*/
    //return 0;
    w.show();

    return a.exec();
}
