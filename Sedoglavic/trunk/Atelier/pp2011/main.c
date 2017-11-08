#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define testa

#ifdef test
#define taille_dico 7
char *dico[taille_dico] = {"pfon","aire","aile","lion","pion","plon","plan"} ;
#else
#define taille_dico 979

/* Un dictionnaire de mots de quatre lettres */
char *dico[taille_dico] = { "drap", "nuee", "agit", "mais", "krak", "eric",
     "aaai", "agir", "drop", "dome", "buis", "rode", "puce", "roda", "drue",
     "buse", "bure", "rode", "haie", "hais", "hait", "puer", "hall", "role",
     "halo", "haro", "puis", "hase", "decu", "pull", "vais", "puma", "haut",
     "valu", "vain", "vase", "alea", "vamp", "thon", "vaux", "vaut", "afin",
     "fier", "fief", "mica", "fiel", "thym", "fini", "midi", "epie", "meat",
     "mien", "fisc", "miel", "film", "mike", "feru", "tige", "mise", "epia",
     "tele", "fevr", "tien", "miss", "mile", "tint", "aout", "fetu", "tilt",
     "mita", "tenu", "mite", "agio", "agir", "agit", "mite", "fele", "ogre",
     "fela", "fele", "meme", "pres", "pref", "aere", "tete", "pret", "tetu",
     "hele", "hote", "here", "foin", "mode", "font", "foot", "moka", "fond",
     "fora", "fort", "toge", "todd", "mont", "mord", "mors", "fore", "mort",
     "four", "toit", "tond", "moto", "tors", "tort", "moue", "moud", "aout",
     "yvan", "tome", "tord", "mous", "yves", "tous", "toux", "flan", "tour",
     "tout", "oeil", "veau", "utah", "utah", "flou", "flot", "heur", "vend",
     "venu", "vent", "velu", "oeuf", "vers", "vert", "flux", "veto", "veuf",
     "veut", "veux", "hale", "hale", "etal", "etai", "etat", "etau", "hata",
     "hate", "ores", "have", "buee", "hate", "jusa", "hair", "etui", "aire",
     "frac", "frai", "fret", "trie", "cade", "tram", "fris", "frit", "froc",
     "cage", "cadi", "trac", "duel", "jade", "cake", "tria", "cane", "dune",
     "camp", "trio", "dura", "cafe", "troc", "mole", "came", "trot", "jais",
     "rude", "trop", "trou", "aine", "ruer", "janv", "tole", "jase", "jars",
     "jasa", "dure", "truc", "java", "jazz", "jase", "rush", "tsar", "epee",
     "clot", "aile", "aigu", "aide", "aine", "hele", "hier", "aile", "vice",
     "vecu", "aise", "aera", "hela", "vint", "viol", "aise", "visa", "vise",
     "aere", "hetu", "vive", "vite", "velo", "ange", "once", "vise", "anis",
     "anon", "onde", "anse", "ansi", "anus", "onze", "cene", "vetu", "onyx",
     "cepe", "hors", "home", "ceci", "houx", "vois", "voir", "voit", "voeu",
     "voix", "cout", "houe", "voie", "volt", "vont", "jean", "coit", "cens",
     "alfa", "cent", "allo", "vote", "vous", "cerf", "cern", "aloi", "jerk",
     "ceux", "jeun", "alto", "vlsi", "amas", "amen", "amer", "ames", "omet",
     "omis", "omit", "arcs", "caid", "oral", "orge", "vrac", "vrai", "fuel",
     "ardu", "ardt", "fuit", "chas", "char", "orme", "aria", "chef", "hote",
     "laid", "sage", "lait", "land", "muni", "tuer", "mule", "lama", "lard",
     "ores", "laps", "turc", "turf", "lame", "fuir", "chai", "chah", "sapa",
     "chat", "mure", "muer", "muet", "full", "sake", "cher", "chez", "saga",
     "saur", "oser", "chic", "tuez", "lame", "choc", "chou", "mura", "musc",
     "muse", "sain", "sais", "sait", "sana", "sang", "sans", "sali", "apex",
     "fute", "sari", "sape", "chut", "sauf", "saut", "sape", "osez", "saxo",
     "jill", "ciel", "cinq", "cime", "opus", "apre", "opte", "apte", "opta",
     "opte", "aval", "cola", "john", "lese", "jonc", "joli", "cote", "coco",
     "tres", "coke", "coin", "conf", "seau", "colt", "seme", "coma", "avec",
     "aveu", "avez", "corp", "joie", "cosy", "clip", "avis", "seme", "lest",
     "sein", "coud", "coup", "cour", "sens", "sent", "self", "sera", "serf",
     "seve", "sers", "zele", "sert", "cote", "type", "joug", "typo", "jour",
     "auto", "ubac", "ovni", "owen", "legs", "clam", "clan", "clef", "aube",
     "lent", "clin", "soul", "clos", "clou", "sema", "leur", "sept", "club",
     "seul", "type", "sexe", "sexy", "skie", "ucla", "crue", "atre", "gain",
     "huit", "gang", "hune", "gala", "gale", "naja", "html", "cote", "nain",
     "cran", "shah", "laic", "aube", "cric", "crin", "cris", "croc", "auge",
     "skia", "cone", "audy", "aune", "huer", "crut", "aura", "cote", "gant",
     "oued", "lice", "auto", "gars", "nais", "lift", "lien", "ours", "nasa",
     "lion", "sied", "nazi", "lira", "lire", "zebu", "lise", "lisp", "show",
     "zele", "lesa", "zinc", "zero", "azur", "lied", "lier", "lieu", "lino",
     "sien", "snob", "silo", "sire", "site", "lese", "oree", "gene", "sofa",
     "loin", "loir", "long", "lors", "soif", "axer", "soir", "ieee", "ayez",
     "zone", "sole", "soli", "sors", "loup", "zona", "zone", "zoom", "gout",
     "noel", "souk", "soya", "mans", "gere", "soda", "soja", "neuf", "soin",
     "soit", "ieee", "sono", "sont", "ibid", "ibis", "geai", "solo", "slip",
     "loto", "sort", "slow", "gens", "nerf", "elle", "nait", "naif", "ouie",
     "ouir", "cube", "erra", "bail", "bain", "cuir", "gata", "gate", "judo",
     "pack", "jube", "gate", "page", "juin", "pane", "quel", "jury", "jupe",
     "paon", "cure", "pars", "paru", "baba", "cuba", "paul", "gite", "watt",
     "erre", "apic", "cube", "cuis", "cuit", "banc", "bang", "jude", "quai",
     "cure", "basa", "base", "juif", "erre", "cuti", "baud", "baux", "pain",
     "pair", "paix", "quoi", "pale", "base", "jute", "parc", "pari", "part",
     "papa", "pape", "neon", "pays", "esse", "gere", "spie", "spot", "neve",
     "gena", "nier", "girl", "unir", "unit", "unix", "gera", "noce", "gond",
     "hifi", "gene", "pere", "noir", "noix", "gnon", "nord", "gene", "nous",
     "ieee", "peau", "idem", "ides", "pend", "goal", "perd", "perl", "pers",
     "peur", "peut", "ebat", "gong", "golf", "pese", "pese", "beau", "pame",
     "glas", "pale", "pama", "pame", "ilot", "pate", "pesa", "stem", "echo",
     "echu", "pate", "ecot", "swap", "ecru", "gras", "bale", "stuc", "grog",
     "gros", "urge", "bati", "daim", "luge", "atil", "race", "dame", "urne",
     "etes", "rame", "luit", "suez", "luxe", "kart", "etre", "star", "raid",
     "suce", "suif", "rail", "suis", "suit", "suiv", "rang", "luth", "rare",
     "surf", "phil", "stop", "yard", "grec", "greg", "user", "gril", "gris",
     "beat", "dada", "dais", "lune", "grue", "kaki", "pied", "dard", "pieu",
     "daze", "lune", "urge", "yack", "suer", "lump", "race", "suie", "rama",
     "rame", "rami", "rapt", "luxa", "luxe", "rave", "rata", "rate", "indu",
     "usez", "bien", "pneu", "beer", "bebe", "bile", "bise", "pige", "exil",
     "pion", "egal", "pire", "pipe", "inca", "pise", "boxe", "idee", "inne",
     "ions", "pois", "poix", "inox", "pool", "poli", "dela", "insu", "port",
     "beta", "bete", "pope", "edam", "pene", "pouf", "pour", "poux", "bock",
     "edit", "kent", "rein", "bois", "boit", "bond", "boni", "plan", "iode",
     "boom", "bord", "iode", "bouc", "boue", "boul", "bous", "bout", "poil",
     "pond", "pont", "boxa", "boxe", "polo", "iota", "porc", "pore", "yeux",
     "plut", "dent", "demi", "bleu", "blet", "rene", "lynx", "bloc", "lyre",
     "lyse", "deux", "rala", "rale", "rend", "plat", "utah", "plot", "elle",
     "suca", "bref", "irai", "imbu", "rale", "irez", "iris", "fame", "irmx",
     "guet", "pris", "prit", "prix", "imsl", "tact", "nuit", "malt", "mare",
     "mari", "taie", "tain", "bras", "tank", "taon", "talc", "ntsc", "maux",
     "bric", "brie", "item", "brio", "brin", "bris", "broc", "brou", "taux",
     "face", "unir", "fade", "fane", "irmx", "mach", "brun", "brut", "rhum",
     "deja", "faim", "mage", "fais", "fait", "fana", "fane", "unir", "faon",
     "uucp", "pole", "fard", "fart", "mail", "main", "dine", "khan", "marc",
     "mark", "mars", "isba", "faut", "dina", "faux", "dine", "tais", "tait",
     "tant", "dery", "rien", "dime", "riez", "kilt", "math", "ture", "tard",
     "reel", "tapi", "ring", "maya", "rira", "rire", "tare", "taxi", "issu",
     "dick", "rite", "defi", "dieu", "deni", "dira", "dire", "dise", "rime",
     "king", "kilo", "dito", "reer", "kiwi", "rima", "kepi", "rime", "uree",
     "dois", "donc", "rock", "rixe", "dors", "dose", "kola", "dota", "acte",
     "rond", "roll", "dose", "gres", "ivre", "rene", "dock", "fend", "roux",
     "teck", "dodu", "mens", "ment", "deca", "doit", "abat", "feue", "dont",
     "recu", "tend", "feve", "tenu", "dort", "dosa", "abbe", "meus", "meut",
     "test", "doux", "yoga", "abus", "abri", "dote", "doue", "rose", "abus",
     "elan", "roue", "mout", "fera", "rose", "ocre", "roue", "menu", "elit",
     "elis", "elle", "obus", "mess", "male", "elue", "elut", "acre", "acre",
     "acte", "emet", "emit", "emir", "emis", "emoi", "item", "oter", "emue",
     "emut" };
