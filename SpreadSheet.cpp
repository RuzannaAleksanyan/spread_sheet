#include <iostream>

class Cell
{
	private:
		std::string m_value;
	public:
		void setValue(std::string value) { m_value = value; }
		std::string getValue() const { return m_value; }
		
		int toInt();
		double toDouble();
		std::string toString();
};

class SpreadSheet
{
	private:
		Cell** m_cells;
		int m_row;
		int m_col;
		void setRow(int row) { m_row = row; }
		void setCol(int col) { m_col = col; }
		int getRow() { return m_row; }
		int getCol() { return m_col; }

	public:
		~SpreadSheet();
		SpreadSheet(int row, int col);

		Cell** getCells();		
		void setCellAt(int row, int col, const std::string& value);
		void setCellAt(int row, int col, Cell* value);
		void addRow(int count = 1);
		void addColumn(int count = 1);
		Cell getCellAt(int row, int col);	

};

int main()
{
	SpreadSheet obj(3, 3);
	obj.setCellAt(1, 1, "hello");
	std::cout << (obj.getCellAt(1, 1)).getValue();
	return 0;
}

Cell SpreadSheet::getCellAt(int row, int col)
{
	if(row < 0 || row > SpreadSheet::getRow() || col < 0 || col > SpreadSheet::getCol())
	{
		throw std::out_of_range("error");
	}
	return m_cells[row][col];
}

void SpreadSheet::setCellAt(int row, int col, Cell* value)
{
	m_cells[row][col] = *value; 	
}

Cell** SpreadSheet::getCells()
{
	return m_cells;
}

void SpreadSheet::setCellAt(int row, int col, const std::string& value)
{
	if(row < 0 || row > SpreadSheet::getRow() || col < 0 || col > SpreadSheet::getCol())
	{
		throw std::out_of_range("error");
	}
	m_cells[row][col].setValue(value);
}

void SpreadSheet::addColumn(int count)
{
	Cell** tmp;
	for(int i = 0; i < SpreadSheet::getRow(); ++i)
	{
		tmp[i] = new Cell[SpreadSheet::getCol() + count];
	}
	
	for(int i = 0; i < SpreadSheet::getRow(); ++i)
	{
		for(int j = 0; j < SpreadSheet::getCol(); ++j)
		{
			tmp[i][j] = m_cells[i][j];
		}
	}
	for(int i = 0; i < SpreadSheet::getRow(); ++i)
	{
		delete[] m_cells[i];
	}
	delete m_cells;
	m_cells = tmp;
	tmp = nullptr;
	SpreadSheet::setCol(SpreadSheet::getCol() + count);
}

void SpreadSheet::addRow(int count)
{
	Cell** tmp;
	tmp = new Cell*[count + SpreadSheet::getRow()];

	for(int i = 0; i < SpreadSheet::getRow(); ++i)
	{
		for(int j = 0; j < SpreadSheet::getCol(); ++j)
		{
			tmp[i][j] = m_cells[i][j];
		}
	}
	for(int i = 0; i < SpreadSheet::getRow(); ++i)
	{
		delete[] m_cells[i];
	}
	delete m_cells;
	m_cells = tmp;
	tmp = nullptr;
	SpreadSheet::setRow(SpreadSheet::getRow() + count);
}

int Cell::toInt()
{ 
	return std::stoi(m_value);
}

double Cell::toDouble()
{
	return std::stod(m_value);
}

std::string Cell::toString()
{
	return m_value;
}

SpreadSheet::SpreadSheet(int row, int col)
{
	m_cells = new Cell*[row];

	for(int i = 0; i < row; ++i)
	{
		m_cells[i] = new Cell[col];
	}
	setRow(row);
	setCol(col);
}

SpreadSheet::~SpreadSheet()
{
	for(int i = 0; i < SpreadSheet::getRow(); ++i)
	{
			delete m_cells[i];
	}

	delete []  m_cells;
}
