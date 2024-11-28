# Eng-s-OpenML-V2
Creating support for GPU accelerated Matrix Multiplications, this time with NumPy Support for ease of use. 


Supported Operations are based in NumPy, and so it will be a requirement for downloading this library. 



### 2 matrices in 1 matrix out
- Matrix Multiplication
	Input: Matrix A (mxn) Matrix B (nxp)
	Output: Matrix C (mxp)
- Matrix-Vector Multiplication
	Input: Matrix A (mxn) Vector v (n x 1)
	Output: Vector (mx1)
- Element-wise Operations
	Input: Matrix A (mxn) Matrix B (mxn)
	Output: Matrix C (mxn)

### 1 matrix in 1 matrix out
- Transpose
	Input: Matrix A (m×n)
	Output: Matrix A^T (n×m)
- Inverse
	Input: Square matrix A (n×n) that is non-singular (determinant ≠ 0)
	Output: Matrix A^(-1) (n×n)

### 1 Matrix in 1 Scalar out
- Determinant
	Input: Square matrix A (n×n)
	Output: Single scalar value
- Trace
	Input: Square matrix A (n×n)
	Output: Single scalar value (sum of diagonal elements)
- Frobenius Norm
	Input: Matrix A (any dimensions m×n)
	Output: Single scalar value (square root of sum of squared elements)

### Other
- Eigenvalues/Eigenvectors
	Input: Square matrix A (n×n)
	Output: n eigenvalues (scalars) and corresponding n eigenvectors (n×1)
- Singular Value Decomposition
	Input: Matrix A (m×n)
	Output: Three matrices: U (m×m), Σ (m×n), and V^T (n×n) where A = UΣV^T