#endif

int adjacent[taille_dico][taille_dico] ;
int parcouru[taille_dico] ;

struct cell_m
{
    int sommet ;
    struct cell_m * next ;
} ;

typedef struct cell_m * pile_t ;

pile_t pile = NULL ;

int provenance[taille_dico] ;
 /* les prototypes de fonctions */

int depiler(void) ;
void empiler(int) ;
void AfficherDico(void) ;
void TriBulle(void) ;
int search(char *) ;
void doublon(void) ;
int DistanceHamming(char *,char *) ;
void ConstruireAdjacent(void) ;
void AfficheAdjacent(void) ;
int ParcourGraphe(char *, char *) ;

int
main
(void)
{
    int i ;
    TriBulle() ;
   // AfficherDico();
    ConstruireAdjacent() ;
   // AfficheAdjacent() ;
    for(i=0;i<taille_dico;i++)
    {
        parcouru[i] = 0 ;
        provenance[i] = -1 ;
    }
    printf("%d\n",search("tttt"));
    printf("%d\n",search("lion")) ;
    printf("%d\n",DistanceHamming("toto","toto")) ;
    printf("%d\n",DistanceHamming("aile","aire")) ;
    printf("%d\n",DistanceHamming("aile","pire"));

   // printf("%d\n",ParcourGraphe("lion","plan")) ;
    printf("%d\n",ParcourGraphe("lion","aire")) ;
    return 0;
}

