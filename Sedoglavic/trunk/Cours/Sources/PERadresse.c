                                 
void PER(int *alpha, int *beta){ 
       int tmp = *alpha ;        
       *alpha  = *beta ;         
       *beta   = tmp  ;          
}                                
                                 
int main(){                      
                                 
        int a = 1 ;              
        int b = 1 ;              
        PER(&a,&b) ;             
        return 0;                
}                                
                                 
