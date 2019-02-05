/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   p_placing.h
 * Author: qq
 *
 * Created on 16 de agosto de 2018, 10:06
 */

#ifndef P_PLACING_H
#define P_PLACING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "h_libs.h"
#include "Euler_LCA.h"
#include "Cluster.h"
#include "structs.h"



void Anadir_node(struct node * root, struct node * a_introducir);
void Ajustar_SNPs_NodosIntermedios (struct node * root, int len_SNPs, char * SNPs);
void Asignar_sequence_nodes (struct seq ** seq_sorted, 
                              struct node ** terminales_sorted);
void SNPAssignment (struct node ** lista_nodes, char * SNP, 
                   unsigned long int * position);
void * CalcularScore(struct argumentos * args);
void Comparar_SNPs (struct node * node, char * SNP, 
                    unsigned long int * position);
double Distancia_aproximada(struct node * a, struct node * b);
void Lectura_SNPS (char * filename_SNPs, unsigned long int ** position_SNPs, char ** Cambio_SNPs);
struct seq * newSeq(char * name, char * sequence);
struct argumentos * NuevoArgumento(struct node * root, struct node * comp, 
                                   int * dir_score);
//struct node * Score_arbol (struct node * root, struct node * a_introducir);

struct seq * newSeq(char * name, char * sequence)
{
    struct seq * Seq = malloc(sizeof (struct seq));

    Seq->name = strdup(name);
    Seq->sequence = strdup(sequence);

