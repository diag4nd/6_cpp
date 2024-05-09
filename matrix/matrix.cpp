#include <iostream>
#include <vector>

enum ERROR
{
	SUCCES          =  0,
	ERROR_SUMM      = -1,
	ERROR_MULTI     = -2,
	ERROR_POW       = -3,
	ERROR_VECTINIT  = -4,
	ERROR_INDEX     = -5
};

class Matrix
{
private:
	unsigned m_height;
	unsigned m_width;
	int** m_ptr = nullptr;
public:
	//Конструкторы и деструктор
	Matrix(const int _value);                                                //Матрица 1 на 1 со значением
	Matrix(const unsigned _height, const unsigned _width, const int _value);
	Matrix(const Matrix& _origin);                                           //Копия матрицы
	Matrix(const std::vector<std::vector<int>> &_vector);                   //Переварить вектор из векторов
	~Matrix();
	//Полезные функции
	void fill(const int _value);                                             //Заполнить всю матрицу значением
	void print();
	void resize(const unsigned _height, const unsigned _width);
	void t();                                                                //Транспонировать
	void set(const unsigned _i, const unsigned _j, const int _value);        //Задать элемент вручную
	void addCol(const std::vector<int> _vector, const unsigned _j);
	void addRow(const std::vector<int> _vector, const unsigned _i);
	//Перегрузка привычных операторов
	friend Matrix operator +(const Matrix& _Lmatrix, const Matrix& _Rmatrix);	
	friend Matrix operator -(const Matrix& _Lmatrix, const Matrix& _Rmatrix);
	friend Matrix operator *(const Matrix& _Lmatrix, const Matrix& _Rmatrix);
	friend Matrix pow(const Matrix& _matrix, const unsigned _degree);        //Возведение в положительную степень
	friend bool operator ==(const Matrix& _Lmatrix, const Matrix& _Rmatrix); //Проверка на поэлементное равенство
	int&  operator ()(const unsigned _i, const unsigned _j);
	Matrix& operator =(const Matrix& _matrix);
};

Matrix::Matrix(const int _value = 0)
{	
	m_ptr = new int*;
	m_height = 1;
	*m_ptr = new int;
	m_width = 1;
	**m_ptr  = _value;
}

Matrix::Matrix(const unsigned _height, const unsigned _width, const int _value = 0)
{
	m_ptr = new int*[_height];
	m_height = _height;
	for(int i(0); i < m_height; i++)
	{
		m_ptr[i]  = new int[_width];
	}
	m_width = _width;
	this->fill(_value);
}

Matrix::Matrix(const Matrix &_origin)
{
	m_height = _origin.m_height;
	m_width = _origin.m_width;
	int** tempo_ptr = new int*[m_height];
	for(int i(0); i < m_height; i++)
	{
		tempo_ptr[i]  = new int[m_width];
		for(int j(0); j < m_width; j++)
		{
			tempo_ptr[i][j] = _origin.m_ptr[i][j];
		}
	}	
	m_ptr = tempo_ptr;
}

Matrix::Matrix(const std::vector<std::vector<int>> &_vector)
{
	try
	{
		int size = _vector[0].size();
		for(int i(1); i < _vector.size(); i++)
		{
			if (_vector[i].size() != size)
			{
				throw(std::string{"error: incorrect size of vector!\n"});
				exit(ERROR_VECTINIT);
			}
		}
		int** tempo_ptr = new int*[_vector.size()];
		for(int i(0); i < _vector.size(); i++)
		{
			tempo_ptr[i] = new int[size];
			for(int j(0); j < size; j++)
			{
				tempo_ptr[i][j] =  _vector[i][j];
			}
		}
		m_height = _vector.size();
		m_width = size;
		m_ptr = tempo_ptr;
		
	}
	catch(const std::string _errorMessage)
	{
		std::cerr << _errorMessage;
		exit(ERROR_VECTINIT);
	}
}

Matrix::~Matrix()
{
	if ((m_height == 1) && (m_width == 1))
	{
		delete *m_ptr;
		delete m_ptr;
	}
	else
	{
		for(int i(0); i < m_height; i++)
		{
			delete[] m_ptr[i];
		}
		delete[]  m_ptr;
	}
}

