#include <SudokuGame.h>

SudokuGame::SudokuGame(unsigned s)
{
	allocCells(s);
	allocLines(s);
	allocColumns(s);
	allocRectangles();

	buildCheck(s);
}

Cell SudokuGame::getCell(unsigned l , unsigned c)
{
	return this->cell[l][c];
}

void SudokuGame::setCellValue(unsigned l , unsigned c , unsigned value)
{
	this->cell[l][c].setValue(value);
}

unsigned SudokuGame::getCellValue(unsigned l , unsigned c) const
{
	return this->cell[l][c].getValue();
}

unsigned SudokuGame::getCellNumberOfPossibleValues(unsigned l , unsigned c) const
{
	return this->cell[l][c].getNumberOfPossibleValues();
}

unsigned SudokuGame::getCellUniquePossibleValue(unsigned l , unsigned c) const
{
	if( this->getCellNumberOfPossibleValues(l,c) == 1)
	{
		// return the first and unique possible value
		return cell[l][c].getPossibleValue(0);
	}
	else throw "Cell with more than one possible value";
}

Line SudokuGame::getLine(unsigned l)
{
	return this->line[l];
}

Column SudokuGame::getColumn(unsigned c)
{
	return this->column[c];
}

Rectangle SudokuGame::getRectangle(unsigned l , unsigned c)
{
	return this->rectangle[l][c];
}

void SudokuGame::allocCells(unsigned s)
{
	// s : game size
	cell.resize( s );
	for(unsigned l=0 ; l<s ; ++l)
	{
		for(unsigned c=0 ; c<s ; ++c)
		{
			// x : column
			// y : line
			Cell newCell(c,l);
			this->cell[l].push_back( newCell );
		}
	}
}

void SudokuGame::allocLines(unsigned s)
{
	// Resize the 'line' vector to have size 's'.
	// For each line 'l', add all line 'l' cells.
	// To add all line 'l' cells, it is necessary to
	// add the cell of each column 'c'.
	this->line.resize( s );
	for(unsigned l=0 ; l<s ; ++l)
	{
		for(unsigned c=0 ; c<s ; ++c){
			this->line[l].addCell( this->cell[l][c] );
		}
	}
}

void SudokuGame::allocColumns(unsigned s)
{
	// Resize the 'column' vector to have size 's'.
	// For each column 'c', add all column 'c' cells.
	// To add all column 'c' cells, it is necessary to
	// add the cell of each line 'l'.
	this->column.resize( s );
	for(unsigned c=0 ; c<s ; ++c)
	{
		for(unsigned l=0 ; l<s ; ++l){
			this->column[c].addCell( this->cell[l][c] );
		}
	}
}

void SudokuGame::allocRectangles(void)
{
	// l: rectangle number of lines
	// c: rectangle number of columns
	// s: game size
	unsigned defaultSize = 3;

	// resize lines and columns
	this->rectangle.resize(defaultSize);
	for(unsigned c=0 ; c<defaultSize ; ++c)
	{
		this->rectangle[c].resize(defaultSize);
	}

	// add Cells to each Rectangle
	for(unsigned l=0 ; l<defaultSize ; ++l)
	{
		for(unsigned c=0 ; c<defaultSize ; ++c)
		{
			for(unsigned cl=0 ; cl<defaultSize ; ++cl) // cl: Cell Line
			{
				for(unsigned cc=0 ; cc<defaultSize ; ++cc) // cc: Cell Column
				{
					this->rectangle[l][c].addCell( this->cell[cl + defaultSize * l][cc + defaultSize * c] );
				}
			}
		}
	}
}

//// ############### solvers ###############
//void SudokuGame::solverForOnePossibleValue(void)
//{
//	bool changed;
//	do
//	{
//		for( unsigned l=0 ; l<N_VALUES ; ++l )
//		{
//			for( unsigned c=0 ; c<N_VALUES ; ++c )
//			{
//				PossibleValues pv = this->getCell(l,c).getPossibleValues();
//				if( pv.size() == 1 )
//				{

//				}
//			}
//		}
//	}while( changed==true );
//}

void SudokuGame::buildCheck(unsigned s)
{
	// default size for a Rectangle
	unsigned defaultSize = 3;

	// Check CellMatrix line number
	if ( this->cell.size() != s ) throw "CellMatrix line numbers wrong";

	// Check CellMatrix column number
	for( unsigned l=0 ; l<s ; ++l)
	{
		if ( this->cell[l].size() != s ) throw "CellMatrix column number wrong";
	}

	// Check LineVector size
	if ( this->line.size() != s ) throw "LineVector size wrong";

	// Check each LineVector size
	for( unsigned l=0 ; l<s ; ++l)
	{
		if ( this->line[l].getNumberOfCell() != s ) throw "Number of cells in line vector wrong";
	}

	// Check ColumnVector size
	if ( this->column.size() != s ) throw "ColumnVector size wrong";

	// Check each ColumnVector size
	for( unsigned c=0 ; c<s ; ++c)
	{
		if ( this->column[c].getNumberOfCell() != s ) throw "Number of cells in column vector wrong";
	}

	// Check RectangleMatrix line number
	if ( this->rectangle.size() != defaultSize ) throw "Number of lines in RectangleMatrix wrong";

	// Check each RectangleMatrix column number
	for(unsigned l=0 ; l<defaultSize ; ++l)
	{
		if ( this->rectangle[l].size() != defaultSize ) throw "Number of columns in RectangleMatrix wrong";
	}
}

void SudokuGame::setUsingArray(unsigned dataArray[9][9])
{
	for (unsigned i=0 ; i<N_VALUES ; ++i)
	{
		for (unsigned j=0 ; j<N_VALUES ; ++j)
		{
			setCellValue(i,j,dataArray[i][j]);
		}
	}
	return;
}

void SudokuGame::write(const char * const fileName)
{
	herr_t err;
	hid_t file;
	hid_t dataset, dataspace, datatype;
	hsize_t rank = 2;
	hsize_t dataspace_size[2];
	unsigned data[N_VALUES][N_VALUES];
	unsigned row, column;

	for (row=0 ; row<N_VALUES ; ++row)
	{
		for(column=0 ; column<N_VALUES ; ++column)
		{
			data[row][column] = this->getCellValue(row,column);
		}
	}


    file = H5Fcreate(fileName, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
	dataspace_size[0] = N_VALUES;
	dataspace_size[1] = N_VALUES;
    dataspace = H5Screate_simple(rank, dataspace_size, NULL);
    dataset = H5Dcreate2(file, "sudoku game", H5T_NATIVE_INT, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Dwrite(dataset, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);

    H5Dclose(dataset);
    H5Sclose(dataspace);
    H5Fclose(file);
	return;
}

void SudokuGame::read(const char * const fileName)
{
	herr_t err;
	hid_t file;
	hid_t dataset, dataspace, datatype;
	hsize_t rank = 2;
	hsize_t dataspace_size[2];
	unsigned data[N_VALUES][N_VALUES];
	unsigned row, column;

    file = H5Fopen(fileName, H5F_ACC_RDONLY, H5P_DEFAULT);
    dataset = H5Dopen2(file, "sudoku game", H5P_DEFAULT);
	err = H5Dread( dataset, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data );

	for (row=0 ; row<N_VALUES ; ++row)
	{
		for(column=0 ; column<N_VALUES ; ++column)
		{
			this->setCellValue(row,column,data[row][column]);
		}
	}

    H5Dclose(dataset);
    H5Fclose(file);
	return;
}
