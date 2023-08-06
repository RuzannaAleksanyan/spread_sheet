#ifndef S_SH
#define S_SH
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

#endif

