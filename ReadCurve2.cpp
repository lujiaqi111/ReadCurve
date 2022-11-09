//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <iostream.h>
#include <fstream>
//---------------------------------------------------------------------------


struct Vertex{
        TPoint po;
        Vertex();
        Vertex(int a,int b);
        void init();
};
Vertex::Vertex()
{
        po = Point(0,0);
}
Vertex::Vertex(int a,int b){
        po = Point(a,b);
}
Vertex * ReadVertex(int a,int b)
{
        Vertex *aver;
        aver = new Vertex();
        aver->po = Point(a,b);
        return aver;
}
void Vertex::init(){
        po = Point(1,1);
}
#pragma argsused


void ReadFromFile(String fName, TList *Polygon)
{
  TList *Poly = NULL;
  Vertex *ver;
  String data;
  // 以读模式打开文件
  ifstream infile;
  infile.open(fName.c_str());

  cout << "Reading from the file" << "\n";
  String itIsPline;
  while (! infile.eof()){
    infile >> itIsPline.c_str();
    itIsPline = itIsPline.c_str();
    if (infile.eof())
         break;

    if (itIsPline == "PLINE")
    {
      Poly = new TList();
      cout << "Start of one poly \n";
      int x, y, index1;
      char ch;
      while (true)
      {
        //String name;
        //cout << infile.getline(cin,name) << "\n"; //没有getline这个函数


        infile >> x >> ch >> y ;

        /*infile >> itIsPline.c_str();

        itIsPline = itIsPline.c_str();
        if (itIsPline.Length() == 0)
           //break;

       // int DotIndex = itIsPline.Pos(",");
        //cout <<  DotIndex << "\n";
         x = itIsPline.SubString(0, 2).ToInt();
         y =  itIsPline.SubString(4, itIsPline.Length()).ToInt();


        */
        if ((x == -1) && (y == -1))
         break;
        cout << "x:" << x << "\n";
        cout << "y:" << y << "\n";
        ver= new Vertex(x, y);
        Poly->Add(ver);
        if (infile.eof())
         break;
      }
      if (Poly->Count != 0){
        Polygon->Add(Poly);
        cout << "end of one poly \n";
      }
      else
        delete Poly;
    }
  }

}

void FreePolygon(TList *Polygon)
{
   for (int i = 0; i < Polygon->Count; ++i)
   {
      TList *Poly = (TList *) Polygon->Items[i];
      for (int j = 0; j < Poly->Count; ++j)
        delete (Vertex *) Poly->Items[j];
      delete Poly;
    }
    delete Polygon;
}

int main(int argc, char* argv[])
{
  /* TList* Polygon = new TList();
   ReadFromFile("_Polys.scr", Polygon);
   FreePolygon(Polygon);

  */
   TList* Curve = new TList();
   ReadFromFile("_Curve.scr", Curve);
   FreePolygon(Curve);




       /* Vertex *ver;


        TList *polygon;

        polygon = new TList();
        ver = new Vertex(155,155);
        //ver->init();
        polygon->Add(ver);

        for(int i = 0; i < 10 ;i++){
                ver = ReadVertex(i*10,i*200);
                polygon->Add(ver);
        }

        if(ver == NULL){
                cout << "ver == null:" << "\n" ;
        }
        for (int i = 0 ; i < polygon->Count ;i++){
                ver =  (Vertex *)polygon->Items[i];
                cout << ver->po.x << "," << ver->po.y << "\n";
        }
        cout << polygon->Count <<"\n";
        if(ver != NULL){
                delete ver;
                delete polygon;
        } */


        int a;
        cin >> a;
        return 0;
}
//---------------------------------------------------------------------------
