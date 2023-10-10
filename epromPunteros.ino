// Incluye la biblioteca Serial para imprimir en el monitor serial
#include <EEPROM.h>


 // Definir el tamaño de la matriz (3x3 en este caso)
  int filas = 30;
  int columnas = 2;

// Declaración de la función imprimirMatriz
void generarMatrizAleatoria(unsigned long *matriz, int *filas, int *columnas);
void imprimirMatriz(unsigned long *matriz, int *filas, int *columnas);
void escribirMatrizEnEEPROM(unsigned long* matriz, int *filas, int *columnas);
void leerMatrizDesdeEEPROM(unsigned long* matriz, int *filas, int *columnas);

void setup() {
  // Inicializa el monitor serial
  Serial.begin(115200);
  
  unsigned long miMatriz[filas][columnas];
  unsigned long miMatriz2[filas][columnas];
  
  generarMatrizAleatoria(&miMatriz[0][0], &filas, &columnas);
  
  // Guardar la matriz en la EEPROM
  escribirMatrizEnEEPROM(&miMatriz[0][0],&filas, &columnas);
  // Recuperar la matriz desde la EEPROM
  leerMatrizDesdeEEPROM(&miMatriz2[0][0],&filas, &columnas);

  // Llama a la función imprimirMatriz pasando la matriz y sus dimensiones como punteros
  imprimirMatriz(&miMatriz2[0][0], &filas, &columnas);
}

void loop() {
  // El bucle principal no hace nada en este ejemplo
}

void generarMatrizAleatoria(unsigned long *matriz, int *filas, int *columnas) {
  // Inicializa el generador de números aleatorios con una semilla
  randomSeed(analogRead(0));
  // Llena la matriz con números aleatorios
  for (int i = 0; i < *filas; i++) {
    for (int j = 0; j < *columnas; j++) {
      (*(matriz + i * (*columnas) + j)) = random(0, 101);  // Genera números aleatorios entre 0 y 100
    }
  }
}

// Definición de la función imprimirMatriz
void imprimirMatriz(unsigned long *matriz, int *filas, int *columnas) {
  // Recorrer las filas de la matriz
  for (int i = 0; i < *filas; i++) {
    // Recorrer las columnas de la matriz
    for (int j = 0; j < *columnas; j++) {
      // Imprimir el elemento en la posición (i, j) usando el puntero
      Serial.print(*(matriz + i * (*columnas) + j));
      Serial.print("\t");  // Tabulador para separar las columnas
    }
    // Imprimir un salto de línea al final de cada fila
    Serial.println();
  }
}

void escribirMatrizEnEEPROM(unsigned long* matriz, int *filas, int *columnas) {
  int direccion = 0;  // Dirección inicial en la EEPROM

  for (int fila = 0; fila < *filas; fila++) {
    for (int columna = 0; columna < *columnas; columna++) {
      EEPROM.put(direccion, (* (matriz + fila * (*columnas) + columna)));
      direccion += sizeof(unsigned long);
    }
  }
}

void leerMatrizDesdeEEPROM(unsigned long* matriz, int *filas, int *columnas) {
  int direccion = 0;  // Dirección inicial en la EEPROM

  for (int fila = 0; fila < *filas; fila++) {
    for (int columna = 0; columna < *columnas; columna++) {
      EEPROM.get(direccion, (* (matriz + fila * (*columnas) + columna)));
      direccion += sizeof(unsigned long);
    }
  }
}
