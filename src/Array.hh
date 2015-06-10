#ifndef ARRAY_HH
#define ARRAY_HH

#include <iostream>

#define DIM_1D (0x0)
#define DIM_2D (0x1)

class Array
{
public:
   
   // Constructor
   Array( int xSize, int ySize );

   ~Array();
   Array(const Array& s);
   Array& operator= (const Array& s);

   // Access Operators
   char & operator () ( int i ,int j );

   // initialize the whole array with a constant value
   void fill( char value );

   // return total size of the array
   int getSize() const;

   // return xSize for dimension==0, ySize for dimension==1
   int getSize(int dimension ) const;

   // added to skeleton
   // return address of first element of the array
   char * getArray() const;

   // Print the whole array ( for debugging purposes )
   void print();

   // returns the maximum (absolute) value of the array
   // char getAbsMax();

private:

   // Sizes
   int xSize_;
   int ySize_;
   int size_;

   // Array pointer holding the actual elements
   char *ar;

};


#endif //ARRAY_HH
