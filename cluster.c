/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cluster.h"

void depthAdjustment(struct node * root){
    if (root == NULL)return;
    if(!strcmp(root->name, "Root")){
        root->depth = 0.0;
    }else{
        root->depth = root->distancia + root->padre->depth;
    }
    
    depthAdjustment(root->siguiente);
    depthAdjustment(root->hijo);
    
}

void dstAdjust(struct node * root, double multiplicador){
    if (root == NULL)return;
    
    root->depth *= multiplicador;
    
    
    dstAdjust(root->siguiente, multiplicador);
    dstAdjust(root->hijo, multiplicador);
}

/*Crea un árbol a partir del archivo .nwk; acepta filogenias solo sin bootstrap.
 *      IMPORTANTE: NO ACEPTA FILOGENIAS SIN DISTANCIAS ( (A,B),(C,D); )
 *----------------------------------------------------------------------------*/
struct node* createTree(char *contenido_newick){
    int ID = 1; //IDENTIFICADOR ÚNICO PARA CADA NODO DEL ÁRBOL.
    double distancia;
    char* name;
    float Bootstrap = 0.0;
    regex_t regex;
    int maxgrupos = 4; //Nuestro regex devuelve siempre 4 grupos (0, 1, 2 y 3)
    regmatch_t match[maxgrupos];
    unsigned int maxmatches = UINT_MAX; //Número exagerado; no sabemos cuantas serán. Como es un máximo, tampoco influye mucho (Ni siquiera en memoria).
    int n;  // Índices para la regex
    int m;  //
    char *cursor = contenido_newick;
    /*Hasta aquí, todo va para la expresión regular y su parseo*/
    struct node *root = NuevoNodo(0.0, Bootstrap, "Root", NULL, ID);
    
    ID++;
    int i; //Para parsear el 3er grupo de los matches, que corresponde con las "acciones"
    
    
    /* EXPRESIÓN REGULAR PARA IR PARSEANDO EL ARCHIVO NWK;
     * Captura 3 grupos:
     *          -Grupo 1: Instrucciones previas de movimiento (",();")
     *          -Grupo 2: name del node O bootstrap (La regexp está preparada para ello, el programa no)
     *          -Grupo 3: Distancia
     * (El grupo 0 es la captura completa)
     */
    
    regcomp(&regex, "([,();]*)([^:]*):([0-9]+\\.*[0-9]*){1}", REG_EXTENDED);
    for (m = 0; m < maxmatches; m++){
        if (regexec(&regex, cursor, maxgrupos, match, 0))break;
        unsigned int offset = 0;  //Lo emplearemos para parsear la expresión regular
        char *acciones; //empleado para almacenar como crear el arbol
        //Bootstrap = 0.0; //Ponemos el valor de Bootstrap a 0 
        for (n = 0; n < maxgrupos; n++){
                if (match[n].rm_so == (size_t) - 1)break;
                if (n == 0){
                    offset = match[n].rm_eo;
                    continue;
                }
                char cursorcopia[strlen(cursor) + 1];
                strcpy(cursorcopia, cursor);
                cursorcopia[match[n].rm_eo] = 0;
                char *substr = strdup(cursorcopia + match[n].rm_so); //Creamos substring con el grupo del match
                /*Para cada n (grupo capturado), se copia el substr a su variable
                 *Correspondiente.*/
                if (n == 1){
                    acciones = strdup(substr);
                    free(substr);
                }
                else if (n == 2){
                    if (strlen(substr) > 0){
                        if (Es_name(substr)){
                            name = strdup(substr);
                        }else{
                            Bootstrap = atof(substr);
                        }
                        free(substr);
                    }
                    
                }else if(n == 3){
                    distancia = atof(substr);
                    free(substr);
                    if (strlen(acciones) == 0){
                        root->hijo = NuevoNodo(distancia, Bootstrap, 
                                     name, root, ID);
                        ID++;
                        root = root->hijo;
                    }
                    /*Si n = 3, se procede a la creación del node/hoja*/
                    for (i = 0; i < strlen(acciones); i++){
                        if (acciones[i] == '('){
                            if (i == strlen(acciones) - 1){
                                root->hijo = NuevoNodo(distancia, 0.0, 
                                             name, root, ID);
                                free(name);
                                ID++;
                                root = root->hijo;
                            }else{
                                root->hijo = NuevoNodo(0.0, Bootstrap,
                                             "Nodo_intermedio", root, ID);
                                ID++;
                                root = root->hijo;
                            }
                        }
                        if (acciones[i] == ',' && (strlen(acciones) - 1) != i){
                         
                            root->siguiente = NuevoNodo(0.0, Bootstrap, 
                                              "Nodo_intermedio", root->padre, ID);
                            ID++;
                            root = root->siguiente;
                        }
                        if (acciones[i] == ',' && (strlen(acciones) - 1) == i){
                            root->siguiente = NuevoNodo(distancia, Bootstrap,
                                              name, root->padre, ID);
                            free(name);
                            ID++;
                            root = root->siguiente;
                        }
                        if (acciones[i] == ')'){
                            root = root->padre;
                            root->distancia = distancia;
                            root->Bootstrap = Bootstrap;
                            
                        }
                    }
                    free(acciones);
                }
                
        }
        cursor += offset;
        fflush(stdout);
    }
    /*Una vez creado, se vuelve a Root, se libera la expresión regular
     *y se devuelve el árbol.*/
    while(root->padre != NULL){
        root = root->padre;
    }
    regfree(&regex);
    return root;
    
}

int Es_name(char *s){
    int i,length;
    length = (strlen(s));

    for (i=0;i<length;i++){
        if(s[i] >= 65){
            return 1;
        }
    }
    return 0;
}

struct node* NuevoNodo(double distancia, float Boot, char namenode[], struct node *padre, int ID){
    
    //Alojamos memoria para el nuevo node
    struct node *node = malloc(sizeof(struct node));
    
    //Le damos la distancia entre los nodes
    
    node->distancia = distancia;
    
    //Le damos el name al node
    strcpy(node->name, namenode);
    
    //Iniciamos los hijos (Y sus names) como NULL
    node->padre = padre;
    node->hijo = NULL;
    node->siguiente = NULL;
    
    // Iniciamos la profundidad y el bootstrap.
    node->depth = 0.0;
    node->Bootstrap = Boot;
    node->ID = ID;
    
    // Terminamos iniciando la sequence a NULL; no nos hace falta si no se va a
    // realizar phylogenetic placement.
    node->taxonSeq = NULL;
    node->SNPs = NULL;
    node->fecha_node = NULL;
    
    return node;
}

void RecorridoAMano(struct node * root){
    int recorrido = 9;
    while (recorrido != 0){
        printf("0-Salir\n1-Hijo\n2-Siguiente\n3-Padre\n");
        scanf("%d", &recorrido);
        if (recorrido == 0)return;
        if (recorrido == 1)root = root->hijo;
        if (recorrido == 2)root = root->siguiente;
        if (recorrido == 3)root = root->padre;
        if (root == NULL){
            printf("Hemos llegado a un NULL. Volviendo a padre\n");
            root = root->padre;
        }else{
            printf("name = %s\nDistancia = %f\n", root->name,root->distancia);
        }
    }
    return;
}


