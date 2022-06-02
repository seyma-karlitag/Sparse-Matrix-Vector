#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H
#include <iostream>
#include <string>
#include <vector>


/* The SparseVector class is a vector that is stored as a sparse vector */
using namespace std;

class SparseVector
{
    private:
        vector<double> container;
    public:

        SparseVector();
        SparseVector(string filename);
        SparseVector(stringstream& ss);
        SparseVector(const vector<double>& container);
        const SparseVector operator+(const SparseVector& right);
        const SparseVector operator-(const SparseVector& right);
        const SparseVector operator-();
        SparseVector& operator=(const SparseVector& right);
        friend ostream& operator<<(ostream& outputStream,const SparseVector& vec);
        friend double dot_product(const SparseVector& right,const SparseVector& left);
        const vector<double>& get_container() const {
         return container;
        }
        int size() const {
            return container.size();
        }
};
#endif