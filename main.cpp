#include "spreadSheet..hpp"

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
