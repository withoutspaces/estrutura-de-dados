#include <stdio.h>


int minimo(int v[], int t) {
    int m = 0, index = 0;
    for(int i = 0; i<t; i++) {
        if(i == 0) {
            m = v[i]; 
        } else {
            if(v[i] < m) {
                m = v[i];
                index = i;
            }
        }
    }
    return index + 1;
}


int get_min(int q, int v) {
    int min = 0, index = 0, min_media = 0, sum = 0;
    int mat[q][v];
    int voltas[q];

    for(int i = 0; i<q; i++) {
        for(int j = 0; j<v; j++) {
            scanf("%d", &mat[i][j]);
            sum += mat[i][j];
        }
        voltas[i] = sum;
        sum = 0;
    }

    min_media = minimo(voltas, q);

    return min_media;

}


int main() {
    int q, v;
    scanf("%d%d", &q, &v);

    int mat[q][v];

    printf("%d\n", get_min(q, v));

    return 0;
}