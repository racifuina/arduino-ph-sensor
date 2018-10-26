#include <LiquidCrystal.h> //Libreria encargada de manejar la pantalla LCD.
LiquidCrystal lcd(8, 9, 10, 11, 12, 13); //Inicialización de la pantalla con sus pin's.

int ph_pin = A2; // A2 -> PIN de lectura de la sonda (Analogico 2).
int m_4 = 623;  //valor de calibración  pH 4 (aceite, lluevia acida).
int m_7 = 605;  //valor de calibración  pH 7 (Agua)

void setup() {
  lcd.begin(16, 2); //Establecer el tipo de pantalla LCD en este caso 16 columnas y 2 filas.
  lcd.setCursor(0, 0);  //Establecer el cursor en la primera casilla de la pantalla.
  lcd.print("Medidor de pH"); //Mostrar en pantalla el texto "Medidor de pH".
  delay(2000);  //Esperar 2000 milisegundos (2 segundos).
  lcd.clear();  //Limpiar el texto de la pantalla
}

void loop() {
  int measure = 0; //variable int que almacenará la medida obtenida de la sonda.
  int prom = 0; //Suma total de las medidas obtenidas para generar un promedio

  //Tomar 20 lecturas del sensor para generar un promedio.
  for (int i = 0; i < 20; i++) {
      measure = analogRead(ph_pin); //lectura de la sonda.
      prom = prom + measure; //sumar la nueva lectura a la suma total de las lecturas anteriores
      delay(50); //esperar 50 milisegundos entre lecturas de sonda.
  }
  
  prom = prom / 20; //Obtener el promedio de los 20 datos.   
  float Po = 7 + ((measure - m_7 ) * 3 / ( m_7 - m_4)); //Conversión del valor obtenido del sensor en voltaje a nivel de pH.
  
  lcd.setCursor(4,0);  //Establecer el cursor en la cuarta casilla de la primera fila
  lcd.print("PH:"); //Escribir en la pantalla el texto "PH".
  lcd.setCursor(7,0); //Establecer el cursor en la septima casilla de la primera fila.
  lcd.print(Po, 2);  //Escribir en la pantalla el valor en pH obtenido con 2 decimales. 
}
