#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Constructor, test1) {
  S21Matrix a;
  int rows = a.GetRows();
  int cols = a.GetCols();
  EXPECT_EQ(rows, 1);
  EXPECT_EQ(cols, 1);
}

TEST(Create, test1) { ASSERT_ANY_THROW(S21Matrix result(0, 0)); }

TEST(Create, test2) { S21Matrix(7, 7); }

TEST(Copy, test1) {
  S21Matrix a(10, 5);
  a.SetMatrix(3);
  S21Matrix b(a);
  bool res = a.EqMatrix(b);
  EXPECT_EQ(res, true);
}

TEST(Copy, test2) {
  S21Matrix a;
  S21Matrix b(a);
  bool res = a.EqMatrix(b);
  EXPECT_EQ(res, true);
}

TEST(SetRows, test1) {
  S21Matrix a(5, 5);
  a.SetRows(7);
  EXPECT_EQ(a.GetRows(), 7);
}

TEST(SetRows, test2_throw) {
  S21Matrix a;
  EXPECT_THROW(a.SetRows(-1), std::logic_error);
}

TEST(SetCols, test1) {
  S21Matrix a(3, 3);
  a.SetCols(5);
  EXPECT_EQ(a.GetCols(), 5);
}

TEST(SetCols, test2_throw) {
  S21Matrix a;
  EXPECT_THROW(a.SetCols(-1), std::logic_error);
}

TEST(Move, test1) {
  S21Matrix B(4, 8);

  S21Matrix Copy(B);
  ASSERT_TRUE(Copy.EqMatrix(B));

  S21Matrix Move(std::move(B));
  ASSERT_TRUE(Copy.EqMatrix(Move));
}

TEST(Move, test2) {
  S21Matrix a(4, 4);
  S21Matrix b(a);

  EXPECT_EQ(a.GetRows(), 4);
  EXPECT_EQ(a.GetCols(), 4);
  EXPECT_EQ(b.GetRows(), 4);
  EXPECT_EQ(b.GetCols(), 4);

  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      EXPECT_EQ(a(i, j), b(i, j));
    }
  }
}

TEST(EqMatrix, test1) {
  S21Matrix a(4, 4);
  S21Matrix b(4, 4);
  a.SetMatrixIncremented(3);
  b.SetMatrixIncremented(7);
  bool res = a.EqMatrix(b);
  EXPECT_EQ(res, false);
}

TEST(EqMatrix, test2) {
  S21Matrix result(2, 2), a(2, 2);

  a(0, 0) = 0.20;
  a(0, 1) = 20.0;

  result(0, 0) = 0.20;
  result(0, 1) = -20.0;

  ASSERT_FALSE(a.EqMatrix(result));
  ASSERT_FALSE(a == result);
}

TEST(EqMatrix_accuracy, test3) {
  S21Matrix result(2, 2), a(2, 2);

  a(0, 0) = 0.2000001101;
  a(0, 1) = 20.000011110;

  result(0, 0) = 0.2000001100;
  result(0, 1) = 20.000011100;

  ASSERT_TRUE(a.EqMatrix(result));
  ASSERT_TRUE(a == result);
}

TEST(EqMatrix_accuracy, test4) {
  S21Matrix result(2, 2), a(2, 2);

  a(0, 0) = 0.2000011100;
  a(0, 1) = 20.000001100;

  result(0, 0) = 0.2000001100;
  result(0, 1) = 20.000011100;

  ASSERT_FALSE(a.EqMatrix(result));
  ASSERT_FALSE(a == result);
}

TEST(SumMatrix, test1) {
  S21Matrix a(4, 4);
  S21Matrix b(4, 4);
  S21Matrix result(4, 4);

  a(0, 0) = 7;
  a(0, 1) = 4;
  a(0, 2) = 7;
  a(0, 3) = 1;

  a(1, 0) = 4;
  a(1, 1) = 6;
  a(1, 2) = 8;
  a(1, 3) = 1;

  a(2, 0) = 45;
  a(2, 1) = 56;
  a(2, 2) = 23;
  a(2, 3) = 44;

  a(3, 0) = 1;
  a(3, 1) = 9;
  a(3, 2) = 0;
  a(3, 3) = 4;

  b.SetMatrix(3);

  a.SumMatrix(b);

  result(0, 0) = 10;
  result(0, 1) = 7;
  result(0, 2) = 10;
  result(0, 3) = 4;

  result(1, 0) = 7;
  result(1, 1) = 9;
  result(1, 2) = 11;
  result(1, 3) = 4;

  result(2, 0) = 48;
  result(2, 1) = 59;
  result(2, 2) = 26;
  result(2, 3) = 47;

  result(3, 0) = 4;
  result(3, 1) = 12;
  result(3, 2) = 3;
  result(3, 3) = 7;

  bool res = a.EqMatrix(result);
  EXPECT_EQ(res, true);
}

