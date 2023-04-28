#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

#include "common.h"

const int MEASUREMENTS = 16; // Кількість вимірів для кожного алгоритму і кожного типу сортування
const int rejected_number = 4; // Кількість відкинутих перших вимірів
const int min_max_number = 4; // Кількість відкинутих екстремальних вимірів