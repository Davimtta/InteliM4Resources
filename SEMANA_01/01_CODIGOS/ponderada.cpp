// C++ code
// Esta é a simulação 1 
//(realizada seguindo o barema presente no card da Adalove)
// Feita por Davi Motta

// Cálculo do valor do resistor (resistência):
//U = R.i -> R = U/i
//U = Ur + Ul  (a tensão total do circuito é a soma das suas tensões, no cado do resistor e do led)
//U = 4,4 V
//i = 22 mA
//R = 4,4/22 . 10^(-3) -> R = 0,2 . 10^3
//R = 200 ohms

void setup()
{
  pinMode(12, OUTPUT); //declarando que o pino é de saída
}

void loop()
{
  digitalWrite(12, HIGH); //Enviando ível lógico alto - led aceso
  delay(1000); 
  digitalWrite(12, LOW);//Enviando ível lógico baixo - led apagado
  delay(500); 
}
