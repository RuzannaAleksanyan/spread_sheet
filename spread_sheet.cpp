#include "spreadSheet..hpp"

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
