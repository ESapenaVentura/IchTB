/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Euler_LCA.h"

char * colors = "#E0E0E0\n#FF8000\n#8DEEEE\n#696969\n#A2CD5A\n#A9A9A9\n#C1CDCD\n"
                "#872657\n#8EE5EE\n#FFE4B5\n#A0522D\n#03A89E\n#FF34B3\n#BFEFFF\n"
                "#6B8E23\n#CD5555\n#9B30FF\n#9A5142\n#B0C4DE\n#FFDAB9\n#CDC5BF\n"
                "#8E388E\n#CD9B9B\n#B4CDCD\n#8B3E2F\n#CDC9A5\n#6959CD\n#8B1A1A\n"
                "#FF3030\n#7D9EC0\n#76EE00\n#00C957\n#EEA2AD\n#27408B\n#D1D1D1\n"
                "#00FF7F\n#00FF00\n#EE2C2C\n#FFA07A\n#708090\n#EE9572\n#7B68EE\n"
                "#FAF0E6\n#8B475D\n#EEDC82\n#FAFAD2\n#8B5A2B\n#3CB371\n#FF7F00\n"
                "#FFFF00\n#000080\n#CD3700\n#00008B\n#308014\n#00FA9A\n#F08080\n"
                "#8B7500\n#FFB6C1\n#757575\n#778899\n#8B0A50\n#68838B\n#E0EEE0\n"
                "#F0F8FF\n#EEAD0E\n#8A8A8A\n#87CEEB\n#A3A3A3\n#AB82FF\n#5F9EA0\n"
                "#FFF0F5\n#8B2500\n#A1A1A1\n#1E90FF\n#98F5FF\n#EEB4B4\n#FFEBCD\n"
                "#00868B\n#B5B5B5\n#F2F2F2\n#D8BFD8\n#EE7942\n#32CD32\n#ADD8E6\n"
                "#00C78C\n#7FFF00\n#8C8C8C\n#008B00\n#FF83FA\n#8470FF\n#ED9121\n"
                "#473C8B\n#8F8F8F\n#EEA9B8\n#FFE4C4\n#808069\n#20B2AA\n#6C7B8B\n"
                "#828282\n#919191\n#A8A8A8\n#FF8247\n#EE4000\n#B7B7B7\n#8B814C\n"
                "#00CDCD\n#79CDCD\n#FFA54F\n#4F94CD\n#EEEED1\n#00C5CD\n#00EEEE\n"
                "#FFF5EE\n#B0E2FF\n#EEAEEE\n#F8F8FF\n#D2B48C\n#EE5C42\n#B2DFEE\n"
                "#00BFFF\n#FFFFE0\n#8B1C62\n#FF8C69\n#EEE0E5\n#F4A460\n#548B54\n"
                "#FFFAF0\n#CD6600\n#7D7D7D\n#FFE1FF\n#EDEDED\n#FF7F50\n#698B22\n"
                "#CD6889\n#FF3E96\n#B8B8B8\n#68228B\n#5B5B5B\n#8B5742\n#FFDEAD\n"
                "#FF7F24\n#FFBBFF\n#CD5B45\n#388E8E\n#838B8B\n#EE7AE9\n#B4EEB4\n"
                "#8B636C\n#BDFCC9\n#CD9B1D\n#40E0D0\n#B22222\n#7A378B\n#8E8E8E\n"
                "#CFCFCF\n#00CD00\n#E066FF\n#9ACD32\n#FF7D40\n#EE6AA7\n#96CDCD\n"
                "#CDCD00\n#DAA520\n#7CFC00\n#FFD700\n#FFEFDB\n#191970\n#878787\n"
                "#0000CD\n#C1FFC1\n#8A3324\n#9C661F\n#EED5B7\n#FF69B4\n#556B2F\n"
                "#808080\n#FFEFD5\n#E6E6FA\n#DA70D6\n#9370DB\n#CD2626\n#F0FFFF\n"
                "#C4C4C4\n#FFA500\n#CDB5CD\n#FFFACD\n#CD853F\n#8A2BE2\n#33A1C9\n"
                "#54FF9F\n#8DB6CD\n#F0FFF0\n#8B3A62\n#B3EE3A\n#555555\n#B9D3EE\n"
                "#FF6347\n#CD0000\n#FFB5C5\n#EEC591\n#1874CD\n#97FFFF\n#C7C7C7\n"
                "#71C671\n#EE7600\n#C71585\n#8B4500\n#EE6A50\n#CDAA7D\n#CD00CD\n"
                "#CD950C\n#912CEE\n#4682B4\n#7F7F7F\n#CDCDB4\n#9AFF9A\n#4EEE94\n"
                "#FF0000\n#3D9140\n#9BCD9B\n#F4F4F4\n#FAEBD7\n#FFFFF0\n#6495ED\n"
                "#7CCD7C\n#CDC9C9\n#CCCCCC\n#EBEBEB\n#66CDAA\n#8B6508\n#E3A869\n"
                "#848484\n#7AC5CD\n#EEE9BF\n#4876FF\n#00E5EE\n#B0B0B0\n#76EEC6\n"
                "#EE3A8C\n#800080\n#5CACEE\n#CDBE70\n#F0F0F0\n#FF7256\n#009ACD\n"
                "#48D1CC\n#E8E8E8\n#BF3EFF\n#CAFF70\n#BBFFFF\n#EE3B3B\n#0000FF\n"
                "#5D478B\n#F0E68C\n#696969\n#CD69C9\n#838B83\n#FCE6C9\n#D9D9D9\n"
                "#FF82AB\n#FF8C00\n#DEB887\n#8B864E\n#104E8B\n#7171C6\n#EE8262\n"
                "#EE6363\n#D02090\n#CD8C95\n#7EC0EE\n#87CEFA\n#CD2990\n#6B6B6B\n"
                "#8B7355\n#CDAD00\n#8B8989\n#8B7B8B\n#EED5D2\n#F5F5F5\n#CD661D\n"
                "#00CED1\n#EE9A00\n#FFAEB9\n#98FB98\n#B8860B\n#D6D6D6\n#8B8682\n"
                "#A52A2A\n#AAAAAA\n#458B00\n#EEEE00\n#00EE00\n#CD8162\n#6E7B8B\n"
                "#A2B5CD\n#EE9A49\n#CDCDC1\n#C5C1AA\n#FFF8DC\n#EE30A7\n#B0E0E6\n"
                "#FFC1C1\n#E3E3E3\n#8B3A3A\n#BDB76B\n#00FFFF\n#EED2EE\n#1C86EE\n"
                "#D2691E\n#66CD00\n#E0EEEE\n#8B2252\n#6A5ACD\n#CDB7B5\n#EEE8CD\n"
                "#528B8B\n#6E6E6E\n#EEE5DE\n#7A7A7A\n#DEDEDE\n#CD5C5C\n#EE1289\n"
                "#BABABA\n#9C9C9C\n#458B74\n#DC143C\n#90EE90\n#F7F7F7\n#8B7D7B\n"
                "#8A360F\n#008B45\n#EEEEE0\n#36648B\n#00F5FF\n#B452CD\n#C67171\n"
                "#CDC8B1\n#A4D3EE\n#836FFF\n#D3D3D3\n#8B4789\n#8B8386\n#9F79EE\n"
                "#9400D3\n#8968CD\n#7D26CD\n#8B8B7A\n#707070\n#8B8B00\n#FFC125\n"
                "#CD1076\n#6CA6CD\n#43CD80\n#FF6103\n#CDAF95\n#00B2EE\n#9AC0CD\n"
                "#CD6090\n#CD7054\n#63B8FF\n#C9C9C9\n#FF4040\n#FF9912\n#0000EE\n"
                "#E0FFFF\n#C0FF3E\n#BCEE68\n#858585\n#EEE685\n#8B4513\n#EECBAD\n"
                "#FFFFFF\n#F5F5DC\n#8B7E66\n#CD6839\n#CD4F39\n#551A8B\n#FFC0CB\n"
                "#BCD2EE\n#EE0000\n#CDB38B\n#7A8B8B\n#CDC0B0\n#B0171F\n#2E8B57\n"
                "#FFEC8B\n#9FB6CD\n#CD3333\n#8B5F65\n#C6E2FF\n#EE7621\n#EEC900\n"
                "#FF6A6A\n#D4D4D4\n#8FBC8F\n#FF1493\n#8B008B\n#668B8B\n#CD96CD\n"
                "#8B2323\n#E5E5E5\n#8B7D6B\n#EECFA1\n#87CEFF\n#8B4726\n#999999\n"
                "#FFFAFA\n#E3CF57\n#A6A6A6\n#EE00EE\n#9E9E9E\n#EEE9E9\n#4169E1\n"
                "#FFE4E1\n#698B69\n#8B8B83\n#BFBFBF\n#3A5FCD\n#C1CDC1\n#808A87\n"
                "#FAFAFA\n#4A708B\n#CDBA96\n#607B8B\n#969696\n#FFF68F\n#F5FFFA\n"
                "#7A67EE\n#CDC673\n#8B795E\n#BA55D3\n#DDA0DD\n#EEDFCC\n#B23AEE\n"
                "#FF6EB4\n#8B668B\n#FDF5E6\n#3D59AB\n#737373\n#CDC1C5\n#CD8500\n"
                "#00EE76\n#C1C1C1\n#DB7093\n#E9967A\n#FFE7BA\n#7FFFD4\n#FFD39B\n"
                "#006400\n#BC8F8F\n#AEEEEE\n#FF00FF\n#BDBDBD\n#8B3626\n#5E2612\n"
                "#00CD66\n#F5F5F5\n#EE82EE\n#ADFF2F\n#9932CC\n#436EEE\n#53868B\n"
                "#9A32CD\n#C0C0C0\n#EEB422\n#4B0082\n#00688B\n#F5DEB3\n#ADADAD\n"
                "#8B6969\n#C2C2C2\n#8B6914\n#8B7765\n#6E8B3D\n#ABABAB\n#DCDCDC\n"
                "#008B8B\n#FA8072\n#CD919E\n#8B8878\n#8B4C39\n#EED8AE\n#B3B3B3\n"
                "#787878\n#808000\n#D15FEE\n#EE799F\n#CDB79E\n#FFB90F\n#D1EEEE\n"
                "#8B0000\n#8B8378\n#EAEAEA\n#008080\n#C76114\n#EEE8AA\n#008000\n"
                "#8E8E38\n#949494\n#228B22\n#CAE1FF\n#CD3278\n#483D8B\n#FF4500\n"
                "#800000\n#DBDBDB\n#8B5A00\n#8B8970\n";

    //FALTA POR COMPLETAR
