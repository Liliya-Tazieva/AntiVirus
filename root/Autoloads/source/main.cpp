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
QVector<QList<RegistryParameter>> Compare_r(QVector<QList<RegistryParameter>> c,QVector<QList<RegistryParameter>> m)
{
    for (int i=0;i<10;i++)
    {
        int l=c[i].length();
        for(int jc=0;jc<l;jc++)
            for(int jm=0;jm<m[i].length();jm++)
                if(c[i][jc].equals(m[i][jm]))
                    m[i].removeAt(jm);
    }
    return m;
}

void QueryKeyA_r(HKEY hKey,QList<RegistryParameter>* l2)
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
                RegistryParameter x=RegistryParameter();
                std::string strValueOfBinDir;
                GetStringRegKey(hKey, achValue, strValueOfBinDir, "err~");
               QString temps=QString::fromLocal8Bit(achValue);
               QString temps1=QString::fromStdString(strValueOfBinDir);
               x.name=temps;
               x.value=temps1;
               if (temps!="")
                l2->push_back(x);

              // qDebug()<<achValue;
              //  _tprintf(TEXT("(%d) %s\n"), i + 1, achValue);
            }
        }
    }
   // qDebug()<<l2;
}

void ask_window::no()
{   if(mode=="registry_changed"){
        std::string temp;
        if(reserved_registry_parameter_changed_int<5){
            if(reserved_registry_parameter_changed_int==0) temp="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
            if(reserved_registry_parameter_changed_int==1) temp="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
            if(reserved_registry_parameter_changed_int==2) temp="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx";
            if(reserved_registry_parameter_changed_int==3) temp="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices";
            if(reserved_registry_parameter_changed_int==4) temp="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce";
            HKEY hKey;
            int tt=RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                                temp.c_str(),
                                0,
                                KEY_SET_VALUE,
                                &hKey);
            if (tt == ERROR_SUCCESS){
              RegDeleteValueA(hKey,(LPCSTR)reserved_registry_parameter_changed.name.toLocal8Bit());
            }else{
                 qDebug()<<tt;
            }
            RegCloseKey(hKey);
        }else  if(reserved_registry_parameter_changed_int<10){
            if(reserved_registry_parameter_changed_int==5) temp="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
            if(reserved_registry_parameter_changed_int==6) temp="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
            if(reserved_registry_parameter_changed_int==7) temp="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx";
            if(reserved_registry_parameter_changed_int==8) temp="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices";
            if(reserved_registry_parameter_changed_int==9) temp="SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce";
            HKEY hKey;
            int tt=RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                                temp.c_str(),
                                0,
                                KEY_SET_VALUE|KEY_WOW64_64KEY,
                                &hKey);
            if (tt == ERROR_SUCCESS){
              RegDeleteValueA(hKey,(LPCSTR)reserved_registry_parameter_changed.name.toLocal8Bit());
            }else{
                 qDebug()<<tt;
            }
            RegCloseKey(hKey);
        }
    }

/*

    LONG RegDeleteKeyExA( HKEY_LOCAL_MACHINE, (char*)"SOFTWARE\\Microsoft\\windows\\currentVersion\\run\\del" ,
                KEY_WOW64_32KEY, NULL);*/
    this->hide();
}

void monitor_r(QVector<QList<RegistryParameter>> &List){


    HKEY hTestKey;
    //win32 first:
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        TEXT("SOFTWARE\\Microsoft\\windows\\currentVersion\\run"),
        0,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
        )
    QueryKeyA_r(hTestKey,&List[0]);
    RegCloseKey(hTestKey);

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce"),
        0,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
        )
    QueryKeyA_r(hTestKey,&List[1]);
    RegCloseKey(hTestKey);

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx"),
        0,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
        )
    QueryKeyA_r(hTestKey,&List[2]);
    RegCloseKey(hTestKey);

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices"),
        0,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
        )
    QueryKeyA_r(hTestKey,&List[3]);
    RegCloseKey(hTestKey);

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce"),
        0,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
        )
    QueryKeyA_r(hTestKey,&List[4]);
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
            QueryKeyA_r(hTestKey,&List[5]);
            RegCloseKey(hTestKey);

            if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce"),
                0,
                KEY_READ | KEY_WOW64_64KEY,
                &hTestKey) == ERROR_SUCCESS
                )
            QueryKeyA_r(hTestKey,&List[6]);
            RegCloseKey(hTestKey);

            if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx"),
                0,
                KEY_READ | KEY_WOW64_64KEY,
                &hTestKey) == ERROR_SUCCESS
                )
            QueryKeyA_r(hTestKey,&List[7]);
            RegCloseKey(hTestKey);

            if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices"),
                0,
                KEY_READ | KEY_WOW64_64KEY,
                &hTestKey) == ERROR_SUCCESS
                )
            QueryKeyA_r(hTestKey,&List[8]);
            RegCloseKey(hTestKey);

            if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce"),
                0,
                KEY_READ | KEY_WOW64_64KEY,
                &hTestKey) == ERROR_SUCCESS
                )
            QueryKeyA_r(hTestKey,&List[9]);
            RegCloseKey(hTestKey);
        }
    }catch(std::exception e){
        qDebug()<<"Whoops";
    }
    //---------------

}

QString _regToString(RegistryParameter x){
    QString temp="";
    temp.append(x.name);
    temp.append(": ");
    temp.append(x.value);
    return temp;
}
void ask_window::invoke(){
    QVector<QList<RegistryParameter>> List_r;
    for(int i=0;i<10;i++){
       QList<RegistryParameter> q=QList<RegistryParameter>();
       List_r.push_back(q);
    }

    monitor_r(List_r);
    QVector<QList<RegistryParameter>> Difference_r=Compare_r(c_r,List_r);
    /*for(int ii=0;ii<10;ii++){
        qDebug()<<ii;
        for(int ii0=0;ii0<List_r[ii].size();ii0++)
            qDebug()<<_regToString(List_r[ii].at(ii0));
    }*/

    for(int ii=0;ii<10;ii++){
        if(Difference_r[ii].size()!=0)
         qDebug()<<ii;
        for(int ii0=0;ii0<Difference_r[ii].size();ii0++)
            qDebug()<<_regToString(Difference_r[ii].at(ii0));
    }

    for(int ii=0;ii<Difference_r.length();ii++)
        if(Difference_r.at(ii).length()!=0){
            qDebug()<<_regToString(Difference_r.at(ii).at(0));
            //QString t0="";
            //t0.append("");
            //GetStringRegKey(HKEY_LOCAL_MACHINE, char* strValueName, std::string &strValue, const std::string &strDefaultValue);
            qDebug()<<"the difference it is,  open the window here we must";
            this->reserved_registry_parameter_changed_int=ii;
            this->reserved_registry_parameter_changed=Difference_r.at(ii).at(0);
            this->set_window(QString("registry_changed"),_regToString(Difference_r.at(ii).at(0)));
            this->show();
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
       QList<RegistryParameter> q=QList<RegistryParameter>();
       w.c_r.push_back(q);
    }

    monitor_r(w.c_r);

    w.activate();

    return a.exec();
}