TEST(SumMatrix, test2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 1);
  EXPECT_THROW(a.SumMatrix(b), std::logic_error);
}

TEST(SubMatrix, test1) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  S21Matrix result(3, 3);

  a(0, 0) = 7;
  a(0, 1) = 4;
  a(0, 2) = 7;

  a(1, 0) = 4;
  a(1, 1) = 6;
  a(1, 2) = 8;

  a(2, 0) = 45;
  a(2, 1) = 56;
  a(2, 2) = 23;

  b.SetMatrix(7);

  a.SubMatrix(b);

  result(0, 0) = 0;
  result(0, 1) = -3;
  result(0, 2) = 0;

  result(1, 0) = -3;
  result(1, 1) = -1;
  result(1, 2) = 1;

  result(2, 0) = 38;
  result(2, 1) = 49;
  result(2, 2) = 16;

  bool res = a.EqMatrix(result);
  EXPECT_EQ(res, true);
}

TEST(SubMatrix, test2) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 2);
  EXPECT_THROW(a.SubMatrix(b), std::logic_error);
}

TEST(MulMatrixSimple, test1) {
  S21Matrix a(2, 2);
  a.SetMatrixIncremented(1);

  S21Matrix b(2, 2);
  b.SetMatrixIncremented(5);

  a.MulMatrix(b);
  /*
    1 2 * 5 6
    3 4   7 8
  */
  S21Matrix result(2, 2);
  result(0, 0) = 19;  // 1 * 5 + 2 * 7
  result(0, 1) = 22;  // 1 * 6 + 2 * 8

  result(1, 0) = 43;  // 3 * 5 + 4 * 7
  result(1, 1) = 50;  // 3 * 6 + 4 * 8

  bool compare = a.EqMatrix(result);
  EXPECT_EQ(compare, true);
}

TEST(MulMatrix, test2) {
  S21Matrix a(3, 3);
  a.SetMatrixIncremented(1);

  S21Matrix b(3, 3);
  b.SetMatrixIncremented(2);

  a.MulMatrix(b);

  S21Matrix result(3, 3);
  result(0, 0) = 36;
  result(0, 1) = 42;
  result(0, 2) = 48;

  result(1, 0) = 81;
  result(1, 1) = 96;
  result(1, 2) = 111;

  result(2, 0) = 126;
  result(2, 1) = 150;
  result(2, 2) = 174;

  bool compare = a.EqMatrix(result);
  EXPECT_EQ(compare, true);
}

TEST(MulMatrix, test3) {
  S21Matrix a(3, 9);
  S21Matrix b(3, 9);
  EXPECT_THROW(a.MulMatrix(b), std::out_of_range);
}

TEST(Transpose, test1) {
  S21Matrix a(2, 2);
  a.SetMatrixIncremented(9.9);
  S21Matrix result(2, 2);
  result(0, 0) = 9.9;
  result(0, 1) = 11.9;

  result(1, 0) = 10.9;
  result(1, 1) = 12.9;

  a = a.Transpose();

  bool compare = a.EqMatrix(result);
  EXPECT_EQ(compare, true);
}

TEST(Transpose, test2) {
  S21Matrix a(1, 1);
  EXPECT_THROW(a.Transpose(), std::logic_error);
}

TEST(CalcComplements, test1) {
  S21Matrix a(5, 2);
  ASSERT_THROW(a.CalcComplements(), std::logic_error);
}

TEST(CalcComplements, test2) {
  S21Matrix a(3, 3);
  S21Matrix b(a.CalcComplements());
  EXPECT_EQ(b(2, 2), 0.0);
}

TEST(CalcComplements, test3) {
  S21Matrix a(3, 3);
  a(0, 0) = 5;
  a(0, 1) = 7;
  a(0, 2) = 1;

  a(1, 0) = -4;
  a(1, 1) = 1;
  a(1, 2) = 0;

  a(2, 0) = 2;
  a(2, 1) = 0;
  a(2, 2) = 3;

  a = a.CalcComplements();

  S21Matrix result(3, 3);
  result(0, 0) = 3;
  result(0, 1) = 12;
  result(0, 2) = -2;

  result(1, 0) = -21;
  result(1, 1) = 13;
  result(1, 2) = 14;

  result(2, 0) = -1;
  result(2, 1) = -4;
  result(2, 2) = 33;

  bool compare = a.EqMatrix(result);
  EXPECT_EQ(compare, true);
}

