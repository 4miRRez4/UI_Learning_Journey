#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> sum(const vector<vector<int>>& A,const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j]+B[i][j];

    return C;
}

vector<vector<int>> subtract(const vector<vector<int>>& A,const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j]-B[i][j];

    return C;
}

vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));

    if (n == 1) {
        C[0][0] = A[0][0]*B[0][0];
        return C;
    }

    int half = n/2;
    vector<vector<int>> A11(half, vector<int>(half)), A12(half, vector<int>(half)),
                    A21(half, vector<int>(half)), A22(half, vector<int>(half)),
                    B11(half, vector<int>(half)), B12(half, vector<int>(half)),
                    B21(half, vector<int>(half)), B22(half, vector<int>(half));

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j+half];
            A21[i][j] = A[i+half][j];
            A22[i][j] = A[i+half][j+half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j+half];
            B21[i][j] = B[i+half][j];
            B22[i][j] = B[i+half][j+half];
        }
    }

    vector<vector<int>> P1 = strassen(A11, subtract(B12, B22));
    vector<vector<int>> P2 = strassen(sum(A11, A12), B22);
    vector<vector<int>> P3 = strassen(sum(A21, A22), B11);
    vector<vector<int>> P4 = strassen(A22, subtract(B21, B11));
    vector<vector<int>> P5 = strassen(sum(A11, A22), sum(B11, B22));
    vector<vector<int>> P6 = strassen(subtract(A12, A22), sum(B21, B22));
    vector<vector<int>> P7 = strassen(subtract(A11, A21), sum(B11, B12));


    vector<vector<int>> C11 = sum(subtract(sum(P5, P4), P2), P6);
    vector<vector<int>> C12 = sum(P1, P2);
    vector<vector<int>> C21 = sum(P3, P4);
    vector<vector<int>> C22 = subtract(subtract(sum(P5, P1), P3), P7);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i+half][j] = C21[i][j];
            C[i+half][j+half] = C22[i][j];
        }
    }

    return C;
}

int main() {
    int n; cin >> n;
    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> B[i][j];

    vector<vector<int>> C = strassen(A, B);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            cout << C[i][j] << " ";
        cout << endl;
    }

    return 0;
}