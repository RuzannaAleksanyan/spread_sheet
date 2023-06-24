#include <iostream>

class Cell
{
	public:
		virtual void setValue(const std::string& value) = 0;
		virtual std::string getValue() const = 0;
};

class IntCell : public Cell
{
	private:
		int m_value = 0;
	public:
		IntCell(int val) { m_value = val; }
		void setValue(const std::string& value) { m_value = std::stoi(value);}
		std::string getValue() const { return std::to_string(m_value); }
};

class DoubleCell : public Cell
{
	private:
		double m_value = 0.0;
	public:
		DoubleCell(double val) { m_value = val; }
		void setValue(const std::string& value) { m_value = std::stod(value);}
		std::string getValue() const { return std::to_string(m_value); };
};

class StringCell : public Cell
{
	private:
		std::string m_value;
	public:
		StringCell(std::string value) { m_value = value; }
		void setValue(const std::string& value) { m_value = value;}
		std::string getValue() const { return m_value; }
};

class SpreadSheet
{
	private:
		Cell*** m_cells;
		int m_row;
		int m_col;
	public:
		SpreadSheet(int row, int col);
		~SpreadSheet();

		void setRow(int row) { m_row = row; }
		void setCol(int col) { m_col = col; }
		int getRow() { return m_row; }
		int getCol() { return m_col; }

		Cell*** getCells();		
		void setCellAt(int row, int col, Cell* value);
		void addRow(int count = 1);
		void addColumn(int count = 1);
		Cell* getCellAt(int row, int col);	
};

int main()
{
	SpreadSheet ob1(2, 3);
    IntCell ob2(88);
    DoubleCell ob3(1.5);
	StringCell ob4("hello");
    ob1.setCellAt(1, 1, &ob3);
    ob1.setCellAt(0, 0, &ob2);
	ob1.setCellAt(0, 1, &ob4);
    std::cout << ob1.getCellAt(0, 0)->getValue() << " " << ob1.getCellAt(1, 1)->getValue();
	std::cout << " " << ob1.getCellAt(0, 1)->getValue() << std::endl;
	return 0;
}

Cell* SpreadSheet::getCellAt(int row, int col)
{
	if(row < 0 || row >= SpreadSheet::getRow() || col < 0 || col >= SpreadSheet::getCol())
	{
		throw std::out_of_range("error");
	}
	return m_cells[row][col];
}

void SpreadSheet::setCellAt(int row, int col, Cell* value)
{
    if (row < 0 || row >= SpreadSheet::getRow() || col < 0 || col >= SpreadSheet::getCol())
    {
        throw std::out_of_range("error");
    }
    m_cells[row][col] = value;
}

Cell*** SpreadSheet::getCells()
{
	return m_cells;
}

void SpreadSheet::addColumn(int count)
{
	if(count < 0) 
	{
        return;
    }

	Cell*** tmp = new Cell**[SpreadSheet::getRow()];
	for(int i = 0; i < SpreadSheet::getRow(); ++i)
	{
		tmp[i] = new Cell*[SpreadSheet::getCol() + count];
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
	delete[] m_cells;
	m_cells = tmp;
	tmp = nullptr;

	SpreadSheet::setCol(SpreadSheet::getCol() + count);
}

void SpreadSheet::addRow(int count)
{
	if(count < 0) 
	{
        return;
    }

	Cell*** tmp = new Cell**[count + SpreadSheet::getRow()];
	for(int i = 0; i < count + SpreadSheet::getRow(); ++i)
	{
		tmp[i] = new Cell*[SpreadSheet::getCol()];
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
	delete[] m_cells;
	m_cells = tmp;
	tmp = nullptr;

	SpreadSheet::setRow(SpreadSheet::getRow() + count);
}

SpreadSheet::SpreadSheet(int row, int col)
{
    m_cells = new Cell**[row];

    for(int i = 0; i < row; ++i)
    {
        m_cells[i] = new Cell*[col];
    }
    SpreadSheet::setRow(row);
    SpreadSheet::setCol(col);
}

SpreadSheet::~SpreadSheet()
{
    for(int i = 0; i < SpreadSheet::getRow(); ++i)
    {
        delete[] m_cells[i];
    }
    delete []  m_cells;
}

