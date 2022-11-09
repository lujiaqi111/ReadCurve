//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <iostream.h>

struct Vertex{
    TPoint po;
    Vertex();
};

Vertex::Vertex()
{
  po = Point(0,0);
}

int readaNum()
{
  return 10;
}


/*
TList * ReadFromFile(char FName[100])
{
}

*/
Vertex * readVertex()
{
   Vertex *aVer;
   aVer = new Vertex();
   aVer->po = Point(100,100);
   return aVer;
}




//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
   /*
   TList *Polygons = NULL;
   TList *poly;
   Polygons = new TList();
   cout << "Polygons->Count: " << Polygons->Count <<  "  Size: " << sizeof(Polygons) << "\n";

   poly = new TList();
   Polygons->Add(poly);
   cout << "Polygons->Added >>  poly" <<  "\n";
   cout << "Now Polygons->Count: " << Polygons->Count <<  "  Size: " << sizeof(Polygons) << "\n";

   poly = new TList();
   Polygons->Add(poly);
   cout << "Polygons->Added >>  poly" <<  "\n";
   cout << "Now Polygons->Count: " << Polygons->Count <<  "  Size: " << sizeof(Polygons) << "\n";

   for (int i = 0; i <Polygons->Count; ++i)
   {
     poly = (TList *) Polygons->Items[i];
     delete poly;
     //delete (TList *) Polygons->Items[i];
   }
    */

    //int a;
    //readInt();
    //a = readInt();


    Vertex *ver;
    ver = readVertex();
    cout << "ver.po = (" << ver->po.x << "," << ver->po.y << ")\n";

    if (ver == NULL)
      cout <<"ver is NULL" <<"\n";
    else
    {
      cout << "ver.po = (" << ver->po.x << "," << ver->po.y << ")\n";
    }

    if (ver != NULL)
      delete ver;
    



   int aaaa;
   cin >> aaaa;

        return 0;
}
//---------------------------------------------------------------------------
 