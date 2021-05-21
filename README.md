# Filesyst
Structure d'arbres avec nombre quelconque d'enfants :
On a choisi de représenter le nœuds enfants dans une liste chaînée c'est-à-dire que chaque nœud enfant pointe vers sont frère suivant
(et vers son parent pour faciliter la  remontée dans l'arbre
et de même chaque nœud pointe vers son frère précédent)
Arbres avec types de nœuds différents :
Les structures de nœud contiennent un type enum qui précise s'il s'agit d'un dossier ou d'un fichier
et ils contiennent un pointeur data qui pointe alors soit sur une structure dossier soit sur une structure fichier.
Les structures dossiers uniquement pointent vers un enfant.

Fonctions de l'arborescence:
Tous les parcours sont implémentés de manière récursive.
Pour l'ajout de dossier ou fichier à l'arborescence on passe par une fonction générique directory_add_node à la fin du traitement spécifique au type.
De même pour les fonctions de suppression avec directory_remove_node.

Fonctions du terminal:
Comme Antoine travaille sous widows, la principale difficulté pour le terminale a été de trouver une fonction my_getline(faite en cours) afin de pouvoir l'utiliser comme nous l'avons appris durant les derniers tp (Nous nous sommes basées des derniers cours). De manière globale, nous entrons notre chaine de caractère et ils sont ensuite séparés par des espaces (strtok() stoockés dans arguments[]) et nous les utilisons ensuite dans notre terminale lors d'appel de fonction.
Le cd prend en compte les notations ./ pour un chemin relatif et / pour le chemin absolu cd .. permet de remonter vers le parent du dossier actuel mais cd ../dossier donne le même résultat.

Fonctions d'affichage :
On a fait le choix de mettre les fonctions d'affichage dans des fichiers de compilation séparés (fsprint.c et fsprint.h) pour faciliter la lisibilité.
