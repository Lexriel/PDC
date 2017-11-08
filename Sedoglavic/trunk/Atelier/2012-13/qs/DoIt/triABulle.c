/* lefils valentin */
void triAbulle(int tab[], int tabsize){

  int i,cpt,tmp;
  for (i=1;i<tabsize;++i){
    cpt=i;
    while(cpt>=0 && tab[cpt]<tab[cpt-1]){
      tmp=tab[cpt-1];
      tab[cpt-1]=tab[cpt];
      tab[cpt]=tmp;
      cpt--;
    }
  }
}
