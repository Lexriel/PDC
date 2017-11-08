Rémi Houdelette
Licence Informatique - Semestre 5
Groupe 2

PDC
TP3 - Le pretty-printer



La logique du pretty-printer est :
- Chaque accolade ouvrante doit être à une nouvelle ligne, au même niveau de tabulation que la ligne précédente.
La prochaine instruction doit être à la ligne suivante et commencer à une tabulation supplémentaire de l'accolade.
- Chaque accolade fermante doit être à une nouvelle ligne, à un niveau de tabulation en moins que la ligne précédente.
La prochaine instruction doit être à la ligne suivante et être au même niveau de tabulation que l'accolade.
- Chaque instruction doit occuper une ligne. Si la ligne précédente était une instruction, alors l'instruction est au même niveau de tabulation qu'elle.
- Chaque ligne de commentaire doit être suivi d'un retour à la ligne avec le même niveau de tabulation qu'elle.
- Chaque ligne commençant par # est une ligne d'instruction au préprocesseur, et sera suivi d'un retour à la ligne sans tabulation.

Pour celà, une fonction afficheTab va permettre d'afficher autant de tabulations que nécessaire.

Tant qu'on n'arrive pas à la fin du fichier (getchar() != EOF), on va lire le caractère, et le traiter grâce à un switch selon le caractère de la manière
décrite ci-dessus. Le seul cas qui pose problème est la parenthèse fermante : comme elle doit retirer une tab par rapport au nombre précédent, il faudrait 
pouvoir supprimer des caractères du flux déjà sorti. C'est pourquoi je passe une nouvelle fois à la ligne avant de fermer une accolade, afin de pouvoir 
effectuer le retrait de tabulation nécessaire. Autrement il faudrait réécraser tout ce qui a déjà été écrit, ce qui pourrait poser problème dans le cas 
de très gros fichiers.