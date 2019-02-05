/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



/* 
 * File:   main.c
 * Author: qq
 *
 * Created on 7 de mayo de 2018, 10:40
 */
#include <setjmp.h>
#include <getopt.h>
#include "h_libs.h"
#include "Euler_LCA.h"
#include "p_placing.h"
#include "Archivos.h"
#include "structs.h"
#include "Cluster.h"

/*DEFINICION DE TRY-CATCH-THROW*/
#define TRY do{ jmp_buf ex_buf__; switch( setjmp(ex_buf__) ){ case 0:
#define CATCH(x) break; case x:
#define ETRY } }while(0)
#define THROW(x) longjmp(ex_buf__, x)

/*EXCEPCIONES*/
#define NO_CONFIG_FILE (1)
#define SETTING_THRESHOLD_EXCEPTION (2)
#define NWK_FAIL (3)
#define SEQ_NOTEQ_SNP (4)
#define NO_LEN_SEQS (5)
#define NO_METHOD (6)
#define HELP (7)
#define JUST_EXIT (8)
#define NO_NWK_GIVEN (9)


#define LIMITE 250
#define OPT_LIST "bqp::o::f::i::a::s::O::I::m::ht::t::uvX"

/*OS*/
#if defined(_WIN32) || defined(_WIN64)
    const char* os = "Windows";
#else
#ifdef __linux
    const char* os = "Linux";
#else
    const char* os = "Unknown";
#endif
#endif
int verboseG, numNodes;

/*MACROS*/
#define BHELP(x) if (strcmp(x, "help")){  //Begin help comprobation
#define NOHELP }else{                     //No help statement as argument
#define EHELP }                           //End help macro
#define VERBOSE(x) if (verboseG == 1) printf("%s", x);

const char *argp_program_version =
  "argp-ex3 1.0";
const char *argp_program_bug_address =
  "<bug-gnu-utils@gnu.org>";

/* Program documentation. */
static char doc[] =
  "Argp example #3 -- a program with options and arguments using argp";

/* A description of the arguments we accept. */
static char args_doc[] = "ARG1 ARG2";
static struct argp_option options[] =
            {
                /*FLAGS*/
                {"seqinc", 'q',  0, 0, "Sequence-related option flag"},
                {"snpbranch", 'b',  0, 0, "SNP Analysis-related option flag"},
                {"clusters-to-itol", 'u', 0, 0, 
                 "Send tree and cluster info to ITOL"},
                {"arguments->verbose", 'v', 0, 0, "Verbose"},
                /*FILE_INDICATIONS*/
                {"phylogeny",'p',  "PHYLOGENY", 0,  "Tree (nwk) used for clustering"},
                {"output-clusters", 'o', "OUTPUT-CLUSTERS" ,0, "Output cluster filename"},
                {"output-clusters-format", 'f', "OUTPUT-CLUSTERS-FORMAT", 0, "Output cluster filename"},
                {"output-clusters-ITOL", 'i', "OUTPUT-CLUSTERS-ITOL", 0, "Output filename for ITOL (Clusters)"},
                {"alignment", 'a', "ALIGNMENT", 0, "Alignment filename (Required for non-NJ analysis and SNP)"},
                {"snp-table", 's', "SNP-TABLE", 0, "SNP table filename"},
                {"output-snp", 'O', "OUTPUT-SNP", 0, "Output filename for SNP analysis"},
                {"output-snp-ITOL", 'I', "OUTPUT-SNP-ITOL", 0, "Output filename for ITOL (SNP Analysis)"},
                {"method", 'm', "METHOD", 0, "Method (1=NJ, 2=ML)"},
                {"help", 'h', 0, 0, "Display help"},
                {"threshold", 't',  "THRESHOLD", 0, "Threshold distance for clustering"},
                {"mexico", 'X', 0, OPTION_HIDDEN, "AAANDALE"},
                { 0 }
            };
    
struct arguments
{
  int method ;
  double threshold;
  int seqInclusion , SNPAnalysis , sendTree , abFlag , verbose,
      pFlag , oFlag , fFlag , aFlag , sFlag , 
      OFlag , iFlag , IFlag,  mFlag , tFlag , mexicoFlag , helpFlag, docHelp;
  /*SUBOPTIONS FOR ITOL BATCH UPLOAD*/
  int eTree, eClust, eBranches;
  /*FLAGS AND ARGS INITIALIZATION*/
  char *filenameNwk, *filenameClusters, *filenameITOL, *clusterMth, *alignSeqs, 
       *filenameSNP, *csvSNP, *itolSNP;
};


