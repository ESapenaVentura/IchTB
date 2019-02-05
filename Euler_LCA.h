/** \defgroup Euler_N Euler_LCA
 *
 * \brief Functions related to tree traversion and clustering.
 */

/*
 * \file Euler_LCA
 * 
 * \ingroup Euler_N
 * 
 * \brief Funciones de Cluster meannte aplicación de LCA
 * 
 * \author qq
 * 
 * \version $Revision: 0.01 $
 *
 * Created on 1 de agosto de 2018, 11:01
 */

#ifndef EULER_LCA_H
#define EULER_LCA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "h_libs.h"
#include <unistd.h>
#include "structs.h"
#include "Archivos.h"
#include "array_treatment.h"

extern char *colors;
    
/**
* \ingroup Euler_N
* 
* 
* \brief Search for Cluster boundaries [OUTDATED]
* 
* @param[in] lots
* 
* 
*/
void boundaries_cluster(char * Clusteres, struct node ** Terminales, 
                        int indice_actual ,int * min, int * max, 
                        int cluster_actual);
/**
* \ingroup Euler_N
* 
* 
* \brief [OUTDATED]
* 
* @param[in] lots
* 
* 
*/
int Camino_Euler (struct node * root, char ** euler, double * profundidad,
                  int position);

/**
 * \ingroup Euler_N
 * 
 * 
 * \brief Create clusters by looking at Lowest Common Ancestor(LCA) of nodes
 * 
 * @param[in] Terminales     List of terminal nodes of the tree
 * 
 * @param[in] tree              Matrix of the tree, generated by Euler_N::treeFill
 * @param[in] depth             depth of nodes
 * @param[in] parents           Matrix of nodes' IDs
 * @param[in] tries_permitidas  Maximum number of tries before going to the next node to test clustering
 * @param[in] Clusters          Matrix where the clusters will be stored.
 * @param[in] Threshold         Maximum distance by which two nodes can be connected
 *                              to be considered a cluster
 * 
 * \returns   Clusters          ==@param[in] Clusters filled with the clusters
 */
struct node *** Clusters_LCA(struct node ** Terminales, struct node *** tree, 
        int * depth, int ** parents, int tries_permitidas, 
        struct node *** Clusters, double Threshold);

/**
 * \ingroup Euler_N
 * 
 * 
 * \brief Calls Rscript with script "command_line.R", to get mean, median and 
 *        standard deviation of a cluster
 * 
 * @param[in] comando   Command to call "command_line.R". Includes all pairwise distances in the cluster.
 * @param[in] mean     Pointer to float variable that stores the mean, allocated in the caller.
 * @param[in] median   Pointer to float variable that stores the median, allocated in the caller
 * @param[in] desvest   Pointer to float variable that stores the standard deviation, allocated in the caller
 * 
 */
void * Cluster_R_datos(char * comando, double * mean, double * median, double * desvest);

/**
 * \ingroup Euler_N
 * 
 * 
 * \brief Given the root of a tree, create "Tree" matrix by calling ::append_nodes() on all nodes except root.
 * 
 * @param[in] comando   Command to call "command_line.R". Includes all pairwise distances in the cluster.
 * @param[in] mean     Pointer to float variable that stores the mean, allocated in the caller.
 * @param[in] median   Pointer to float variable that stores the median, allocated in the caller
 * @param[in] desvest   Pointer to float variable that stores the standard deviation, allocated in the caller
 * 
 */
void treeFill(struct node * root, struct node *** tree);
void * clusterCrr(struct node **** cluster, struct node *** tree, 
                         int * depth, int ** parent, int Threshold,
                         struct node ** Terminales);
void * Corregir_clusters(struct node **** cluster, struct node *** tree, 
                         int * depth, int ** parent, int Threshold,
                         struct node ** Terminales);
double ** clusterStats(struct node *** cluster, struct node *** tree, 
                         int * depth, int ** parent);
void Detectar_Monofileticos(char ** Clusteres, struct node ** Terminales,
                            int * depth, int ** parent, 
                            struct node *** tree);
void dfs(int cur, int prev, struct node *** tree, int ** depth, int ** parent);
int Es_monofiletico(int ** matriz_lca, int longitud_fila, struct node *** tree);
int LCA (int u, int v, int * depth, int ** parent);
void liberarArbol(struct node * root);
void * limites_cluster(struct argumentos_boundaries * args);
struct node * Lowest_Common_Ancestor(struct node * a, struct node * b);
int leavesTree(struct node * root, struct node *** Terminales, 
                     int longitudArray);
void * Matrices_cluster(struct node ** cluster, struct node * solitario, struct node *** tree, 
                        int * depth, int ** parent, double *** m_distancias,
                        int *** m_lca);
void * Matriz_distancias(struct node ** Cluster, struct node *** tree, 
                        int ** lista_LCA, int *** matriz_distancias);
char ** Modificar_Clusteres(struct node ** Terminales, int * depth,
                            int ** parent, struct node *** tree,
                            char ** Clusteres);
void SparseMatrix(int n, int *** parent);
void * Todos_LCA_Cluster (struct node * intro, struct node ** cluster, 
                          int *** lista_LCA, int * depth, int ** parent);
void * sendToItol(char * name_archivo, char * name_itol);


    
#ifdef __cplusplus
}
#endif

#endif /* EULER_LCA_H */

