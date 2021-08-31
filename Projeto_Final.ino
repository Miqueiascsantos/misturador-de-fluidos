//#include <Ultrasonic.h> //biblioteca refernte ao sensor ultrassônico

// variáveis
int gatilho = 9; // pino TRIG do sensor ultrassônico
int echo = 8; // pino ECHO do sensor ultrassônico
float tempo; // para armazenar o tempo de ida e volta do sinal em microsegundos
float centimetros; // para armazenar a distância em centímetros
float polegadas; // para armazenar a distância em polegadas
float volume;
float abase;
 
// setup (executado apenas uma vez)
void setup() 
{
   pinMode(10, OUTPUT); //pino 10 bomba como saída
   pinMode(11, OUTPUT); //pino 11 misturador como saída
   pinMode(gatilho,OUTPUT); // configura pino GATILHO como saída
   digitalWrite(gatilho,LOW);// deixa pino em LOW
   delayMicroseconds(10); //delay entre os pulsos dados pelo sensor
   pinMode(echo,INPUT); // configura pino ECHO como entrada
  
   Serial.begin(9600);
}
 
 
// laço principal (executado indefinidamente)
void loop()
{
   // disparar pulso ultrassônico
   digitalWrite(gatilho, HIGH);
   delayMicroseconds(10);
   digitalWrite(gatilho, LOW);
   
   // medir tempo de ida e volta do pulso ultrassônico
   tempo = pulseIn(echo, HIGH);
   
   // calcular as distâncias em centímetros e polegadas
   centimetros = (tempo / 29.4) / 2;
   polegadas = (tempo / 74.7) / 2;
   
   abase = 15 * 15; // área da base do reservatório menor

   
   volume = 5 - ((abase * centimetros)/1000); //volume nominal do reservatório menor - volume lido pelo sensor para encotrar volume existente naquele instante
    if (volume <0)volume=0; //para leituras em que o valor de volume for superior ao volume nominal específicado, a variavel é zerada
   
   //Serial.print("Leitura da distância aferida= ");
   //Serial.println(centimetros);
   //Serial.println("");
   //Serial.print("Leitura do volume aferido = ");
   Serial.println(volume); // envia valor referente ao volume para ser lido pela interface java
   //Serial.println("");
   
   // aguardar um pouquinho antes de começar tudo de novo
   delay(1000);

   if(Serial.available()) // Verifica se a porta serial tem caracteres para serem lidos.
    {
        char onoff = Serial.read(); //armazena o valor existente na porta serial dentro da variavel
  
        switch(onoff) //realiza teste lógico da variavel
        {
          case 'A':
            digitalWrite(10, HIGH); //LIGA A BOMBA
            break;
          case 'B':
            digitalWrite(10, LOW); //DESLIGA A BOMBA
            break;
          case 'C':
            digitalWrite(11, HIGH); //LIGA MOTOR DO MISTURADOR
            delay(5000); //CONTA 5 SEGUINDOS
            digitalWrite(11, LOW); //DESLIGA MOTOR DO MISTURADOR
            break;
            
          case 'D': //botão de desligamento geral.
            digitalWrite(10, LOW); //DESLIGA A BOMBA
            digitalWrite(11, LOW); //DESLIGA MOTOR DO MISTURADOR
            break;
        }
    }
}
