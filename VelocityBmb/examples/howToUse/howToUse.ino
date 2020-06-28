/*
 * Programa para aquisição de dados de velocidade e aceleração de um veículo 
 * com o auxílio de sensores infravermelho.
 * 
 * Por Renilson Medeiros <https://www.instagram.com/renilson_medeiross/>
 *                       <https://github.com/RenilsonMedeiros>
 * 
 * Coordenador: Marcos Erike <https://www.instagram.com/marcos_erike_/>
 * 
 * Alunos de engenharia mecânica da Universidade Estadual do Maranhão.
 * Fazem parte do projeto BajaSAE, compondo a equipe Bumba Meu Baja.
 * 
 * 
 * Criado em 27/06/2020
 * Versão: 1.0.0
**/

/* OBS: 
 * Não precisa inicializar os pinos com o método pinMode(), pois a bliblioteca já faz
 * esse trabalho inicializando-os como INPUT. 
**/

/* É OPCIONAL USAR UM BOTÃO.
 * A ideia é que se tenha um botão, interruptor ou algo do tipo, para indicar ao
 * microcontrolador a hora certa para começar a fazer o teste. Isto é: execultar
 * o método doTest() da bliblioteca. 
**/

#include <VelocityBmb.h>

//Guarda a porta que está ligado o botão.
uint16_t button = 8;

//Variáveis que guardam o endereço(porta) que cada laser está ligado. 
uint16_t l1 = 1, l2 = 2, l3 = 3, l4 = 4;
//Distância posta entre os lasers, ex: dist_l1_l2 -> distância do laser-1 até laser-2.
float dist_l1_l2 = 30, dist_l2_l3 = 99, dist_l3_l4 = 100;

VelocityBmb bmb(l1, l2, l3, l4, dist_l1_l2, dist_l2_l3, dist_l3_l4);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(button) == true){
    Serial.println("Iniciando o teste de aceleração e velocidade do veículo!");

    bmb.doTest(); //Aqui é feito os cálculos em cada posição dos lasers.
    
    Serial.print("Aceleração (em m/s^2), de l1 até l2: ");
    Serial.print(bmb.getAccel_MS());
    Serial.println("m/s^2");

    Serial.print("Aceleração (em km/h^2), de l1 até l2: ");
    Serial.print(bmb.getAccel_KMH());
    Serial.println("km/h^2");

    Serial.print("Velocidade (em m/s), de l3 até l4: ");
    Serial.print(bmb.getVel_MS(3)); //O parâmetro '3' passado, indica qual etapa do percurso o método deve retornar 
    Serial.println("m/s");

    Serial.print("Velocidade (em km/h), de l3 até l4: ");
    Serial.print(bmb.getVel_KMH(3));
    Serial.println("km/h");

    Serial.print("Tempo de duração do teste: ");
    Serial.print(bmb.getTime(4) / 1000); //O método retorna o tempo em milisegundos.
    Serial.println("segundos");
  }
}