#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include <iostream>
#include <vector>
#include <string>
#include "SparseVector.h"

/* The SparseMatrix class is a class that stores a collection of SparseVector objects */

using namespace std;

class SparseMatrix
{
    private:
        vector<SparseVector> container;
        SparseMatrix(const vector<SparseVector>& container);
    public:
        SparseMatrix();
        SparseMatrix(string filename);
        const SparseMatrix operator+(const SparseMatrix& right);
        const SparseMatrix operator-(const SparseMatrix& right);
        const SparseMatrix operator-();
        const SparseMatrix operator*(const SparseMatrix& right);
        SparseMatrix&  operator=(const SparseMatrix& right);
        SparseMatrix transpose();
        friend ostream& operator<<(ostream& outputStream,const SparseMatrix& vec);
        const vector<SparseVector>& get_container() const {
            return container;
        }
        int size() const {
            return container.size();
        }
        int findLargestRow() const;
};
#endif