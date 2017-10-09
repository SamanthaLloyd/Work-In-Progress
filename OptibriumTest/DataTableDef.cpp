//---------------------------------------------------------------------------

#pragma hdrstop

#include "DataTableDef.h"
#include "SysUtils.hpp"
#include <algorithm>
//---------------------------------------------------------------------------
#pragma package(smart_init)

bool CompareDataRows::operator()( const TDataRow &Row1, const TDataRow &Row2 )
{
	// This function returns true if Row1 is < Row2
	bool Result = false;

	// First inspect the number of items
    // If Row 1 has fewer than Row 2 no need to continue
	if( Row1.ValueCount() < Row2.ValueCount() )
		{
		Result = true;
		}

	if( !Result )
		{
		// Now look at the rows themselves
        // Compare 1 with 1, 2 with 2 as the multimap sorts out the order
		bool FoundDifference = false;
        // Stop if we find a difference. If Row1 is greater than Row2, there's no need to continue
		for( int i = 0; i < Row1.ValueCount() && !FoundDifference;  i++ )
			{
			std::string Key1 = Row1.GetKey(i);
			std::string Key2 = Row2.GetKey(i);
			// Compare the strings
			if( strcmp( Key1.c_str(), Key2.c_str() ) == 0 )
				{
                // Strings match so check the values
				if( Row1.ValueByKey( Key1 ) < Row2.ValueByKey( Key2 ) )
					{
					FoundDifference = true;
					Result = true;
					}
				else
					{
					// Row 1's value is not less than Row 2
                    // If they aren't equal then Row 1 must be larger, so we can stop looking
					if( Row1.ValueByKey( Key1 ) != Row2.ValueByKey( Key2 ) )
						{
						FoundDifference = true;
						}
					}

				}
			else
				{
                // Otherwise look at the string comparison
				if( strcmp( Key1.c_str(), Key2.c_str() ) < 0 )
					{
                    Result = true;
                    }
				}
			}
		}

	return Result;
}

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

int TDataValue::AsInt()
{
	// returns the data value as an int
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
		// this will round off
		Result = FFloat;
		break;
	}

	return Result;
}

float TDataValue::AsFloat()
{
	// returns the data value as a float
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
	// returns the data value as a string
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

// This set of functions tell you the original type of the value
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

bool TDataValue::operator==(const TDataValue &Incoming)
{
	// Returns true if Incoming has the same relevant values as 'this'

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
    // Inverse of ==
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
	else
		{

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

TDataRow::~TDataRow()
{
    FRow.clear();
}

void TDataRow::Insert( std::string Key, TDataValue Value )
{
	// Insert Key and Value into the Row

	// Not passing the key by reference saves us a type headache
    // Possible room for improvement
	FRow.insert( std::make_pair( Key, Value ) );
}

std::string TDataRow::GetKey( unsigned int Position ) const
{
	// Returns the Key at Position
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

TDataValue TDataRow::ValueByKey( std::string Key ) const
{
    // Returns the data value for the first instance of Key
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


TDataRow &TDataRow::operator=(TDataRow Incoming)
{
	// copy assignment
	if( this != &Incoming )
		{
        // clear existing
		FRow.clear();
		// copy the contents of the row
		FRow.insert(Incoming.FRow.begin(), Incoming.FRow.end());
		}
	return *this;
}

#pragma endregion

#pragma region TDataTable definition

TDataTable::TDataTable()
{

}

TDataTable::~TDataTable()
{
	Clear();
}

void TDataTable::Clear( )
{
	FRows.clear();
}

void TDataTable::Add( TDataRow &Row )
{
	FRows.push_back( Row );
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

TDataTable TDataTable::SetUnion( TDataTable &Table1 )
{
	// requires a sorted data set
	std::sort( FRows.begin(), FRows.end(), CompareDataRows() );
	std::sort( Table1.FRows.begin(), Table1.FRows.end(), CompareDataRows() );

	// Then use std function with CompareDataRows
	TDataTable OutputTable;
	std::set_union( FRows.begin(), FRows.end(), Table1.FRows.begin(), Table1.FRows.end(), std::back_inserter( OutputTable.FRows ), CompareDataRows() );
	return OutputTable;
}

TDataTable TDataTable::SetDifference( TDataTable &Table1  )
{
	// requires a sorted data set
	std::sort( FRows.begin(), FRows.end(), CompareDataRows() );
	std::sort( Table1.FRows.begin(), Table1.FRows.end(), CompareDataRows() );

	// Then use std function with CompareDataRows
	TDataTable OutputTable;
	std::set_difference( FRows.begin(), FRows.end(), Table1.FRows.begin(), Table1.FRows.end(), std::back_inserter( OutputTable.FRows ), CompareDataRows() );
	return OutputTable;
}


TDataTable TDataTable::Intersection( TDataTable &Table1)
{
	// requires a sorted data set
	std::sort( FRows.begin(), FRows.end(), CompareDataRows() );
	std::sort( Table1.FRows.begin(), Table1.FRows.end(), CompareDataRows() );

	// Then use std function with CompareDataRows
	TDataTable OutputTable;
	std::set_intersection( FRows.begin(), FRows.end(), Table1.FRows.begin(), Table1.FRows.end(), std::back_inserter( OutputTable.FRows ), CompareDataRows() );
	return OutputTable;
}

#pragma endregion
