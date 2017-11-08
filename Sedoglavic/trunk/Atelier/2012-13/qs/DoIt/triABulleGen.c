/* lefils valentin */
void triABulleGen(void *base, int nelem, int size,int(*compar)(const void *, const void *)){

  int i,j,tmp;
  for (i=1;i<nelem;i++){
    j=i;
    while(j>0 && compar(base+j*size,base+(j-1)*size)<0){
      swap(base+j*size,base+(j-1)*size,size);
      j--;
    }
  }

}
