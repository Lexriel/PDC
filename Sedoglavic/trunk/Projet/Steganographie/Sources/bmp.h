#define NBITEMS_BMPHEADER 15
#define NBCOULEURS 3 

struct _BMPHeader{
  char         Identifier[2]   ; /* Contient toujours l'octet `B'
				    suivit de l'octet `M' */
  unsigned int FileSize        ; /* Taille totale du fichier en
				   octets */
  unsigned int Reserved        ; /* Champs r\'eserv\'e, doit \^etre
				  \'egal \`a 0 */
  unsigned int DataOffset      ; /* Nombre d'octets s\'eparant le
				  d\'ebut du fichier des donn\'ees de
				  l'image */
  unsigned int HeaderSize      ; /* Taille en octets de l'header */
  unsigned int Width           ; /* Largeur de l'image en pixels */
  unsigned int Height          ; /* Hauteur de l'image en pixels */
  short int    Planes          ; /* Nombre de plans */
  short int    BitsPerPixels   ; /* Nombre de bits n\'ecessaires pour
				   repr\'esenter un pixel */
  unsigned int Compression     ; /* Type de compression */
  unsigned int BitmapDataSize  ; /* Taille en octets des donn\'ees de
				    l'image */
  unsigned int HResolution     ; /* R\'esolution horizontale de
				    l'image en pixels par m\`etre */
  unsigned int VResolution     ; /* R\'esolution verticale de l'image
				    en pixels par m\`etre */
  unsigned int Colors          ; /* Nombre de couleurs dans l'image */
  unsigned int ImportantColors ; /* Nombre de couleurs importantes */
} ;
 
typedef struct _BMPHeader BMPHeader_t ;

typedef enum couleurs {RED, GREEN, BLUE} couleurs_t; 