//

void Matrix::fill(const int _value)
{
	for(int i(0); i < m_height; i++)
	{
		for(int j(0); j < m_width; j++)
		{
			this->set(i, j, _value);
		}
	}
}

void Matrix::print()
{
	for(int i(0); i < m_height; i++)
	{
		for(int j(0); j < m_width; j++)
		{
			std::cout << m_ptr[i][j];
			if(j != m_width - 1)
			{
				std::cout << '\t';
			}
		}
		std::cout << std::endl;
	}
}

void Matrix::resize(const unsigned _height, const unsigned _width)
{
	int** tempo_ptr = new int*[_height];
	for(int i(0); i < _height; i++)
	{
		tempo_ptr[i] = new int[_width];
		if(i < m_height)
		{
			for(int j(0); j < _width; j++)
			{
				if(j < m_width)
				{
					tempo_ptr[i][j] = m_ptr[i][j];
				}
				else
				{
					tempo_ptr[i][j] = 0;
				}
			}
		}
		else
		{
			for(int j(0); j < _width; j++)
			{
				tempo_ptr[i][j] = 0;
			}
		}
	}
	this->~Matrix();
	m_ptr = tempo_ptr;
	m_height = _height;
	m_width = _width;
}

void Matrix::t()
{
	int** tempo_ptr = new int*[m_width];
	for(int i(0); i < m_width; i++)
	{
		tempo_ptr[i] = new int[m_height];
		for(int j(0); j < m_height; j++)
		{
			tempo_ptr[i][j] = m_ptr[j][i];
		}
	}
	this->~Matrix();
	m_ptr = tempo_ptr;
	int tempo_height(m_height);
	m_height = m_width;
	m_width = tempo_height;
}	

void Matrix::set(const unsigned _i, const unsigned _j, const int _value)
{
	m_ptr[_i][_j] = _value;
}

void Matrix::addCol(const std::vector<int> _vector, const unsigned _j = 0)
{
	try
	{
		if (_vector.size() != m_height)
		{
			throw(std::string{"error: incorrect size of vector!\n"});
		}
		if (_j > m_width)
		{
			throw(std::string{"error: incorrect index!\n"});
		}
		this->resize(m_height, m_width + 1);
		for(int j(m_width - 1); j >= 0 ; j--)
		{
			for(int i(0); i < m_height; i++)
			{
				if (j > _j)
				{
					m_ptr[i][j] = m_ptr[i][j - 1];
				}
				else if (j == _j)
				{
					m_ptr[i][j] = _vector[i];
				}
			}
		}
	}
	catch(std::string _errorMessage)
	{
		std::cerr << _errorMessage;
		exit(ERROR_VECTINIT);
	}
}

void Matrix::addRow(const std::vector<int> _vector, const unsigned _i = 0)
{
	try
	{
		if (_vector.size() != m_width)
		{
			throw(std::string{"error: incorrect size of vector!\n"});
		}
		if (_i > m_height)
		{
			throw(std::string{"error: incorrect index!\n"});
		}
		this->resize(m_height + 1, m_width);
		for(int i(m_height - 1); i >= 0 ; i--)
		{
			for(int j(0); j < m_width; j++)
			{
				if (i > _i)
				{
					m_ptr[i][j] = m_ptr[i - 1][j];
				}
				else if (i == _i)
				{
					m_ptr[i][j] = _vector[j];
				}
			}
		}
	}
	catch(std::string _errorMessage)
	{
		std::cerr << _errorMessage;
		exit(ERROR_VECTINIT);
	}
}

//

Matrix operator +(const Matrix& _Lmatrix, const Matrix& _Rmatrix)
{
	try
	{	
		if ((_Lmatrix.m_height == _Rmatrix.m_height) && (_Lmatrix.m_width == _Rmatrix.m_width))
		{
			Matrix tempo(_Lmatrix.m_height, _Lmatrix.m_width);
			for(int i(0); i < tempo.m_height; i++)
			{
				for(int j(0); j < tempo.m_width; j++)
				{
					tempo.set(i, j, _Lmatrix.m_ptr[i][j] + _Rmatrix.m_ptr[i][j]);
				}
			}
			return tempo;
		}
		else
		{
			throw std::string{"error: Can not do such operation with different sized matrices!\n"};
		}
	}
	catch (const std::string _errorMessage)
	{
		std::cerr << _errorMessage;
		exit(ERROR_SUMM);
	}
}

