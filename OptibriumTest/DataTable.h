#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <vector>


enum DataValueType { dvtUnknown, dvtInt, dvtFloat, dvtString };

class TDataValue
{
private:
	DataValueType FOriginalType;
	bool FSet;
	int FInt;
	float FFloat;
	std::string FString;

public:
	TDataValue();
	TDataValue(int ValueIn);
	TDataValue(float ValueIn);
	TDataValue(std::string ValueIn);

	~TDataValue();

	int AsInt();
	float AsFloat();
	std::string AsString();

	bool IsInt();
	bool IsFloat();
	bool IsString();

	bool Set(int ValueIn);
	bool Set(float ValueIn);
	bool Set(std::string ValueIn);
};

class TDataRow
{
private:
	std::multimap< std::string, TDataValue >FRow;
public:
	TDataRow();
	~TDataRow();
};

class TDataTable
{
private:
	std::vector< TDataRow >FRows;
public:
	TDataTable();
	~TDataTable();
};