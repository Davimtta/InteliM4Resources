//Neste código acendemos um led laranja utilizando a GPIO 12.

void setup()
{
  pinMode(12, OUTPUT); //declarando que o pino é de saída
}

void loop()
{
  digitalWrite(12, HIGH); //Enviando ível lógico alto - led aceso
  delay(1000); 
  digitalWrite(12, LOW);//Enviando ível lógico baixo - led apagado
  delay(1000); 
}

//A simulação deste código está na pasta videos com o título 'simulacao1.mp4'