TP de RYCKEMBUSCH Nicolas

Choix de baser le switch sur les caractères plutot que sur les états, afin de gérer
les commentaires (possible aussi de les considèrer comme un autre automate et de les
imbriquer dans un autre switch).
Je présume qu'après c'est un choix: switcher sur les états / commentaires et faire 
les verifications pour chaque caracteres a chaque fois, ou switcher sur les caracteres 
et faire les verifications sur les etats / commentaires a chaque fois.

./bin/pp < ./test/pourri.c > result