    return Seq;
}
    
    /*Lectura y almacenamiento de los SNPs y su posición genómica*/
    void Lectura_SNPS (char * filename_SNP, unsigned long int ** position_SNPs, char ** Cambio_SNPs){
        char * contenido = ReadFile(filename_SNP);
        int hFlag = 0;  //Header flag
        if (!strncmp(contenido, "Chrom\tPosition", 14))
        {
            hFlag = 1;
        }
        FILE * fp = fopen(filename_SNP, "r");
        long unsigned int i = 0;
        int Lineas = ConteoCaracter(contenido, '\n') + 2;
        *position_SNPs = malloc (sizeof(unsigned long int) * Lineas);
        *Cambio_SNPs = malloc(sizeof(char) * Lineas * 2 + 1);
        (*Cambio_SNPs)[0] = '\0';
        int indice = 0;
        char line[3000];
        char buff_cambio[100];
        char buff_position[100];
        while (fgets(line,sizeof(line), fp) != NULL){
            if (hFlag)
            {
                hFlag = 0;
                continue;
            }
            int contador_whtspc = 0;
            memset(buff_cambio, '\0', 100);
            int ind_cambio = 0;
            memset(buff_position, '\0', 100);
            int ind_pos = 0;
            for (int i = 0; line[i] != '\0'; i++){
                if (isspace(line[i])){
                    contador_whtspc++;
                    for (i = i; isspace(line[i + 1]); i++)continue;
                }else{
                    if (contador_whtspc == 1){
                        for (i = i; !isspace(line[i + 1]); i++){
                            buff_position[ind_pos++] = line[i];
                        }
                        buff_position[ind_pos++] = line[i];
                        buff_position[ind_pos++] = '\0';
                        (*position_SNPs)[indice] = atof(buff_position);
                    }else if (contador_whtspc == 2 || contador_whtspc == 3){
                        for (i = i; !isspace(line[i + 1]); i++){
                            buff_cambio[ind_cambio++] = line[i];
                        }
                        buff_cambio[ind_cambio++] = line[i];
                        buff_cambio[ind_cambio] = '\0';
                    }else if (contador_whtspc > 3){
                        strcat((*Cambio_SNPs), buff_cambio);
                        break;
                    }
                }
            }
            indice++;
        }
        fflush(stdout);
        free(contenido);
        fclose(fp);
        (*Cambio_SNPs)[indice * 2] = '\0';
        (*position_SNPs)[indice] = -1;
        
        return;
    }
    
    void Comparar_SNPs (struct node * node, char * SNP, unsigned long int * position){
        int len_seq = strlen(node->taxonSeq);
        /*if (!strcmp(node->name, "MZ194.snp")){
            printf("HOLA%d\n", len_seq);
            free(node->SNPs);
        }*/
        node->SNPs = malloc(sizeof (int) * (len_seq + 1));
        int i;
        for (i = 0; i < len_seq; i++){
            if (node->taxonSeq[i] == SNP[i * 2]){
                node->SNPs[i] = 0;
            }else{
                node->SNPs[i] = 1;
            }
        }
        
        node->SNPs[i] = 2;
        return;
    }
    
    void freeSNP(struct node * root)
    {
        if (root == NULL) return;
        if (strcmp(root->name, "Root"))
        {
            free(root->SNPs);
        }
        freeSNP(root->siguiente);
        freeSNP(root->hijo);
    }
    
    void SNPAssignment (struct node ** lista_nodes, char * SNP, 
                       unsigned long int * position){
        for (int i = 0; lista_nodes[i] != NULL; i++){
            Comparar_SNPs(lista_nodes[i], SNP, position);
        }
        return;
    }
    
    void Ajustar_SNPs_NodosIntermedios (struct node * root, int len_SNPs, char * SNPs){
        
        if (root == NULL)return;
        Ajustar_SNPs_NodosIntermedios (root->hijo, len_SNPs, SNPs);
        Ajustar_SNPs_NodosIntermedios (root->siguiente, len_SNPs, SNPs);
        
        if(!strcmp(root->name, "Root")){
            int i;
            root->SNPs = malloc(sizeof(int) * len_SNPs + 8);
            for (i = 0; i < len_SNPs; i++){
                root->SNPs[i] = 0;
            }
            root->SNPs[i] = 2;
            return;
        }
        /*Si es un node intermedio, con el apartado SNP vacío, se procede.*/
        if (!strcmp(root->name, "Nodo_intermedio") && root->SNPs == NULL){
            root->SNPs = malloc(sizeof(int) * (len_SNPs + 1));
            root->taxonSeq = malloc(sizeof(char) * (len_SNPs + 1));
            for (int i = 0; i < len_SNPs; i++){
                if (root->hijo->SNPs[i] == root->hijo->siguiente->SNPs[i]){
                    root->taxonSeq[i] = root->hijo->taxonSeq[i];
                    root->SNPs[i] = root->hijo->SNPs[i];
                }else{
                    if (root->hijo->SNPs[i] == 0 || root->hijo->siguiente->SNPs[i] == 0){
                        root->SNPs[i] = 0;
                        root->taxonSeq[i] = SNPs[i * 2];
                    }else{
                        if (root->hijo->taxonSeq[i] == SNPs[i * 2 + 1] || root->hijo->siguiente->taxonSeq[i] == SNPs[i * 2 + 1]){
                            root->taxonSeq[i] = SNPs[i * 2 + 1];
                        }else{
                            /*Both secuences are not hugely represented, so we rand int to determine which one we put*/
                            int random = rand() % 2;
                            if (random == 0){
                                root->taxonSeq[i] = root->hijo->taxonSeq[i];
                            }else{
                                root->taxonSeq[i] = root->hijo->siguiente->taxonSeq[i];
                            }
                        }
                        root->SNPs[i] = 1;
                    }
                    
                }
            }
            root->taxonSeq[len_SNPs] = '\0';
            root->SNPs[len_SNPs] = 2;
        }
    }
    
    void * CalcularScore(struct argumentos * args){
        for(int i = 0; args->root->SNPs[i] < 2; i++){
            if(args->root->SNPs[i] == args->a_introducir->SNPs[i]){
                (*args->score)+= args->root->SNPs[i];
            }else{
                (*args->score)-= args->root->SNPs[i];
            }
        }
    }
    
    /* Nuevo argumento para "CalculaScore". Tiene de componentes el node "root"
     * (Raíz de lo que le hayas pasado), el node a introducir, y un puntero a
     * la posición de memoria de la variable donde se guarda la puntuación
     *  de ese node                                                           */
    struct argumentos * NuevoArgumento(struct node * root, struct node * comp, int * dir_score){
        struct argumentos * argumento = malloc(sizeof(struct argumentos));
        argumento->root = root;
        argumento->a_introducir = comp;
        argumento->score = dir_score;
        *argumento->score = 0;
        return argumento;
    }
    
    
    /* Búsqueda del score más alto en un árbol, con respecto a un node de interés
     * que añadir. Función:
     * Loop while, con la condición de que finaliza si se ha llegado a un node
     * terminal. Sigue los siguientes pasos:
     * 
     *      1-Se crea una lista de la estructura "argumentos", que se pasa
     *        a la función "CalcularScore". Esta lista contiene todos los hijos
     *        de root en cada ciclo, así como el node a introducir y la dirección
     *        de memoria donde se almacena el score de cada hijo.
     *      
     *      2-Se crean tantos threads como hijos haya.
     * 
     *      3-Compara los scores. Si se alcanza un máximo (Es decir, aunque
     *        no sea un node terminal, ambos hijos tienen un score inferior al
     *        del node actualmente "seleccionado") se detiene el loop. De lo
     *        contrario, éste seguirá hasta encontrarse un node terminal.
     * 
     *      4-Devuelve el puntero al node del árbol de referencia donde se 
     *        debería introducir la sequence
     */
    /*struct node * Score_arbol (struct node * root, struct node * a_introducir){
        
        int winner = 0; //Score máxima de las obtenidas en el anterior ciclo
        int winner_temporal = 0;
        struct node * win_temp;
        
        while (root->hijo != NULL){
            struct node * tmp = root->hijo;
            int Num_hijos = 1;
            while (tmp->siguiente !=  NULL){
                Num_hijos++;
                tmp = tmp->siguiente;
            }
            
            pthread_t Threads[Num_hijos];
            int Score[Num_hijos];
            struct argumentos ** lista_args = malloc(sizeof(struct argumentos *) * (Num_hijos + 1));
            for (int i = 0; i < Num_hijos; i++){
                struct node * temporal = root->hijo;
                for (int j = 0; j < i; j++)temporal = temporal->siguiente;
                lista_args[i] =  NuevoArgumento(temporal, a_introducir, &Score[i]);
            }
            
            for (int i = 0; i < Num_hijos; i++){
                pthread_create(&Threads[i], NULL, (void*)CalcularScore, lista_args[i]);
            }
            
            for (int i = 0; i < Num_hijos; i++){
                pthread_join(Threads[i], NULL);
            }
            for (int i = 0; i < Num_hijos; i++)printf("Score[%d]: %d\n", i, Score[i]);
            fflush(stdout);
            int Maximo_alcanzado = 0;
            for (int i = 0; i < Num_hijos; i++){
                if (winner <= Score[i])break;
                if (i == Num_hijos - 1)Maximo_alcanzado = 1;
            }
            if (Maximo_alcanzado)break;
            
            root = root->hijo;
            int i, j;
            for (i = 1; i < Num_hijos; i++){
                for (j = i; j < Num_hijos; j++){
                    if (Score[i - 1] >= Score[j]){
                        winner = Score[i - 1];
                    }else{
                        winner = Score[j];
                        root = root->siguiente;
                        break;
                    }
                }
                if (j == Num_hijos)break;
            
            }
            
            
            for (int i = 0; i < Num_hijos; i++){
                free(lista_args[i]);
            }
            free(lista_args);
        }
        //for(int i = 0; root->SNPs[i] != 2; i++)printf("%d", root->SNPs[i]);
        //printf("%s", root->hijo->hijo->hijo->hijo->hijo->hijo->hijo->hijo->hijo->hijo->name);
        printf("name: %s\n", root->name);
        Anadir_node(root, a_introducir);
        return root;
    }*/
    
    /*Añade un node al árbol, calculando una distancia aproximada basada en los
      SNPs diferentes entre ambos nodes*/
    void Anadir_node (struct node * root, struct node * a_introducir){
        root->padre = NuevoNodo(root->distancia,0.0, "Nodo_intermedio", root->padre, -1);
        root->distancia = 0.0;
        root->padre->hijo = root;
        root->padre->siguiente = root->siguiente;
        root->siguiente = a_introducir;
        root->siguiente->distancia = Distancia_aproximada (root->siguiente, root);
        
    }
    
    /*Cálculo de la distancia aproximada de la distancia (diferencias) entre dos
      nodes. Se coge el número de diferencias en SNPs y dividimos entre 2. Esta
      distancia nos sirve para, aproximadamente, predecir si un taxón podría ser
      parte de un clúster de transmisión*/
    double Distancia_aproximada (struct node * a, struct node * b){
        double distancia;
        for (int i = 0; a->SNPs[i] < 2; i++){
            if (a->SNPs[i] != b->SNPs[i])distancia++;
        }
        return distancia/2;
    }
    
    /*Dadas 2 listas, de sequences y de nodes terminales del árbol de referencia,
      ORDENADAS POR name (Se entiende que las sequences a introducir tienen
      el mismo name que los taxones del árbol), asigna a cada node su sequence
      correspondiente*/
    void Asignar_sequence_nodes (struct seq ** seq_sorted, struct node ** terminales_sorted){
        for (int i = 0; terminales_sorted[i] != NULL; i++){
            terminales_sorted[i]->taxonSeq = strdup(seq_sorted[i]->sequence);
        }
        return;
    }
    
    
    

#ifdef __cplusplus
}
#endif

#endif /* P_PLACING_H */

