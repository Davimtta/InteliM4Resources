//Este é um código adicional, onde dois leds são acendidos alternadamente.

void setup()
{
  pinMode(13, OUTPUT); //declarando que o pino é de saída
  pinMode(7, OUTPUT);  //declarando que o pino é de saída
}

void loop()
{
  digitalWrite(13, HIGH); //Enviando ível lógico alto - led aceso
  digitalWrite(7, LOW);   //Enviando ível lógico baixo - led apagado
  delay(1000); 
  digitalWrite(13, LOW); //Enviando ível lógico baixo - led apagado
  digitalWrite(7, HIGH); //Enviando ível lógico alto - led aceso
  delay(1000); 
}

//A simulação deste código está na pasta videos com o título 'simulacao2.mp4'