void
AfficheAdjacent
(void)
{
    int i,j ;
    for(i=0;i<taille_dico;i++)
    {
        for(j=0;j<taille_dico;j++)
          printf(" %d ",adjacent[i][j]) ;

        printf("\n") ;
    }
    return ;
}
void
AfficherDico
(void)
{
    int i ;
    for(i=0;i<taille_dico;i++)
      printf("%s\n",dico[i]) ;
    return ;
}

void
empiler
(int sommet)
{
    pile_t tmp ;
    tmp = (pile_t) malloc(sizeof(struct cell_m)) ;
    tmp->sommet = sommet ;
    tmp->next = NULL ;

    tmp->next = pile ;
    pile = tmp ;
    return ;
}

int
depiler
(void)
{
    int res ;
    pile_t tmp ;
    res = pile->sommet ;
    tmp = pile ;
    pile = pile-> next ;
    free(tmp) ;
    return res ;
}

void
TriBulle
(void)
{
    int i,j ;
    char *tmp ;
    for(i=taille_dico-1;i>0;i--)
      for(j=0;j<i;j++)
        if(strcmp(dico[j],dico[j+1])>0)
          {
              tmp=dico[j] ;
              dico[j] = dico[j+1] ;
              dico[j+1] = tmp ;
          }

    return ;
}

