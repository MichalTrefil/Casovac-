
#include <casovac.h>            // casovac.h a casovac.cpp

void func(void);                // predbezna deklarace
void debug(void);
void restart(void);

casovac t1(2000, func);         // cas vyprseni v milliseconds , a volana funkce
casovac *t2 = new casovac(50, func);             // definovany casovac pozdeji startovan jako t2.start(1000); porvede se pouze JEDNOU po 1 vterine
// nebo t2.start(1000,20); provede se 20X
casovac t3();                 // prazdny casovac
casovac t4(2000, 1000, func); // pridany offset, posunuti zacatku casovani
casovac t5(2000, debug);
casovac t6 (restart);


void setup() {
  Serial.begin(115200);
  t6.start(10000);
  casovac *tx = new(casovac);
  tx->new_func(func3);
  tx->start(5000, 1);
  //delete tx;
}

void loop() {
  t1.loop_all();   //  kontrolovani vsech casovacu instance casovac
}

////////////////////////////// funkce 1 //////////////////////////////
void func(void) {
  Serial.println("Im \"func\"");
  t1.new_func(func2);  // zmena funkce
  t1.new_time(1000);   // zmena timeout

}
////////////////////////////// funkce 2 ///////////////////////////////
void func2(void) {
  Serial.println("Im \"func2\"");
  t1.new_func(func);
  t1.new_time(5000);
}

void func3(void) {
  Serial.println("Im Resort");
  t2->del();
  delete t2;
  
  //t3.del();
  t4.del();

  //t1.resort();
  //t1.new_func(func2);  // zmena funkce
  //t1.new_time(1000);   // zmena timeout

}

void debug(void)
{
  t1.debug();
}
void restart(void) {
  ESP.restart();
}
