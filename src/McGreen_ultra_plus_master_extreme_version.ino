// Define os pinos dos motores
#define M1 9
#define M2 11
#define dir1 8
#define dir2 10

// Define os pinos dos sensores
#define pin_S1 6
#define pin_S2 7

// Variáveis para armazenar os estados dos sensores
bool Sensor1 = false;
bool Sensor2 = false;

// Define as velocidades dos motores
const int VELOCIDADE_MAXIMA = 222;
const int VELOCIDADE_CURVA = 140;

// Variáveis para o controle de tempo
unsigned long previousMillis = 0;
const long interval = 100;

// Variáveis para controlar a detecção de curvas
unsigned long tempoCurva = 0;
bool curvaDetectada = false;

// Variáveis para controlar a direção dos motores
bool direcaoMotor1 = true;
bool direcaoMotor2 = true;

void setup()
{
    Serial.begin(9600);
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);
    pinMode(dir1, OUTPUT);
    pinMode(dir2, OUTPUT);
    pinMode(pin_S1, INPUT);
    pinMode(pin_S2, INPUT);
}

void loop()
{
    unsigned long currentMillis = millis();

    // Leitura dos estados dos sensores
    Sensor1 = digitalRead(pin_S1);
    Sensor2 = digitalRead(pin_S2);

    // Se uma curva foi detectada e 2 segundos se passaram
    if (curvaDetectada && (currentMillis - tempoCurva) >= 300)
    {
        curvaDetectada = false;
    }

    // Se ambos os sensores estiverem fora da linha
    if (!Sensor1 && !Sensor2)
    {
        curvaDetectada = false;
        acionarMotores(curvaDetectada ? VELOCIDADE_CURVA : VELOCIDADE_MAXIMA, curvaDetectada ? VELOCIDADE_CURVA : VELOCIDADE_MAXIMA, true, true);
    }
    
    // Se o Sensor1 estiver sobre a linha e Sensor2 fora da linha
    else if (Sensor1 && !Sensor2)
    {
        tempoCurva = currentMillis;
        curvaDetectada = true;
        direcaoMotor1 = true;
        acionarMotores(VELOCIDADE_CURVA, VELOCIDADE_CURVA, direcaoMotor1, false);
    }

    // Se o Sensor2 estiver sobre a linha e Sensor1 fora da linha
    else if (!Sensor1 && Sensor2)
    {
        tempoCurva = currentMillis;
        curvaDetectada = true;
        direcaoMotor2 = true;
        acionarMotores(VELOCIDADE_CURVA, VELOCIDADE_CURVA, false, direcaoMotor2);
    }
}

// Função para controlar os motores
void acionarMotores(int velocidadeM1, int velocidadeM2, bool direcaoMotor1, bool direcaoMotor2)
{

    // Define a direção dos motores
    digitalWrite(dir1, direcaoMotor1 ? LOW : HIGH);
    digitalWrite(dir2, direcaoMotor2 ? LOW : HIGH);

    // Ativa os motores com as velocidades especificadas
    analogWrite(M1, direcaoMotor1 ? 255 : velocidadeM1);
    analogWrite(M2, direcaoMotor2 ? 255 : velocidadeM2);
}
