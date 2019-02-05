/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Archivos.h"
#include "Euler_LCA.h"
extern int verboseG, numNodes;
int actNode = 1;

void storeArrayInt(int * matriz, char * name_archivo, int columns)
{
    FILE *file = fopen(name_archivo, "w");
    fclose(file);
    file = fopen(name_archivo, "w+");
    for (int j = 0; j < columns; j++){
        fprintf(file, "%d ", matriz[j]);
    }
    fclose(file);
}
    

void storeMtrxInt(int ** matriz, char * name_archivo, int rows, int columns){
        FILE *file = fopen(name_archivo, "w");
        fclose(file);
        file = fopen(name_archivo, "w+");
        
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                fprintf(file, "%d ", matriz[i][j]);
            }
            fputc('\n', file);
        }
        fclose(file);
    }

int longestLine(FILE * fp){
    char line[10000];
    int max_winner = 0, max_temporal = 0;
    while (fgets(line, sizeof(line) - 1, fp) != NULL){
        int len_linea = strlen(line);
        max_temporal += len_linea;
        if (line[len_linea - 1] == '\n'){
            if(max_temporal > max_winner) max_winner = max_temporal;
            max_temporal = 0;
        }
    }
    rewind(fp);
    return max_winner;
}

char * Convertir_arbol_newick(struct node * root, char * arbol){
    if (root == NULL)return arbol;
 
    
    if (strcmp(root->name, "Nodo_intermedio") == 0 || strcmp(root->name, "Root") == 0){
        strncat(arbol, "(", 1);
    }else{
        strcat(arbol, root->name);
        char temp[50];
        sprintf(temp, ":%f", root->distancia);
        strcat(arbol, temp);
        if (root->siguiente != NULL)strncat(arbol, ",", 1);
    }
    Convertir_arbol_newick(root->hijo, arbol);
    
    if (strcmp(root->name, "Nodo_intermedio") == 0 || strcmp(root->name, "Root") == 0){
        char temp[50];
        sprintf(temp, "):%f", root->distancia);
        strcat(arbol, temp);
        if (root->siguiente != NULL)strncat(arbol, ",", 1);
    }
    
    Convertir_arbol_newick(root->siguiente, arbol);

    if (strcmp(root->name, "Nodo_intermedio") != 0 || strcmp(root->name, "Root") != 0){
        if (root->siguiente != NULL)strncat(arbol, ")", 1);
    }
    return arbol;
}

void copyFileToSource(char * abs_file)
{
    if (access(abs_file, F_OK) == -1)return;
    char commBuff[1000] = {'\0'};
    sprintf(commBuff, "cp %s %s", abs_file, strrchr(abs_file, '/') + 1);
    
    FILE * fp = popen(commBuff, "w");
    if(!fp)printf("Failed moving phylogeny to source location...\n");
    pclose(fp);
    
}

char ** fastaRead(char * filename){
    FILE * fp = fopen(filename, "r");
    
    /*FIND LONGEST LINE AND CREATE CHAR ARRAY WITH THAT SIZE*/
    int maxLine = longestLine(fp) + 2;
    char line[maxLine];
    
    /*INITIALIZE STRING MATRIX*/
    char ** fasta_list = malloc(sizeof(char*));
    
    /*INDEX FOR STRING MATRIX*/
    int i = -1;
    
    while (fgets(line, sizeof(line) - 1, fp) != NULL){
        line[strlen(line) - 1] = '\0'; // Delete newline char
        if (line[0] == '>'){
            i++;
            char ** buff;
            while(!(buff = realloc(fasta_list, sizeof(char*) * (i + 3))))continue;
            fasta_list = buff;
            fasta_list[i++] = strdup(line + 1); //Delete '>' from name
            fasta_list[i] = malloc(sizeof(char));
            fasta_list[i][0] = '\0';
        }else{
            if (strlen(fasta_list[i]) == 0){
                free(fasta_list[i]);
                fasta_list[i] = strdup(line);
            }else{
                char * buff;
                while (!(buff = realloc(fasta_list[i], sizeof(char) * (strlen(fasta_list[i]) + strlen(line) + 2))))continue;
                
                fasta_list[i] = buff;
                strcat(fasta_list[i], line);
            }
        }
        memset(line, '\0', sizeof(char) * maxLine);
    }
    fasta_list[i + 1] = NULL;
    rewind(fp);
    fclose(fp);
    return fasta_list;
}

