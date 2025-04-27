# Morse_Project
Develop in C++ a program for for encoding/decoding messages in MORSE code.
# Morse Code Converter

## Introduction

Ce projet est un convertisseur de code Morse en C++. Il permet de convertir un message texte en code Morse et vice versa. Le message Morse peut être stocké au format audio WAV, permettant ainsi d'écouter le message en utilisant un lecteur audio comme VLC.

## Prérequis

- Un compilateur C++ (par exemple, `g++`).
- `make` pour la compilation.
- `git` pour cloner le dépôt.

## Installation

1. **Cloner le dépôt** :
   ```sh
   git clone https://github.com/votre_utilisateur/votre_depot.git
   cd Morse_Project
   ```

2. **Compiler le proframm** (Optionne, fichier déjà compilé):
   ```sh
    make myprogram
   ```


## Utilisation

### Encoder un message

Pour encoder un message à partir d'un fichier texte et générer un fichier audio WAV :
```sh
myprogram --encode mymessage.txt mymessage.wav
```

### Décoder un message

Pour décoder un message à partir d'un fichier audio WAV et générer un fichier texte :
```sh
myprogram --decode mymessage.wav mymessage.txt
```

Vous pourrez trouver un fichier texte nommé `text_test.txt` dans le répertoire data pour tester le programme.


## Nettoyage**: Instructions pour nettoyer les fichiers générés par la compilation.

```sh
make clean # Supprime les fichiers objets
make cleanall # Supprime les fichiers objets et le fichier exécutable

```

## Structure du Projet**: Description des fichiers principaux du projet.

main.cpp : Fichier principal contenant la fonction main.
message.cpp : Fichier contenant la classe Message pour gérer les messages texte.
morse_converter.cpp : Fichier contenant la classe MorseConverter pour convertir entre texte et code Morse.audio_wav.cpp : Fichier contenant la classe AudioWav pour gérer la génération et la lecture des fichiers audio WAV.
utils.cpp : Fichier contenant des fonctions utilitaires.
Makefile : Fichier Makefile pour la compilation du projet.

## Auteurs

Alexandre Gavaudan - Etudiant en 3eme Année du Cycle Ingénieur Civil des Mines de Paris