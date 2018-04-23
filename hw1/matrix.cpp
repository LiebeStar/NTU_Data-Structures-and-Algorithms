

#include "matrix.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <new>

Matrix::Matrix(const int& r, const int& c) //constructor
{
    row = r;
    col = c;
    
    array = new double*[row];
    for(int i=0; i<row; i++){
        array[i] = new double[col];
    }
    
    for(int i = 0 ; i < r ; i++){
        for(int j = 0 ; j < c ; j++){
            array[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix& rhs) //copy constructor
{
    row = rhs.row;
    col = rhs.col;
    
    array = new double*[row];
    for(int i=0; i<row; ++i){
        array[i] = new double[col];
    }
    
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            array[i][j] = rhs.array[i][j];
        }
    }
}

Matrix::~Matrix() //destructor
{
    for(int i=0; i<row; i++){
        delete[] array[i];
    }
    delete[] array;
}

double* & Matrix::operator [](const int& idx) const
{
    return array[idx];
}

Matrix Matrix::operator =(const Matrix& rhs) // assignment operator
{
    if(&rhs==this){
        return *this;
    }
    else{
        for(int i=0; i<row; i++){
            delete[] array[i];
        }
        delete[] array;
    
        row = rhs.row;
        col = rhs.col;
        array = new double*[row];
        for(int i=0; i<row; ++i){
            array[i] = new double[col];
        }
        
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                array[i][j] = rhs.array[i][j];
            }
        }
        
        return *this;
    }
}

Matrix Matrix::operator -() const
{
    Matrix *m = new Matrix(*this);
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            m->array[i][j] = (array[i][j]<0)?array[i][j]:-array[i][j];
        }
    }
    return *m;
}

Matrix Matrix::operator +() const
{
    Matrix *m = new Matrix(*this);
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            m->array[i][j] = (array[i][j]>=0)?array[i][j]:-array[i][j];
        }
    }
    return *m;
}

Matrix Matrix::operator -(const Matrix& rhs) const
{
    Matrix *m = new Matrix(*this);
    for(int i=0; i<row; i+=1){
        for(int j=0; j<col; j+=1){
            m->array[i][j] -= rhs[i][j];
        }
    }
    
    return *m;
}

Matrix Matrix::operator +(const Matrix& rhs) const
{
    Matrix *m = new Matrix(*this);
    for(int i=0; i<row; i+=1){
        for(int j=0; j<col; j+=1){
            m->array[i][j] += rhs[i][j];
        }
    }
    
    return *m;
}

Matrix Matrix::operator *(const Matrix& rhs) const
{
    Matrix *m = new Matrix(row, rhs.col);
    for(int i=0; i<row; i++){
        for(int j=0; j<rhs.col; j++){
            for(int k=0; k<col; k++){
                m->array[i][j] += (array[i][k] * rhs[k][j]);
            }
        }
    }
    
    return *m;
}

Matrix Matrix::operator /(const Matrix& rhs) const
{
    return (*this)*rhs.inverse();
}


void getCofactor(Matrix A, Matrix &temp, int p, int q, int n)
{
    int i=0, j=0;

    for (int row=0; row<n; row++){
        for (int col=0; col<n; col++){

            if (row != p && col != q){
                temp[i][j++] = A[row][col];

                if (j==n-1){
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double determinant(Matrix A, int n)
{
    int D = 0;
    
    if (n == 1) return A[0][0];
    
    Matrix *temp = new Matrix(A);
    
    int sign = 1;
    for (int f = 0; f < n; f++){
        getCofactor(A, *temp, 0, f, n);
        D += sign * A[0][f] * determinant(*temp, n - 1);
        sign = -sign;
    }
    
    return D;
}

void adjoint(Matrix A, Matrix &adj)
{
    int N = A.row;
    
    if (N == 1){
        adj[0][0] = 1;
        return;
    }
    
    int sign = 1;
    
    Matrix *temp = new Matrix(N, N);
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            getCofactor(A, *temp, i, j, N);
            sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(determinant(*temp, N-1));
        }
    }
}

Matrix Matrix::inverse() const
{
    int N = row;
    double det = determinant(*this, N);

    // Find adjoint
    Matrix *adj = new Matrix(N, N);
    adjoint(*this, *adj);

    Matrix *inverse = new Matrix(N, N);
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            inverse->array[i][j] = adj->array[i][j]/det;
    
    return *inverse;
}

void Matrix::read(const char* fn)
{
    int r, c;
    FILE *fp = fopen(fn, "r");
    if(fp == NULL){
        printf("read file [%s] error\n", fn);
        exit(0);
    }
    fscanf(fp, "%d%d", &r, &c);
    Matrix tmp(r, c);
    for(int i = 0 ; i < r ; i++)
        for(int j = 0 ; j < c ; j++)
            fscanf(fp, "%lf", &tmp.array[i][j]);
    fclose(fp);
    *this = tmp;
}

void Matrix::write(const char* fn)
{
    FILE *fp = fopen(fn, "w");
    if(fp == NULL){
        printf("write file [%s] error\n", fn);
        exit(0);
    }
    fprintf(fp, "%d %d\n", row, col);
    for(int i = 0 ; i < row ; i++)
        for(int j = 0 ; j < col ; j++)
            fprintf(fp, "%lf%c", array[i][j], " \n"[j==col-1]);
    fclose(fp);
}

void Matrix::print() const
{
    for(int i = 0 ; i < row ; i++)
        for(int j = 0 ; j < col ; j++)
            printf("%lf%c", array[i][j], " \n"[j==col-1]);
    
    printf("\n");
}
