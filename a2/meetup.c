/*Required Headers*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include "meetup.h"
#include "resource.h"

/*
 * Declarations for barrier shared variables -- plus concurrency-control
 * variables -- must START here.
 */

pthread_mutex_t key;
pthread_cond_t m;

int SizeofHips;
int generation;
int count;
int mode;






resource_t* ar;
int cap;






void *erealloc(void *ptr ,size_t n){
	void *p; 
	p = realloc(ptr,n);
	if (p==NULL){
		fprintf(stderr, "realloc failed, out of memory");
		exit(1);
	}
	return p;
}


void *emalloc(size_t n){
	void *p; 
	p = malloc(n);
	if (p==NULL){
		fprintf(stderr, "malloc failed, out of memory");
		exit(1);
	}
	return p;
}










//recource_t * resource;

void initialize_meetup(int n, int mf) {
    char label[100];
    int i;

    if (n < 1) {
        fprintf(stderr, "Who are you kidding?\n");
        fprintf(stderr, "A meetup size of %d??\n", n);
        exit(1);
    }


        ar = (resource_t*)erealloc(NULL, sizeof(resource_t*)*10);
        cap = 10;


	pthread_mutex_init(&key, NULL);
	int ret = pthread_cond_init(&m,NULL);
	SizeofHips = n;
	if (mf == 0){
		mode =0;
		// meet first
	}else if(mf==1){
		mode = 1;
		//meet last
	}else {
		fprintf(stderr, "meet option error");
		exit(1);
	}
}


void join_meetup(char *value, int len) {
 //  printf("NOTHING IMPLEMENTED YET FOR join_meetup\n");
	printf("\nat line 136 count = %d\n mode = %d",count, mode);
	pthread_mutex_lock(&key);
	count = count +1;
	printf("\nat line 138 count = %d\n mode = %d", count, mode);
	if (count < SizeofHips){
		int mygen = generation;
		resource_t* word = ar;
		word = word + mygen;
//xit(1);
		if (mode == 1 && count == 1){ // if in meet first mode store the code word for the first person
			// check if the generation number is greater than the size of the vector 
			// if yes, re-size

			if (mygen + 1 > cap){
				int k = 2 * cap;
				ar = realloc(ar,k * sizeof(resource_t));
			}  // resize complete, then must check if realloc is successful. 
printf("\non line 157 writing value = %s\n", value);
			write_resource(word, value, strlen(value));
		}





		while(mygen == generation){
			pthread_cond_wait(&m, &key);
		}

		// read word
		// for both meet first and meet last ?
		// read the word corresponding to your generation only
		
		char * temp = word-> value;
		printf("temp = %s\n value = %s\n", temp,value);
		read_resource(word, value,strlen(temp));
		if (word->num_reads == SizeofHips){ // once the final read is issued free the variable
			//free(word);
		}
		
	}else{


		resource_t* word= ar;
		word = word + generation;

		if (mode == 0){ // if in meet last mode store the code word for the first person
			// check if the generation number is greater than the size of the vector 
			// if yes, re-size
			if (generation + 1 > cap){
				int k = 2 * cap;
				ar = realloc(ar,k * sizeof(resource_t));
			}  // resize complete, then must check if realloc is successful. 
			printf("\nLine 184 writing value = %s\n",value);
			write_resource(word, value, strlen(value));
			
		}
		char * temp = word-> value;
printf("on line 185 temp = %s\n, value = %s\n",temp ,value);
		read_resource(word, value,strlen(temp));
		if (word->num_reads == SizeofHips){ // once the final read is issued free the variable
			//free(word);
		}


		count = 0;
		generation++;
		pthread_cond_broadcast(&m);

	}

	pthread_mutex_unlock(&key);




}










