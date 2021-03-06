#include  <Wire.h> //Libreria encargada de manejar la comunicación I2C con la pantalla.
#include  <LiquidCrystal_I2C.h> //Libreria encargada de manejar la pantalla LCD.
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
  lcd.setCursor(0,1);  //Establecer el cursor en la primera casilla de la segunda fila
  if (pH >= 7.35 && pH <= 7.40) { //lectura dentro de parametros saludables
      lcd.print("SALUDABLE");  //Escribir TEXTO en la pantalla
  } else if (pH > 7.40) {
      if (ph < 8) {
          lcd.print("NO TAN SALUDABLE"); //Escribir TEXTO en la pantalla
      } else {
          lcd.print("NO SALUDABLE"); //Escribir TEXTO en la pantalla
      }
  } else if (pH < 7.35) {
      if (ph > 6) {
          lcd.print("NO SALUDABLE"); //Escribir TEXTO en la pantalla
      } else {
          lcd.print("NO SALUDABLE"); //Escribir TEXTO en la pantalla
      }
  }

  delay(2000); //Esperar 2000 milisegundos (2 segundos) entre mediciones.
  lcd.clear();  //Limpiar el texto de la pantalla
}
