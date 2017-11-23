#include<Servo.h>

#define ESTADO_BUSCANDO 0
#define ESTADO_POSIBLE_LUGAR 1
#define ESTADO_FIN_LUGAR 2
#define ESTADO_MANIOBRA 3

Servo myservo; // create servo object to control servo
int Echo = A4;  
int Trig = A5;
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int ENA = 5;
int ENB = 11;
int ABS = 100;
int distancia;
int estado;


void setup(){
  
 
  myservo.attach(3);// attach servo on pin 3 to servo object
  Serial.begin(9600);     
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  estado = ESTADO_BUSCANDO;
}




  void _mForward()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
  digitalWrite(in1,HIGH);//digital output
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
 Serial.println("go forward!");
}

void _mBack()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
 Serial.println("go back!");
}

void _mleft()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW); 
 Serial.println("go left!");
}

void _mright()
{
 analogWrite(ENA,ABS);
 analogWrite(ENB,ABS);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
 Serial.println("go right!");
} 
void _mStop()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  Serial.println("Stop!");
}

 /*Ultrasonic distance measurement Sub function*/
int Distance_test()   
{
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance/58;       
  return (int)Fdistance;  
}





  
  
  
  int distanciaOriginal;
  unsigned long inicioLugar;




  void _buscarEstacionamiento()
  {
  
    myservo.write(160);
    _mForward();
    distancia=Distance_test();
    if(distancia>distanciaOriginal+10)
    {
      inicioLugar=millis();
      estado = ESTADO_POSIBLE_LUGAR;
    }
  
  distanciaOriginal=distancia;
  }
  unsigned long finLugar;
  unsigned long D;

  void _lugarEncontrado(){

  myservo.write(160);
  _mForward();
  distancia=Distance_test();
  if(distancia<distanciaOriginal-10){
  

  finLugar=millis();

  D=finLugar-inicioLugar;

    _mStop();
    delay(1000);
estado=ESTADO_FIN_LUGAR;

    
    
    
  }

 
  }

 void  _maniobraEstacionamiento(){
    _mBack();
    delay(D/2);

    _mleft();
    delay(500);

    _mForward();
    delay(700);

    _mright();
    delay(500);

    _mBack();
    delay(250);

    _mStop();

    estado= ESTADO_MANIOBRA;
    
  }
 
  
void loop(){
  switch(estado)
  {
    case ESTADO_BUSCANDO:
       _buscarEstacionamiento();
    break;

    case ESTADO_POSIBLE_LUGAR:
    _lugarEncontrado();
    break;

    case ESTADO_FIN_LUGAR:
    _maniobraEstacionamiento();
    break;

    

    
    
    
    
  }
}
  


  

  




