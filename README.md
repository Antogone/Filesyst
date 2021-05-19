# Filesyst
Structure d'arbres avec nombre quelconque d'enfants : 
On a choisi de représenter le noeuds enfants dans une liste chainée c'est-à-dire que chaque noeud enfant pointe vers sont frère suivant 
(et vers son parent pour faciliter la  remontée dans l'arbre)
Arbres avec types de noeuds différents :
Les structures de noeud contiennent un type enum qui précise s'il s'agit d'un dossier ou d'un fichier 
et ils contiennent un pointeur data qui pointe alors soit sur une structure dossier soit sur une structure fichier.
Les structures dossiers uniquement pointent vers un enfant.