TEST(CalcComplements, test4) {
  S21Matrix a(3, 3);

  a(0, 0) = 0;
  a(0, 1) = -1;
  a(0, 2) = 3;

  a(1, 0) = 3;
  a(1, 1) = 1;
  a(1, 2) = 2;

  a(2, 0) = -2;
  a(2, 1) = -1;
  a(2, 2) = 4;

  a = a.CalcComplements();

  S21Matrix result(3, 3);
  result(0, 0) = 6;
  result(0, 1) = -16;
  result(0, 2) = -1;

  result(1, 0) = 1;
  result(1, 1) = 6;
  result(1, 2) = 2;

  result(2, 0) = -5;
  result(2, 1) = 9;
  result(2, 2) = 3;

  bool compare = a.EqMatrix(result);
  EXPECT_EQ(compare, true);
}

TEST(CalcComplements, test5) {
  S21Matrix a(4, 4);

  a(0, 0) = -6;
  a(0, 1) = -16;
  a(0, 2) = -1;
  a(0, 3) = -1;

  a(1, 0) = -1;
  a(1, 1) = -6;
  a(1, 2) = -2;
  a(1, 3) = -2;

  a(2, 0) = -5;
  a(2, 1) = -9;
  a(2, 2) = -3;
  a(2, 3) = -3;

  a(3, 0) = -5;
  a(3, 1) = -9;
  a(3, 2) = -3;
  a(3, 3) = -3;

  a = a.CalcComplements();
  S21Matrix result(4, 4);
  result(0, 0) = 0;
  result(0, 1) = -0;
  result(0, 2) = 0;
  result(0, 3) = -0;

  result(1, 0) = -0;
  result(1, 1) = 0;
  result(1, 2) = -0;
  result(1, 3) = 0;

  result(2, 0) = 0;
  result(2, 1) = -0;
  result(2, 2) = -91;
  result(2, 3) = 91;

  result(3, 0) = -0;
  result(3, 1) = 0;
  result(3, 2) = 91;
  result(3, 3) = -91;

  bool compare = a.EqMatrix(result);
  EXPECT_EQ(compare, true);
}

TEST(CalcComplements, test6) {
  S21Matrix a(1, 1);
  a.SetMatrix(1.0);
  a = a.CalcComplements();
  S21Matrix result(1, 1);
  result(0, 0) = 1.0;

  bool compare = a.EqMatrix(result);
  EXPECT_EQ(compare, true);
}

TEST(CalcComplements, test7) {
  S21Matrix a(1, 1);
  a.SetMatrix(-100);
  a = a.CalcComplements();
  S21Matrix result(1, 1);
  result(0, 0) = 1;

  bool compare = a.EqMatrix(result);
  EXPECT_EQ(compare, true);
}

TEST(Determinant, TestOne4x4) {
  S21Matrix a(4, 4);
  a(0, 0) = -2;
  a(0, 1) = 1;
  a(0, 2) = 3;
  a(0, 3) = 2;

  a(1, 0) = 3;
  a(1, 1) = 0;
  a(1, 2) = -1;
  a(1, 3) = 2;

  a(2, 0) = -5;
  a(2, 1) = 2;
  a(2, 2) = 3;
  a(2, 3) = 0;

  a(3, 0) = 4;
  a(3, 1) = -1;
  a(3, 2) = 2;
  a(3, 3) = -3;

  double det = a.Determinant();
  double result = -80;

  EXPECT_EQ(det, result);
}

TEST(Determinant, testTwo2x2) {
  S21Matrix a(2, 2);
  a(0, 0) = -6;
  a(0, 1) = -3;

  a(1, 0) = -10;
  a(1, 1) = -4;

  double det = a.Determinant();
  double result = -6;

  EXPECT_EQ(det, result);
}

TEST(Determinant, testThree3x3) {
  S21Matrix a(3, 3);
  a(0, 0) = 7;
  a(0, 1) = 4;
  a(0, 2) = 9;

  a(1, 0) = 0;
  a(1, 1) = 6;
  a(1, 2) = -3;

  a(2, 0) = 4;
  a(2, 1) = -10;
  a(2, 2) = -4;

  double det = a.Determinant();
  double result = -642;

  EXPECT_EQ(det, result);
}

TEST(Determinant, testFour1x1) {
  S21Matrix a(1, 1);
  a.SetMatrixIncremented(100);
  double det = a.Determinant();
  double result = 100;
  EXPECT_EQ(det, result);
}

