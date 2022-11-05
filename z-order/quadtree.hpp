typedef struct qtnode {
    int sx, sy, fx, fy;
    int **data;
    struct qtnode *top_right, *top_left;
    struct qtnode *bottom_right, *bottom_left;
} qtnode;


void init(qtnode**, int**, int, int, int, int);
void find(qtnode**, int, int);
