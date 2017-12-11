#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "minsom.h"

void init_map(struct som_t *map) {
    for (int i = 0; i < DIM_MAPY; ++i)
	for (int j = 0; j < DIM_MAPX; ++j)
	    init_node(&(map->nodes[i][j]), j, i);

    map->t = 0;
}

void init_node(struct node_t *node, int x, int y) {
    for (int i = 0; i < DIM_DATA; ++i)
	node->model[i] = random_double(MODEL_INIT_MIN, MODEL_INIT_MAX);

    node->pos_x = x;
    node->pos_y = y;
}

double random_double(double n, double m) {
    return n + (rand() / (RAND_MAX / (m-n)));
}

double euclidean_dist(double x[], double m[], int dim) {
    double sum = 0.0;

    for (int i = 0; i < dim; ++i)
	sum += pow(x[i]-m[i], 2);

    return sqrt(sum);
}

struct node_t *find_best_match(double x[], struct som_t *map) {
    struct node_t *c;
    double min_dist = DBL_MAX, temp_dist;

    for (int i = 0; i < DIM_MAPY; ++i) {
	for (int j = 0; j < DIM_MAPX; ++j) {
	    temp_dist = euclidean_dist(x, map->nodes[i][j].model, DIM_DATA);
	    if (temp_dist < min_dist) {
		c = &(map->nodes[i][j]);
		min_dist = temp_dist;
	    }
	}
    }

    return c;
}
/*
int main(int argc, char *argv[]) {
    srand(time(NULL));
    
    struct som_t som;
    init_map(&som);

    double x[] = { 0, 0, 0, 0, 0 };
    struct node_t *winner = find_best_match(x, &som);
    printf("%d,%d\n\n", winner->pos_x, winner->pos_y);

    for (int i = 0; i < DIM_MAPY; ++i) {
	for (int j = 0; j < DIM_MAPX; ++j) {
	    printf("%d,%d: ", som.nodes[i][j].pos_x, som.nodes[i][j].pos_y);
	    for (int k = 0; k < DIM_DATA; ++k)
		printf("%lf ", som.nodes[i][j].model[k]);
	    printf("\n");
	}
    }
    
    printf("%d,%d: ", som.nodes[0][1].pos_x, som.nodes[0][1].pos_y);
    for (int i = 0; i < DIM_DATA; ++i)
	printf("%lf ", som.nodes[0][1].model[i]);
    printf("\n\n");

    double x[] = {2, -1};
    double m[] = {-2, 2};
    double d = euclidean_dist(x, m, 2);
    printf("%lf\n", d);

    return 0;
    }
*/
