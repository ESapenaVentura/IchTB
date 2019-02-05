/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "array_treatment.h"

void append_nodes (struct node * root_1, struct node * root_2, struct node *** lista)
{
    int a = root_1->ID;
    int b = root_2->ID;

    int i;

    i = nodeListLen(lista[a]);

    lista[a][i] = root_2;
    lista[a][i+1] = NULL;

    i = nodeListLen(lista[b]);

    lista[b][i] = root_1;
    lista[b][i+1] = NULL;
}

void * mtrxIni(void *** matriz, int filas, int longitud_filas, char tipo)
{
    switch(tipo){
        case 'd':
            (*matriz) = malloc(sizeof(double*) * (filas + 1));
            for (int i = 0; i < filas; i++){
                (*matriz)[i] = malloc(sizeof(double) * longitud_filas);
            }
            (*matriz)[filas] = NULL;
            break;
        case 'i':
            (*matriz) = malloc(sizeof(int*) * (filas + 1));
            for (int i = 0; i < filas; i++){
                (*matriz)[i] = malloc(sizeof(int) * longitud_filas);
            }
            (*matriz)[filas] = NULL;
            break;
        case 'n':
            (*matriz) = malloc(sizeof(struct node**) * (filas + 1));
            for (int i = 0; i < filas; i++){
                (*matriz)[i] = malloc(sizeof(struct node*) * longitud_filas + 1);
            }
            (*matriz)[filas] = NULL;
    }
}

int ConteoCaracter (char * str, char Caracter)
{
    char c;
    int i = 0;
    int conteo = 0;
    c = str[i];
    while (c != '\0'){
        if (c == Caracter) conteo++;
        i++;
        c = str[i];
    }
    return conteo;
}

int nodeCount (struct node * root, int acumulado)
{
    if (root == NULL)return acumulado;

    acumulado = nodeCount(root->hijo, acumulado);
    acumulado = nodeCount(root->siguiente,acumulado);

    acumulado++;
    return acumulado;

}

int ID_min (int * lista_LCA){

    int menor;
    for (int i = 0; lista_LCA[i] != NULL; i++){
        if (lista_LCA[i] < menor){
            menor = lista_LCA[i];
        }
    }
    return menor;
}

int indice_min_ID(struct node ** lista){
    int ID = INT_MAX;
    int indice;
    for(int i = 0; lista[i] != NULL; i++){
        if (lista[i]->ID < ID){
            ID = lista[i]->ID;
            indice = i;
        }
    }
    return indice;
}

/*Intercambio de punteros a strings*/
void Intercambio(char ** a, char ** b) 
{
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}

void Intercambio_double(double * a, double* b){
    double *tmp = a;
    *a = *b;
    *b = *tmp;
}

void Intercambio_Nodos(struct node ** a, struct node ** b)
{
    struct node *tmp = *a;
    *a = *b;
    *b = tmp;
}

void Intercambio_Seqs(struct seq ** a, struct seq ** b)
{
    struct seq * tmp = *a;
    *a = *b;
    *b = tmp;
}

void Intercambio_strings(char * a, char * b)
{
    char *tmp = *a;
    *a = *b;
    *b = tmp;
}

void * freeMtrx(void *** matriz, int num_filas)
{
        int i;
        for (i = 0; i < num_filas; i++)free((*matriz)[i]);
        free((*matriz)[i]);
        free(*matriz);

}

int nodeListLen(struct node ** lista)
{
    int i;
    for (i = 0; lista[i] != NULL; i++){
        continue;
    }
    return i;
}

int seqStringsLen(char ** lista){
    int i;
    for (i = 0; lista[i] != NULL; i++){
        continue;
    }
    return i;
}

struct node ** mvAdjClusters(struct node ** clusters, int index){
    int len_cluster = nodeListLen(clusters);
    clusters[index] = NULL;
    struct node ** buff = malloc(sizeof(struct node *) * (len_cluster - 1) + 8);
    int j = 0;
    for(int i = 0; i < len_cluster; i++){
        if(clusters[i] != NULL){
            printf("Clus: %s\n", clusters[i]->name);
            buff[j++] = clusters[i];
        }
    }
    buff[j] = NULL;
    if (len_cluster - 1 == 0)emptyFl = 1;
    return buff;
}

struct node *** delCluster(struct node **** clusters, int index){
    int len_cluster = nodeListLen((*clusters));
    (*clusters)[index] = NULL;
    if (index != len_cluster -1){
        for (int i = index; i < len_cluster; i++){
            (*clusters)[i] = (*clusters)[i + 1];
            (*clusters)[i + 1] = NULL;
        }
    }
    struct node *** buff = realloc((*clusters), sizeof(struct node **) * (len_cluster - 1) + 8);
    if(!buff){
        printf("Error en el realojamiento de memoria para el cluster");
    }
    (*clusters) = buff;
    emptyFl = 0; //Set empty flag to 0 again
    return *clusters;
}

int node_en_lista (struct node *** lista, struct node * name, int i)
{
    int Substr_en_str = -1;
    if (i < 0) i = 0;
    if (lista[i] == NULL)return Substr_en_str;

    for(i = i; lista[i] != NULL; i++){
        for (int j = 0; lista[i][j] != NULL; j++){
           if (lista[i][j] == name){
               return i;
        }
        }

    }
    return Substr_en_str;
}

