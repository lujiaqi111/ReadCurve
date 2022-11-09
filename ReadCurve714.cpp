//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <iostream.h>
#include <fstream>
#include <math.h>
//---------------------------------------------------------------------------

#define _DEBUG_

struct oneLine{
  TPoint p1, p2;
  int len;
  oneLine(TPoint pp1, TPoint pp2, int Dist){
     p1 = pp1;
     p2 = pp2;
     len = Dist;
  }

};


struct Vertex{
        TPoint po;
        Vertex();
        Vertex(int a,int b);
        void init();
};
Vertex::Vertex()
{
        po = Point(0, 0);
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

double getAngle (TPoint p1, TPoint p2);


double GetAngleDotProduct(double ang1, double ang2)
{
    double a;

    a = (cos(ang1) * cos(ang2) + sin(ang1) * sin(ang2));
    if (fabs(a) < 0.000001) a = 0;
    return a;

}


double GetAngleDotProduct(TPoint p1, TPoint p2, TPoint p3)
{
    double ang1, ang2;
    ang1 = getAngle(p1, p2);
    ang2 = getAngle(p2, p3);
    return GetAngleDotProduct(ang1, ang2);
}


double getAngle (TPoint p1, TPoint p2)
{
  double retval;
  double x,y;
  x = p2.x - p1.x;
  y = p2.y - p1.y;
  if(x==0 && y==0) retval = 0; else retval = atan2 (y, x);
  if(retval<0) retval += 2 * M_PI;
  return(retval);
}

double Distance(TPoint p1, TPoint p2)
{
    double xx = (double)(p2.x - p1.x) * (double)(p2.x - p1.x);
    double yy = (double)(p2.y - p1.y) * (double)(p2.y - p1.y);
    return (sqrt(xx + yy));
}



bool GetIntersection(TPoint &gp, TPoint V1, TPoint V2, TPoint V3, TPoint V4, bool extended)
{
    int mode;

    if (extended)
        mode = 1;
    else
        mode = 0;
    float x12, y12, x34, y34;
    float t1, t, a;

    x12 = float(V2.x - V1.x);
    y12 = float(V2.y - V1.y);
    x34 = float(V4.x - V3.x);
    y34 = float(V4.y - V3.y);

    if (x12 == 0.0f && y12 == 0.0f && x34 == 0.0f && y34 == 0.0f)
    {
        if (V1.x == V3.x && V1.y == V3.y)
        {
            gp = V1;
            return true;
        }
        else
            return false;
    }
    if (x12 == 0.0f && y12 == 0.0f)
    {
        if ((Distance(V3, V1) + Distance(V4, V1)) <= Distance(V3, V4))
        {
            gp = V1;
            return true;
        }
        else
            return false;
    }
    if (x34 == 0.0f && y34 == 0.0f)
    {
        if ((Distance(V3, V1) + Distance(V3, V2)) <= Distance(V2, V1))
        {
            gp = V3;
            return true;
        }
        else
            return false;
    }

    if ((x12 * y34) == (x34 * y12))
        return false;

    t1 = (y34 * V1.x - y34 * V3.x - x34 * V1.y + x34 * V3.y) / (y12 * x34 - y34 * x12);
    a = x12 * t1 + V1.x;
    gp.x = int(a);
    gp.y = int(y12 * t1) + V1.y;
    if (mode == 1)
        return true;
    else
    {
        if (y34 != 0.0f)
            t = (y12 * t1 + V1.y - V3.y) / y34;
        else
            t = (x12 * t1 + V1.x - V3.x) / x34;

        if (t >= 0 && t <= 1.00005f && t1 >= 0 && t1 <= 1.00005f)
            if (t >= 0 && t <= 1.00005f && t1 >= 0 && t1 <= 1.00005f)
                return true;
    }
    return false;
}

void writePolygon(String fName, TList *Curve)
{
  TList *Poly;
  Vertex *ver;

  ofstream oFile;
  oFile.open(fName.c_str());

  for (int n = 0; n < Curve->Count; ++n)
  {
    Poly = (TList *) Curve->Items[n];
    if (oFile.fail()) return;
     oFile << "PLINE\n";
     for(int i = 0 ;i < Poly->Count;i++){
          oFile << ((Vertex*)Poly->Items[i])->po.x << "," << ((Vertex*)Poly->Items[i])->po.y << "\n";
     }
    oFile << "\n";
  }
  oFile.close();
}

void writeOnePolygon(String fName, TList *Poly)
{
  Vertex *ver;

  ofstream oFile;
  oFile.open(fName.c_str());

    if (oFile.fail()) return;
     oFile << "PLINE\n";
     for(int i = 0 ;i < Poly->Count;i++){
          oFile << ((Vertex*)Poly->Items[i])->po.x << "," << ((Vertex*)Poly->Items[i])->po.y << "\n";
     }
    oFile << "\n";

  oFile.close();
}



void fixSelfCuttingCurve_2(TList *Poly)
{
   Vertex *ver;
   TPoint gb;
   Vertex *v1, *v2,*v3, *v4;
   for (int i = 0; i < Poly->Count-2; ++i)
   {
       for(int j = i+2; j < Poly->Count-1;++j)
       {
           v1 = (Vertex*)Poly->Items[i];
           v2 = (Vertex*)Poly->Items[i+1];
           v3 = (Vertex*)Poly->Items[j];
           v4 = (Vertex*)Poly->Items[j+1];
           if ( GetIntersection(gb, v1->po, v2->po, v3->po, v4->po,false)){
               ((Vertex*)Poly->Items[i+1])->po.x = gb.x;
               ((Vertex*)Poly->Items[i+1])->po.y = gb.y;
               for (int n = i+2; n <=j; ++n){
                  delete (Vertex *) Poly->Items[n];
                  Poly->Items[n] = NULL;
               }
               Poly->Pack();
               i = -1;
               break;
            }
       }
   }
}

void fixSelfCuttingCurve_3(TList *Poly)
{
   Vertex *ver;
   TPoint gb;
   Vertex *v1, *v2,*v3, *v4;
   for (int i = 0; i < Poly->Count-2; ++i)
   {
       for(int j = Poly->Count-2; j>= i+2; --j)
       {
           v1 = (Vertex*)Poly->Items[i];
           v2 = (Vertex*)Poly->Items[i+1];
           v3 = (Vertex*)Poly->Items[j];
           v4 = (Vertex*)Poly->Items[j+1];
           if ( GetIntersection(gb, v1->po, v2->po, v3->po, v4->po,false)){
               ((Vertex*)Poly->Items[i+1])->po.x = gb.x;
               ((Vertex*)Poly->Items[i+1])->po.y = gb.y;
               for (int n = i+2; n <=j; ++n){
                  delete (Vertex *) Poly->Items[n];
                  Poly->Items[n] = NULL;
               }
               Poly->Pack();
               break;
            }
       }
   }
}

void getPerpendAngle(TPoint p0, TPoint p1, TPoint p2, double &ang, double perAngle)
{
  double ang1, ang2;

  ang1 = getAngle(p0, p1);
  ang2 = getAngle(p1, p2);
  if( ((p1.x - p0.x) == 0) && ( (p1.y- p0.y) == 0) )
    ang = ang2;
  else
  if((p2.x - p1.x) == 0 && (p2.y - p1.y) == 0)
     ang = ang1;
  else ang = (ang1 + ang2) / 2.0;
  ang2 = getAngle(p0, p2);
  double dotP = GetAngleDotProduct(ang, ang2);
  //if((cos(ang)*cos(ang2)+sin(ang)*sin(ang2))<0) ang -= M_PI;
  if (dotP < 0)
    ang -= M_PI;
  ang -= perAngle;
}

double GetVectoreAngle(TPoint p1, TPoint p2, TPoint p3)
{
   if( (p1.x == p2.x) && (p1.y == p2.y) ) return(0);
   if( (p2.x == p3.x) && (p2.y == p3.y) ) return(0);

 try
 {
   double x1, y1, x2, y2, x3, y3;
   x1=p1.x;
   y1=p1.y;
   x2=p2.x;
   y2=p2.y;
   x3=p3.x;
   y3=p3.y;
   if(((x1==x2)&&(y1==y2))||((x2==x3)&&(y2==y3)))
  return 0;
   return(acos (max(-1., (min (1., (((x2-x1)*(x3-x2)+(y2-y1)*(y3-y2))/(sqrt(pow((x2-x1),2)+pow((y2-y1),2))*sqrt(pow((x3-x2),2)+pow((y3-y2),2))))) ))));
 }
 catch(...)
 { return(0); }
}



void ReadFromFile(String fName, TList *Polygon)
{
  TList *Poly = NULL;
  Vertex *ver;
  String data;
  String itIsPline;
  char str[100];
  ifstream infile;
  infile.open(fName.c_str());
#ifdef _DEBUG_
  if (infile.fail())
    cout << "Failed!!!\n" ;
  cout << "Reading from the file" << "\n";
#endif

  while (! infile.eof()){
    infile >> str;
#ifdef _DEBUG_
    cout << str;
#endif
    itIsPline = str;
    if (itIsPline == "PLINE")
    {
      Poly = new TList();
#ifdef _DEBUG_
      cout << "Start of one poly \n";
#endif
      int x, y, ndx;
      char ch;
      while (true)
      {
        infile >> str;
        if (infile.eof())
         break;
        String sss = str;//itIsPline.c_str();
        if (sss.Length() == 0)
           break;
       ndx = sss.Pos(',');
       if (ndx == 0)
       break;
         x = sss.SubString(0, ndx-1).ToInt();
         y =  sss.SubString(ndx+1, sss.Length()).ToInt();
        ver= new Vertex(x, y);
        Poly->Add(ver);
        if (infile.eof())
         break;
      }
      if (Poly->Count != 0)
        Polygon->Add(Poly);
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

void extendCurve(TList *Curve)
{
  double ageE;
  double ageE1;
  TList *Poly;
  Vertex *ver;

  if (Curve->Count == 0)
    return;

  Poly = (TList *) Curve->First();

  if (Poly->Count < 2){
    ageE = 0;
    return;
  }

  ageE = getAngle(((Vertex*)Poly->Items[1])->po,((Vertex*)Poly->First())->po);
  int x1 =  ((Vertex*)Poly->First())->po.x + 1000000*cos(ageE);
  int y1 =  ((Vertex*)Poly->First())->po.y + 1000000*sin(ageE);
  ver = new Vertex(x1,y1);
  Poly->Insert(0,ver);
  ageE1 = getAngle(((Vertex*)Poly->Items[Poly->Count-2])->po,((Vertex*)Poly->Items[Poly->Count-1])->po);// Last())->po);
  int x2 =  ((Vertex*)Poly->Last())->po.x + 1000000*cos(ageE1);
  int y2 =  ((Vertex*)Poly->Last())->po.y + 1000000*sin(ageE1);
  ver = new Vertex(x2,y2);
  Poly->Add(ver);
}





void writeLines(String fName, TList *Lines)
{
  oneLine *L1;
  ofstream oFile;
  oFile.open(fName.c_str());

  for (int i = 0; i < Lines->Count; ++i){
    L1 = (oneLine*) Lines->Items[i];
    oFile << "Line\n";
    oFile << L1->p1.x << "," << L1->p1.y << "\n";
    oFile << L1->p2.x << "," << L1->p2.y << "\n\n";
  }
  oFile.close();
}


bool cw(TPoint a, TPoint b, TPoint c) {
    return ((double)a.x * (double)( b.y - (double)c.y ) + (double)b.x * ( (double)c.y - (double)a.y ) + (double)c.x * ( (double)a.y - (double)b.y )) < 0;
}

bool ccw(TPoint a, TPoint b, TPoint c) {
    return ((double)a.x * (double)( b.y - (double)c.y ) + (double)b.x * ( (double)c.y - (double)a.y ) + (double)c.x * ( (double)a.y - (double)b.y )) > 0;
}

void filterCurves(TList* poly, int offsetDist)
{
   Vertex *v1, *v2, *v3;
   int Dist12, Dist23;
   double dotP;
   for (int i = 0; i < poly->Count-2;i++){
        if( poly->Items[i]== NULL)
          continue;
        if( poly->Items[i+1]== NULL)
          continue;
        if( poly->Items[i+2]== NULL)
          continue;
      v1 = (Vertex *) poly->Items[i];
      v2 = (Vertex *) poly->Items[i+1];
      v3 = (Vertex *) poly->Items[i+2];
      Dist12 = Distance(v1->po,v2->po);
      Dist23 = Distance(v2->po,v3->po);
      if ( (Dist12 > offsetDist) && (Dist23 > offsetDist))
        continue; 

      double ang1 = getAngle(v1->po, v2->po);
      double ang2 = getAngle(v2->po, v3->po);
      dotP = GetAngleDotProduct(ang1, ang2);
#ifdef _DEBUG_
        cout << "dotP:" << dotP << "\n";
#endif
      if(dotP<0){
        if( Distance(v1->po,v2->po)< Distance(v2->po,v3->po)) {
          delete v1;
          poly->Items[i]= NULL;
        }
        else if(Distance(v1->po,v2->po)> Distance(v2->po,v3->po)) {
           delete v3;
           poly->Items[i+2]= NULL;
        }
      }



   }
     poly->Pack();
     writeOnePolygon("polytext.scr", poly);
}


void offsetCurve(TList *Curve, TList *Poly, int Len)
{
  Vertex *v1, *v2, *v3;
  double newAng;
  TPoint newPo, gp;
  int newLen;
  oneLine *L1, *L2;
  TList *Lines;

  //ofstream oFile;
  //oFile.open("lines.scr");
   Lines = new TList();

  filterCurves(Poly, Len);
  writeOnePolygon("offsetPoly-Filterd.scr", Poly);



  TList *newPoly = new TList();

  v1 = (Vertex *) Poly->First();
  for (int i= 0; i < Poly->Count; ++i){
    v2 = (Vertex *) Poly->Items[i];
    if (i == Poly->Count-1)
      v3 = (Vertex *) Poly->Last();
    else
      v3 = (Vertex *) Poly->Items[i+1];

    getPerpendAngle(v1->po, v2->po, v3->po, newAng, M_PI_2);

    int newLen = Len;
    double vecAngle  = GetVectoreAngle(v1->po, v2->po, v3->po);
    if (vecAngle != 0)
      newLen = newLen / cos(vecAngle /2);
    //if ( (Distance(v1->po, v2->po) < Len) || (Distance(v2->po, v3->po) < Len) ){
    //  continue;
    //}



    newPo.x = v2->po.x + newLen * cos(newAng);
    newPo.y = v2->po.y + newLen * sin(newAng);
    if (newPoly->Count != 0){
      double ang1 = getAngle(v1->po, v2->po);
      double ang2 = getAngle(((Vertex*) newPoly->Last())->po, newPo);
      double dotP = GetAngleDotProduct(ang1, ang2);
      if (dotP < 0)
        continue;
    }

    Lines->Add(new oneLine(v2->po, newPo, Distance(v2->po, newPo)));

    //newPoly->Add(new Vertex(newPo.x, newPo.y));

    //    oFile << "Line\n";
    //    oFile << v2->po.x << "," << v2->po.y << "\n";
    //    oFile << newPo.x << "," << newPo.y << "\n\n";

        v1 = v2;
  }

  writeLines("lines_0.scr", Lines);

  for (int i = 0; i < Lines->Count-1; ++i){
    L1 = (oneLine*) Lines->Items[i];
    if  (Lines->Items[i] == NULL)
      continue;
    for (int j = i +1 ; j < Lines->Count; ++j)
    {
      if (Lines->Items[j] == NULL)
         continue;
      L2 = (oneLine*) Lines->Items[j];
      if (GetIntersection(gp, L1->p1, L1->p2, L2->p1, L2->p2, false))
      {
        if (L1->len < L2->len)
        {  delete L1;
           Lines->Items[i]= NULL;
        }
        else
        {  delete L2;
           Lines->Items[j]= NULL;
        }
        --i;
        break;
      }
    }
  }
  Lines->Pack();
  writeLines("lines_1.scr", Lines);

  for (int i = 0;  i < Lines->Count; ++i)
  {
    L1 = (oneLine*) Lines->Items[i];
    newPoly->Add(new Vertex(L1->p2.x, L1->p2.y));
    delete L1;
  }
  delete Lines;

  //oFile.close();
  writeOnePolygon("offsetPoly_0.scr", newPoly);

  fixSelfCuttingCurve_3(newPoly);
  if (newPoly->Count < 2)
    delete newPoly;
  else{
    if ( Len < 0 )
      Curve->Insert(0, newPoly);
    else
      Curve->Add(newPoly);
  }
  //TList* Polygon = new TList();
  //ReadFromFile("_Polys.scr", Polygon);
  writeOnePolygon("offsetPoly.scr", newPoly);


  //writePolygon("offsetPoly.scr", Curve);
}




int main(int argc, char* argv[])
{
   int offsetDist = 1000;

   TList* Curve = new TList();
   ReadFromFile("Curve_f.scr", Curve);

   fixSelfCuttingCurve_2((TList*)Curve->First());
   filterCurves((TList*)Curve->First(), offsetDist);

   extendCurve(Curve);

   writePolygon("outCurve.scr" , Curve);

   for (int n = 0; n <20; ++n){
     offsetCurve(Curve, (TList *) Curve->Last(), 1000);
   }

   for (int n = 0; n <20; ++n){
     offsetCurve(Curve, (TList *) Curve->First(), -1000);
   }

   writePolygon("AllPolygons.scr", Curve);
   FreePolygon(Curve);


        int a;
        cin >> a;
        return 0;
}


//---------------------------------------------------------------------------
