#define NUM_DATA 5
#define DIM_DATA 5
#define DIM_MAPX 5
#define DIM_MAPY 3
#define MODEL_INIT_MIN -100.0
#define MODEL_INIT_MAX 100.0

struct node_t {
    double model[DIM_DATA];
    int pos_x;
    int pos_y;
};

struct som_t {
    struct node_t nodes[DIM_MAPY][DIM_MAPX];
    int N_size;
    int t;
};

void init_map(struct som_t *map);
void init_node(struct node_t *node, int x, int y);
double random_double(double n, double m);
double node_dist(struct node_t *node1, struct node_t *node2);
double euclidean_dist(double x[], double m[], int dim);
struct node_t *find_best_match(double x[], struct som_t *map);
void training_cycle(struct som_t *map, double inputs[][DIM_DATA]);
