//---------------------------------------------------------------------------

#pragma hdrstop

#include "DataTableDef.h"
#include "SysUtils.hpp"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)


#pragma region TDataValue definition

TDataValue::TDataValue()
{
	// Set everything to initial variables
	FOriginalType = dvtUnknown;
	FSet = false;
	FInt = 0;
	FFloat = 0.0;
	FString = "";
}

TDataValue::TDataValue(const TDataValue &ToCopy)
{
	// Copy constructor
    TDataValue();
	FOriginalType = ToCopy.FOriginalType;
	FSet = ToCopy.FSet;
	FInt = ToCopy.FInt;
	FFloat = ToCopy.FFloat;
	FString = ToCopy.FString;

}

TDataValue::TDataValue(int ValueIn)
{
	TDataValue();
	Set(ValueIn);
}
TDataValue::TDataValue(float ValueIn)
{
	TDataValue();
	Set(ValueIn);
}
TDataValue::TDataValue(std::string ValueIn)
{
	TDataValue();
	Set(ValueIn);
}

TDataValue::~TDataValue()
{

}

bool TDataValue::Set(int ValueIn)
{
	// Set this as an int
	FOriginalType = dvtInt;
	FInt = ValueIn;
	FSet = true;
	return FSet;
}
bool TDataValue::Set(float ValueIn)
{
	// set this as a float
	FOriginalType = dvtFloat;
	FFloat = ValueIn;
	FSet = true;
	return FSet;
}

bool TDataValue::Set(std::string ValueIn)
{
	// set this as a string
	FOriginalType = dvtString;
	FString = ValueIn;
	FSet = true;
	return FSet;
}

int TDataValue::AsInt()
{
	int Result = -1;
	switch (FOriginalType)
	{
	case dvtString:
		// translate it
		Result = atoi(FString.c_str());
		break;
	case dvtInt:
		// Native
		Result = FInt;
		break;
	case dvtFloat:
		// this will round off, but I guess that's what we want?
		Result = FFloat;
		break;
	}

	return Result;
}

float TDataValue::AsFloat()
{
	int Result = -1.0;
	switch (FOriginalType)
	{
	case dvtString:
		// translate it
		Result = atof(FString.c_str());
		break;
	case dvtInt:
		// Translate
		Result = FInt;
		break;
	case dvtFloat:
		//Native
		Result = FFloat;
		break;
	}

	return Result;
}

std::string TDataValue::AsString()
{
	std::string Result = "";
	switch (FOriginalType)
	{
	case dvtString:
		//Native
		Result = FString;
		break;
	case dvtInt:
		Result = TToString( FInt );
		break;
	case dvtFloat:
		Result = TToString( FFloat );
		break;
	}
	return Result;
}

bool TDataValue::IsInt()
{
	if (FOriginalType == dvtInt)
		return true;
	else
		return false;
}
bool TDataValue::IsFloat()
{
	if (FOriginalType == dvtFloat)
		return true;
	else
		return false;
}
bool TDataValue::IsString()
{
	if (FOriginalType == dvtString)
		return true;
	else
		return false;
}

bool TDataValue::operator==(const TDataValue &Incoming)
{
	bool Result = false;
	if( this == &Incoming )
		{
		// Check for self equalling
		Result = true;
		}
	else
		{
		//Check the relevant properties
		if( this->FSet == Incoming.FSet &&
			this->FOriginalType == Incoming.FOriginalType )
			{
			switch( this->FOriginalType )
				{
				case dvtInt:
					if( this->FInt == Incoming.FInt )
						{
						Result = true;
						}
					break;
				case dvtFloat:
					if( this->FFloat == Incoming.FFloat )
						{
						Result = true;
						}
					break;
				case dvtString:
					if( this->FString == Incoming.FString )
						{
						Result = true;
						}
					break;
				default:
					Result = true;
                    break;
				}
			}
		}
	return Result;
}

bool TDataValue::operator!=(const TDataValue &Incoming)
{
	bool Result = true;
	if( *this == Incoming )
		{
		Result = false;
		}
	return Result;
}

bool TDataValue::operator<(const TDataValue &Incoming)
{
	bool Result = false;
    if( this == &Incoming )
		{
		// Check for self equalling
		Result = false;
		}

	// If 'this' isn't set but incoming is
	// or the types are different
	// then the result holds true
	if( this->FSet < Incoming.FSet ||
		( this->FSet == Incoming.FSet && this->FOriginalType < Incoming.FOriginalType ) )
		{
		Result = true;
		}

	// If both are set and the same type, compare the types
	if( this->FSet == Incoming.FSet &&
		this->FOriginalType == Incoming.FOriginalType )
		{
		switch( this->FOriginalType )
			{
			case dvtInt:
				if( this->FInt < Incoming.FInt )
					{
					Result = true;
					}
				break;
			case dvtFloat:
				if( this->FFloat < Incoming.FFloat )
					{
					Result = true;
					}
				break;
			case dvtString:
				if( this->FString < Incoming.FString )
					{
					Result = true;
					}
				break;
			default:
				Result = true;
				break;
			}
		}
	return Result;
}

