//---------------------------------------------------------------------------

#include <vcl.h>
#include <JPEG.hpp>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
#pragma resource "*.dfm"

#define TBitmap Graphics::TBitmap
#define MAX_SIZE 12
#define START_SIZE 3
#define MAX_WINDOWS_HEIGHT 480
#define MENU_HEIGHT 30

TForm1 *Form1;

TBitmap *Bitmap= new TBitmap();
TImage *grid[MAX_SIZE*MAX_SIZE]= {0};  //image list
int board[MAX_SIZE][MAX_SIZE];    //board matrix
int size= START_SIZE;
double vTile[MAX_SIZE*MAX_SIZE], yTile[MAX_SIZE*MAX_SIZE];  //speed and position tiles to animate fall tiles
bool win= false;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  srand(time(NULL));
  DoubleBuffered= true;
  TopMenu->Height= MENU_HEIGHT;
  Preview->Top= MENU_HEIGHT+1;
  Preview->Left= 1;

  if(FileExists(ParamStr(1))) {
    loadBitmap(ParamStr(1),Bitmap);
    if(Bitmap->Width > 0 )
      CreateGrid(Bitmap);
  }
  else {

    FormResize(this);
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CreateGrid(TBitmap *Bitmap) {
  int bmpWidth= Bitmap->Width/size;
  int bmpHeight=  Bitmap->Height/size;
  ClientHeight= MAX_WINDOWS_HEIGHT+1;
  ClientWidth= Bitmap->Width*(1.0f*MAX_WINDOWS_HEIGHT / Bitmap->Height);

  int tileWidth= (ClientWidth-size)/size;
  int tileHeight= (ClientHeight-size)/size;

  ClientHeight= tileHeight*size+MENU_HEIGHT+size+1;   //add space for Menu
  ClientWidth= tileWidth*size+size+1;

  int n;

  TRect rectSize;
  rectSize = Rect(0,0,bmpWidth,bmpHeight);
  TRect cut;

 for(int y=0;y<size;y++) {
    for(int x=0;x<size;x++) {
      if(x != size-1 || y != size-1) {  //without last tile
        cut= Rect(x*bmpWidth,y*bmpHeight,(x+1)*bmpWidth,(y+1)*bmpHeight);      // rect to cut from bitmap

        n= y*size+x+1;
        board[x][y]= n;

        grid[n]= new TImage(this);
        grid[n]->Parent= Form1;
        grid[n]->Height= bmpHeight;
        grid[n]->Width= bmpWidth;
        grid[n]->Canvas->CopyRect(rectSize, Bitmap->Canvas, cut);
        //scale tiles
        grid[n]->Stretch= true;
        grid[n]->Height= tileHeight;
        grid[n]->Width= tileWidth;
        grid[n]->OnClick= &TileClick;
        //move tiles
        grid[n]->Top= y*(tileHeight+1)+1+MENU_HEIGHT;
        grid[n]->Left=x*(tileWidth+1)+1;
        Application->ProcessMessages();
      }
      else
        board[x][y]= 0;
    }
  }

  shuffleTiles();

}
void __fastcall TForm1::loadBitmap(AnsiString dir,TBitmap *Bitmap) {

  //convert jpg to Bitmap
  if(AnsiPos(".jpg",LowerCase(dir))+AnsiPos(".jpeg",LowerCase(dir)) != 0) {
    TJPEGImage *jpg= new TJPEGImage();
    jpg->LoadFromFile(dir);
    Bitmap->Assign(jpg);
    jpg->Free();
  }
  else if(AnsiPos(".bmp",LowerCase(dir)) != 0) {
    Bitmap->LoadFromFile(dir);
  }
  else {
    Application->MessageBox("Unsupported File Type","Warning", MB_OK | MB_ICONWARNING );
  }

}

void __fastcall TForm1::TileClick(TObject *Sender)
{
  TImage *tile = (TImage*)Sender;
  int x= (int)(tile->Left/tile->Width);
  int y= (int)(tile->Top/tile->Height);
  double m=0,v=0;
  int start;

    if(x+1 < size && board[x+1][y] == 0) {
      start= tile->Left;
      while(m+v < tile->Width+1) {
        v++;
        m+=v;
        tile->Left= start+m;
        Application->ProcessMessages();
        Sleep(1);
      }
      tile->Left=start+tile->Width+1;
      board[x+1][y]= board[x][y];
      board[x][y]= 0;
    }
    else if(x-1 >= 0 && board[x-1][y] == 0) {
      start= tile->Left;
      while(m+v < tile->Width+1) {
        v++;
        m+=v;
        tile->Left= start-m;
        Application->ProcessMessages();
        Sleep(1);
      }
      tile->Left=start-tile->Width-1;
      board[x-1][y]= board[x][y];
      board[x][y]= 0;
    }
    else if(y+1 < size && board[x][y+1] == 0) {
      start= tile->Top;
      while(m+v < tile->Height+1) {
        v++;
        m+=v;
        tile->Top= start+m;
        Application->ProcessMessages();
        Sleep(1);
      }
      tile->Top=start+tile->Height+1;
      board[x][y+1]= board[x][y];
      board[x][y]= 0;
    }
    else if(y-1 >= 0 && board[x][y-1] == 0) {
      start= tile->Top;
      while(m+v < tile->Height+1) {
        v++;
        m+=v;
        tile->Top= start-m;
        Application->ProcessMessages();
        Sleep(1);
      }
      tile->Top=start-tile->Height-1;
      board[x][y-1]= board[x][y];
      board[x][y]= 0;
    }

    // check if win
    win= true;
    int count=0;

    for(int y= 0;y < size;y++)
      for(int x= 0;x < size; x++)
       if(board[x][y] != ++count && (x != size-1 || y != size-1)) { //if numbering is ok without last empty tile
         win= false;
         break;
       }

    if(win){
      Preview->Width= ClientWidth-2;
      Preview->Height= ClientHeight-MENU_HEIGHT-2;
      Preview->Picture->Bitmap= Bitmap;
      Preview->Visible= true;
      Preview->BringToFront();
      Application->ProcessMessages();
      WinnerLabel->Visible= true;
      Sleep(1500);
      Preview->Visible= false;

      for(int i= 1; i < size*size;i++) {
        yTile[i]= grid[i]->Top;
        vTile[i]= 0;
      }
      WinAnimation->Enabled= true;
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormResize(TObject *Sender)
{
  ExitIcon->Left= ClientWidth- ExitIcon->Width-5;
  OpenIcon->Left= ExitIcon->Left-OpenIcon->Width-15;
  ShowPreviewIcon->Left= OpenIcon->Left-ShowPreviewIcon->Width-15;
  PlusIcon->Left= ShowPreviewIcon->Left-PlusIcon->Width-20;
  GridResize->Left= PlusIcon->Left-GridResize->Width-3;
  MinusIcon->Left= GridResize->Left-MinusIcon->Width-3;

  WinnerLabel->Top= (MAX_WINDOWS_HEIGHT- WinnerLabel->Height-MENU_HEIGHT)/2;
  WinnerLabel->Left= (ClientWidth - WinnerLabel->Width)/2;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ExitIconClick(TObject *Sender)
{
  Application->Terminate();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::TopMenuMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    ReleaseCapture();
        Perform(WM_SYSCOMMAND, 0xF012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OpenIconClick(TObject *Sender)
{
  TOpenDialog *openDialog = new TOpenDialog(this);
  openDialog->InitialDir= "C:/Users/toboriusz/Desktop/11133735_972772702757724_6195641981861175935_n.jpg";
  openDialog->Filter= "All types  (*.*)|*.*|JPG Image  (*.jpg)|*.jpg|JPEG Image  (*.jpeg)|*.jpeg|Bitmap Image  (*.bmp)|*.bmp";
  openDialog->Options= openDialog->Options << ofFileMustExist <<ofPathMustExist;

  if(openDialog->Execute()){
    if(Bitmap->Width > 0) {
      for(int i=1;i < size*size;i++)
        grid[i]->Free();
    }
    loadBitmap(openDialog->FileName,Bitmap);
    if(Bitmap->Width > 0 ) {
      OpenImage->Visible= false;
      WinnerLabel->Visible= false;
      CreateGrid(Bitmap);
    }
  }

  openDialog->Free();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PlusIconClick(TObject *Sender)
{
  if(size < MAX_SIZE && Bitmap->Width > 0) {
    WinnerLabel->Visible= false;
    for(int i=1;i < size*size;i++)
      grid[i]->Free();
    size++;
    CreateGrid(Bitmap);
    win= false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MinusIconClick(TObject *Sender)
{
  if(size > 3 && Bitmap->Width > 0) {
    WinnerLabel->Visible= false;
    for(int i=1;i < size*size;i++)
      grid[i]->Free();
    size--;
    CreateGrid(Bitmap);
    win= false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ShowPreviewIconMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if(Bitmap->Width > 0) {
    Preview->Width= ClientWidth-2;
    Preview->Height= ClientHeight-MENU_HEIGHT-2;
    Preview->Picture->Bitmap= Bitmap;
    Preview->Visible= true;
    Preview->BringToFront();
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ShowPreviewIconMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  Preview->Visible= false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::WinAnimationTimer(TObject *Sender)
{
  for(int i=1;i < size*size;i++)  {
      vTile[i]+= 1.0f*((i-1)/size/size)+0.005*(rand()%100);
      yTile[i]+= vTile[i];
      grid[i]->Top= (int)yTile[i];
      if(grid[i]->Top > 2000) {
        WinAnimation->Enabled= false;
      }
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClick(TObject *Sender)
{
 if(win) {
   size--;
   PlusIconClick(PlusIcon);
 }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
 if(Key == ' ') {
    Preview->Width= ClientWidth-2;
    Preview->Height= ClientHeight-MENU_HEIGHT-2;
    Preview->Picture->Bitmap= Bitmap;
    Preview->Visible= true;
    Preview->BringToFront();
 }        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  Preview->Visible= false;
}
//---------------------------------------------------------------------------

void  __fastcall TForm1::shuffleTiles() {
  /*int a,b, aX,aY,bX,bY,temp;

  for(int n=0 ;n<size*size+size;n++) {
    a= rand()%(size*size-1)+1;
    b= rand()%(size*size-1)+1;

    aX= (grid[a]->Left/grid[a]->Width);
    aY= (grid[a]->Top/grid[a]->Height);

    bX= (grid[b]->Left/grid[b]->Width);
    bY= (grid[b]->Top/grid[b]->Height);

    temp= board[aX][aY];
    board[aX][aY]= board[bX][bY];
    board[bX][bY]= temp;

    temp= grid[a]->Top;
    grid[a]->Top= grid[b]->Top;
    grid[b]->Top= temp;

    temp= grid[a]->Left;
    grid[a]->Left= grid[b]->Left;
    grid[b]->Left= temp;
    Application->ProcessMessages();
  } */

  int x=size-1,y=size-1, mx,my, temp, r;
  TImage * tile= new TImage(this);

  for(int n=0;n<size*size*size*2;n++) {
    r= rand()%4;
    if(r == 0) {
      mx= 1;
      my= 0;
    }
    else if(r == 1) {
      mx= -1;
      my= 0;
    }
    else if(r == 2) {
      mx= 0;
      my= 1;
    }
    else {
      mx= 0;
      my= -1;
    }

    if(x+mx >= size || x+mx < 0)
      mx*= -1;
    if(y+my >= size || y+my < 0)
      my*= -1;


    temp= board[x][y];
    board[x][y]= board[x+mx][y+my];
    board[x+mx][y+my]= temp;

    tile= grid[board[x][y]];
    tile->Top+= (tile->Height+1)*my*(-1);
    tile->Left+= (tile->Width+1)*mx*(-1);

    x+=mx;
    y+=my;
  }
}

