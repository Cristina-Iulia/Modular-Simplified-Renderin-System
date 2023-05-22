#ifndef MATHTEST_IMATRIX_H
#define MATHTEST_IMATRIX_H

#include <memory>
#include <cstring>
#include "spdlog/spdlog.h"

template <typename T, size_t M, size_t N> struct matrix_t
{
	/*//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////---------------- ASSETS --------------////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////*/
	T data[M][N];
	using Type = T;  // for data type deduction


	/*//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////---------------- CONSTRUCTORS --------------//////////////////
	//////////////////////////////////////////////////////////////////////////////////////*/

	// Default constructor -> fill matrix with zeros
	matrix_t() { ::memset(data, 0, sizeof(T) * M * N); };

	// Copy constructor
	matrix_t(const matrix_t<float, 3, 3>& other)
	{
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				data[i][j] = other.data[i][j];
			}
		}
	}

	// Single value constructor -> fill matrix with given value
	matrix_t(T val)
	{
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				data[i][j] = val;
			}
		}
	}

	/*//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////---------------- OPERATORS --------------/////////////////////
	//////////////////////////////////////////////////////////////////////////////////////*/

	// Element access operator
	T* operator[](int i)
	{
		return data[i];
	}

	// Assignment operator
	matrix_t& operator=(const matrix_t<T, M, N>& other)
	{
		if (this != &other) {
			for (int i = 0; i < M; ++i) {
				for (int j = 0; j < N; ++j) {
					data[i][j] = other.data[i][j];
				}
			}
		}
		return *this;
	}

	// Equality operator
	bool operator==(const matrix_t<T, M, N>& other)
	{
		if (this != &other)
		{
			for (int i = 0; i < M; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					if (data[i][j] != other.data[i][j])
					{
						return false;
					}
				}
			}
		}
		return true;
	}


	// Matrix addition
	matrix_t operator+(const matrix_t<T, M, N>& other) const
	{
		matrix_t result;
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				result.data[i][j] = data[i][j] + other.data[i][j];
			}
		}
		return result;
	}

	// Matrix addition -> short version
	matrix_t& operator+=(const matrix_t<T, M, N>& other)
	{
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				data[i][j] = data[i][j] + other.data[i][j];
			}
		}
		return *this;
	}

	// Matrix subtraction
	matrix_t operator-(const matrix_t<T, M, N>& other) const
	{
		matrix_t result;
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				result.data[i][j] = data[i][j] - other.data[i][j];
			}
		}
		return result;
	}

	// Matrix subtraction -> short version
	matrix_t& operator-=(const matrix_t<T, M, N>& other)
	{
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				data[i][j] = data[i][j] - other.data[i][j];
			}
		}
		return *this;
	}

	// Scalar multiplication
	matrix_t operator*(T scalar) const
	{
		matrix_t result;
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				result.data[i][j] = scalar * data[i][j];
			}
		}
		return result;
	}

	// Matrix multiplication
	template<size_t X>
	matrix_t<T, M, X> operator*(const matrix_t<T, N, X>& other) const
	{
		matrix_t<T, M, X> result;
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < X; ++j) {
				for (int k = 0; k < N; ++k) {
					result.data[i][j] += data[i][k] * other.data[k][j];
				}
			}
		}
		return result;
	}

	// Matrix multiplication short version
	void operator*=(const matrix_t<T, M, N>& other)
	{
		if (!isSquare())
		{
			spdlog::error("Matrix is not square");
			return;
		}
		matrix_t<T, M, N> result;
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				result.data[i][j] = 0;
				for (int k = 0; k < M; ++k) {
					result.data[i][j] += data[i][k] * other.data[k][j];
				}
			}
		}

		::memcpy(data, result.data, sizeof(T) * M * N);
	}


	/*//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////---------------- MANIPULATORS --------------//////////////////
	//////////////////////////////////////////////////////////////////////////////////////*/


	// Dot product
	template<size_t X>
	matrix_t<T, M, X> dotProd(const matrix_t<T, N, X>& mat_) const
	{
		matrix_t<T, M, X> result;
		// Perform dot product
		for (size_t i = 0; i < M; ++i) {
			for (size_t j = 0; j < X; ++j) {
				for (size_t k = 0; k < N; ++k) {
					result[i][j] += data[i][k] * mat_.data[k][j];
				}
			}
		}
		return result;
	}


	// Matrix transpose
	matrix_t<T, N, M> Tran() const
	{
		matrix_t<T, N, M> result;
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				result.data[j][i] = data[i][j];
			}
		}
		return result;
	}

	// Get identity
	matrix_t<T, M, N> Identity() const
	{
		if (!isSquare())
		{
			spdlog::error("Matrix is not square");
			return {};
		}
		matrix_t<T, M, N> result;
		
		for (int i = 0; i < M; ++i)
		{
			result.data[i][i] = 1;
		}
		
		return result;
	}

	// Set identity
	void setIdentity()
	{
		if (!isSquare())
		{
			spdlog::error("Matrix is not square");
			return;
		}
		::memset(data, 0, sizeof(T) * M * N);
		for (int i = 0; i < M; ++i) 
		{
			data[i][i] = 1;				
		}
	}

	// Reset Matrix
	void reset()
	{
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				data[i][i] = 0;
			}
		}
	}

	// Determinant
	double det() const
	{
		// Check if the matrix is square
		if (!isSquare())
		{
			spdlog::error("Matrix is not square");
			return T(0);
		}

		// Create a copy of the matrix to perform LU decomposition
		matrix_t<T, M, N> luMatrix(*this);

		// Perform LU decomposition with partial pivoting
		for (size_t k = 0; k < M - 1; ++k)
		{
			for (size_t i = k + 1; i < M; ++i)
			{
				if (luMatrix[k][k] == 0)
				{
					spdlog::error("Error: Zero pivot encountered");
					return T(0);
				}
				luMatrix[i][k] /= luMatrix[k][k];
				for (size_t j = k + 1; j < M; ++j)
				{
					luMatrix[i][j] -= luMatrix[i][k] * luMatrix[k][j];
				}
			}
		}

		// Calculate determinant from LU decomposition
		double determinant = luMatrix[0][0];
		for (size_t k = 1; k < M; ++k) {
			determinant *= luMatrix[k][k];
		}

		return determinant;
	}

	// Invert of Matrix
	matrix_t<T, M, N> invert() const
	{
		matrix_t<T, M, N> inverse;
		double determinant = det();
		if (determinant == 0)
		{
			spdlog::error("Matrix not invertible");
			return inverse;
		}


		// Create a copy of the matrix to perform LU decomposition
		matrix_t<T, M, N> adjugate;

		// Create the adjugate matrix
		for (size_t i = 0; i < M; ++i) {
			for (size_t j = 0; j < N; ++j) {
				matrix_t<T, M - 1, N - 1> submatrix;
				for (size_t row = 0; row < M; ++row) {
					for (size_t col = 0; col < N; ++col) {
						if (row != i && col != j) {
							submatrix[row < i ? row : row - 1][col < j ? col : col - 1] = data[row][col];
						}
					}
				}
				double cofactor = ((i + j) % 2 == 0) ? 1 : -1;
				adjugate[j][i] = cofactor * submatrix.det();
			}
		}

		// Multiply adjugate matrix by the reciprocal of the determinant to get the inverse

		double reciprocalDeterminant = T(1) / determinant;
		for (size_t i = 0; i < M; ++i) {
			for (size_t j = 0; j < N; ++j) {
				inverse[i][j] = adjugate[i][j] * reciprocalDeterminant;
			}
		}

		return inverse;
	}

	/*//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////---------------- VALIDATORS --------------//////////////////
	//////////////////////////////////////////////////////////////////////////////////////*/


	// Square matrix check
	bool isSquare() const
	{
		if (M != N) return false;
		return true;
	}

	// Empty matrix check
	bool isEmpty() const
	{
		for (int i = 0; i < M; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if (data[i][j] != 0)
				{
					return false;
				}
			}
		}
		return true;
	}

	// Identity matrix check
	bool isIdentity() const
	{
		for (int i = 0; i < M; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if ((data[i][j] != 0 && i != j) || (data[i][j] != 1 && i == j))
				{
					return false;
				}
			}
		}
		return true;
	}

	// Invertible matrix check
	bool isInvertible()
	{
		double determinant = det();
		if (determinant == 0)
			return false;

		return true;
	}

	// Symmetric matrix check
	bool isSymmetric() const
	{
		for (int i = 0; i < M; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				if ((i != j) && (data[i][j] != data[j][i]))
				{
					return false;
				}
			}
		}
		return true;
	}

	/*//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////---------------- PRINT --------------//////////////////
	//////////////////////////////////////////////////////////////////////////////////////*/

	/*void display() const
	{
		std::cout << std::endl;
		for (int i = 0; i < M; ++i)
		{
			std::cout << std::endl;
			for (int j = 0; j < N; ++j)
			{
				std::cout << data[i][j] << " ";
			}
		}
	}*/
};


#endif //MATHTEST_IMATRIX_H
