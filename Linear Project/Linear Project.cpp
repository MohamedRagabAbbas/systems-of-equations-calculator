#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
void getCofactor(vector<vector<double>>& matrix, vector<vector<double>>& submatrix, int row, int col) 
{
    int n = matrix.size();
    int subrow = 0, subcol = 0;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if (i != row && j != col) 
            {
                submatrix[subrow][subcol++] = matrix[i][j];
                if (subcol == n - 1) {
                    subrow++;
                    subcol = 0;
                }
            }
        }
    }
}
double determinant(vector<vector<double>>& matrix) {
    int n = matrix.size();
    if (n == 1) 
        return matrix[0][0];
    double det = 0;
    vector<vector<double>> submatrix(n - 1, vector<double>(n - 1));
    for (int j = 0; j < n; j++) {
        getCofactor(matrix, submatrix, 0, j);
        det += matrix[0][j] * determinant(submatrix) * (j % 2 == 0 ? 1 : -1);
    }
    return det;
}
vector<double> solveSystem(vector<vector<double>>& coefficients, vector<double>& constants) {
    int n = coefficients.size();
    // Check if the coefficient matrix is invertible
    double det_A = determinant(coefficients);
    if (det_A == 0) {
        cout << "The coefficient matrix is not invertible." << endl;
        return vector<double>();
    }
    vector<double> solutions(n);

    // Solve for each variable using Cramer's Rule
    for (int i = 0; i < n; i++) {
        vector<vector<double>> matrix_i = coefficients;
        // Replace the ith column with the constants
        for (int j = 0; j < n; j++) {
            matrix_i[j][i] = constants[j];
        }
        // Calculate the determinant of the modified matrix
        double det_i = determinant(matrix_i);
        // Calculate the solution for the ith variable
        solutions[i] = det_i / det_A;
    }
    return solutions;
}
void programManger()
{
    while (true)
    {
        int n;
        cout << "Enter the size of the system: ";
        cin >> n;

        vector<vector<double>> coefficients(n, vector<double>(n));
        vector<double> constants(n);

        // Get the coefficients from the user
        cout << "Please enter the coefficients and constants for each equation." << endl;
        cout << "if the equation is (x1 + 2x2 + 5x3 = 15) you have to input (1 2 5 15)." << endl;
        for (int i = 0; i < n; i++) {
            cout << "Enter the coefficients and constant for equation " << i + 1 << ": ";
            for (int j = 0; j < n; j++) {
                cin >> coefficients[i][j];
            }
            cin >> constants[i];
        }
        // Solve the system of linear equations
        vector<double> solutions = solveSystem(coefficients, constants);
        // Print the solution
        if (!solutions.empty()) {
            cout << "The solution is:" << endl;
            for (int i = 0; i < n; i++) {
                cout << "Variable " << setw(8) << left << i + 1 << ": " << solutions[i] << endl;
            }
        }
        int x;
        cout << "To continue enter 1 : ";
        cin >> x;
        if (x != 1)
            break;
    }
    
}
int main() 
{
    programManger();
    return 0;
}