void boundaries_cluster(char * Clusteres, struct node ** Terminales, int indice_actual ,int * min, int * max, int cluster_actual)
{
    struct argumentos_boundaries * maxi = malloc(sizeof(struct argumentos_boundaries));
    struct argumentos_boundaries * mini = malloc(sizeof(struct argumentos_boundaries));

    char leng_num_cluster[10];
    sprintf(leng_num_cluster, "%d", cluster_actual);

    maxi->Clusteres = Clusteres, mini->Clusteres = Clusteres;
    maxi->Terminales = Terminales, mini->Terminales = Terminales;
    maxi->indice_actual = indice_actual, mini->indice_actual = indice_actual;
    maxi->leng_ind_actual = strlen(leng_num_cluster), mini->leng_ind_actual = strlen(leng_num_cluster);


    maxi->limite = max;
    maxi->direccion = '+';

    mini->limite = min;
    mini->direccion = '-';

    limites_cluster(maxi);
    printf("Max = %d", *maxi->limite);
    /*
    pthread_t Threads[2];

    pthread_create(&Threads[0], NULL, (void *)limites_cluster, maxi);
    pthread_create(&Threads[1], NULL, (void *)limites_cluster, mini);

    pthread_join(Threads[0], NULL);
    pthread_join(Threads[1], NULL);*/
}

