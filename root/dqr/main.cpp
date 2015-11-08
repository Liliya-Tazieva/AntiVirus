#include <iostream>
#include <fstream>
#include <QDir>




int main(int argc, char *argv[])
{
    if (argc!=2){
        std::cout<<"WRONG PARAMETER NUMBER"<<std::endl;
        std::cout<<"END."<<std::endl;
        return 5;
    }

    std::string s=argv[1];

    std::ifstream::pos_type size;
    char * memblock;
    std::ifstream file (s, std::ios::in|std::ios::binary|std::ios::ate);
    if (file.is_open()){
        size = file.tellg();
        //if(size>30000)
           // size=30000;
        memblock = new char [size];
        file.seekg (0, std::ios::beg);
        file.read (memblock, size);
        file.close();
        //delete[] memblock;
     }
    else {
        std::cout<<"NOT FOUND"<<std::endl;
        std::cout<<"END."<<std::endl;
        return 5;
    }

    char *buf2=new char[size/2+1];
    for (int i = 0; i < size; i+=2){
        std::ifstream::pos_type i2=i;
        i2+=1;
        char decoded=((memblock[i]-87)<<4)+(memblock[i+1]-87);
        buf2[i/2]=decoded;
    }
    buf2[size/2]=0;
    delete[] memblock;
    std::string s0=std::string(s);




    size_t index = 0;
    while (index!=-1) {
         index = s0.find('\\');
         if(index!=-1)
         s0.replace(index, 1, "/");
    }

    s0=s0.substr(s0.rfind("/")+1);
    s0="quarantine/"+s0.substr(0,s0.rfind(".quar"));

    QDir().mkdir("quarantine");

    std::ofstream fs(s0, std::ios::out | std::ios::binary );
    fs.write(buf2, size/2);
    fs.close();




    std::cout<<"SUCCESS"<<std::endl;
    std::cout<<"END."<<std::endl;


    return 0;
}
