/** \defgroup array_N array_treatment
 *
 * \brief Functions related to array treatment.
 */

/*
 * \file array_treatment
 * 
 * \ingroup array_N
 * 
 * \brief Functions related to array treatment.
 * 
 * \author qq
 * 
 * \version $Revision: 0.01 $
 *
 * Created on 1 de agosto de 2018, 11:01
 */

#ifndef ARRAY_TREATMENT_H
#define ARRAY_TREATMENT_H

#include "h_libs.h"
#include "structs.h"
int emptyFl;

/**
 * \ingroup array_N
 * 
 * \brief Append nodes to matrix
 * 
 * This function appends nodes to a matrix, row based on the unique int ID of 
 * the given nodes.
 * 
 * 
 * @param root_1 parent of root_2
 * @param root_2 child node of root_1
 * @param lista  matrix where de nodes will be appended.
 * 
 */
void append_nodes(struct node * root_1, struct node * root_2, 
                  struct node *** lista);
int ConteoCaracter(char * str, char Caracter);
struct node *** delCluster(struct node **** clusters, int index);
int nodeCount(struct node * root, int acumulado);
int ID_min(int * lista_LCA);
int indice_min_ID(struct node ** lista);
void Intercambio(char ** A, char ** B);
void Intercambio_double(double * a, double* b);
void Intercambio_Nodos(struct node ** a, struct node ** b);
void Intercambio_strings(char * a, char * b);
void Intercambio_Seqs(struct seq ** a, struct seq ** b);
void * mtrxIni(void *** matriz, int filas, int columnas, char tipo);
void * meanMedianDesvest(double * sortedNumbers, double * mean, double * median,
                         double * desvest, int lenArray);
void * freeMtrx(void *** matriz, int num_filas);
int nodeListLen(struct node ** lista);
int seqStringsLen(char ** lista);
struct node ** mvAdjClusters(struct node ** clusters, int index);
int name_en_lista(char ** lista, char * name, int i);
int node_en_lista(struct node *** lista, struct node * name, int i);
void quicksort_array_double(double * args, unsigned int len);
void quicksort_array_strings(char ** Array, unsigned int len);
void quicksort_array_struct_nodes(struct node ** args, unsigned int len);
void quicksort_array_struct_seq(struct seq ** args, unsigned int len);
void quicksort_strings(char * Array, unsigned int len);

    


#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* ARRAY_TREATMENT_H */