int Camino_Euler (struct node * root, char ** euler, double * profundidad, 
                  int position)
{
    if (root == NULL) return position;

    euler[position] = malloc(sizeof(struct node));
    euler[position] = root;

    profundidad[position] = root->depth;
    euler[position + 1] = NULL;
    profundidad[position +1] == -1;
    position++;

    position = Camino_Euler(root->hijo, euler, profundidad, position);
    position = Camino_Euler(root->siguiente, euler, profundidad, position);

    return position;
}

/*Función para crear los clústeres. Se le pasa una serie de parámetros:
     1- Array de punteros a los nodes terminales del árbol.
     2- Array de array de punteros a nodes, necesario para la función LCA.
     3- Array de Niveles del árbol.
     4- Matriz dispersa, indicativa de los padres. Más información en SparseMatrix.
     5- Número de reintentos (Número de veces que el programa intenta crear un
        cluster entre Terminales[i] y Terminales[j] y falla) permitidos.
     6- Array de strings donde se almacernarán los clústeres. Todos los elementos
        (Cluster[i]) están ya iniciados meannte un malloc. La memoria de almacenamiento
        de cada string se aloja dinámicamente durante la creación de los clústeres.
     7- Umbral de distancia para la creación de los clústeres.
     8- Básicamente, número con el que se alojó dinámicamente la memoria de
        Clusteres. Se le pasa al programa para, una vez terminada la función, 
        liberar la memoria de los clústeres no creados [desde cluster_index
        (último cluster creado) hasta NumeroClusters].*/
