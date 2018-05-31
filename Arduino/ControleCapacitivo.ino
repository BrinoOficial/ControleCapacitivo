#include "UnoJoy.h"
#include <CapacitiveSensor.h>
const int resolution = 10;
const long sensitivity = 2300;
const long sensitivity2 = 2700;
CapacitiveSensor cs[] = {
  CapacitiveSensor(8, 2),
  CapacitiveSensor(8, 3),
  CapacitiveSensor(8, 4),
  CapacitiveSensor(8, 5), 
  CapacitiveSensor(8, 6),
  CapacitiveSensor(8, 7),
};
const int NUMBER_OF_SENSORS = 6;
long timeArr[NUMBER_OF_SENSORS];

void setup(){
  for (int i = 0; i++; i < NUMBER_OF_SENSORS) {
    timeArr[i] = 0;
    cs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
  }
  setupUnoJoy();// Inicializa as funções do UnoJoy
  pinMode(11, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
}

void loop(){
  // Sempre fica atualizando o dado a ser enviado ao computador
  dataForController_t controllerData = getControllerData();
  setControllerData(controllerData);
}

dataForController_t getControllerData(void){  
  //  Configura local onde dados do controle são armazenados
  //  Serve para limpar o buffer onde os dados do controle são armazenados
  dataForController_t controllerData = getBlankDataForController();

  controllerData.dpadDownOn = (cs[0].capacitiveSensor(resolution) > sensitivity);
  controllerData.dpadLeftOn = (cs[1].capacitiveSensor(resolution) > sensitivity);
  controllerData.dpadUpOn = (cs[2].capacitiveSensor(resolution) > sensitivity);
  controllerData.dpadRightOn = (cs[3].capacitiveSensor(resolution) > sensitivity);
  controllerData.crossOn = (cs[4].capacitiveSensor(resolution) > sensitivity2);
  controllerData.triangleOn = (cs[5].capacitiveSensor(resolution) > sensitivity);
  controllerData.startOn = !digitalRead(11);
  controllerData.selectOn = !digitalRead(10);

  return controllerData;
}
