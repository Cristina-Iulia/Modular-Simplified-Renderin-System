#ifndef MATHTEST_IMATRIX_H
#define MATHTEST_IMATRIX_H

#include <memory>
#include <cstring>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

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
	void operator=(const matrix_t<T, M, N>& other)
	{
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				data[i][j] = other.data[i][j];
			}
		}

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

	// Scalar multiplication short version
	void operator*=(T scalar)
	{
		for (int i = 0; i < M; ++i) {
			for (int j = 0; j < N; ++j) {
				data[i][j] = scalar * data[i][j];
			}
		}	
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
	/*void invert()
	{
		matrix_t<T, M, N> inverse;
		double determinant = det();
		if (determinant == 0)
		{
			spdlog::error("Matrix not invertible");
			return;
		}


		// Create the cofactor matrix
		matrix_t<T, M, N> cofactor;
		for (size_t i = 0; i < M; ++i) {
			for (size_t j = 0; j < M; ++j) {
				// Create submatrix by removing the current row and column
				matrix_t<T, M-1, N-1> submatrix;
				size_t subRow = 0;
				for (size_t row = 0; row < M; ++row) {
					if (row == i) continue; // Skip the current row
					size_t subCol = 0;
					for (size_t col = 0; col < M; ++col) {
						if (col == j) continue; // Skip the current column
						submatrix[subRow][subCol] = data[row][col];
						++subCol;
					}
					++subRow;
				}
				// Calculate the cofactor as the determinant of the submatrix multiplied by the appropriate sign
				T sign = ((i + j) % 2 == 0) ? T(1) : T(-1);
				cofactor[j][i] = sign * submatrix.det();
			}
		}

		// Calculate the adjugate matrix
		matrix_t<T, M, N> adjugate;
		for (size_t i = 0; i < M; ++i) {
			for (size_t j = 0; j < M; ++j) {
				adjugate[i][j] = cofactor[i][j] / determinant;
			}
		}

		::memcpy(data, adjugate.data, sizeof(T)* M * N);
	}*/

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

	void display() const
	{
		auto logger = spdlog::get("matrixLogger");

		if(!logger) {
			// If the logger does not exist, create it with the name "matrixLogger"
			auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			logger = std::make_shared<spdlog::logger>("matrixLogger", console_sink);
			spdlog::register_logger(logger);
		}

		logger->info("Matrix:");

		// Iterate over the matrix and log each row
		for (int i = 0; i < M; ++i) {
			std::string rowStr;
			for (int j = 0; j < N; ++j) {
				// Convert each element to a string and append it to the row string
				rowStr += std::to_string(data[i][j]) + " ";
			}
			logger->info(rowStr);
		}
	}
};


#endif //MATHTEST_IMATRIX_H
