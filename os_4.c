#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

struct counter_thread
{
	int value;
	pthread_mutex_t lock;
};
void topup(struct counter_thread *p)
{
	pthread_mutex_lock(&p->lock);
	p->value++;
	pthread_mutex_unlock(&p->lock);

}

void *the_thing(void *c)
{//printf("thread created\n");
	struct counter_thread *d=(struct counter_thread*)c;
	long long int k=0;
	while(k<1000000000)
	{
		topup(d);
		//printf("\n");
		k++;
	}
}


int main()
{
	pthread_t thready[10];
	struct counter_thread c;
	c.value=0;
	clock_t ti,t;
	double total=0;
	pthread_mutex_init(&c.lock,NULL);
	int N=2,i,j;
	while(N<=10)
	{	
//printf("check1\n");
		total=0;
		for(j=0;j<50;++j)
		{//printf("check2\n");
			c.value=0;
			pthread_mutex_init(&c.lock,NULL);
		ti=clock();
		for(i=0;i<N;++i)
		{
			pthread_create(&thready[i],NULL,the_thing,(void*)(&c));
		}
		for(i=0;i<N;++i)
		{
			pthread_join(thready[i],NULL);
		}
		t=clock();
		total=total+((double)(t-ti)/CLOCKS_PER_SEC);
		}

		double avg=total/50;
	printf("%f\n",avg );
	N++;
	}

	
	

	return 0;
}