TEST(Determinant, testFivezero) {
  S21Matrix a(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;

  a(1, 0) = 4;
  a(1, 1) = 5;
  a(1, 2) = 6;

  a(2, 0) = 7;
  a(2, 1) = 8;
  a(2, 2) = 9;

  double det = a.Determinant();
  double result = 0.000000000;

  EXPECT_DOUBLE_EQ(det, result);
}

TEST(Determinant, testSixaccuracy) {
  S21Matrix a(3, 3);
  a.SetMatrixIncremented(1);

  double det = a.Determinant();
  double result = 0.000000000000000000000000001;

  ASSERT_FALSE(det);
  ASSERT_TRUE(result);
}

TEST(Determinant, testSeven) {
  S21Matrix a(3, 9);
  ASSERT_THROW(a.Determinant(), std::logic_error);
}

TEST(InverseMatrix, test1) {
  S21Matrix a(4, 4);
  ASSERT_THROW(a.InverseMatrix(), std::out_of_range);
}

TEST(InverseMatrix, testTwodetEq1) {
  S21Matrix a(4, 4);
  a(0, 0) = 2;
  a(0, 1) = -3;
  a(0, 2) = 31;
  a(0, 3) = -23;

  a(1, 0) = -1;
  a(1, 1) = 2;
  a(1, 2) = -19;
  a(1, 3) = 14;

  a(2, 0) = 0;
  a(2, 1) = 0;
  a(2, 2) = 3;
  a(2, 3) = -2;

  a(3, 0) = 0;
  a(3, 1) = 0;
  a(3, 2) = -4;
  a(3, 3) = 3;

  a = a.InverseMatrix();
  S21Matrix result(4, 4);

  result = a;

  bool compare = a.EqMatrix(result);
  EXPECT_EQ(compare, true);
}

TEST(InverseMatrix, testThreedetEqNegative1) {
  S21Matrix a(3, 3);
  a(0, 0) = 2;
  a(0, 1) = 5;
  a(0, 2) = 7;

  a(1, 0) = 6;
  a(1, 1) = 3;
  a(1, 2) = 4;

  a(2, 0) = 5;
  a(2, 1) = -2;
  a(2, 2) = -3;

  a = a.InverseMatrix();

  S21Matrix result(3, 3);

  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;

  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;

  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;

  bool compare = a.EqMatrix(result);
  EXPECT_EQ(compare, true);
}

TEST(OperatorEqMatrix, test1) {
  S21Matrix a(7, 7);
  S21Matrix b(7, 7);
  a.SetMatrix(1);
  b.SetMatrix(2);
  bool res = a == b;
  EXPECT_EQ(res, false);
}

TEST(OperatorIndex, test1) {
  S21Matrix a(3, 3);
  a.SetMatrix(7);

  double res = a(0, 0);
  double compare = 7;
  EXPECT_EQ(compare, res);
  EXPECT_ANY_THROW(a(365, 0));
}

TEST(OperatorIndex, test2) {
  S21Matrix a(2, 3);
  a.SetMatrix(5);
  EXPECT_ANY_THROW(a(10, 0));
}

TEST(OperatorIndex, test3) {
  S21Matrix a(2, 3);
  a.SetMatrix(7.7);
  EXPECT_ANY_THROW(a(-1, 0));
}

TEST(OperatorPlus, test1) {
  S21Matrix a(5, 5);
  S21Matrix b(5, 5);
  S21Matrix c(5, 5);
  S21Matrix result(5, 5);

  a.SetMatrixIncremented(4);
  b.SetMatrixIncremented(6);
  c = a + b;

  result(0, 0) = 10;
  result(0, 1) = 12;
  result(0, 2) = 14;
  result(0, 3) = 16;
  result(0, 4) = 18;

  result(1, 0) = 20;
  result(1, 1) = 22;
  result(1, 2) = 24;
  result(1, 3) = 26;
  result(1, 4) = 28;

  result(2, 0) = 30;
  result(2, 1) = 32;
  result(2, 2) = 34;
  result(2, 3) = 36;
  result(2, 4) = 38;

  result(3, 0) = 40;
  result(3, 1) = 42;
  result(3, 2) = 44;
  result(3, 3) = 46;
  result(3, 4) = 48;

  result(4, 0) = 50;
  result(4, 1) = 52;
  result(4, 2) = 54;
  result(4, 3) = 56;
  result(4, 4) = 58;

  bool res = c.EqMatrix(result);
  EXPECT_EQ(res, true);
}

TEST(OperatorMinus, test1) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  S21Matrix c(3, 3);
  S21Matrix result(3, 3);

  a.SetMatrixIncremented(9);
  b.SetMatrixIncremented(3.3);
  c = a - b;
  result.SetMatrix(5.7);

  bool compare = a.EqMatrix(result);
  EXPECT_EQ(compare, true);
}

