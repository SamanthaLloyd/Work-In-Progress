#pragma once
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <vector>

template<class T>
std::string TToString(T Value)
{
	std::stringstream StringStream;
	std::string String;
	StringStream << Value;
	String = StringStream.str();

	return String;
}

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

	void Insert( std::string Key, TDataValue Value );
	TDataValue *TDataRow::ValueByKey( std::string Key );
	std::string TDataRow::GetKey( int Position );
    int ValueCount();
};

class TDataTable
{
private:
	std::vector< TDataRow >FRows;
public:
	TDataTable();
	~TDataTable();

	void Clear( );
	void Add( TDataRow &Row );
	TDataRow *GetRow( int i );
	int RowCount();
};