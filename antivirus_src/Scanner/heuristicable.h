#ifndef HEURISTICABLE
#define HEURISTICABLE

#endif // HEURISTICABLE

#include <pe_lib/pe_bliss.h>
#ifdef PE_BLISS_WINDOWS
#include "pe_lib/lib.h"


using namespace pe_bliss;
/*contains heuristic methods*/
class Heuristicable{
public:
    long long databaseLengthHeuristic=0;
    QList<QList<char*>>heuristicDatabase;

    /*
        it loads in operative memory all the known virus imports (in the heuristicDatabase list)
    */
    bool parseHeuristicDB(QString data){
                try{
                long long l=data.length();
                long niterator=0;

                QString str="";
                QString libname="";
                QList<char*> n;
                for(long long i=0;i<l;i++){
                    if (data.at(i)!='\n'){
                        if(data.at(i)!='\r')
                         str+=data.at(i);
                    }else{
                        if("[+#@]"==str.mid(0,5)){    //then its the name of the lib
                            libname=str.mid(5,-1);
                            str="";
                        }else{
                             if(! ( (str=="}{") || (str=="}") )   ){    //then its just a normal string
                                 if(str!=""){
                                     int len=str.length();
                                     char* str_c=new char[len];
                                     strncpy(str_c,(str).toStdString().c_str(),len);
                                     str_c[len-1]=0;
                                     n.append(str_c);
                                 }


                             }else{                                      //then its a list end.
                                  QList<char*> m(n);
                                   heuristicDatabase.append(m);
                                   n.clear();
                             }

                        }
                             str="";
                             ++niterator;


                    }

                }
                databaseLengthHeuristic=niterator;
                std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout <<"Heuristic base loaded"<< std::endl;         fout.close();
        return true;
        }catch(std::exception e){}
        return false;
    }


    /*
        goes to pe file at a0,
        returns vector of std::strings in v.
        reads the imports of pe header, if it is valid.
    */

    int mineHeader_c(char*a0,std::vector<char*> &v){
        v.clear();

        //Открываем файл
        std::ifstream pe_file(a0, std::ios::in | std::ios::binary);
        if(!pe_file)
        {
            return -1;
        }

        try
        {
            //Создаем экземпляр PE или PE+ класса с помощью фабрики
            pe_base image(pe_factory::create_pe(pe_file));

            //Проверим, есть ли импорты у файла
            if(!image.has_imports()){
                return 0;
            }

            //Получаем список импортируемых библиотек с функциями
            const imported_functions_list imports = get_imported_functions(image);
            //Перечисляем импортированные библиотеки и выводим информацию о них
            for(imported_functions_list::const_iterator it = imports.begin(); it != imports.end(); ++it)
            {
                const import_library& lib = *it; //Импортируемая библиотека
                //Перечисляем импортированные функции для библиотеки
                const import_library::imported_list& functions = lib.get_imported_functions();
                //const std::string symbol="[+#@]"+lib.get_name();
                //v.push_back((char*)symbol.c_str());
                for(import_library::imported_list::const_iterator func_it = functions.begin(); func_it != functions.end(); ++func_it)
                {
                    const imported_function& func = *func_it; //Импортированная функция
                    if(func.has_name()) //Если функция имеет имя - выведем его
                    {
                        std::string ot=lib.get_name()+' '+func.get_name();
                        int len=func.get_name().length();
                        char* str_c=new char[len];
                        strncpy(str_c,ot.c_str(),len);
                        str_c[len-1]=0;
                        v.push_back(str_c);
                    }
                }

            }
            return 0;
        }catch(std::exception e){
            std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout <<"-"<< e.what();         fout.close();
            return -1;
        }
    }

    /*
    ScanHeuristic is a function that can be applied to FILES ONLY.	directories' analog of scan is traverseForScanning function
    does signature search on a given file
    if finds something, then it opens whattodowithvirus.exe window, if not, does nothing
    requires the database to be loaded before to work correctly

    if founds virus-like imports, returns true and changes param1 and param2 to adress and name of the virus
    else returns false
    */
    bool scanHeuristic_c(QString s,QString& param1, std::string& param2){

        std::vector<char*> v;
        mineHeader_c(s.toLocal8Bit().data(),v);

        long dt=heuristicDatabase.length();
        int lt=v.size();
        long hitcounter=0;
        for(int i=0;i<dt;i++){
            int ccount=0;
            int tt=heuristicDatabase[i].length();



            for(int ii=0;ii<tt;ii++){
                if(heuristicDatabase[i][0][0]!=v[0][0])
                    continue;
                for(int iii=0;iii<lt;iii++){
                    if(strcmp(heuristicDatabase[i][ii],v[iii])==0)
                       ccount++;
                }
            }
            if(ccount==tt){
                  hitcounter++;
            }
        }
       if(hitcounter>0){
           param1=s;
           param2=QString::number(hitcounter).toStdString();
           return true;
       }
       return false;

    }


};


#endif
