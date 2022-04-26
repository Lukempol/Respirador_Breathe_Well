#define PINO_DIR 3
#define PINO_STEP 2

#define DIR_CW  LOW
#define DIR_CCW HIGH

#define ESTADO_AVANCO 1
#define ESTADO_RECUO  2
#define ESTADO_PAUSA  3


int ciclos_pausa = 500;
int passos_percurso = 1000;
int etapa = 0;


int estado_atual = ESTADO_PAUSA;

void setup() {
  pinMode(PINO_DIR, OUTPUT);
  pinMode(PINO_STEP, OUTPUT);
  Serial.begin(9600);
  Serial.println("COMEÇO");
}

void loop() {
  if(estado_atual == ESTADO_PAUSA){
    processaPausa();
  }

  if(estado_atual == ESTADO_AVANCO){
    processaAvanco();
  }
   
  if(estado_atual == ESTADO_RECUO){
    processaRecuo();
  }

  delay(4);
}

void processaPausa(){
  etapa++;
  if(etapa>ciclos_pausa){
    estado_atual = ESTADO_AVANCO;
    etapa = 0;
    setaMotorHoraio();
    Serial.println("MUDOU PARA ESTADO_AVANCO");
  }
}

void processaAvanco(){
  // controlar ciclos e mover o motor 
  etapa++;
  executaPasso();
  
  if(etapa>passos_percurso){
    estado_atual = ESTADO_RECUO;
    etapa = 0;
    setaMotorAntiHoraio();
    Serial.println("MUDOU PARA ESTADO_RECUO");
  }
}

void processaRecuo(){
  etapa++;
  executaPasso();
  
  if(etapa>passos_percurso){
    estado_atual = ESTADO_PAUSA;
    etapa = 0;
    Serial.println("MUDOU PARA ESTADO_PAUSA");
  }
}

void setaMotorHoraio(){
  digitalWrite(PINO_DIR, DIR_CW);
  delay(1);
}
void setaMotorAntiHoraio(){
  digitalWrite(PINO_DIR, DIR_CCW);
  delay(1);
}

void executaPasso(){
  //Serial.println("STP");
  delayMicroseconds(20);
  digitalWrite(PINO_STEP, HIGH);
  delayMicroseconds(2);
  digitalWrite(PINO_STEP, LOW);
}
