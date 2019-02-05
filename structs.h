/** \defgroup structs_N Structures
 *
 * \brief Structures.
 */

/**
 * \ingroup structs_N
 * 
 * \file Structures used by source files.
 *
 * \author qq
 *
 * \version $Revision: 0.00001 $
 *
 * \date $Date: 2018/10/04 10:24:00 $
 *
 * Contact: SapenaVentura@gmail.com
 *
 *
 */

#ifndef STRUCTS_H
#define STRUCTS_H

    /**
     * \ingroup structs_N
     * 
     * \brief Multithreading-purposed structure.
     * 
     * struct to pass as an argument to p_placing.h function 
     * Calcular_Score() for multithreading purposes.
     */
    struct argumentos {
        //! Node where the new branch will be created.
        struct node * root;
        //! Node that's going to be introduced.
        struct node * a_introducir;
        //! Memory direction of int (&int) corresponding to the assigned score
        //! for that placement.
        int * score;
    };
    
    /**
     * \ingroup structs_N
     * 
     * \brief Multithreading-purposed structure.
     * 
     * struct to pass as an argument to function limites_cluster()
     * for multithreading purposes.
     */
    struct argumentos_boundaries{
        //! Current cluster.
        char * Clusteres; 
        //! Array of all terminal nodes.
        struct node ** Terminales;
        //! Length of current index (i.e. Cluster number 27 = 2).
        int leng_ind_actual; 
        //! current cluster index.
        int indice_actual;
        //! Memory direction (&int) to where the limit will be written.
        int * limite;
        //! Direction; '+' or '-'.
        char direccion;
    };
    
    /**
     * \ingroup structs_N
     * 
     * \brief Date of adquisition of sample
     */
    struct fecha{
        char * dia;
        char * mes;
        char * ano;
        char * fecha_completa;
    };
    
    /*
     * \ingroup structs_N
     * 
     * \brief Node of tree.
     */
    struct node{
        //! Distance to the last common ancestor of taxon with the nearest taxon.
        double distancia;
        //! Distance to root
        double depth;
        float Bootstrap;
        //! Unique ID given when the tree is created.
        int ID;
        //! Child node.
        struct node *hijo;
        //! Next node (same parent as previous node).
        struct node *siguiente;
        //! Parent node.
        struct node *padre;
        //! Node name.
        char name[50];
        //! \brief Single-Nucleotide Polymorphism list associated with node.
        //! 
        //! Int "binary" list (0 or 1) indicating, for a given vcf (variant
        //! calling file) the presence or absence of these polymorphisms.
        //!
        //! 0: Absence (The given sequence is equal to ancestral sequence at that
        //! position)
        //!
        //! 1: Presence (The given sequence presents the polymorphism)
        int * SNPs;
        //! Associated sequence
        char * taxonSeq;
        //! Associated struct ::fecha
        struct fecha * fecha_node;
    };
    
    /**
     * \ingroup structs_N
     * 
     * \brief Sequence.
     */
    struct seq {
        //! Name
        char * name;
        //! Sequence
        char * sequence;
    };

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* STRUCTS_H */

