#ifndef ODPOCET_H_INCLUDED
#define ODPOCET_H_INCLUDED

class odpocet
{
public:
    bool active = 0;
    int  cas = 0;
    int  casEnd = 0;

    ///////////////////////////////////////////////
    odpocet()
    {
        cas = 1000;
    }
    ///////////////////////////////////////////////
    odpocet(int i)
    {
        cas = i;
    }
    ///////////////////////////////////////////////
    void start()
    {
        casEnd = millis() + cas;
        active = 1;
    }
    ///////////////////////////////////////////////
    void start(int novyCas)
    {
        cas = novyCas;
        start();
    }
    ///////////////////////////////////////////////
    void stop()
    {
        active = 0;
    }
    ///////////////////////////////////////////////
    bool ok()
    {
        if (active == 1)
        {
            if ( millis() >= casEnd) /// je uz cas? ano
            {
                active = 0;
            }
        }
        return active;
    }
};

#endif // ODPOCET_H_INCLUDED
