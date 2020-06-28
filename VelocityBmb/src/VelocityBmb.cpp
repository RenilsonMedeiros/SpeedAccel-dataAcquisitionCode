#include <VelocityBmb.h>

VelocityBmb::VelocityBmb(uint16_t l1, uint16_t l2, uint16_t l3, uint16_t l4,
                  float dist1, float dist2, float dist3){
  _l1 = l1;
  _l2 = l2;
  _l3 = l3;
  _l4 = l4;

  this->dist_l1_l2 = dist1;
  this->dist_l2_l3 = dist2;
  this->dist_l3_l4 = dist3;

  uint16_t pinos[4] = {_l1, _l2, _l3, _l4};
  for(int i = 0; i < 4; i++){
  pinMode(pinos[i], INPUT);
  }
}

void VelocityBmb::doTest(){
  while(digitalRead(_l1)); //Enquanto o l1 estiver sentindo o veículo -> não faz nada.
  this->startTime_test = millis(); //Inicia o tempo quando o laser1 não sente mais o veículo.

  while(!digitalRead(_l2)); //Enquanto o l2 não sentir o veículo -> não faz nada.
  this->time1 = millis() - this->startTime_test; //Tempo levado para ir de l1 até l2.
  _dist = this->dist_l1_l2;
  this->vel1 = _dist / this->time1;         //Cálculo da velocidade de l1 até l2.
  this->accel = this->vel1 / this->time1;   //Cálculo da aceleração de l1 até l2.
  this->time2 = millis();

  while(!digitalRead(_l3)); //Enquanto o l3 não sentir o veículo -> não faz nada.
  this->time2 = millis() - this->time2; //Tempo levado para ir de l2 até l3.
  _dist = this->dist_l2_l3 - this->dist_l1_l2;
  this->vel2 = _dist / this->time2;
  this->time3 = millis();

  while(!digitalRead(_l4)); //Enquanto o l4 não sentir o veículo -> não faz nada.
  this->time3 = millis() - this->time3;
  _dist = this->dist_l3_l4 - this->dist_l2_l3;
  this->vel3 = _dist / this->time3;

  this->finalTime_test = this->time3 - this->startTime_test; //Tempo final do teste.
}

uint32_t VelocityBmb::getTime(int time){
  switch (time){
  case 1:
    return this->time1;
    break;

  case 2:
    return this->time2;
    break;

  case 3:
    return this->time3;
    break;
  
  case 4:
    return this->finalTime_test;
    break;
    
  default:
    return 0;
    break;
  }
}

float VelocityBmb::getDist(int dist){
  switch (dist){
  case 1:
    return this->dist_l1_l2;
    break;

  case 2:
    return this->dist_l2_l3;
    break;

  case 3:
    return this->dist_l3_l4;
    break;
  
  default:
    return 0;
    break;
  }
}

float VelocityBmb::getVel_MS(int vel){
  switch (vel){
  case 1:
    return this->vel1 * 1000; //Converte para metros/segundos
    break;

  case 2:
    return this->vel2 * 1000; 
    break;

  case 3:
    return this->vel3 * 1000; 
    break;
  
  default:
    return 0;
    break;
  }
}

float VelocityBmb::getVel_KMH(int vel){
  switch (vel){
  case 1:
    return this->vel1 * 1000 * 3.6f; //Converte para quilometros/hora
    break;

  case 2:
    return this->vel2 * 1000 * 3.6f; 
    break;

  case 3:
    return this->vel3 * 1000 * 3.6f; 
    break;
  
  default:
    return 0;
    break;
  }
}

float VelocityBmb::getAccel_MS(){
  return this->accel * 1000000; //Converte para metros/segundos ao quadrado
}

float VelocityBmb::getAccel_KMH(){
  return this->accel * 1000000 * (12960); //Converte para quilometros/hora ao quadrado
}