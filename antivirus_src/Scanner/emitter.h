#ifndef EMITTER
#define EMITTER

#endif // EMITTER
#include <string>
#include <QObject>
/*
emitter object. each one must have its own thread.
it knows if the thread is working and can give it tasks with em(QString);
*/
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