#pragma endregion

#pragma region TDataRow definition

TDataRow::TDataRow()
{

}

TDataRow::TDataRow( const TDataRow &ToCopy )
{
	// Copy constructor
	FRow.clear();
	FRow.insert(ToCopy.FRow.begin(), ToCopy.FRow.end());
}
           /*
TDataRow::TDataRow( TDataRow &&ToCopy )
{
	// Copy constructor
	FRow.clear();
	FRow.insert(ToCopy.FRow.begin(), ToCopy.FRow.end());
}          */

TDataRow::~TDataRow()
{
    FRow.clear();
}

void TDataRow::Insert( std::string Key, TDataValue Value )
{
	// Not passing the key by reference saves us a type headache
    // Possible room for improvement
	FRow.insert( std::make_pair( Key, Value ) );
}

TDataValue TDataRow::ValueByKey( std::string Key ) const
{
	TDataValue Result;

	if( Key.length() )
		{
		std::multimap< std::string, TDataValue >::const_iterator it;
		it = FRow.find( Key );
		if( it != FRow.end() )
			{
			Result = it->second;
			}
		}
	return Result;
}

std::string TDataRow::GetKey( unsigned int Position ) const
{
	std::string Result = "";
	if( FRow.size() > Position )
		{
		std::multimap< std::string, TDataValue >::const_iterator it;
		it = FRow.begin();
		unsigned int Count = 0;
		while( Count != Position && Count < FRow.size() )
			{
			it++;
			Count++;
			}
		Result = it->first;
		}
	return Result;
}

int TDataRow::ValueCount() const
{
	return FRow.size();
}

bool TDataRow::operator==(const TDataRow &Incoming)
{
	// Compare each item in the map in turn
	// Order is defined by map by key sort
	// 1 to 1, 2 to 2 etc
	bool Result = true;
	std::multimap< std::string, TDataValue >::const_iterator it1 = FRow.begin();
	std::multimap< std::string, TDataValue >::const_iterator it2 = Incoming.FRow.begin();
	for( ; it1 != FRow.end() && it2 != Incoming.FRow.end() && Result; it1++, it2++ )
		{
		TDataValue Temp1( it1->second );
		TDataValue Temp2( it2->second );
		if( it1->first != it2->first || Temp1 != Temp2 )
			{
			Result = false;
			}

		}
	return Result;
}

TDataRow &TDataRow::operator=(TDataRow Incoming)
{
	// copy assignment
	if( this != &Incoming )
		{
		// copy the contents of the row
		FRow.clear();
		FRow.insert(Incoming.FRow.begin(), Incoming.FRow.end());
		}
	return *this;
}

              /*
TDataRow &TDataRow::operator=(const TDataRow &&Incoming)
{
	return *this = Incoming;
}
											   /*
TDataRow &TDataRow::operator=(TDataRow Incoming)
{
    return this = Incoming;
}        */
			 /*
bool operator<(const TDataRow &First, const TDataRow &Second)
{
	// this is < Incoming if we compare keys or values.
	bool Result = true;
	std::multimap< std::string, TDataValue >::const_iterator it1 = First.FRow.begin();
	std::multimap< std::string, TDataValue >::const_iterator it2 = Second.FRow.begin();
	for( ; it1 != First.FRow.end() && it2 != Second.FRow.end() && Result; it1++, it2++ )
		{
		std::string TmpStr1 = it1->first;
		std::string TmpStr2 = it2->first;
		TDataValue Temp1( it1->second );
		TDataValue Temp2( it2->second );
		if(
		if( it1->first >= it2->first && !(Temp1 < Temp2 ) )
			{
			Result = false;
			}

		}
	return Result;
}         */

bool TDataRow::operator<( const TDataRow &Incoming )
{
	bool Result = true;
	std::multimap< std::string, TDataValue >::const_iterator it1 = this->FRow.begin();
	std::multimap< std::string, TDataValue >::const_iterator it2 = Incoming.FRow.begin();
	for( ; it1 != this->FRow.end() && it2 != Incoming.FRow.end() && Result; it1++, it2++ )
		{
		TDataValue Temp1( it1->second );
		TDataValue Temp2( it2->second );
		if( it1->first >= it2->first && !(Temp1 < Temp2) )
			{
			Result = false;
			}
		}
	return Result;
}

