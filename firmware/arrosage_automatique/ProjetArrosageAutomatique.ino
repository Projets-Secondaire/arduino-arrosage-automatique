const int pinCapteurReservoir = A1; // Capteur ultrason du réservoir
const int pinCapteurHumidite1 = A2; // Capteur d'humidité du sol 1
const int pinCapteurHumidite2 = A3; // Capteur d'humidité du sol 2

const int boutonArretUrgence = 2; // Bouton pour l'arrêt d'urgence
const int boutonManuel = 3; // Bouton pour le mode manuel
const int boutonRemplissage = 4; // Bouton pour le remplissage de la cuve externe
const int boutonResetArretUrgence = 5; // Bouton pour réinitialiser l'arrêt d'urgence
const int temoinArrosagePlantes = 6; // Témoin pour indiquer l'arrosage des plantes
const int temoinNiveauBasReservoir = 7; // Témoin pour indiquer un niveau bas d'eau dans le réservoir
const int temoinNiveauHautReservoir = 8; // Témoin pour indiquer un niveau haut d'eau dans le réservoir
const int temoinArretUrgence = 9; // Témoin pour indiquer l'arrêt d'urgence
const int relaisPompeAquarium = 10; // Relais pour la pompe de l'aquarium
const int relaisPompeReservoir = 11; // Relais pour la pompe du réservoir
const int electrovanne1 = 12; // Électrovanne pour le capteur d'humidité 1
const int electrovanne2 = 13; // Électrovanne pour le capteur d'humidité 2
const int selecteurModeManuel = A5; // Sélecteur pour le mode manuel
const int selecteurModeAutomatique = A4; // Sélecteur pour le mode automatique

const int TEMPS_CLIGNOTEMENT = 500; // Durée du clignotement en millisecondes

const int seuilHumidite1 = 500; // Seuil pour le premier capteur d'humidité
const int seuilHumidite2 = 500; // Seuil pour le deuxième capteur d'humidité

const float NIVEAU_HAUT = 6.0; // Niveau maximum dans le réservoir
const float NIVEAU_BAS = 50.0; // Niveau minimum dans le réservoir

const int NUMERO_LECTURES = 10; // Nombre de lectures pour la moyenne

float lectures[NUMERO_LECTURES];
int indexLecture = 0;

void setup() {
  pinMode(pinCapteurHumidite1, INPUT);
  pinMode(pinCapteurHumidite2, INPUT);
  pinMode(pinCapteurReservoir, INPUT);
  pinMode(boutonArretUrgence, INPUT_PULLUP);
  pinMode(boutonManuel, INPUT_PULLUP);
  pinMode(boutonRemplissage, INPUT_PULLUP);
  pinMode(boutonResetArretUrgence, INPUT_PULLUP);
  pinMode(temoinArrosagePlantes, OUTPUT);
  pinMode(temoinNiveauBasReservoir, OUTPUT);
  pinMode(temoinNiveauHautReservoir, OUTPUT);
  pinMode(temoinArretUrgence, OUTPUT);
  pinMode(relaisPompeAquarium, OUTPUT);
  pinMode(relaisPompeReservoir, OUTPUT);
  pinMode(electrovanne1, OUTPUT);
  pinMode(electrovanne2, OUTPUT);
  pinMode(selecteurModeManuel, INPUT_PULLUP);
  pinMode(selecteurModeAutomatique, INPUT_PULLUP);

  digitalWrite(relaisPompeAquarium, HIGH);  
  digitalWrite(relaisPompeReservoir, HIGH); 
  digitalWrite(electrovanne1, HIGH);        
  digitalWrite(electrovanne2, HIGH);        
  digitalWrite(temoinArrosagePlantes, HIGH); 
  digitalWrite(temoinNiveauBasReservoir, HIGH);
  digitalWrite(temoinNiveauHautReservoir, HIGH);
  digitalWrite(temoinArretUrgence, HIGH);

  // Initialiser les lectures à zéro
  for (int i = 0; i < NUMERO_LECTURES; i++) {
    lectures[i] = 0;
  }

  Serial.begin(9600);
}

