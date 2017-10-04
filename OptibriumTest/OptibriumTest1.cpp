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
	PopulateGrids();
}
//---------------------------------------------------------------------------
void __fastcall TTestForm::PopulateGrids()
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

}
//---------------------------------------------------------------------------


void __fastcall TTestForm::Button2Click(TObject *Sender)
{
	// clear the current output
	OutputGrid->ClearColumns();

    // Fill the table
	TDataRow *Row1 = VirtualTable.GetRow(0);
	if( Row1 )
		{
		Row1->
        }
}
//---------------------------------------------------------------------------

