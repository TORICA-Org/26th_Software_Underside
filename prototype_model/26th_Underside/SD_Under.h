/*-----------------------
このファイルの役割：Under用SD用関数

------------------------*/

#pragma once

#include <SD.h>
#include <TORICA_SD.h>

#include "TORICA_parameters.h"

void initSD();

void save_SD_BUF(char* BUF);

void flashSD();

bool SDisActive();