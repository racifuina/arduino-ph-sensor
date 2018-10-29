#include  <Wire.h> //Libreria encargada de manejar la comunicación I2C con la pantalla.
#include  <LiquidCrystal_I2C.h> //Libreria encargada de manejar la pantalla LCD.
/*
PINOUT
LCD SCREEN      Arduino NANO
GND             GND
VCC             5V
SDA             A4
SCL             A5

PH PROBE      Arduino NANO
V+             5V
G              GND
G              GND || N/C
Po             A2
Do             N/C 
To             N/C
*/

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //Inicialización de la pantalla con sus pin's.

int ph_pin = A2; // A2 -> PIN de lectura de la sonda (Analogico 2).
void setup() {
  lcd.begin(16, 2); //Establecer el tipo de pantalla LCD en este caso 16 columnas y 2 filas.
  lcd.setCursor(0, 0);  //Establecer el cursor en la primera casilla de la pantalla.
  lcd.print("Medidor de pH"); //Mostrar en pantalla el texto "Medidor de pH".
  delay(2000);  //Esperar 2000 milisegundos (2 segundos).
  lcd.clear();  //Limpiar el texto de la pantalla
}

void loop() {
  float Po = (1023 - analogRead(ph_pin)); //lectura analogica de la sonda (voltaje).
  float pHm = map(Po, 290, 406, 400, 700); //Conversión del valor obtenido del sensor en voltaje a nivel de pH.
  float pH = (pHm/100);
  lcd.setCursor(4,0);  //Establecer el cursor en la cuarta casilla de la primera fila
  lcd.print("PH:"); //Escribir en la pantalla el texto "PH".
  lcd.setCursor(7,0); //Establecer el cursor en la septima casilla de la primera fila.
  lcd.print(pH, 2);//Escribir en la pantalla el valor en pH obtenido con 2 decimales.
  delay(2000); //Esperar 2000 milisegundos (2 segundos) entre mediciones.
}
