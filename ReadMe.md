
  
  

## Prérequis

Avant de compiler l'application, assurez-vous d'avoir GTK installé sur votre système. 

## Compilation

  ## Compilation

Compilez l'application avec la commande suivante :

```bash
gcc -o simple_gtk testGtk.c image.c arbrezpixel.c zpixel.c stack2.c $(pkg-config --cflags --libs gtk+-3.0) -lm
```

## Exécution

Exécutez le binaire compilé :

```bash
./simple_gtk
```

## Utilisation

1. Cliquez sur "Fichier" dans le menu et choisissez "Ouvrir".
2. Sélectionnez un fichier image BMP.
3. L'application traitera l'image et affichera le résultat.
4. L'image traitée est enregistrée sous `images/result.bmp`.
  

## Travail réalisé

  

### Interface graphique :

L'interface graphique contient les éléments suivants

  

1.  **Fenêtre "A propos"**

- Affiche des informations sur l'application.

- Contient un nom, une version et un bouton "Ok" pour fermer.

  

2.  **Barre de menu**

- Comprend des options "Fichier" avec New, Open, Save, etc., et "Aide" avec l'option "A propos".
- Seule l'option Open dans la barre Fichier est fonctionnelle et elle permet de charger une image sous format Bmp

  

3.  **Fenêtre principale**

- Contient une disposition horizontale avec trois zones :

-  **Zone gauche (vbox4)** : Affiche une image initiale et une zone de sélection de filtre.

-  **Zone centrale (vbox2)** : Contient des boutons radio pour choisir un filtre et une échelle pour ajuster le seuil.

-  **Zone droite (vbox5)** : Affiche  l'image dégradée.

  

4.  **Fenêtre "Fichier"**

- Permet de gérer les fichiers avec une boîte pour la sélection de fichiers.

### Connexion entre  l'interface graphique et le code :
La connexion entre l'interface graphique et le code est géré par le fichier testGtk.c qui contient les fonctions suivantes : 


1. **Fonction `write_bmp` :**
   - Écrit une image dans un fichier BMP.
   - Prend en entrée le nom du fichier (`filename`) et une structure `Image` contenant les informations sur l'image et ses pixels.
   - Vérifie la validité de la structure et des pixels.
   - Ouvre le fichier en mode binaire (`wb`).
   - Initialise l'en-tête BMP et le remplit avec les informations de l'image.
   - Écrit l'en-tête et les pixels dans le fichier.
   - Ferme le fichier.

2. **Fonction `open_dialog` :**
   - Appelée lorsqu'un élément de menu est sélectionné pour ouvrir un fichier.
   - Affiche une boîte de dialogue de sélection de fichier.
   - Si un fichier BMP est sélectionné, charge son contenu dans un widget image, construit un arbre à partir de l'image, le modifie, et sauvegarde la nouvelle image dans un fichier BMP.
   - Affiche les images initiale et modifiée dans deux widgets distincts.

3. **Fonctions `on_about_activate` et `on_fichier_activate` :**
   - Appelées lorsqu'un élément de menu "A propos" ou "Fichier" est activé.
   - Affichent respectivement les fenêtres associées ("A propos" et "Fichier").

4. **Fonction `main` :**
   - Point d'entrée de l'application.
   - Initialise GTK, charge l'interface utilisateur à partir d'un fichier Glade.
   - Connecte les fonctions définies ci-dessus aux signaux correspondants (clic sur bouton, activation de menu).
   - Affiche la fenêtre principale et lance la boucle principale de l'interface GTK.

En résumé, le code gère les interactions avec l'interface graphique, la manipulation d'images BMP, la création et la modification d'un arbre d'images, et l'affichage des résultats. La logique de l'application est principalement définie dans ces fonctions.


