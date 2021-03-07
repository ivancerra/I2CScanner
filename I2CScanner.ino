/**************************************************************************
 *               <<<<<<<< I 2 C S C A N N E R >>>>>>>
 *    <<<<<<<< Copyright Ivan Cerra De Castro - Febrero 2021 >>>>>>>>>>>
 *           <<<<<<<< https://www.ivancerra.com >>>>>>>>>>>
 * 
 *  Scanner de Puertos de dispositivos conectados en I2C, 
 *  Muy util para ver conflictos
 * ************************************************************************/

#include <Wire.h>
 
// Tiempo en ms para volver a scanear
#define REFRESH_TIME 30000

// Direcciones validas de 0 a 127
#define ADDRESS_START 0
#define ADDRESS_END 127

// Direcciones por fila al mostrarlo por puerto serie
#define ITEMS_ROW 8

/**************************************************************************
  Inicializacion
 **************************************************************************/
void setup()
{
  // Inicializamos la clase Wire
  Wire.begin();

  // Inicializamos la clase Serial
  Serial.begin(115200);

  // Mostramos titulo
  Serial.println(" -------------------------------------------------------");
  Serial.println("| S C A N N E R   D E   D I S P O S I T I V O S   I 2 C |");
  Serial.println(" -------------------------------------------------------\n");
}
 
/**************************************************************************
  Bucle principal
 **************************************************************************/ 
void loop()
{
  // Numero de dispositivos encontrados
  int counterDevices = 0;
  // Buffer para impresiones formateadas
  char buf[15];

  // Encabezado de Scanner
  Serial.println("Scanneando bus I2C...");
  Serial.println("------------------------");
 
  // Nos recorremos las direcciones indicadas
  for(uint8_t address = ADDRESS_START, itemsPerRow = 0; address <= ADDRESS_END; address++, itemsPerRow++)
  {
    // Comenzamos transmision en direccion
    Wire.beginTransmission(address);

    // Finalizamos y cogemos error
    uint8_t error = Wire.endTransmission();

    // Imprimimos Direccion
    Serial.print("Addr ");
    sprintf(buf,"%03u(0x%02X):", address, address);
    Serial.print(buf);

    // Si el resultado fue 0 es exito, habia dispositivo
    Serial.print((error == 0)?" [X] ":"  -  ");
 
    // Ponemos lineas de N direcciones
    Serial.print((itemsPerRow % ITEMS_ROW != ITEMS_ROW - 1)?"\t":"\n");

    // Actualizamos el contador
    counterDevices = counterDevices + ((error == 0)?1:0);
  }

  // Pie de Scanner
  Serial.println("\n------------------------");
  Serial.println("* Scanner Completado!!");
  Serial.print("* Dispositivos Encontrados: ");
  Serial.println(counterDevices);
  Serial.print("\n\n");
  
  // Esperamos X segundos y escaneamos de nuevo
  delay(REFRESH_TIME);           
}