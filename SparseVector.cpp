#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "SparseVector.h"


SparseVector::SparseVector() {}
SparseVector::SparseVector(string filename)
{
    //determination of parameters

    ifstream infile;
    int index;
    double value;
    char buffer;
    vector<int> indexes;
    vector<double> values;

    //Reading the data from the file according to integer, char, double and transferring the data to vector

    infile.open(filename); //opening the file
    if(infile.is_open())
    {
        while(infile >> index)
        {
            
            infile >> buffer >> value;
            indexes.push_back(index);
            values.push_back(value);
        }
        //determining the vector to you

        container.resize(indexes[indexes.size()-1] + 1);
        for(int i=0; i<indexes.size(); i++)
        {
            //transferring data to vector

            container[indexes[i]] = values[i];
        }
    }
    else
        cout << "File could not open!" << endl;
}
/*
  The function takes a string stream and reads in the indexes and values of a sparse vector. It then
  creates a vector of the appropriate size and populates it with the values read in
  transferring data to vector
 */
SparseVector::SparseVector(stringstream& ss)
{
    int index;
    double value;
    char buffer;
    vector<int> indexes;
    vector<double> values;
    while(ss >> index)
    {
        ss >> buffer >> value;
        indexes.push_back(index);
        values.push_back(value);
    }
    container.resize(indexes[indexes.size()-1] + 1);
    for(int i=0; i<indexes.size(); i++)
    {
        container[indexes[i]] = values[i];
    }
}

//Given a vector of doubles, create a sparse vector a vector of doubles 

SparseVector::SparseVector(const vector<double>& container)
{
    this->container = container;
}

/*
  Given two sparse vectors, return a new sparse vector that is the sum of the two
 the right hand side of the addition.A new SparseVector object.
 */

const SparseVector SparseVector::operator+(const SparseVector& right)
{
    if(container.size() != right.container.size())
    {
        cerr << "the length of the two vectors is not the same!";
        return SparseVector();
    }
    vector<double> totals(container.size());
    for(int i=0; i<totals.size(); i++)
    {
        totals[i] = container[i] + right.container[i];
       
    }
    

    return SparseVector(totals);
}

/*
  The function subtracts the values of the right vector from the values of the left vector and returns
  a new vector
  return A new SparseVector object.
 */

const SparseVector SparseVector::operator-(const SparseVector& right)
{
     
    if(container.size() != right.container.size())
    {
        cerr << "the length of the two vectors is not the same!";
        return SparseVector();
    }

    vector<double> totals(container.size());
    for(int i=0; i<totals.size(); i++)
    {
        totals[i] = container[i] - right.container[i];
      
    }

    return SparseVector(totals);

}

/*
  Given a sparse vector, return a sparse vector with all the values negated

 */

const SparseVector SparseVector::operator-()
{
    for(int i=0; i<container.size(); i++)
    {
         container[i] = -container[i];
      
    }
   return SparseVector(container);
}

/*
  The function copies the contents of the right hand side to the left hand side

 */
SparseVector& SparseVector::operator=(const SparseVector& right)
{
    if(this == &right)
        return *this;
    container =right.container;
    return *this;
}

/*
  This function takes in a vector of type SparseVector and outputs the vector in the form of
  a string
 */

ostream& operator<<(ostream& outputStream, const SparseVector& vec)
{
    for(int i=0; i<vec.container.size(); i++)
    {
        if(vec.container[i]!=0)
        {
            outputStream << i << ":" <<vec.container[i] << " ";
        }
    }
   return outputStream;
}

/*
 Given two sparse vectors, return the dot product of the two vectors
 */
double dot_product(const SparseVector& right,const SparseVector& left)
{
    double sum=0;

    if(right.container.size() != left.container.size())
    {
        cerr << "the length of the two vectors is not the same!";
       
    }

    for(int i=0; i<right.container.size(); i++)
    {
      
        sum = sum + right.container[i] * left.container[i];
      
    }
    return sum;
}