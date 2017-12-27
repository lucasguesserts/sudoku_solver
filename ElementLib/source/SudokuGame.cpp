#include <SudokuGame.h>

SudokuGame::SudokuGame(unsigned s)
{
	allocCells(s);
	allocLines(s);
	allocColumns(s);
	allocRectangles();

	buildCheck(s);
}

Cell SudokuGame::getCell(unsigned r , unsigned c)
{
	return this->cell[r][c];
}

void SudokuGame::setCellValue(unsigned r , unsigned c , unsigned value)
{
	this->cell[r][c].setValue(value);
}

unsigned SudokuGame::getCellValue(unsigned r , unsigned c) const
{
	return this->cell[r][c].getValue();
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
	for(unsigned r=0 ; r<s ; ++r)
	{
		cell[r].resize( s );
	}
}

void SudokuGame::allocLines(unsigned s)
{
	this->line.resize( s );
	for(unsigned r=0 ; r<s ; ++r)
	{
		for(unsigned c=0 ; c<s ; ++c){
			this->line[r].addCell( this->cell[r][c] );
		}
	}
}

void SudokuGame::allocColumns(unsigned s)
{
	this->column.resize( s );
	for(unsigned c=0 ; c<s ; ++c)
	{
		for(unsigned r=0 ; r<s ; ++r){
			this->column[c].addCell( this->cell[r][c] );
		}
	}
}

void SudokuGame::allocRectangles(void)
{
	// r: rectangle number of rows
	// c: rectangle number of columns
	// s: game size
	unsigned defaultSize = 3;

	// resize rows and columns
	this->rectangle.resize(defaultSize);
	for(unsigned c=0 ; c<defaultSize ; ++c)
	{
		this->rectangle[c].resize(defaultSize);
	}

	// add Cells to each Rectangle
	for(unsigned r=0 ; r<defaultSize ; ++r)
	{
		for(unsigned c=0 ; c<defaultSize ; ++c)
		{
			for(unsigned cr=0 ; cr<defaultSize ; ++cr) // cr: Cell row
			{
				for(unsigned cc=0 ; cc<defaultSize ; ++cc) // cc: Cell Column
				{
					this->rectangle[r][c].addCell( this->cell[cr + defaultSize * r][cc + defaultSize * c] );
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
