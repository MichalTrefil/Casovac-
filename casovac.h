#ifndef CASOVAC_H
#define CASOVAC_H

#define NONE 0
#define INFINITE 1
#define ONCE 2
#define SEVERAL 3

class casovac

{
private:
    unsigned long inkrement = 1000;
    unsigned long cas = 0;
    unsigned long citac = 0;
    unsigned int aktivni = 1;
    void (*p_func)(void);
    int typ = INFINITE ;

public:
    casovac (); ///konstruktor  casovac pr; INFINITE
    casovac (void (*)(void)); ///  ONCE or SEVERAL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    casovac (unsigned long,void (*)(void)); ///casovac pr(1000,funkce); INFINITE
    casovac (unsigned long,unsigned long,void (*)(void)); ///casovac pr(1000,offset,funkce); INFINITE
    void over (); //hlavni program
    void init();
    void new_time(unsigned long); //   pr.new_time(5000);
    void new_func(void (*)(void)); //  pr.new_func(novaFunkce);

    void start(unsigned long);  /// ONCE !!!!!!!!!!!!!!!!!!!!!!!!!!
    void start(unsigned long,unsigned long); /// start(1000,20);  SEVERAL !!!!!!!!!!!!!!!!!!!!!!!
    void start(unsigned long,unsigned long,void (*)(void));

    void aktiv();
    void inaktiv(); /// deaktivuje casovac
    void loop_all();/// checkuje  vsechny instance tridy casovac
};
/// ///////////////////////////////////////// ct /////////////////////////////////////////
class ct //registr casovacu
{
private:
    int pocet = 0;
    casovac* addressy[10];
public:
    ct();
    void add_address(casovac *);
    void loop (void);
} ;



#endif // CASOVAC_H
