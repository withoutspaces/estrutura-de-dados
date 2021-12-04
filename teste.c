#include <stdio.h>
#include <math.h>


double distance(int x1, int x2, int y1, int y2) {
    double ans = sqrt(pow((x2 - x1), 2) + (pow((y2 - y1), 2)));
    return ans;
}

int main() {
    int x1 = 3, x2 = 5, y1 = 3, y2 = 2;

    printf("%.2lf", distance(x1, x2, y1, y2));

    return 0;
}