std::string TDataRow::ToString()
{
	std::string Result = "";

	std::multimap< std::string, TDataValue >::iterator it1 = this->FRow.begin();
	for( ; it1 != this->FRow.end(); it1++ )
		{
        Result += "Header: " + it1->first + ". Value: " + it1->second.AsString() + "\r\n";
        }
    return Result;
}

#pragma endregion

#pragma region TDataTable definition

TDataTable::TDataTable()
{

}

TDataTable::~TDataTable()
{

}

void TDataTable::Add( TDataRow &Row )
{
	FRows.push_back( Row );
}

void TDataTable::Clear( )
{
	FRows.clear();
}

TDataRow *TDataTable::GetRow( unsigned int Row )
{
	TDataRow *Result = NULL;
	if( FRows.size() > Row )
		{
		Result = &FRows.at( Row );

		}
	return Result;
}

TDataRow TDataTable::GetRow( unsigned int Row ) const
{
	TDataRow Result;
	if( FRows.size() > Row )
		{
		Result = FRows.at( Row );

		}
	return Result;
}

int TDataTable::RowCount() const
{
	return FRows.size();
}

// Operators

TDataTable & TDataTable::operator+=(const TDataTable &rhs)
{
	// Add one table to this table
	FRows.insert( FRows.end(), rhs.FRows.begin(), rhs.FRows.end() );

	return *this;
}


const TDataTable TDataTable::operator+(const TDataTable &OtherTable) const
{
	// use the += operator to simplify this
	return TDataTable(*this) += OtherTable;
}

#pragma endregion

bool less_than_key::operator()( const TDataRow &Row1, const TDataRow &Row2 )
{
	bool Result = false;

	if( Row1.ValueCount() < Row2.ValueCount() )
		{
		Result = true;
		}

	if( !Result )
		{
		bool FoundDifference = false;
		for( int i = 0; i < Row1.ValueCount() && !FoundDifference;  i++ )
			{
			std::string Key1 = Row1.GetKey(i);
			std::string Key2 = Row2.GetKey(i);
			if( strcmp( Key1.c_str(), Key2.c_str() ) == 0 )
				{
				if( Row1.ValueByKey( Key1 ) < Row2.ValueByKey( Key2 ) )
					{
					FoundDifference = true;
					Result = true;
					}
				else
					{
					if( Row1.ValueByKey( Key1 ) != Row2.ValueByKey( Key2 ) )
						{
						FoundDifference = true;
						}
                    }

				}
			else
				{
				Result = strcmp( Key1.c_str(), Key2.c_str() );
                }
            }
        }

	return Result;
}

#pragma region Other functions

void TDataTable::Sort()
{
	std::sort( FRows.begin(), FRows.end(), less_than_key() );
}

TDataTable TDataTable::SetUnion( TDataTable &Table1 )
{
	// Use stl::set_union
	// requires a sorted data set
	std::sort( FRows.begin(), FRows.end(), less_than_key() );
	std::sort( Table1.FRows.begin(), Table1.FRows.end(), less_than_key() );

	TDataTable OutputTable;
	std::set_union( FRows.begin(), FRows.end(), Table1.FRows.begin(), Table1.FRows.end(), std::back_inserter( OutputTable.FRows ), less_than_key() );
	return OutputTable;
}

TDataTable TDataTable::SetDifference( TDataTable &Table1  )
{
	// requires a sorted data set
	std::sort( FRows.begin(), FRows.end(), less_than_key() );
	std::sort( Table1.FRows.begin(), Table1.FRows.end(), less_than_key() );

	TDataTable OutputTable;
	std::set_difference( FRows.begin(), FRows.end(), Table1.FRows.begin(), Table1.FRows.end(), std::back_inserter( OutputTable.FRows ), less_than_key() );
	return OutputTable;
}


TDataTable TDataTable::Intersection( TDataTable &Table1)
{
	// requires a sorted data set	std::sort( Table1.FRows.begin(), Table1.FRows.end() );
	std::sort( FRows.begin(), FRows.end(), less_than_key() );
	std::sort( Table1.FRows.begin(), Table1.FRows.end(), less_than_key() );

	TDataTable OutputTable;
	std::set_intersection( FRows.begin(), FRows.end(), Table1.FRows.begin(), Table1.FRows.end(), std::back_inserter( OutputTable.FRows ), less_than_key() );
	return OutputTable;
}

std::string TDataTable::ToString()
{
	std::string Result;

	Result = "Grid:\r\n";
	for( unsigned int i = 0; i < FRows.size(); i++ )
		{
		Result += "Row " + TToString(i) + ":\r\n";
		Result += FRows[i].ToString();
		}

	return Result;
}



#pragma endregion