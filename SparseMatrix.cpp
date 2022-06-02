#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "SparseMatrix.h"

using namespace std;
// Private constructor
SparseMatrix::SparseMatrix(const vector<SparseVector>& container)
{
    this->container = container;
}

// Default constructor, creates 0x0 size SparseMatrix to prevent terminating program when an invalid entry is entered
SparseMatrix::SparseMatrix(){}

// Takes the filename and read the file, then creates a SparseMatrix object
SparseMatrix::SparseMatrix(string filename)
{
    ifstream infile;
    string line;
    int row;
    vector<int> rows;
    vector<SparseVector> tempContainer;
    infile.open(filename);
    if (infile.is_open())
    {
        while(getline(infile,line))
        {
            stringstream ss(line);
            ss >> row;
            rows.push_back(row);
            SparseVector tempVector(ss);
            tempContainer.push_back(tempVector);
        }
        container.resize(rows[rows.size()-1] + 1);
        for(int i=0; i<rows.size(); i++)
        {
            container[rows[i]] = tempContainer[i];
        }
        int max=0;
    }
    else
        cout << "File could not open!" << endl;

}

// Add function overloadings to below here
const SparseMatrix SparseMatrix::operator+(const SparseMatrix& right)
{
    //compares you if not equal return empty object instead of terminating program
    
    if(size() != right.size())
    {
        cout << "Error: Matrix dimensions do not match" << endl;
        return SparseMatrix();
    }
    vector<SparseVector> tempContainer;
    for (int i=0; i<size(); i++)
    {
        //picking up the same indexes and assigning them to the vector

        tempContainer.push_back(container[i] + right.container[i]);
    }
    
    return SparseMatrix(tempContainer);
}

const SparseMatrix SparseMatrix::operator-(const SparseMatrix& right)
{
    //compares you if not equal return empty object instead of terminating program

    if(size() != right.size())
    {
        cout << "Error: Matrix dimensions do not match" << endl;
        return SparseMatrix();
    }
    vector<SparseVector> tempContainer;
    for (int i=0; i<size(); i++)
    {
        //extracts the same indexes and assigns them to the vector
        
        tempContainer.push_back(container[i] - right.container[i]);
    }
    return SparseMatrix(tempContainer);
}
/*
  Given a sparse matrix, return a new sparse matrix with all the values negated
 The matrix with the negative values of the original matrix
 */
const SparseMatrix SparseMatrix::operator-()
{
     for(int i=0; i<size(); i++)
    {
         container[i] = -container[i];
      
    }
    return SparseMatrix(container);
}
/* This is the assignment operator. It is checking if the object is the same as the right object. If it
is the same, it returns the object. If it is not the same, it assigns the right object to the left
object. */

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& right)
{
    if(this==&right)
        return *this;
    container = right.container;
    return *this;
    
}
/*
  The function returns a SparseMatrix object
 */
const SparseMatrix SparseMatrix::operator*(const SparseMatrix& right)
{
   return SparseMatrix();
}
/*
  This function prints the matrix in a readable format
 */
ostream& operator<<(ostream& outputStream,const SparseMatrix& matrix)
{
    for(int i=0; i<matrix.size(); i++)
    {
        if (matrix.container[i].get_container().size() != 0)
            outputStream << i << ": " << matrix.container[i] << endl;
    }
    return outputStream;
}
/**
 * Given a sparse matrix, return a transpose of the matrix
 */
SparseMatrix SparseMatrix::transpose()
{
    //rov and column checks and swaps

    SparseMatrix transpose;
    int largestRow = findLargestRow();  
   
    for (int k = 0; k<largestRow; k++)
    {
        vector<double> datas;
        for (int i = 0; i < size(); i++)
        {
            if(k <container[i].size())   
                datas.push_back(container[i].get_container()[k]); 
            else 
                datas.push_back(0);    
        }
        transpose.container.push_back(SparseVector(datas));
        datas.resize(0);
    }
    return transpose;
}

/**
   Find the largest row in the matrix
*/
int SparseMatrix::findLargestRow() const
{
    int largest = 0;
    for (int i = 0; i < size(); i++)
    {
        if (container[i].size() > largest)
            largest = container[i].size();
    }
    return largest;
}

