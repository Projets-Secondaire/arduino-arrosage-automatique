 
const int pinCapteurHumidite1 = A2; // Capteur d'humidité du sol 1
const int relaisPompeReservoir = 11; // Relais pour la pompe du réservoir
const int seuilHumidite1 =500; // Seuil pour le premier capteur d'humidité
const int electrovanne1 = 12; // Électrovanne pour le capteur d'humidité 1
void setup(){
   Serial.begin(9600);

   pinMode(pinCapteurHumidite1, INPUT);
   pinMode(electrovanne1, OUTPUT);
  pinMode(relaisPompeReservoir, OUTPUT);
}

void loop(){
   
  Serial.print(" : ");
  Serial.println(pinCapteurHumidite1);
  
   int humidite1 = analogRead(pinCapteurHumidite1);
   if (humidite1 < seuilHumidite1) {
    // Si l'humidité est inférieure au seuil, ouvrir l'électrovanne 1
    digitalWrite(electrovanne1, HIGH);
    digitalWrite(relaisPompeReservoir, HIGH);
  } else {
    // Sinon, fermer l'électrovanne 1
    digitalWrite(electrovanne1, LOW);
    digitalWrite(relaisPompeReservoir, LOW);
  }
 
  delay(1000); 

}