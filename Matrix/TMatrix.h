#pragma once
#include<iostream>
#include"TVector.h"
using namespace std;
template <class T>
class TMatrix {
private:
	TVector<TVector<T> > matr;
	int size;
public:
	TMatrix<T>(int _size = 0);
	~TMatrix<T>() {}
	TMatrix<T>(const TMatrix<T> & tmp);
	TMatrix<T>(const TVector<TVector<T> > & tmp);
	TVector<T> & operator[](const int k);
	TMatrix<T> operator +(const TMatrix<T> &tmp);
	TMatrix<T> operator -(const TMatrix<T> & tmp);
	TMatrix<T> & operator =(const TMatrix<T> &tmp);
	TMatrix<T> operator*(TMatrix<T> &tmp);
	TMatrix<T> operator *(const int k);
	friend istream & operator >>(istream &in, TMatrix<T> &tmp) {
		for (int i = 0; i < tmp.size; i++) {
			for (int j = 0; j < tmp.size; j++) {
				if (j >= i) {
					in >> tmp[i][j];
				}
				else {
					int x;
					in >> x;
				}
			}
		}
		return in;
	}
	friend ostream & operator <<(ostream & out, TMatrix<T> & tmp) {
		for (int i = 0; i < tmp.size; i++) {
			for (int j = 0; j < tmp.size; j++) {
				if (j >= i) {
					out << tmp[i][j] << ' ';
				}
				else out << "0 ";
			}
			out << '\n';
		}
		return out;
	}
};

template<class T>
inline TMatrix<T>::TMatrix(int _size) {
	if (_size < 0) throw - 1;
	this->size = _size;
	this->matr = TVector<TVector<T> >(this->size);
	for (int i = 0; i < this->size; i++) {
		this->matr[i] = TVector<T>(this->size - i, i);
	}
}

template<class T>
inline TMatrix<T>::TMatrix(const TMatrix<T>& tmp) {
	if (tmp.size < 0) throw - 1;
	this->size = tmp.size;
	this->matr = TVector<TVector<T> >(tmp.matr);
}

template<class T>
inline TMatrix<T>::TMatrix(const TVector<TVector<T>>& tmp) {
	this->size = tmp.size;
	this->matr = tmp;
}

template<class T>
inline TVector<T>& TMatrix<T>::operator[](const int k) {
	if (k < 0 || k >= this->size) throw - 1;
	return this->matr[k];
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator+(const TMatrix<T> &tmp) {
	if (this->size != tmp.size) throw - 1;
	TMatrix<T> res(this->size);
	res.matr = this->matr + tmp.matr;
	return res;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator-(const TMatrix<T>& tmp) {
	if (this->size != tmp.size) throw - 1;
	TMatrix<T> res(this->size);
	res.matr = this->matr - tmp.matr;
	return res;
}

template<class T>
inline TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T>& tmp) {
	this->size = tmp.size;
	this->matr = tmp.matr;
	return *this;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator*(TMatrix<T>& tmp) {
	if (tmp.size != this->size) throw - 1;
	TMatrix<T> res(this->size);
	for (int i = 0; i < this->size; i++) {
		for (int j = i; j < this->size; j++) {
			for (int k = i; k <= j; k++) {
				T kek = tmp.matr[k][j];
				kek *= this->matr[i][k];
				res[i][j] += kek;
			}
		}
	}
	return res;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator*(const int k) {
	TMatrix<T> res(this->size);
	for (int i = 0; i < (this->size); i++)
		res.matr[i] = (this->matr[i]) * k;
	return res;
}

