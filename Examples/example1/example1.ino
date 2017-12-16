
#include <casovac.h>

void func(void);           // predbezna deklarace 
casovac t1(2000, func);    // cas vyprseni v milliseconds , a volana funkce 
casovac t2(func);          // definovany casovac pozdeji startovan jako t2.start(1000); porvede se pouze JEDNOU po 1 vterine
                           // nebo t2.start(1000,20); provede se 20X  
casovac t3();              // prazdny casovac
casovac t4(2000,1000, func);
casovac t5(2000, func);

void setup() {
  Serial.begin(115200);
}

void loop() {
  t1.loop_all();   //  kontrolovani vsech casovacu instance casovac 
}

////////////////////////////// funkce 1 //////////////////////////////
void func(void) {  
  Serial.println("Im \"func\"");
  t1.new_func(func2);
  t1.new_time(1000);
  
}
////////////////////////////// funkce 2 ///////////////////////////////
void func2(void) {  
  Serial.println("Im \"func2\"");
  t1.new_func(func);
  t1.new_time(5000);
  
}
