#include <iostream>
#include <cmath>

using namespace std;
class Matrix{
    public: 
    Matrix();
    Matrix(int row, int column);
    ~Matrix();
    Matrix* add( const Matrix* m2) const;
    Matrix* multiply( const Matrix* m2) const;
    static Matrix* transposit(const Matrix* m);
     Matrix* scalar(int number) const;
     void setMatrix(const int* initialValues);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);

    private:
    int** myArray;
    int row;
    int column;
};

//constructor without matrix dimensions
Matrix::Matrix(){
   myArray= nullptr;
   row=0;
   column=0;
}
//constructor with matrix dimensions
Matrix::Matrix(int Mrow, int Mcolumn){
    row= Mrow;
    column= Mcolumn;
    myArray= new int*[row];
    for(int i=0; i< row; i++)
    {
        myArray[i]= new int[column];
    }
}

//Matrix class destructor
Matrix::~Matrix(){
    for (int i=0; i< row; i++){
        delete myArray[i];
    }
    delete[] myArray;
}

//addition function
 Matrix* Matrix::add( const Matrix* m2) const{
    //throw errors when matrixes are missing or have different dimensions
    if (this && m2){
        if (row != m2->row || column != m2->column){
            throw invalid_argument("The matrices must have the same dimensions");
        }
        Matrix* temp= new Matrix(row, column);
        for(int i=0; i<row; i++){
            for(int j=0; j<column; j++){
               temp->myArray[i][j]= myArray[i][j] + m2->myArray[i][j];
            }
        }
        return temp;
    }
    else
    throw runtime_error("Missing matrix");

}

//multiplication function
Matrix* Matrix::multiply( const Matrix* m2) const{
    //throw errors when matrixes are missing or have different dimensions
    if (this && m2){
        if (column != m2->row){
            throw invalid_argument("Mismatching number of columns and rows");
        }
        Matrix* temp= new Matrix(row, m2->column);
        for (int i=0; i<row; i++){
            for(int j=0; j<m2->column; j++){
                temp->myArray[i][j]=0;
                for(int k=0; k< m2->row; k++){
                    temp->myArray[i][j]+= (myArray[i][k])* (m2->myArray[k][j]);
                }
            }
            
        }
        return temp;
    }
    else
    throw runtime_error("Missing matrix");

}
//function for scalar multiplication
Matrix* Matrix::scalar(int k) const{
    if (!this || !k) throw invalid_argument("Missing argument");
    Matrix* temp= new Matrix(row, column);
    for(int i=0; i< row; i++){
        for(int j=0; j< column; j++){
            temp->myArray[i][j] = k* myArray[i][j];
        }
    }
    return temp;
}

//function to find the transposit of a matrix
Matrix* Matrix::transposit(const Matrix* m){
    if(!m) throw invalid_argument("Missing argument");
    Matrix* temp= new Matrix(m->column,m->row);
    for(int i=0; i<temp->row; i++){
        for(int j=0; j< temp->column; j++){
            temp->myArray[i][j]= m->myArray[j][i];
        }
    }
    return temp;
}

//set matrix values function 
void Matrix::setMatrix(const int* initialValues){
    if(!initialValues) throw invalid_argument("Missing argument");
    for(int i=0; i< row; i++){
        for(int j=0; j<column; j++){
            myArray[i][j]= initialValues[i*column+ j];
        }
    }
}

std::ostream& operator<<(std::ostream& out, const Matrix& m){
    for(int i=0; i< m.row; i++){
        for(int j=0; j< m.column; j++){
            out<<m.myArray[i][j]<<" ";
        }
        out<<endl;
    }
    return out;
}

int main(){
    Matrix* A=new Matrix(2,2);
    Matrix* B= new Matrix(2,3);
    Matrix* C= new Matrix(2,3);
    
    //setting the matrix A
    int aValue[2][2]={{6,4}, {8,3}};
    A->setMatrix((const int*)aValue);
    
    //setting matrix B
    int bValue[2][3]={{1,2,3}, {4,5,6}};
    B->setMatrix((const int*)bValue);

    //setting matrix C
    int cValue[2][3]={{2,4,6}, {1,3,5}};
    C->setMatrix((const int*)cValue);
    
    //Assignment operations
    Matrix* temp1= B->scalar(3);
    Matrix* transposed= Matrix::transposit(C);
    Matrix* temp2= temp1->multiply(transposed);
    Matrix* D= A->add(temp2);

    //print operations result
    cout<<*D;

    //free memory
    delete A;
    delete B;
    delete C;
    delete temp1;
    delete transposed;
    delete temp2;
    delete D;

    return 0;
}