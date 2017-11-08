# define BUFFERSIZE 1<<20
# define CANARI 16
# define MYNULL 0
# define SIZE2BIG 1
# define WRONGFREE 2
# define MAGICNUMBER 4294967291U

struct cell_m{
  unsigned int magicnumber;
  struct cell_m *next;
  void *userspacestart;
  void *userspacestop;
};

typedef struct cell_m *liste_t;

void etendrememoire(void);
