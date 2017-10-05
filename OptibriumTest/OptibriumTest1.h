//---------------------------------------------------------------------------

#ifndef OptibriumTest1H
#define OptibriumTest1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Rtti.hpp>
#include "DataTable.h"
//---------------------------------------------------------------------------
class TTestForm : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *DataGrid1;
	TStringGrid *StringGrid2;
	TStringGrid *StringGrid3;
	TStringGrid *StringGrid4;
	TLabel *Label1;
	TLabel *Label2;
	TButton *Button1;
	TStringGrid *OutputGrid;
	TButton *Button2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
	void __fastcall PopulateSourceDataGrids();
	void __fastcall PopulateOutputGrid( TStringGrid *OutputGrid, TDataTable *OutputTable );
	int __fastcall IsHeaderInGrid( TStringGrid *Grid, std::string String );

	TDataTable VirtualTable;
public:		// User declarations
	__fastcall TTestForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTestForm *TestForm;
//---------------------------------------------------------------------------
#endif
