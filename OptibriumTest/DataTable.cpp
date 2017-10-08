
#include "DataTable.h"
#include "SysUtils.hpp"


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
				case dvtFloat:
					if( this->FFloat == Incoming.FFloat )
						{
						Result = true;
						}
				case dvtString:
					if( this->FString == Incoming.FString )
						{
						Result = true;
						}
				default:
					Result = true;
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

int TDataValue::Compare( const TDataValue &Incoming )
{
	int Result = 0;
	// Returns 0 if this is the same as Incoming
	// If data types are different, returns this datatype - incoming data type
	// If data types are the same, returns this vaue - incoming value

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
	FRow = ToCopy.FRow;
}

TDataRow::~TDataRow()
{

}

void TDataRow::Insert( std::string Key, TDataValue Value )
{
	// Not passing the key by reference saves us a type headache
    // Possible room for improvement
	FRow.insert( std::make_pair( Key, Value ) );
}

TDataValue *TDataRow::ValueByKey( std::string Key )
{
	TDataValue *Result = NULL;

	if( Key.length() )
		{
		std::multimap< std::string, TDataValue >::iterator it;
		it = FRow.find( Key );
		if( it != FRow.end() )
			{
			Result = &it->second;
			}
		}
	return Result;
}

std::string TDataRow::GetKey( int Position )
{
	std::string Result = "";
	if( FRow.size() > Position && Position >= 0 )
		{
		std::multimap< std::string, TDataValue >::iterator it;
		it = FRow.begin();
		int Count = 0;
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
		if( &it1 != &it2 )
			{
			Result = false;
			}

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

TDataRow *TDataTable::GetRow( int Row )
{
	TDataRow *Result = NULL;
	if( FRows.size() > Row && Row >= 0 )
		{
		Result = &FRows.at( Row );

		}
	return Result;
}

TDataRow TDataTable::GetRow( int Row ) const
{
	TDataRow Result;
	if( FRows.size() > Row && Row >= 0 )
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

	// This will add the contents of rhs to this
	for( int Incoming = 0; Incoming < rhs.RowCount(); Incoming++ )
		{
		// Look for this row in the table
		bool Found = false;
		for( int Current = 0; Current < *this.RowCount() && !Found; Current++ )
			{
			if( rhs.GetRow( Incoming ) == *this.GetRow( Current ) )
				{
				Found = true;
				}
			}

		if( !Found )
			{
			// It's not in there, make a copy of it & insert it into our table
			FRows.push_back( TDataRow( rhs.GetRow( Incoming ) ) );
			}
		}
	return *this
}


const TDataTable TDataTable::operator+(const TDataTable &OtherTable) const
{
	// use the += operator to simplify this
	return TDataTable(*this) += OtherTable;
}


#pragma endregion