struct node *** Clusters_LCA(struct node ** Terminales, struct node *** tree, 
        int * depth, int ** parents, int tries_permitidas, struct node *** Clusters,
        double Threshold)
{
    int j, lca;
    int cluster_aparicion = -1;
    int i = 0;
    int ici = 0; //intra-cluster-index
    int cluster_index = -1; 
    int borrado_cluster = 0; //BOOL; puede tomar valor 1 o 0.
    int tries_intentadas = 0;
    int distancia_entre_nodes;
    

    while(Terminales[i] != NULL){
        if (Terminales[i]->distancia > Threshold){
            i++;
            continue;
        }
        j = i + 1;
            while(Terminales[j] != NULL){
                /*Pequeño if para acelerar los bucles*/
                if (Terminales[j]->distancia > Threshold){
                    j++;
                    tries_intentadas++;
                    if (tries_intentadas > tries_permitidas){
                            tries_intentadas = 0;
                            break;
                    }
                    continue;
                }
                cluster_aparicion = node_en_lista(Clusters, Terminales[j], cluster_index -3);

                if (cluster_aparicion == -1){
                    lca = LCA(Terminales[i]->ID, Terminales[j]->ID, depth, parents);
                    distancia_entre_nodes = Terminales[i]->depth + Terminales[j]->depth - 2 * tree[lca][1]->padre->depth;
                    if (distancia_entre_nodes <= Threshold){
                        tries_intentadas = 0;
                        cluster_aparicion = node_en_lista(Clusters, Terminales[i], cluster_index - 3);
                        if (cluster_aparicion == -1){
                            ici = 0;
                            borrado_cluster = 0;
                            cluster_index++;
                            Clusters[cluster_index] = malloc(sizeof(struct node*) * 2 + 8); //Alojamos memoria.
                            Clusters[cluster_index][ici++] = Terminales[i];
                            Clusters[cluster_index][ici++] = Terminales[j];
                            Clusters[cluster_index][ici] = NULL;
                            Clusters[cluster_index + 1] = NULL;
                        }else{
                            Clusters[cluster_aparicion] = realloc(Clusters[cluster_aparicion], sizeof(struct node*) * (ici + 2));
                            Clusters[cluster_aparicion][ici++] = Terminales[j];
                            Clusters[cluster_aparicion][ici] = NULL;
                        }
                    }else{
                        if (tries_intentadas > tries_permitidas){
                            tries_intentadas = 0;
                            break;
                        }else{
                            tries_intentadas++;
                        }
                    }
                /*Este else if pregunta si la coincidencia se da en un cluster anterior. Si esto es así,
                 y la distancia es menor al umbral, se mueve todo el cluster que se había creado a ese índice.*/
                }else if (cluster_aparicion < cluster_index){
                    lca = LCA(Terminales[i]->ID, Terminales[j]->ID, depth, parents);
                    distancia_entre_nodes = Terminales[i]->depth + Terminales[j]->depth - 2 * tree[lca][1]->padre->depth;
                    if (distancia_entre_nodes <= Threshold && borrado_cluster == 0){
                        int len_lista_A = nodeListLen(Clusters[cluster_aparicion]);

                        int len_lista_B = nodeListLen(Clusters[cluster_index]);
                        ici = len_lista_A;
                        Clusters[cluster_aparicion] = realloc(Clusters[cluster_aparicion], sizeof(struct node) * (ici + len_lista_B));
                        for (int i = 0; Clusters[cluster_index][i] != NULL; i++){
                            Clusters[cluster_aparicion][ici++] = Clusters[cluster_index][i];
                        }
                        Clusters[cluster_aparicion][ici] = NULL;
                        free(Clusters[cluster_index]);
                        Clusters[cluster_index] = NULL;
                        cluster_index--;
                        borrado_cluster = 1;
                    }else if (distancia_entre_nodes > Threshold){
                        tries_intentadas++;
                    }
                }else if (cluster_aparicion == cluster_index){
                    lca = LCA(Terminales[i]->ID, Terminales[j]->ID, depth, parents);
                    distancia_entre_nodes = Terminales[i]->depth + Terminales[j]->depth - 2 * tree[lca][1]->padre->depth;
                    if (distancia_entre_nodes <= Threshold && node_en_lista(Clusters, Terminales[i], cluster_index - 3) == -1){
                        int longitud_lista = nodeListLen(Clusters[cluster_aparicion]);
                        Clusters[cluster_aparicion] = realloc(Clusters[cluster_aparicion], sizeof(struct node*) * (longitud_lista + 10));
                        Clusters[cluster_aparicion][longitud_lista++] = Terminales[i];
                        Clusters[cluster_aparicion][longitud_lista] = NULL;
                    }
                }
                j++;
            }
        i++;
    }
    /*Liberamos memoria sobrante de los clusteres que no se han hecho*/
    Clusters = realloc(Clusters, sizeof(struct node **) * (cluster_index + 2));
    
    return Clusters;
}

