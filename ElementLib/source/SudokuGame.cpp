#include <SudokuGame.h>

const unsigned SudokuGame::size = 9;

SudokuGame::SudokuGame(unsigned s)
{
	allocCells();
	allocRows();
	allocColumns();
	allocRectangles();

	buildCheck();
}

unsigned SudokuGame::getCellValue(unsigned row , unsigned column) const
{
	return this->cell[row][column].getValue();
}

unsigned SudokuGame::getCellNumberOfPossibleValues(unsigned row , unsigned column) const
{
	return this->cell[row][column].getNumberOfPossibleValues();
}

unsigned SudokuGame::getCellUniquePossibleValue(unsigned row , unsigned column) const
{
	return cell[row][column].getUniquePossibleValue();
}

void SudokuGame::setCellValue(unsigned row , unsigned column , unsigned value)
{
	this->cell[row][column].setValue(value);
}

GroupPtrVector SudokuGame::getCellGroups(unsigned row , unsigned column) const
{
	return cell[row][column].getGroups();
}

bool SudokuGame::isValid(void)
{
	bool vality = true;
	for( unsigned row=0 ; row<this->size ; ++row )
		for( unsigned column=0 ; column<this->size ; ++column )
				vality = cell[row][column].isValid() && vality;
	return vality;
}

bool SudokuGame::isSolved(void)
{
	bool vality;
	vality = this->isValid();
	for( unsigned row=0 ; row<this->size ; ++row )
		for( unsigned column=0 ; column<this->size ; ++column )
				if( this->getCellValue(row,column)==0) vality=false;
	return vality;
}

void SudokuGame::solverForOnePossibleValue(void)
{
	bool aCellWasSet;
	unsigned uniquePossibleValue;
	do
	{
		aCellWasSet = false;
		for( unsigned row=0 ; row<this->size ; ++row )
		{
			for( unsigned column=0 ; column<this->size ; ++column )
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

void SudokuGame::set(const std::vector< std::vector<unsigned> > data)
{
	{// size verification
		if (data.size() != this->size)
			throw "Invalid matrix row size - set sudoku game values.";
		for(unsigned row=0 ; row<this->size ; ++row)
			if (data[row].size() != this->size)
				throw "Invalid matrix column size - set sudoku game values.";
	}
	for (unsigned row=0 ; row<this->size ; ++row)
	{
		for (unsigned column=0 ; column<this->size ; ++column)
		{
			setCellValue(row , column , data[row][column] );
		}
	}
	return;
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

void SudokuGame::set(const unsigned * const dataArray)
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

void SudokuGame::set(const vector<unsigned> data)
{
	if (data.size() != N_VALUES*N_VALUES)
		throw "Invalid vector size - set sudoku game values.";
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

void SudokuGame::createFile(const char * const fileName, const char * datasetName) const
{
	hid_t file;
	hid_t dataset, dataspace;
	const hid_t datatype = H5T_NATIVE_UINT;
	const hsize_t rank = 2;
	hsize_t dataspace_size[2];
	unsigned data[SudokuGame::size][SudokuGame::size];
	unsigned row, column;

	for (row=0 ; row<SudokuGame::size ; ++row)
		for(column=0 ; column<SudokuGame::size ; ++column)
			data[row][column] = this->getCellValue(row,column);

    file = H5Fcreate(fileName, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT); if(file<0) throw "Error creating file to write.";
	dataspace_size[0] = SudokuGame::size;
	dataspace_size[1] = SudokuGame::size;
	dataspace = H5Screate_simple(rank, dataspace_size, NULL); if(dataspace<0) throw "Error opening dataspace to save file.";
	dataset = H5Dcreate2(file, datasetName, datatype, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT); if(dataset<0) throw "Error opening dataset to save file.";
	H5Dwrite(dataset, datatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);

	H5Dclose(dataset);
	H5Sclose(dataspace);
	H5Fclose(file);
	return;
}

void SudokuGame::appendFile(const char * const fileName, const char * datasetName) const
{
	hid_t file;
	hid_t dataset, dataspace;
	const hid_t datatype = H5T_NATIVE_UINT;
	const hsize_t rank = 2;
	hsize_t dataspace_size[2];
	unsigned data[SudokuGame::size][SudokuGame::size];
	unsigned row, column;

	for (row=0 ; row<SudokuGame::size ; ++row)
		for(column=0 ; column<SudokuGame::size ; ++column)
			data[row][column] = this->getCellValue(row,column);

    file = H5Fopen(fileName, H5F_ACC_RDWR, H5P_DEFAULT); if(file<0) throw "Error opening file to write.";
	dataspace_size[0] = SudokuGame::size;
	dataspace_size[1] = SudokuGame::size;
	dataspace = H5Screate_simple(rank, dataspace_size, NULL); if(dataspace<0) throw "Error opening dataspace to save file.";
	dataset = H5Dcreate2(file, datasetName, datatype, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT); if(dataset<0) throw "Error opening dataset to save file.";
	H5Dwrite(dataset, datatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);

	H5Dclose(dataset);
	H5Sclose(dataspace);
	H5Fclose(file);
	return;
}

void SudokuGame::readFromFile(const char * const fileName, const char * datasetName)
{
	hid_t file;
	hid_t dataset;
	const hid_t datatype = H5T_NATIVE_UINT;
	unsigned data[SudokuGame::size][SudokuGame::size];
	unsigned row, column;

    file = H5Fopen(fileName, H5F_ACC_RDONLY, H5P_DEFAULT); if(file<0) throw "Error opening file to read.";
	dataset = H5Dopen2(file, datasetName, H5P_DEFAULT); if(dataset<0) throw "Error opening dataset to read file.";
	H5Dread(dataset, datatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, data );

	for (row=0 ; row<SudokuGame::size; ++row)
		for(column=0 ; column<SudokuGame::size ; ++column)
			this->setCellValue(row,column,data[row][column]);

    H5Dclose(dataset);
    H5Fclose(file);
	return;
}

bool operator==(SudokuGame lhs , SudokuGame rhs)
{
	unsigned r, c;
	for(r=0 ; r<SudokuGame::size ; ++r)
		for(c=0 ; c<SudokuGame::size ; ++c)
			if(lhs.getCellValue(r,c) != rhs.getCellValue(r,c)) return false;
	return true;
}
