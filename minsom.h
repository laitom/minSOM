#ifndef MINSOM_H
#define MINSOM_H

#define NUM_DATA 5
#define DIM_DATA 5
#define DIM_MAPX 5
#define DIM_MAPY 3
#define MODEL_INIT_MIN -100.0
#define MODEL_INIT_MAX 100.0

struct node {
    double model[DIM_DATA];
    int pos_x;
    int pos_y;
};

struct som {
    struct node nodes[DIM_MAPY][DIM_MAPX];
    int N_size;
    int t;
};

void init_map(struct som *map);
void init_node(struct node *node, int x, int y);
double random_double(double n, double m);
double node_dist(struct node *node1, struct node *node2);
double euclidean_dist(double x[], double m[], int dim);
struct node *find_best_match(double x[], struct som *map);
void training_cycle(struct som *map, double inputs[][DIM_DATA]);

#endif // MINSOM_H
