# define VRAI (1 == 1)
# define FAUX (! VRAI)

# define CHIFFRE(c)     ((c>='0')&&(c<='9'))
# define MAJUSCULE(c)   ((c>='A')&&(c<='Z'))
# define CHIFROUMAJ(c)  (CHIFFRE(c)||MAJUSCULE(c))

# define mauvais_carre(x)   x*x        /* incorrect */
# define bon_carre(x)       ((x)*(x))  /* correct */
