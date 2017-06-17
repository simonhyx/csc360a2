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









typedef struct dynamic_array_struct
{
  resource_t* data;
  int capacity; /* total capacity */
  int* size; /* number of elements in vector */
} vector;

vector* v ;
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









int vector_init(vector* s, int init_capacity)
{
//
//printf("init capacity = %d",init_capacity);
//exit(1);
  
	ar = (resource_t*)erealloc(NULL, sizeof(resource_t*)*init_capacity);
	cap = init_capacity;
	//s->data = temp1;
//exit(1);
  //if (!s->data) return -1;

  //s->size = 0;
//exit(1);
 // s->capacity = init_capacity;

  return 0; /* success */
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

//exit(1);
    /*
     * Initialize the shared structures, including those used for
     * synchronization.
     */
	//pthread_cond_init();
	vector* w;
	 i = vector_init(w, 10);
	//init_resource(resource, char *);
	pthread_mutex_init(&key, NULL);

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
   printf("NOTHING IMPLEMENTED YET FOR join_meetup\n");
	printf("at line 136 count = %d\n mode = %d",count, mode);
	pthread_mutex_lock(&key);
	count = count +1;
	printf("at line 138 count = %d\n mode = %d", count, mode);
	if (count < SizeofHips){
		int mygen = generation;
		while(mygen == generation){
			pthread_cond_wait(&m, &key);
		}
		resource_t* word = ar;
		word = word + mygen;
exit(1);
		if (mode == 1 && count == 1){ // if in meet first mode store the code word for the first person
			// check if the generation number is greater than the size of the vector 
			// if yes, re-size
			if (mygen + 1 > cap){
				int k = 2 * cap;
				ar = realloc(ar,k * sizeof(resource_t));
			}  // resize complete, then must check if realloc is successful. 
			write_resource(word, value, strlen(value));
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
			write_resource(word, value, strlen(value));
		}
		char * temp = word-> value;
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










