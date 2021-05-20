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

Fonctions d'affichage :
On a fait le choix de mettre les fonctions d'affichage dans des fichiers de compilation séparés (fsprint.c et fsprint.h) pour faciliter la lisibilité.
