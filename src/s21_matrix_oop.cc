#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(1, 1) {}

S21Matrix::S21Matrix(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  Alloc();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  if (&other != this) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.cols_ = 0;
  }
}

S21Matrix::~S21Matrix() {
  if (cols_ != 0) {
    Dealloc();
  }
}

void S21Matrix::SetRows(int rows) {
  if (rows < 0) {
    throw std::logic_error("The number of columns cannot be less than 0\n");
  }
  S21Matrix result(rows, cols_);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i >= rows_) {
        result.matrix_[i][j] = 0;
      } else {
        result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  *this = result;
}

void S21Matrix::SetCols(int cols) {
  if (cols < 0) {
    throw std::logic_error("The number of columns cannot be less than 0\n");
  }
  S21Matrix result(rows_, cols);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols; j++) {
      if (j >= cols_) {
        result.matrix_[i][j] = 0;
      } else {
        result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  *this = result;
}

int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

double S21Matrix::SetMatrix(double value) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = value;
    }
  }
  return value;
}

double S21Matrix::SetMatrixIncremented(double value) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = value++;
    }
  }
  return value;
}

void S21Matrix::Alloc() {
  if (rows_ < 1 || cols_ < 1) {
    throw std::logic_error("Wrong size of the Matrix");
  }
  matrix_ = new double*[rows_];
  if (matrix_ == nullptr) {
    throw std::bad_alloc();
  }
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
    if (matrix_[i] == nullptr) throw std::bad_alloc();
  }
}

void S21Matrix::Dealloc() {
  for (int row = 0; row < rows_; row++) {
    delete[] matrix_[row];
  }
  delete[] matrix_;
  matrix_ = nullptr;
}

bool S21Matrix::EqualSize(const S21Matrix& other) {
  bool res = true;
  if ((rows_ == other.rows_) && (cols_ == other.cols_) && matrix_ != nullptr &&
      other.matrix_ != nullptr) {
    res = true;
  } else {
    res = false;
    throw std::logic_error("Matrix sizes are not identical\n");
  }
  return res;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  static const double EPS = 0.0000001;
  bool res = false;
  if (EqualSize(other)) {
    res = true;
    for (int i = 0; res != false && i < rows_; i++) {
      for (int j = 0; res != false && j < cols_; j++) {
        double accuracy = matrix_[i][j] - other.matrix_[i][j];
        if (accuracy > EPS || accuracy < -EPS) {
          res = false;
        }
      }
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (EqualSize(other)) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (EqualSize(other)) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "the number of columns of the first matrix does not equal the number "
        "of rows of the second matrix\n");
  }
  S21Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < tmp.rows_; i++) {
    for (int j = 0; j < tmp.cols_; j++) {
      tmp.matrix_[i][j] = 0.0;
      for (int k = 0; k < cols_; k++) {
        tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = tmp;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix transposedMatrix(rows_, cols_);
  if ((transposedMatrix.rows_ <= 0) || (transposedMatrix.cols_ <= 0) ||
      (transposedMatrix.rows_ == 1 && transposedMatrix.cols_ == 1)) {
    throw std::logic_error("Wrong matrix size\n");
  }
  for (int i = 0; i < transposedMatrix.rows_; i++) {
    for (int j = 0; j < transposedMatrix.cols_; j++) {
      transposedMatrix.matrix_[i][j] = matrix_[j][i];
    }
  }
  return transposedMatrix;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result = *this;
  if (SquareMatrix(*this)) {
    if (cols_ == 1) {
      result.matrix_[0][0] = 1.0;
    } else {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
          S21Matrix tmpMatrix = MinorMatrix(i, j);
          result.matrix_[i][j] = tmpMatrix.Determinant() * Pow(-1, i + j + 2);
        }
      }
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  double determ = 0.0;
  if (SquareMatrix(*this)) {
    if (cols_ == 2) {
      determ = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    } else if (cols_ == 1) {
      determ = matrix_[0][0];
    } else if (cols_ > 2) {
      int degree = -1;
      for (int i = 0; i < rows_; i++) {
        degree = -1 * degree;
        S21Matrix tmpMatrix = MinorMatrix(i, 0);
        determ += degree * matrix_[i][0] * tmpMatrix.Determinant();
      }
    }
  }
  return determ;
}

S21Matrix S21Matrix::MinorMatrix(int Row, int Col) {
  S21Matrix slicedMatrix(rows_ - 1, cols_ - 1);
  int offsetRow = 0;
  for (int i = 0; i < slicedMatrix.rows_; i++) {
    if (i == Row) {
      offsetRow = 1;
    }
    int offsetCol = 0;
    for (int j = 0; j < slicedMatrix.cols_; j++) {
      if (j == Col) {
        offsetCol = 1;
      }
      slicedMatrix.matrix_[i][j] = matrix_[i + offsetRow][j + offsetCol];
    }
  }
  return slicedMatrix;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0.0) {
    throw std::out_of_range("matrix determinant is 0");
  }
  return CalcComplements().Transpose() * (1 / Determinant());
}

bool S21Matrix::SquareMatrix(const S21Matrix& other) {
  bool res = true;
  if (other.rows_ != other.cols_) {
    res = false;
    throw std::logic_error("Matrix is not square\n");
  }
  return res;
}

double S21Matrix::Pow(double base, long int exp) {
  double temp = 0.0;
  double res = 0.0;
  if (exp == 0) return 1;
  temp = Pow(base, exp / 2);
  if ((exp % 2) == 0) {
    res = temp * temp;
  } else {
    if (exp > 0) {
      res = base * temp * temp;
    } else
      res = (temp * temp) / base;
  }
  return res;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {  //&& (2operator=)
  if (matrix_ != nullptr) {
    Dealloc();
  }
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;

  Alloc();
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix other) { return EqMatrix(other); }

double& S21Matrix::operator()(int i, int j) {
  if ((i < 0 || i > rows_) || (j < 0 || j > cols_)) {
    throw std::out_of_range("Incorrect input, index is out of range\n");
  }
  return matrix_[i][j];
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  SumMatrix(other);
  S21Matrix res = *this;
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  SubMatrix(other);
  S21Matrix res = *this;
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  MulNumber(num);
  S21Matrix result = *this;
  return result;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}
