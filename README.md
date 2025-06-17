## Détection de Somnolence et Arrêt Automatique d’un Véhicule Autonome

### Aperçu du Projet
Ce projet vise à détecter la somnolence et le bâillement du conducteur en temps réel à l'aide d'une caméra et d'un système de vision par ordinateur. Lorsqu'un état de somnolence ou un bâillement est détecté, le système déclenche une alarme et arrête automatiquement le véhicule après avec décélération progressive pour assurer la sécurité.

(./Docs/circuit.jpg)
### Project Structure 
├── Docs/

  ├── circuit.jpg               
  └── drowsy.jpeg               
├── Models/
  ├── haarcascade_frontalface_default.xml    
  └── shape_predictor_68_face_landmarks.dat  
├── Drowsiness_Detection.py        
├── mvvoiture.ino                  
└── README.md                      

### Fonctionnalités Principales
[Caméra] → 
    ├─[Analyse Yeux (EAR), Analyse Lèvres] → [Détection Somnolence] → [Alarme] → [Arrêt Véhicule]

### Configuration et Exécution

#### Overview

Ce guide explique comment installer et utiliser le système de détection de somnolence. Après avoir branché la caméra Raspberry Pi et l'Arduino, installez les librairies Python nécessaires (opencv, dlib). Exécutez ensuite le script Python : il analysera en temps réel les yeux et la bouche du conducteur. En cas de somnolence détectée, une alarme se déclenche et un signal est envoyé à l'Arduino pour stopper le véhicule. Un bouton d'urgence permet aussi d'arrêter manuellement le système.

#### Prérequis

# Installer les bibliothèques Python nécessaires :

pip install opencv-python imutils dlib picamera2 serial

# Exécution du Script Python
Branchez la caméra Pi et assurez-vous qu'elle est détectée.

Exécutez le script de détection :

python Drowsiness_Detection.py

Appuyez sur q pour quitter le programme.

# Téléversement du Code Arduino
Ouvrez le fichier mvvoiture.ino dans l'IDE Arduino.

Sélectionnez la carte Arduino et le port approprié.

Téléversez le code sur l'Arduino.

### Algorithm
Chaque œil est représenté par 6 points (x, y), en commençant par le coin externe gauche de l’œil (comme si on regardait la personne en face), puis en suivant le contour de l’œil dans le sens horaire.
Le système analyse 20 images consécutives, et si le ratio d’aspect de l’œil (Eye Aspect Ratio) est inférieur à 0,25, une alarme est déclenchée.

(./Docs/eye1.jpg)
(./Docs/eye2.png)

### Résultat
(./Docs/drowsy.JPG)

### Améliorations Futures
- **Intégration de Capteurs Supplémentaires** : Utiliser des capteurs de fréquence cardiaque ou de mouvement pour améliorer la détection de la fatigue.

- **Interface Utilisateur Graphique** : Développer une interface pour afficher les statistiques en temps réel.

- **Amélioration des Performances** : Optimiser le script Python pour une exécution plus fluide sur Raspberry Pi.
