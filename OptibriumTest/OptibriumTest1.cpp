//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "OptibriumTest1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TTestForm *TestForm;
//---------------------------------------------------------------------------
__fastcall TTestForm::TTestForm(TComponent* Owner)
	: TForm(Owner)
{
	PopulateSourceDataGrids();
}
//---------------------------------------------------------------------------
void __fastcall TTestForm::PopulateSourceDataGrids()
{
	//Populating the 4 grids

	// Grid 1
	TColumn *Grid1Column1 = new TColumn(DataGrid1);
	Grid1Column1->Header = "Molecule";
	DataGrid1->Model->InsertColumn( 0, Grid1Column1 );

	TColumn *Grid1Column2 = new TColumn(DataGrid1);
	Grid1Column2->Header = "Solubility";
	DataGrid1->Model->InsertColumn( 1, Grid1Column2 );

	TColumn *Grid1Column3 = new TColumn(DataGrid1);
	Grid1Column3->Header = "Molecular Weight";
	DataGrid1->Model->InsertColumn( 2, Grid1Column3 );

	DataGrid1->Model->Cells[0][0] = "Paracetamol";
	DataGrid1->Model->Cells[1][0] = "4.97";
	DataGrid1->Model->Cells[2][0] = "151";

	DataGrid1->Model->Cells[0][1] = "Caffeine";
	DataGrid1->Model->Cells[1][1] = "5.05";
	DataGrid1->Model->Cells[2][1] = "194";

	DataGrid1->Model->Cells[0][2] = "Indomethacin";
	DataGrid1->Model->Cells[1][2] = "0.4";
	DataGrid1->Model->Cells[2][2] = "358";

	DataGrid1->Model->Cells[0][3] = "Thrimethoprim";
	DataGrid1->Model->Cells[1][3] = "3.14";
	DataGrid1->Model->Cells[2][3] = "290";

}
void __fastcall TTestForm::Button1Click(TObject *Sender)
{
	// Make sure the table in memory is clear
	VirtualTable.Clear();

	for( int Row = 0 ; Row < DataGrid1->Model->RowCount; Row++ )
		{
		// Make a row
		TDataRow RowContainer;
		//copy in the data
		RowContainer.Insert( AnsiString( DataGrid1->Model->Columns[0]->Header ).c_str(), TDataValue( AnsiString( DataGrid1->Model->Cells[0][Row] ).c_str() ) );
		float Temp = StrToFloatDef( DataGrid1->Model->Cells[1][Row], 0.0 ); //There's an odd type issue here, using temp to stop ambiguation
		RowContainer.Insert( AnsiString( DataGrid1->Model->Columns[1]->Header ).c_str(), TDataValue( Temp ) );
		RowContainer.Insert( AnsiString( DataGrid1->Model->Columns[2]->Header ).c_str(), TDataValue( StrToIntDef( DataGrid1->Model->Cells[2][Row], 0 ) ) );

		//Add the row to the table
		VirtualTable.Add( RowContainer );
		}

	int Lyssa = VirtualTable.RowCount();
	Lyssa++;
}
//---------------------------------------------------------------------------


void __fastcall TTestForm::Button2Click(TObject *Sender)
{
	PopulateOutputGrid( OutputGrid, &VirtualTable );

}

void __fastcall TTestForm::PopulateOutputGrid( TStringGrid *OutputGrid, TDataTable *OutputTable )
{
	// clear the current output
	OutputGrid->ClearColumns();

	// Loop through the data source
	for( int i = 0; i < OutputTable->RowCount(); i++ )
		{
		// Get the row
		TDataRow *Row1 = OutputTable->GetRow(i);
		if( Row1 )
			{
			int Melandru = Row1->ValueCount();

			for( int j = 0; j < Row1->ValueCount(); j++ )
				{
				// Look to see if the grid already has a header with this name
				std::string HeaderName = Row1->GetKey( j );
				int ColumnToInsert = IsHeaderInGrid( OutputGrid, HeaderName );
				if( ColumnToInsert == -1 )
					{
					// It doesn't, need to add a column with the header
					TColumn *NewColumn = new TColumn( OutputGrid );
					NewColumn->Header = HeaderName.c_str();
					OutputGrid->Model->InsertColumn( OutputGrid->ColumnCount, NewColumn );

					// Update the insertion variable
					ColumnToInsert = OutputGrid->ColumnCount - 1;
					}

				// Insert the data
				OutputGrid->Model->Cells[ ColumnToInsert ][ i ] = Row1->ValueByKey( HeaderName )->AsString().c_str();
				}
			}
		}
}
//---------------------------------------------------------------------------
int __fastcall TTestForm::IsHeaderInGrid( TStringGrid *Grid, std::string String )
{
	// This function will return -1 if the header isn't in the grid, or the column index
	int Result = -1;
	if( Grid && String.length() )
		{
		// Loop through the columns, stop if we find a match or the end of the columns
		for( int i = 0; i < Grid->ColumnCount && Result == -1; i++ )
			{
			// Get the header name and compare it with the incoming string
			AnsiString Header = Grid->Model->Columns[i]->Header;
            // Do a case insensitive compare
			if( lstrcmpi( Header.c_str(), String.c_str() ) == 0 )
				{
				Result = i;
                }

            }
        }

	return Result;
}
