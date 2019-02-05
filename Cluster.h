/** \defgroup Cluster_N Clusters
 *
 * \brief Clustering-related functions.
 */

/*
 * \file Cluster
 * 
 * \ingroup Cluster_N
 * 
 * \brief Funciones de Cluster
 * 
 * \author qq
 * 
 * \version $Revision: 0.01 $
 *
 * Created on 7 de mayo de 2018, 10:45
 */

#ifndef CLUSTER_H
#define CLUSTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "h_libs.h"
#include <regex.h>
    
/**
 * \ingroup Cluster_N
 * 
 * 
 * \brief Adjust root depth for posterior analysis.
 * 
 * @param[in] root
 * 
 * \brief Tree root.
 * 
 * 
 */
void depthAdjustment(struct node * root);
/**
 * \ingroup Cluster_N
 * 
 * \brief Create tree from .nwk file
 * 
 * 
 * \param contenido_newick Contents of .nwk file
 *
 * \return Root of the newly-generated tree.
 * 
 * \note Ended in ';'. 
 * No-distance trees (i.e. (A,B)C) are not allowed.
 */
struct node* createTree(char *contenido_newick);
/**
 * \ingroup Cluster_N
 * 
 * \brief Determine presence of non-numeric characters in string.
 * 
 * This function determines if a given string is a name (not a number) by
 * detecting ascii characters outside of 0-9 range (>=65)
 * @param s pointer to a string
 * @return 1 if char >= 65 is found; 0 otherwise.
 */
int Es_name(char *s);
/**
 * \ingroup Cluster_N
 * 
 * \brief Create new node.
 * 
 * Function to allocate memory and create a new node, giving the basic values to
 * the newly created node. For a description of the parameters, see ::node
 * @param distancia
 * @param Boot
 * @param namenode
 * @param padre
 * @param ID
 * @return Created node
 */
struct node* NuevoNodo(double distancia, float Boot, char namenode[], struct node *padre, int ID);
/**
 * \ingroup Cluster_N
 * 
 * \brief Debugging tool for manual traversion of tree.
 * @param root Node from where you want to begin the traversion.
 */
void RecorridoAMano(struct node * root);

/**
 * \ingroup Cluster_N
 * 
 * \brief Branch lenght adjustment for clustering-related purposes
 * 
 * 
 * @param root Root node for the tree
 * @param multiplicador Multiplier to adjust the distance
 */
void dstAdjust(struct node * root, double multiplicador);


#ifdef __cplusplus
}
#endif

#endif /* CLUSTER_H */

