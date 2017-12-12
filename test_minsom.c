#include <assert.h>
#include <stdio.h>

#include "minsom.h"

void test_init_map_and_init_node() {
    printf("Testing init_map() and init_node()... ");

    struct som_t map;
    init_map(&map);

    for (int i = 0; i < DIM_MAPY; ++i) {
	for (int j = 0; j < DIM_MAPX; ++j) {
	    assert(map.nodes[i][j].pos_x == j);
	    assert(map.nodes[i][j].pos_y == i);

	    for (int k = 0; k < DIM_DATA; ++k) {
		assert(map.nodes[i][j].model[k] >= MODEL_INIT_MIN);
		assert(map.nodes[i][j].model[k] <= MODEL_INIT_MAX);
	    }
	}
    }

    if (DIM_MAPX < DIM_MAPY) {
	assert(map.N_size >= DIM_MAPX);
	assert(map.N_size <= DIM_MAPY);
    }
    else if (DIM_MAPX > DIM_MAPY) {
	assert(map.N_size <= DIM_MAPX);
	assert(map.N_size >= DIM_MAPY);
    }
    else {
	assert(map.N_size == DIM_MAPX+1);
    }

    printf("OK\n");
}

void test_random_double() {
    printf("Testing random_double()... ");
    
    double d;
    for (int i = 0; i < 5; ++i) {
	d = random_double(-4.567, 13.4);
	assert(d >= -4.567);
	assert(d <= 13.4);
    }

    printf("OK\n");
}

void test_node_dist() {
    printf("Testing node_dist()... ");

    struct som_t map;
    init_map(&map);

    assert(node_dist(&(map.nodes[0][0]), &(map.nodes[2][4])) > 4.472);
    assert(node_dist(&(map.nodes[0][0]), &(map.nodes[2][4])) < 4.473);

    printf("OK\n");
}

void test_euclidean_dist() {
    printf("Testing euclidean_dist()... ");

    double v[] = { 2, -1 };
    double u[] = { -2, 2 };
    assert(euclidean_dist(v, u, 2) == 5.0);

    double x[] = { -1.324, 56.2, 0.0 };
    double y[] = { 98.3, 45.67, -13.3 };
    assert(euclidean_dist(x, y, 2) > 101.057965-1);
    assert(euclidean_dist(x, y, 2) < 101.057965+1);

    printf("OK\n");
}

void test_find_best_match() {
    printf("Testing find_best_match()... ");

    struct som_t map;
    init_map(&map);

    double x[] = { 1.0, 1.0, 1.0, 1.0, 1.0 };
    
    struct node_t *should_win = &(map.nodes[1][2]);
    for (int i = 0; i < DIM_DATA; ++i)
	should_win->model[i] = x[i]-0.001;
    
    struct node_t *should_not_win = &(map.nodes[3][0]);
    for (int i = 0; i < DIM_DATA; ++i)
	should_win->model[i] = x[i]-0.01;
    
    struct node_t *winner = find_best_match(x, &map);
    assert(winner == should_win);
    assert(winner != should_not_win);

    printf("OK\n");
}

void test_training_cycle() {
    printf("Testing training_cycle()...\n");

    struct som_t map;
    init_map(&map);

    double inputs[][DIM_DATA] = {
	{ 0.0, 0.0, 0.0, 0.0, 0.0 },
	{ 100.0, 100.0, 100.0, 100.0, 100.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0 },
	{ 100.0, 100.0, 100.0, 100.0, 100.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0 }
    };

    for (int i = 0; i < DIM_MAPY; ++i) {
	for (int j = 0; j < DIM_MAPX; ++j) {
	    printf("%d,%d: ", map.nodes[i][j].pos_x, map.nodes[i][j].pos_y);
	    for (int k = 0; k < DIM_DATA; ++k)
		printf("%lf ", map.nodes[i][j].model[k]);
	    printf("\n");
	}
    }
    printf("\n");

    for (int i = 0; i < 1000; ++i)
	training_cycle(&map, inputs);

    for (int i = 0; i < DIM_MAPY; ++i) {
	for (int j = 0; j < DIM_MAPX; ++j) {
	    printf("%d,%d: ", map.nodes[i][j].pos_x, map.nodes[i][j].pos_y);
	    for (int k = 0; k < DIM_DATA; ++k)
		printf("%lf ", map.nodes[i][j].model[k]);
	    printf("\n");
	}
    }

    printf("OK\n");
}

int main(int argc, char *argv[]) {
    test_init_map_and_init_node();
    test_random_double();
    test_node_dist();
    test_euclidean_dist();
    test_find_best_match();
    test_training_cycle();
}
