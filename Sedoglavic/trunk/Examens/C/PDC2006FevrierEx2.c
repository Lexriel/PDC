#include<stdio.h>
union compteenbanque {
	double          solde;
	int             numero;
};
struct etudiant {
	char          **nom;
	union compteenbanque potdevin;
	enum e {
		male, femelle, indetermine
	}               genre;
	unsigned short  numiden;
	struct etudiant *acopiersur;
};
typedef struct etudiant *PDC[100];

int
main(void)
{
	printf("%d\n", sizeof(struct etudiant));
	printf("%d\n", sizeof(PDC));
	return 0;
}