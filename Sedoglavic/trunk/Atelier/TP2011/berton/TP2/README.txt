BERTON Edouard

Le programme n'est pas complétement fonctionnel. J'ai essayé de respecter le codage d'un automate, mais des cas m'echappent.

*Indentation : ok
*Commentaires : nok sur les commentaires sur plusieurs lignes
*Erreur : On incrémente et décremente à chaque '{' et '}'. Si l'indentation est de 0, pas de problème, EXIT_SUCCES, si != 0 EXIT_FAILURE
*Une accolade dans un commentaire doit être ignorée : ok
*Aucune modification ne doit être faite sur une ligne commençant par une directive de cpp (#define, #include... ou d'autres lignes commençant par '#') : ok
*Les guillemets ne sont pas traités


Les états de l'automate :

ETAT_DBT_LIGNE :
Etat initial.
Suppression des espaces et des tabulations.
Detection des lignes de directive (envoi en ETAT_CROISILLON)
Detection des accolades ouvrantes et fermante, avec le traitement associé

ETAT_NORMAL :
Etat après lecture d'un caractère de début de ligne.
Detection des accolades ouvrantes et fermante, avec le traitement associé (on note ici de la répétition de code, à optimiser)
Si on lit un '/' il y a peut-être le début d'un commentaire, on passe en ETAT_COM_OUVRANT.

ETAT_CROISILLON :
Lorsque l'on se trouve dans cet état, lecture de caractère jusqu'a trouver un '\n'.
Ensuite, retour en ETAT_DBT_LIGNE.

ETAT_COM_OUVRANT :
Si lecture de '*' on se trouve dans un commentaire et on va dans l'état ETAT_COMMENTAIRE
Sinon, on affiche '/' et on retourne dans ETAT_NORMAL

ETAT_COMMENTAIRE :
Si on lit une '*' il y a peut-être la fin d'un commentaire, on passe en ETAT_COM_FERMANT
Si on lit un '\n' on ferme le commentaire, passe une ligne, et ré-ouvre un commentaire, on reste dans cet état

ETAT_COM_FERMANT :
Si lecture de '/' on trouve la fin d'un commentaire, on retourne dans l'état ETAT_NORMAL
Sinon, on affiche '*' et on retourne dans ETAT_COMMENTAIRE