char ** LecturaMultiFas(char * contenido) {

    int Retorno_de_Carros = ConteoCaracter(contenido, '\n');
    int longitud_contenido = strlen(contenido);
    int i = 0;
    char * name;
    char * sequence;
    int j = -1;
    int k = 0;
    char ** lista_de_sequences = malloc(sizeof (char*) * (Retorno_de_Carros + 10));
    lista_de_sequences[0] = malloc(sizeof (char) * longitud_contenido);

    while (contenido[i] != '\0') {
        if (contenido[i] == '>') {
            j++;
            i++;
            lista_de_sequences[j] = malloc(sizeof (char) * longitud_contenido);
            while (contenido[i] != '\n') {
                lista_de_sequences[j][k] = contenido[i];
                i++;
                k++;
            }
            lista_de_sequences[j][k] = '\0';
            k = 0;
            lista_de_sequences[j] = realloc(lista_de_sequences[j], sizeof(char) * strlen(lista_de_sequences[j]));
            j++;
            lista_de_sequences[j] = NULL;
        }else{
            lista_de_sequences[j] = malloc(sizeof (char) * longitud_contenido);
            while (contenido[i] != '>' && contenido[i] != '\0') {
                if (contenido[i] == '\n') {
                    i++;
                    continue;
                }
                lista_de_sequences[j][k] = contenido[i];
                i++;
                k++;
            }
            lista_de_sequences[j][k] = '\0';
            k = 0;
            lista_de_sequences[j] = realloc(lista_de_sequences[j], strlen(lista_de_sequences[j]));
        }
    }
    lista_de_sequences[++j] = NULL;
    return lista_de_sequences;
}

int * readIntArray(char * name_archivo, int columns)
{
    /*Inicializamos depth*/
    int * depth = malloc(sizeof(int*) * columns);

    char * treeFileCnt = ReadFile(name_archivo);
    char c = treeFileCnt[0];
    char str[12];
    int j = 0;          //Índices para la lectura de la matriz
    int IndexNumero = 0;

    for (int i = 0; c != '\0'; i++){
        if (c != ' '){
            str[IndexNumero] = c;
            IndexNumero++;
            str[IndexNumero] = '\0';
        }else if (c == ' '){
            sscanf(str, "%d", &depth[j]);
            j++;
            IndexNumero = 0;
        }
        c = treeFileCnt[i + 1];
    }
    free(treeFileCnt);
    return depth;
}

int ** readIntMtrx(char * name_archivo, int rows, int columns){
        /*Inicializamos parent*/
        int ** parent = malloc(sizeof(int**) * rows);
        for (int i = 0; i<rows; i++){
            parent[i] = malloc(sizeof(int*) * columns);
        }
        
        char * treeFileCnt = ReadFile(name_archivo);
        char c = treeFileCnt[0];
        char str[12];
        int j = 0;          //Índices para la lectura de la matriz
        int k = 0;          //
        int IndexNumero = 0;
        
        for (int i = 0; c != '\0'; i++){
            if (c != '\n' && c != ' '){
                str[IndexNumero] = c;
                IndexNumero++;
                str[IndexNumero] = '\0';
            }else if (c == ' '){
                sscanf(str, "%d", &parent[j][k]);
                //parent[j][k] = atoi(str);
                k++;
                IndexNumero = 0;
            }else if (c == '\n'){
                k = 0;
                j++;
            }
            c = treeFileCnt[i + 1];
        }
        free(treeFileCnt);
        return parent;
    }

