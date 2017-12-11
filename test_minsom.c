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

int main(int argc, char *argv[]) {
    test_init_map_and_init_node();
    test_random_double();
}
