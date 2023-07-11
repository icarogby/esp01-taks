#define LED 2   // Constante LED associada ao pino GPIO2.
#define BUT 0   // Constante BUT associada ao pino GPIO0.

int vbut = LOW; // Valor lido do botão.
int vser = 0;   // Valor lido da entrada serial.

// Função de interrupção
void ICACHE_RAM_ATTR digin() {
  vbut = digitalRead(BUT); // Lê o valor lógico da tensão no pino 0.

}

void setup() {
  pinMode(BUT, INPUT);  // Pino do botão definido como de entrada.
  pinMode(LED, OUTPUT); // Pino do led definido como de saída

  Serial.begin(74880);  // Comunicação com baud rate 74880 Hz.

  // Interrupção associada ao pino do botão
  // associada à função digin
  // ocorrendo sempre que houver variação de nível lógico no pino.
  attachInterrupt(digitalPinToInterrupt(BUT), digin, CHANGE);

}

void loop() {
  // Se houver algo na fila do console serial...
  if (Serial.available() > 0) {
    Serial.print("Serial: ");
    
    vser = Serial.parseInt();  // Encontrar um inteiro...
    Serial.readString();	 // Limpa o buffer.
    
    Serial.println(vser);      // Imprime o número lido.

  }

  if (vbut == LOW)             // Se o botão não estiver pressionado
      analogWrite(LED, vser);  // escrita analógica.
  else                         // caso contrário...
      digitalWrite(LED, vbut); // escrita digital.

}
