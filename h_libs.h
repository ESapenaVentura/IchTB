/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   h_libs.h
 * Author: qq
 *
 * Created on 4 de octubre de 2018, 10:07
 */

#ifndef H_LIBS_H
#define H_LIBS_H

#define BETWEEN(value, min, max) (value < max && value > min)




#include <stdio.h>
#include <argp.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <limits.h>
#include <pthread.h>
#include <math.h>
#include <errno.h>
#include "structs.h"

#define MAX_BUFF_FN 255 //Filename
#define MAX_BUFF_LN 1000 //Lines


#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* H_LIBS_H */