/*Si existe el substring, devuelve el índice en la lista. Si no, devuelve -1*/
int name_en_lista(char ** lista, char * name, int i){
    int Substr_en_str = -1;
    if (i < 0) i = 0;
    if (lista[0] == NULL)return Substr_en_str;

    for(i = i; lista[i] != NULL; i++){
        fflush(stdout);
        if (strstr(lista[i], name)){
            Substr_en_str = i;
            break;
        }
    }
    return Substr_en_str;
}

void * meanMedianDesvest(double * sortedNumbers, double * mean, double * median,
                         double * desvest, int lenArray)
{
    if (lenArray == 2)
    {
        *mean = sortedNumbers[0];
        *median = sortedNumbers[0];
        *desvest = 0;
        return;
    }
    
    /*MEAN*/
    for (int i = 0; i < lenArray; i++){
        *mean += sortedNumbers[i];
    }
    *mean /= lenArray;
    
    /*STD*/
    double provStd[lenArray];
    for (int i = 0; i < lenArray; i++){
        provStd[i] = pow(sortedNumbers[i] - *mean, 2);
        *desvest += provStd[i];
    }
    *desvest /= lenArray;
    *desvest = sqrt(*desvest);
    
    /*median*/
    if (lenArray % 2 == 0)
    {
        *median = (sortedNumbers[lenArray / 2] + sortedNumbers[lenArray / 2 - 1]) / 2.0;
    }else
    {
        *median = sortedNumbers[lenArray/2];
    }
}

void quicksort_array_double(double * args, unsigned int len)
{
    unsigned int i, pvt = 0;

    if (len <= 1)return;

    Intercambio_double(&(args + ((unsigned int)rand() % len))[0], &(args + len - 1)[0]);

    for(i = 0; i < len - 1; i++){
        if (args[i] < args[len-1]){
            Intercambio_double(&(args + i)[0], &(args + pvt++)[0]);
        }
    }
    Intercambio_double(&(args+pvt)[0], &(args+len-1)[0]);

    quicksort_array_double(args, pvt++);
    quicksort_array_double((args + pvt), (len - pvt));
}

/* Método sweep (Preguntar qué es exactamente eso) para realizar quicksort.
 * Para aclararme yo también, escribiré paso por paso lo que hace:
 *      1-Designa un pivote al azar (aritmética de punteros), que se
 *        convierte en el último elemento del array.
 *      2-Bucle for: de 0 hasta len -1.
 *          2.1-Si args[i] es menor al último elemento del array, se
 *              intercambian.
 *          2.2-En cada uno de estos casos, pvt (pivote) incrementa en uno.
 *      3-Intercambio entre el nuevo pivote y el último elemento del array.
 *      4-LLamada recursiva con la parte derecha e izquierda de la particion.
 */
void quicksort_array_strings(char ** args, unsigned int len)
{
    unsigned int i, pvt = 0;

    if (len <= 1)return;

    Intercambio(&(args+((unsigned int)rand() % len))[0], &(args+len-1)[0]);

    for(i = 0; i < len-1; ++i){
            if(strcmp(args[i], args[len-1]) < 0){
                Intercambio(&(args+i)[0], &(args+pvt++)[0]);
            }
    }
    Intercambio(&(args+pvt)[0], &(args+len-1)[0]);

    quicksort_array_strings(args, pvt++);
    quicksort_array_strings((args+pvt), len - pvt);

}

void quicksort_strings(char * args, unsigned int len)
{
    unsigned int i, pvt = 0;

    if (len <= 1)return;

    Intercambio_strings(&(args + ((unsigned int)rand() % len))[0], &(args + len - 1)[0]);

    for(i = 0; i < len - 1; i++){
        if (args[i] < args[len-1]){
            Intercambio_strings(&(args + i)[0], &(args + pvt++)[0]);
        }
    }
    Intercambio_strings(&(args+pvt)[0], &(args+len-1)[0]);

    quicksort_strings(args, pvt++);
    quicksort_strings((args + pvt), (len - pvt));
}

void quicksort_array_struct_nodes(struct node ** args, unsigned int len)
{
    unsigned int i, pvt = 0;

    if (len <= 1)return;

    Intercambio_Nodos(&(args+((unsigned int)rand() % len))[0], &(args+len-1)[0]);

    for(i = 0; i < len - 1; i++){
        if(strcmp(args[i]->name, args[len-1]->name) < 0){
                Intercambio_Nodos(&(args+i)[0], &(args+pvt++)[0]);
        }
    }
    Intercambio_Nodos(&(args+pvt)[0], &(args+len-1)[0]);

    quicksort_array_struct_nodes(args, pvt++);
    quicksort_array_struct_nodes((args + pvt), (len - pvt));
}

void quicksort_array_struct_seq(struct seq ** args, unsigned int len)
{
    unsigned int i, pvt = 0;

    if (len <= 1)return;

    Intercambio_Seqs(&(args+((unsigned int)rand() % len))[0], &(args+len-1)[0]);

    for(i = 0; i < len - 1; i++){
        if(strcmp(args[i]->name, args[len-1]->name) < 0){
                Intercambio_Seqs(&(args+i)[0], &(args+pvt++)[0]);

        }
    }
    Intercambio_Seqs(&(args+pvt)[0], &(args+len-1)[0]);

    quicksort_array_struct_seq(args, pvt++);
    quicksort_array_struct_seq((args + pvt), (len - pvt));
}


