#define N 100
int
main(void)
{
#ifdef N
	printf("N vaut %d\n", N);
#else
	printf("N n'est pas defini\n");
#endif
}
