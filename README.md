# Filesyst
Structure d'arbres avec nombre quelconque d'enfants :
On a choisi de représenter le nœuds enfants dans une liste chaînée c'est-à-dire que chaque nœud enfant pointe vers sont frère suivant
(et vers son parent pour faciliter la  remontée dans l'arbre)
Arbres avec types de nœuds différents :
Les structures de nœud contiennent un type enum qui précise s'il s'agit d'un dossier ou d'un fichier
et ils contiennent un pointeur data qui pointe alors soit sur une structure dossier soit sur une structure fichier.
Les structures dossiers uniquement pointent vers un enfant.