void * Cluster_R_datos(char * comando, double * mean, double * median, 
                       double * desvest)
{
    FILE *fp;
    char path[300];
    
    fp = popen(comando, "r");
    if (fp == NULL){
        printf("Esto ha fallau\n");
        exit(1);
    }
    int linea = 1;
    while (fgets(path, sizeof(path)-1, fp) != NULL){
        switch(linea){
            case 1:
                *median = strtod(path, NULL);
                linea++;
                break;
            case 2:
                *mean = strtod(path, NULL);
                linea++;
                break;
            case 3:
                *desvest = strtod(path, NULL);
        }
    }
    pclose(fp);
    }

double ** clusterStats(struct node *** cluster, struct node *** tree, 
                         int * depth, int ** parent)
{
    /*COMPUTE CLUSTER NUMBER*/
    int clusterNmbr, l;
    for (clusterNmbr = 0; cluster[clusterNmbr] != NULL; clusterNmbr++)continue;
    
    /*INITIALIZE STATS MATRIX*/
    double ** mtrxStats;
    mtrxIni((void***)&mtrxStats, clusterNmbr, 3, 'd');
    
    /*FILL WITH MEAN, MEDIAN AND STD FOR EACH CLUSTER*/
    for (int i = 0; cluster[i] != NULL; i++){
        l = 0;
        int longitud_cluster = nodeListLen(cluster[i]);
        double * distancias = malloc(sizeof(double) * (longitud_cluster * 
                                    (longitud_cluster + 1)));
        for (int j = 0; j < longitud_cluster; j++){
            for (int k = j + 1; k < longitud_cluster; k++){
                int common = LCA(cluster[i][j]->ID, cluster[i][k]->ID, depth, parent);
                distancias[l++] = cluster[i][j]->depth + cluster[i][k]->depth -
                                  2 * tree[common][1]->padre->depth;
            }
        }
        quicksort_array_double(distancias, l);
        
        double mean, median, desvest;
        meanMedianDesvest(distancias, &mean, &median,
                         &desvest, longitud_cluster);
        mtrxStats[i][0] = mean;
        mtrxStats[i][1] = median;
        mtrxStats[i][2] = desvest;
        free(distancias);
    }
    
    return mtrxStats;
}


void * clusterCrr(struct node **** cluster, struct node *** tree, 
                         int * depth, int ** parent, int Threshold,
                         struct node ** Terminales)
{
    int clusApp = -1; //Cluster apparition index (pending to change name)
    double ** matriz_distancias;
    int ** matriz_lca;
    for (int i = 0; Terminales[i] != NULL; i++)
    {
        clusApp = node_en_lista((*cluster), Terminales[i], 0);
        for (int j = 0; Terminales[j] != NULL; j++)
        {
            if (i == j) continue;
            if (clusApp != -1 && node_en_lista((*cluster), Terminales[j], 0) == -1)
            {
                int longitud_cluster = nodeListLen((*cluster)[clusApp]);
                mtrxIni((void***)&matriz_distancias, longitud_cluster, longitud_cluster + 1, 'd');
                mtrxIni((void***)&matriz_lca, longitud_cluster, longitud_cluster + 1, 'i');
                
                Matrices_cluster((*cluster)[clusApp], Terminales[j], tree, depth, parent,
                                     &matriz_distancias, &matriz_lca);
                
                if (Es_monofiletico(matriz_lca, longitud_cluster, tree))
                {
                    struct node ** buff = realloc((*cluster)[clusApp], sizeof(struct node *) * (longitud_cluster + 1) + 8);
                    while(!buff)
                    {
                        printf("Error en el realojamiento de la memoria para corrección de clusteres\n");
                    }
                    (*cluster)[clusApp] = buff;
                    (*cluster)[clusApp][longitud_cluster] = Terminales[j];
                    (*cluster)[clusApp][longitud_cluster + 1] = NULL;
                }
                freeMtrx((void***)&matriz_distancias, longitud_cluster);
                freeMtrx((void***)&matriz_lca, longitud_cluster);
            }
        }
    }
}

