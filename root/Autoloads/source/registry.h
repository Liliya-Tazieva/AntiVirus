#ifndef REGISTRY
#define REGISTRY

#endif // REGISTRY
#include <QString>

class RegistryParameter{
public:
    QString name="";
    QString value="";

    bool equals(RegistryParameter x){
        if(name==x.name)
            if(value==x.value)
                return true;
        return false;
    }

};