/*STILL THERE ARE THINGS TO CHANGE*/
/* Parse a single option. */
static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;
  switch (key)
    {

        case 'b':
            arguments->SNPAnalysis = 1;
            break;
        case 'q':
            arguments->seqInclusion = 1;
            break;
        case 'u':
            arguments->sendTree = 1;
            break;
        case 'v':
            arguments->verbose = 1;
            verboseG = 1;
            break;
        case 'h':
            arguments->docHelp = 1;
            break;
            
        case 'p':
            BHELP(arg)
                if(!arguments->pFlag){
                    //copyFileToSource(arg);
                    arguments->filenameNwk = strdup(arg);
                }
                arguments->pFlag = 1;
                break;
            NOHELP
                printf( "\n---------------------------------------------------\n"
                        "|Argument '-p', --phylogeny' info:                |\n"
                        "|                                                 |\n"
                        "| Tree filename, can be either the complete path  |\n"
                        "| or just the filename, but always with the       |\n"
                        "| extension (Usually, '.tree' or '.nwk')          |\n"
                        "|                                                 |\n"
                        "| Usage: -p Filename                              |\n"
                        "|        --phylogeny=Filename                     |\n"
                        "---------------------------------------------------\n");
                arguments->helpFlag = 1;
                break;
            EHELP

        case 'o':
            BHELP(arg)
                if(!arguments->oFlag)arguments->filenameClusters = strdup(arg);
                arguments->oFlag = 1;
                break;
            NOHELP
                printf( "\n---------------------------------------------------\n"
                        "|Argument '-o', '--output-clusters' info:         |\n"
                        "|                                                 |\n"
                        "| Clustering output filename(csv output, with ';' |\n"
                        "| as separators).Defaults to newick filename if   |\n"
                        "| no argument is given.                           |\n"
                        "| (Do not run without 'tree' argument)            |\n"
                        "---------------------------------------------------\n");
                arguments->helpFlag = 1;
                break;
            EHELP
                        
        case 'f':
            BHELP(arg)
                if(!arguments->fFlag)arguments->clusterMth = strdup(arg);
                arguments->fFlag = 1;
                break;
            NOHELP
                printf( "\n---------------------------------------------------\n"
                        "|Argument '-f', '--output-clusters-format' info:  |\n"
                        "|                                                 |\n"
                        "| Clustering output format, currently 2 options:  |\n"
                        "|   (DEFAULT)    1-'normal':                      |\n"
                        "|                  -> Cluster number              |\n"
                        "|                  -> Taxa names, comma separated |\n"
                        "|                  -> Mean pairwise taxa distance |\n"
                        "|                  -> median distance             |\n"
                        "|                  -> Standard deviation distance |\n"
                        "|                2-'senyorito-irving':            |\n"
                        "|                  -> Easter egg                  |\n"
                        "|                                                 |\n"
                        "| Usage: -f Filename.txt                          |\n"
                        "|        --output-clusters-format=Filename.txt    |\n"
                        "---------------------------------------------------\n");
                arguments->helpFlag = 1;
                break;
            EHELP
        case 'i':
            BHELP(arg)
                if (!arguments->iFlag)arguments->filenameITOL = strdup(arg);
                arguments->iFlag = 1;
                break;
            NOHELP
                printf( "\n---------------------------------------------------\n"
                        "|Argument '-i', '--output-clusters-ITOL' info:    |\n"
                        "|                                                 |\n"
                        "| Output Filename for ITOL 'TREE_COLORS'          |\n"
                        "| dataset, which stores the found clusters        |\n"
                        "| for an easy visualization on the ITOL website   |\n"
                        "|                                                 |\n"
                        "| Usage: -i Filename.txt                          |\n"
                        "|        --output-clusters-ITOL=Filename.txt      |\n"
                        "---------------------------------------------------\n");
                arguments->helpFlag = 1;
                break;
            EHELP

        case 'a':
            BHELP(arg)
                if(!arguments->aFlag)arguments->alignSeqs = strdup(arg);
                arguments->aFlag = 1;
                break;
            NOHELP
                printf( "\n---------------------------------------------------\n"
                        "|Argument '-a', '--alignment' info:               |\n"
                        "|                                                 |\n"
                        "| Input filename for sequences used for           |\n"
                        "| the alignment. Must be multiFasta file:         |\n"
                        "| -Sequence name beginning with '>' (one liner)   |\n"
                        "| -Sequence (May span multiple lines)             |\n"
                        "|                                                 |\n"
                        "| File must be in 'path-to-script/sequences'      |\n"
                        "|                                                 |\n"
                        "| Usage: -a Filename.txt                          |\n"
                        "|        --alignment=filename.txt                 |\n"
                        "---------------------------------------------------\n");
                arguments->helpFlag = 1;
                break;
            EHELP
        case 's':
            BHELP(arg)
                if (!arguments->sFlag)arguments->filenameSNP = strdup(arg);
                arguments->sFlag = 1;
                break;
            NOHELP
                printf( "\n---------------------------------------------------\n"
                        "|Argument '-s', '--snp-table' info:               |\n"
                        "|                                                 |\n"
                        "| Input filename for SNP table:                   |\n"
                        "|      -> Every line represents 1 base in the     |\n"
                        "|         alignment                               |\n"
                        "|                                                 |\n"
                        "| File must be in 'path-to-script/SNP_Tables      |\n"
                        "|                                                 |\n"
                        "| Usage: -s filename.txt                          |\n"
                        "|        --snp-table=filename.txt                 |\n"
                        "---------------------------------------------------\n");
                arguments->helpFlag = 1;
                break;
            EHELP
        case 'O':
            BHELP(arg)
                if (!arguments->OFlag)arguments->csvSNP = strdup(arg);
                arguments->OFlag = 1;
                break;
            NOHELP
                printf( "\n---------------------------------------------------\n"
                        "|Argument '-O', '--output-snp' info:              |\n"
                        "|                                                 |\n"
                        "| Output filename for SNP assignment by branch.   |\n"
                        "| filename must be provided with extension.       |\n"
                        "| Output is written as follows:                   |\n"
                        "|  ->Branch name (internal nodes are labeled      |\n"
                        "|    as INT'X')                                   |\n"
                        "|  ->;SNP('GenomicPosition''Ancestor'->'Mutation')|\n"
                        "|    (e.g. 1278A->G), repeated as many times as   |\n"
                        "|    unique SNP per branch                        |\n"
                        "|                                                 |\n"
                        "| Output will be written to                       |\n"
                        "| 'path-to-script/SNP_Branch'                     |\n"
                        "|                                                 |\n"
                        "| Usage: -O filename.txt                          |\n"
                        "|        --output-snp=filename.txt                |\n"
                        "---------------------------------------------------\n");
                arguments->helpFlag = 1;
                break;
            EHELP
        case 'I':
            BHELP(arg)
                if (!arguments->IFlag)arguments->itolSNP = strdup(arg);
                arguments->IFlag = 1;
                break;
            NOHELP
                printf( "\n---------------------------------------------------\n"
                        "|Argument '-I', '--output-snp-ITOL' info:         |\n"
                        "|                                                 |\n"
                        "| Output filename for ITOL for SNP assignment     |\n"
                        "| by branch. Visualization is done via HTML       |\n"
                        "| table generation for every node.                |\n"
                        "|                                                 |\n"
                        "| Output will be written to                       |\n"
                        "| 'path-to-script/ITOL'. if it's not already      |\n"
                        "| created, it will automatically be created.      |\n"
                        "|                                                 |\n"
                        "| Usage: -I filename.txt                          |\n"
                        "|        --output-snp-ITOL=filename.txt           |\n"
                        "---------------------------------------------------\n");
                arguments->helpFlag = 1;
                break;
            EHELP

        case 'm':
            BHELP(arg)
                if(arguments->mFlag)break;
                arguments->mFlag = 1;
                char * endptr = NULL;
                errno = 0;
                arguments->method = strtol(arg, &endptr, 10);
                /* test return to number and errno values */
                if (arg == endptr){
                    if(!strcmp(arg, "nj") || !strcmp(arg, "NJ")){
                        arguments->method = 0;
                    }else if(!strcmp(arg, "ml") || !strcmp(arg, "ML")){
                        arguments->method = 1;
                    }else{
                        printf ("invalid method (no digits found, 0 returned)\n");
                        arguments->helpFlag = 1;
                    }
                }else if (errno == ERANGE && arguments->method == LONG_MIN){
                    printf ("invalid method (underflow occurred)\n");
                    arguments->helpFlag = 1;
                }else if (errno == ERANGE && arguments->method == LONG_MAX){
                    printf ("invalid method (overflow occurred)\n");
                    arguments->helpFlag = 1;
                }else if (errno == EINVAL){  /* not in all c99 implementations - gcc OK */
                    printf ("invalid method (base contains unsupported value)\n");
                    arguments->helpFlag = 1;
                }else if (errno != 0 && arguments->method == 0){
                    printf ("invalid method (unspecified error occurred)\n");
                    arguments->helpFlag = 1;
                }else if (errno == 0 && arg && *endptr != 0){
                    printf ("valid method: %d (but additional characters remain)\n"
                            "Proceeding to shut down...\n", arguments->method);
                    arguments->helpFlag = 1;
                }
                break;
            NOHELP
                printf( "\n---------------------------------------------------\n"
                        "|Argument '-m', '--method' info:                  |\n"
                        "|                                                 |\n"
                        "| Method used for tree reconstruction. Accepts    |\n"
                        "| the following values:                           |\n"
                        "|     -Neighbour-Joining: 0, 'NJ', 'nj'           |\n"
                        "|     -Maximum Likelihood:1, 'ML', 'ml'           |\n"
                        "|                                                 |\n"
                        "| Usage: -m Method                                |\n"
                        "|        --output-snp-ITOL=Method                 |\n"
                        "---------------------------------------------------\n");
                arguments->helpFlag = 1;
                break;
            EHELP

        case 't':
            BHELP(arg)
                if(arguments->tFlag)break;
                arguments->tFlag = 1;
                char * endptr = NULL;
                errno = 0;
                arguments->threshold = strtod(arg, &endptr);
                /* test return to number and errno values */
                if (arg == endptr){
                    if(!strcmp(arg, "nj") || !strcmp(arg, "NJ")){
                        arguments->threshold = 0;
                    }else if(!strcmp(arg, "ml") || !strcmp(arg, "ML")){
                        arguments->threshold = 1;
                    }else{
                        printf ("invalid Threshold (no digits found, 0 returned)\n");
                        arguments->helpFlag = 1;
                    }
                }else if (errno == ERANGE && arguments->threshold == LONG_MIN){
                    printf ("invalid Threshold (underflow occurred)\n");
                    arguments->helpFlag = 1;
                }else if (errno == ERANGE && arguments->threshold == LONG_MAX){
                    printf ("invalid Threshold (overflow occurred)\n");
                    arguments->helpFlag = 1;
                }else if (errno == EINVAL){  /* not in all c99 implementations - gcc OK */
                    printf ("invalid Threshold (base contains unsupported value)\n");
                    arguments->helpFlag = 1;
                }else if (errno != 0 && arguments->threshold == 0){
                    printf ("invalid Threshold (unspecified error occurred)\n");
                    arguments->helpFlag = 1;
                }else if (errno == 0 && arg && *endptr != 0){
                    printf ("valid Threshold: %f (but additional characters remain)\n"
                            "Proceeding to shut down...\n", arguments->threshold);
                    arguments->helpFlag = 1;
                }
                break;
            NOHELP
                printf( "\n---------------------------------------------------\n"
                        "|Argument '-t', '--threshold' info:               |\n"
                        "|                                                 |\n"
                        "| Number of max SNP differences(Calculated by     |\n"
                        "| branch distance) nodes can have to be           |\n"
                        "| considered a cluster. Defaults to 10.0          |\n"
                        "|                                                 |\n"
                        "|              Accepted formats:                  |\n"
                        "| int              float            double        |\n"
                        "|  1                1.2             1.33...       |\n"
                        "|                                                 |\n"
                        "| Usage: -t Threshold                             |\n"
                        "|        --threshold=Threshold                    |\n"
                        "---------------------------------------------------\n");
                arguments->helpFlag = 1;
                break;
            EHELP

        case 'X':
            arguments->mexicoFlag = 1;
            break;

    case ARGP_KEY_ARG:
        break;

    case ARGP_KEY_END:
      /*if (state->arg_num < 1)
        /* Not enough arguments. 
        argp_usage (state);*/
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };


