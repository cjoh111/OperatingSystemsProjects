// Compile with gcc -pthread -lm <source.c> -o <executable>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
   // TO DO: What arguments do you need to send to each thread?
    int row_a;
    int col_a;
    
    int row_b;
    int col_b;
} instruction_t;

void *cell_multiply(void *);
void read_matrix(FILE *f, int[10][10], int *, int *);
void print_matrix(char *, int[10][10], int, int);

int matrix_a[10][10];
int matrix_b[10][10];
int matrix_c[10][10];

int main(int argc, char *argv[]) {
    printf("Multi-threaded Matrix Multiplication - ACO 350 - Cole Johnson\n");
   FILE *f = NULL;
   int row_a, col_a;
   int row_b, col_b;

   if (argc != 2) {
      fprintf(stderr,"usage: %s <file>\n", argv[0]);
      return 1;
   }

   f = fopen(argv[1], "r");
   if (f == NULL) {
      fprintf(stderr, "Can't open file %s\n", argv[1]);
      return -1;
   }

   read_matrix(f, matrix_a, &row_a, &col_a);
   read_matrix(f, matrix_b, &row_b, &col_b);

   print_matrix("A", matrix_a, row_a, col_a);
   print_matrix("B", matrix_b, row_b, col_b);

   if (col_a != row_b) {
      fprintf(stderr, "Error: Columns in A (%d) must equal rows in B (%d)\n", col_a, row_b);
      return 2;
   }
    
    //value first used for thread creation for-loop
    int num_threads = row_a * col_b;

   pthread_t tids[num_threads]; //array of threadIDs
   pthread_attr_t attr; //creation of attribute set

   pthread_attr_init(&attr); //initialize attribute set

   // TO DO: Create the threads.
    for(int i = 0; i < row_a; i++) {
        for(int j = 0; j < col_b; j++) {
            instruction_t *inst = (instruction_t *)(malloc(sizeof(instruction_t)));
            
            inst->row_a = i;
            inst->col_a = col_a;
            
            inst->col_b = j;
            
            pthread_create(&tids[i * col_b + j], &attr, cell_multiply, inst); //why not i*j?
        }
    }

   // TO DO: wait for all the threads to complete.
    for(int i=0; i<num_threads; i++) {
        pthread_join(tids[i], NULL);
    }

   print_matrix("A x B = C", matrix_c, row_a, col_b);
}

void *cell_multiply(void *param) {
   // TO DO: Perform the assigned part of the multiply.
    instruction_t *inst = (instruction_t *)param;
    
    int row_a = inst->row_a;
    int col_a = inst->col_a;
    
    int col_b = inst->col_b;
    
    matrix_c[row_a][col_b] = 0;
    
    for(int i=0; i < col_a; i++){
        matrix_c[row_a][col_b] += matrix_a[row_a][i] * matrix_b[i][col_b];
    }
    pthread_exit(NULL);
}

void print_matrix(char *title, int m[10][10], int row_cnt, int col_cnt) {
   printf("%s [%dx%d]:\n", title, row_cnt, col_cnt);
   int max = 0;
   for(int r = 0; r < row_cnt; r++) {
      for (int c = 0; c < col_cnt; c++) {
        max = max < m[r][c] ? m[r][c] : max; 
      }
   }

   int size = (int)(log10((double)max)+1);
   char format[10];
   sprintf(format, "%%%dd ", size);

   for(int r = 0; r < row_cnt; r++) {
      printf("   ");
      for (int c = 0; c < col_cnt; c++) {
         printf(format, m[r][c]);
      };
      printf("\n");
   }
   printf("\n");
}

void read_matrix(FILE *f, int m[10][10], int *row_cnt, int *col_cnt) {
   fscanf(f, "%d %d", row_cnt, col_cnt);
   for (int r = 0; r < *row_cnt; r++) {
      for (int c = 0; c < *col_cnt; c++) {
         fscanf(f, "%d", &(m[r][c]));
      }
   }
}
