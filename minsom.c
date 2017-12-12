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

    map->N_size = node_dist(&(map->nodes[0][0]), &(map->nodes[DIM_MAPY-1][DIM_MAPX-1])) / 2 + 1;
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

double node_dist(struct node_t *node1, struct node_t *node2) {
    return sqrt(pow(node2->pos_x - node1->pos_x, 2) + pow(node2->pos_y - node1->pos_y, 2));
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

void training_cycle(struct som_t *map, double inputs[][DIM_DATA]) {
    struct node_t *c;
    double alpha;
    
    ++(map->t);
    if (map->t % 1000 == 0)
	--(map->N_size);

    alpha = 0.9 * (1 - (map->t/1000));
    
    for (int i = 0; i < NUM_DATA; ++i) {
	c = find_best_match(inputs[i], map);

	for (int j = 0; j < DIM_MAPY; ++j) {
	    for (int k = 0; k < DIM_MAPX; ++k) {
		if (node_dist(c, &(map->nodes[j][k])) <= map->N_size) {
		    for (int l = 0; l < DIM_DATA; ++l) {
			map->nodes[j][k].model[l] = alpha * (inputs[i][l] - map->nodes[j][k].model[l]);
		    }
		}
	    }
	}
    }
}
