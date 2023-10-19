// Incluye la biblioteca Serial para imprimir en el monitor serial
#include <EEPROM.h>

#include <SPI.h>
#include <SD.h>
#include <stdlib.h>


// Líneas máximas de programas
const int ROWS = 30; 
// Col01 : Escenarios; Col02: Tiempos 
const int COLUMNS = 2;

//////////-Prog/Esc/Col-///////////////////////////////////////////////////////////////////////
int matrizProgramacion [4] [32] [2] = {//Programa guardado en EPROM o MicroSD  
                            { // Programa 1
                              {0b00000000000000000000000000000000, 0},      // ***Inicio de Programa****
                              {0b10010010010000100100000000000000, 10000},  // ***Escenario 1***
                              {0b00100100110000110000000000000000, 10000},  // ***Escenario 2***
                              {0b00100110000110000100000000000000, 12000},  // ***Escenario 3***  
                              {0b11111111111111111111111111111111, 0},      // ***Fin de Programa****
                            }, 
                            { // Programa 2
                              {0b00000000000000000000000000000000, 0},      // ***Inicio de Programa****
                              {0b10010010010000100100000000000000, 10000},  // ***Escenario 1***
                              {0b00100100110000110000000000000000, 10000},  // ***Escenario 2***
                              {0b00100110000110000100000000000000, 10000},  // ***Escenario 3***
                              {0b11111111111111111111111111111111, 0},      // ***Fin de Programa****
                            },
                            { // Programa 3
                              {0b00000000000000000000000000000000, 0},      // ***Inicio de Programa****
                              {0b10010010010000100100000000000000, 10000},  // ***Escenario 1***
                              {0b00100100110000110000000000000000, 10000},  // ***Escenario 2***
                              {0b00100110000110000100000000000000, 20000},  // ***Escenario 3***
                              {0b11111111111111111111111111111111, 0},      // ***Fin de Programa****
                            }, 
                            { // Programa 4
                              {0b00000000000000000000000000000000, 0},      // ***Inicio de Programa****
                              {0b10010010010000100100000000000000, 10000},  // ***Escenario 1***
                              {0b00100100110000110000000000000000, 10000},  // ***Escenario 2***
                              {0b00100110000110000100000000000000, 20000},  // ***Escenario 3***
                              {0b11111111111111111111111111111111, 0},      // ***Fin de Programa****
                            } 
                          };

unsigned long matrizProgramacion2 [ROWS] [COLUMNS] = {//Programa de Escenarios guardado en MicroSD  
                             // Programa 1
                              {0b00000000000000000000000000000000, 0},      // ***Inicio de Programa****
                              {0b10010010010000100100000000000000, 10000},  // ***Escenario 1***
                              {0b00100100110000110000000000000000, 10000},  // ***Escenario 2***
                              {0b00100110000110000100000000000000, 12000},  // ***Escenario 3***  
                              {0b11111111111111111111111111111111, 0},      // ***Fin de Programa****
                             
                             // Programa 2
                              {0b00000000000000000000000000000000, 0},      // ***Inicio de Programa****
                              {0b10010010010000100100000000000000, 10000},  // ***Escenario 1***
                              {0b00100100110000110000000000000000, 10000},  // ***Escenario 2***
                              {0b00100110000110000100000000000000, 10000},  // ***Escenario 3***
                              {0b11111111111111111111111111111111, 0},      // ***Fin de Programa****
                            
                             // Programa 3
                              {0b00000000000000000000000000000000, 0},      // ***Inicio de Programa****
                              {0b10010010010000100100000000000000, 10000},  // ***Escenario 1***
                              {0b00100100110000110000000000000000, 10000},  // ***Escenario 2***
                              {0b00100110000110000100000000000000, 20000},  // ***Escenario 3***
                              {0b11111111111111111111111111111111, 0},      // ***Fin de Programa**** 

                            // Programa 4
                              {0b00000000000000000000000000000000, 0},      // ***Inicio de Programa****
                              {0b10010010010000100100000000000000, 10000},  // ***Escenario 1***
                              {0b00100100110000110000000000000000, 10000},  // ***Escenario 2***
                              {0b00100110000110000100000000000000, 20000},  // ***Escenario 3***
                              {0b11111111111111111111111111111111, 0},      // ***Fin de Programa**** 

                              {0b11111111111111111111111111111110, 0}       // Fin de Programas
};

