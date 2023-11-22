// Definição dos pinos de controle do motor
#define M1 9    // Pino_Velocidade 1º Motor (0 a 255)_ Porta IN2 ponte H;
#define M2 11   // Pino_Velocidade 2º Motor (0 a 255) _ Porta IN4 ponte H;
#define dir1 8  // Pino_Direção do 1º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN1 ponte H;
#define dir2 10 // Pino_Direção do 2º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN3 ponte H;

// Definição dos pinos dos sensores
#define pin_S1 2
#define pin_S2 3

float Sensor_esquerdo = 0;
float Sensor_direito = 0;

float motorDireito = 0;
float motorEsquerdo = 0;

// Constantes do PID
double Kp = 4.5; // Ganho proporcional

void setup()
{
  Serial.begin(9600);
  // Setamos os pinos de controle dos motores como saída
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);

  // Setamos a direção inicial do motor como 0, isso fará com que ambos os motores girem para frente
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);

  // Setamos os pinos dos sensores como entrada
  pinMode(pin_S1, INPUT);
  pinMode(pin_S2, INPUT);
}

void loop()
{
  // Leitura dos sensores
  Sensor_esquerdo = analogRead(pin_S1);
  Sensor_direito = analogRead(pin_S2);

  // Cálculo do erro
  float error = Sensor_esquerdo - Sensor_direito;

  // Controle Proporcional (P)
  float output = Kp * error;

  // Ajuste da velocidade dos motores
  // VELOCIDADE MAXIMA IDEAL = 255
  // VALOR IDEAL PARA ERRO ALGO ENTRE -300 ate 300;
  if (output >= -300 && output <= 300)
  {
    //  FAIXA POSITIVA 
    motorDireito = 255;
    motorEsquerdo = 255;
  }
  else
  {
    // FAIXA NEGATIVA
    motorDireito = 150 + output;
    motorEsquerdo = 150 - output;
  }

  // Garante que as velocidades estejam no intervalo permitido (0 a 255)
  motorDireito = constrain(motorDireito, 0, 255);
  motorEsquerdo = constrain(motorEsquerdo, 0, 255);

  // Controle dos motores
  analogWrite(M1, motorDireito);
  analogWrite(M2, motorEsquerdo);
}
