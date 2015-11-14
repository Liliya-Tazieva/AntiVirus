#ifndef EMITTER
#define EMITTER

#endif // EMITTER
#include <string>
#include <QObject>
class Emitter:public QObject{
    Q_OBJECT
public:

    bool isWorking=false;
    void em(const QString &x){
         isWorking=true;
         emit operate(x);
    };

    public slots:
    void finishSlot(){
        isWorking=false;
    }
   signals:
   void operate(const QString & );

};