/*CODIGO MUERTO; FUNCIONA, CORRECCIÓN DE CLUSTERES MONOFILÉTICOS
void * checkClusterMono(struct node **** cluster, struct node *** tree, 
                         int * depth, int ** parent)
{
    
    int len = nodeListLen(*cluster);
    int i, j, k;
    double ** matriz_distancias;
    int ** matriz_lca;
    i = 0;
    for (int i = 0; (*cluster)[i] != NULL; i++)
    {
        for (int j = i + 1; (*cluster)[j] != NULL; j++)
        {
            for (int k = 0; (*cluster)[j][k] != NULL; k++)
            {
                /*ESTO HAY QUE MEJORARLO SUSTANCIALMENTE; NO SE PUEDE LLAMAR
                 A LA FUNCIÓN DE CREAR LAS MATRICES TANTAS VECES
                int longitud_cluster = nodeListLen((*cluster)[i]);
                mtrxIni((void***)&matriz_distancias, longitud_cluster, longitud_cluster + 1, 'd');
                mtrxIni((void***)&matriz_lca, longitud_cluster, longitud_cluster + 1, 'i');
                Matrices_cluster((*cluster)[i], (*cluster)[j][k], tree, depth, parent,
                                     &matriz_distancias, &matriz_lca);
                if (Es_monofiletico(matriz_lca, longitud_cluster, tree))
                {
                    printf("%s\n%s\n", (*cluster)[i][0]->name, (*cluster)[j][k]->name);
                    for (int l = 0; matriz_lca[l] != NULL; l++)
                    {
                        for (int n = 0; matriz_lca[l][n] != -1; n++)
                        {
                            printf("%d ", matriz_lca[l][n]);
                            
                        }
                        printf("\n");
                    }
                    printf("Holiiii\n");
                }
                freeMtrx((void***)&matriz_distancias, longitud_cluster);
                freeMtrx((void***)&matriz_lca, longitud_cluster);
            }
           
        }
    }
}
*/

void treeFill(struct node * root, struct node *** tree)
{
    if (root == NULL)return;
    if (strcmp(root->name, "Root")){
        append_nodes (root->padre, root, tree);
    }
    treeFill(root->hijo, tree);
    treeFill(root->siguiente, tree);
    return;
}

void dfs(int cur, int prev, struct node *** tree, int ** depth, int ** parent)
{
    (*depth)[cur] = (*depth)[prev] + 1;
    parent[cur][0] = prev;
    for (int i = 0; i < nodeListLen(tree[cur]); i++){
        if (tree[cur][i]->ID != prev){
            dfs(tree[cur][i]->ID, cur, tree, depth, parent);
        }
    }
}

int Es_monofiletico(int ** matriz_lca, int longitud_fila, struct node *** tree)
{
    int rowDepth = matriz_lca[0][0];
    int colDepth = matriz_lca[0][longitud_fila - 1];
    int i, j, lca;
    for (i = 0; i < longitud_fila; i++){
        for (j = 0; matriz_lca[i][j + 1] != -1; j++){
            lca = matriz_lca[i][j];
            if (rowDepth > lca) rowDepth = lca;
        }
        lca = matriz_lca[i][j];
        if (colDepth > lca) colDepth = lca;        
    }
    if (rowDepth > colDepth || colDepth == 1){
        return 0;
    }else{
        return 1;
    }
}

