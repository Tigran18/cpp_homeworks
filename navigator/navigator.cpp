#include <iostream>
#include <iomanip>

using namespace std;

void sort(int n, int a[][3]) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j][0] < a[minIndex][0]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            for (int k = 0; k < 3; k++) {
                int temp = a[i][k];
                a[i][k] = a[minIndex][k];
                a[minIndex][k] = temp;
            }
        }
    }
}

void print(int size, int a[][100]) {
    int i, j;
    cout << "\n  ";
    for (i = 0; i < size; i++) {
        cout << setw(3) << i + 1;
    }
    cout << "\n  ";
    for (i = 0; i < size; i++) {
        cout << setw(3) << "_";
    }
    cout << "\n";
    for (i = 0; i < size; i++) {
        cout << i + 1 << "|";
        for (j = 0; j < size; j++) {
            cout << setw(3) << a[i][j];
        }
        cout << "\n";
    }
}

void iteration(int size, int A[][100], int prev[][100]) {
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (A[i][k] != 0 && A[k][j] != 0) {
                    if (A[i][k] + A[k][j] < A[i][j] || A[i][j] == 0) {
                        A[i][j] = A[i][k] + A[k][j];
                        prev[i][j] = k;
                    }
                }
            }
        }
        cout << "\nIteration " << k + 1 << ":";
        print(size, A);
    }
    cout << "Shortest paths matrix:\n";
}

void printShortestPath(int start, int end, int prev[][100]) {
    if (start == end) {
        cout << start + 1 << " ";
    }
    else if (prev[start][end] == -1) {
        cout << "No path exists" << endl;
    }
    else {
        printShortestPath(start, prev[start][end], prev);
        cout << end + 1 << " ";
    }
}

int main() {
    bool t = true;
    while (t) {
        int C[100][3]={0}, i, j = 0, k = 0, n, prev[100][100] = {0}, choice;
        int A[100][100]={0}, max, x;
        cout << "Choose 1 to continue or 2 to exit: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter the number of edges: ";
            cin >> n;
            for (i = 0; i < n; i++) {
                cout << "Enter the edges of the graph and the length between them (" << i + 1 << "): ";
                for (j = 0; j < 3; j++) {
                    cin >> C[i][j];
                }
            }
            max = C[0][0];
            for (i = 0; i < n; i++) {
                for (j = 0; j < 2; j++) {
                    if (C[i][j] > max) {
                        max = C[i][j];
                    }
                }
            }
            sort(n, C);
            int x1, x2, y;
            for (i = 0; i < max; i++) {
                for (j = 0; j < max; j++) {
                    A[i][j] = 0;
                }
            }
            for (y = 0; y < n; y++) {
                x1 = C[y][0];
                x2 = C[y][1];
                A[x1 - 1][x2 - 1] = C[y][2];
            }
            print(max, A);
            iteration(max, A, prev);
            x = A[0][max - 1];
            cout << "\nThe length of the shortest path is: " << x << "\n";
            for (i = 0; i < max; i++) {
                for (j = 0; j < max; j++) {
                    cout << setw(3) << prev[i][j];
                }
                cout << "\n";
            }
            i = 0;
            for (j = 0; j < max; j++) { 
                cout << "\nShortest path from " << i + 1 << " to " << j + 1 << ": ";
                printShortestPath(i, j, prev);
                cout << "\n";
            }
            cout << "\n";
            break;
        case 2:
            t = false;
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid action\n";
            break;
        }
    }
    return 0;
}
/*13
1 2 3 1 3 5 2 4 4 2 5 2 3 5 3 3 6 8 4 5 2 4 7 5 5 6 9 5 8 1 6 8 10 7 9 10 8 9 6
*/