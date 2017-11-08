/* Fichier add.c */
static int add_local (int x, int y)
{
    return x + y;
}
int add (int x, int y)
{
    return add_local (x, y);
}
