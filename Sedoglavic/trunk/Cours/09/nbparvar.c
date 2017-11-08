

int somme(int nbpar, ...)
{
  int *pt = &nbpar ; /* on fait pointer pt sur le premier param\`etre */
  int res = 0; 

  for(;nbpar>0;nbpar--)
    {
      pt++      ; /* On passe au param\`etre suivant */
      res += *pt ;
    }

  return res ;
}

int main(void)
{
  return somme(3,1,2,3)+somme(4,4,5,3,1) ;
}
