//Proof of concept for reading continuous sensors
#define sensor1Pin A0
#define sensor2Pin A1
#define output1Pin 3
#define buttonPin 4


//infos sensor1
int sensor1=0;
int sensor1Max=0;
int sensor1Min=1023;
long sensor1Moy=sensor1;
//info sensor 2 
int sensor2=0; 
int sensor2Max=0;
int sensor2Min=1023;
long sensor2Moy=sensor2;
//infos bouton
int button = HIGH;
int previousButton= button;
//info variable de sortie pour LED
int output1=0;
//gestion du temps & moyennage
long time=0;
long dureeMoyenne=4000;
long nbMoyenne=0;

void setup() {
  pinMode(output1Pin, OUTPUT); //Using Digital pin 3 for PWM on an LED
  pinMode(13, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600); //Initilizing Serial
  
}

void loop(){
  time=millis();
  
  while(millis()-time < dureeMoyenne){
    sensor1=analogRead(sensor1Pin); //lecture du capteur
    //Recalage des bornes min / max 
    if (sensor1 > sensor1Max)
        sensor1Max=sensor1;
    if (sensor1 < sensor1Min) 
        sensor1Min=sensor1;
    //delay(1); //to allow DAC to reset
    
    sensor2=analogRead(sensor2Pin);
    //recalage des bornes min / max
    if (sensor2 > sensor2Max)
        sensor2Max=sensor2;
    if (sensor2 < sensor2Min) 
        sensor2Min=sensor2;
    //delay(1); //to allow DAC to reset
    nbMoyenne++;
    sensor1Moy+= sensor1;
    sensor2Moy+= sensor2;
  }
  
  //Affichage des Moyennes de la "dureeMoyenne" précédente
  /* DEBUG
  Serial.println(sensor1Moy);
  Serial.println(sensor2Moy);
  Serial.println(nbMoyenne);
  */ 
  sensor1Moy=sensor1Moy/nbMoyenne;
  sensor2Moy=sensor2Moy/nbMoyenne;
  Serial.println("LES MOYENNES : ");
  Serial.print ("moyenne du sensor 1 = ");
  Serial.println(sensor1Moy);
  Serial.print ("moyenne du sensor 2 = ");
  Serial.println(sensor2Moy);
  sensor1Moy=0;
  sensor2Moy=0;
  nbMoyenne=0;
  /*
  button=digitalRead(buttonPin);
  if( button==LOW && previousButton ==HIGH){
  Serial.println(sensor1);
  Serial.println(sensor2);
  
  Serial.println("");
  }
  previousButton=button;
  */
  output1=map(sensor2, sensor2Min, sensor2Max, 0,255); //normalisation des valeurs pour sortie sur 255
  analogWrite(output1Pin,output1);
}

