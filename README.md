# cy-dventure
projet pre-ing

## Apercu
ce dépôt contient un moteur de jeu basé sur le langage C pour créer et exécuter des jeux textuels interactifs, ou des histoires de type "choisissez votre propre aventure". Le code est structuré autour de divers éléments du jeu tels que l'histoire, les choix, les événements et l'inventaire.

## Composants Clés
1. Étapes de l'histoire (step.h)
Chaque étape de l'histoire est représentée par la structure Step. Chaque Step comprend une description (Description), un événement (Event), et un tableau de choix (Choice) que le joueur peut faire. Des fonctions sont fournies pour charger, exécuter et libérer une Step.

2. Inventaire (inventory.h)
La structure Inventory représente l'inventaire du joueur, qui peut contenir un certain nombre d'éléments. Des fonctions sont fournies pour initialiser l'inventaire, y ajouter un élément, imprimer son contenu, vérifier s'il contient un certain élément, et libérer la mémoire allouée quand elle n'est plus nécessaire.

3. Utilitaires (util.h)
Une fonction utilitaire est fournie pour supprimer les caractères de nouvelle ligne à la fin d'une chaîne de caractères. Cela peut être particulièrement utile lors de la lecture de l'entrée d'un joueur.

## Utilisation:
- ce deplacer dans le fichier ppp puis le sous dossier 1-sources avec 'cdd ppp/1-sources/'
- pour compiler 'make'
- lancer le jeu './game'