/*MAGIA. FUCKING MAGIA.*/
int LCA (int u, int v, int * depth, int ** parent)
{
    if (depth[v] < depth[u]){
        int temp = u;
        u = v;
        v = temp;
    }

    int diff = depth[v] - depth[u];

    // Step 1 of the pseudocode
    for (int i=0; i<18; i++)
        if ((diff>>i)&1)
            v = parent[v][i];

    // now depth[u] == depth[v]
    if (u == v)
        return u;

    // Step 2 of the pseudocode
    for (int i=18-1; i>=0; i--){

        if (parent[u][i] != parent[v][i])
        {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

void liberarArbol(struct node * root){
    if(root == NULL)return;
    
    liberarArbol(root->siguiente);
    liberarArbol(root->hijo);
    
    free(root);
}

void * limites_cluster(struct argumentos_boundaries * args)
{
    int i;
    int leng_Cluster = strlen(args->Clusteres);
    switch(args->direccion){
        case '+':
        {
            printf("Limite = %d", *args->limite);
            fflush(stdout);
            for(i = args->indice_actual; strstr(args->Clusteres, args->Terminales[i]->name) != (const char*) &args->Clusteres + (leng_Cluster - strlen(args->Terminales[i]->name)); i++){
                printf("Holi; i = %d\n", i);
                printf("Terminales[i] = %s\n", args->Terminales[i]->name);
            }
            (*args->limite) = i - 1;
            break;
        }



        case '-':
        {
            const char * sub;
            if (args->indice_actual == 0){
                (*args->limite) = 0;
                break;
            }

            printf("Hemos llegau hasta aquí\n");
            for (i = args->indice_actual; strstr(args->Clusteres, args->Terminales[i]->name) != args->Clusteres + (args->leng_ind_actual + 1); i--){
                const char * sub;
                sub = strstr(args->Clusteres, args->Terminales[i]->name);
                if (sub != NULL){
                    printf("%s\n", sub);
                    fflush(stdout);
                }else{
                    printf("MIAU\n");
                    fflush(stdout);
                    continue;
                }
                if (i-1 == 0){
                    printf("Cero\n");
                    break;
                }
            }
            printf("Llega hasta aquí?");
            fflush(stdout);
            (*args->limite) = i + 1;
            break;

        }
    }
}

struct node * Lowest_Common_Ancestor(struct node * a, struct node * b)
{
    while(1){
        if (a->depth > b->depth){
            a = a->padre;
        }else if (a->depth < b->depth){
            b = b->padre;
        }else if (a->depth == b->depth){
            if (a->ID == b->ID){
                return a;
            }else{
                a = a->padre;
                b = b->padre;
            }
        }
    }
}

void * Matrices_cluster(struct node ** cluster, struct node * solitario, struct node *** tree, 
                        int * depth, int ** parent, double *** m_distancias, 
                        int *** m_lca)
{
    int longitud_cluster = nodeListLen(cluster);

    int i,j;
    for (i = 0; cluster[i] != NULL; i++){
        for (j = i+1; cluster[j] != NULL; j++){
            (*m_lca)[i][j-i-1] = tree[LCA(cluster[i]->ID, cluster[j]->ID, depth, parent)][1]->padre->ID;
            (*m_distancias)[i][j-i-1] = cluster[i]->depth + cluster[j]->depth - 2 * tree[(*m_lca)[i][j-i-1]][1]->padre->depth;
        }
        (*m_lca)[i][j-i-1] = tree[LCA(cluster[i]->ID, solitario->ID, depth, parent)][1]->padre->ID;
        (*m_distancias)[i][j-i-1] = cluster[i]->depth + solitario->depth - 2 * tree[(*m_lca)[i][j-i-1]][1]->padre->depth;
        (*m_lca)[i][j-i] = -1;
        (*m_distancias)[i][j - i] = -1;
    }
    (*m_distancias)[longitud_cluster] = NULL;
    (*m_lca)[longitud_cluster] = NULL;
}

    /*Terminales, en esta función, es &Terminales + posición de inicio;
     aritmética de punteros.*/
void * Matriz_distancias(struct node ** Cluster, struct node *** tree, 
                        int ** lista_LCA, int *** matriz_distancias){

    int i,j;
    for (i = 0; lista_LCA[i] != NULL; i++){
        (*matriz_distancias[i][i]) = 0;
        for (j = i+1; lista_LCA[i][j] != NULL; j++){
            (*matriz_distancias[i][j]) = Cluster[i]->depth + Cluster[j]->depth - 2*tree[lista_LCA[i][j]][1]->padre->depth;
        }
    }
}

char ** Modificar_Clusteres(struct node ** Terminales, int * depth,
                            int ** parent, struct node *** tree,
                            char ** Clusteres)
{
    int index_cluster = 0;
    int ind_lca = 0;
    int lca;
    for (int i = 0; Terminales[i]!= NULL; i++){
        if (strstr(Clusteres[index_cluster], Terminales[i]->name)){
            printf("Prueba: %s\n", strstr(Clusteres[index_cluster], Terminales[i]->name));
            continue;
        }else if(strstr(Clusteres[index_cluster + 1], Terminales[i]->name)){
            index_cluster++;
            continue;
        }else{
            int min, max;
            ind_lca = 0;
            boundaries_cluster(Clusteres[index_cluster], Terminales, i, &min, &max, index_cluster); //deteccion del primer y último índice en el cluster
            printf("Min: %d\nMax: %d\n", min, max);
            fflush(stdout);
        }
    }
}

/*Devuelve la cantidad de nodes terminales existentes*/
int leavesTree(struct node * root, struct node *** Terminales, 
                     int longitudArray)
{
    if(root == NULL)return longitudArray;

    if(strcmp(root->name, "Nodo_intermedio") && strcmp(root->name, "Root")){
        (*Terminales)[longitudArray++] = root;
        (*Terminales)[longitudArray] = NULL;
    }
    longitudArray = leavesTree(root->hijo, Terminales, longitudArray);
    longitudArray = leavesTree(root->siguiente, Terminales, longitudArray);

    return longitudArray;
}
/**
 * \brief Sends .tree file to itol
 * @param name_archivo
 * @return 
 */
void * sendToItol(char * name_temp, char * name_itol){
    FILE *fp;
    char path[300];
    int len_name_archivo = strlen(name_temp) + 5;
    char name_archivo[strlen(name_temp) + 5];
    if (name_temp[strlen(name_temp) - 1] != 'e'){
        char comando_cambio_name[strlen(name_temp) + 100];
        sprintf(comando_cambio_name, "cp %s %s.tree", name_temp, name_temp);
        fp = popen(comando_cambio_name, "w");
        if (fp == NULL){
            printf("Esto ha fallau\n");
            exit(1);
        }
        fclose(fp);
        sprintf(name_archivo, "%s", name_temp);
        strcat(name_archivo, ".tree");
    }else{
        sprintf(name_archivo, "%s", name_temp);
    }
    
    char comando_compres[strlen(name_archivo) * 2 + strlen(name_itol) + 100];
    sprintf(comando_compres, "zip -q -r %s.zip %s %s", name_archivo, name_archivo, name_itol);
    
    fp = popen(comando_compres, "w");
    if (fp == NULL){
        printf("Esto ha fallau\n");
        exit(1);
    }
    fclose(fp);
    
    
    char comando_upload[strlen(name_archivo) + 100];
    name_archivo[len_name_archivo] = '\0';
    sprintf(comando_upload, "curl -s -F \"zipFile=@%s.zip\" https://itol.embl.de/batch_uploader.cgi", name_archivo);
    char url[1000] = "https://itol.embl.de/tree/";
    fp = popen(comando_upload, "r");
        if (fp == NULL){
        printf("Esto ha fallau\n");
        exit(1);
    }
    while (fgets(path, sizeof(path)-1, fp) != NULL){
        if (path[0] == 'S'){
            strcat(url, path + 9);
            printf("URL para ITOL: %s", url);
        }else{
            printf("Fallos en la subida del árbol");
        }
            
    }
    
    fclose(fp);
    
    char comando_borrado [100];
    sprintf(comando_borrado, "rm %s.zip", name_archivo);
    fp = popen(comando_borrado, "w");
    fp = popen(comando_upload, "r");
        if (fp == NULL){
        printf("Esto ha fallau\n");
        exit(1);
    }
    fclose(fp);
    
}

void SparseMatrix(int n, int *** parent){
    for (int i = 1; i < 18; i++){ //18 es el nivel;
        for (int node = 1; node <= n; node++){
            if ((*parent)[node][i-1] != -1){
                (*parent)[node][i] = (*parent)[(*parent)[node][i-1]][i-1];
            }
        }
    }
}

    
void * Todos_LCA_Cluster (struct node * intro, struct node ** cluster, 
                          int *** lista_LCA, int * depth, int ** parent)
{
    int i,j;
    for (i = 0; cluster[i] != NULL; i++){
        for (j = i + 1; cluster[j] != NULL; j++){
            (*lista_LCA[i][j]) = LCA(cluster[j]->ID, cluster[i]->ID, depth, parent);
        }
        (*lista_LCA[i][j]) = NULL;
    }
    (*lista_LCA[i]) = NULL;
}