void Output_ITol(char *Clusters, char *name_output){
    char *Colores = malloc(sizeof(char) * 4065); //Colores en Hexadecimal
    if ( access("500ColoresHexShuff.txt", F_OK) != -1){
        Colores = ReadFile("500ColoresHexShuff.txt");
        FILE *file = fopen(name_output, "w"); //Crea y destruye contenido del archivo
        fclose(file);                        //Pendiente de cambio.
        file = fopen(name_output, "w+");
        int IndexColores = 0;               //Indice para saber en qué color estamos
        int IndexColor = 0;                 //Indice para meter caracteres del color
        int IndexClusteres = 0;
        int NumeroCluster = 0;
        int boolean = 0;
        /*No necesito la variable Input, colo es comodidad. Acordarse de 
         *preguntar si borrarla*/
        /*Comienza el código para crear el output. Primero, creamos el archivo
         'base', que será siempre el mismo, de momento.*/
        fprintf(file,"TREE_COLORS\nSEPARATOR COMMA\nDATA\n");
        char input = Clusters[IndexClusteres];
        /*Hasta que no nos encontremos con el final del string, irá escribiendo
         clusteres en el archivo.*/
        while (input != '\0'){
            if (input == '\n' && boolean == 0){ //Primer elemento
                NumeroCluster++;
                boolean = 1;
            }else if (input != '\n'){           //Introduce las hojas caracter a caracter
                if (Clusters[IndexClusteres -1] == '\n' && boolean > 1)fputc('|', file);
                boolean = 2;                    //Indicamos que hay más de un elemento en el cluster
                fputc(input, file);
            }else if (input == '\n' && (Clusters[IndexClusteres -1] == '\n' && boolean > 1) || Clusters[IndexClusteres + 1] == '\0'){
                char *Color = malloc(sizeof(char) * 8); //Almacenamiento dinámico del color.
                while(Colores[IndexColores] != '\n'){
                    Color[IndexColor++] = Colores[IndexColores++];
                }
                Color[IndexColor] = '\0';
                IndexColor = 0;
                IndexColores++;
                if (IndexColores > 4060)IndexColores = 0; //Solo tenemos 508 colores
                /*A partir de aquí, se escribe toda la información complementaria:
                 -Es un rango (iTOL lo trata así)
                 -Color en hexadecimal
                 -name del Cluster (De momento, se ha optado por un número)*/
                fprintf(file,",range,%s,Cluster Numero %d\n", Color, NumeroCluster);
                free(Color);
                boolean = 0;
            }
            IndexClusteres++;
            input = Clusters[IndexClusteres];
        }
    }else{
        free(Colores);
        printf("No existe el archivo de colores en hexadecimal. Saliendo");
    }
}

void Print_Clusteres(struct node *** Clusteres, char * name_archivo, const char * metodo,
                     double ** matriz_stats)
{
        FILE *file = fopen(name_archivo, "w");
        fclose(file);
        file = fopen(name_archivo, "w+");
        int i = 0;
        
        char * header = "Cluster Number;Taxa;Mean;median;Standard Deviation\n";
        fwrite(header, sizeof(char), strlen(header), file);
        while(Clusteres[i] != NULL){
            if (!strcmp(metodo, "senyorito_irving"))
            {
            
                char buff_dig[15];
                sprintf(buff_dig, "%d;", i+1);
                for (int j = 0; Clusteres[i][j] != NULL; j++){
                    fwrite(buff_dig, sizeof(char), strlen(buff_dig), file);
                    fwrite(Clusteres[i][j]->name, sizeof(char), strlen(Clusteres[i][j]->name), file);
                    char buff_stats[100];
                    sprintf(buff_stats, ";%f;%f;%f", matriz_stats[i][0], matriz_stats[i][1], matriz_stats[i][2]);
                    fwrite(buff_stats, sizeof(char), strlen(buff_stats), file);
                    if(Clusteres[i][j+1] != NULL)fputc('\n', file);
                }
            }else
            {
                char buff_dig[15];
                sprintf(buff_dig, "%d;", i+1);
                fwrite(buff_dig, sizeof(char), strlen(buff_dig), file);
                for (int j = 0; Clusteres[i][j] != NULL; j++){
                    fwrite(Clusteres[i][j]->name, sizeof(char), strlen(Clusteres[i][j]->name), file);
                    if (Clusteres[i][j+1] != NULL)fputc(',', file);
                }
                char buff_stats[100];
                sprintf(buff_stats, ";%f;%f;%f", matriz_stats[i][0], matriz_stats[i][1], matriz_stats[i][2]);
                fwrite(buff_stats, sizeof(char), strlen(buff_stats), file);
            }
            if (Clusteres[++i] != NULL)fputc('\n', file);
        }
        fclose(file);
    }

