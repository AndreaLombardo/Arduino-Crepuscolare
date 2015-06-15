/*
 * Arduino Crepuscolare
 * Semplice programmino per mostrare come creare un sistema crepuscolare utilizzando Arduino
 *
 * Autore  : Andrea Lombardo
 * Web     : http://www.lombardoandrea.com
 * Post    : http://bit.ly/arduino-crepuscolare
 * Git     : https://github.com/AndreaLombardo/Arduino-Crepuscolare
 */ 

static int sensore_luce = A0; //pin analogico che riceve l'indice di luminosità
static int comando_luce = 13; //pin che comanderà la luce (o sistema di pilotaggio grosso carico)
static int minuti_attesa = 2; //specifica il numero di minuti dopo i quali rieseguire il controllo una volta accesa la luce

static int soglia = 15; //modificare questo valore per definire la soglia dopo la quale verr accesa la luce

unsigned long attesa; //conterra' i minuti di attesa trasformati in millisecondi
int luminosita; // conterra' l'indice di luminosità percepito
boolean luceOn; // conterra' lo stato della luce, true = 1 = accesa, false = 0 = spenta

void setup() {

  //inizializzo comunicazione seriale per mostrare a video quello che stà accadendo
  Serial.begin(9600);

  //definisco la modalità dei pin
  pinMode(comando_luce, OUTPUT);
  pinMode(sensore_luce, INPUT);

  //trasformo i minuti d'attesa in millisecondi da dare in pasto alla funzione delay
  attesa = ((minuti_attesa * 60UL ) * 1000UL);

  //imposto indice di luminosità a 0
  luminosita = 0;

  //di default imposto lo stato della luce = a spento
  luceOn = false;

  //spengo la luce
  digitalWrite(comando_luce, LOW);
}

void loop() {

  //leggo l'indice di luminosità dal pin A0 (sensore_luce)
  luminosita = analogRead(sensore_luce);

  //comunico le info via monitor seriale
  Serial.print("Luminosita' percepita : ");
  Serial.print(luminosita);

  //se l'indice di luminosità è inferiore alla soglia
  if (luminosita < soglia) {
    //accendo la luce
    digitalWrite(comando_luce, HIGH);
    //informo il programma che la luce è accesa
    luceOn = true;
    //informo tramite monitor seriale
    Serial.print(" - Accendo luce e aspetto ");
    Serial.print(minuti_attesa);
    Serial.print(" minuti (");
    Serial.print(attesa);
    Serial.print(" millisecondi) prima di rieseguire il controllo");
    //mi metto in pausa e aspetto che finiscano i minuti_attesa
    delay(attesa);
  } else {
    //se l'indice di luminosità non è inferiore alla soglia, mantengo la luce spenta
    digitalWrite(comando_luce, LOW);
    //informo il programma che la luce è spenta
    luceOn = false;
  }

  //invio le info al monitor seriale
  Serial.print(" - Stato luce : ");
  Serial.println(luceOn);

}
