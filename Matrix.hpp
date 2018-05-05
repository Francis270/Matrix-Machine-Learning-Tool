// created by François Caïcedo
// francois.caicedo@epitech.eu

#pragma once

#include <iostream>
#include <exception>

template <class T>
class Matrix {

public:
	Matrix() {
		this->_rows = 0;
		this->_cols = 0;
		this->_data = new T[this->_rows * this->_cols];
	}

	Matrix(std::size_t const &rows, std::size_t const &cols) {
		this->_rows = rows;
		this->_cols = cols;
		this->_data = new T[this->_rows * this->_cols];
		for (std::size_t len = 0; len < this->_rows * this->_cols; len++) {
			this->_data[len] = 0;
		}
	}

	Matrix(std::vector<T> vec) {
		this->_rows = vec.size();
		this->_cols = 1;
		this->_data = new T[this->_rows * this->_cols];
		for (std::size_t len = 0; len < this->_rows * this->_cols; len++) {
			this->_data[len] = vec[len];
		}
	}

	Matrix(Matrix const &matrix) {
		this->_rows = matrix._rows;
		this->_cols = matrix._cols;
		this->_data = new T[this->_rows * this->_cols];
		for (std::size_t len = 0; len < this->_rows * this->_cols; len++) {
			this->_data[len] = matrix._data[len];
		}
	}

	std::size_t const &getRows() {
		return this->_rows;
	}

	std::size_t const &getCols() {
		return this->_cols;
	}

	void fill(std::vector<T> vec) {
		for (std::size_t len = 0; len < this->_rows * this->_cols; len++) {
			this->_data[len] = vec[len];
		}
	}

	Matrix &operator=(Matrix const &matrix) {
		if (matrix._rows == this->_rows && matrix._cols == this->_cols) {
			for (size_t len = 0; len < this->_rows * this->_cols; len++) {
				this->_data[len] = matrix._data[len];
			}
		} else {
			delete[] this->_data;
			this->_rows = matrix._rows;
			this->_cols = matrix._cols;
			this->_data = new T[this->_rows * this->_cols];
			for (std::size_t len = 0; len < this->_rows * this->_cols; len++) {
				this->_data[len] = matrix._data[len];
			}
		}
		return *this;
	}

	Matrix &operator*=(Matrix const &matrix) {
		if (this->_cols != matrix._rows) {
			throw std::runtime_error("Invalid mul");
		}
		Matrix tmp = *this;
		Matrix mult(this->_rows, matrix._cols);
		*this = mult;

		for (std::size_t i = 0; i < tmp._rows; i++) {
			for (std::size_t j = 0; j < matrix._cols; j++) {
				T sum = 0;
				for (std::size_t k = 0; k < matrix._rows; k++) {
					sum += tmp._data[i * tmp._cols + k] * matrix._data[k * matrix._cols + j];
				}
				(*this)._data[i * (*this)._cols + j] = sum;
			}
		}
		return *this;
	}

	Matrix &operator+=(Matrix const &matrix) {
		if (this->_rows != matrix._rows || this->_cols != matrix._cols) {
			throw std::runtime_error("Invalid add");
		}
		Matrix tmp = *this;
		Matrix add(this->_rows, this->_cols);
		*this = add;
		for (std::size_t i = 0; i < tmp._rows * tmp._cols; i++) {
			(*this)._data[i] = tmp._data[i] + matrix._data[i];
		}
		return *this;
	}

	Matrix &operator-=(Matrix const &matrix) {
		if (this->_rows != matrix._rows || this->_cols != matrix._cols) {
			throw std::runtime_error("Invalid sub");
		}
		Matrix tmp = *this;
		Matrix add(this->_rows, this->_cols);
		*this = add;
		for (std::size_t i = 0; i < tmp._rows * tmp._cols; i++) {
			(*this)._data[i] = tmp._data[i] - matrix._data[i];
		}
		return *this;
	}

	std::vector<T> const toVec() {
		std::vector<T> vec;

		for (std::size_t len = 0; len < (*this)._rows * (*this)._cols; len++) {
			vec.push_back((*this)._data[len]);
		}
		return vec;
	}

	bool operator==(Matrix const &matrix) {
		bool eval = true;

		if (matrix._rows != this->_rows || matrix._cols != this->_cols) {
			eval = false;
		} else {
			for (std::size_t len = 0; len < this->_rows * this->_cols; len++) {
				if (this->_data[len] != matrix._data[len]) {
					eval = false;
					break;
				}
			}
		}
		return eval;
	}

	bool operator!=(Matrix const &matrix) {
		bool eval = false;

		if (matrix._rows != this->_rows || matrix._cols != this->_cols) {
			eval = true;
		} else {
			for (std::size_t len = 0; len < this->_rows * this->_cols; len++) {
				if (this->_data[len] != matrix._data[len]) {
					eval = true;
					break;
				}
			}
		}
		return eval;
	}

	void randomize(T const &min, T const &max) {
		for (std::size_t len = 0; len < this->_rows * this->_cols; len++) {
			this->_data[len] = (((T)(rand()) / (T)(RAND_MAX)) * (max - min)) + min;
		}
	}

	void sigmoid() {
		for (std::size_t len = 0; len < this->_rows * this->_cols; len++) {
			this->_data[len] = this->_data[len] / (1 + abs(this->_data[len]));
		}
	}

	void clear() {
		this->_rows = 0;
		this->_cols = 0;
		delete[] this->_data;
		this->_data = new T[0];
	}

	void dump() {
		for (std::size_t len = 0; len < this->_rows * this->_cols; len++) {
			if (len && !(len % this->_cols)) {
				std::cout << '\n';
			}
			std::cout << this->_data[len] << " ";
		}
		std::cout << '\n';
	}

	~Matrix() {
		delete[] this->_data;
	}

private:
	std::size_t _rows;
	std::size_t _cols;
	T *_data;
};
