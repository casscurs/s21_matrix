# s21_matrix  

Implementation of the matrix.h library.   

## Matrix Operations Implementation

Implement the following basic operations with matrices:

- **Creation**: Create a matrix
- **Cleaning and Destruction**: Remove a matrix
- **Comparison**: Compare two matrices
- **Addition**: Add two matrices
- **Subtraction**: Subtract one matrix from another
- **Multiplication**: Multiply two matrices or a matrix by a scalar
- **Transpose**: Transpose a matrix
- **Determinant Calculation**: Calculate the determinant of a matrix
- **Calculation of Matrix of Algebraic Complements**: Calculate the matrix of algebraic complements
- **Finding Inverse of the Matrix**: Find the inverse of a matrix

### Library Development Guidelines

- Develop the library in C language of C11 standard using gcc compiler
- Locate the library code in the src folder on the develop branch   
- Avoid outdated and legacy language constructions and library functions, adhering to the POSIX.1-2017 standard
- Follow the Google style guide when writing code
- Make it a static library with the s21_matrix.h header file
- Develop the library according to the principles of structured programming
- Use the prefix s21_ before each function
- Ensure full coverage of library functions code with unit-tests using the Check library
- Unit tests should cover at least 80% of each function (checked using gcov)  
- Provide a Makefile for building the library and tests, including targets all, clean, test, s21_matrix.a, gcov_report
- The gcov_report target should generate an HTML page
- Implement the matrix structure as described in the "Matrix Structure in C Language" section above
- Ensure verifiable accuracy of the fractional part up to 6 decimal places

