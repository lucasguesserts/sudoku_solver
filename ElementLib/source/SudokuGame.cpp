#include <SudokuGame.h>

const unsigned SudokuGame::size = 9;

SudokuGame::SudokuGame(unsigned s)
{
	allocCells();
	allocRows();
	allocColumns();
	allocRectangles();
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

void SudokuGame::allocCells(void)
{
	cell.resize( this->size );
	for(unsigned row=0 ; row<this->size ; ++row)
	{
		cell[row].resize( ths->size );
	}
}

void SudokuGame::allocRows(void)
{
	this->row.resize( this->size );
	for(unsigned r=0 ; r<this->size ; ++r)
	{
		for(unsigned c=0 ; c<this->size ; ++c){
			this->row[r].addCell( this->cell[r][c] );
		}
	}
}

void SudokuGame::allocColumns(void)
{
	this->column.resize( this->size );
	for(unsigned c=0 ; c<this->size ; ++c)
	{
		for(unsigned r=0 ; r<this->size ; ++r){
			this->column[c].addCell( this->cell[r][c] );
		}
	}
}

void SudokuGame::allocRectangles(void)
{
	// resize vector
	this->rectangle.resize(Retangle::size);
	for(unsigned retangleRow=0 ; retangleRow<Retangle::size ; ++retangleRow)
	{
		this->rectangle[retangleRow].resize(Retangle::size);
	}
	// add Cells to each Rectangle
	for(unsigned retangleRow=0 ; retangleRow<Retangle::size ; ++retangleRow)
		for(unsigned retangleColumn=0 ; retangleColumn<Retangle::size ; ++retangleColumn)
			for(unsigned cellRowInRetangle=0 ; cellRowInRetangle<Retangle::size ; ++cellRowInRetangle)
				for(unsigned cellColumnInRetangle=0 ; cellColumnInRetangle<Retangle::size ; ++cellColumnInRetangle)
				{
					unsigned cellGlobalRow = cellRowInRetangle + Retangle::size*retangleRow;
					unsigned cellGlobalColumn = cellColumnInRetangle + Retangle::size*retangleColumn;
					this->rectangle[retangleRow][retangleColumn].addCell( this->cell[cellGlobalRow][cellGlobalColumn] );
				}
	return;
}
