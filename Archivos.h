/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Archivos.h
 * Author: qq
 *
 * Created on 10 de septiembre de 2018, 19:21
 */

#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "h_libs.h"
    extern int verboseG;
void storeArrayInt(int * matriz, char * name_archivo, int columns);
void storeMtrxInt(int ** matriz, char * name_archivo, int rows,
                         int columns);
void copyFileToSource(char * abs_file);
int longestLine(FILE * fp);
char * Convertir_arbol_newick(struct node * root, char * arbol);
char ** fastaRead(char * filename);
char ** LecturaMultiFas(char * contenido_alineamiento);
int * readIntArray(char * name_archivo, int columns);
int ** readIntMtrx(char * name_archivo, int rows, int columns);
char * ReadFile(char * filename);
/**
 * \ingroup Cluster_N
 * 
 * \brief Create output for ITOL webtool.
 * 
 * Function to write output for Interactive Tree Of Life webtool. 
 * @param Clusters 
 * @param name_output Pointer to string containing the name.
 */
void Output_ITol(char *Clusters, char *name_output);
void Print_Clusteres(struct node *** Clusteres, char * name_archivo, const char * metodo,
                     double ** matriz_stats);
void Print_ITOL(struct node *** Clusteres, char * name_ITOL);
void printPopupITOL(char * filename, char * file_uniq_SNP);
void print_SNPs(FILE ** fp, struct node * root, char * SNP, 
                unsigned long int * position, int len_max_dig);
void * printStr(char * filename, char * str);
void * writeExtendedTree(FILE ** fp, struct node * root);


#ifdef __cplusplus
}
#endif

#endif /* ARCHIVOS_H */

