//---------------------------------------------------------------------------

#ifndef DataTableDefH
#define DataTableDefH

#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <vector>

//---------------------------------------------------------------------------

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
	TDataValue(const TDataValue &ToCopy);
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

	bool operator == ( const TDataValue &Incoming );
	bool operator != ( const TDataValue &Incoming );
	bool operator < ( const TDataValue &Incoming );

};

class TDataRow
{
private:

public:
	TDataRow();
	TDataRow( const TDataRow &ToCopy );
//    TDataRow( TDataRow &&ToCopy );
	~TDataRow();
    std::multimap< std::string, TDataValue >FRow;

	void Insert( std::string Key, TDataValue Value );
	TDataValue TDataRow::ValueByKey( std::string Key ) const;
	std::string TDataRow::GetKey( unsigned int Position ) const;
	int ValueCount() const;

	bool operator==(const TDataRow &Incoming);
	bool operator!=(const TDataRow &Incoming);
	TDataRow &operator=(TDataRow Incoming);  // Copy assignment
//	TDataRow &operator=(const TDataRow &&Incoming); // Move assignment
// 	friend bool operator<(const TDataRow &First, const TDataRow &Second);
	bool operator<( const TDataRow &Incoming );

	std::string ToString();
};

struct less_than_key
{
	bool operator()( const TDataRow &Row1, const TDataRow &Row2 );
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
	TDataRow *GetRow( unsigned int i );
	int RowCount() const ;
	TDataRow GetRow( unsigned int Row ) const;
	//Operators

	TDataTable & TDataTable::operator+=(const TDataTable &rhs);
	const TDataTable TDataTable::operator+(const TDataTable &OtherTable) const;

	void Sort();

	TDataTable SetUnion( TDataTable &Table1 );
	TDataTable SetDifference( TDataTable &Table1 );
	TDataTable Intersection( TDataTable &Table1 );
	std::string ToString();
};



#endif
