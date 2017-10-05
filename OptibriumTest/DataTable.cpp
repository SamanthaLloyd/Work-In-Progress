
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

#pragma endregion

#pragma region TDataRow definition

TDataRow::TDataRow()
{
	
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

int TDataRow::ValueCount()
{
    return FRow.size();
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

int TDataTable::RowCount()
{
    return FRows.size();
}

#pragma endregion