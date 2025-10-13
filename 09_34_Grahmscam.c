#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point {
    int x, y;
} Point;

// A global point needed for sorting points with reference to the first point
Point p0;

// Function to swap two points
void swap(Point *p1, Point *p2) {
    Point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// Function to find the next-to-top element in a stack
Point nextToTop(Point stack[], int *top) {
    return stack[*top - 1];
}

// Function to return the square of distance between two points
int distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y);
}

// To find orientation of ordered triplet (p, q, r).
// Returns:
// 0 --> Collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// A comparison function used by qsort() to sort points with respect to p0
int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;
    return (o == 2) ? -1 : 1;
}

// Prints the convex hull of a set of n points
void convexHull(Point points[], int n) {
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
            ymin = points[i].y;
            min = i;
        }
    }

    // Place the bottom-most point at first position
    swap(&points[0], &points[min]);

    // Sort remaining points based on polar angle with p0
    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // Remove collinear points, keeping the farthest one
    int m = 1;
    for (int i = 1; i < n; i++) {
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;
        points[m] = points[i];
        m++;
    }

    // If less than 3 unique points, convex hull is not possible
    if (m < 3) {
        printf("Convex hull not possible.\n");
        return;
    }

    // Create an empty stack and push first three points
    Point stack[m];
    int top = -1;
    stack[++top] = points[0];
    stack[++top] = points[1];
    stack[++top] = points[2];

    // Process remaining points
    for (int i = 3; i < m; i++) {
        while (orientation(nextToTop(stack, &top), stack[top], points[i]) != 2)
            top--;
        stack[++top] = points[i];
    }

    // Print the convex hull
    printf("\nPoints in Convex Hull (in counterclockwise order):\n");
    for (int i = 0; i <= top; i++)
        printf("(%d, %d)\n", stack[i].x, stack[i].y);
}

// Main function
int main() {
    int n;
    printf("Enter number of points: ");
    scanf("%d", &n);

    Point points[n];
    printf("Enter coordinates (x y):\n");
    for (int i = 0; i < n; i++)
        scanf("%d %d", &points[i].x, &points[i].y);

    convexHull(points, n);

    return 0;
}
