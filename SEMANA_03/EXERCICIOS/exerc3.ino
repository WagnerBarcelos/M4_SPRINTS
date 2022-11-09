//porta dos leds, botões, buzzer e sensor

#define LED1 10
#define LED2 3
#define LED3 15
#define LED4 15
#define BUZZER 7
#define GREEN_BUTTON 1
#define RED_BUTTON 4
#define LDR 4

int getSensor = 0;
int tamanhoVetor[100];
int lugarVetor = 0;
int valorBinario[4];
int quantidadeVetor = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(LDR, INPUT);
  Serial.begin(9600);
}

void loop() {
  getSensor=analogRead(LDR);
  Serial.println(getSensor);
  
  if (digitalRead(GREEN_BUTTON) == LOW) {
    delay(100);
    //conversão do valor lido pelo sensor
    getSensor = ((getSensor * 15) - 1223) / 4095;
    Serial.print ("Leitura atual do sensor: ");
    Serial.println(getSensor);
    //armazena os valores em um vetor
    tamanhoVetor[lugarVetor] = getSensor;
    Serial.print ("Valor armazenado no vetor: ");
    Serial.println(tamanhoVetor[lugarVetor]);
    // função que converte em binário
    binario(valorBinario, tamanhoVetor[lugarVetor]);
    //mostra nos leds o valor lido
    turnOn(valorBinario);
    //toca o som específico para o valor do sensor
    soundBuzzer(tamanhoVetor[lugarVetor]);
    turnOff();
    // próxima posição livre no vetor
    lugarVetor += 1;
    //número de dados no vetor
    quantidadeVetor += 1;
  }
  //botão 2 pressionado
  if (digitalRead(RED_BUTTON) == LOW) {
    delay(100);
    for(int i = 0; i < quantidadeVetor; i++)
    {
      // converte em binário todos os valores do vetor
      binario(valorBinario, tamanhoVetor[i]);
      turnOn(valorBinario);
      soundBuzzer(tamanhoVetor[i]);
      turnOff();
    }
    for(int i = 0; i < quantidadeVetor; i++)
    {
      tamanhoVetor[i] = 0;
    }
    quantidadeVetor = 0;
  }
}

void turnOff(void) {
  delay(700);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}

void turnOn(int *valorBinario) {

//alterando os estados do led
  if (valorBinario[0] == 0) {
    digitalWrite(LED1, LOW);
  }
  else {
    digitalWrite(LED1, HIGH);
  }
  if (valorBinario[1] == 0) {
    digitalWrite(LED2, LOW);
  }
  else {
    digitalWrite(LED2, HIGH);
  }
  if (valorBinario[2] == 0) {
    digitalWrite(LED3, LOW);
  }
  else {
    digitalWrite(LED3, HIGH);
  }
  if (valorBinario[3] == 0) {
    digitalWrite(LED4, LOW);
  }
  else {
    digitalWrite(LED4, HIGH);
  }
}

void binario(int *vetor, int valor) {
  int i = 4;
  while (i > 0)
  {
    i--;
    vetor[i] = valor % 2;
    valor = valor/2;
  }
}

void soundBuzzer(int getSensor) {
  //alterando o tom a cada valor binário
  switch(getSensor) {
    case 1:
      tom(BUZZER, 400, 600);
    break;
    case 2:
      tom(BUZZER, 500, 600);
    break;
    case 3:
      tom(BUZZER, 600, 600);
    break;
    case 4:
      tom(BUZZER, 700, 600);
    break;
    case 5:
      tom(BUZZER, 8000, 600);
    break;
    case 6:
      tom(BUZZER, 900, 600);
    break;
    case 7:
      tom(BUZZER, 1000, 600);
    break;
    case 8:
      tom(BUZZER, 1100, 600);
    break;
    case 9:
      tom(BUZZER, 1200, 600);
    break;
    case 10:
      tom(BUZZER, 1300, 600);
    break;
    case 11:
      tom(BUZZER, 1400, 600);
    break;
    case 12:
      tom(BUZZER, 1500, 600);
    break;
    case 13:
      tom(BUZZER, 1600, 600);
    break;
    case 14:
      tom(BUZZER, 1700, 600);
    break;
    case 15:
      tom(BUZZER, 1800, 600);
    break;
    default:
      tom(BUZZER, 1900, 600);
  }
}

void tom(char BUZZER, int frequencia, int duracao) {
  float periodo = 1000.0/frequencia;
  for (int i = 0; i< duracao/(periodo); i++)
  {
    digitalWrite(BUZZER, HIGH);
    delayMicroseconds(periodo*500);
    digitalWrite(BUZZER, LOW);
    delayMicroseconds(periodo*500);
  }
}