void loop() {
  int etatBoutonArretUrgence = digitalRead(boutonArretUrgence);
  int etatBoutonResetArretUrgence = digitalRead(boutonResetArretUrgence);
  int etatBoutonManuel = digitalRead(boutonManuel);
  int etatSelecteurModeManuel = digitalRead(selecteurModeManuel);
  int etatBoutonRemplissage = digitalRead(boutonRemplissage);
  int etatSelecteurModeAutomatique = digitalRead(selecteurModeAutomatique);

  if (etatBoutonArretUrgence == HIGH) {
    arretUrgence();
    clignoterTemoin(temoinArretUrgence);
  } else {
        
    if (etatBoutonResetArretUrgence == LOW) {
      reactiverSysteme();
    }

     if (etatSelecteurModeManuel == HIGH && etatBoutonManuel == LOW) {

      demarrerPompeReservoir(); 
      ouvrirElectrovanne1();
      ouvrirElectrovanne2();
     

      } else {       
      while (lireNiveauReservoirMoyenne()  >= NIVEAU_BAS) {
       
      }   
      
      arreterPompeReservoir();
      fermerElectrovanne1();
      fermerElectrovanne2();

      }
      if (etatSelecteurModeManuel == HIGH && etatBoutonRemplissage == LOW) {
     demarrerPompeAquarium();
    } else {  
      while (lireNiveauReservoirMoyenne() == NIVEAU_HAUT) {
       // Attendre que le niveau atteigne le niveau haut
      }   
     arreterPompeAquarium();
     arreterPompeReservoir();
     fermerElectrovanne1();
     fermerElectrovanne2();


     }


    if (etatSelecteurModeAutomatique == HIGH) {
      int humidite1 = analogRead(pinCapteurHumidite1);
      int humidite2 = analogRead(pinCapteurHumidite2);

      if (humidite1 < seuilHumidite1 && humidite2 < seuilHumidite2) { // Les deux sols doivent être secs pour arroser

        ouvrirElectrovanne1();
        ouvrirElectrovanne2();
        demarrerPompeReservoir();

      } else {
        while (lireNiveauReservoirMoyenne()  >= NIVEAU_BAS) {
    
        // Attendre que le niveau atteigne le niveau bas
      }
        fermerElectrovanne1();
        fermerElectrovanne2();
        arreterPompeReservoir();

      }

    }

    float niveauReservoir = lireNiveauReservoirMoyenne();

    if (niveauReservoir  >= NIVEAU_BAS) {
      digitalWrite(temoinNiveauBasReservoir, LOW);
      digitalWrite(temoinNiveauHautReservoir, HIGH);
      arreterPompeReservoir();
      

    } else if (niveauReservoir == NIVEAU_HAUT) {
      digitalWrite(temoinNiveauHautReservoir, LOW);
      digitalWrite(temoinNiveauBasReservoir, HIGH);
      arreterPompeAquarium();

    } 
  

    Serial.print("Humidite du sol 1 : ");
    Serial.print(analogRead(pinCapteurHumidite1));
    Serial.print(", Humidite du sol 2 : ");
    Serial.println(analogRead(pinCapteurHumidite2));

    Serial.print("Niveau du reservoir : ");
    Serial.print(niveauReservoir);
    Serial.println(" cm");
    delay(1000);
  }
}

void arretUrgence() {
  digitalWrite(electrovanne1, HIGH);
  digitalWrite(electrovanne2, HIGH);
  digitalWrite(relaisPompeAquarium, HIGH);
  digitalWrite(relaisPompeReservoir, HIGH);
  digitalWrite(temoinArrosagePlantes, HIGH);

}

void reactiverSysteme() {
  // Remettre à zéro les indicateurs et réactiver le système
  digitalWrite(temoinArretUrgence, HIGH);
  digitalWrite(relaisPompeAquarium, HIGH);  // Éteindre pompe aquarium
  digitalWrite(relaisPompeReservoir, HIGH); // Éteindre pompe réservoir
  digitalWrite(electrovanne1, HIGH);        // Fermer électrovanne 1
  digitalWrite(electrovanne2, HIGH);        // Fermer électrovanne 2
  digitalWrite(temoinArrosagePlantes, HIGH);
}

float lireNiveauReservoir() {
  int sensorValue = analogRead(pinCapteurReservoir);
  float voltage = sensorValue * (5.0 / 1023.0);
  float distanceMeters = 0.051 + ((voltage / 5.0) * (0.508 - 0.051));
  float distanceCm = distanceMeters * 100;
  return distanceCm;
}

float lireNiveauReservoirMoyenne() {
  lectures[indexLecture] = lireNiveauReservoir();
  indexLecture = (indexLecture + 1) % NUMERO_LECTURES;

  float somme = 0;
  for (int i = 0; i < NUMERO_LECTURES; i++) {
    somme += lectures[i];
  }
  return somme / NUMERO_LECTURES;
}

void demarrerPompeAquarium() {
  digitalWrite(relaisPompeAquarium, LOW); // Démarrer pompe aquarium
}

void arreterPompeAquarium() {
  digitalWrite(relaisPompeAquarium, HIGH); // Arrêter pompe aquarium
}

void demarrerPompeReservoir() {
  digitalWrite(relaisPompeReservoir, LOW); // Démarrer pompe réservoir
  digitalWrite(temoinArrosagePlantes, LOW);

}

void arreterPompeReservoir() {
  digitalWrite(relaisPompeReservoir, HIGH); // Arrêter pompe réservoir
  digitalWrite(temoinArrosagePlantes, HIGH);

}

void ouvrirElectrovanne1() {
  digitalWrite(electrovanne1, LOW); // Ouvrir électrovanne 1
}

void fermerElectrovanne1() {
  digitalWrite(electrovanne1, HIGH); // Fermer électrovanne 1
}

void ouvrirElectrovanne2() {
  digitalWrite(electrovanne2, LOW); // Ouvrir électrovanne 2

}

void fermerElectrovanne2() {
  digitalWrite(electrovanne2, HIGH); // Fermer électrovanne 2
}

void clignoterTemoin(int pin) {
  digitalWrite(pin, HIGH);
  delay(TEMPS_CLIGNOTEMENT);
  digitalWrite(pin, LOW);
  delay(TEMPS_CLIGNOTEMENT);
}