int main(int argc, char** argv) {
    
    //emptyFl = 0;
    verboseG = 0;
    /*TRY-THROW-CATCH*/
    TRY{
        /*DIRECTORY CREATION*/
        mkdir("Matrices", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        mkdir("Matrices/depth", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        mkdir("Matrices/parent", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        mkdir("Clusters", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        mkdir("ITOL", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        mkdir("sequences", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        mkdir("SNP_Tables", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        mkdir("SNP_Branch", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        
        if (argc < 2){
            printf("\nTo display help about the program, type '-h' or '--help'\n\n");
            THROW(JUST_EXIT);
        }
        
        struct arguments arguments;
        /*DEFAULT VALUES*/
        arguments.seqInclusion = 0, arguments.SNPAnalysis = 0, arguments.sendTree = 0, arguments.abFlag = 0, arguments.verbose = 0,
        arguments.pFlag = 0, arguments.oFlag = 0, arguments.fFlag = 0, arguments.aFlag = 0, arguments.sFlag = 0, 
        arguments.OFlag = 0, arguments.iFlag = 0, arguments.IFlag = 0, arguments.mFlag = 0, arguments.tFlag = 0, arguments.mexicoFlag = 0, arguments.helpFlag = 0,
        arguments.method = 0, arguments.docHelp = 0;
        
        argp_parse (&argp, argc, argv, 0, 0, &arguments);
        /*HELP AND ERROR CHECKING*/
        if(arguments.docHelp) THROW (HELP);
        if(arguments.helpFlag)THROW (JUST_EXIT);  //Just help, so program exits.
        if(!arguments.pFlag)THROW (NO_NWK_GIVEN); //No phylogeny given, so program exits.
        if(!arguments.aFlag && arguments.seqInclusion){
            printf("No alignment was given, so sequences cannot be included.\n"
                   "Proceeding to run without sequence assignment...\n");
            arguments.seqInclusion = 0;
        }
        if(!arguments.sFlag && arguments.SNPAnalysis){
            printf("No SNP table was given, so SNP analysis is not available.\n"
                   "Proceeding to run without SNP analysis...\n");
            arguments.SNPAnalysis = 0;
        }
        
        if (access(arguments.filenameNwk, F_OK | R_OK) == -1) THROW(NWK_FAIL);
        if (arguments.method > 0 && !arguments.seqInclusion) THROW(NO_LEN_SEQS);
        
        /* CHECK FOR ABSOLUTE OR RELATIVE PATH
         * STILL NOT IMPLEMENTED*/
        char * absNwk;
        if (arguments.filenameNwk[0] == '/'){
            absNwk = strdup(arguments.filenameNwk);
            arguments.abFlag = 1;
            char * buff = strdup(strrchr(arguments.filenameNwk, '/') + 1);
            free(arguments.filenameNwk);
            arguments.filenameNwk = strdup(buff);
        }
        
        
        /*DEFAULT VALUES ASSIGNATION*/
        VERBOSE("Values assignation\n");
        if(!arguments.oFlag){
            arguments.filenameClusters = malloc(sizeof(char) * (11 + strlen(arguments.filenameNwk)));
            strcpy(arguments.filenameClusters, "Clusters_");
            strcat(arguments.filenameClusters, arguments.filenameNwk);
            char * lastDot = strrchr(arguments.filenameClusters, '.');
            lastDot[0] = '\0';
            strcat(arguments.filenameClusters, ".csv");
        }
        if(!arguments.iFlag){
            arguments.filenameITOL = malloc(sizeof(char) * (14 + strlen(arguments.filenameNwk)));
            strcpy(arguments.filenameITOL, "Output_ITOL_");
            strcat(arguments.filenameITOL, arguments.filenameNwk);
            char * lastDot = strrchr(arguments.filenameITOL, '.');
            lastDot[0] = '\0';
            strcat(arguments.filenameITOL, ".txt");
        }
        if(!arguments.fFlag){
            arguments.clusterMth = strdup("Normal");
        }
        if (arguments.mexicoFlag)
            {
                printf("\n"
        "                                     ╓Φ╫╫╫╫▓▓▄                      \n" 
        "                                     ║╫╫╫╫╫╫▓▓╫M                    \n"
        "                                    ╓▌Ñ╫╫╫╫╫▓▓╫M                    \n"
        "                                    ▓▓▓▓▓▓▓▓▓▓▓⌐                    \n"
        "            ▓▓▓▓K▄,               ▓   ```\"╨╨╨║                     \n"
        "             ▀▓█▓▓▓▓▓▓▓╦▄,        ▓▓▓▓▓▓▓▓▓▓▓▓▓                     \n"
        "              ▀▓▓▓▓▓▓▓▓▓▓▓▓▓▓N╗▄▄▓╫╫╫╫╫╫╫╫╫╫╫╫▓                     \n"
        "               `▀╫╫╫╫╫▀▀▀▓▓▓▓▓▓▓▓▓█▓██▓▓▓▓▓▓▓▓▓▄╓╓,,,,,,,,,,,,,╓╓,  \n"
        "                 `▀▄╫╫╫╫╫╫╫╫╫╫╫╫▀▀▀▓▓█▓▓▓█▓▓▓██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓█M \n"
        "                    ╙▀███▓▓▄▄╫╫╫╫╫╫╫╫╫╫╫╫╫╫╫╫╫╫▀▀▀▀▀▀▀▀▀▀▓▓▓▓▓▓▓▀`  \n"
        "           ╔╬╫▓╫▄w    \"▀▓██████▓╫╫╫▄▄╫╫╫╫╫╫╫╫╫╫╫╫╫╫╫╫╫╫╫╫╫╫╫▓▀      \n"
        "            ╫╫▄▓█▓▓▄       `╙╙▀▓▌╣╫▓╫▓╫╣╫▓▓█████████▓╫╫╫▓▀╜\"╓▄╦N╦,  \n"
        "            ╙▓▓▓▓▓▓█           ╫╫▓▓▌╫▓╫▓▓▓▓▀▀▀▀▀▀╜╙\"╙▄╗╥  ▄▓▓▓█╫╣╫M \n"
        "              ╙▀▀╫╫▌,╓╗╦,     .▌╫╫▓▀▓▌▀▓╫▓▓        .▓╫▓Ñ▓╔╫█▓▓▓█▓Ñ  \n"
        "                   ╫█▓╫▓▓     ║╫▌▓Φ▓╫╔▄║▓▓▌        ╫╫╫╫╫Ñ╫▀▓▓▓▓▀^   \n"
        "                   ▌███▓▓     ▓╫░▓▄▄▌╙╓▓▓▀H       ╓╫▓████           \n"
        "                   ╫╫▓▓▓▌  ▄,╔▄▓███▓███╫▓▓        ▓╣╫█▓▓M           \n"
        "                  ▐╫╫▓╫▓▌  `╙║▀████▓██████▄▄     ╓╫▓╫╫▌╣            \n"
        "                  j╫╬▌╣▓▌    ▓╫▌╫▌╫▓╫╫▌▓▓▌``     ▓▓╬▓▓▓╛            \n"
        "                  j▓╫▌╣▓▌    ▓╫╫▓╫╫▓╫╫╫▓▓M      ╬▓╫▓▓▓M             \n"
        "                   ▓╫▓╫▓▓    ▌╫╫▓╫▓╫╫▓╫▓▓,,╓╓╗Φ▓▓▓▓▓▓┘              \n"
        "                   ╢▓╬▓╫▓▓╗ ▐M▓╫▌╫▓╬╫▓▓▓▓▓▓▓▓▓╫▓▓▓▓▀                \n"
        "                    ╙▀▓▓▓▓▓▓▓╫▌╫╫╫▌╫╫▌▓▓▓▓▓▓▓▀▀╨\"`                 \n"
        "                       `╙▀▀▓▓╫▓▓M╣╫╫╣▓▓▓M                           \n"
        "                           ▓▓╫▓╫▓╫╫▓▓▓▓                             \n"
        "                            ▌▓╫▌╫▓╬╫▓▓▓▌                            \n"
        "                           j▓▓╫▌╫▌╫╫▓▓▓M                            \n"
        "                           ║╫╫╫╫╫╫╫▓▓▓▓⌐                            \n"
        "                           ╫▓╫╣╫╣╫╫▓▓▓▓                             \n"
        "                           ║▓╫╣╫╣╫▓▓▓▓▌                             \n"
        "                   ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n");
                printf("\t\t\t    ¡AAAANDALE!\n\n");
            }
        
        if(!arguments.OFlag){
            arguments.csvSNP = malloc(sizeof(char) * (13 + strlen(arguments.filenameNwk)));
            strcpy(arguments.csvSNP, "Output_SNP_");
            strcat(arguments.csvSNP, arguments.filenameNwk);
            char * lastDot = strrchr(arguments.csvSNP, '.');
            lastDot[0] = '\0';
            strcat(arguments.csvSNP, ".txt");
        }
        if(!arguments.IFlag){
            arguments.itolSNP = malloc(sizeof(char) * (23 + strlen(arguments.filenameNwk)));
            strcpy(arguments.itolSNP, "Output_SNPTable_ITOL_");
            strcat(arguments.itolSNP, arguments.filenameNwk);
            char * lastDot = strrchr(arguments.itolSNP, '.');
            lastDot[0] = '\0';
            strcat(arguments.itolSNP, ".txt");
        }
        
        VERBOSE("Filename assignment\n");
        /*FILENAMES ASSIGNMENT*/
        char depthFile[LIMITE] = "Matrices/depth/";
        strcat(depthFile, arguments.filenameNwk);
        depthFile[strlen(depthFile) -4] = '\0';
        strcat(depthFile, "_depth.mtrx");
        char * name_tmp = strdup(arguments.filenameNwk);
        
        char parentFilename[LIMITE] = "Matrices/parent/";
        strcat(parentFilename, arguments.filenameNwk);
        parentFilename[strlen(parentFilename) -4] = '\0';
        strcat(parentFilename, "_parent.mtrx");
        
        char clusterFilename[LIMITE] = "Clusters/";
        strcat(clusterFilename, arguments.filenameClusters);
        free(arguments.filenameClusters);
        char itolFilename[LIMITE] = "ITOL/";
        strcat(itolFilename, arguments.filenameITOL);
        free(arguments.filenameITOL);
        
        char seqsFilename[LIMITE] = "sequences/";
        if(arguments.seqInclusion){
            strcat(seqsFilename, arguments.alignSeqs);
            free(arguments.alignSeqs);
        }
        
        char archivo_SNPs[LIMITE] = "SNP_Tables/";
        if(arguments.SNPAnalysis){
            strcat(archivo_SNPs, arguments.filenameSNP);
            free(arguments.filenameSNP);
        }
        
        char archivo_SNP_unique[LIMITE] = "SNP_Branch/";
        strcat(archivo_SNP_unique, arguments.csvSNP);
        free(arguments.csvSNP);
        
        char archivo_SNP_ITOL[LIMITE] = "ITOL/";
        strcat(archivo_SNP_ITOL, arguments.itolSNP);
        //free(arguments.itolSNP);
        
        
        char * treeFileCnt;
        if (!arguments.abFlag)
        {
            treeFileCnt = ReadFile((char*) arguments.filenameNwk);
        }else
        {
            treeFileCnt = ReadFile(absNwk);
        }
        VERBOSE("Creating tree and performing analysis\n");
        /*TREE CREATION*/
        struct node * root;
        root = createTree(treeFileCnt);
        depthAdjustment(root);
        
        int nodeNmbr = nodeCount(root, 0) + 1; //Node number
        numNodes = nodeNmbr - 1;
        
        struct node *** tree;
        mtrxIni((void***)&tree, nodeNmbr, 18, 'n');
        for (int i = 0; i < nodeNmbr; i++)
        {
            for (int j = 0; j < 18; j++) tree[i][j] = NULL;
        }
        treeFill(root, tree); //Fills "tree" with pointer to nodes
        
        int * depth;
        int ** parent;
        /* IF VARIABLES ARE ALREADY STORED, READ. 
         * ELSE, CREATE WITH APPROPIATE FUNCTIONS AND STORE.*/
        if (access(parentFilename, F_OK) != -1 && 
            access(depthFile, F_OK) != -1)
        {
            depth = readIntArray(depthFile, nodeNmbr);
            parent = readIntMtrx(parentFilename, nodeNmbr, 18);
            
        }else
        {
            
            depth = malloc(sizeof(int) * nodeNmbr);
            mtrxIni((void***)&parent, nodeNmbr, 18, 'i');
            for (int i = 0; i < nodeNmbr; i++){
                for (int j = 0; j < 18; j++){
                parent[i][j] = -1;
                }
            }
            /*PRECOMPUTE DEPTH PARENT*/
            dfs(1, 0, tree, &depth, parent);
            SparseMatrix(nodeNmbr-1, &parent);
            
            /*STORE COMPUTED MATRIX AND ARRAY*/
            storeMtrxInt(parent, parentFilename, nodeNmbr, 18);
            storeArrayInt(depth, depthFile, nodeNmbr);
        }

        /*INITIALIZE LEAVES LIST*/
        struct node ** leaves = malloc (sizeof (struct node*) * nodeNmbr);
        leavesTree(root, &leaves, 0);
        int positionLen;
        /*IF SEQS ARE GIVEN, PROCEED*/
        if (arguments.seqInclusion){
            VERBOSE("Sequence assignment in process...\n")
            /*SEQUENCE READING*/
            char ** seqStrings = fastaRead(seqsFilename);
                
            int seqListLen = seqStringsLen(seqStrings);
            struct seq ** seqList = malloc(sizeof(struct seq*) * (seqListLen + 1));
            
            /*ASSIGN SEQUENCES TO STRUCTURE LIST*/
            int j = 0;
            for (int i = 0; seqStrings[i] != NULL; i += 2){
                seqList[j++] = newSeq(seqStrings[i], seqStrings[i+1]);
            }
            seqList[j] = NULL;
            
            /*SEQUENCE SORTING*/
            quicksort_array_struct_seq(seqList, j);
            int nodesLen = nodeListLen(leaves);
            quicksort_array_struct_nodes(leaves, nodesLen);
            
            /* SEQUENCE ASSIGNMENT (TO NODES) AND REMAKE OF LEAVES LIST
             *      (Quicksorted, so we make a new one that follows
             *              the tree structure again)                  */
            Asignar_sequence_nodes(seqList, leaves);
            free(leaves);
            leaves = malloc (sizeof (struct node*) 
                              * nodeNmbr);
            leavesTree(root, &leaves, 0);
            
            /*FREE SEQUENCE LIST; SEQUENCES ARE ASSIGNED TO THE TREE NODES*/
            for(int i = 0; seqList[i] != NULL; i++){
                free(seqList[i]->name);
                free(seqList[i]->sequence);
                free(seqList[i]);
            }
            free(seqList);
            for (positionLen = 0; leaves[0]->taxonSeq[positionLen] != '\0';
                 ++positionLen);
            fflush(stdout);
            /*SNP ANALYSIS*/
            if (arguments.SNPAnalysis){
                VERBOSE("Beginning SNP analysis...\n");
                char * SNP;
                unsigned long int * position;
                Lectura_SNPS(archivo_SNPs, &position, &SNP);
                if (positionLen != strlen(SNP) / 2)
                {
                    printf("Lineas de SNP: %d\nlongitud de las secuencias: %lu\n",
                    positionLen, strlen(SNP) / 2);
                    THROW (SEQ_NOTEQ_SNP);
                
                }
                SNPAssignment(leaves, SNP, position);
                int len_SNPs = strlen(SNP) / 2;
                Ajustar_SNPs_NodosIntermedios (root, len_SNPs, SNP);

                char max_dig_pos[255]; //Store the value for the largest genomic position as a string
                sprintf(max_dig_pos, "%lu", position[len_SNPs]);
                int len_max_dig = strlen(max_dig_pos); //Stores the value for the largest genomic position as an int.
                FILE * fp = fopen(archivo_SNP_unique, "w");
                if (arguments.verbose == 1)
                {
                    printf("Writing SNPs output...\n");
                }
                print_SNPs(&fp, root, SNP, position, len_max_dig);
                fclose(fp);
                printPopupITOL(archivo_SNP_ITOL, archivo_SNP_unique);
                free(SNP);
                free(position);
            }
        }
        
        /*BRANCH DEPTH (DISTANCE TO ROOT) ADJUSTMENT BASED ON CHOSEN METHOD*/
        if (arguments.method){
            switch(arguments.method){
                case 1:
                if (!positionLen)THROW(NO_LEN_SEQS);
                dstAdjust(root, positionLen + 1);
                break;
            }
        }
        
        struct node *** Clusters = malloc(sizeof(struct node**) * (int) nodeNmbr / 2);
        for (int i = 0; i < (int) nodeNmbr/2; i++){
            Clusters[i] = NULL;
        }
        Clusters = Clusters_LCA(leaves, tree, depth, parent, nodeNmbr, 
                Clusters, arguments.threshold);
        
        
        /*Se crean y almacenan en archivos los clústeres encontrados y 
         *el archivo output para ITOL*/
        char * exTree = malloc(sizeof(char) * (strlen(arguments.filenameNwk) + 10));
        strcpy(exTree, "Extended_");
        strcat(exTree, arguments.filenameNwk);

        FILE * fp = fopen(exTree, "w");
        writeExtendedTree(&fp,root);
        fclose(fp);
        clusterCrr(&Clusters, tree, depth, parent, arguments.threshold, leaves);
        double ** mtrx_stats;
        mtrx_stats = clusterStats(Clusters,tree, depth, parent);
        if (Clusters[0] != NULL){
            Print_Clusteres(Clusters, (char*) clusterFilename, arguments.clusterMth, mtrx_stats);
            Print_ITOL(Clusters, (char*) itolFilename);
        }
        
        free(depth);
        int i = 0;
        for (i = 0; i < nodeNmbr; i++){
            if (Clusters[i] != NULL){
                free(Clusters[i]);
            }else{
                break;
            }
        }
        

        free(Clusters[i]);
        freeMtrx(&mtrx_stats, i);
        free(leaves);
        free(Clusters);
        free(treeFileCnt);
        for (int i = 0; i < nodeNmbr; i++){
            free(tree[i]);
            free(parent[i]);
        }
        free(parent);
        free(exTree);
        free(tree);
        free(arguments.clusterMth);
        free(arguments.filenameNwk);
        liberarArbol(root);
        VERBOSE("Sending tree to ITOL...\n");
        if(arguments.sendTree)sendToItol(name_tmp, itolFilename);
        free(name_tmp);

        printf("\n");
        
    }
    /*Catches de las excepciones creadas*/
    CATCH (NO_CONFIG_FILE){
        printf("Parece que el archivo de configuración no existe. Revísalo.\n"
                "Recuerda que debe llamarse 'config.txt'\n");
    }
    CATCH (SETTING_THRESHOLD_EXCEPTION){
        printf("El threshold está mal escrito. Revísalo\n");
    }
    CATCH (NWK_FAIL){
        printf("No existe el archivo '.nwk'\n\n");
    }
    CATCH (SEQ_NOTEQ_SNP){
        printf("El número de lineas del fichero de SNPs y la longitud de las "
                "sequences debería ser el mismo.\n\n");
    }
    CATCH (NO_LEN_SEQS){
        printf("No alignment given, so no clustering function can be done with that phylogeny.\n"
                "Exiting...\n");
    }
    CATCH (NO_METHOD){
        printf("No valid phylogeny construction method was given. Please, give "
                "one and restart the program. Exiting...\n\n");
    }
    CATCH (HELP){
        printf("\nichTBhys usage info:\n");
        printf("--------------------\n"
               "All proceedings go to making QQ happy =)\n\n"
               "For more specific info about each function, type it with argument\n"
               "\"help\"(e.g., --output-clusters=help). You can put more than one at once.\n"
               "(ONLY OPTIONS WITH ARGUMENTS, FLAGS DON'T HAVE HELP)\n\n"
               "Argument priority is determined just by order; repeated uses of\n"
               "same argument(e.g., -tTree.nwk --tree=AnotherTree.nwk) will only\n"
               "account for the first one used\n\n"
               "FLAGS\n"
               "-----------------------\n"
               "-q --seqinc\t\t\tSequence-related options flag\n\n"
               "-b --snpbranch\t\t\tSNP-related analysis flag\n\n"
               "-u --clusters-to-itol\t\tSend tree and cluster info to ITOL\n\t\t\t\t(Requires Curl)\n\n"
               "OPTIONS WITH ARGUMENTS\n"
               "-----------------------\n"
               "-p --phylogeny\t\t\tTree file(Nwk format)\n\n"
               "-o --output-clusters\t\tClustering output filename(csv output).\n\t\t\t\tIf no argument is given, defaults to\n\t\t\t\ttree filename (+.csv)\n\n"
               "-f --output-clusters-format\tClustering output format\n  ->Options:\n     -'Normal'\n     -'senyorito-irving'\n\n"
               "-i --output-clusters-ITOL\tClustering ITOL output filename.\n\t\t\t\tDefaults to tree filename\n\n"
               "-m --method\t\t\tTree construction method.\n  ->Options:\n    0-(Default)Neighbour-Joining\n    1-Maximum Likelihood(Requires alignment)\n\n"
               "-a --alignment\t\t\tAlignment used for the phylogeny reconstruction\n\n"
               "-s --snp-table\t\t\tSNP table\n\n"
               "-O --output-SNP\t\t\tSNP by branch output filename. Defaults to tree\n\t\t\t\tFilename (+.txt) if no name is given\n\n"
               "-I --output-snp-ITOL\t\tSNP by branch output for ITOL. Defaults to tree\n\t\t\t\t(Output_SNPTable_ITOL_)Filename(.txt) if no name\n\t\t\t\tis given\n\n"
               "-t --threshold\t\t\tThreshold of SNPs used to determine clusters\n\t\t\t\tin the phylogeny. 10 by default.\n\n");
    }
    CATCH (NO_NWK_GIVEN){
        printf("No phylogeny (nwk or tree file) was given.\n"
               "Proceeding to exit...\n\n");
    }
    CATCH (JUST_EXIT){
        return (EXIT_SUCCESS);
    }
    ETRY;
    
    return (EXIT_SUCCESS);
    
}

