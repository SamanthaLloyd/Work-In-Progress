//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "OptibriumTest1.h"
#include "DataTable.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TTestForm *TestForm;
//---------------------------------------------------------------------------
__fastcall TTestForm::TTestForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTestForm::Button1Click(TObject *Sender)
{
	StringGrid1->Model->RowCount = 1;
	StringGrid1->Model->InsertColumn(0, new TColumn(StringGrid1));

    StringGrid1->Model->Cells[0][0] = "Hello";
}
//---------------------------------------------------------------------------
