#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <ostream>

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);
  double SetMatrix(double value);
  double SetMatrixIncremented(double value);

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix& operator=(const S21Matrix& other);
  bool operator==(const S21Matrix other);
  double& operator()(int i, int j);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);

 private:
  int rows_;
  int cols_;
  double** matrix_;

  void Alloc();
  void Dealloc();
  bool EqualSize(const S21Matrix& other);
  bool SquareMatrix(const S21Matrix& other);
  S21Matrix MinorMatrix(int row, int column);
  static double Pow(double base, long int exp);
};

#endif  // SRC_S21_MATRIX_OOP_H_
