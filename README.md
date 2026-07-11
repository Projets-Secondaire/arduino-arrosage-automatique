# Arrosage automatique (SI4) – Arduino

Situation d'intégration 4 – Projet de fin d'étude, qualification Électricien-Automaticien
Institut Saint Joseph, Etterbeek – Année académique 2023-2024

## Description

Système d'arrosage automatique pour les plantes de l'atelier, développé sur Arduino UNO. Le système gère à la fois le remplissage d'un réservoir d'eau (depuis un aquarium) et l'irrigation goutte-à-goutte des plantes, avec un sélecteur permettant de basculer entre un mode manuel et un mode automatique piloté par capteurs d'humidité.

## Fonctionnement

**Mode manuel**
- Maintien du bouton de remplissage → la pompe de l'aquarium remplit le réservoir
- Maintien du bouton d'arrosage → la pompe du réservoir démarre et les deux électrovannes s'ouvrent

**Mode automatique**
- Si les deux capteurs d'humidité du sol détectent une sécheresse → la pompe du réservoir démarre et les électrovannes s'ouvrent automatiquement
- Le remplissage du réservoir est régulé par un capteur à ultrason (niveau bas / niveau haut)

**Sécurité**
- Bouton d'arrêt d'urgence (coup de poing) + bouton de reset dédié
- 4 témoins de signalisation : arrosage en cours (vert), niveau bas (jaune), niveau haut (bleu), arrêt d'urgence (rouge clignotant)

## Matériel principal

- Arduino UNO R3
- 2 capteurs d'humidité du sol (hygromètre LM393)
- 1 capteur à ultrason (niveau du réservoir)
- 2 pompes submersibles d'aquarium (JEBAO JECOD)
- 2 électrovannes
- Module 8 relais
- Sélecteur manuel/automatique, boutons poussoir, arrêt d'urgence + reset
- 4 témoins LED de signalisation

La liste complète du matériel (références, caractéristiques techniques, justification des choix) est disponible dans le rapport.

## Firmware

- `firmware/arrosage_automatique/` : programme principal (gestion des deux modes, sécurité, lecture des capteurs)
- `firmware/test_seuil_humidite/` : test isolé du capteur d'humidité du sol, utilisé pour calibrer le seuil avant intégration au programme final

## Rapport complet

Le rapport complet (cahier des charges, étude du système, choix technologiques, dimensionnement, schémas, liste du matériel, grafcet niveau 1/2/3, conclusions et maintenance) est disponible dans [`docs/rapport_arrosage_automatique.pdf`](docs/rapport_arrosage_automatique.pdf).