void Print_ITOL(struct node *** Clusteres, char * name_ITOL){
        FILE *file = fopen(name_ITOL, "w");
        fclose(file);
        file = fopen(name_ITOL, "w+");
        int i = 0;
        char c;
        int j, Final, IndexColores = 0, IndexColor = 0,  Excepcion = 10;
        int j_inicio = 2;
        int exponente = 1;
        char *Color;
        char * Buffer = malloc(sizeof(char) * 40);
        fprintf(file,"TREE_COLORS\nSEPARATOR COMMA\nDATA\n");
            
        while(Clusteres[i] != NULL){
            /*INTRODUCIMOS EL COLOR DE LOS CLUSTERES*/
            Color = malloc(sizeof(char) * 8); //Almacenamiento dinámico del color.
            while(colors[IndexColores] != '\n'){
                Color[IndexColor++] = colors[IndexColores++];
            }
            Color[IndexColor] = '\0';
            IndexColor = 0;
            IndexColores++;
            if (IndexColores > 4060)IndexColores = 0; //Solo tenemos 508 colores

            for (int j = 0; Clusteres[i][j] != NULL; j++){
                fwrite(Clusteres[i][j]->name, sizeof(char), strlen(Clusteres[i][j]->name), file);
                sprintf(Buffer, ",range,%s,Cluster numero %d\n", Color, i+1);
                fwrite(Buffer, sizeof(char), strlen(Buffer), file);
                free(Buffer);
                Buffer = malloc(sizeof(char) * 40);
            }
            free(Color);
            i++;
        }
        free(Buffer);
        fclose(file);
    }

void printPopupITOL(char * filename, char * file_uniq_SNP){
    FILE * fp = fopen(file_uniq_SNP, "r");
    FILE * nf = fopen(filename, "w+");
    fclose(nf);
    nf = fopen(filename, "a");
    char first_rows_archive[] = "POPUP_INFO\nSEPARATOR TAB\nDATA\n";
    fwrite("POPUP_INFO\nSEPARATOR TAB\nDATA\n", sizeof(char), strlen(first_rows_archive), nf);
    const char * colors[2];
    colors[0] = "LightCyan";
    colors[1] = "PaleTurquoise";
    char line[longestLine(fp) + 10];
    char buf_write[BUFSIZ] = {'\0'};
    int len_buf = 0;
    while(fgets(line, sizeof(line) - 1, fp) != NULL){
        if (ConteoCaracter(line, ';') == 0)continue;
        char * name;
        name = strtok(line, ";");
        if (len_buf + strlen(name) >= BUFSIZ){
            fwrite(buf_write, sizeof(char), len_buf, nf);
            memset(buf_write, '\0', BUFSIZ); //set buffer bytes to NULL
            len_buf = 0;
        }
        strcpy(buf_write + len_buf, name);
        len_buf = strlen(buf_write);
        buf_write[len_buf++] = '\t';
        sprintf(buf_write + len_buf, "%s: ", name);
        len_buf = strlen(buf_write);
        if (len_buf + 381 >= BUFSIZ){
            fwrite(buf_write, sizeof(char), len_buf, nf);
            memset(buf_write, '\0', BUFSIZ); //set buffer bytes to NULL
            len_buf = 0;
        }
        char beg_html[] = "SNPs Unicos\t<html><body><table cellspacing=\"0\" cellpadding=\"0\" border=\"1\" width=\"325\"><tr><td><table cellspacing=\"0\" cellpadding=\"1\" border=\"1\" width=\"300\"><tr style=\"color:white;background-color:grey\"><th>Position</th><th>SNP</th></tr></table></td></tr><tr><td><div style=\"width:320px; height:150px; overflow:auto;\"><table cellspacing=\"0\" cellpadding=\"1\" border=\"1\" width=\"300\">";
        strcpy(buf_write + len_buf, beg_html);
        len_buf += strlen(beg_html);
        
        int contadorSNP = 0;
        char * token;
        while((token = strtok(NULL, ";")) != NULL){
            if (len_buf + 145 >= BUFSIZ){
                fwrite(buf_write, sizeof(char), len_buf, nf);
                memset(buf_write, '\0', BUFSIZ); //set buffer bytes to NULL
                len_buf = 0;
            }
            sprintf(buf_write + len_buf, "<tr><tr style=\"color:black;background-color:%s\"><td>", colors[contadorSNP % 2]);
            contadorSNP++;
            len_buf = strlen(buf_write);
            
            int i;
            for (i = 0;isdigit(token[i]); i++){
                buf_write[len_buf++] = token[i];
            }
            sprintf(buf_write + len_buf, "</td><td>%c -> %c</td></tr>", token[i], token[i + 2]);
            len_buf = strlen(buf_write);
            
        }
        
        if (len_buf + 40 >= BUFSIZ){
            fwrite(buf_write, sizeof(char), len_buf, nf);
            memset(buf_write, '\0', BUFSIZ); //set buffer bytes to NULL
            len_buf = 0;
        }
        
        strcpy(buf_write + len_buf, "</table></body></html>\n");
        len_buf = strlen(buf_write);
    }
    if (len_buf > 0)fwrite(buf_write, sizeof(char), len_buf, nf);
    fclose(fp);
    fclose(nf);
}

