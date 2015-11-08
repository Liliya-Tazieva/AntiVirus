#ifndef LOGGER
#define LOGGER

#endif // LOGGER

#include <iostream>
#include <QString>
#include <fstream>
/*
object which is situated in Scanner and PassiveProtection objects.
for each module it must have a separate log file.



NOT WORKING AS STATED. MUST REFACTOR SO IT WILL WORK AS IS SAID BELOW
and so it will take all 3 string types in printing function




When programm starts and Antivirus is created, it creates output file stream(separate for each module) and you can write with writeToLog() function
*/

class Logger{
public:
    void writeToLog(const char* s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s;
    }
    void writeToLog(std::string s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s;
    }
    void writelnToLog(std::string s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s << std::endl;
    }
    void writelnToLog(const char* s){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << s << std::endl;
    }
    void writelnToLog(){
        std::ofstream fout; fout.open("log_scanner.txt", std::ios::app); fout << std::endl;
    }
    Logger(){
        std::ofstream fout; fout.open("log_scanner.txt"); fout.close();
    }

};

