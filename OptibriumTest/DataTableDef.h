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
    // Template class to simplify ToString
	std::stringstream StringStream;
	std::string String;
	StringStream << Value;
	String = StringStream.str();

	return String;
}

class TDataRow;
struct CompareDataRows
{
    // This is a functor that returns true if Row1 < Row2
	bool operator()( const TDataRow &Row1, const TDataRow &Row2 );
};

// Supported data types
enum DataValueType { dvtUnknown, dvtInt, dvtFloat, dvtString };

// This represents a value in the table
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

	// Comparison operators
	bool operator == ( const TDataValue &Incoming );
	bool operator != ( const TDataValue &Incoming );
	bool operator < ( const TDataValue &Incoming );
};

// This class represents a row of data as a multimap
class TDataRow
{
private:
    std::multimap< std::string, TDataValue >FRow;
public:
	TDataRow();
	TDataRow( const TDataRow &ToCopy ); // Copy constructor

	~TDataRow();

	void Insert( std::string Key, TDataValue Value );
	std::string TDataRow::GetKey( unsigned int Position ) const;
	TDataValue TDataRow::ValueByKey( std::string Key ) const;
	int ValueCount() const;

    // Comparison operators
	bool operator==(const TDataRow &Incoming);
	bool operator<( const TDataRow &Incoming );

	TDataRow &operator=(TDataRow Incoming); // Copy assignment

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
	TDataRow GetRow( unsigned int Row ) const;
	int RowCount() const ;

	//Operator, only need +=
	TDataTable & TDataTable::operator+=(const TDataTable &rhs);

	TDataTable SetUnion( TDataTable &Table1 );
	TDataTable SetDifference( TDataTable &Table1 );
	TDataTable Intersection( TDataTable &Table1 );
};



#endif