void print_SNPs(FILE ** fp, struct node * root, char * SNP, 
                unsigned long int * position, int len_max_dig)
{
    if (root == NULL)return;
    print_SNPs(fp, root->siguiente, SNP, position, len_max_dig);
    print_SNPs(fp, root->hijo, SNP, position, len_max_dig);
    
    if (!strcmp(root->name, "Root"))
    {
        if (verboseG == 1)
        {
            char buf[255];
            sprintf(buf, "%d - %d", actNode++, numNodes);
            printf("Nodo número: %s\n", buf);
        }
        return;
    }
    char buff[BUFSIZ] = {'\0'};
    int len_buff = 0;
    if(verboseG == 1)
    {
        char buf[255];
        sprintf(buf, "%d - %d", actNode++, numNodes);
        printf("Nodo número: %s", buf);
        fflush(stdout);
        for (int i = 0; i < strlen(buf) + 13; i++)
        {
            printf("\b");
        }
        fflush(stdout);
    }
    if (strcmp("Nodo_intermedio", root->name)){
        strcpy(buff, root->name);
    }else{
        char identifier[255];
        sprintf(identifier, "INT%d", root->ID);
        strcpy(buff, identifier);
    }
    len_buff = strlen(buff);
    
    for (int j = 0; j < strlen(root->taxonSeq); j++){
            if (root->SNPs[j] == 1 && root->SNPs[j] != root->padre->SNPs[j]){
                if (root->taxonSeq[j] != '-'){
                    sprintf(buff + len_buff, ";%lu%c>%c", 
                            position[j], SNP[j * 2], root->taxonSeq[j]);
                    len_buff = strlen(buff);
                }else{
                    sprintf(buff + len_buff, ";%lu-DEL", position[j]);
                }
            }
            if (len_buff > BUFSIZ - len_max_dig){
                fwrite(buff, sizeof(char), len_buff, *fp);
                memset(buff, '\0', BUFSIZ); //set buffer bytes to NULL
                len_buff = 0;
            }
        }
    if (len_buff != 0){
                fwrite(buff, sizeof(char), len_buff, *fp);
                memset(buff, '\0', BUFSIZ); //set buffer bytes to NULL
                len_buff = 0;
    }
    fputc('\n', *fp);
    
    return;
}

/*Escritura en CHUNKS de BUFSIZ de strings*/
void * printStr(char * filename, char * str){
    int len_str = strlen(str);
    int div = len_str / BUFSIZ;
    FILE * fp = fopen(filename, "w");
    for (int i = 0; i < div; i++){
        fwrite(str + (i * BUFSIZ), sizeof(char), BUFSIZ, fp);
    }
    if (len_str > div * BUFSIZ)fwrite(str + (div * BUFSIZ), sizeof(char), len_str - (div * BUFSIZ), fp);
    
    fclose(fp);
}

char * ReadFile(char * filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       // Busca el último byte del archivo
       fseek(handler, 0, SEEK_END);
       // Tamaño del archivo
       string_size = ftell(handler);
       // Vuelta al principio
       rewind(handler);

       // Allocate a string that can hold it all
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;
       }

       // Always remember to close the file.
       fclose(handler);
    }

    return buffer;
}

/*RECURSIVITY AS A LIFESTYLE BBY*/
void * writeExtendedTree(FILE ** fp, struct node * root){
    
    if (root == NULL)return;
    
    if (root->hijo != NULL){
        fputc('(', *fp);
    }
    
    writeExtendedTree(fp, root->hijo);
    
    if (strcmp(root->name, "Nodo_intermedio") && root->ID != 1)
    {
        fprintf(*fp, "%s:%f", root->name, root->distancia);
    }

    if (!strcmp(root->name, "Nodo_intermedio")){
        fprintf(*fp, ")INT%d:%f[%f]", root->ID, root->distancia, root->Bootstrap);
    }
    
    if (root->siguiente != NULL)fputc(',', *fp);
    writeExtendedTree(fp, root->siguiente);
    
    if (!strcmp(root->name, "Root"))fprintf(*fp, ");");
    
    
}