//int filas = sizeof(matrizProgramacion2) / sizeof(matrizProgramacion2[0]);
//int columnas = sizeof(matrizProgramacion2[0]) / sizeof(matrizProgramacion2[0][0]);

unsigned long matrizEjecucion[31][2] = {// Programa Completo
                            {0b00000000000000000000000000000000, 0},      // ***Inicio de Programa***

                            {0b10010010010000100100000000000000, 10000},  // ***Escenario 1***
                            {0b00000000010000100100000000000000, 375},    // Transición de Verde a Ambar
                            {0b10010010010000100100000000000000, 375},    // Transición de Verde a Ambar
                            {0b00000000010000100100000000000000, 375},    // Transición de Verde a Ambar
                            {0b10010010010000100100000000000000, 375},    // Transición de Verde a Ambar
                            {0b00000000010000100100000000000000, 375},    // Transición de Verde a Ambar
                            {0b10010010010000100100000000000000, 375},    // Transición de Verde a Ambar
                            {0b00000000010000100100000000000000, 375},    // Transición de Verde a Ambar
                            {0b10010010010000100100000000000000, 375},    // Transición de Verde a Ambar
                            {0b01001001010000100100000000000000, 3000},   // Tiempo de ambar  

                            {0b00100100110000110000000000000000, 10000}, // ***Escenario 2***
                            {0b00100100100000100000000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100100110000110000000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100100100000100000000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100100110000110000000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100100100000100000000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100100110000110000000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100100100000100000000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100100110000110000000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100100101000101000000000000000, 3000}, // Tiempo de ambar  

                            {0b00100110000110000100000000000000, 12000}, // ***Escenario 3***
                            {0b00100110000100000100000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100110000110000100000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100110000100000100000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100110000110000100000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100110000100000100000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100110000110000100000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100110000100000100000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100110000110000100000000000000, 375}, // Transición de Verde a Ambar
                            {0b00100110000101000100000000000000, 3000}  // Tiempo de ambar  
};

// Definición de Matrices de prueba
//unsigned long miMatriz[31][2];// = {0};
unsigned long miMatriz2[ROWS][COLUMNS];// = {0};

// Declaración de la funciones

void setup() {
  // Inicializa el monitor serial
  Serial.begin(115200);

  // Leer matriz de Programación desde microSD
  unsigned long ** matrizMicroSD = leerMatrizDesdeMicroSD();
  
  // Llama a la función que determina las líneas de programación
  int * filasColumnas = revisionMatrizProgramacion(matrizMicroSD,&ROWS, &COLUMNS);

  // Genera una matriz aleatoria de tamaño filasXcolumnas
  //unsigned long ** matrizAleatoria = generarMatrizAleatoria(&filasColumnas[0], &filasColumnas[1]);
  //imprimirMatriz(matrizAleatoria, &filasColumnas[0], &filasColumnas[1]);

  // Llama a la función imprimirMatriz pasando la matriz y sus dimensiones como punteros
  imprimirMatriz(matrizMicroSD, &filasColumnas[0], &filasColumnas[1]);

  // Guardar la matriz en la EEPROM
  escribirMatrizEnEEPROM(matrizMicroSD, &filasColumnas[0], &filasColumnas[1]);

  // Recuperar la matriz desde la EEPROM
  unsigned long ** matrizdeEEPROM = leerMatrizDesdeEEPROM(&filasColumnas[0], &filasColumnas[1]);

  // Llama a la función imprimirMatriz pasando la matriz y sus dimensiones como punteros
  imprimirMatriz(matrizdeEEPROM, &filasColumnas[0], &filasColumnas[1]);
}

