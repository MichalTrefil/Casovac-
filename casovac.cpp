//#include "casovac.h"
//#include <time.h>
#include "casovac.h"
#include <Arduino.h>
#define ANO 1
#define NE 0

ct ctAll;

/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ////////// class casovac slouzi ke sposteni udalosti v urcitem intervalu //////////////////////////////////
casovac::casovac ()
{
    typ = NONE ;
    aktivni = NE;
    pozice_v_ct = ctAll.add_address(this);
}
/// /////////////////////////////////////////////////////////////////////////////////////////
casovac::casovac (unsigned long t,void (*f)(void)) /// INFINITE
{
    typ = INFINITE ;
    p_func = f;
    inkrement = t;
    cas = millis();
    aktivni = ANO;
    pozice_v_ct = ctAll.add_address(this);
}
/// ///////////////////////////////////////////////////////////////////////////////////////
casovac::casovac (void (*f)(void))  /// NONE
{
    typ = NONE ;
    p_func = f;
    aktivni = NE;
    pozice_v_ct = ctAll.add_address(this);
}
/// ///////////////////////////////////casovac (time,offset,func) ////////////////////////////////////////////////////////
casovac::casovac (unsigned long t,unsigned long offset,void (*f)(void))  /// INFINITE
{
    p_func = f;
    inkrement = t;
    cas = millis() + offset;
    aktivni = ANO;
    pozice_v_ct = ctAll.add_address(this);
}
/// /////////////////////////////   run   ///////////////////////
void casovac::over()
{
    if(millis() > cas )
    {
        cas = cas + inkrement;
        if(aktivni > NE)
        {
            /// zde se spousti pri preteceni
            //Serial.print (pozice_v_ct);
            p_func();
            if(typ == ONCE ) aktivni--;
            if(typ == SEVERAL ) citac > 0 ? citac -- : aktivni = 0;
        }
    }
}
/// //////////////////////////////     init    //////////////////
void casovac::init()
{
    cas = millis();
}
/// /////////////////////////////   new cas , new funkce  //////////////////
void casovac::new_time(unsigned long t )
{
    inkrement = t;
}
/// //////////////////////////////////////////////////////////////
void casovac::new_func(void (*f)(void) )
{
    p_func = f;
}
/// ////////////////////// zmena aktivity ///////////////////////
void casovac::aktiv()
{
    aktivni = ANO;
}
/// //////////////////////////////////////////////////////////////
void casovac::inaktiv()
{
    aktivni = NE;
}
/// ////////////////////// chekovani timeru /////////////////////
void casovac::loop_all()
{
    ctAll.loop();
}

/// //////////////////////////// start ONCE ///////////////////////////
void casovac::start(unsigned long t ) /// ONCE
{
    typ = ONCE ;
    cas = millis() + t;
    aktivni++;
}
/// //////////////////////////// start SEVERAL ////////////////////////
void casovac::start(unsigned long t,unsigned long times) /// SEVERAL
{
    typ = SEVERAL ;
    citac = --times;
    inkrement = t;
    cas = millis() + t;
    aktivni++;
}
/// ///////////////////////////////////////////////////////////////////////////
void casovac::start(unsigned long t,unsigned long times,void (*f)(void)) /// SEVERAL
{
    p_func = f;
    typ = SEVERAL ;
    citac = --times;
    inkrement = t;
    cas = millis() + t;
    aktivni++;
}

/// ////////////////////////// odhlaseni z ct ////////////////////////////////////
void casovac::del ()
{
    ctAll.del(pozice_v_ct);
    resort();
}
/// ////////////////////////// debuger ////////////////////////////////////////////
void casovac::debug()
{
    ctAll.debug();
}
/// ////////////////////////// resorter ////////////////////////////////////////////
void casovac::resort()
{
    ctAll.resort();
}

/// //////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////////////

ct::ct() {}

/// //////////////////////////   pridani addressy   //////////////////////////////////
int ct::add_address(casovac *addr)
{
    //int tmp;
    addressy[pocet]  = addr;  
    priznak[pocet] = 1;
    pocet++;
    //tmp = 
    return (int)pocet - 1;
}

/// //////////////////////  spuisteni prikazu clenu v poli     ///////////////////////
void ct::loop(void)
{
    for(int i  = 0; i < pocet; i++)
    {
        addressy[i]->over();
    }
}
/// /////////////////////   delete from list  ////////////////////////////////
void ct::del(unsigned int tmp)
{
    priznak[tmp] = 0;
}
/// /////////////////////////   debuger    ///////////////////////////////////
void ct::debug()
{
    Serial.print("_________________________________________");
    Serial.print(pocet);
    Serial.print("/");
    Serial.print(N_CASOVACU);
    Serial.print("#");
    for(int i  = 0; i < N_CASOVACU; i++)
    {
        Serial.print(priznak[i]);
    }
    Serial.println("#");
}
/// /////////////////////////  re-sort  //////////////////////////////////////
void ct::resort(void)
{
    int posledniPocet = pocet;
    for(int i  = 0; i < posledniPocet; i++)
    {
        if(priznak[i] == 0 && i < (posledniPocet -1)) /// zanamy mimo konce
        {
            priznak[i] = priznak[posledniPocet - 1];   /// presun <-
            priznak[posledniPocet - 1] = 0;            /// nulovani posledniho
            addressy[i] = addressy[posledniPocet - 1]; /// presun <-
            posledniPocet --; /// snizeni ukazatele
        }

        else if (priznak[i] == 0 && i == (posledniPocet -1)) /// posledni zaznam
        {

            posledniPocet --; /// snizeni ukazatele
        }
    }
    pocet = posledniPocet;
}

