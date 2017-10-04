
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
	char *ResultChar;
	std::string Result = "";
	switch (FOriginalType)
	{
	case dvtString:
		//Native
		Result = FString;
		break;
	case dvtInt:
		sprintf(ResultChar,"%d",FInt);
		Result = ResultChar;
		break;
	case dvtFloat:
		sprintf(ResultChar,"%f",FFloat);
		Result = ResultChar;
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

#pragma endregion

#pragma region TDataTable definition

TDataTable::TDataTable()
{

}

TDataTable::~TDataTable()
{

}

#pragma endregion