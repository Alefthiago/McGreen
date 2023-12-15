#define TAMANHO_MAXIMO 10

// Define os pinos dos motores
#define M1 9
#define dir1 8

#define M2 11
#define dir2 10

// Define os pinos dos sensores
#define pin_S1 6
#define pin_S2 7

// Variáveis para armazenar os estados dos sensores
bool Sensor1 = false;
bool Sensor2 = false;

// Define as velocidades dos motores
int velocidade = 155;
int curva = 140;

int padrao_sensor[TAMANHO_MAXIMO] = {0};
int n_atual_array = 0;

int contador = 0;
int resultado = 0;

void adicionarElemento(int novoElemento)
{
    if (n_atual_array < TAMANHO_MAXIMO)
    {
        padrao_sensor[n_atual_array] = novoElemento;
        n_atual_array++;
    }
    else
    {
    }
}

void limparArray()
{
    for (int i = 0; i < TAMANHO_MAXIMO; ++i)
    {
        padrao_sensor[i] = 0;
    }

    n_atual_array = 0;
}

void setup()
{
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);

    pinMode(dir1, OUTPUT);
    pinMode(dir2, OUTPUT);

    pinMode(pin_S1, INPUT);
    pinMode(pin_S2, INPUT);
}

void loop()
{
    // Leitura dos estados dos sensores
    Sensor1 = digitalRead(pin_S1);
    Sensor2 = digitalRead(pin_S2);

    resultado = Sensor1 - Sensor2;
    // Adiciona a leitura dos sensores ao array

    // Se ambos os sensores estiverem fora da linha
    if (!Sensor1 && !Sensor2)
    {
        // Ambos os motores avançam
        acionarMotores(velocidade, velocidade);
    }
    // Se o Sensor1 estiver sobre a linha e Sensor2 fora da linha
    else if (Sensor1 && !Sensor2)
    {
        // Motor1 gira mais rápido para curvar para a esquerda
        acionarMotores(curva, 0);
    }
    // Se o Sensor2 estiver sobre a linha e Sensor1 fora da linha
    else if (!Sensor1 && Sensor2)
    {
        // Motor2 gira mais rápido para curvar para a direita
        acionarMotores(0, curva);
    }

    adicionarElemento(resultado);

    if (contador == 10)
    {
        limparArray();
        contador = 0;
        
    }
    else
    {
        contador++;
    }
}

// Função para controlar os motores
void acionarMotores(int velocidadeM1, int velocidadeM2)
{
    // Define a direção dos motores
    if (velocidadeM1 >= 0)
    {
        digitalWrite(dir1, LOW); // Define a direção do Motor1 para frente
    }
    else
    {
        digitalWrite(dir1, HIGH);     // Define a direção do Motor1 para trás
        velocidadeM1 = -velocidadeM1; // Transforma a velocidade negativa em positiva
    }

    if (velocidadeM2 >= 0)
    {
        digitalWrite(dir2, LOW); // Define a direção do Motor2 para frente
    }
    else
    {
        digitalWrite(dir2, HIGH);     // Define a direção do Motor2 para trás
        velocidadeM2 = -velocidadeM2; // Transforma a velocidade negativa em positiva
    }

    // Ativa os motores com as velocidades especificadas
    analogWrite(M1, velocidadeM1);
    analogWrite(M2, velocidadeM2);
}