int
search
(char *str)
{
    int debut, fin, milieu, res ;

    debut = 0 ;
    fin = taille_dico-1 ;

    while(debut<=fin)
    {
        milieu = (debut+fin)/2 ;

        res = strcmp(dico[milieu],str) ;

        if(res==0)
            return milieu ;

        if(res<0)
            debut=milieu+1 ;
        else
            fin = milieu-1 ;
    }
    return -1 ;
}

void
doublon
(void)
{
    int i,j,doublon ;
    i=0 ;
    doublon = 0 ;
    while(i<taille_dico-1)
    {
        j=i+1 ;

        while(strcmp(dico[i],dico[j])==0)
        {
          dico[j] = "xxxx" ;
          doublon++ ;
          j++ ;
          if(j==taille_dico)
            return ;
        }
        i= j;
    }
    printf("doublon : %d\n",doublon) ;

    return ;
}

int
DistanceHamming
(char *str1, char *str2)
{
    int modif,i ;
    modif = 0 ;

    for(i=0;i<4;i++)
        modif += str1[i]-str2[i]? 1: 0;

    if(modif==0)
      return 0 ;

    if(modif==1)
      return 1 ;

    return 0 ;
}

void
ConstruireAdjacent
(void)
{
    int i,j ;

    for(i=0;i<taille_dico;i++)
    {
        adjacent[i][i]=0 ;
        for(j=i+1;j<taille_dico;j++)
        {
          adjacent[i][j] = DistanceHamming(dico[i],dico[j]) ;
           adjacent[j][i] = adjacent[i][j] ;
        }
    }
    return ;
}

int
ParcourGraphe
(char *source, char *destination)
{
    int depart,arrive,courant,i ;

    depart = search(source) ;

    if(depart==-1)
        return 0 ;

    arrive = search(destination) ;
    if(arrive==-1)
        return 0 ;

    empiler(depart) ;
    parcouru[depart] = 1 ;

    while(pile!=NULL)
    {
        courant = depiler() ;
        if(courant==arrive)
        {
            i=arrive ;
            while(provenance[i]!=-1)
            {
                printf("%s\n",dico[i]) ;
                i = provenance[i] ;
            }
                printf("%s\n",dico[depart]) ;
             return 1 ;
        }


        for(i=0;i<taille_dico;i++)
          if(adjacent[courant][i] ==1 && !parcouru[i])
          {
              empiler(i) ;
              parcouru[i] = 1 ;
              provenance[i] = courant ;
          }
    }
   return 0 ;
}







































