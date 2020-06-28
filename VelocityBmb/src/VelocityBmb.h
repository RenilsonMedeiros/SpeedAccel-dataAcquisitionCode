#ifndef VelocityBmb_h
#define VelocityBmb_h

#include <Arduino.h>

class VelocityBmb {
  
  private: //Será acessado apenas dentro dessa biblioteca.
    uint16_t _l1, _l2, _l3, _l4;  //Guarda o valor do pino de cada sensores.
    float _dist;             //Variável auxiliar para o cálculo da distância.

    uint32_t startTime_test;
    uint32_t finalTime_test;
    uint32_t time1;
    uint32_t time2;
    uint32_t time3;
    float dist_l1_l2;
    float dist_l2_l3;
    float dist_l3_l4;
    float vel1;
    float vel2;
    float vel3;
    float accel;
    
  public: //Será acessado dentro do nosso código, quando a biblioteca for importada.
    //Método Costrutor; Parâmetros: O pino de entrada dos dados dos sensores, em ordem) 
    VelocityBmb(uint16_t l1, uint16_t l2, uint16_t l3, uint16_t l4, 
          float dist1, float dist2, float dist3); 
    void doTest();
    uint32_t getTime(int time);
    float getDist(int dist);
    float getVel_KMH(int vel);
    float getVel_MS(int vel);
    float getAccel_MS();
    float getAccel_KMH();
};

#endif