void loop() {
  // Llama a la función imprimirMatriz pasando la matriz y sus dimensiones como punteros
  //imprimirMatriz(&miMatriz2[0][0], &filas, &columnas);
  //delay(2000);
}

// Definición de la función generarMatrizAleatoria
unsigned long** generarMatrizAleatoria(int *filas, int *columnas) {
  // Reserva memoria para el puntero a la matriz
  unsigned long** matrix = (unsigned long**) malloc(*filas * sizeof(unsigned long*));
  // Reserva memoria para cada fila de la matriz
  for (int i = 0; i < filas; i++) {
    matrix[i] = (unsigned long*) malloc(*columnas * sizeof(unsigned long));
  }

  // Llena la matriz de Ceros
  for (int i = 0; i < *filas; i++) {
    for (int j = 0; j < *columnas; j++) {
      matrix[i][j] = 0; 
    }
  }
  // Inicializa el generador de números aleatorios con una semilla
  randomSeed(analogRead(0));
  // Llena la matriz con números aleatorios
  for (int i = 0; i < *filas; i++) {
    for (int j = 0; j < *columnas; j++) {
      //(*(matriz + i * (*columnas) + j)) = random(0, 101);  // Genera números aleatorios entre 0 y 100
      matrix[i][j] = random(0, 101);  // Genera números aleatorios entre 0 y 100
    }
  }

  return matrix;
}
// Definición de la función imprimirMatriz
void imprimirMatriz(unsigned long** matriz, int *filas, int *columnas) {
  int prog = 0;
  if (*filas != 0 && *columnas != 0) {
    Serial.println("Programas: ");
    Serial.println("Inicio de Programa:");
    // Recorrer las filas de la matriz
    for (int i = 0; i < *filas; i++) {
      Serial.print(i);
      Serial.print(" - ");
      // Recorrer las columnas de la matriz
      for (int j = 0; j < *columnas; j++) {
        // Imprimir el elemento en la posición (i, j) usando el puntero
        //Serial.print(*(matriz + i * (*columnas) + j), DEC);
        if (matriz[i][j] == 0 && matriz[i][j+1] == 0) {
          Serial.print(" Prog : ");
          Serial.print(prog);
          Serial.print(" / ");
        }
        if (matriz[i][j] == 4294967295 && matriz[i][j+1] == 0) {
          Serial.print(" Fin : ");
          Serial.print(prog);
          Serial.print(" / ");
          prog++;
        }
        Serial.print(matriz[i][j], DEC);
        Serial.print("\t");  // Tabulador para separar las columnas
      }
      // Imprimir un salto de línea al final de cada fila
      Serial.println();
  }
  Serial.println("Fin de Programa:");
  } else {
    Serial.println("Programa Corrupto:");
  }
  
}
// Definición de la función escribirMatrizEnEEPROM
void escribirMatrizEnEEPROM(unsigned long** matriz, int *filas, int *columnas) {
  int direccion = 0;  // Dirección inicial en la EEPROM

  for (int i = 0; i < *filas; i++) {
    for (int j = 0; j < *columnas; j++) {
      //EEPROM.put(direccion, (* (matriz + i * (*columnas) + j)));
      EEPROM.put(direccion, matriz[i][j]);
      direccion += sizeof(unsigned long);
    }
  }
}
// Definición de la función escribirMatrizEnEEPROM
void escribirMatriz3EnEEPROM(unsigned long* matriz, int *prog, int *esc, int *col) {
  int direccion = 0;  // Dirección inicial en la EEPROM

  for (int fila = 0; fila < *prog; fila++) {
    for (int columna = 0; columna < *esc; columna++) {
      for (int columna2 = 0; columna2 < *esc; columna2++) {
        EEPROM.put(direccion, (* (matriz + fila * (*esc) + columna) * (*col) + columna2));
        direccion += sizeof(unsigned long);
      }
    }
  }
}
// Definición de la función leerMatrizDesdeEEPROM
unsigned long ** leerMatrizDesdeEEPROM(int *filas, int *columnas) {
  // Reserva memoria para el puntero a la matriz
  unsigned long** matrix = (unsigned long**) malloc(*filas * sizeof(unsigned long*));
  // Reserva memoria para cada fila de la matriz
  for (int i = 0; i < filas; i++) {
    matrix[i] = (unsigned long*) malloc(*columnas * sizeof(unsigned long));
  }

  // Llena la matriz de Ceros
  for (int i = 0; i < *filas; i++) {
    for (int j = 0; j < *columnas; j++) {
      matrix[i][j] = 0; 
    }
  }

  int direccion = 0;  // Dirección inicial en la EEPROM

  for (int i = 0; i < *filas; i++) {
    for (int j = 0; j < *columnas; j++) {
      //EEPROM.get(direccion, (* (matriz + i * (*columnas) + j)));
      EEPROM.get(direccion, matrix[i][j]);
      //Serial.println(matrix[i][j]);
      direccion += sizeof(unsigned long);
    }
  }

  return matrix;
}
// Definición de la función de revisión de matriz de programación
int* revisionMatrizProgramacion(unsigned long** matriz, int *filas, int *columnas) {
  static int arreglo[2] = {0};

  // Recorrer las filas de la matriz
  for (int i = 0; i < *filas; i++) {
    // Recorrer las columnas de la matriz
    for (int j = 0; j < *columnas; j++) {
      if ((matriz[i][j] == 4294967294) && (matriz[i][j+1] == 0)) {
        Serial.print("No. de filas de Programa: ");
        Serial.println(i+1);
        // Asigna valores aleatorios a los elementos del arreglo
        arreglo[0] = ++i;
        arreglo[1] = *columnas;
        // Retorna el arreglo
        return arreglo;
      } 
      
    }
  }
}
// Definición de Prohgramación desde MicroSD
unsigned long ** leerMatrizDesdeMicroSD() {
  
  // Reserva memoria para el puntero a la matriz
  unsigned long** matrix = (unsigned long**) malloc(ROWS * sizeof(unsigned long*));
  // Reserva memoria para cada fila de la matriz
  for (int i = 0; i < ROWS; i++) {
    matrix[i] = (unsigned long*) malloc(COLUMNS * sizeof(unsigned long));
  }

  // Llena la matriz de Ceros
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      matrix[i][j] = 0; 
    }
  }
  
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  File myFile = SD.open ("prog.txt"); // open the file
  if (!myFile) { // check if the file exists
    Serial.println ("File not found");
    return NULL;
  }

  if (myFile) {
    String line; // to store each line
    int row = 0; // to keep track of the row index
    int col = 0; // to keep track of the column index
    //unsigned long matrix [15] [2]; // to store the matrix, change the size as needed
    myFile = SD.open("prog.txt");
    while (myFile.available ()) { // while there is something to read
      line = myFile.readStringUntil ('\n'); // read a line until newline character
      //Serial.println (line); // print the line for debugging
      col = 0; // reset the column index for each line
      for (int i = 0; i < line.length (); i++) { // loop through each character in the line
        if (line.charAt (i) == ',') { // if a comma is found
          matrix [row] [col] = strtoul (line.substring (0, i).c_str (), NULL, 10); // convert the substring before the comma to an unsigned long and store it in the matrix
          line = line.substring (i + 1); // remove the substring before the comma from the line
          i = 0; // reset the index to start from the beginning of the new line
          col++; // increment the column index
        }
      }
      matrix [row] [col] = strtoul (line.c_str (), NULL, 10); // convert the remaining substring to an unsigned long and store it in the matrix
      row++; // increment the row index
    }
    myFile.close (); // close the file when done reading

    //Serial.println("Imprimiendo matriz:");
    // print the matrix for debugging
    //for (int i = 0; i < ROWS; i++) {
    //  for (int j = 0; j < COLUMNS; j++) {
    //    Serial.print (matrix [i] [j], DEC); // print the matrix element in decimal format
    //    Serial.print (" ");
    //  }
     // Serial.println ();
    //}

    return matrix;
    
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening prog.txt");
  }
  
}
