//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "CGAUGES.h"
#include <ImgList.hpp>
#include <jpeg.hpp>
#include <Dialogs.hpp>
#include <Graphics.hpp>

#define TBitmap Graphics::TBitmap
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *TopMenu;
        TImage *ExitIcon;
        TImage *ShowPreviewIcon;
        TImage *OpenIcon;
        TLabel *GridResize;
        TImage *MinusIcon;
        TImage *PlusIcon;
        TTimer *WinAnimation;
        TImage *Label;
        TImage *Preview;
        TImage *WinnerLabel;
        TImage *OpenImage;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall CreateGrid(TBitmap *Bitmap);
        void __fastcall loadBitmap(AnsiString dir,TBitmap *Bitmap);
        void __fastcall TileClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall ExitIconClick(TObject *Sender);
        void __fastcall TopMenuMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall OpenIconClick(TObject *Sender);
        void __fastcall PlusIconClick(TObject *Sender);
        void __fastcall MinusIconClick(TObject *Sender);
        void __fastcall ShowPreviewIconMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall ShowPreviewIconMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall WinAnimationTimer(TObject *Sender);
        void __fastcall FormClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void  __fastcall shuffleTiles();
private:
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
