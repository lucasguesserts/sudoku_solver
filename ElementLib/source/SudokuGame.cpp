#include <SudokuGame.h>

SudokuGame::SudokuGame(unsigned s)
{
	allocCells(s);
	allocRows(s);
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

GroupPtrVector SudokuGame::getCellGroups(unsigned r , unsigned c) const
{
	return cell[r][c].getGroups();
}

Row SudokuGame::getRow(unsigned l)
{
	return this->row[l];
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

void SudokuGame::allocRows(unsigned s)
{
	this->row.resize( s );
	for(unsigned r=0 ; r<s ; ++r)
	{
		for(unsigned c=0 ; c<s ; ++c){
			this->row[r].addCell( this->cell[r][c] );
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
bool SudokuGame::isValid(void)
{
	bool vality = true;
	unsigned row, column;
	for( unsigned row=0 ; row<N_VALUES ; ++row )
	{
		for( unsigned column=0 ; column<N_VALUES ; ++column )
		{
			foreach(Group * g , this->getCellGroups(row,column) )
			{
				vality = g->isValid() && vality;
			}
		}
	}
	return vality;
}

void SudokuGame::solverForOnePossibleValue(void)
{
	bool aCellWasSet;
	unsigned row, column;
	unsigned uniquePossibleValue;
	do
	{
		aCellWasSet = false;
		for( unsigned row=0 ; row<N_VALUES ; ++row )
		{
			for( unsigned column=0 ; column<N_VALUES ; ++column )
			{
				if( this->getCellNumberOfPossibleValues(row,column) == 1 )
				{
					uniquePossibleValue = this->getCellUniquePossibleValue(row,column);
					this->setCellValue(row,column,uniquePossibleValue);
					aCellWasSet = true;
				}
			}
		}
	}while( aCellWasSet==true );
}

void SudokuGame::buildCheck(unsigned s)
{
	// default size for a Rectangle
	unsigned defaultSize = 3;

	// Check CellMatrix row number
	if ( this->cell.size() != s ) throw "CellMatrix row numbers wrong";

	// Check CellMatrix column number
	for( unsigned l=0 ; l<s ; ++l)
	{
		if ( this->cell[l].size() != s ) throw "CellMatrix column number wrong";
	}

	// Check RowVector size
	if ( this->row.size() != s ) throw "RowVector size wrong";

	// Check each RowVector size
	for( unsigned l=0 ; l<s ; ++l)
	{
		if ( this->row[l].getNumberOfCell() != s ) throw "Number of cells in row vector wrong";
	}

	// Check ColumnVector size
	if ( this->column.size() != s ) throw "ColumnVector size wrong";

	// Check each ColumnVector size
	for( unsigned c=0 ; c<s ; ++c)
	{
		if ( this->column[c].getNumberOfCell() != s ) throw "Number of cells in column vector wrong";
	}

	// Check RectangleMatrix row number
	if ( this->rectangle.size() != defaultSize ) throw "Number of rows in RectangleMatrix wrong";

	// Check each RectangleMatrix column number
	for(unsigned l=0 ; l<defaultSize ; ++l)
	{
		if ( this->rectangle[l].size() != defaultSize ) throw "Number of columns in RectangleMatrix wrong";
	}
}

void SudokuGame::setUsingArray(unsigned dataArray[])
{
	for (unsigned r=0 ; r<N_VALUES ; ++r)
	{
		for (unsigned c=0 ; c<N_VALUES ; ++c)
		{
			unsigned entry = N_VALUES*r + c;
			setCellValue(r,c,dataArray[entry]);
		}
	}
	return;
}

void SudokuGame::setUsingVector(vector<unsigned> data)
{
	for (unsigned r=0 ; r<N_VALUES ; ++r)
	{
		for (unsigned c=0 ; c<N_VALUES ; ++c)
		{
			unsigned entry = N_VALUES*r + c;
			setCellValue(r,c,data[entry]);
		}
	}
	return;
}

void SudokuGame::setUsingMatrix(vector< vector<unsigned> > data)
{
	for (unsigned r=0 ; r<N_VALUES ; ++r)
	{
		for (unsigned c=0 ; c<N_VALUES ; ++c)
		{
			setCellValue(r,c,data[r][c]);
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

bool operator==(SudokuGame lhs , SudokuGame rhs)
{
	unsigned r, c;
	for(r=0 ; r<N_VALUES ; ++r)
		for(c=0 ; c<N_VALUES ; ++c)
			if(lhs.getCellValue(r,c) != rhs.getCellValue(r,c)) return false;
	return true;
}