Matrix operator -(const Matrix& _Lmatrix, const Matrix& _Rmatrix)
{
	try
	{	
		if ((_Lmatrix.m_height == _Rmatrix.m_height) && (_Lmatrix.m_width == _Rmatrix.m_width))
		{
			Matrix tempo(_Lmatrix.m_height, _Lmatrix.m_width);
			for(int i(0); i < tempo.m_height; i++)
			{
				for(int j(0); j < tempo.m_width; j++)
				{
					tempo.set(i, j, _Lmatrix.m_ptr[i][j] - _Rmatrix.m_ptr[i][j]);
				}
			}
			return tempo;
		}
		else
		{
			throw std::string{"error: Can not do such operation with different sized matrices!\n"};
		}
	}
	catch(const std::string _errorMessage)
	{
		std::cerr << _errorMessage;
		exit(ERROR_SUMM);
	}
}

Matrix operator *(const Matrix& _Lmatrix, const Matrix& _Rmatrix)
{
	try
	{
		if (_Lmatrix.m_width == _Rmatrix.m_height)
		{
			Matrix tempo(_Lmatrix.m_height, _Rmatrix.m_width);
			for(int i(0); i < tempo.m_height; i++)
			{
				for(int j(0); j < tempo.m_width; j++)
				{
					for(int k(0); k < _Lmatrix.m_width; k++)
					{
						tempo.m_ptr[i][j] += _Lmatrix.m_ptr[i][k]*_Rmatrix.m_ptr[k][j];
					}
				}
			}
			return tempo;
		}
		else
		{
			throw std::string{"error: Can not multiply matrices with such dimensions!\n"};
		}
	}
	catch(const std::string _errorMessage)
	{
		std::cerr << _errorMessage;
		exit(ERROR_MULTI);
	}
}

Matrix pow(const Matrix& _matrix, const unsigned _degree)
{
		try
		{
			if (_degree > 0)
			{
				int i(1);
				Matrix tempo(_matrix);
				while(i < _degree)
				{
					tempo = tempo*tempo;
					i++;
				}
				return tempo;
			}
			else
			{
				throw std::string{"error: Incorrect argument for function 'pow'\n"};
			}
		}
		catch(const std::string _errorMessage)
		{
			std::cerr << _errorMessage;
			exit(ERROR_POW);
		}
}

bool operator ==(const Matrix& _Lmatrix, const Matrix& _Rmatrix)
{
	bool signal = true;
	if ((_Lmatrix.m_height == _Rmatrix.m_height) && (_Lmatrix.m_width == _Rmatrix.m_width))
	{
		for(int i(0); i < _Lmatrix.m_height; i++)
		{
			for(int j(0); j < _Lmatrix.m_width; j++)
			{
				if (_Lmatrix.m_ptr[i][j] != _Rmatrix.m_ptr[i][j])
				{
					signal = false;
					return signal;
				}
			}
		}
	}
	else
	{
		signal = false;
		return signal;
	}
}

int& Matrix::operator ()(const unsigned _i, const unsigned _j)
{
	return m_ptr[_i][_j];	
}
	
Matrix& Matrix::operator =(const Matrix& _matrix)
{	
	this->resize(_matrix.m_height, _matrix.m_width);
	for (int i(0); i < m_height; i++)
	{
		for (int j(0); j < m_width; j++)
		{
			this->set(i, j, _matrix.m_ptr[i][j]);
		}
	}
	return *this;
}