TEST(OperatorPlusEquals, test1) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix result(2, 2);

  a.SetMatrixIncremented(10.4);
  b.SetMatrixIncremented(7.7);
  a += b;

  result(0, 0) = 18.1;
  result(0, 1) = 20.1;

  result(1, 0) = 22.1;
  result(1, 1) = 24.1;

  bool res = a.EqMatrix(result);
  EXPECT_EQ(res, true);
}

TEST(OperatorMinusEquals, test1) {
  S21Matrix a(5, 5);
  S21Matrix b(5, 5);
  S21Matrix result(5, 5);

  a.SetMatrix(10.9);
  b.SetMatrix(3.1);
  a -= b;
  result.SetMatrix(7.8);
  bool compare = a.EqMatrix(result);
  EXPECT_EQ(compare, true);
}

TEST(OperatorMulNumber, test1) {
  S21Matrix a(4, 3);
  a.SetMatrixIncremented(5);
  S21Matrix res(4, 3);

  res(0, 0) = 35;
  res(0, 1) = 42;
  res(0, 2) = 49;

  res(1, 0) = 56;
  res(1, 1) = 63;
  res(1, 2) = 70;

  res(2, 0) = 77;
  res(2, 1) = 84;
  res(2, 2) = 91;

  res(3, 0) = 98;
  res(3, 1) = 105;
  res(3, 2) = 112;

  a * 7;
  bool compare = a.EqMatrix(res);
  EXPECT_EQ(compare, true);
}

TEST(OperatorMulMatrix, test1) {
  S21Matrix a(4, 7);
  S21Matrix b(4, 7);
  EXPECT_THROW(a * b, std::out_of_range);
}

TEST(OperatorMulMatrix, test2) {
  S21Matrix A(5, 5);
  A.SetMatrix(1.6);
  S21Matrix B(5, 5);
  B.SetMatrix(1.6);
  S21Matrix result(5, 5);
  result.SetMatrix(12.8);

  S21Matrix C(A * B);
  ASSERT_TRUE(C == result);
}

TEST(OperatorMulEqualsNum, Test1) {
  S21Matrix a(5, 5);
  a.SetMatrixIncremented(7);
  S21Matrix result(5, 5);
  a *= 4.5;

  result(0, 0) = 31.5;
  result(0, 1) = 36;
  result(0, 2) = 40.5;
  result(0, 3) = 45;
  result(0, 4) = 49.5;

  result(1, 0) = 54;
  result(1, 1) = 58.5;
  result(1, 2) = 63;
  result(1, 3) = 67.5;
  result(1, 4) = 72;

  result(2, 0) = 76.5;
  result(2, 1) = 81;
  result(2, 2) = 85.5;
  result(2, 3) = 90;
  result(2, 4) = 94.5;

  result(3, 0) = 99;
  result(3, 1) = 103.5;
  result(3, 2) = 108;
  result(3, 3) = 112.5;
  result(3, 4) = 117;

  result(4, 0) = 121.5;
  result(4, 1) = 126;
  result(4, 2) = 130.5;
  result(4, 3) = 135;
  result(4, 4) = 139.5;

  bool compare = a.EqMatrix(result);
  EXPECT_EQ(compare, true);
}

TEST(OperatorMulEqualsOther, test1) {
  S21Matrix a(5, 5);
  a.SetMatrixIncremented(1);

  S21Matrix b(5, 5);
  b.SetMatrixIncremented(2);

  S21Matrix result(5, 5);
  result(0, 0) = 230;
  result(0, 1) = 245;
  result(0, 2) = 260;
  result(0, 3) = 275;
  result(0, 4) = 290;

  result(1, 0) = 530;
  result(1, 1) = 570;
  result(1, 2) = 610;
  result(1, 3) = 650;
  result(1, 4) = 690;

  result(2, 0) = 830;
  result(2, 1) = 895;
  result(2, 2) = 960;
  result(2, 3) = 1025;
  result(2, 4) = 1090;

  result(3, 0) = 1130;
  result(3, 1) = 1220;
  result(3, 2) = 1310;
  result(3, 3) = 1400;
  result(3, 4) = 1490;

  result(4, 0) = 1430;
  result(4, 1) = 1545;
  result(4, 2) = 1660;
  result(4, 3) = 1775;
  result(4, 4) = 1890;

  a *= b;

  bool compare = a.EqMatrix(result);
  EXPECT_EQ(compare, true);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
