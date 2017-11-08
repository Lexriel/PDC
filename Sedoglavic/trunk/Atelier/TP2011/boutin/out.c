#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<pthread.h>
#include<stdlib.h>

/* un peu de commentaire pour voir */ 
/* et oui pour voir */

unsigned long long nb ;unsigned int nbproc ;pthread_t *threads ;struct data_m 
{
		unsigned long long start ;	unsigned long long end ;	unsigned int current_thread_nb ;
}
 ;typedef struct data_m data_t ;void *searchdivisor(void * data)
{
		unsigned long long i ;	unsigned int j ;	
	/* indicates that a cancellation request is acted immediately */
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL) ;	for(i=((data_t*) data)->start;	     i<((data_t *) data)->end; i++)		if (!(nb % i))		
	{
					printf(" %llu est un diviseur de %llu \n",i,nb) ;			for(j=0;j<nbproc;j++) 				if(j!=((data_t *) data)->current_thread_nb)					if (!pthread_cancel(threads[j])) 						printf("Incorrect cancellation");					return NULL;		
	}
		return NULL ;
}
intmain(void)
{
		unsigned long long sqrt_nb ;	unsigned long long tmp ;        int result ;	int i ;		data_t *data ;				nb = 4611686138686472687ULL ;	nbproc = sysconf(_SC_NPROCESSORS_ONLN) ;	printf("%d computing unit available\n",nbproc) ;	threads = (pthread_t *) malloc(nbproc*sizeof(pthread_t)) ;	data = (data_t *) malloc(nbproc*sizeof(data_t)); 	sqrt_nb = sqrt(nb) ; 	tmp = sqrt_nb / nbproc ;	for(i=0;i<nbproc;i++) 	 
	{
				data[i].start = 2+i*tmp ;		data[i].end = data[i].start + tmp ;		data[i].current_thread_nb = i ;		pthread_create(&threads[i],NULL,searchdivisor,				(void *) &data[i]) ;	 
	}
				for(i=0;i<nbproc;i++)		pthread_join(threads[i],NULL) ;        return 0 ;	
}