int main()
{
	//Объект класса можно объявить, передавая только одно значение. Создастся матрица 1 на 1 с этим значением (по умолчанию значение 0)
	{
		Matrix A(1);
		std::cout << "Вызов Matrix A(1):\n";
		A.print();
		std::cout << std::endl;
	}
	//Можно передать размеры матрицы и значение. Тогда создастся матрица соответствующего размера с этим значением (по умолчанию значение 0)
	{
		Matrix A(2, 3, 1);
		std::cout << "Вызов Matrix A(2, 3, 1):\n";
		A.print();
		std::cout << std::endl;
	}
	//Можно задать элементы матрицы вручную
	{
		Matrix A({
				{1, 2, 3},
				{4, 5, 6}
			});
		std::cout << "Вызов Matrix A({ {1, 2, 3}, {4, 5, 6} }):\n";
		A.print();
		std::cout << std::endl;

	//Можно скопировать готовую матрицу
		
		Matrix B(A);
		std::cout << "Вызов Matrix B(A):\n";
		B.print();
		std::cout << std::endl;

	//Готовую матрицу можно принудительно заполнить заданным числом

		B.fill(7);
		std::cout << "Вызов B.fill(7):\n";
		B.print();
		std::cout << std::endl;

	//Можно увеличить размеры матрицы, передавая требуемые параметры
		
		B.resize(3, 4);
		std::cout << "Вызов B.resize(3, 4):\n";
		B.print();
		std::cout << std::endl;

	//Можно и уменьшить размеры
	
		B.resize(3, 2);
		std::cout << "Вызов B.resize(3, 2):\n";
		B.print();
		std::cout << std::endl;

	//Можно транспонировать матрицу

		B.t();
		std::cout << "Вызов B.t():\n";
		B.print();
		std::cout << std::endl;
	
	//Можно вписать в матрицу вектор-столбец, передавая сам вектор и желаемую позицию (по умолчанию на первое место)

		B.addCol({1, 2}, 1);
		std::cout << "Вызов B.addCol({1, 2}, 1):\n";
		B.print();
		std::cout << std::endl;
	
	//Можно вписать в матрицу вектор-строку, передавая сам вектор и желаемую позицию (по умолчанию на первое место)

		B.addRow({5, 5, 5, 5}, 1);
		std::cout << "Вызов B.addRow({5, 5, 5, 5}, 1):\n";
		B.print();
		std::cout << std::endl;
	}
	//Можно складывать матрицы
	{
		Matrix A({
				{1, 2},
				{3, 4}
			});
		std::cout << "Вызов Matrix A({ {1, 2}, {3, 4} }):\n";
		A.print();
		std::cout << std::endl;
		Matrix B({
				{5, 6},
				{7, 8}
			});
		std::cout << "Вызов Matrix B({ {5, 6}, {7, 8} }):\n";
		B.print();
		std::cout << std::endl;
		{
			Matrix C(A + B);
			std::cout << "Вызов Matrix C(A + B):\n";
			C.print();
			std::cout << std::endl;
		}
	//Можно вычетать матрицы
		{
			Matrix C(A - B);
			std::cout << "Вызов Matrix C(A - B):\n";
			C.print();
			std::cout << std::endl;
		}
	//Можно перемножать матрицы
		{
			Matrix C(A*B);
			std::cout << "Вызов Matrix C(A*B):\n";
			C.print();
			std::cout << std::endl;
		}
	//Можно возвести матрицу в степень
		{
			Matrix C(pow(A, 2));
			std::cout << "Вызов Matrix C(pow(A, 2)):\n";
			C.print();
			std::cout << std::endl;
		}
	//Можно проверить матрицы на поэлементное соответствие
	
	std::cout << "Вызов A == B:\n";
	std::cout << (bool)(A == B) << std::endl;
	std::cout << std::endl;
	
	//Можно присвоить матрице значение другой матрицы
	B = A;
	std::cout << "Вызов B = A:\n";	
	std::cout << "Вызов B:\n";
	B.print();
	std::cout << std::endl;
		
	//Можно обращаться к элементам матрицы напрямую
	
	std::cout << "Вызов A(0, 1):\n";
	std::cout << A(0, 1) << std::endl;
	std::cout << std::endl;

	//Можно изменить значение элемента
	
	A(0, 1) = -1;
	std::cout << "Вызов A(0, 1) = -1:\n";
	std::cout << "Вызов A(0, 1):\n";
	std::cout << A(0, 1) << std::endl;
	std::cout << std::endl;
	}
	return SUCCES;
}

