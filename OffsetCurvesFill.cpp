//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <iostream.h>
#include <fstream>
#include <math.h>
#include <classes.hpp>

//---------------------------------------------------------------------------


 /*
// A C++ program to find single source longest distances
// in a DAG
#include <iostream>
#include <limits.h>
#include <list>
#include <stack>
#define NINF INT_MIN
using namespace std;
 
// Graph is represented using adjacency list. Every
// node of adjacency list contains vertex number of
// the vertex to which edge connects. It also
// contains weight of the edge
class AdjListNode {
    int v;
    int weight;
   
public:
    AdjListNode(int _v, int _w)
    {
        v = _v;
        weight = _w;
    }
    int getV() { return v; }
    int getWeight() { return weight; }
};
   
// Class to represent a graph using adjacency list
// representation
class Graph {
    int V; // No. of vertices'
   
    // Pointer to an array containing adjacency lists
    list<AdjListNode>* adj;

    // A function used by longestPath
    void topologicalSortUtil(int v, bool visited[],
                             stack<int>& Stack);
   
public:
    Graph(int V); // Constructor
    ~Graph(); // Destructor
 
    // function to add an edge to graph
    void addEdge(int u, int v, int weight);
   
    // Finds longest distances from given source vertex
    void longestPath(int s);
};
   
Graph::Graph(int V) // Constructor
{
    this->V = V;
    adj = new list<AdjListNode>[V];
}

Graph::~Graph() // Destructor
{
    delete [] adj;
}
 
 
void Graph::addEdge(int u, int v, int weight)
{
    AdjListNode node(v, weight);
    adj[u].push_back(node); // Add v to u's list
}
   
// A recursive function used by longestPath. See below
// link for details
// https:// www.geeksforgeeks.org/topological-sorting/
void Graph::topologicalSortUtil(int v, bool visited[],
                                stack<int>& Stack)
{
    // Mark the current node as visited
    visited[v] = true;
   
    // Recur for all the vertices adjacent to this vertex
    list<AdjListNode>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
        AdjListNode node = *i;
        if (!visited[node.getV()])
            topologicalSortUtil(node.getV(), visited, Stack);
    }
   
    // Push current vertex to stack which stores topological
    // sort
    Stack.push(v);
}
   
// The function to find longest distances from a given vertex.
// It uses recursive topologicalSortUtil() to get topological
// sorting.
void Graph::longestPath(int s)
{
    stack<int> Stack;
    int dist[6];
   
    // Mark all the vertices as not visited
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
   
    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);
   
    // Initialize distances to all vertices as infinite and
    // distance to source as 0
    for (int i = 0; i < V; i++)
        dist[i] = NINF;
    dist[s] = 0;
    // Process vertices in topological order
    while (Stack.empty() == false) {
        // Get the next vertex from topological order
        int u = Stack.top();
        Stack.pop();
   
        // Update distances of all adjacent vertices
        list<AdjListNode>::iterator i;
        if (dist[u] != NINF) {
            for (i = adj[u].begin(); i != adj[u].end(); ++i){
             
                if (dist[i->getV()] < dist[u] + i->getWeight())
                    dist[i->getV()] = dist[u] + i->getWeight();
            }
        }
    }
   
    // Print the calculated longest distances
    for (int i = 0; i < V; i++)
        (dist[i] == NINF) ? cout << "INF " : cout << dist[i] << " ";

    delete [] visited;
}
   
// Driver program to test above functions
int main1()
{
    // Create a graph given in the above diagram.
    // Here vertex numbers are 0, 1, 2, 3, 4, 5 with
    // following mappings:
    // 0=r, 1=s, 2=t, 3=x, 4=y, 5=z
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 1);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);
   
    int s = 1;
    cout << "Following are longest distances from "
            "source vertex "
         << s << " \n";
    g.longestPath(s);
   
    return 0;
}
*///////////////////////////////////////////////////////////////////////




#define CCW 1
#define CW -1

#define X 0
#define Y 1

#define leftNextCurve 0
#define leftPrevCurve 1
#define rightNextCurve 2
#define rightPrevCurve 3


double getAngle (TPoint p1, TPoint p2);
double GetVectoreAngle(TPoint p1, TPoint p2, TPoint p3);
void reverseOneGroup(TList *group);
void getPerpendAngle(TPoint p0, TPoint p1, TPoint p2, double &ang, double perAngle);

struct Vertex;


 struct oneLine{
  TPoint p1, p2;
  bool isNew;
  bool isValid;
  bool p1Changed, p2Changed;
  oneLine *Next, *Prev;
  Vertex *vP1, *vP2;//used for OffsetLines
  Vertex *vL;
  TPoint dxy;
  TPoint oneStepXY;
  int len;
  int stepLen;
  double angle;
  oneLine(TPoint pp1, TPoint pp2, int Dist){
     p1 = pp1;
     p2 = pp2;
     len = Dist;
     isValid = true;
     isNew = false;
     p1Changed = p2Changed = false;
     vP1 = vP2 = vL = NULL;
  }

};

struct oneCircle{
   TPoint po;
   TList *connections;
   //TList *chidrenConnections;
   TList *Neighborhood;
   TList *children;
   int groupIndex;
   int Radius;
   int Row, Col;
   bool isAtEdge;
   int neighboursStatus;
   bool visited;
   oneCircle(TPoint p, int R, int Row = -1, int Col = -1);
   ~oneCircle();
   bool hasAnyFreeConnection();
   bool hasANullConnectio();
   void reverse();
};

bool oneCircle::hasANullConnectio()
{
  for (int i = 0; i < connections->Count; ++i)
     if (connections->Items[i] == NULL)
        return true;
  return false;

}

bool oneCircle::hasAnyFreeConnection()
{
  for (int i = 0; i < connections->Count; ++i){
     if (connections->Items[i] == NULL) continue;
     oneCircle *aC = (oneCircle*) connections->Items[i];
     if ( !aC->visited && aC->isAtEdge )
       return true;
  }
  return false;
}


oneCircle::oneCircle(TPoint p,int R, int Row, int Col)
{
  po = p;
  Radius = R;
  this->Row = Row;
  this->Col = Col;
  //Row = Row_;
  //Col = Col_;
  connections = NULL;
  Neighborhood = NULL;
  children = new TList();
  //chidrenConnections = new TList();
  isAtEdge = false;
  visited = false;
  neighboursStatus = 0;
  groupIndex = -1;
}

oneCircle::~oneCircle()
{
  if ( connections != NULL)
    delete connections;
  if (Neighborhood != NULL)
    delete Neighborhood;
    delete children;
  //delete chidrenConnections;
}

void oneCircle::reverse(){
   
}
enum {VerTypeNormal, VerTypeIntersect};

struct Vertex{
        TPoint po;
        int VertextType; //0= normal point   1= IntersectionPoint
        int PolyIndex;
        int PolyVerIndex;
        int cerveVerIndex;
        int curveIndex;
        int Dist;
        bool igoneInMakeRun;
        //double PerpendAngle;
        Vertex *curveVertex;
        Vertex *PolyVertex;
        oneLine *prevLine, *nextLine;
        Vertex *nextVer, *prevVer;

        Vertex(int VerType = VerTypeNormal, int cIndex = -1, int pIndex = -1);
        Vertex(int a, int b, int VerType = VerTypeNormal, int cIndex = -1, int pIndex = -1);
        Vertex(TPoint p, int VerType = VerTypeNormal, int cIndex = -1, int pIndex = -1);

        void init();
};

Vertex::Vertex(int VerType, int cIndex, int pIndex){
   po = Point(0, 0);
   VertextType = VerType;
   PolyIndex = pIndex;
   curveVertex = NULL;
   curveIndex = -1;
   nextVer = prevVer = NULL;
   prevLine = nextLine = NULL;
   igoneInMakeRun = false;
}

Vertex::Vertex(TPoint p, int VerType, int cIndex, int pIndex){
   po = p;
   VertextType = VerType;
   PolyIndex = pIndex;
   curveVertex = NULL;
   curveIndex = -1;
   nextVer = prevVer = NULL;
   prevLine = nextLine = NULL;
   prevLine = nextLine = NULL;
   igoneInMakeRun = false;


}

Vertex::Vertex(int a,int b, int VerType, int cIndex, int pIndex){
   po = Point(a,b);
   VertextType = VerType;
   PolyIndex = pIndex;
   curveVertex = NULL;
   curveIndex = -1;
   nextVer = prevVer = NULL;
   prevLine = nextLine = NULL;
   prevLine = nextLine = NULL;
   igoneInMakeRun = false;
}




class oneCurve : public TList
{
 public:

  oneCurve(); 
  __fastcall ~oneCurve();

  int offsetIndex;
  bool byFixInters;
  double area;
  int Direction;
  bool NotConnectedToBoundry;
  bool visited;
  double length;

  oneCurve *connectionHands[4];
  TList *polyVerList[4];

  int ConnectedNext; //0=leftNextCurve  1=leftPrevCurve  2=rightNextCurve  3=rightPrevCurve
  int ConnectedPrev; //0=leftNextCurve  1=leftPrevCurve  2=rightNextCurve  3=rightPrevCurve
  int leftrightDist[4];

  void reverseFirstLine();
  void reverse();

  void DeleteAll();
  void AppendVerList(TList *newList);

  void calculateLength();

};


void Vertex::init(){
        po = Point(1,1);
}


struct oneIntersection{
   TPoint intPoint;
   Vertex *cv1, *cv2, *pv1, *pv2;
   Vertex *intVerOnCurve;
   int Dist;
   int PolyIndex;
   int pv1Index, pv2Index;
};




#pragma argsused





int GetPolygonDirection(oneCurve *SubPoly);
void  check_Fix_Offset_NewCurves(TList *extraNewCurves);
void setOpenPolygonNextPrev(TList *Lines);


bool samePoint(TPoint p1, TPoint p2)
{
   if ((p1.x == p2.x) && (p1.y == p2.y) )
     return true;
   return false;
}


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


double GetDistLinePoint(TPoint p1, TPoint p2, TPoint p)
{
    try
    { return (sin(GetVectoreAngle(p1, p2, p)) * sqrt(pow((p.x - p2.x), 2) + pow((p.y - p2.y), 2))); }
    catch (...)
    { 
        return 0;
    }
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

double Distance (int    P1[2], TPoint  P2)
{ return(sqrt ((P2.x - P1[X]) * (P2.x - P1[X]) + (P2.y - P1[Y]) * (P2.y - P1[Y]))); }


double Distance (double P1[2], double P2[2])
{ return(sqrt ((P2[X] - P1[X]) * (P2[X] - P1[X]) + (P2[Y] - P1[Y]) * (P2[Y] - P1[Y]))); }

double Distance (int P1[2], int P2[2])
{  return(sqrt ((double)(P2[X] - P1[X]) * (double)(P2[X] - P1[X]) + (double)(P2[Y] - P1[Y]) * (double)(P2[Y] - P1[Y]))); }

double Distance (int P1[2], double P2[2])
{  return(sqrt ((double)(P2[X] - P1[X]) * (double)(P2[X] - P1[X]) + (double)(P2[Y] - P1[Y]) * (double)(P2[Y] - P1[Y]))); }

double Distance (double P1[2], int P2[2])
{  return(sqrt ((double)(P2[X] - P1[X]) * (double)(P2[X] - P1[X]) + (double)(P2[Y] - P1[Y]) * (double)(P2[Y] - P1[Y]))); }



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
        if ( (fabs(x34) > fabs(y34)) || (y34 == 0.0f))
          t = (x12 * t1 + V1.x - V3.x) / x34;
        else
          t = (y12 * t1 + V1.y - V3.y) / y34;

        //if (y34 != 0.0f)
        //    t = (y12 * t1 + V1.y - V3.y) / y34;
        //else
        //    t = (x12 * t1 + V1.x - V3.x) / x34;

        if (t >= 0 && t <= 1.0f && t1 >= 0 && t1 <= 1.0f)
            if (t >= 0 && t <= 1.0f && t1 >= 0 && t1 <= 1.0f)
                return true;
    }
    return false;
}

int GetIntersection (double (&IP)[2], double p1[2], double p2[2], double p3[2], double p4[2], int mode)
{
  long double x12, y12, x34, y34;
  long double t1, t, a;
  x12 = (double)p2[X] - (double)p1[X];
  y12 = (double)p2[Y] - (double)p1[Y];
  x34 = (double)p4[X] - (double)p3[X];
  y34 = (double)p4[Y] - (double)p3[Y];
 try
 {
  if(x12 == 0 && y12 == 0 && x34 == 0 && y34 == 0)
    { if(p1[X] == p3[X] && p1[Y] == p3[Y]){ IP[X] = p1[X]; IP[Y] = p1[Y]; return 1; } else return 0; }
  if(x12 == 0 && y12 == 0)
    { if( (Distance(p1, p3) + Distance(p1, p4)) <= Distance(p3, p4))
       { IP[X] = p1[X]; IP[Y] = p1[Y]; return 1; } else return 0;
    }
  if(x34 == 0 && y34 == 0)
    { if( (Distance(p3, p1) + Distance(p3, p2)) <= Distance(p1, p2))
       { IP[X] = p3[X]; IP[Y] = p3[Y]; return 1; } else return 0;
    }

  if((x12 * y34) == (x34 * y12)) return 0;
  t1 = (y34 * p1[X] - y34 * p3[X] - x34 * p1[Y] + x34 * p3[Y]) / (y12 * x34 - y34 * x12);
  a = x12 * t1 + p1[X];
  IP[X] = (int)(a);
  IP[Y] = y12 * t1 + p1[Y];
  if(mode == 1) return 1;
  else
  {
    if(y34 != 0)
	 t = (y12 * t1 + p1[Y] - p3[Y]) / y34;
    else
	 t = (x12 * t1 + p1[X] - p3[X]) / x34;
    if(t >= 0 && t <= 1 && t1 >= 0 && t1 <= 1) return 1;
  }
  return 0;
 }
 catch( ... )
 { 
   return 0;
 }
}

/*
void ___write_oneGroup(String fName, TList *oneGroup, bool writePolyIndex = true)
{
  oneCurve *Poly, *insPoly;
  TList *conList;
  ofstream oFile;
  oFile.open(String("Results\\" + fName).c_str());
  TPoint start;
  Vertex *v;

  //This writes from first to last, Next connection needs to be checked
    if (oneGroup->Count == 0)
      return;
    oFile << "PLINE\n";
    for (int j = 0; j < oneGroup->Count; ++j){
      Poly = (oneCurve *) oneGroup->Items[j];

      for(int n = 0 ;n < Poly->Count; n++){
          v = (Vertex*)Poly->Items[n];
          oFile << v->po.x << "," << v->po.y << "\n";
      }

      if ( (Poly->ConnectedNext != -1) && (j != oneGroup->Count-1) ) {
        conList = Poly->polyVerList[Poly->ConnectedNext];
        for (int n = 0; n < conList->Count; ++n){
            v = (Vertex*)conList->Items[n];
            oFile << v->po.x << "," << v->po.y << "\n";
        }
      }
    }
    oFile << "\n";

    if (writePolyIndex)
    for (int j = 0; j < oneGroup->Count; ++j){
      Poly = (oneCurve *) oneGroup->Items[j];
      v = (Vertex*)Poly->First();
      oFile << "Text " << v->po.x << "," << v->po.y
               << " 250 0 " <<  IntToStr(v->PolyIndex).c_str() << "\n";
      v = (Vertex*)Poly->Last();
      oFile << "Text " << v->po.x << "," << v->po.y
               << " 250 0 " <<  IntToStr(v->PolyIndex).c_str() << "\n";

    }


  oFile.close();
}

void ____write_oneGroup(ofstream &oFile, TList *oneGroup, TPoint &start, TPoint &end)
{
  oneCurve *Poly;
  TList *conList;

    oFile << "PLINE\n";
    for (int j = 0; j < oneGroup->Count; ++j){
      Poly = (oneCurve *) oneGroup->Items[j];
      //if (Poly->childGroup == NULL
      for(int n = 0 ;n < Poly->Count; n++){
          if ((j == 0) && (n == 0))
            start = ((Vertex*)Poly->Items[n])->po;
          end = ((Vertex*)Poly->Items[n])->po;
          oFile << end.x << "," << end.y << "\n";
      }
      if ( ( j <oneGroup->Count-1 ) && (Poly->ConnectedNext != -1) ){
        conList = Poly->polyVerList[Poly->ConnectedNext];
        for (int n = 0; n < conList->Count; ++n){
            end = ((Vertex*)conList->Items[n])->po;
            oFile << end.x << "," << end.y << "\n";
        }
      }
    }
    oFile << "\n";
}

void ___writeInsertedGroup(ofstream &oFile, TList *aGroup)
{
   oneCurve *insPoly = (oneCurve*)aGroup->First();
   TList *conList = insPoly->polyVerList[insPoly->ConnectedPrev];
   for (int n = conList->Count-1; n >= 0;  --n)
      oFile << ((Vertex*)conList->Items[n])->po.x << "," << ((Vertex*)conList->Items[n])->po.y << "\n";
   for (int k = 0; k < aGroup->Count; ++k){
      insPoly = (oneCurve*)aGroup->Items[k];
      //if (insPoly->childGroupAtCurveStart)
      //  writeInsertedGroup(oFile, insPoly->childGroupAtCurveStart);
      for(int n = 0 ;n < insPoly->Count; n++){
          oFile << ((Vertex*)insPoly->Items[n])->po.x << "," << ((Vertex*)insPoly->Items[n])->po.y << "\n";
      }
      //if (insPoly->childGroupAtCurveEnd)
      //  writeInsertedGroup(oFile, insPoly->childGroupAtCurveEnd);

   }
   insPoly = (oneCurve*)aGroup->Last();
   conList = insPoly->polyVerList[insPoly->ConnectedNext];
   for (int n = 0; n < conList->Count; ++n)
      oFile << ((Vertex*)conList->Items[n])->po.x << "," << ((Vertex*)conList->Items[n])->po.y << "\n";
}
*/


void write_allObjGroups_connected(String fName, TList *allObjGroups)
{
  ofstream oFile;
  oFile.open(String("Results\\" + fName).c_str());
  TPoint start, end;

  //This writes from first to last, Next connection needs to be checked
  for (int i = 0; i < allObjGroups->Count;  ++i){
    TList *oneGroup = (TList *) allObjGroups->Items[i];
    if (oneGroup->Count == 0)
      continue;
    oFile << "COLOR " << IntToStr(i+1).c_str() << "\n";

  oneCurve *Poly, *insPoly;
  TList *conList;

    oFile << "PLINE\n";
    for (int j = 0; j < oneGroup->Count; ++j){

      Poly = (oneCurve *) oneGroup->Items[j];

      for(int n = 0 ;n < Poly->Count; n++){
          if ((j == 0) && (n == 0))
            start = ((Vertex*)Poly->Items[n])->po;
          end = ((Vertex*)Poly->Items[n])->po;
          oFile << end.x << "," << end.y << "\n";
      }

      if ( ( j <oneGroup->Count-1 ) && (Poly->ConnectedNext != -1) ){
        conList = Poly->polyVerList[Poly->ConnectedNext];
        for (int n = 0; n < conList->Count; ++n){
            end = ((Vertex*)conList->Items[n])->po;
            oFile << end.x << "," << end.y << "\n";
        }
      }
    }
    oFile << "\n";


    oFile << "Point " << IntToStr(start.x).c_str() << "," << IntToStr(start.y).c_str() << "\n";
    oFile << "Point " << IntToStr(end.x).c_str() << "," << IntToStr(end.y).c_str() << "\n";

  }
  oFile.close();
}

/*
void ___write_allObjGroups(String fName, TList *allObjGroups)
{
  oneCurve *Poly;
  TList *conList;
  ofstream oFile;
  oFile.open(String("Results\\" + fName).c_str());
  TPoint start, end;

  //This writes from first to last, Next connection needs to be checked
  for (int i = 0; i < allObjGroups->Count;  ++i){
    TList *oneGroup = (TList *) allObjGroups->Items[i];
    if (oneGroup->Count == 0)
      continue;
    oFile << "COLOR " << IntToStr(i+1).c_str() << "\n";
    for (int j = 0; j < oneGroup->Count; ++j){
      Poly = (oneCurve *) oneGroup->Items[j];
      oFile << "PLINE\n";
      for(int n = 0 ;n < Poly->Count; n++){
          if ((j == 0) && (n == 0))
            start = ((Vertex*)Poly->Items[n])->po;
          end = ((Vertex*)Poly->Items[n])->po;
          oFile << end.x << "," << end.y << "\n";
      }
      oFile << "\n";
      if ( (j < oneGroup->Count-1) && (Poly->ConnectedNext != -1)) {
        conList = Poly->polyVerList[Poly->ConnectedNext];
        oFile << "PLINE\n";
        for (int n = 0; n < conList->Count; ++n){
            end = ((Vertex*)conList->Items[n])->po;
            oFile << end.x << "," << end.y << "\n";
        }
        oFile << "\n";
      }

    }
  }
  oFile.close();
}
*/
/*
void __writeInfoForPolygon(String fName, TList *Curves)
{
  oneCurve *Poly;
  Vertex *ver;

  ofstream oFile;
  oFile.open(String("Results\\" + fName).c_str());

  for (int n = 0; n < Curves->Count; ++n)
  {
    Poly = (oneCurve *) Curves->Items[n];
    if (oFile.fail()) return;
    oFile << "COLOR " << IntToStr(n+1).c_str() << "\n";
    oFile << "PLINE\n";
     for(int i = 0 ;i < Poly->Count;i++){
          oFile << ((Vertex*)Poly->Items[i])->po.x << "," << ((Vertex*)Poly->Items[i])->po.y << "\n";
     }
    oFile << "\n";

    for(int i = 0 ;i < Poly->Count;i++){
       ver = (Vertex*)Poly->Items[i];
       if (ver->curveIndex != -1){
         oFile << "POINT " << ((Vertex*)Poly->Items[i])->po.x << "," << ((Vertex*)Poly->Items[i])->po.y << "\n";
         oFile << "Text " << ((Vertex*)Poly->Items[i])->po.x << "," << ((Vertex*)Poly->Items[i])->po.y
               << " 250 0 " <<  "pvi:" << IntToStr(i).c_str() <<  "c#:" << IntToStr(ver->curveIndex).c_str() << "cvi:" << IntToStr(ver->cerveVerIndex).c_str() << "\n";
       }
    }


  }
  oFile.close();
}

void writeInfoOfCurve_LeftRightLists(String fName, oneCurve *aCurve, int Index = -1)
{
  Vertex *ver;

    //aCurve = (oneCurve *) newCurves->Items[curveIndex];
    if (aCurve->NotConnectedToBoundry)
      return;

    ofstream oFile;
    oFile.open(String("Results\\" + fName).c_str());
    if (oFile.fail()) return;

    if (Index == -1){
      for (int n = 0; n < 4; ++n){
        oFile << "COLOR " << IntToStr(n+1).c_str() << "\n";//rightPrevPolyVerList
        oFile << "PLINE\n";
         for(int i = 0 ; i < aCurve->polyVerList[n]->Count;i++){
              oFile << ((Vertex*)aCurve->polyVerList[n]->Items[i])->po.x << "," << ((Vertex*)aCurve->polyVerList[n]->Items[i])->po.y << "\n";
         }
        oFile << "\n";
      }
    }
    else{
      oFile << "COLOR " << IntToStr(Index+1).c_str() << "\n";//rightPrevPolyVerList
      oFile << "PLINE\n";
       for(int i = 0 ;i < aCurve->polyVerList[Index]->Count;i++){
            oFile << ((Vertex*)aCurve->polyVerList[Index]->Items[i])->po.x << "," << ((Vertex*)aCurve->polyVerList[Index]->Items[i])->po.y << "\n";
       }
      oFile << "\n";
    }

  oFile.close();
}



void writeInfoForCurve(String fName, TList *newCurves)
{
  oneCurve *aCurve;
  Vertex *ver;

  ofstream oFile;
  oFile.open( String("Results\\" + fName).c_str());

  for (int n = 0; n < newCurves->Count; ++n)
  {
    aCurve = (oneCurve *) newCurves->Items[n];
    if (oFile.fail()) return;

    oFile << "PLINE\n";
     for(int i = 0 ;i < aCurve->Count;i++){
          oFile << ((Vertex*)aCurve->Items[i])->po.x << "," << ((Vertex*)aCurve->Items[i])->po.y << "\n";
     }
    oFile << "\n";

    for(int i = 0 ;i < aCurve->Count;i++)
         oFile << "POINT " << ((Vertex*)aCurve->Items[i])->po.x << "," << ((Vertex*)aCurve->Items[i])->po.y << "\n";

    ver = (Vertex*)aCurve->First();
    oFile << "Text " << ver->po.x << "," << ver->po.y-250
               << " 250 0 " <<  "c:" << IntToStr(n).c_str() << "p:" << IntToStr(ver->PolyIndex).c_str() << "v:" <<  IntToStr(ver->PolyVerIndex).c_str() << "\n";

    ver = (Vertex*)aCurve->Last();
    oFile << "Text " << ver->po.x << "," << ver->po.y-250
               << " 250 0 " <<  "p:" << IntToStr(ver->PolyIndex).c_str() << "pvi:" <<  IntToStr(ver->PolyVerIndex).c_str() << "\n";

  }
  oFile.close();
}
*/

void writePolygon(String fName, TList *Curves, bool writePoints = false)
{
  oneCurve *Poly;
  Vertex *ver;

  ofstream oFile;
  oFile.open(String("Results\\" + fName).c_str());

  for (int n = 0; n < Curves->Count; ++n)
  {
    Poly = (oneCurve *) Curves->Items[n];
    if (oFile.fail()) return;

    if (Poly->byFixInters)
        oFile << "Color 3\n";
    else
        oFile << "Color 1\n";

    oFile << "PLINE\n";
     for(int i = 0 ;i < Poly->Count;i++){
       if (Poly->Items[i] == NULL) continue;
          oFile << ((Vertex*)Poly->Items[i])->po.x << "," << ((Vertex*)Poly->Items[i])->po.y << "\n";
     }
    oFile << "\n";

    if (writePoints){
     for(int i = 0 ;i < Poly->Count;i++){
       if (Poly->Items[i] == NULL) continue;
       oFile << "Point ";
       oFile << ((Vertex*)Poly->Items[i])->po.x << "," << ((Vertex*)Poly->Items[i])->po.y << "\n";

       //oFile << "Line ";
       //oFile << ((Vertex*)Poly->Items[i])->po.x << "," << ((Vertex*)Poly->Items[i])->po.y << "\n";
       //oFile << "@500<" << FloatToStr(((Vertex*)Poly->Items[i])->PerpendAngle).c_str() << "\n\n";
     }
    }



  }
  oFile.close();
}


void writePointsList(String fName, TList *PoList)
{
  Vertex *ver;

  ofstream oFile;
  oFile.open(String("Results\\" + fName).c_str(), std::ios_base::out);

  if (oFile.fail()) return;

  for (int i = 0; i < PoList->Count; ++i){
     oFile << "POINT " << ((Vertex*)PoList->Items[i])->po.x << "," << ((Vertex*)PoList->Items[i])->po.y << "\n";
  }

  oFile.close();
}


void writeOnePolygon(String fName, oneCurve *Poly, int status = std::ios_base::out)
{
  Vertex *ver;

  ofstream oFile;
    oFile.open(String("Results\\" + fName).c_str(), status);

    if (oFile.fail()) return;

    if (Poly->byFixInters)
        oFile << "Color 3\n";
    else
        oFile << "Color 1\n";

     oFile << "PLINE\n";
     for(int i = 0 ;i < Poly->Count;i++){
          oFile << ((Vertex*)Poly->Items[i])->po.x << "," << ((Vertex*)Poly->Items[i])->po.y << "\n";
     }
    oFile << "\n";

     for(int i = 0 ;i < Poly->Count;i++){
        if ( ((Vertex*)Poly->Items[i])->VertextType != VerTypeIntersect)
          continue;
        oFile << "POINT " << ((Vertex*)Poly->Items[i])->po.x << "," << ((Vertex*)Poly->Items[i])->po.y << "\n";
     }


  oFile.close();
}


void FreeOnePoly(oneCurve *Poly){
      for (int j = 0; j < Poly->Count; ++j)
        delete (Vertex *) Poly->Items[j];
      delete Poly;
}

void fixSelfCuttingCurve_3(oneCurve *Poly, TList *extraNewCurves)
{
   Vertex *ver;
   TPoint gb, newPo;
   Vertex *v1, *v2,*v3, *v4, *v, *vn;
   oneCurve *newCurve = NULL;
   setOpenPolygonNextPrev(Poly);
   bool IntersectFound;
   for (int i = 0; i < Poly->Count-2; ++i)
   {
       for(int j = Poly->Count-2; j>= i+2; --j)
       {
           v1 = (Vertex*)Poly->Items[i];
           v2 = (Vertex*)Poly->Items[i+1];
           v3 = (Vertex*)Poly->Items[j];
           v4 = (Vertex*)Poly->Items[j+1];
           if ((i == 0) && (j == Poly->Count-2) && (samePoint(v1->po, v4->po) ) )
             continue;
           if ( GetIntersection(gb, v1->po, v2->po, v3->po, v4->po,false)){

               vn = v2;

               if (extraNewCurves != NULL){
                  newCurve = new oneCurve();
                  newCurve->Add(new Vertex(gb, VerTypeNormal, -1, -1));
                  //newCurve->isNewHole = true;
                  newCurve->byFixInters = true;
                  v = v2;
                  IntersectFound = false;
                  while (v != v4){
                    newCurve->Add(new Vertex(v->po, VerTypeNormal, -1, -1));
                    v = v->nextVer;
                  }
                  newCurve->Add(new Vertex(gb, VerTypeNormal, -1, -1));
                  //writeOnePolygon("new_Curve.scr", newCurve);
                  for (int n = 0; n < newCurve->Count-1; ++n){
                    v1 = (Vertex*) newCurve->Items[n];
                    v2 = (Vertex*) newCurve->Items[n+1];
                    for (int m = newCurve->Count-1 ; m > n+2; --m){
                       v4 = (Vertex*) newCurve->Items[m];
                       v3 = (Vertex*) newCurve->Items[m-1];
                       if ( GetIntersection(newPo, v1->po, v2->po, v3->po, v4->po,false)){
                          v1->po = newPo;
                          v4->po = newPo;

                          int lastNewCurveCount = newCurve->Count;
                          if ( (newCurve->Count == 4) && (n == 0) && ( m = 3)){
                            IntersectFound = false;
                            //FreeOnePoly(newCurve);
                            //newCurve = NULL;
                          }
                          else{
                            IntersectFound = true;
                            for (int k = 0; k < n; ++k){
                              delete (Vertex*) newCurve->Items[k];
                              newCurve->Items[k] = NULL;
                            }
                            for (int k = m+1; k < newCurve->Count; ++k){
                              delete (Vertex*) newCurve->Items[k];
                              newCurve->Items[k] = NULL;
                            }
                          }
                          newCurve->Pack();
                          if (newCurve->Count != lastNewCurveCount){
                            n = newCurve->Count;
                            break;
                          }
                       }
                    }
                  }
                  //if have no intersect then delete newCurve
                  if (!IntersectFound){
                    //if (newCurve != NULL)
                    FreeOnePoly(newCurve);
                    newCurve = NULL;
                  }
                  //else
                  //  writeOnePolygon("new_Curve.scr", newCurve);
               }

               vn->po.x = gb.x;
               vn->po.y = gb.y;

               for (int n = i+2; n <=j; ++n){
                  delete (Vertex *) Poly->Items[n];
                  Poly->Items[n] = NULL;
               }
               Poly->Pack();

               if (newCurve != NULL){
                  //newCurve->Add(new Vertex(gb, VerTypeNormal, -1, -1));
                  //(newCurve, extraNewCurves);
                  if (newCurve->Count > 2){
                    extraNewCurves->Add(newCurve);
                    //fixSelfCuttingCurve_3(newCuve, extraNewCurves);
                  }
                  else{
                     FreeOnePoly(newCurve);
                     newCurve = NULL;
                  }
               }
               break;
            }
       }
   }
}

// this will check if the new created poly has any intersection with the initPoly Or not
void fixSelfCuttingCurve_4(oneCurve *Poly, TList *extraNewCurves)
{
   Vertex *ver;
   TPoint gb, newPo;
   Vertex *v1, *v2,*v3, *v4, *v, *vn;
   oneCurve *newCurve = NULL;
   setOpenPolygonNextPrev(Poly);
   int Dist = -1, D;
   int bestI, bestJ;
   TPoint lastInt;
   bool IntersectFound;
   for (int i = 0; i < Poly->Count-2; ++i)
   {   Dist = -1;
       for(int j = Poly->Count-2; j>= i+2; --j)
       {
           v1 = (Vertex*)Poly->Items[i];
           v2 = (Vertex*)Poly->Items[i+1];
           v3 = (Vertex*)Poly->Items[j];
           v4 = (Vertex*)Poly->Items[j+1];
           if ((i == 0) && (j == Poly->Count-2) && (samePoint(v1->po, v4->po) ) )
             continue;
           if ( GetIntersection(gb, v1->po, v2->po, v3->po, v4->po,false)){
               D = Distance(gb , v1->po);
               if (Dist == -1){
                 Dist = D;
                 bestI = i;
                 bestJ = j;
                 lastInt = gb;
               }
               else if (Dist > D) {
                 Dist = D;
                 bestI = i;
                 bestJ = j;
                 lastInt = gb;
               }
           }
       }
       if (Dist != -1){
         v1 = (Vertex*)Poly->Items[bestI];
         v2 = (Vertex*)Poly->Items[bestI+1];
         v3 = (Vertex*)Poly->Items[bestJ];
         v4 = (Vertex*)Poly->Items[bestJ+1];
         vn = v2;

         if (extraNewCurves != NULL){
            newCurve = new oneCurve();
            newCurve->Add(new Vertex(lastInt, VerTypeNormal, -1, -1));
            //newCurve->isNewHole = true;
            newCurve->byFixInters = true;
            v = v2;
            IntersectFound = false;
            while (v != v4){
              newCurve->Add(new Vertex(v->po, VerTypeNormal, -1, -1));
              v = v->nextVer;
            }
            newCurve->Add(new Vertex(lastInt, VerTypeNormal, -1, -1));
            //writeOnePolygon("new_Curve.scr", newCurve);
            for (int n = 0; n < newCurve->Count-1; ++n){
              v1 = (Vertex*) newCurve->Items[n];
              v2 = (Vertex*) newCurve->Items[n+1];
              for (int m = newCurve->Count-1 ; m > n+2; --m){
                 v4 = (Vertex*) newCurve->Items[m];
                 v3 = (Vertex*) newCurve->Items[m-1];
                 if ( GetIntersection(newPo, v1->po, v2->po, v3->po, v4->po,false)){
                    v1->po = newPo;
                    v4->po = newPo;

                    int lastNewCurveCount = newCurve->Count;
                    if ( (newCurve->Count == 4) && (n == 0) && ( m = 3)){
                      IntersectFound = false;
                    }
                    else{
                      IntersectFound = true;
                      for (int k = 0; k < n; ++k){
                        delete (Vertex*) newCurve->Items[k];
                        newCurve->Items[k] = NULL;
                      }
                      for (int k = m+1; k < newCurve->Count; ++k){
                        delete (Vertex*) newCurve->Items[k];
                        newCurve->Items[k] = NULL;
                      }
                    }
                    newCurve->Pack();
                    if (newCurve->Count != lastNewCurveCount){
                      n = newCurve->Count;
                      break;
                    }
                 }
              }
            }
            //if have no intersect then delete newCurve
            if (!IntersectFound){
              FreeOnePoly(newCurve);
              newCurve = NULL;
            }
         }

         vn->po.x = lastInt.x;
         vn->po.y = lastInt.y;

         for (int n = bestI+2; n <=bestJ; ++n){
            delete (Vertex *) Poly->Items[n];
            Poly->Items[n] = NULL;
         }
         Poly->Pack();

         if (newCurve != NULL){
            if (newCurve->Count > 2){
                extraNewCurves->Add(newCurve);
            }
            else{
               FreeOnePoly(newCurve);
               newCurve = NULL;
            }
         }

       }
   }
}



void fixSelfCutting_Closed_Curve(oneCurve *Poly)
{
   Vertex *ver;
   TPoint gb, newPo;
   Vertex *v1, *v2,*v3, *v4, *v, *vn;
   oneCurve *newCurve = NULL;
   setOpenPolygonNextPrev(Poly);
   bool IntersectFound;
   for (int i = 0; i < Poly->Count-2; ++i)
   {
       for(int j = Poly->Count-2; j>= i+2; --j)
       {
           v1 = (Vertex*)Poly->Items[i];
           v2 = (Vertex*)Poly->Items[i+1];
           v3 = (Vertex*)Poly->Items[j];
           v4 = (Vertex*)Poly->Items[j+1];
           if ((i == 0) && (j == Poly->Count-2) && (samePoint(v1->po, v4->po) ) )
             continue;
           if ( GetIntersection(gb, v1->po, v2->po, v3->po, v4->po,false)){

               v1->po = gb;
               v4->po = gb;
               for (int n = 0; n < i; ++n){
                  v = (Vertex*)Poly->Items[n];
                  delete v;
                  Poly->Items[n] = NULL;
               }
               for (int n = j+2; n < Poly->Count; ++n){
                  v = (Vertex*)Poly->Items[n];
                  delete v;
                  Poly->Items[n] = NULL;
               }
               Poly->Pack();
               return;
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

void ReadFromFile_2(String fName, TList *Polygon, bool skipLast)
{
  oneCurve *Poly = NULL;
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


  Poly = NULL;
  int x, y, ndx;
  char ch;

  while (! infile.eof()){
    infile >> str;
    if (infile.eof())
    break;
    String sss = str;//itIsPline.c_str();
    if (UpperCase(sss) == "PLINE"){
       if (Poly != NULL)
       {
          if (Poly->Count != 0){
             if (skipLast){
               delete (Vertex*)Poly->Last();
               Poly->Delete(Poly->Count-1);
             }
              Polygon->Add(Poly);
          }
          else
            delete Poly;
       }
       Poly = new oneCurve();
       continue;
    }
    if (sss.Length() == 0)
      continue;
    ndx = sss.Pos(',');
    if (ndx == 0)
       continue;
    x = sss.SubString(0, ndx-1).ToInt();
    y =  sss.SubString(ndx+1, sss.Length()).ToInt();
    ver= new Vertex(x, y, VerTypeNormal, -1, -1);
    Poly->Add(ver);
  }
  if (Poly != NULL){
     if (skipLast){
       delete (Vertex*)Poly->Last();
       Poly->Delete(Poly->Count-1);
     }
     Polygon->Add(Poly);
  }
}


void FreePolygon(TList *Polygon)
{
   for (int i = 0; i < Polygon->Count; ++i)
   {
      if (Polygon->Items[i] == NULL)
        continue;
      oneCurve *Poly = (oneCurve *) Polygon->Items[i];
      FreeOnePoly(Poly);
    }
    delete Polygon;
}

void FreeRectPolygon(TList *Polygon)
{
   for (int i = 0; i < Polygon->Count; ++i)
   {
      if (Polygon->Items[i] == NULL)
        continue;
      oneCurve *Poly = (oneCurve *) Polygon->Items[i];
      FreeOnePoly(Poly);
    }
    delete Polygon;
}

void extendCurve(TList *Curves)
{
  double ageE;
  double ageE1;
  oneCurve *Poly;
  Vertex *ver;

  if (Curves->Count == 0)
    return;

  Poly = (oneCurve *) Curves->First();

  if (Poly->Count < 2){
    ageE = 0;
    return;
  }

  ageE = getAngle(((Vertex*)Poly->Items[1])->po,((Vertex*)Poly->First())->po);
  int x1 =  ((Vertex*)Poly->First())->po.x + 100000*cos(ageE);
  int y1 =  ((Vertex*)Poly->First())->po.y + 100000*sin(ageE);
  ver = new Vertex(x1,y1, VerTypeNormal, -1, -1);
  Poly->Insert(0,ver);
  ageE1 = getAngle(((Vertex*)Poly->Items[Poly->Count-2])->po,((Vertex*)Poly->Items[Poly->Count-1])->po);// Last())->po);
  int x2 =  ((Vertex*)Poly->Last())->po.x + 100000*cos(ageE1);
  int y2 =  ((Vertex*)Poly->Last())->po.y + 100000*sin(ageE1);
  ver = new Vertex(x2,y2, VerTypeNormal, -1, -1);
  Poly->Add(ver);
}



void writeLines(String fName, TList *Lines, int col1 = 7, int col2 = 1)
{
  oneLine *L1;
  ofstream oFile;
  oFile.open(String("Results\\" + fName).c_str() );

  for (int i = 0; i < Lines->Count; ++i){
    oFile << "Color " << IntToStr(col1).c_str() << "\n";
    L1 = (oneLine*) Lines->Items[i];
    if (! L1->isValid){
      oFile << "Color " << IntToStr(col2).c_str() << "\n";
    }
    oFile << "Line\n";
    oFile << L1->p1.x << "," << L1->p1.y << "\n";
    oFile << L1->p2.x << "," << L1->p2.y << "\n\n";
  }
  oFile.close();
}


void writeCircles(String fName, TList *Circles, int col1 = 1)
{
  oneCircle *C1;
  ofstream oFile;
  oFile.open(String("Results\\" + fName).c_str() );

  for (int i = 0; i < Circles->Count; ++i){
    TList * cirColList = (TList*) Circles->Items[i];
    for ( int j = 0; j < cirColList->Count; ++j){
       if (cirColList->Items[j] == NULL) continue;
       C1 = (oneCircle *) cirColList->Items[j];
       if (C1->isAtEdge || C1->neighboursStatus == 1 ){
         oFile << "Color 2\n" ;
       }
       else{
         oFile << "Color " << IntToStr(col1).c_str() << "\n";
       }
      oFile << "circle\n";
      oFile << C1->po.x << "," << C1->po.y << " " << C1->Radius << "\n";

      oFile << "PLINE\n";
      oFile << C1->po.x << "," << C1->po.y << "\n";
      for (int k = 0; k < C1->connections->Count; ++ k){
        if ( C1->connections->Items[k] != NULL){
           oneCircle *cc = (oneCircle *) C1->connections->Items[k];
           oFile << cc->po.x << "," << cc->po.y << "\n";
           oFile << C1->po.x << "," << C1->po.y << "\n";
        }
      }
      oFile << "\n";

    }
  }
  oFile.close();
}

void writeCircles_copy(String fName, TList *Circles, int col1 = 1)
{
  oneCircle *C1;
  ofstream oFile;
  oFile.open(String("Results\\" + fName).c_str() );

  for (int i = 0; i < Circles->Count; ++i){
       C1 = (oneCircle *) Circles->Items[i];
       if (C1->isAtEdge || C1->neighboursStatus == 1 ){
         oFile << "Color 3\n" ;
       }
       else{
         oFile << "Color " << IntToStr(col1).c_str() << "\n";
       }
      oFile << "circle\n";
      oFile << C1->po.x << "," << C1->po.y << " " << C1->Radius << "\n";


      oFile << "PLINE\n";
      oFile << C1->po.x << "," << C1->po.y << "\n";
      for (int k = 0; k < C1->connections->Count; ++ k){
        if ( C1->connections->Items[k] != NULL){
           oneCircle *cc = (oneCircle *) C1->connections->Items[k];
           oFile << cc->po.x << "," << cc->po.y << "\n";
           oFile << C1->po.x << "," << C1->po.y << "\n";
        }
      }
      oFile << "\n";


  }
  oFile.close();
}

void writePaths(String fName, TList *Paths, int col1 = 1)
{
  oneCircle *C1, *Cp;
  ofstream oFile;
  oFile.open(String("Results\\" + fName).c_str() );

  for (int i = 0; i < Paths->Count; ++i){
    TList * aPath = (TList*) Paths->Items[i];
    if (aPath->Count == 0) continue;
    oFile << "Color " << IntToStr(i+1).c_str() << "\n" ;
    Cp = NULL;
    for ( int j = 0; j < aPath->Count; ++j){
       C1 = (oneCircle *) aPath->Items[j];
      oFile << "circle\n";
      oFile << C1->po.x << "," << C1->po.y << " " << C1->Radius << "\n";
      if (Cp != NULL){
        oFile << "Line\n";
        oFile << Cp->po.x << "," << Cp->po.y << "\n";
        oFile << C1->po.x << "," << C1->po.y << "\n\n";
      }
      Cp = C1;
    }
  }
  oFile.close();
}


void writeCilderen(ofstream &oFile, oneCircle *Cp)
{
  if (Cp->children->Count == 0)
    return;
  for (int i = 0; i < Cp->children->Count; ++i){
    oneCircle *C1 = (oneCircle*) Cp->children->Items[i];
    oFile << "Color 3" << "\n" ;
    oFile << "Line\n";
    oFile << Cp->po.x << "," << Cp->po.y << "\n";
    oFile << C1->po.x << "," << C1->po.y << "\n\n";
    writeCilderen(oFile, C1);
  }
}


void writePathsChildrenEddie(String fName, TList *Paths)
{
  oneCircle *C1, *Cp;
  ofstream oFile;
  oFile.open(String("Results\\" + fName).c_str() );


  for (int i = 0; i < Paths->Count; ++i){
    TList *aPath = (TList*) Paths->Items[i];
    if (aPath->Count == 0) continue;
    Cp = (oneCircle *) aPath->First();
    writeCilderen(oFile, Cp);
    for (int j = 1; j < aPath->Count; ++j){
      C1 = (oneCircle *) aPath->Items[j];
      oFile << "Color 1" << "\n" ;
      oFile << "Line\n";
      oFile << Cp->po.x << "," << Cp->po.y << "\n";
      oFile << C1->po.x << "," << C1->po.y << "\n\n";
      Cp = C1;
      writeCilderen(oFile, Cp);
    }
  }
  oFile.close();
}


void writePathsChildren(String fName, TList *Paths)
{
  oneCircle *C1, *Cp;
  ofstream oFile;
  oFile.open(String("Results\\" + fName).c_str() );

  for (int i = 0; i < Paths->Count; ++i){
    //oFile << "Color " << IntToStr(i+1).c_str() << "\n" ;
    C1 = (oneCircle *) Paths->Items[i];
    oFile << "circle\n";
    oFile << C1->po.x << "," << C1->po.y << " " << C1->Radius << "\n";
    if(C1->children != NULL){
       for(int j = 0;j < C1->children->Count; ++j){
          Cp = (oneCircle *) C1->children->Items[j];
          oFile << "circle\n";
          oFile << Cp->po.x << "," << Cp->po.y << " " << Cp->Radius << "\n";
          oFile << "Line\n";
          oFile << Cp->po.x << "," << Cp->po.y << "\n";
          oFile << C1->po.x << "," << C1->po.y << "\n\n";
       }
    }
  }
  oFile.close();
}



void filterCurves(oneCurve* poly, int offsetDist)
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

      double ang1 = getAngle(v1->po, v2->po);
      double ang2 = getAngle(v2->po, v3->po);
      dotP = GetAngleDotProduct(ang1, ang2);
      if (dotP > 0.9999){
          delete v2;
          poly->Items[i+1]= NULL;
      }


      Dist12 = Distance(v1->po,v2->po);
      Dist23 = Distance(v2->po,v3->po);
      if ( (Dist12 > offsetDist) && (Dist23 > offsetDist))
        continue;

      if( (dotP < 0) || (Dist12 == 0) || (Dist23 == 0) ){
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
}


TPoint getPolarPoint(TPoint po, int Len, double angle){
   return Point(po.x + Len * cos(angle), po.y + Len * sin(angle));
}

void deleteLines(TList *Lines){
  for (int i = 0; i < Lines->Count; ++i)
    delete (oneLine *) Lines->Items[i];
  delete Lines;
}


void setLinesNextPrev_ClosedCurve(TList *Lines)
{
  oneLine *L1 , *L2;
  L1 = (oneLine*) Lines->Last();
  for (int i = 0;  i < Lines->Count; ++i)
  {
    L2 = (oneLine*) Lines->Items[i];
    L2->Prev = L1;
    L1->Next = L2;
    L1 = L2;
  }
}
void setLinesNextPrev(TList *Lines)
{
  oneLine *L1 = NULL, *L2;
  for (int i = 0;  i < Lines->Count; ++i)
  {
    L2 = (oneLine*) Lines->Items[i];
    L2->Prev = L1;
    L2->Next = NULL;
    if (L1 != NULL)
      L1->Next = L2;
    L1 = L2;
  }

}

void setOpenPolygonNextPrev(TList *Poly)
{
  Vertex *L1 = NULL, *L2;
  for (int i = 0;  i < Poly->Count; ++i)
  {
    L2 = (Vertex*) Poly->Items[i];
    L2->prevVer = L1;
    L2->nextVer = NULL;
    if (L1 != NULL)
      L1->nextVer = L2;
    L1 = L2;
  }

}


int PointInPolygon(TPoint p1, oneCurve *Poly )
{
  Vertex *Vertex1, *Vertex2;
  int n;
  double p2[2], p3[2], p4[2], p5[2], P1[2];
  P1[X] = p1.x;
  P1[Y] = p1.y;

  int HowManyInt1 = 0;

 try
 {
  if( Poly->Count < 3 ) return(0);

  p2[X] = p1.x + 2000000.0;
  p2[Y] = p1.y;

  int m = 0;
  for(n=1; n<Poly->Count; ++n)
  { Vertex2 = (Vertex *) Poly->Items[n];
    switch (m)
    {
        case 0:
            if (p2[Y] == Vertex2->po.y)
            {
                p2[X] = p1.x;
                p2[Y] = p1.y + 2000000;
                m = 1;
                n = 0;
            }
            break;
        case 1:
            if (p2[X] == Vertex2->po.x)
            {
                p2[Y] = p1.y;
                p2[X] = p1.x - 2000000;
                m = 2;
                n = 0;
            }
            break;
        case 2:
            if (p2[Y] == Vertex2->po.y)
            {
                p2[Y] = p1.y - 2000000;
                p2[X] = p1.x;
                m = 3;
                n = 0;
            }
            break;
        case 3:
            if (p2[X] == Vertex2->po.x)
            {
                p2[Y] = p1.y + 2198235;
                p2[X] = p1.x + 1935362;
            }
            break;
    }
  }
  Vertex1 = (Vertex *) Poly->Last();

  p3[X] = Vertex1->po.x;
  p3[Y] = Vertex1->po.y;
  for(n=1; n<Poly->Count; ++n)
  { Vertex2 = (Vertex *) Poly->Items[n];
    p4[X] = Vertex2->po.x;
    p4[Y] = Vertex2->po.y;
    if( GetIntersection(p5, P1, p2, p3, p4, 0) )
      {  HowManyInt1+=1;
         if(p5[X] == p4[X] && p5[Y] == p4[Y]) HowManyInt1-=1;
      }
    p3[X] = p4[X];
    p3[Y] = p4[Y];
    Vertex1 = Vertex2;
  }
  if (HowManyInt1 % 2 == 0) return(0); else return(1);
 }
 catch( ... )
 {
   return(0);
 }
}

bool PointIn_Polygons(TPoint p1, TList *Polygons )
{
  for (int i =0; i < Polygons->Count; ++i){
     oneCurve * aCurve = (oneCurve*) Polygons->Items[i];
     if (i == 0){
       if (PointInPolygon(p1, aCurve) == 0)
         return false;
     }
     else{
       if (PointInPolygon(p1, aCurve) == 1)
         return false;
     }
  }
  return true;
}




bool offset_Closed_Curve(TList *Curves, oneCurve *Poly, int Len, TList *extraNewCurves)
{

  if (Len  == 0)
    return false;

  TList *offsetLines = new TList();
  Vertex *V1, *V2;
  double lineAngle, linePerAngle;

  Vertex *v1, *v2, *v3, *v4;
  double newAng, dotPro1, dotPro2;
  TPoint newPo, gp, p1, p2, p3;
  int newLen;
  oneLine *L1, *L2, *L3, *L4, *L;
  double ang1;
  double ang2;
  oneCurve *tempCurve;

  filterCurves(Poly, abs(Len/4));

  //writeOnePolygon("offsetPoly-Raw.scr", Poly);

  Len = abs(Len);
  if (Len == 0)
    return false;


  //Create offset lines for each two vertexes
  for (int i = 0; i < Poly->Count-1; ++i){
    V1 = (Vertex *) Poly->Items[i];
    V2 = (Vertex *) Poly->Items[i+1];
    lineAngle = getAngle(V1->po, V2->po );

    if (Poly->Direction == CW)
      linePerAngle = lineAngle - M_PI_2;
    else
      linePerAngle = lineAngle + M_PI_2;

      
    p1 = getPolarPoint(V1->po, Len, linePerAngle);
    p2 = getPolarPoint(V2->po, Len, linePerAngle);
    L1 = new oneLine(p1, p2, 0);
    L1->angle = lineAngle;
    L1->vP1 = V1;
    L1->vP2 = V2;
    V1->nextLine = L1;
    V2->prevLine = L1;
    offsetLines->Add(L1);
  }


  //writeLines("of-Lines_0.scr", offsetLines);

  //if L1 & L2 lines have intersection, then change L1->P2, L2->P1
  for (int i = 0; i < offsetLines->Count-1; ++i){
     L1 = (oneLine *) offsetLines->Items[i];
     L2 = (oneLine *) offsetLines->Items[i+1];
     if (GetIntersection(gp, L1->p1, L1->p2, L2->p1, L2->p2, false) ){
        L1->p2.x = gp.x;
        L1->p2.y = gp.y;
        L2->p1.x = gp.x;
        L2->p1.y = gp.y;
        L1->p2Changed = true;
        L2->p1Changed = true;
     }
     else if (GetIntersection(gp, L1->p1, L1->p2, L2->p1, L2->p2, true) ){
         //writeLines("of-Lines_0__.scr", offsetLines);
         ang1 = getAngle(L1->p1, gp);
         ang2 = getAngle(gp, L2->p2);
         dotPro1 = GetAngleDotProduct(ang1 , L1->angle);
         dotPro2 = GetAngleDotProduct(ang2 , L2->angle);
         if ((dotPro1 > 0) && (dotPro2 > 0) ){ // the intersection is ok
           L1->p2 = gp;
           L2->p1 = gp;
         }
         else{
            if (dotPro1 < 0){
              delete L1;
              offsetLines->Items[i] = NULL;
            }

            if (dotPro2 < 0){
              delete L2;
              offsetLines->Items[i+1] = NULL;
            }
            offsetLines->Pack();
            i = max(-1, i-2);
         }
     }
  }
  //writeLines("of-Lines_1.scr", offsetLines);
  if ( offsetLines->Count < 2) {
     deleteLines(offsetLines);
     return false;
  }
  tempCurve = new oneCurve();
  L1 = (oneLine* ) offsetLines->First();
  tempCurve->Add(new Vertex(L1->p1, VerTypeNormal, -1, -1));

  for (int i = 0; i < offsetLines->Count; ++i)
  {
    L1 = (oneLine* ) offsetLines->Items[i];
    tempCurve->Add(new Vertex(L1->p2, VerTypeNormal, -1, -1));
  }

  deleteLines(offsetLines);


  if (tempCurve->Count < 2){
    FreeOnePoly(tempCurve);
    return false;
  }
  else{
    //writeOnePolygon("tempCurve_Before_Fix.scr", tempCurve);

    fixSelfCutting_Closed_Curve(tempCurve);

    //writeOnePolygon("tempCurve_AFTER_Fix.scr", tempCurve);

    GetPolygonDirection(tempCurve);

    Curves->Add(tempCurve);

    //get the xtra curves count
    //then check if any has intersection with the initial Poly, delete it...
    int ndx = extraNewCurves->Count;
    fixSelfCuttingCurve_3(tempCurve, extraNewCurves);
    //writeOnePolygon("tempCurve.scr", tempCurve);
    GetPolygonDirection(tempCurve);
    for (int j = 0; j < tempCurve->Count; ++j){
      v1 = (Vertex*) tempCurve->Items[j];
      if (!PointInPolygon(v1->po, Poly)){
        //writeOnePolygon("deleting.scr", tempCurve);
        Curves->Items[ Curves->Count-1] = NULL;//Remove(tempCurve);
        FreeOnePoly(tempCurve);
        tempCurve = NULL;
        break;
      }
    }
    Curves->Pack();

    //if any extraNewCurve intersects with Poly, we removed it
    for (int i = ndx; i < extraNewCurves->Count; ++i){
      oneCurve *aCurve = (oneCurve *) extraNewCurves->Items[i];
      //writeOnePolygon("extraNewCurves" + IntToStr(i) + ".scr", aCurve);

      v1 = (Vertex*) aCurve->First();
      for (int k = 1; k < aCurve->Count; ++k){
         v2 = (Vertex*) aCurve->Items[k];
         v3 = (Vertex*) Poly->First();
         for (int l = 1; l < Poly->Count; ++l){
           v4 = (Vertex*) Poly->Items[l];
           if (GetIntersection(newPo, v1->po, v2->po, v3->po, v4->po, false)){
             FreeOnePoly(aCurve);
             extraNewCurves->Items[i] = NULL;
             aCurve = NULL;
             break;
           }
           v3 = v4;
         }
         if(aCurve == NULL)
           break;
         v1 = v2;
      }

    }
    extraNewCurves->Pack();

    if (tempCurve == NULL)
      return false;
    else{
      if ( (tempCurve->Direction != Poly->Direction) ||
           (!samePoint(  ((Vertex*)tempCurve->First())->po , ((Vertex*)tempCurve->Last())->po)) )
      {
         Curves->Remove(tempCurve);
         FreeOnePoly(tempCurve);
         return(false);
      }

    }
    return(true);
  }



}



bool offsetCurve_3(TList *Curves, oneCurve *Poly, int Len, TList *extraNewCurves)
{
  if (Len  == 0)
    return false;

  TList *offsetLines = new TList();
  Vertex *V1, *V2;
  double lineAngle, linePerAngle;

  Vertex *v1, *v2, *v3, *v4;
  double newAng, dotPro1, dotPro2;
  TPoint newPo, gp, p1, p2, p3;
  int newLen;
  oneLine *L1, *L2, *L3, *L4, *L;
  double ang1;
  double ang2;

  filterCurves(Poly, abs(Len/4));

  //writeOnePolygon("offsetPoly-Raw.scr", Poly);

  if (Len == 0)
    return false;


  //Create offset lines for each two vertexes
  for (int i = 0; i < Poly->Count-1; ++i){
    V1 = (Vertex *) Poly->Items[i];
    V2 = (Vertex *) Poly->Items[i+1];
    lineAngle = getAngle(V1->po, V2->po );
    linePerAngle = lineAngle - M_PI_2;
    p1 = getPolarPoint(V1->po, Len, linePerAngle);
    p2 = getPolarPoint(V2->po, Len, linePerAngle);
    L1 = new oneLine(p1, p2, 0);
    L1->angle = lineAngle;
    L1->vP1 = V1;
    L1->vP2 = V2;
    V1->nextLine = L1;
    V2->prevLine = L1;
    offsetLines->Add(L1);
  }

  writeLines("of-Lines_0.scr", offsetLines);


  //Checking if that last two lines on the curve are parallel,
  //then
  L1 = (oneLine*) offsetLines->First();
  L2 = (oneLine*) offsetLines->Last();
  if ( GetAngleDotProduct(L1->angle, L2->angle) < -0.99995){ //Lines are Parallel
    v1 = (Vertex *) Poly->First();
    v2 = (Vertex *) Poly->Last();
    ang1 = getAngle(v1->po, L1->p1);
    ang2 = getAngle(v2->po, L2->p2);
    if ( GetAngleDotProduct(ang1, ang2) < 0){ // Offset is twards eachother
      int Dist1 = Distance(v1->po, L1->p1);
      int Dist2 = Distance(v2->po, L2->p2);
      v3 = (Vertex *) Poly->Items[1];
      if ( (Dist1 + Dist2) > GetDistLinePoint(v1->po, v3->po, v2->po) ){ // This offset is inValid
         deleteLines(offsetLines);
         return false;
      }
    }
  }

  //if L1 & L2 lines have intersection, then change L1->P2, L2->P1
  for (int i = 0; i < offsetLines->Count-1; ++i){
     L1 = (oneLine *) offsetLines->Items[i];
     L2 = (oneLine *) offsetLines->Items[i+1];

     writeLines("of-Lines_1__.scr", offsetLines);
     if (GetIntersection(gp, L1->p1, L1->p2, L2->p1, L2->p2, false) ){
        L1->p2.x = gp.x;
        L1->p2.y = gp.y;
        L2->p1.x = gp.x;
        L2->p1.y = gp.y;
        L1->p2Changed = true;
        L2->p1Changed = true;
     }
     else if (GetIntersection(gp, L1->p1, L1->p2, L2->p1, L2->p2, true) ){
         writeLines("of-Lines_0__.scr", offsetLines);
         ang1 = getAngle(L1->p1, gp);
         ang2 = getAngle(gp, L2->p2);
         dotPro1 = GetAngleDotProduct(ang1 , L1->angle);
         dotPro2 = GetAngleDotProduct(ang2 , L2->angle);
         if ((dotPro1 > 0) && (dotPro2 > 0) ){ // the intersection is ok
           L1->p2 = gp;
           L2->p1 = gp;
         }
         else{
            if (dotPro1 < 0){   //mistake here
              if(i>0){
                delete L1;
                offsetLines->Items[i] = NULL;
              }

              //offsetLines->Pack();
              //i = max(-1, i-2);

            }
            ///*****************************************/////

               //int offsetDist = 200;
               //String PolyFile = "Polys\\P13.scr";
               //String CurveFile = "Curves\\C13.scr";
               //if (dotPro2 < 0){
               // 2022_09_06   Below line was causing a endless lopp where the gp was located on L2->P2
               //so I just changed it to  <= 

            if (dotPro2 <= 0){
              delete L2;
              offsetLines->Items[i+1] = NULL;
            }
            offsetLines->Pack();
            i = max(-1, i-2);

         }

     }
  }
  writeLines("of-Lines_1.scr", offsetLines);

  oneCurve *tempCurve = new oneCurve();
  L1 = (oneLine* ) offsetLines->First();
  tempCurve->Add(new Vertex(L1->p1, VerTypeNormal, -1, -1));

  for (int i = 0; i < offsetLines->Count; ++i)
  {
    L1 = (oneLine* ) offsetLines->Items[i];
    tempCurve->Add(new Vertex(L1->p2, VerTypeNormal, -1, -1));
  }

  deleteLines(offsetLines);


  if (tempCurve->Count < 2){
    FreeOnePoly(tempCurve);
    return false;
  }
  else{
    //writeOnePolygon("tempCurve_Before_Fix.scr", tempCurve);

    int ndx = extraNewCurves->Count;
    fixSelfCuttingCurve_4(tempCurve, extraNewCurves);
    //writeOnePolygon("tempCurve_AFTER_Fix.scr", tempCurve);
    if ( Len < 0 )
      Curves->Insert(0, tempCurve);
    else
      Curves->Add(tempCurve);
    for (int i = ndx; i < extraNewCurves->Count; ++i){
      tempCurve = (oneCurve *) extraNewCurves->Items[i];
      //writeOnePolygon("extraNewCurves" + IntToStr(i) + ".scr", tempCurve);
      fixSelfCuttingCurve_4(tempCurve, extraNewCurves);
    }

    //if any extraNewCurve intersects with Poly, we removed it
    for (int i = ndx; i < extraNewCurves->Count; ++i){
      tempCurve = (oneCurve *) extraNewCurves->Items[i];
      //writeOnePolygon("extraNewCurves" + IntToStr(i) + ".scr", tempCurve);

      v1 = (Vertex*) tempCurve->First();
      for (int k = 1; k < tempCurve->Count; ++k){
         v2 = (Vertex*) tempCurve->Items[k];
         v3 = (Vertex*) Poly->First();
         for (int l = 1; l < Poly->Count; ++l){
           v4 = (Vertex*) Poly->Items[l];
           if (GetIntersection(newPo, v1->po, v2->po, v3->po, v4->po, false)){
             FreeOnePoly(tempCurve);
             extraNewCurves->Items[i] = NULL;
             tempCurve = NULL;
             break;
           }
           v3 = v4;
         }
         if(tempCurve == NULL)
           break;
         v1 = v2;
      }

    }
    extraNewCurves->Pack();

    return(true);
  }
}

/*
void write_allIntList(String fName, TList *allIntList)
{

  ofstream oFile;
  oFile.open(String("Results\\" + fName).c_str());

     for (int jj = 0; jj < allIntList->Count; ++jj){

       TList *IntList = (TList *) allIntList->Items[jj];
       oFile << IntToStr(jj).c_str() << "\n";

       for (int j = 0; j < IntList->Count; ++j){
            oneIntersection *oneInt = (oneIntersection *) IntList->Items[j];
            oFile << "  " <<  IntToStr(j).c_str() <<  ": " << oneInt->intPoint.x << "," << oneInt->intPoint.y << "\n";
       }
     }
   oFile.close();
}
*/

bool getCurveAndRectIntersection(TList *Polygons, oneCurve *oneCurveMain){
    Vertex *cv1, *cv2;
    Vertex *pv1, *pv2;
    TPoint intPo;
    bool AnyFound = false;
    for(int i = 0 ; i<oneCurveMain->Count-1;++i){
      cv1 = (Vertex *)oneCurveMain->Items[i];
      cv2 = (Vertex *)oneCurveMain->Items[i+1];
      for(int j = 0; j<Polygons->Count;++j){
         oneCurve *Poly = (oneCurve *) Polygons->Items[j];
         pv1 = (Vertex *)Poly->Last();
         for(int k = 0; k<Poly->Count;++k){
            pv2 = (Vertex *)Poly->Items[k];
            if ( GetIntersection(intPo, cv1->po, cv2->po, pv1->po, pv2->po, false) ){
               AnyFound = true;
               break;

            }
            pv1 = pv2;
         }
         if (AnyFound)
          break;
      }
      if (AnyFound)
        break;
    }

    return AnyFound;
}

bool getCurveAndPolygonIntersection(TList *Polygons, oneCurve *oneCurveMain, TList *newCurves)
{

   Vertex *cv1, *cv2;
   Vertex *pv1, *pv2;
   Vertex* ver;
   TPoint intPo;
   TList *allIntList = new TList();
   oneCurve *aCurve = new oneCurve();
   int pv1Index;
   //Copy the curve
   for (int i = 0; i < oneCurveMain->Count; ++i)
     aCurve->Add(new Vertex( ((Vertex*)oneCurveMain->Items[i])->po ) );


   bool AnyFound = false;


   //writeOnePolygon("aCurve.scr", oneCurveMain);
   //writePolygon("AllPolygons.scr", Polygons);

   for (int i = 0; i < aCurve->Count-1; ++i){

     cv1 = (Vertex *) aCurve->Items[i];
     cv2 = (Vertex *) aCurve->Items[i+1];
     TList *cv1cv2IntList = NULL;
     for (int polyIndex = 0; polyIndex < Polygons->Count; ++polyIndex){
        oneCurve *poly = (oneCurve *) Polygons->Items[polyIndex];
        pv1 = (Vertex*) poly->Last();
        pv1Index = poly->Count-1;
        for (int verIndex = 0; verIndex < poly->Count; ++verIndex){
           pv2 = (Vertex*) poly->Items[verIndex];
           if ( GetIntersection(intPo, cv1->po, cv2->po, pv1->po, pv2->po, false) ){
               if (!samePoint(intPo, cv2->po)){
                 oneIntersection *oneInt = new oneIntersection;
                 oneInt->intPoint = intPo;
                 oneInt->cv1 = cv1;
                 oneInt->cv2 = cv2;
                 oneInt->pv1 = pv1;
                 oneInt->pv2 = pv2;
                 //oneInt->pv1Index = pv1Index;
                 //oneInt->pv2Index = verIndex;
                 oneInt->PolyIndex = polyIndex;
                 if (cv1cv2IntList == NULL){
                   cv1cv2IntList = new TList;
                   allIntList->Add(cv1cv2IntList);
                 }
                 cv1cv2IntList->Add(oneInt);
                 AnyFound = true;
               }
           }
           pv1 = pv2;
           pv1Index = verIndex;
        }
     }
   }

   //write_allIntList("allIntList.txt", allIntList);


   if (allIntList->Count > 0){

     for (int jj = 0; jj < allIntList->Count; ++jj){

       TList *IntList = (TList *) allIntList->Items[jj];
       if (IntList->Count > 1){
         for (int j = 0; j < IntList->Count; ++j){
            oneIntersection *oneInt = (oneIntersection *) IntList->Items[j];
            oneInt->Dist =  Distance(oneInt->cv1->po, oneInt->intPoint);
         }

         //Sort
         for (int j = 0; j < IntList->Count-1; ++j)
           for (int k = j+1; k < IntList->Count; ++k){
             oneIntersection *oneIntJ = (oneIntersection *) IntList->Items[j];
             oneIntersection *oneIntK = (oneIntersection *) IntList->Items[k];
             if ( oneIntJ->Dist > oneIntK->Dist )
               IntList->Exchange(j, k);

           }
        }

        for (int j = 0; j < IntList->Count-1; ++j){
           oneIntersection *oneIntJ = (oneIntersection *) IntList->Items[j];
           oneIntersection *oneIntK = (oneIntersection *) IntList->Items[j+1];
           if (samePoint(oneIntJ->intPoint, oneIntK->intPoint)){
              IntList->Items[j] = NULL;
              IntList->Items[j+1] = NULL;
              delete (oneIntersection *) IntList->Items[j];
              delete (oneIntersection *) IntList->Items[j+1];
              ++j;
           }
        }
        IntList->Pack();
        //write_allIntList("allIntList2.txt", allIntList);

       //Inserting sorted points into Curve
       ver = ((oneIntersection *) IntList->First())->cv2;
       int aVerIndex = aCurve->IndexOf( ver );
       for (int i = IntList->Count-1 ; i >=0 ; --i){
         oneIntersection *oneInt = (oneIntersection *) IntList->Items[i];
         Vertex* ver = new Vertex(oneInt->intPoint, VerTypeIntersect, -1, oneInt->PolyIndex);
         oneInt->intVerOnCurve = ver;
         aCurve->Insert(aVerIndex, ver);
       }


       for (int j = 0; j < IntList->Count; ++j){
          oneIntersection *oneInt = (oneIntersection *) IntList->Items[j];
          oneCurve *Poly = (oneCurve*) Polygons->Items[oneInt->PolyIndex];
          Vertex* ver = new Vertex(oneInt->intPoint, VerTypeIntersect);
          ver->curveVertex = oneInt->intVerOnCurve;
          oneInt->intVerOnCurve->PolyVertex = ver;


          /// Check other Intersections ...
          //If there is any intersection which same pv1 and pv2
          //Then correct pv2 in those ones
          for (int k = jj+1; k < allIntList->Count; ++k){
             TList *aIntList = (TList *) allIntList->Items[k];
             for (int kk = 0; kk < aIntList->Count; ++kk){
               oneIntersection *nextInt = (oneIntersection *) aIntList->Items[kk];
               if ( (nextInt->pv1 == oneInt->pv1) &&(nextInt->pv2 == oneInt->pv2) ){
                  if (Distance(nextInt->pv2->po , nextInt->intPoint) < Distance(nextInt->pv2->po , oneInt->intPoint))
                    nextInt->pv1 = ver;
                  else
                    nextInt->pv2 = ver;
                }
             }
          }
          Poly->Insert(Poly->IndexOf(oneInt->pv2), ver);
        }

     }

   }//for (int jj = 0; jj < allIntList->Count; ++jj)


   int lastCurveIndex = newCurves->Count;
   for (int i = 0; i < aCurve->Count; ++i){
      ver = (Vertex *) aCurve->Items[i];
      if (ver->VertextType == VerTypeIntersect){
        oneCurve *aNewCurve = new oneCurve();// TList();
        newCurves->Add(aNewCurve);
        aNewCurve->Add(ver);
        aCurve->Items[i] = NULL;
        int j;
        for (j = i+1; j < aCurve->Count; ++j){
          ver = (Vertex *) aCurve->Items[j];
          aNewCurve->Add(ver);
          aCurve->Items[j] = NULL;
          if (ver->VertextType == VerTypeIntersect)
            break;
        }
        i = j;
      }
   }
   aCurve->Pack();

   for (int i = 0; i < Polygons->Count;  ++i){
     oneCurve *poly = (oneCurve *) Polygons->Items[i];
     for (int j = 0; j < poly->Count; ++j){
        ver = (Vertex *) poly->Items[j];
        if (ver->curveVertex == NULL)
          continue;
        for (int k = lastCurveIndex; k < newCurves->Count; ++k)
        {
           oneCurve *aNewCurve = (oneCurve *) newCurves->Items[k];
           int cVerIndex = aNewCurve->IndexOf(ver->curveVertex);
           if (cVerIndex != -1){
             //ver->curveVertex->PolyVerIndex = j;
             ver->curveIndex = k;
             ver->cerveVerIndex = cVerIndex;
             break;
           }
        }
     }
   }

   //writeOnePolygon("aCurve.scr", oneCurveMain);

   FreeOnePoly(aCurve);

   for(int i = 0; i < allIntList->Count; ++i){
     TList *IntList = (TList *) allIntList->Items[i];
     for (int j = 0; j < IntList->Count; ++j)
       delete (oneIntersection *) IntList->Items[j];
     delete IntList;
   }
   delete allIntList;



   return AnyFound;
}





void setPolygonsNextPrevVertexes(TList *Polygons)
{
   Vertex *aVer, *curVer;
   oneCurve *aPoly;

   for (int i = 0; i < Polygons->Count; ++i){
     aPoly = (oneCurve *) Polygons->Items[i];
     aVer = (Vertex *) aPoly->Last();
     for (int j = 0; j < aPoly->Count; ++j){
        curVer = (Vertex*) aPoly->Items[j];
        curVer->prevVer = aVer;
        aVer->nextVer = curVer;
        aVer->Dist = Distance(aVer->po, curVer->po);
        aVer = curVer;
     }
   }
}


void setCurvesNextPrevCurves(TList *newCurves, TList *Polygons)
{
  oneCurve *aCurve;
  Vertex *lVer, *rVer, *pVer;
  TList *polyVertices;

  for (int i = 0; i < newCurves->Count; ++i){
     aCurve = (oneCurve *) newCurves->Items[i];
     lVer = (Vertex *) aCurve->First();
     rVer = (Vertex *) aCurve->Last();

     if (lVer->PolyIndex == -1)
       continue;

     pVer = lVer->PolyVertex;

     // from pVer we move forward, then the first found curve will be the leftNext Curve
     aCurve->polyVerList[leftNextCurve]->Add(pVer);
     aCurve->leftrightDist[leftNextCurve] = pVer->Dist;
     do{
       pVer = pVer->nextVer;
       if (!pVer->curveVertex)
         aCurve->leftrightDist[leftNextCurve] += pVer->Dist;
       aCurve->polyVerList[leftNextCurve]->Add(pVer);
       if (pVer->curveVertex){
         aCurve->connectionHands[leftNextCurve] = (oneCurve *) newCurves->Items[ pVer->curveIndex ];
         break;
       }

     }while(true);

     // from pVer we move backward, then the first found curve will be the leftprev Curve
     pVer = lVer->PolyVertex;
     aCurve->polyVerList[leftPrevCurve]->Add(pVer);
     do{
       pVer = pVer->prevVer;
       aCurve->leftrightDist[leftPrevCurve] += pVer->Dist;
       aCurve->polyVerList[leftPrevCurve]->Add(pVer);
       if (pVer->curveVertex){
         aCurve->connectionHands[leftPrevCurve] = (oneCurve *) newCurves->Items[ pVer->curveIndex ];
         break;
       }
     }while(true);

     pVer = rVer->PolyVertex;

     aCurve->polyVerList[rightNextCurve]->Add(pVer);
     aCurve->leftrightDist[rightNextCurve] = pVer->Dist;
     do{
       pVer = pVer->prevVer;
       if (!pVer->curveVertex)
         aCurve->leftrightDist[rightNextCurve] += pVer->Dist;
       aCurve->polyVerList[rightNextCurve]->Add(pVer);
       if (pVer->curveVertex){
         aCurve->connectionHands[rightNextCurve] = (oneCurve *) newCurves->Items[ pVer->curveIndex ];
         break;
       }
     }while(true);

     // from pVer we move forward, then the first found curve will be the rightprev Curve
     pVer = rVer->PolyVertex;
     aCurve->polyVerList[rightPrevCurve]->Add(pVer);
     do{
       pVer = pVer->nextVer;
       aCurve->polyVerList[rightPrevCurve]->Add(pVer);
       aCurve->leftrightDist[rightPrevCurve] += pVer->Dist;

       if (pVer->curveVertex){
         aCurve->connectionHands[rightPrevCurve] = (oneCurve *) newCurves->Items[ pVer->curveIndex ];
         break;
       }
     }while(true);

  }

}

void getOnePolyArea(oneCurve *Poly)
{
   Vertex *v1, *v2;
   v1 = (Vertex *) Poly->Last();
   Poly->area = 0;
   for (int i = 0; i < Poly->Count; ++i){
      v2 = (Vertex *) Poly->Items[i];
      Poly->area += (v2->po.x - v1->po.x) * (v1->po.y + v2->po.y) /2;
      v1 = v2;
   }
   Poly->area = abs(Poly->area);
}


int GetPolygonDirection(oneCurve *SubPoly)
{
   Vertex *Vertex1, *Vertex2;
   double ang1, ang2, ang3, vang, Angle=0;
   int n;
 try
 {

   if( SubPoly->Count <=2 )
   { SubPoly->Direction = CCW;
     return(CCW);
   }

   Vertex1 = (Vertex *) SubPoly->Last();;
   Vertex2 = (Vertex *) SubPoly->First();
   ang1 = getAngle(Vertex1->po, Vertex2->po); //Vertex1->AngleNext;// angle(Vertex2->Point.x-Vertex1->Point.x, Vertex2->Point.y-Vertex1->Point.y);

   Angle = 0;
   Vertex1 = Vertex2;
   for(n = 1; n<SubPoly->Count; ++n)
   { Vertex2 = (Vertex *) SubPoly->Items[n];
     ang2 = getAngle(Vertex1->po, Vertex2->po);//Vertex2->AngleNext;// angle(Vertex2->Point.x-Vertex1->Point.x, Vertex2->Point.y-Vertex1->Point.y);
     vang = acos(max(-1.0, min(1.0, GetAngleDotProduct(ang1, ang2))));
     ang3 = ang1 + M_PI_2;
     if( (cos(ang3)*cos(ang2) + sin(ang3)*sin(ang2)) >=0 )
        Angle += vang;
     else Angle -= vang;
     ang1 = ang2;
     Vertex1 = Vertex2;
   }
   if( Angle > 0 )
   { SubPoly->Direction = CCW; return(CCW); }
   else
   { SubPoly->Direction = CW; return(CW);   }
 }
 catch( ... )
 {
   return(0);
 }
}

Vertex* getOutsideVertexPointInPolygons(TList *Polygons, oneCurve *aCurve){

  oneCurve *Poly;
  Vertex *v;
  for (int n = 0; n < Polygons->Count; ++n){
    Poly = (oneCurve *) Polygons->Items[n];
    for (int m = 0; m < aCurve->Count; ++m){
      v = (Vertex*) aCurve->Items[m];
      if ( (n == 0) && (!PointInPolygon(v->po, Poly)) ){
        return(v);
      }
      if ( (n != 0) && (PointInPolygon(v->po, Poly)) ){
        return(v);
      }
    }
  }
  return(NULL);
}


bool getClosed_Curve_AndPolygonIntersection(TList *Polygons, oneCurve *oneCurveMain, TList *newCurves){
   Vertex *cv1, *cv2;
   Vertex *pv1, *pv2;
   Vertex* ver;
   TPoint intPo;
   TList *allIntList = new TList();
   oneCurve *aCurve = new oneCurve();
   int pv1Index;

   //Copy the curve
   for (int i = 0; i < oneCurveMain->Count; ++i)
     aCurve->Add(new Vertex( ((Vertex*)oneCurveMain->Items[i])->po ) );


   //bool AnyFound = false;

   //Lets open the curve and set the start outside the polygon
   Vertex *v1 = (Vertex *) aCurve->Last();
   Vertex *v2;
   for (int i = 0;  i < aCurve->Count; ++i)
   {
     v2 = (Vertex*) aCurve->Items[i];
     v2->prevVer = v1;
     v1->nextVer = v2;
     v1 = v2;
   }

   //I start from a point outside the polygon
   //and I open the curve (last and first on same point
   //if result is NULL, it means aCurve is inside (or outside) Polygons
   Vertex *v = getOutsideVertexPointInPolygons(Polygons, aCurve);
   if (v == NULL) // All Points are inside Poly
   {  bool Result = true;
      aCurve->NotConnectedToBoundry = true;
        newCurves->Add(aCurve);
     for(int i = 0; i < allIntList->Count; ++i){
       TList *IntList = (TList *) allIntList->Items[i];
       for (int j = 0; j < IntList->Count; ++j)
         delete (oneIntersection *) IntList->Items[j];
       delete IntList;
     }
     delete allIntList;
     return Result;
   }

   pv1Index = aCurve->IndexOf(v);
   for(int i = 0; i < pv1Index; ++i){
      aCurve->Add(aCurve->Items[i]);
      aCurve->Items[i] = NULL;
   }
   aCurve->Add(new Vertex(v->po));
   aCurve->Pack();
   //writeOnePolygon("aCurve.scr", aCurve);


   //writeOnePolygon("IntPoints\\aCurve.scr", oneCurve, std::ios_base::app);

   for (int i = 0; i < aCurve->Count-1; ++i){

     cv1 = (Vertex *) aCurve->Items[i];
     cv2 = (Vertex *) aCurve->Items[i+1];
     TList *cv1cv2IntList = NULL;
     for (int polyIndex = 0; polyIndex < Polygons->Count; ++polyIndex){
        oneCurve *poly = (oneCurve *) Polygons->Items[polyIndex];
        pv1 = (Vertex*) poly->Last();
        pv1Index = poly->Count-1;
        for (int verIndex = 0; verIndex < poly->Count; ++verIndex){
           pv2 = (Vertex*) poly->Items[verIndex];
           if ( GetIntersection(intPo, cv1->po, cv2->po, pv1->po, pv2->po, false) ){
               oneIntersection *oneInt = new oneIntersection;
               oneInt->intPoint = intPo;
               oneInt->cv1 = cv1;
               oneInt->cv2 = cv2;
               oneInt->pv1 = pv1;
               oneInt->pv2 = pv2;
               oneInt->PolyIndex = polyIndex;
               if (cv1cv2IntList == NULL){
                 cv1cv2IntList = new TList;
                 allIntList->Add(cv1cv2IntList);
               }
               cv1cv2IntList->Add(oneInt);
               //AnyFound = true;
           }
           pv1 = pv2;
           pv1Index = verIndex;
        }
     }
   }


   if (allIntList->Count > 0){

     for (int jj = 0; jj < allIntList->Count; ++jj){

       TList *IntList = (TList *) allIntList->Items[jj];
       if (IntList->Count > 1){
         for (int j = 0; j < IntList->Count; ++j){
            oneIntersection *oneInt = (oneIntersection *) IntList->Items[j];
            oneInt->Dist =  Distance(oneInt->cv1->po, oneInt->intPoint);
         }

         //Sort
         for (int j = 0; j < IntList->Count-1; ++j)
           for (int k = j+1; k < IntList->Count; ++k){
             oneIntersection *oneIntJ = (oneIntersection *) IntList->Items[j];
             oneIntersection *oneIntK = (oneIntersection *) IntList->Items[k];
             if ( oneIntJ->Dist > oneIntK->Dist )
               IntList->Exchange(j, k);

           }
        }


       //Inserting sorted points into Curve
       ver = ((oneIntersection *) IntList->First())->cv2;
       int aVerIndex = aCurve->IndexOf( ver );
       for (int i = IntList->Count-1 ; i >=0 ; --i){
         oneIntersection *oneInt = (oneIntersection *) IntList->Items[i];
         Vertex* ver = new Vertex(oneInt->intPoint, VerTypeIntersect, -1, oneInt->PolyIndex);
         oneInt->intVerOnCurve = ver;
         aCurve->Insert(aVerIndex, ver);
       }


       for (int j = 0; j < IntList->Count; ++j){
          oneIntersection *oneInt = (oneIntersection *) IntList->Items[j];
          oneCurve *Poly = (oneCurve*) Polygons->Items[oneInt->PolyIndex];
          Vertex* ver = new Vertex(oneInt->intPoint, VerTypeIntersect);
          ver->curveVertex = oneInt->intVerOnCurve;
          oneInt->intVerOnCurve->PolyVertex = ver;


          /// Check other Intersections ...
          //If there is any intersection which same pv1 and pv2
          //Then correct pv2 in those ones
          for (int k = jj+1; k < allIntList->Count; ++k){
             TList *aIntList = (TList *) allIntList->Items[k];
             for (int kk = 0; kk < aIntList->Count; ++kk){
               oneIntersection *nextInt = (oneIntersection *) aIntList->Items[kk];
               if ( (nextInt->pv1 == oneInt->pv1) &&(nextInt->pv2 == oneInt->pv2) ){
                  if (Distance(nextInt->pv2->po , nextInt->intPoint) < Distance(nextInt->pv2->po , oneInt->intPoint))
                    nextInt->pv1 = ver;
                  else
                    nextInt->pv2 = ver;
                }
             }
          }
          Poly->Insert(Poly->IndexOf(oneInt->pv2), ver);
        }

     }

   }//for (int jj = 0; jj < allIntList->Count; ++jj)

   //writeOnePolygon("aCurve.scr", aCurve);

   int lastCurveIndex = newCurves->Count;
   for (int i = 0; i < aCurve->Count; ++i){
      ver = (Vertex *) aCurve->Items[i];
      if (ver->VertextType == VerTypeIntersect){
        oneCurve *aNewCurve = new oneCurve();// TList();
        newCurves->Add(aNewCurve);
        aNewCurve->Add(ver);
        aCurve->Items[i] = NULL;
        int j;
        for (j = i+1; j < aCurve->Count; ++j){
          ver = (Vertex *) aCurve->Items[j];
          aNewCurve->Add(ver);
          aCurve->Items[j] = NULL;
          if (ver->VertextType == VerTypeIntersect)
            break;
        }
        i = j;
      }
   }
   aCurve->Pack();
   //writeOnePolygon("aCurve.scr", aCurve);

   for (int i = 0; i < Polygons->Count;  ++i){
     oneCurve *poly = (oneCurve *) Polygons->Items[i];
     for (int j = 0; j < poly->Count; ++j){
        ver = (Vertex *) poly->Items[j];
        if (ver->curveVertex == NULL)
          continue;
        for (int k = lastCurveIndex; k < newCurves->Count; ++k)
        {
           oneCurve *aNewCurve = (oneCurve *) newCurves->Items[k];
           int cVerIndex = aNewCurve->IndexOf(ver->curveVertex);
           if (cVerIndex != -1){
             //ver->curveVertex->PolyVerIndex = j;
             ver->curveIndex = k;
             ver->cerveVerIndex = cVerIndex;
             break;
           }
        }
     }
   }

     //writeOnePolygon("IntPoints\\aCurve.scr", oneCurve, std::ios_base::app);

   FreeOnePoly(aCurve);

   for(int i = 0; i < allIntList->Count; ++i){
     TList *IntList = (TList *) allIntList->Items[i];
     for (int j = 0; j < IntList->Count; ++j)
       delete (oneIntersection *) IntList->Items[j];
     delete IntList;
   }
   delete allIntList;



   return true;

}

Vertex* findNearestVertexOnPolygons(TList *Polygons, TPoint startPoint){

   Vertex *Result = NULL, *v;
   int minDist = 0x0FFFFFFF;
   int Dist;

      oneCurve *curve = (oneCurve*) Polygons->Items[0];
      for (int j = 0; j < curve->Count; ++j){
        v = (Vertex*) curve->Items[j];
        v->PolyIndex = 0;
        Dist = Distance(v->po, startPoint);
        if (minDist > Dist){
           Result = v;
           minDist = Dist;

        }
      }
   cout << Result->PolyVerIndex << "\n";
   return(Result);

}


bool reverseFirstLineOfOneGroup(TList *oneGroup)
{
  oneCurve *curCurve, *nextCurve;
  int con;

  for (int i = 0; i < oneGroup->Count-1; ++i){
    curCurve = (oneCurve *) oneGroup->Items[i];
    nextCurve = (oneCurve *) oneGroup->Items[i+1];
    if ( (curCurve->connectionHands[leftNextCurve] != nextCurve) || (curCurve->connectionHands[rightNextCurve] != nextCurve))
      return false;
  }

  for (int i = 0; i < oneGroup->Count; ++i){
    curCurve = (oneCurve *) oneGroup->Items[i];
    curCurve->reverseFirstLine();
  }


  return true ;


}

void traverseOneGroup(TList *newCurves, TList *oneGroup, oneCurve *Curve, bool forward)
{
   oneCurve *nextCurve = NULL, *prevCurve = NULL;
   Vertex *curvePolyLV, *curvePolyFV, *CurveLastVer, *CurveFirstVer;
   Vertex *nextCurveFV, *nextCurveLV, *prevCurveFV, *prevCurveLV;

   //writeOnePolygon("Curve.scr", Curve);
   //writeInfoOfCurve_LeftRightLists("Curve_Connection_.scr", Curve);

   CurveLastVer = (Vertex*) Curve->Last();
   CurveFirstVer = (Vertex*) Curve->First();
   if (forward){
       if ( (!Curve->connectionHands[rightNextCurve]->visited) ){
           if (Curve->connectionHands[rightNextCurve] != Curve){
             curvePolyLV = (Vertex *) Curve->polyVerList[rightNextCurve]->Last();
             curvePolyFV = (Vertex *) Curve->polyVerList[rightNextCurve]->First();
             nextCurve = Curve->connectionHands[rightNextCurve];
             Curve->ConnectedNext = rightNextCurve;
           }
       }
       else
       if ( (!Curve->connectionHands[rightPrevCurve]->visited) ){
           if (Curve->connectionHands[rightPrevCurve] != Curve){
             curvePolyLV = (Vertex *) Curve->polyVerList[rightPrevCurve]->Last();
             curvePolyFV = (Vertex *) Curve->polyVerList[rightPrevCurve]->First();
             nextCurve = Curve->connectionHands[rightPrevCurve];
             Curve->ConnectedNext = rightPrevCurve;
           }
       }
   }
   else{
       if ( (!Curve->connectionHands[leftPrevCurve]->visited) ){
           if (Curve->connectionHands[leftPrevCurve] != Curve){
             curvePolyLV = (Vertex *) Curve->polyVerList[leftPrevCurve]->Last();
             curvePolyFV = (Vertex *) Curve->polyVerList[leftPrevCurve]->First();
             nextCurve = Curve->connectionHands[leftPrevCurve];
             Curve->ConnectedPrev = leftPrevCurve;
           }
       }
       else if ( (!Curve->connectionHands[leftNextCurve]->visited) ){
           if (Curve->connectionHands[leftNextCurve] != Curve){
             curvePolyLV = (Vertex *) Curve->polyVerList[leftNextCurve]->Last();
             curvePolyFV = (Vertex *) Curve->polyVerList[leftNextCurve]->First();
             nextCurve = Curve->connectionHands[leftNextCurve];
             Curve->ConnectedPrev = leftNextCurve;
           }                                                                
       }
   }

   if (nextCurve != NULL){
     //writeOnePolygon("nextCurve.scr", nextCurve);
     //writeInfoOfCurve_LeftRightLists("nextCurve_Connection_.scr", nextCurve);
     if (forward)
       oneGroup->Add(nextCurve);
     else
       oneGroup->Insert(0, nextCurve);
     newCurves->Remove(nextCurve);
     nextCurve->visited = true;

     nextCurveFV = (Vertex*) nextCurve->First();
     nextCurveLV = (Vertex*) nextCurve->Last();

     if (forward){
       if (!samePoint(curvePolyLV->po, nextCurveFV->po))
         nextCurve->reverseFirstLine();
     }
     else{ //backward
       if (!samePoint(curvePolyLV->po, nextCurveLV->po))
           nextCurve->reverseFirstLine();
     }

     if(forward){
       Vertex *v1 = (Vertex*) nextCurve->polyVerList[leftNextCurve]->Last();
       if ( samePoint(v1->po, curvePolyFV->po))
         nextCurve->ConnectedPrev = leftNextCurve;
       else{
         Vertex *v1 = (Vertex*) nextCurve->polyVerList[rightNextCurve]->Last();
         if ( samePoint(v1->po, curvePolyFV->po))
           nextCurve->ConnectedPrev = rightNextCurve;
         else {
           Vertex *v1 = (Vertex*) nextCurve->polyVerList[leftPrevCurve]->Last();
           if ( samePoint(v1->po, curvePolyFV->po))
             nextCurve->ConnectedPrev = leftPrevCurve;
           else{
             Vertex *v1 = (Vertex*) nextCurve->polyVerList[rightPrevCurve]->Last();
             if ( samePoint(v1->po, curvePolyFV->po))
               nextCurve->ConnectedPrev = rightPrevCurve;
           }
         }
       }
     }
     else{
       Vertex *v1 = (Vertex*) nextCurve->polyVerList[leftNextCurve]->Last();
       if ( samePoint(v1->po, curvePolyFV->po))
         nextCurve->ConnectedNext = leftNextCurve;
       else{
         Vertex *v1 = (Vertex*) nextCurve->polyVerList[rightNextCurve]->Last();
         if ( samePoint(v1->po, curvePolyFV->po))
           nextCurve->ConnectedNext = rightNextCurve;
         else {
           Vertex *v1 = (Vertex*) nextCurve->polyVerList[leftPrevCurve]->Last();
           if ( samePoint(v1->po, curvePolyFV->po))
             nextCurve->ConnectedNext = leftPrevCurve;
           else{
             Vertex *v1 = (Vertex*) nextCurve->polyVerList[rightPrevCurve]->Last();
             if ( samePoint(v1->po, curvePolyFV->po))
               nextCurve->ConnectedNext = rightPrevCurve;
           }
         }
       }
     }
     //writeOnePolygon("nextCurve.scr", nextCurve);
     //writeInfoOfCurve_LeftRightLists("nextCurve_Connection_.scr", nextCurve);

     traverseOneGroup(newCurves, oneGroup, nextCurve, forward);
   }

}


void correctPolygonDirections(TList *Polygons)
{
   oneCurve *curve;

   curve = (oneCurve*) Polygons->First();
   if (curve->Direction != CW)
     curve->reverseFirstLine();
   for (int i = 1; i < Polygons->Count; ++i){
     curve = (oneCurve*) Polygons->Items[i];
     if (curve->Direction == CW)
       curve->reverseFirstLine();
   }
}

void makeAllPolygonDirectionsSame(TList *Polygons)
{
   oneCurve *curve1, *curve2;

   curve1 = (oneCurve*) Polygons->First();
   //if (curve->Direction != CW)
   //  curve->reverseFirstLine();
   for (int i = 1; i < Polygons->Count; ++i){
     curve2 = (oneCurve*) Polygons->Items[i];
     if (curve2->Direction != curve1->Direction)
       curve2->reverse();
   }
}



int makeRunOnMainPolygonEdge(oneCurve* Poly, Vertex* startV, Vertex* endV , TList *runList)
{
  TList *runListNext = new TList();
  TList *runListPrev = new TList();
  Vertex *nextVer = startV;
  int ResultDist = -1;
  int DistNext = 0;
  int DistPrev = 0;
  runListNext->Add(nextVer);
  while(nextVer != endV){
    DistNext += Distance(nextVer->po, nextVer->nextVer->po);
    nextVer = nextVer->nextVer;
    runListNext->Add(nextVer);
  }

  Vertex* prevVer = startV;
  runListPrev->Add(prevVer);
  while(prevVer != endV){
        DistPrev += Distance(prevVer->po, prevVer->prevVer->po);
        prevVer = prevVer->prevVer;
        runListPrev->Add(prevVer);
  }

  if (DistNext < DistPrev){
        ResultDist = DistNext;
        for (int n = 0; n < runListNext->Count; ++n)
          runList->Add(runListNext->Items[n]);
  }
  else{
        ResultDist = DistPrev;
        for (int n = 0; n < runListPrev->Count; ++n)
          runList->Add(runListPrev->Items[n]);
   }
  delete runListNext;
  delete runListPrev;
  return ResultDist;
}



void InsertinnerGroupsToOutterGroups(TList *Polygons, TList *allObjGroups)
{

   TList *baseGroup;
   int minDist, Dist;
   int selectedBaseCurveIndex, selectedCurveIndex;
   oneCurve *selectedBaseCurve;
   oneCurve *selectedCurve;
   int selectedConHand;
   bool joineToFirstOnBaseCurve = true;
   TList *selectedGroup = NULL;

   for (int i = allObjGroups->Count-1; i > 0; --i)
   {
     TList *oneGroup = (TList*) allObjGroups->Items[i];
     if (oneGroup->Count == 0) continue;
     //write_oneGroup("oneGroup.scr", oneGroup);
     oneCurve *firstCurve = (oneCurve*) oneGroup->First();
     oneCurve *lastCurve  = (oneCurve*) oneGroup->Last();
     //writeInfoOfCurve_LeftRightLists("firstCurve_Conn.scr", firstCurve);
     //writeInfoOfCurve_LeftRightLists("lastCurve_Conn.scr", lastCurve);
     //below means, Start / End must not be on main Polygon
     if ( (((Vertex*) firstCurve->First())->PolyIndex == 0) && (((Vertex*) lastCurve->Last())->PolyIndex == 0) ) continue;
     //below means both start end must be on one Polygon
     if ( ((Vertex*) firstCurve->First())->PolyIndex != ((Vertex*) lastCurve->Last())->PolyIndex ) continue;

     minDist = 0x0FFFFFFF;
     selectedBaseCurve = NULL;
     selectedCurve = NULL;
     selectedConHand = 0;


     for (int j = 0;  j < allObjGroups->Count; ++j){
       if ( i == j )    continue;
       baseGroup = (TList*) allObjGroups->Items[j];
       if (baseGroup->Count == 0) continue;

       oneCurve *baseFirstCurve = (oneCurve*) baseGroup->First();
       oneCurve *baseLastCurve  = (oneCurve*) baseGroup->Last();
       if ( (((Vertex*)baseFirstCurve->First())->PolyIndex != ((Vertex*) firstCurve->First())->PolyIndex) ||
            (((Vertex*)baseLastCurve->Last())->PolyIndex != ((Vertex*) firstCurve->First())->PolyIndex))
           continue; 


       //if (joinedList->IndexOf(baseGroup) != -1) continue;
       //write_oneGroup("baseGroup.scr", baseGroup);
       for (int n = 0; n < oneGroup->Count; ++n){
         oneCurve* Curve = (oneCurve*) oneGroup->Items[n];
         //writeOnePolygon("Curve.scr", Curve);
         //writeInfoOfCurve_LeftRightLists("Curve_Conn.scr", Curve);

         for (int m = leftNextCurve; m <= rightPrevCurve; ++m){
            //writeOnePolygon("baseCurve.scr", Curve->connectionHands[m]);
            int ndx = baseGroup->IndexOf((TList*) Curve->connectionHands[m]);
            if ( ndx != -1){
              if ( Curve->leftrightDist[m] < minDist){
                selectedBaseCurve = Curve->connectionHands[m];
                selectedBaseCurveIndex = ndx;
                minDist = Curve->leftrightDist[m];
                selectedConHand = m;
                selectedCurve = Curve;
                selectedCurveIndex = n;

                selectedGroup = baseGroup;


                Vertex *connLastVer = (Vertex*) selectedCurve->polyVerList[selectedConHand]->Last();
                Vertex *selectedBaseCurveVer = (Vertex*) selectedBaseCurve->Last();
                if (samePoint(connLastVer->po, selectedBaseCurveVer->po))
                  joineToFirstOnBaseCurve = false;
                else
                  joineToFirstOnBaseCurve = true;
              }
           }
         }
       }
     }

     if (selectedBaseCurve != NULL){

        //write_oneGroup("selectedGroup.scr", selectedGroup);
        //writeOnePolygon("selectedBaseCurve.scr", selectedBaseCurve);
        //writeOnePolygon("selectedCurve.scr", selectedCurve);
        //writeInfoOfCurve_LeftRightLists("selectedCurve_Conn.scr", selectedCurve, selectedConHand);
        if (joineToFirstOnBaseCurve){
          oneCurve *selectedBasePrevCurve = (oneCurve *) selectedGroup->Items[selectedBaseCurveIndex-1];
          //writeOnePolygon("selectedBasePrevCurve.scr", selectedBasePrevCurve);
          oneCurve *firstCurve = (oneCurve*) oneGroup->First();
          oneCurve *lastCurve = (oneCurve*) oneGroup->Last();
          //writeInfoOfCurve_LeftRightLists("selectedCurve_Conn.scr", selectedCurve, selectedConHand);
          Vertex *selectedBaseCurveFirstVer = (Vertex*) selectedBaseCurve->First();
          Vertex *selectedCurveFirstVer = (Vertex*) selectedCurve->First();
          makeRunOnMainPolygonEdge( (oneCurve*) Polygons->Items[selectedCurveFirstVer->PolyIndex],
                    selectedBaseCurveFirstVer->PolyVertex,
                    ((Vertex*) firstCurve->First())->PolyVertex,
                    selectedBasePrevCurve->polyVerList[selectedBasePrevCurve->ConnectedNext]);
           //writeInfoOfCurve_LeftRightLists("selectedBasePrevCurve_Conn.scr", selectedBasePrevCurve);


           if (firstCurve->ConnectedNext == rightPrevCurve)
             firstCurve->ConnectedPrev = leftPrevCurve;
           else if (firstCurve->ConnectedNext == rightNextCurve)
             firstCurve->ConnectedPrev = leftNextCurve;
           else if (firstCurve->ConnectedNext == leftPrevCurve)
             firstCurve->ConnectedPrev = rightNextCurve;
           else if (firstCurve->ConnectedNext == leftNextCurve)
             firstCurve->ConnectedPrev = rightPrevCurve;
           firstCurve->connectionHands[firstCurve->ConnectedPrev] = selectedBasePrevCurve;
           selectedBasePrevCurve->connectionHands[selectedBasePrevCurve->ConnectedNext] = firstCurve;
           firstCurve->polyVerList[firstCurve->ConnectedPrev]->Clear();
           for (int n = selectedBasePrevCurve->polyVerList[selectedBasePrevCurve->ConnectedNext]->Count-1; n >= 0; --n)
             firstCurve->polyVerList[firstCurve->ConnectedPrev]->Add(selectedBasePrevCurve->polyVerList[selectedBasePrevCurve->ConnectedNext]->Items[n]);
           //writeInfoOfCurve_LeftRightLists("firstCurve_Conn.scr", firstCurve);


           selectedBaseCurve->polyVerList[selectedBaseCurve->ConnectedPrev]->Clear();
           makeRunOnMainPolygonEdge( (oneCurve*) Polygons->Items[selectedCurveFirstVer->PolyIndex],
                    ((Vertex*) selectedBaseCurve->First())->PolyVertex,
                    ((Vertex*) lastCurve->Last())->PolyVertex,
                    selectedBaseCurve->polyVerList[selectedBaseCurve->ConnectedPrev]);
           //writeInfoOfCurve_LeftRightLists("selectedBaseCurve_Conn.scr", selectedBaseCurve);
           selectedBaseCurve->connectionHands[selectedBaseCurve->ConnectedPrev] = lastCurve;
           if (lastCurve->ConnectedPrev == rightPrevCurve)
             lastCurve->ConnectedNext = leftPrevCurve;
           else if (lastCurve->ConnectedPrev == rightNextCurve)
             lastCurve->ConnectedNext = leftNextCurve;
           else if (lastCurve->ConnectedPrev == leftPrevCurve)
             lastCurve->ConnectedNext = rightNextCurve;
           else if (lastCurve->ConnectedPrev == leftNextCurve)
             lastCurve->ConnectedNext = rightPrevCurve;
           lastCurve->connectionHands[lastCurve->ConnectedNext] = selectedBaseCurve;
           lastCurve->polyVerList[lastCurve->ConnectedNext]->Clear();
           for (int n = selectedBaseCurve->polyVerList[selectedBaseCurve->ConnectedPrev]->Count-1; n >=0; --n)
              lastCurve->polyVerList[lastCurve->ConnectedNext]->Add(selectedBaseCurve->polyVerList[selectedBaseCurve->ConnectedPrev]->Items[n]);
           //writeInfoOfCurve_LeftRightLists("lastCurve_Conn.scr", lastCurve);
           for (int i = oneGroup->Count-1; i >= 0; --i)
             selectedGroup->Insert(selectedBaseCurveIndex, oneGroup->Items[i]);
           oneGroup->Clear();
           //write_oneGroup("selectedGroup.scr", selectedGroup);

        }
        else{
           //Join to last of the baseCurve
           //writeInfoOfCurve_LeftRightLists("selectedCurve_Conn.scr", selectedCurve, selectedConHand);
           oneCurve *selectedBaseNextCurve = (oneCurve *) selectedGroup->Items[selectedBaseCurveIndex+1];
           //writeOnePolygon("selectedBaseNextCurve.scr", selectedBaseNextCurve);
           //writeInfoOfCurve_LeftRightLists("selectedBaseNextCurve_Conn.scr", selectedBaseNextCurve);
           oneCurve *firstCurve = (oneCurve*) oneGroup->First();
           oneCurve *lastCurve = (oneCurve*) oneGroup->Last();
           Vertex *selectedCurveLastVer = (Vertex*) selectedBaseCurve->Last();
           //writeOnePolygon("firstCurve.scr", firstCurve);
           //writeOnePolygon("lastCurve.scr", lastCurve);
           //writeInfoOfCurve_LeftRightLists("selectedBaseCurve_Conn.scr", selectedBaseCurve);
           selectedBaseCurve->polyVerList[selectedBaseCurve->ConnectedNext]->Clear();
           makeRunOnMainPolygonEdge( (oneCurve*) Polygons->Items[selectedCurveLastVer->PolyIndex],
                    ((Vertex*) selectedBaseCurve->Last())->PolyVertex,
                    ((Vertex*) firstCurve->First())->PolyVertex,
                    selectedBaseCurve->polyVerList[selectedBaseCurve->ConnectedNext]);
           //writeInfoOfCurve_LeftRightLists("selectedBaseCurve_Conn.scr", selectedBaseCurve);
           if (firstCurve->ConnectedNext == rightPrevCurve)
             firstCurve->ConnectedPrev = leftPrevCurve;
           else if (firstCurve->ConnectedNext == rightNextCurve)
             firstCurve->ConnectedPrev = leftNextCurve;
           else if (firstCurve->ConnectedNext == leftPrevCurve)
             firstCurve->ConnectedPrev = rightNextCurve;
           else if (firstCurve->ConnectedNext == leftNextCurve)
             firstCurve->ConnectedPrev = rightPrevCurve;
           firstCurve->connectionHands[firstCurve->ConnectedPrev] = selectedBaseCurve;
           selectedBaseCurve->connectionHands[selectedBaseCurve->ConnectedNext] = firstCurve;
           firstCurve->polyVerList[firstCurve->ConnectedPrev]->Clear();
           for (int n = selectedBaseCurve->polyVerList[selectedBaseCurve->ConnectedNext]->Count-1; n >= 0; --n)
             firstCurve->polyVerList[firstCurve->ConnectedPrev]->Add(selectedBaseCurve->polyVerList[selectedBaseCurve->ConnectedNext]->Items[n]);
           //writeInfoOfCurve_LeftRightLists("firstCurve_Conn.scr", firstCurve);

           makeRunOnMainPolygonEdge( (oneCurve*) Polygons->Items[selectedCurveLastVer->PolyIndex],
                    ((Vertex*) selectedBaseCurve->Last())->PolyVertex,
                    ((Vertex*) lastCurve->Last())->PolyVertex,
                    selectedBaseNextCurve->polyVerList[selectedBaseNextCurve->ConnectedPrev]);
           //writeInfoOfCurve_LeftRightLists("selectedBaseNextCurve_Conn.scr", selectedBaseNextCurve);
           selectedBaseNextCurve->connectionHands[selectedBaseNextCurve->ConnectedPrev] = lastCurve;
           if (lastCurve->ConnectedPrev == rightPrevCurve)
             lastCurve->ConnectedNext = leftPrevCurve;
           else if (lastCurve->ConnectedPrev == rightNextCurve)
             lastCurve->ConnectedNext = leftNextCurve;
           else if (lastCurve->ConnectedPrev == leftPrevCurve)
             lastCurve->ConnectedNext = rightNextCurve;
           else if (lastCurve->ConnectedPrev == leftNextCurve)
             lastCurve->ConnectedNext = rightPrevCurve;
           lastCurve->connectionHands[lastCurve->ConnectedNext] = selectedBaseNextCurve;
           lastCurve->polyVerList[lastCurve->ConnectedNext]->Clear();
           for (int n = selectedBaseNextCurve->polyVerList[selectedBaseNextCurve->ConnectedPrev]->Count-1; n >=0; --n)
              lastCurve->polyVerList[lastCurve->ConnectedNext]->Add(selectedBaseNextCurve->polyVerList[selectedBaseNextCurve->ConnectedPrev]->Items[n]);
           //writeInfoOfCurve_LeftRightLists("lastCurve_Conn.scr", lastCurve);
           for (int i = oneGroup->Count-1; i >= 0; --i)
             selectedGroup->Insert(selectedBaseCurveIndex+1, oneGroup->Items[i]);
           oneGroup->Clear();
           //write_oneGroup("selectedGroup.scr", selectedGroup);
        }
     }
   }

}


void InsertaGroupToCurveStart(TList *Polygons, TList *oneGroup, TList *baseGroup, oneCurve *baseCurve,
                                 oneCurve *firstCurve, oneCurve *lastCurve, oneCurve* basePrevCurve, int firstConnectionHandIndex, int IndexInBaseFromFirst)
{
               //writeOnePolygon("basePrevCurve.scr", basePrevCurve);
               //writeInfoOfCurve_LeftRightLists("basePrevCurve_Conn.scr", basePrevCurve);

               makeRunOnMainPolygonEdge((oneCurve*)Polygons->Items[((Vertex*) baseCurve->First())->PolyIndex],
                    ((Vertex*) baseCurve->First())->PolyVertex,
                    ((Vertex*) firstCurve->First())->PolyVertex, basePrevCurve->polyVerList[basePrevCurve->ConnectedNext]);

               //writeInfoOfCurve_LeftRightLists("basePrevCurve_Conn.scr", basePrevCurve);

               basePrevCurve->connectionHands[basePrevCurve->ConnectedNext] = firstCurve;
               firstCurve->ConnectedPrev = firstConnectionHandIndex;
               firstCurve->connectionHands[firstCurve->ConnectedPrev] = basePrevCurve;
               firstCurve->polyVerList[firstCurve->ConnectedPrev]->Clear();
               for (int n = basePrevCurve->polyVerList[basePrevCurve->ConnectedNext]->Count-1; n >= 0; --n)
                 firstCurve->polyVerList[firstCurve->ConnectedPrev]->Add( basePrevCurve->polyVerList[basePrevCurve->ConnectedNext]->Items[n] );

               if (firstCurve != lastCurve){
                  if ( lastCurve->ConnectedPrev == leftNextCurve)
                    lastCurve->ConnectedNext = rightPrevCurve;
                  else if ( lastCurve->ConnectedPrev == rightNextCurve)
                    lastCurve->ConnectedNext = leftPrevCurve;
                  else if ( lastCurve->ConnectedPrev == leftNextCurve)
                    lastCurve->ConnectedNext = rightPrevCurve;
                  else if ( lastCurve->ConnectedPrev == rightPrevCurve)
                    lastCurve->ConnectedNext = leftNextCurve;
                  else if ( lastCurve->ConnectedPrev == leftPrevCurve)
                    lastCurve->ConnectedNext = rightNextCurve;
               }
               else
               { //firstCurve == lastCurve
                   if ( lastCurve->ConnectedPrev == leftNextCurve )
                      lastCurve->ConnectedNext = rightNextCurve;
                    else
                    lastCurve->ConnectedNext = leftNextCurve;
               }

               //writeOnePolygon("lastCurve.scr", lastCurve);
               //writeInfoOfCurve_LeftRightLists("lastCurve_Conn.scr", lastCurve);


               lastCurve->polyVerList[lastCurve->ConnectedNext]->Clear();
               makeRunOnMainPolygonEdge((oneCurve*)Polygons->Items[((Vertex*) lastCurve->Last())->PolyIndex],
                                        ((Vertex*) lastCurve->Last())->PolyVertex,
                                        ((Vertex*)baseCurve->First())->PolyVertex , lastCurve->polyVerList[lastCurve->ConnectedNext]);

               //writeInfoOfCurve_LeftRightLists("lastCurve_Conn.scr", lastCurve, lastCurve->ConnectedNext);

               lastCurve->connectionHands[lastCurve->ConnectedNext] = baseCurve;

               //writeOnePolygon("baseCurve.scr", baseCurve);
               //writeInfoOfCurve_LeftRightLists("baseCurve_Conn.scr", baseCurve);


               baseCurve->polyVerList[baseCurve->ConnectedPrev]->Clear();
               for (int n = lastCurve->polyVerList[lastCurve->ConnectedNext]->Count-1; n >= 0; --n)
                  baseCurve->polyVerList[baseCurve->ConnectedPrev]->Add( lastCurve->polyVerList[lastCurve->ConnectedNext]->Items[n]);

               //writeInfoOfCurve_LeftRightLists("baseCurve_Conn.scr", baseCurve);


               for (int n = oneGroup->Count-1; n >= 0; --n)
                  baseGroup->Insert(IndexInBaseFromFirst, oneGroup->Items[n]);
               oneGroup->Clear();
               //write_oneGroup("baseGroup.scr", baseGroup);

}


void AddaGroupToCurveEnd(TList *Polygons, TList *oneGroup, TList *baseGroup, oneCurve *baseCurve,
                                 oneCurve *firstCurve, oneCurve *lastCurve)
{

      if (baseCurve->ConnectedPrev == leftNextCurve)
        baseCurve->ConnectedNext = rightPrevCurve;
      else if (baseCurve->ConnectedPrev == leftPrevCurve)
        baseCurve->ConnectedNext = rightNextCurve;
      else if (baseCurve->ConnectedPrev == rightPrevCurve)
        baseCurve->ConnectedNext = leftNextCurve;
      else if (baseCurve->ConnectedPrev == rightNextCurve)
        baseCurve->ConnectedNext = leftPrevCurve;


      baseCurve->polyVerList[baseCurve->ConnectedNext]->Clear();
      makeRunOnMainPolygonEdge((oneCurve*)Polygons->Items[((Vertex*) baseCurve->Last())->PolyIndex],
                    ((Vertex*) baseCurve->Last())->PolyVertex,
                    ((Vertex*) firstCurve->First())->PolyVertex,
                    baseCurve->polyVerList[baseCurve->ConnectedNext]);

      if (firstCurve->ConnectedNext == leftNextCurve)
        firstCurve->ConnectedPrev = rightPrevCurve;
      else if (firstCurve->ConnectedNext == leftPrevCurve)
        firstCurve->ConnectedPrev = rightNextCurve;
      else if (firstCurve->ConnectedNext == rightPrevCurve)
        firstCurve->ConnectedPrev = leftNextCurve;
      else if (firstCurve->ConnectedNext == rightNextCurve)
        firstCurve->ConnectedPrev = leftPrevCurve;

      baseCurve->connectionHands[baseCurve->ConnectedNext] = firstCurve;
      firstCurve->connectionHands[firstCurve->ConnectedPrev] = baseCurve;
      firstCurve->polyVerList[firstCurve->ConnectedPrev]->Clear();
      for (int i = baseCurve->polyVerList[baseCurve->ConnectedNext]->Count-1; i >=0; --i)
        firstCurve->polyVerList[firstCurve->ConnectedPrev]->Add(baseCurve->polyVerList[baseCurve->ConnectedNext]->Items[i]);
      for (int n = 0; n < oneGroup->Count; ++n)
        baseGroup->Add(oneGroup->Items[n]);
      oneGroup->Clear();
      //write_oneGroup("baseGroup.scr", baseGroup);
}


void InsertaGroupToCurveEnd(TList *Polygons, TList *oneGroup, TList *baseGroup, oneCurve *baseCurve,
                                 oneCurve *firstCurve, oneCurve *lastCurve, oneCurve* baseNextCurve, int firstConnectionHandIndex, int IndexInBaseFromFirst)
{
              //writeInfoOfCurve_LeftRightLists("baseNextCurve_Conn.scr", baseNextCurve);
              makeRunOnMainPolygonEdge((oneCurve*)Polygons->Items[((Vertex*) baseCurve->Last())->PolyIndex],
                    ((Vertex*) baseCurve->Last())->PolyVertex,
                    ((Vertex*) lastCurve->Last())->PolyVertex,
                    baseNextCurve->polyVerList[baseNextCurve->ConnectedPrev]);

              //writeInfoOfCurve_LeftRightLists("baseNextCurve_Conn.scr", baseNextCurve);

              Vertex *firstCurveVer = (Vertex*)firstCurve->First();

              Vertex *v = (Vertex*) baseCurve->polyVerList[leftNextCurve]->Last();
              if (samePoint(v->po, firstCurveVer->po))
                 baseCurve->ConnectedNext = leftNextCurve;
              else{
                v = (Vertex*) baseCurve->polyVerList[rightNextCurve]->Last();
                if (samePoint(v->po, firstCurveVer->po))
                   baseCurve->ConnectedNext = rightNextCurve;
                else {
                   v = (Vertex*) baseCurve->polyVerList[leftPrevCurve]->Last();
                   if (samePoint(v->po, firstCurveVer->po))
                     baseCurve->ConnectedNext = leftPrevCurve;
                   else{
                     v = (Vertex*) baseCurve->polyVerList[rightPrevCurve]->Last();
                     if (samePoint(v->po, firstCurveVer->po))
                       baseCurve->ConnectedNext = rightPrevCurve;
                   }
                }
              }

              baseCurve->connectionHands[baseCurve->ConnectedNext] = firstCurve;

              Vertex *baseLastV = (Vertex*) baseCurve->Last();
              v = (Vertex*) firstCurve->polyVerList[leftNextCurve]->Last();
              if (samePoint(v->po, baseLastV->po))
                 firstCurve->ConnectedPrev = leftNextCurve;
              else{
                v = (Vertex*) firstCurve->polyVerList[rightNextCurve]->Last();
                if (samePoint(v->po, baseLastV->po))
                   firstCurve->ConnectedPrev = rightNextCurve;
                else {
                   v = (Vertex*) firstCurve->polyVerList[leftPrevCurve]->Last();
                   if (samePoint(v->po, baseLastV->po))
                     firstCurve->ConnectedPrev = leftPrevCurve;
                   else{
                     v = (Vertex*) firstCurve->polyVerList[rightPrevCurve]->Last();
                     if (samePoint(v->po, baseLastV->po))
                       firstCurve->ConnectedPrev = rightPrevCurve;
                   }
                }
              }
               //firstCurve->ConnectedPrev = firstConnectionHandIndex;
               firstCurve->connectionHands[firstCurve->ConnectedPrev] = baseCurve;

               if (firstCurve != lastCurve){
                    ////lastCurve->ConnectedNext = leftNextCurve;
                    if (lastCurve->ConnectedPrev == leftNextCurve)
                      lastCurve->ConnectedNext = rightPrevCurve;
                    else if (lastCurve->ConnectedPrev == leftPrevCurve)
                      lastCurve->ConnectedNext = rightNextCurve;
                    else if (lastCurve->ConnectedPrev == rightNextCurve)
                      lastCurve->ConnectedNext = leftPrevCurve;
                    else if (lastCurve->ConnectedPrev == rightPrevCurve)
                      lastCurve->ConnectedNext = leftNextCurve;
               }
               else
               { //firstCurve == lastCurve
                   if ( lastCurve->ConnectedPrev == leftNextCurve )
                      lastCurve->ConnectedNext = rightNextCurve;
                    else
                    lastCurve->ConnectedNext = leftNextCurve;
               }


               lastCurve->connectionHands[lastCurve->ConnectedNext] = baseNextCurve;
               baseNextCurve->connectionHands[baseNextCurve->ConnectedPrev] = lastCurve;
               lastCurve->polyVerList[lastCurve->ConnectedNext]->Clear();
               for (int n = baseNextCurve->polyVerList[baseNextCurve->ConnectedPrev]->Count-1; n >= 0; --n)
                  lastCurve->polyVerList[lastCurve->ConnectedNext]->Add( baseNextCurve->polyVerList[baseNextCurve->ConnectedPrev]->Items[n]);
               for (int n = oneGroup->Count-1; n >= 0; --n)
                  baseGroup->Insert(IndexInBaseFromFirst+1, oneGroup->Items[n]);
               oneGroup->Clear();
               //write_oneGroup("baseGroup.scr", baseGroup);
}


void InsertaGroupWhereStartEndAreNotOnFirstPolygonAndCloseToAnotherGroup(TList *Polygons, TList *allObjGroups)
{
   TList *groupIndex = new TList();

   for (int i = allObjGroups->Count-1; i >= 0; --i)
   {
     TList *oneGroup = (TList*) allObjGroups->Items[i];
     if (oneGroup->Count == 0) continue;

     if (groupIndex->IndexOf((Pointer*)i) != -1) continue;

     //write_oneGroup("oneGroup.scr", oneGroup);

     oneCurve *firstCurve = (oneCurve*) oneGroup->First();
     oneCurve *lastCurve  = (oneCurve*) oneGroup->Last();
//writeInfoOfCurve_LeftRightLists("firstCurve_Conn.scr", firstCurve);
//writeInfoOfCurve_LeftRightLists("lastCurve_Conn.scr", lastCurve);
     //below means, Start / End must not be on main Polygon
     //if ( (((Vertex*) firstCurve->First())->PolyIndex == 0) && (((Vertex*) lastCurve->Last())->PolyIndex == 0) ) continue;
     //below means both start end must be on one Polygon
     if ( ((Vertex*) firstCurve->First())->PolyIndex != ((Vertex*) lastCurve->Last())->PolyIndex ) continue;


     for (int j = 0;  j < allObjGroups->Count; ++j){
       if ( i == j ) continue;
       if (oneGroup->Count == 0) break;
       TList *baseGroup = (TList*) allObjGroups->Items[j];
       if (baseGroup->Count == 0) continue;
       int firstConnectionDist, lastConnectionDist;

       oneCurve *baseFirstCurve = (oneCurve*) baseGroup->First();
       oneCurve *baseLastCurve  = (oneCurve*) baseGroup->Last();



       //write_oneGroup("baseGroup.scr", baseGroup);

       int firstConnectionHandIndex = leftNextCurve;
       int IndexInBaseFromFirst = baseGroup->IndexOf(firstCurve->connectionHands[leftNextCurve]);
       if ( IndexInBaseFromFirst == -1){
          firstConnectionHandIndex = rightNextCurve;
          IndexInBaseFromFirst = baseGroup->IndexOf(firstCurve->connectionHands[rightNextCurve]);
          if ( IndexInBaseFromFirst == -1){
            firstConnectionHandIndex = leftPrevCurve;
            IndexInBaseFromFirst = baseGroup->IndexOf(firstCurve->connectionHands[leftPrevCurve]);
            if ( IndexInBaseFromFirst == -1){
              firstConnectionHandIndex = rightPrevCurve;
              IndexInBaseFromFirst = baseGroup->IndexOf(firstCurve->connectionHands[rightPrevCurve]);
              if ( IndexInBaseFromFirst != -1)
                firstConnectionDist = firstCurve->leftrightDist[rightPrevCurve];
            }
            else
               firstConnectionDist = firstCurve->leftrightDist[leftPrevCurve];
          }
          else
             firstConnectionDist = firstCurve->leftrightDist[rightNextCurve];
       }
       else
         firstConnectionDist = firstCurve->leftrightDist[leftNextCurve];



       int lastConnectionHandIndex = rightPrevCurve;
       int IndexInBaseFromLast = baseGroup->IndexOf(lastCurve->connectionHands[rightPrevCurve]);
       if ( IndexInBaseFromLast == -1){
          lastConnectionHandIndex = rightNextCurve;
          IndexInBaseFromLast = baseGroup->IndexOf(lastCurve->connectionHands[rightNextCurve]);
          if ( IndexInBaseFromLast != -1)
             lastConnectionDist = lastCurve->leftrightDist[rightNextCurve];
       }
       else
         lastConnectionDist = lastCurve->leftrightDist[rightPrevCurve];

       if ( (IndexInBaseFromFirst != -1) && (IndexInBaseFromLast != -1) ){
         if (firstConnectionDist < lastConnectionDist)
             IndexInBaseFromLast = -1;
         else
           IndexInBaseFromFirst = -1;

       }

        if (IndexInBaseFromFirst != -1){
          groupIndex->Add((Pointer*)i);
          //allObjGroups->Items[i] = NULL;
          Vertex *v = (Vertex *) firstCurve->polyVerList[firstConnectionHandIndex]->Last();
          oneCurve *baseCurve = (oneCurve*)baseGroup->Items[IndexInBaseFromFirst];
          //writeOnePolygon("baseCurve.scr", baseCurve);
          //writeInfoOfCurve_LeftRightLists("baseCurve_Conn.scr", baseCurve);

          if (samePoint( ((Vertex*) baseCurve->First())->po, v->po)){
             oneCurve *basePrevCurve = (oneCurve*)baseGroup->Items[IndexInBaseFromFirst-1];
             //writeOnePolygon("basePrevCurve.scr", basePrevCurve);
             //writeInfoOfCurve_LeftRightLists("basePrevCurve_Conn.scr", basePrevCurve);


             InsertaGroupToCurveStart(Polygons, oneGroup, baseGroup, baseCurve, firstCurve, lastCurve, basePrevCurve, firstConnectionHandIndex, IndexInBaseFromFirst);

             //write_oneGroup("baseGroup.scr", baseGroup);
          }
          else{
            oneCurve *baseNextCurve = NULL;
            if ( IndexInBaseFromFirst < baseGroup->Count-1){
              baseNextCurve = (oneCurve*)baseGroup->Items[IndexInBaseFromFirst+1];
              //writeOnePolygon("baseNextCurve.scr", baseNextCurve);
              //writeInfoOfCurve_LeftRightLists("baseNextCurve_Conn.scr", baseNextCurve);
              InsertaGroupToCurveEnd(Polygons, oneGroup, baseGroup, baseCurve, firstCurve, lastCurve, baseNextCurve, firstConnectionHandIndex, IndexInBaseFromFirst);
            }
            else
              AddaGroupToCurveEnd(Polygons, oneGroup, baseGroup, baseCurve, firstCurve, lastCurve);

            //write_oneGroup("baseGroup.scr", baseGroup);
          }
          ++i;
          break;
        }
        else if (IndexInBaseFromLast != -1){

           groupIndex->Add((Pointer*)i);
            reverseOneGroup(oneGroup);
            //write_oneGroup("oneGroup.scr", oneGroup);
            firstCurve = (oneCurve*) oneGroup->First();
            lastCurve  = (oneCurve*) oneGroup->Last();

//writeInfoOfCurve_LeftRightLists("firstCurve_Conn.scr", firstCurve);
//writeInfoOfCurve_LeftRightLists("lastCurve_Conn.scr", lastCurve);




          if (lastConnectionHandIndex == rightNextCurve)
            lastConnectionHandIndex = leftNextCurve;
          else //so it is rightPrevCurve
            lastConnectionHandIndex = leftPrevCurve;

          Vertex *v = (Vertex *) firstCurve->polyVerList[lastConnectionHandIndex]->Last();
          oneCurve *baseCurve = (oneCurve*)baseGroup->Items[IndexInBaseFromLast];

          //writeOnePolygon("baseCurve.scr", baseCurve);
          //writeInfoOfCurve_LeftRightLists("baseCurve_Conn.scr", baseCurve);


          if (samePoint( ((Vertex*) baseCurve->First())->po, v->po)){
             oneCurve *basePrevCurve = (oneCurve*)baseGroup->Items[IndexInBaseFromLast-1];
             //writeOnePolygon("basePrevCurve.scr", basePrevCurve);

             InsertaGroupToCurveStart(Polygons, oneGroup, baseGroup, baseCurve, firstCurve, lastCurve, basePrevCurve, lastConnectionHandIndex, IndexInBaseFromLast);
             //write_oneGroup("baseGroup.scr", baseGroup);
          }
          else{
            oneCurve *baseNextCurve = (oneCurve*)baseGroup->Items[IndexInBaseFromLast+1];
          //writeOnePolygon("baseNextCurve.scr", baseNextCurve);
          //writeInfoOfCurve_LeftRightLists("baseNextCurve_Conn.scr", baseNextCurve);
            InsertaGroupToCurveEnd(Polygons, oneGroup, baseGroup, baseCurve, firstCurve, lastCurve, baseNextCurve, lastConnectionHandIndex, IndexInBaseFromLast);
            //write_oneGroup("baseGroup.scr", baseGroup);
          }
          ++i;
          break;
        }
     }
   }

   for (int i = 0; i < groupIndex->Count; ++i){
      allObjGroups->Items[(int) groupIndex->Items[i]] = NULL;
   }
   delete groupIndex;
   allObjGroups->Pack();
}


void reverseOneGroup(TList *group)
{
  oneCurve *curve1, *curve2;
  for (int n = 0; n < group->Count/2; ++n)
  {
    curve1 = (oneCurve *) group->Items[n];
    curve2 = (oneCurve *) group->Items[group->Count-1-n];
    //writeOnePolygon("curve1.scr", curve1);
    //writeInfoOfCurve_LeftRightLists("curve1_Conn.scr", curve1);

    //writeOnePolygon("curve2.scr", curve2);
    //writeInfoOfCurve_LeftRightLists("curve2_Conn.scr", curve2);

    curve1->reverse();
    curve2->reverse();

    //writeOnePolygon("curve1.scr", curve1);
    //writeInfoOfCurve_LeftRightLists("curve1_Conn.scr", curve1);

    //writeOnePolygon("curve2.scr", curve2);
    //writeInfoOfCurve_LeftRightLists("curve2_Conn.scr", curve2);

    group->Exchange(n, group->Count-1-n);
  }

  if ( (group->Count % 2 ) != 0){
    curve1 = (oneCurve *) group->Items[group->Count/2];
    //writeOnePolygon("curve1.scr", curve1);
    //writeInfoOfCurve_LeftRightLists("curve1_Conn.scr", curve1);
    curve1->reverse();
    //writeOnePolygon("curve1.scr", curve1);
    //writeInfoOfCurve_LeftRightLists("curve1_Conn.scr", curve1);
  }

}

int findClosestGroupFromLast(TList *allObjGroups, TList *Polygons, TList *candidateConnectList, TList *group1, oneCurve *firstCurveOfFirstGroup, Vertex* sV){

   if (candidateConnectList->Count == 0)
     return -1;
   oneCurve *lastCurve;
   int DistNext, DistPrev, minDist = 0x0FFFFFFF;
   TList *candidateGroup;
   TList *runVerList = new TList();
   TList *runListNext = new TList();
   TList *runListPrev = new TList();


   for (int i = 0; i < candidateConnectList->Count; ++i){
      TList *aGroup = (TList *) candidateConnectList->Items[i];
      lastCurve = (oneCurve *) aGroup->Last();
      Vertex *lastVer = (Vertex *) lastCurve->Last();
      Vertex *PolyVer = lastVer->PolyVertex;
      Vertex *nextVer = PolyVer;
      Vertex *prevVer = PolyVer;
      runListNext->Clear();
      runListPrev->Clear();
      DistNext = DistPrev = 0;
      runListNext->Add(nextVer);
      while(nextVer != sV->PolyVertex){
        DistNext += Distance(nextVer->po, nextVer->nextVer->po);
        nextVer = nextVer->nextVer;
        runListNext->Add(nextVer);
      }
      runListPrev->Add(prevVer);
      while(prevVer != sV->PolyVertex){
        DistPrev += Distance(prevVer->po, prevVer->prevVer->po);
        prevVer = prevVer->prevVer;
        runListPrev->Add(prevVer);
      }

      if ( (DistNext < DistPrev) && (DistNext < minDist) ) {
        runVerList->Clear();
        for (int n = 0; n < runListNext->Count; ++n)
          runVerList->Add(runListNext->Items[n]);
        minDist = DistNext;
        candidateGroup = aGroup;
      }
      else if ( (DistPrev < DistNext) && (DistPrev < minDist) ) {
        runVerList->Clear();
        for (int n = 0; n < runListPrev->Count; ++n)
          runVerList->Add(runListPrev->Items[n]);
        minDist = DistPrev;
        candidateGroup = aGroup;
      }
   }

   //write_oneGroup("candidateGroup_.scr", candidateGroup);
   //write_oneGroup("group1.scr", group1);

   //reverseOneGroup(candidateGroup);
   lastCurve = (oneCurve*)candidateGroup->Last();
   //writeInfoOfCurve_LeftRightLists("lastCurve_Conn.scr", lastCurve);
   //writeOnePolygon("lastCurve.scr", lastCurve);

   //lastCurve->ConnectedNext = rightPrevCurve;

   if (lastCurve->ConnectedPrev == leftPrevCurve)
     lastCurve->ConnectedNext = rightNextCurve;
   else if (lastCurve->ConnectedPrev == leftNextCurve)
     lastCurve->ConnectedNext = rightPrevCurve;
   else if (lastCurve->ConnectedPrev == rightNextCurve)
     lastCurve->ConnectedNext = leftPrevCurve;
   else
     lastCurve->ConnectedNext = leftNextCurve;

   lastCurve->polyVerList[lastCurve->ConnectedNext]->Clear();
   for (int n = 0; n < runVerList->Count; ++n){
     lastCurve->polyVerList[lastCurve->ConnectedNext]->Add(runVerList->Items[n]);
   }
   //writeInfoOfCurve_LeftRightLists("lastCurve_Conn.scr", lastCurve);
   //write_oneGroup("group1.scr", group1);
   //writeInfoOfCurve_LeftRightLists("firstCurve_Conn.scr", firstCurveOfFirstGroup);
   //writeOnePolygon("FirstCurve.scr", firstCurveOfFirstGroup);

   if (firstCurveOfFirstGroup->ConnectedNext == leftPrevCurve)
     firstCurveOfFirstGroup->ConnectedPrev = rightNextCurve;
   else if (lastCurve->ConnectedNext == leftNextCurve)
     firstCurveOfFirstGroup->ConnectedPrev = rightPrevCurve;
   else if (lastCurve->ConnectedNext == rightNextCurve)
     firstCurveOfFirstGroup->ConnectedPrev = leftPrevCurve;
   else
     firstCurveOfFirstGroup->ConnectedPrev = leftNextCurve;


   firstCurveOfFirstGroup->polyVerList[firstCurveOfFirstGroup->ConnectedPrev]->Clear();
   for (int n = runVerList->Count-1; n >= 0; --n){
     firstCurveOfFirstGroup->polyVerList[firstCurveOfFirstGroup->ConnectedPrev]->Add(runVerList->Items[n]);
   }

   for (int n = 0; n < group1->Count; ++n){
      candidateGroup->Add(group1->Items[n]);
      group1->Items[n] = NULL;
   }
   group1->Pack();

   delete runVerList;
   delete runListNext;
   delete runListPrev;
   return (allObjGroups->IndexOf(candidateGroup));
}


bool findClosestGroupToFirstGroupEndAndJoinToFirstGroup(TList * Polygons, TList *firstGroup, TList* candidateConnectList, TList *needToBeResersedList)
{

   if (candidateConnectList->Count == 0)
     return false;

   oneCurve *firstGroupLastCurve = (oneCurve*) firstGroup->Last();
   Vertex *firstGroupEndVer = (Vertex *) firstGroupLastCurve->Last();

   int DistNext, DistPrev, minDist = 0x0FFFFFFF;
   TList *runVerList = new TList();
   TList *runListNext = new TList();
   TList *runListPrev = new TList();
   TList *candidateGroup = NULL;
   int  candidateGroupIndex = -1;

   for (int nextGroupIndex = 0; nextGroupIndex < candidateConnectList->Count; ++nextGroupIndex){
      TList *nextGroup = (TList *) candidateConnectList->Items[nextGroupIndex];
      oneCurve *nextGroupLastCurve = (oneCurve *) nextGroup->Last();
      oneCurve *nextGroupFirstCurve = (oneCurve *) nextGroup->First();
      Vertex *nextGroupEndVer = (Vertex *) nextGroupLastCurve->Last();
      Vertex *nextGroupStartVer = (Vertex *) nextGroupFirstCurve->First();
      
      Vertex *nextGroupVer;
      if (needToBeResersedList->Items[nextGroupIndex] != NULL)
         nextGroupVer = nextGroupEndVer;
      else
         nextGroupVer = nextGroupStartVer;


      Vertex *PolyVer = firstGroupEndVer->PolyVertex;
      Vertex *nextVer = PolyVer;
      Vertex *prevVer = PolyVer;
      runListNext->Clear();
      runListPrev->Clear();
      DistNext = DistPrev = 0;
      runListNext->Add(nextVer);
      while(nextVer != nextGroupVer->PolyVertex){
        DistNext += Distance(nextVer->po, nextVer->nextVer->po);
        nextVer = nextVer->nextVer;
        runListNext->Add(nextVer);
      }
      runListPrev->Add(prevVer);
      while(prevVer != nextGroupVer->PolyVertex){
        DistPrev += Distance(prevVer->po, prevVer->prevVer->po);
        prevVer = prevVer->prevVer;
        runListPrev->Add(prevVer);
      }

      if ( (DistNext < DistPrev) && (DistNext < minDist) ) {
        runVerList->Clear();
        for (int n = 0; n < runListNext->Count; ++n)
          runVerList->Add(runListNext->Items[n]);
        minDist = DistNext;
        candidateGroup = nextGroup;
        candidateGroupIndex = nextGroupIndex;

      }
      else if ( (DistPrev < DistNext) && (DistPrev < minDist) ) {
        runVerList->Clear();
        for (int n = 0; n < runListPrev->Count; ++n)
          runVerList->Add(runListPrev->Items[n]);
        minDist = DistPrev;
        candidateGroup = nextGroup;
        candidateGroupIndex = nextGroupIndex;
      }
   }

   if (candidateGroup == NULL)
     return false;
   //write_oneGroup("candidateGroup_.scr", candidateGroup);
   //write_oneGroup("group1.scr", group1);

   //reverseOneGroup(candidateGroup);
   //write_oneGroup("firstGroup1.scr", firstGroup, true);
   //write_oneGroup("candidateGroup1.scr", candidateGroup, true);
   if (needToBeResersedList->Items[candidateGroupIndex] != NULL)
     reverseOneGroup(candidateGroup);
   //write_oneGroup("candidateGroup2.scr", candidateGroup, true);

   oneCurve *firstGrouLastCurve = (oneCurve*) firstGroup->Last();

   oneCurve *secondGrouFirstCurve = (oneCurve*) candidateGroup->First();

   //writeInfoOfCurve_LeftRightLists("lastCurve_Conn.scr", lastCurve);
   //writeOnePolygon("lastCurve.scr", lastCurve);

   if (firstGrouLastCurve->ConnectedPrev == leftPrevCurve)
     firstGrouLastCurve->ConnectedNext = rightNextCurve;
   else if (firstGrouLastCurve->ConnectedPrev == leftNextCurve)
     firstGrouLastCurve->ConnectedNext = rightPrevCurve;
   else if (firstGrouLastCurve->ConnectedPrev == rightNextCurve)
     firstGrouLastCurve->ConnectedNext = leftPrevCurve;
   else
     firstGrouLastCurve->ConnectedNext = leftNextCurve;


   if (secondGrouFirstCurve->ConnectedNext == leftPrevCurve)
     secondGrouFirstCurve->ConnectedPrev = rightNextCurve;
   else if (secondGrouFirstCurve->ConnectedNext == leftNextCurve)
     secondGrouFirstCurve->ConnectedPrev = rightPrevCurve;
   else if (secondGrouFirstCurve->ConnectedNext == rightNextCurve)
     secondGrouFirstCurve->ConnectedPrev = leftPrevCurve;
   else
     secondGrouFirstCurve->ConnectedPrev = leftNextCurve;


   firstGroupLastCurve->connectionHands[firstGrouLastCurve->ConnectedNext] = secondGrouFirstCurve;
   secondGrouFirstCurve->connectionHands[firstGrouLastCurve->ConnectedPrev] = firstGroupLastCurve;

   firstGroupLastCurve->polyVerList[firstGrouLastCurve->ConnectedNext]->Clear();
   firstGroupEndVer = (Vertex*) firstGroupLastCurve->Last();
   secondGrouFirstCurve->polyVerList[secondGrouFirstCurve->ConnectedPrev]->Clear();
   Vertex *secondGroupFirstVer = (Vertex*) secondGrouFirstCurve->First();
   
   makeRunOnMainPolygonEdge((oneCurve*) Polygons->Items[firstGroupEndVer->PolyIndex],
                             firstGroupEndVer->PolyVertex,
                             ((Vertex*) secondGrouFirstCurve->First())->PolyVertex,
                             firstGroupLastCurve->polyVerList[firstGrouLastCurve->ConnectedNext]);
   for (int n = firstGroupLastCurve->polyVerList[firstGrouLastCurve->ConnectedNext]->Count-1; n >= 0; --n)
     secondGrouFirstCurve->polyVerList[secondGrouFirstCurve->ConnectedPrev]->Add( firstGroupLastCurve->polyVerList[firstGrouLastCurve->ConnectedNext]->Items[n] );

   for (int n = 0; n < candidateGroup->Count; ++n){
      firstGroup->Add(candidateGroup->Items[n]);
   }
   candidateGroup->Clear();
   //write_oneGroup("firstGroup2.scr", firstGroup, true);

   delete runVerList;
   delete runListNext;
   delete runListPrev;
   return true;
}

//This joins groups where Start and end are on different polygob other than the main poly
bool Join_Stupid_Groups(TList *Polygons, TList *allObjGroups)
{
   bool Result = false;
   oneCurve *firstGroupFirstCurve, *firstGroupLastCurve;
   TList *firstGroup, *nextGroup;
   TList *candidateConnectList = new TList();
   TList *needToBeResersedList = new TList();

   Vertex *firstGroupStartVer , *firstGroupEndVer;

   // Group1 Start at PolyN and end on PolyM
   // so we search any poly started on PolyN, (which ends on another poly)
   // OR End on PolyN and start on another Poly (needs Reverse)
   for (int i = 0; i < allObjGroups->Count; ++i){
     firstGroup = (TList*) allObjGroups->Items[i];
     if (firstGroup->Count == 0) continue;
     //write_oneGroup("first_Group.scr", firstGroup);
     firstGroupFirstCurve = (oneCurve*) firstGroup->First();
     firstGroupLastCurve  = (oneCurve*) firstGroup->Last();
     firstGroupStartVer = (Vertex*) firstGroupFirstCurve->First();
     firstGroupEndVer = (Vertex*) firstGroupLastCurve->Last();
     candidateConnectList->Clear();
     needToBeResersedList->Clear();
     if (firstGroupStartVer->PolyIndex != firstGroupEndVer->PolyIndex)
     {
       for (int j = 0; j < allObjGroups->Count; ++j){
          if (i == j) continue;
          nextGroup = (TList*) allObjGroups->Items[j];
          if (nextGroup->Count == 0) continue;
          oneCurve *nextGroupFirstCurve  = (oneCurve*) nextGroup->First();
          oneCurve *nextGroupLastCurve = (oneCurve*) nextGroup->Last();
          Vertex* nextGroupStartVer = (Vertex*) nextGroupFirstCurve->First();
          Vertex* nextGroupEndVer = (Vertex*) nextGroupLastCurve->Last();
          if ( (nextGroupStartVer->PolyIndex == firstGroupEndVer->PolyIndex) && (nextGroupStartVer->PolyIndex != nextGroupEndVer->PolyIndex)){
             candidateConnectList->Add(nextGroup);
             needToBeResersedList->Add(NULL);
          }
          else if ( (nextGroupEndVer->PolyIndex == firstGroupEndVer->PolyIndex) && (nextGroupStartVer->PolyIndex != nextGroupEndVer->PolyIndex)){
             candidateConnectList->Add(nextGroup);
             needToBeResersedList->Add((Pointer*)1);
          }
       }

       //WO MEN YOU DONGXI candidateConnectList LIMIAN
       if (candidateConnectList->Count != 0){
          if (findClosestGroupToFirstGroupEndAndJoinToFirstGroup(Polygons, firstGroup, candidateConnectList, needToBeResersedList)){
             --i;
             Result = true;
          }
       }
     }

   }

   //write_allObjGroups_connected("allObjGroups.scr", allObjGroups);


   // Group1 Ends on Poly0 and starts on PolyN
   // so we search any poly ending on PolyN, (which starts on another poly)
   // OR End on PolyN and start on another Poly (needs Reverse)
   for (int i = 0; i < allObjGroups->Count; ++i){
     firstGroup = (TList*) allObjGroups->Items[i];
     if (firstGroup->Count == 0) continue;
     //write_oneGroup("first_Group.scr", firstGroup);
     firstGroupFirstCurve = (oneCurve*) firstGroup->First();
     firstGroupLastCurve  = (oneCurve*) firstGroup->Last();
     firstGroupStartVer = (Vertex*) firstGroupFirstCurve->First();
     firstGroupEndVer = (Vertex*) firstGroupLastCurve->Last();
     candidateConnectList->Clear();
     needToBeResersedList->Clear();


     if (firstGroupStartVer->PolyIndex != firstGroupEndVer->PolyIndex)
     {
       reverseOneGroup(firstGroup);
       firstGroupFirstCurve = (oneCurve*) firstGroup->First();
       firstGroupLastCurve  = (oneCurve*) firstGroup->Last();
       firstGroupStartVer = (Vertex*) firstGroupFirstCurve->First();
       firstGroupEndVer = (Vertex*) firstGroupLastCurve->Last();


       for (int j = 0; j < allObjGroups->Count; ++j){
          if (i == j) continue;
          nextGroup = (TList*) allObjGroups->Items[j];
          if (nextGroup->Count == 0) continue;
          oneCurve *nextGroupFirstCurve  = (oneCurve*) nextGroup->First();
          oneCurve *nextGroupLastCurve = (oneCurve*) nextGroup->Last();
          Vertex* nextGroupStartVer = (Vertex*) nextGroupFirstCurve->First();
          Vertex* nextGroupEndVer = (Vertex*) nextGroupLastCurve->Last();
          if ( (nextGroupStartVer->PolyIndex == firstGroupEndVer->PolyIndex) && (nextGroupStartVer->PolyIndex != nextGroupEndVer->PolyIndex)){
             candidateConnectList->Add(nextGroup);
             needToBeResersedList->Add(NULL);
          }
          else if ( (nextGroupEndVer->PolyIndex == firstGroupEndVer->PolyIndex) && (nextGroupStartVer->PolyIndex != nextGroupEndVer->PolyIndex)){
             candidateConnectList->Add(nextGroup);
             needToBeResersedList->Add((Pointer*)1);
          }
       }

       //WO MEN YOU DONGXI candidateConnectList LIMIAN
       if (candidateConnectList->Count != 0){
          if (findClosestGroupToFirstGroupEndAndJoinToFirstGroup(Polygons, firstGroup, candidateConnectList, needToBeResersedList)){
             --i;
             Result = true;
          }
       }
     }

   }

   //write_allObjGroups_connected("allObjGroups.scr", allObjGroups);

   candidateConnectList->Clear();
   delete candidateConnectList;
   delete needToBeResersedList;
   return(Result);
}


void JoinGroups(TList *Polygons, TList *allObjGroups)
{
   oneCurve *firstGroupFirstCurve, *firstGroupLastCurve;
   TList *firstGroup, *nextGroup;
   TList *candidateConnectList = new TList();
   TList *needToBeResersedList = new TList();

   Vertex *firstGroupStartVer , *firstGroupEndVer;

   // Group1 Start at Poly0 and end on PolyN
   // so we search any poly started on PolyN, (which ends on another poly)
   // OR End on PolyN and start on another Poly (needs Reverse)
   for (int i = 0; i < allObjGroups->Count; ++i){
     firstGroup = (TList*) allObjGroups->Items[i];
     //write_oneGroup("first_Group.scr", firstGroup);
     if (firstGroup->Count == 0)  continue;
     firstGroupFirstCurve = (oneCurve*) firstGroup->First();
     firstGroupLastCurve  = (oneCurve*) firstGroup->Last();
     firstGroupStartVer = (Vertex*) firstGroupFirstCurve->First();
     firstGroupEndVer = (Vertex*) firstGroupLastCurve->Last();
     candidateConnectList->Clear();
     needToBeResersedList->Clear();
     if ( (firstGroupStartVer->PolyIndex != firstGroupEndVer->PolyIndex) && (firstGroupStartVer->PolyIndex == 0))
     {
       for (int j = 0; j < allObjGroups->Count; ++j){
          if (i == j) continue;
          nextGroup = (TList*) allObjGroups->Items[j];
          if (nextGroup->Count == 0) continue;
          oneCurve *nextGroupFirstCurve  = (oneCurve*) nextGroup->First();
          oneCurve *nextGroupLastCurve = (oneCurve*) nextGroup->Last();
          Vertex* nextGroupStartVer = (Vertex*) nextGroupFirstCurve->First();
          Vertex* nextGroupEndVer = (Vertex*) nextGroupLastCurve->Last();
          if ( (nextGroupStartVer->PolyIndex == firstGroupEndVer->PolyIndex) && (nextGroupStartVer->PolyIndex != nextGroupEndVer->PolyIndex)){
             candidateConnectList->Add(nextGroup);
             needToBeResersedList->Add(NULL);
          }
          else if ( (nextGroupEndVer->PolyIndex == firstGroupEndVer->PolyIndex) && (nextGroupStartVer->PolyIndex != nextGroupEndVer->PolyIndex)){
             candidateConnectList->Add(nextGroup);
             needToBeResersedList->Add((Pointer*)1);
          }
       }

       //WO MEN YOU DONGXI candidateConnectList LIMIAN
       if (candidateConnectList->Count != 0){
          if (findClosestGroupToFirstGroupEndAndJoinToFirstGroup(Polygons, firstGroup, candidateConnectList, needToBeResersedList)){
             --i;
          }
       }
     }

   }

   //write_allObjGroups_connected("allObjGroups.scr", allObjGroups);


   // Group1 Ends on Poly0 and starts on PolyN
   // so we search any poly ending on PolyN, (which starts on another poly)
   // OR End on PolyN and start on another Poly (needs Reverse)
   for (int i = 0; i < allObjGroups->Count; ++i){
     firstGroup = (TList*) allObjGroups->Items[i];
     //write_oneGroup("first_Group.scr", firstGroup);
     if (firstGroup->Count == 0)  continue;
     firstGroupFirstCurve = (oneCurve*) firstGroup->First();
     firstGroupLastCurve  = (oneCurve*) firstGroup->Last();
     firstGroupStartVer = (Vertex*) firstGroupFirstCurve->First();
     firstGroupEndVer = (Vertex*) firstGroupLastCurve->Last();
     candidateConnectList->Clear();
     needToBeResersedList->Clear();


     if ( (firstGroupStartVer->PolyIndex != firstGroupEndVer->PolyIndex) && (firstGroupEndVer->PolyIndex == 0))
     {
       reverseOneGroup(firstGroup);
       firstGroupFirstCurve = (oneCurve*) firstGroup->First();
       firstGroupLastCurve  = (oneCurve*) firstGroup->Last();
       firstGroupStartVer = (Vertex*) firstGroupFirstCurve->First();
       firstGroupEndVer = (Vertex*) firstGroupLastCurve->Last();


       for (int j = 0; j < allObjGroups->Count; ++j){
          if (i == j) continue;
          nextGroup = (TList*) allObjGroups->Items[j];
          if (nextGroup->Count == 0) continue;
          oneCurve *nextGroupFirstCurve  = (oneCurve*) nextGroup->First();
          oneCurve *nextGroupLastCurve = (oneCurve*) nextGroup->Last();
          Vertex* nextGroupStartVer = (Vertex*) nextGroupFirstCurve->First();
          Vertex* nextGroupEndVer = (Vertex*) nextGroupLastCurve->Last();
          if ( (nextGroupStartVer->PolyIndex == firstGroupEndVer->PolyIndex) && (nextGroupStartVer->PolyIndex != nextGroupEndVer->PolyIndex)){
             candidateConnectList->Add(nextGroup);
             needToBeResersedList->Add(NULL);
          }
          else if ( (nextGroupEndVer->PolyIndex == firstGroupEndVer->PolyIndex) && (nextGroupStartVer->PolyIndex != nextGroupEndVer->PolyIndex)){
             candidateConnectList->Add(nextGroup);
             needToBeResersedList->Add((Pointer*)1);
          }
       }

       //WO MEN YOU DONGXI candidateConnectList LIMIAN
       if (candidateConnectList->Count != 0){
          if (findClosestGroupToFirstGroupEndAndJoinToFirstGroup(Polygons, firstGroup, candidateConnectList, needToBeResersedList)){
             --i;
          }
       }
     }

   }

   //write_allObjGroups_connected("allObjGroups.scr", allObjGroups);

   candidateConnectList->Clear();
   delete candidateConnectList;
   delete needToBeResersedList;
}



void clearZeroLenGroups(TList *allObjGroups)
{
   for (int i = allObjGroups->Count-1; i >=0; --i){
     TList *oneGroup = (TList*) allObjGroups->Items[i];
     if (oneGroup->Count == 0){
        allObjGroups->Delete(i);
        delete oneGroup;
     }
   }
}   


void Join_Final_Good_Groups(TList *Polygons, TList *allObjGroups)
{
   TList *runList[4];
   //int runListDist[4];
   // 0 = End-Start (the first Joins the Second, only needs to make a running from firstGroup-LastCurve-Lastver to secondGHroup-FirstCurve-First)
   // 1 = Start-End (swap first and second group, so it becomes same as dt 0 = End-Start
   // 2 = Start-Start (reverse the first one, so it becomes like 0 = End-Start
   // 3 = End-End (reverse the second group, so it becomes like 0 = End-Start

   int minDist;
   int Dist;
   int selectedRunIndex = -1;
   TList *selectedRunList = new TList();
   TList *fGroup, *sGroup;



   for (int i = 0; i < 4; ++i)
      runList[i] = new TList();

   while(true){
      selectedRunIndex = -1;
      minDist = 0x0FFFFFFF;
      TList* firstGroup, *secondGroup;
      for (int i = 0; i < allObjGroups->Count; ++i){
         firstGroup = (TList *) allObjGroups->Items[i];
         if (firstGroup->Count ==0) continue;
         oneCurve *fgFirstCurve = (oneCurve*) firstGroup->First();
         oneCurve *fgLastCurve = (oneCurve*) firstGroup->Last();
         Vertex *fgStart = (Vertex*)fgFirstCurve->First();
         Vertex *fgEnd = (Vertex*)fgLastCurve->Last();
         if ( fgStart->PolyIndex != fgEnd->PolyIndex) continue;
         for (int j = 0; j < allObjGroups->Count; ++j){
           if (i == j ) continue;
           secondGroup = (TList *) allObjGroups->Items[j];
           if (secondGroup->Count ==0) continue;
           oneCurve *sgFirstCurve = (oneCurve*) secondGroup->First();
           oneCurve *sgLastCurve = (oneCurve*) secondGroup->Last();
           Vertex *sgStart = (Vertex*)sgFirstCurve->First();
           Vertex *sgEnd = (Vertex*)sgLastCurve->Last();
           if (sgStart->PolyIndex != sgEnd->PolyIndex)  continue;
           if (fgStart->PolyIndex != sgStart->PolyIndex) continue;

           for (int i = 0; i < 4; ++i){
             runList[i]->Clear();
           }


           //0 = End-Start
           Dist = makeRunOnMainPolygonEdge((oneCurve*) Polygons->Items[fgStart->PolyIndex],
                fgEnd->PolyVertex, sgStart->PolyVertex,
                runList[0]);
           if (Dist < minDist){
              minDist = Dist;
              fGroup = firstGroup;
              sGroup = secondGroup;
              selectedRunIndex = 0;  //0 = End-Start
              selectedRunList->Clear();
              for (int n = 0; n < runList[0]->Count; ++n)
                selectedRunList->Add(runList[0]->Items[n]);
           }

           // 1 = Start-End
           Dist = makeRunOnMainPolygonEdge((oneCurve*) Polygons->Items[fgStart->PolyIndex],
                fgStart->PolyVertex, sgEnd->PolyVertex,
                runList[1]);
           if (Dist < minDist){
              minDist = Dist;
              fGroup = firstGroup;
              sGroup = secondGroup;
              selectedRunIndex = 1;  // 1 = Start-End
              selectedRunList->Clear();
              for (int n = 0; n < runList[1]->Count; ++n)
                selectedRunList->Add(runList[1]->Items[n]);
           }

           // 2 = Start-Start
           Dist = makeRunOnMainPolygonEdge((oneCurve*) Polygons->Items[fgStart->PolyIndex],
                fgStart->PolyVertex, sgStart->PolyVertex,
                runList[2]);
           if (Dist < minDist){
              minDist = Dist;
              fGroup = firstGroup;
              sGroup = secondGroup;
              selectedRunIndex = 2;  // 2 = Start-Start
              selectedRunList->Clear();
              for (int n = 0; n < runList[2]->Count; ++n)
                selectedRunList->Add(runList[2]->Items[n]);
           }

           // 3 = End-End
           Dist = makeRunOnMainPolygonEdge((oneCurve*) Polygons->Items[fgStart->PolyIndex],
                fgEnd->PolyVertex, sgEnd->PolyVertex,
                runList[3]);
           if (Dist < minDist){
              minDist = Dist;
              fGroup = firstGroup;
              sGroup = secondGroup;
              selectedRunIndex = 3;  // 3 = End-End
              selectedRunList->Clear();
              for (int n = 0; n < runList[3]->Count; ++n)
                selectedRunList->Add(runList[3]->Items[n]);
           }

         }

      }
      if (selectedRunIndex == -1)
        break;
      if (selectedRunIndex == 3)  // 3 = End-End (reverse the second group, so it becomes like 0 = End-Start
        reverseOneGroup(sGroup);
      if (selectedRunIndex == 2) // 2 = Start-Start (reverse the first one, so it becomes like 0 = End-Start
        reverseOneGroup(fGroup);
      if (selectedRunIndex == 1){ // 1 = Start-End (swap first and second group, so it becomes same as dt 0 = End-Start
         swap(sGroup, fGroup);
         for (int n = 0; n < selectedRunList->Count/2; ++n)
           selectedRunList->Exchange(n, selectedRunList->Count-1-n);
      }
      oneCurve *lastCurve = (oneCurve*) fGroup->Last();
      oneCurve *firstCurve = (oneCurve*) sGroup->First();
      Vertex *StartVer = (Vertex*)firstCurve->First();
      Vertex *EndVer = (Vertex*)lastCurve->Last();

      if (lastCurve->ConnectedPrev == leftNextCurve)
         lastCurve->ConnectedNext = rightPrevCurve;
      else if (lastCurve->ConnectedPrev == leftPrevCurve)
         lastCurve->ConnectedNext = rightNextCurve;
      else if (lastCurve->ConnectedPrev == rightNextCurve)
         lastCurve->ConnectedNext = leftPrevCurve;
      else if (lastCurve->ConnectedPrev == rightPrevCurve)
         lastCurve->ConnectedNext = leftNextCurve;

      if (firstCurve->ConnectedNext == leftNextCurve)
         firstCurve->ConnectedPrev = rightPrevCurve;
      else if (firstCurve->ConnectedNext == leftPrevCurve)
         firstCurve->ConnectedPrev = rightNextCurve;
      else if (firstCurve->ConnectedNext == rightNextCurve)
         firstCurve->ConnectedPrev = leftPrevCurve;
      else if (firstCurve->ConnectedNext == rightPrevCurve)
         firstCurve->ConnectedPrev = leftNextCurve;

      lastCurve->polyVerList[lastCurve->ConnectedNext]->Clear();
      firstCurve->polyVerList[firstCurve->ConnectedPrev]->Clear();

      for (int n = 0; n < selectedRunList->Count; ++n)
        lastCurve->polyVerList[lastCurve->ConnectedNext]->Add(selectedRunList->Items[n]);

      for (int n = selectedRunList->Count-1; n >= 0; --n)
        firstCurve->polyVerList[firstCurve->ConnectedPrev]->Add(selectedRunList->Items[n]);


      //write_oneGroup("fGroup.scr", fGroup, false);
      //write_oneGroup("sGroup.scr", sGroup, false);
      //writeInfoOfCurve_LeftRightLists("lastCurve.scr", lastCurve);
      //writeInfoOfCurve_LeftRightLists("firstCurve.scr", firstCurve);


      lastCurve->connectionHands[lastCurve->ConnectedNext] = firstCurve;
      firstCurve->connectionHands[firstCurve->ConnectedPrev] = lastCurve;

      for (int n = 0; n < sGroup->Count; ++n)
        fGroup->Add(sGroup->Items[n]);
      sGroup->Clear();
   }

   delete selectedRunList;
   for (int i = 0; i < 4; ++i)
      delete runList[i];

}

void Join_Groups_where_Start_End_Is_Located_On_oneHand_Of_a_Curve(TList *allObjGroups)
{
   for (int i = 0; i < allObjGroups->Count; ++i){

         TList *firstGroup = (TList *) allObjGroups->Items[i];
         if (firstGroup->Count ==0) continue;
         oneCurve *FirstCurve = (oneCurve*) firstGroup->First();
         oneCurve *LastCurve = (oneCurve*) firstGroup->Last();
         Vertex *Start = (Vertex*)FirstCurve->First();
         Vertex *End = (Vertex*)LastCurve->Last();
         Vertex *StartPolyVer = Start->PolyVertex;
         Vertex *EndPolyVer = End->PolyVertex;

         bool done = false;
         for (int j = 0; j < allObjGroups->Count; ++j){
             if (i == j) continue;
             TList *secondGroup = (TList *) allObjGroups->Items[j];
             if (secondGroup->Count == 0) continue;
             for (int n = 0; n < secondGroup->Count-1; ++n){
                oneCurve *aCurve = (oneCurve*) secondGroup->Items[n];
                for (int ndx = leftNextCurve; ndx <= rightPrevCurve; ++ndx){
                   int stIndex = aCurve->polyVerList[ndx]->IndexOf(StartPolyVer);
                   int endIndex = aCurve->polyVerList[ndx]->IndexOf(EndPolyVer);
                   if ( (stIndex != -1) && (endIndex != -1) ){

                      //writeInfoOfCurve_LeftRightLists("aCurve_Hand.scr", aCurve, ndx);

                      if (endIndex < stIndex){
                         reverseOneGroup(firstGroup);
                         FirstCurve = (oneCurve*) firstGroup->First();
                         LastCurve = (oneCurve*) firstGroup->Last();
                         swap(stIndex, endIndex);
                         //write_oneGroup("firstGroup.scr", firstGroup);
                      }

                      oneCurve *nextCurve = (oneCurve*) secondGroup->Items[n+1];
                      nextCurve->connectionHands[nextCurve->ConnectedPrev] = LastCurve;

                      if (LastCurve->ConnectedPrev == leftNextCurve)
                         LastCurve->ConnectedNext = rightPrevCurve;
                      else if (LastCurve->ConnectedPrev == leftPrevCurve)
                         LastCurve->ConnectedNext = rightNextCurve;
                      else if (LastCurve->ConnectedPrev == rightNextCurve)
                         LastCurve->ConnectedNext = leftPrevCurve;
                      else if (LastCurve->ConnectedPrev == rightPrevCurve)
                         LastCurve->ConnectedNext = leftNextCurve;

                      LastCurve->connectionHands[LastCurve->ConnectedNext] = nextCurve;
                      LastCurve->polyVerList[LastCurve->ConnectedNext]->Clear();
                      nextCurve->polyVerList[nextCurve->ConnectedPrev]->Clear();

                      for (int m = endIndex; m < aCurve->polyVerList[ndx]->Count; ++m)
                         LastCurve->polyVerList[LastCurve->ConnectedNext]->Add(aCurve->polyVerList[ndx]->Items[m]);

                      for (int m =LastCurve->polyVerList[LastCurve->ConnectedNext]->Count-1; m >= 0; --m)
                        nextCurve->polyVerList[nextCurve->ConnectedPrev]->Add( LastCurve->polyVerList[LastCurve->ConnectedNext]->Items[m]);

                      //writeInfoOfCurve_LeftRightLists("lastCurve_Conn.scr", LastCurve);
                      //writeInfoOfCurve_LeftRightLists("nextCurve_Conn.scr", nextCurve);

                      aCurve->connectionHands[aCurve->ConnectedNext] = FirstCurve;

                      if (FirstCurve->ConnectedNext == leftNextCurve)
                         FirstCurve->ConnectedPrev = rightPrevCurve;
                      else if (FirstCurve->ConnectedNext == leftPrevCurve)
                         FirstCurve->ConnectedPrev = rightNextCurve;
                      else if (FirstCurve->ConnectedNext == rightNextCurve)
                         FirstCurve->ConnectedPrev = leftPrevCurve;
                      else if (FirstCurve->ConnectedNext == rightPrevCurve)
                         FirstCurve->ConnectedPrev = leftNextCurve;
                      FirstCurve->connectionHands[FirstCurve->ConnectedPrev] = aCurve;
                      FirstCurve->polyVerList[FirstCurve->ConnectedPrev]->Clear();

                      for (int m = stIndex; m >= 0; --m)
                         FirstCurve->polyVerList[FirstCurve->ConnectedPrev]->Add(aCurve->polyVerList[ndx]->Items[m]);


                      for (int m = stIndex+1; m < aCurve->polyVerList[ndx]->Count; ++m)
                        aCurve->polyVerList[aCurve->ConnectedNext]->Items[m] = NULL;
                     aCurve->polyVerList[ndx]->Pack();

                      for (int m = firstGroup->Count-1; m >= 0; --m)
                        secondGroup->Insert(n+1, firstGroup->Items[m] );
                      firstGroup->Clear();

                      //write_oneGroup("firstGroup.scr", firstGroup);
                      //write_oneGroup("secondGroup.scr", firstGroup);
                      //writeInfoOfCurve_LeftRightLists("aCurve_Hand.scr", aCurve, ndx);

                      done = true;
                      break;
                   }
                }
                if (done) break;
             }
             if (done) break;
         }
   }


}


void oneCurve::AppendVerList(TList *newList)
{
   for (int i = 0; i < newList->Count; ++i)
     Add(newList->Items[i]);
   newList->Clear();
}

void oneCurve::DeleteAll()
{
  for (int i = 0; i < Count; ++i)
    delete (Vertex*) Items[i];
  Clear();
}

void oneCurve::calculateLength()
{
    Vertex *p1 = (Vertex *) First();
    Vertex *p2;
    length = 0;
    for(int j = 1; j < Count; ++j){
      p2 = (Vertex *) Items[j];
      length +=  Distance(p1->po,p2->po);
      p1 = p2;
    }
}

oneCurve::oneCurve() :  TList() { //Constroctor

  offsetIndex = 0;
  length = 0;
  for (int i = 0; i < 4; ++i){
    connectionHands[i] = NULL;
    polyVerList[i] = new TList();
  }
  ConnectedNext = ConnectedPrev = -1;

  leftrightDist[leftNextCurve] = 0;
  leftrightDist[leftPrevCurve] = 0;
  leftrightDist[rightNextCurve] = 0;
  leftrightDist[rightPrevCurve] = 0;
  byFixInters = false;
  NotConnectedToBoundry = false;//false =- means connected to coundry Polygon, true means it is not connected
  visited = false;
}


__fastcall oneCurve::~oneCurve() {

  for (int n = 0; n < 4; ++n)
      delete polyVerList[n];
}


void oneCurve::reverseFirstLine()
{
  oneCurve *exchangeC;
  TList *exchangeL;

  for (int i = 0; i < Count/2; ++i)
    Exchange(i, Count-1-i);
  if (Direction == CW)
    Direction = CCW;
  else
    Direction = CW;

  exchangeC = connectionHands[leftNextCurve];
  connectionHands[leftNextCurve] = connectionHands[rightNextCurve];
  connectionHands[rightNextCurve] = exchangeC;

  exchangeC = connectionHands[leftPrevCurve];
  connectionHands[leftPrevCurve] = connectionHands[rightPrevCurve];
  connectionHands[rightPrevCurve] = exchangeC;

  exchangeL = polyVerList[leftNextCurve];
  polyVerList[leftNextCurve] = polyVerList[rightNextCurve];
  polyVerList[rightNextCurve] = exchangeL;

  exchangeL = polyVerList[leftPrevCurve];
  polyVerList[leftPrevCurve] = polyVerList[rightPrevCurve];
  polyVerList[rightPrevCurve] = exchangeL;

  int exch;

  exch = leftrightDist[leftNextCurve];
  leftrightDist[leftNextCurve] = leftrightDist[leftPrevCurve];
  leftrightDist[leftPrevCurve] = exch;

  exch = leftrightDist[rightNextCurve];
  leftrightDist[rightNextCurve] = leftrightDist[rightPrevCurve];
  leftrightDist[rightPrevCurve] = exch;
}

void oneCurve::reverse()
{
  oneCurve *exchangeC;
  TList *exchangeL;

  for (int i = 0; i < Count/2; ++i)
    Exchange(i, Count-1-i);
  if (Direction == CW)
    Direction = CCW;
  else
    Direction = CW;

  exchangeC = connectionHands[leftNextCurve];
  connectionHands[leftNextCurve] = connectionHands[rightNextCurve];
  connectionHands[rightNextCurve] = exchangeC;

  exchangeC = connectionHands[leftPrevCurve];
  connectionHands[leftPrevCurve] = connectionHands[rightPrevCurve];
  connectionHands[rightPrevCurve] = exchangeC;

  exchangeL = polyVerList[leftNextCurve];
  polyVerList[leftNextCurve] = polyVerList[rightNextCurve];
  polyVerList[rightNextCurve] = exchangeL;

  exchangeL = polyVerList[leftPrevCurve];
  polyVerList[leftPrevCurve] = polyVerList[rightPrevCurve];
  polyVerList[rightPrevCurve] = exchangeL;

  int exch;
  exch = leftrightDist[leftNextCurve];
  leftrightDist[leftNextCurve] = leftrightDist[rightNextCurve];
  leftrightDist[rightNextCurve] = exch;

  exch = leftrightDist[rightPrevCurve];
  leftrightDist[rightPrevCurve] = leftrightDist[leftPrevCurve];
  leftrightDist[leftPrevCurve] = exch;

  if (ConnectedNext == leftPrevCurve)
    ConnectedNext = rightPrevCurve;
  else
  if (ConnectedNext == rightPrevCurve)
    ConnectedNext = leftPrevCurve;
  else
  if (ConnectedNext == leftNextCurve)
    ConnectedNext = rightNextCurve;
  else
  if (ConnectedNext == rightNextCurve)
    ConnectedNext = leftNextCurve;


  if (ConnectedPrev == leftPrevCurve)
    ConnectedPrev = rightPrevCurve;
  else
  if (ConnectedPrev == rightPrevCurve)
    ConnectedPrev = leftPrevCurve;
  else
  if (ConnectedPrev == leftNextCurve)
    ConnectedPrev = rightNextCurve;
  else
  if (ConnectedPrev == rightNextCurve)
    ConnectedPrev = leftNextCurve;


  exch = ConnectedNext;
  ConnectedNext = ConnectedPrev;
  ConnectedPrev = exch;
}

bool checkVertexesStraightness(Vertex *v1, Vertex *v2, int maxDist){

  Vertex *v = v1->nextVer;
  if (v == v2)
    return(true);
  while(v != v2->prevVer){
    if (GetDistLinePoint(v1->po, v2->po, v->po) > maxDist)
        return(false);
    v = v->nextVer;
  }
  return(true);
}



void getNewBoundRect(TList *Polygons,int rectMargin,TList *Curves){
  writePolygon("AllPolygons_1.scr", Polygons);
  TPoint p1;
  TPoint p2;
  TPoint p3;
  TPoint p4;
  TPoint intPo;
  Vertex *rectv;
  oneCurve *rectList = new oneCurve();
  Vertex *pv1,*pv2,*cv1,*cv2;
  oneCurve *poly = (oneCurve*) Polygons->Items[0];
  Vertex *v = (Vertex *) poly->First();
  TPoint polyMin = v->po , polyMax = v->po;
  for(int i = 0; i < poly->Count; ++i){
      Vertex *v = (Vertex *) poly->Items[i];
      if(v->po.x > polyMax.x )
        polyMax.x = v->po.x;
      if(v->po.x < polyMin.x)
        polyMin.x = v->po.x;
      if(v->po.y > polyMax.y)
        polyMax.y = v->po.y;
      if(v->po.y < polyMin.y)
        polyMin.y = v->po.y;
  };
  
  p1.x = polyMin.x-rectMargin;
  p1.y = polyMax.y+rectMargin;
  rectv = new Vertex(p1, 0, -1, -1);
  rectList->Add(rectv);
  p2.x = polyMax.x+rectMargin;
  p2.y = polyMax.y+rectMargin;
  rectv = new Vertex(p2, 0, -1, -1);
  rectList->Add(rectv);
  p3.x = polyMax.x+rectMargin;
  p3.y = polyMin.y-rectMargin;
  rectv = new Vertex(p3, 0, -1, -1);
  rectList->Add(rectv);
  p4.x = polyMin.x-rectMargin;
  p4.y = polyMin.y-rectMargin;
  rectv = new Vertex(p4, 0, -1, -1);
  rectList->Add(rectv);

  cout << p1.x << "," << p1.y << "\n";
  cout << p2.x << "," << p2.y << "\n";
  cout << p3.x << "," << p3.y << "\n";
  cout << p4.x << "," << p4.y << "\n";

  writePolygon("AllCurves_1.scr", Curves);
  writeOnePolygon("Rect.scr", rectList);

  oneCurve *aCurve = (oneCurve*) Curves->First();
  pv1 = (Vertex *)rectList->Last();
  bool curveTrimmed1 = false;
  bool curveTrimmed2 = false;
  for(int i = 0; i< rectList->Count; ++i){
     pv2 = (Vertex *)rectList->Items[i];
     if (!curveTrimmed1){
       for(int j = 0;j<aCurve->Count-2; ++j){
            cv1 = (Vertex *) aCurve->Items[j];
            cv2 = (Vertex *) aCurve->Items[j+1];
          if(GetIntersection(intPo,pv1->po,pv2->po,cv1->po,cv2->po,false)){
             cout << "Int Fount at: "<< intPo.x << "," << intPo.y <<  '\n';
             cv1->po = intPo;
             for (int n =0; n < j; ++n){
               Vertex *v = (Vertex*)aCurve->Items[n];
               aCurve->Items[n] = NULL;
               delete v;
             }
             aCurve->Pack();
             curveTrimmed1 = true;
             break;
          }
       }

     }
     if (!curveTrimmed2){
       for(int j = aCurve->Count-1; j > 1; --j){
            cv1 = (Vertex *) aCurve->Items[j];
            cv2 = (Vertex *) aCurve->Items[j-1];
          if(GetIntersection(intPo,pv1->po,pv2->po,cv1->po,cv2->po,false)){
             cout << "Int Fount at: "<< intPo.x << "," << intPo.y <<  '\n';
             cv1->po = intPo;
             for (int n =j+1; n < aCurve->Count; ++n){
               Vertex *v = (Vertex*)aCurve->Items[n];
               aCurve->Items[n] = NULL;
               delete v;
             }
             aCurve->Pack();
             curveTrimmed2 = true;
             break;
          }
       }
     }
       if (curveTrimmed1 && curveTrimmed2) break;

     pv1 = pv2;
  }

  writePolygon("AllCurves_2.scr", Curves);

  FreeOnePoly(rectList);

}


void makeSimnpleRunning(oneCurve *aCurve, int runLen)
{
  oneCurve *newRunList = new oneCurve();
  Vertex *vp1,*vp2;
  Vertex *v1, *v2;
  double a, ang1,ang2,dotAngle;
  double Len = 0;
  double rdist = 0;
  double LenAll = 0;
  TPoint PR;
  TPoint P3, P4;


  v1 = (Vertex *) aCurve->First();
  v2 = (Vertex *) aCurve->Last();
  LenAll = 0;
  Vertex *v = v1;

    vp1 =  (Vertex *) aCurve->First();
    for(int i = 0;i < aCurve->Count-1;++i){
          vp2 = (Vertex *) aCurve->Items[i+1];
          LenAll += Distance(vp1->po,vp2->po);
          vp1 = vp2;
    };




   int i = LenAll / runLen  +1;
   Len = LenAll / i;


    newRunList->Add(new Vertex(v1->po, 0, -1, -1));
    Vertex *Data1 = v1, *lastData = v1;
    Vertex *Data2, *Data3;
    PR.x = Data1->po.x;
    PR.y = Data1->po.y;
    int lastVerIndex = 0;
    for(int i=0;i<aCurve->Count-1;++i){
      Data2 = (Vertex *)aCurve->Items[i+1];
      if (i<aCurve->Count-2)
        Data3 = Data2;
      else
        Data3 = Data2;
      Data1->nextVer = Data2;
      Data2->prevVer = Data1;
      a = Len-rdist;
      rdist += Distance(Data1->po, Data2->po);
      ang1 = getAngle(Data1->po, Data2->po);
      double newrdist = Distance(Data1->po, Data2->po);
      while( rdist > Len+5)
      { PR.x = Data1->po.x + a * cos(ang1);
        PR.y = Data1->po.y + a * sin(ang1);
        Vertex *newV =  new Vertex(PR, 0, -1, -1);
        newRunList->Add(newV);
        a += Len;
        rdist -= Len;
        lastData = Data1;
        if (rdist < Len+5)
          lastVerIndex = i;
      }
      //writeOnePolygon("aCurve_2.scr", newRunList);
      Data1 = Data2;
    }

    vp1 =  (Vertex *) aCurve->Last();
    newRunList->Add(new  Vertex(vp1->po, 0));


    aCurve->DeleteAll();

    for (int n = 0; n < newRunList->Count; ++n){
         Vertex *vp = (Vertex*) newRunList->Items[n];
         aCurve->Add(newRunList->Items[n]);
    }

  delete newRunList;

}



void makeRunningBetweenTwoVertexes(TList *Curves, int runLen, int tatamiOffset, bool sharpCorners)
{
  oneCurve *newRunList = new oneCurve();
  int interval = 3;
  int runPointsCount;
  oneCurve *aCurve;
  Vertex *vp1,*vp2;
  Vertex *v1, *v2;
  double a, ang1,ang2,dotAngle;
  double Len = 0;
  double rdist = 0;
  double LenAll = 0;
  TPoint PR;
  TPoint P3, P4;



  aCurve = (oneCurve*) Curves->Items[ Curves->Count/2];
  vp1 =  (Vertex *) aCurve->First();
  for(int i = 0;i < aCurve->Count-1;++i){
          vp2 = (Vertex *) aCurve->Items[i+1];
          LenAll += Distance(vp1->po,vp2->po);
          vp1 = vp2;
  };
  runPointsCount = LenAll / (runLen / abs(tatamiOffset)) +1;




  for (int n = Curves->Count-1; n >= 0; --n){


    aCurve = (oneCurve*) Curves->Items[n];
    writeOnePolygon("aCurve.scr", aCurve);
    v1 = (Vertex *) aCurve->First();
    v2 = (Vertex *) aCurve->Last();
    LenAll = 0;
    Vertex *v = v1;

    vp1 =  (Vertex *) aCurve->First();
    for(int i = 0;i < aCurve->Count-1;++i){
          vp2 = (Vertex *) aCurve->Items[i+1];
          LenAll += Distance(vp1->po,vp2->po);
          vp1 = vp2;
    };




      int i = LenAll / (runLen / abs(tatamiOffset)) +1;
      Len = LenAll / i;
    //Len = LenAll / runPointsCount;


    newRunList->Add(new Vertex(v1->po, 0, -1, -1));
    Vertex *Data1 = v1, *lastData = v1;
    Vertex *Data2, *Data3;
    PR.x = Data1->po.x;
    PR.y = Data1->po.y;
    int lastVerIndex = 0;
    for(int i=0;i<aCurve->Count-1;++i){
      Data2 = (Vertex *)aCurve->Items[i+1];
      if (i<aCurve->Count-2)
        Data3 = Data2;
      else
        Data3 = Data2;
      Data1->nextVer = Data2;
      Data2->prevVer = Data1;
      //P2 = Data2->po;
      a = Len-rdist;
      rdist += Distance(Data1->po, Data2->po);
      ang1 = getAngle(Data1->po, Data2->po);
      double newrdist = Distance(Data1->po, Data2->po);
      while( rdist > Len+5)
      { PR.x = Data1->po.x + a * cos(ang1);
        PR.y = Data1->po.y + a * sin(ang1);
          if (sharpCorners){
            for(int j = lastVerIndex + 1 ; j<i+1; j++){
               Vertex *Pdata1 = (Vertex *)aCurve->Items[j-1];
               Vertex *Pdata2 = (Vertex *)aCurve->Items[j];
               Vertex *Pdata3 = (Vertex *)aCurve->Items[j+1];
               double dotP = GetAngleDotProduct(Pdata1->po, Pdata2->po, Pdata3->po);
               if(dotP<0.707){
                  v = new Vertex(Pdata2->po, 0, -1, -1);
                  v->igoneInMakeRun = true;
                  newRunList->Add(v);
                  lastVerIndex = j+1;
               }
            }
          }
        Vertex *newV =  new Vertex(PR, 0, -1, -1);
        newRunList->Add(newV);
        a += Len;
        rdist -= Len;
        lastData = Data1;
        if (rdist < Len+5)
          lastVerIndex = i;
      }
      writeOnePolygon("aCurve_2.scr", newRunList);
      Data1 = Data2;

    }


    aCurve->DeleteAll();
    int newInterval = interval;
    if (newInterval != abs(tatamiOffset)){
      aCurve->Add(newRunList->First());
      newRunList->Items[0] = NULL;
    }

    for (int n = 0; n < newRunList->Count; ++n){
       if (newRunList->Items[n] != NULL){
         Vertex *vp = (Vertex*) newRunList->Items[n];

         if (vp->igoneInMakeRun){
           aCurve->Add(newRunList->Items[n]);
           newRunList->Items[n] = NULL;
           continue;
         }

       }

       if(newInterval == abs(tatamiOffset)){
         aCurve->Add(newRunList->Items[n]);
         newRunList->Items[n] = NULL;
       }
       if(tatamiOffset<0){
         --newInterval;
         if (newInterval == 0)
           newInterval = abs(tatamiOffset);
       }else{
          ++newInterval;
         if (newInterval > tatamiOffset)
           newInterval = 1;
       }

    }

     --interval;
     if (interval < 1)
       interval = abs(tatamiOffset);

    if (newRunList->Last() != NULL){
      aCurve->Add(newRunList->Last());
      newRunList->Items[newRunList->Count-1] = NULL;
    }
    for (int n = 0; n < newRunList->Count; ++n)
      if (newRunList->Items[n] != NULL)
        delete (Vertex*) newRunList->Items[n];
    newRunList->Clear();

  writeOnePolygon("aCurve_1.scr", aCurve);
  }

  delete newRunList;

}

void makeRunningBetweenTwoVertexes_before(TList *Curves, int runLen, int tatamiOffset, bool sharpCorners)
{
  oneCurve *newRunList = new oneCurve();
  int interval = 3;

  for (int n = Curves->Count-1; n >= 0; --n){

    oneCurve *aCurve = (oneCurve*) Curves->Items[n];
    writeOnePolygon("aCurve.scr", aCurve);
    Vertex *v1 = (Vertex *) aCurve->First();
    Vertex *v2 = (Vertex *) aCurve->Last();
    Vertex *vp1,*vp2;
    double LenAll = 0;
    Vertex *v = v1;

    vp1 =  (Vertex *) aCurve->First();
    for(int i = 0;i < aCurve->Count-1;++i){
          vp2 = (Vertex *) aCurve->Items[i+1];
          LenAll += Distance(vp1->po,vp2->po);
          vp1 = vp2;
    };


    double a, ang1,ang2,dotAngle;
    double Len = 0;
    double rdist = 0;
    TPoint P1, P2, PR;
    TPoint P3, P4;

    int i = LenAll / (runLen/abs(tatamiOffset)) +1;
    Len = LenAll / i;

    newRunList->Add(new Vertex(v1->po, 0, -1, -1));
    Vertex *Data1 = v1, *lastData = v1;
    Vertex *Data2;
    P1.x = PR.x = Data1->po.x;
    P1.y = PR.y = Data1->po.y;
    int lastVerIndex = 0;
    for(int i=0;i<aCurve->Count-1;++i){
      Data2 = (Vertex *)aCurve->Items[i+1];
      Data1->nextVer = Data2;
      Data2->prevVer = Data1;
      P2 = Data2->po;
      a = Len-rdist;
      rdist += Distance(P1, P2);
      ang1 = getAngle(P1, P2);
      while( rdist > Len+5)
      { PR.x = P1.x + a * cos(ang1);
        PR.y = P1.y + a * sin(ang1);
        if (sharpCorners){
            for(int j = lastVerIndex + 1 ; j<i+1; j++){
               Vertex *Pdata1 = (Vertex *)aCurve->Items[j-1];
               Vertex *Pdata2 = (Vertex *)aCurve->Items[j];
               Vertex *Pdata3 = (Vertex *)aCurve->Items[j+1];
               double dotP = GetAngleDotProduct(Pdata1->po, Pdata2->po, Pdata3->po);
               if(dotP<0.707){
                  v = new Vertex(Pdata2->po, 0, -1, -1);
                  v->igoneInMakeRun = true;
                  newRunList->Add(v);
                  lastVerIndex = j+1;
               }
            }
          }
        newRunList->Add(new Vertex(PR, 0, -1, -1));
        a += Len;
        rdist -= Len;
        lastData = Data1;
        if (rdist < Len+5)
          lastVerIndex = i;
      }
      P1 = P2;
      Data1 = Data2;

    }


    aCurve->DeleteAll();
    int newInterval = interval;
    if (newInterval != abs(tatamiOffset)){
      aCurve->Add(newRunList->First());
      newRunList->Items[0] = NULL;
    }

    for (int n = 0; n < newRunList->Count; ++n){
      if (newRunList->Items[n] != NULL){
         Vertex *vp = (Vertex*) newRunList->Items[n];

         if (vp->igoneInMakeRun){
           aCurve->Add(newRunList->Items[n]);
           newRunList->Items[n] = NULL;
           continue;
         }

       }
       if(newInterval == abs(tatamiOffset)){
         aCurve->Add(newRunList->Items[n]);
         newRunList->Items[n] = NULL;
       }
       if(tatamiOffset<0){
         --newInterval;
         if (newInterval == 0)
           newInterval = abs(tatamiOffset);
       }else{
          ++newInterval;
         if (newInterval > tatamiOffset)
           newInterval = 1;
       }
    }

     --interval;
     if (interval < 1)
       interval = abs(tatamiOffset);

    if (newRunList->Last() != NULL){
      aCurve->Add(newRunList->Last());
      newRunList->Items[newRunList->Count-1] = NULL;
    }
    for (int n = 0; n < newRunList->Count; ++n)
      if (newRunList->Items[n] != NULL)
        delete (Vertex*) newRunList->Items[n];
    newRunList->Clear();
    writeOnePolygon("aCurve_changed.scr", aCurve);


  }

  delete newRunList;

}



void makeRunningBetweenTwoVertexes_after(TList *Curves, int runLen, int tatamiOffset, bool sharpCorners)
{
  oneCurve *newRunList = new oneCurve();
  int interval = 3;
  int runPointsCount;
  oneCurve *aCurve;
  Vertex *vp1,*vp2;
  Vertex *v1, *v2;
  double a, ang1,ang2,dotAngle;
  double Len = 0;
  double rdist = 0;
  double LenAll = 0;
  TPoint P1, P2, PR;
  TPoint P3, P4;



  aCurve = (oneCurve*) Curves->Items[ Curves->Count/2];
  vp1 =  (Vertex *) aCurve->First();
  for(int i = 0;i < aCurve->Count-1;++i){
          vp2 = (Vertex *) aCurve->Items[i+1];
          LenAll += Distance(vp1->po,vp2->po);
          vp1 = vp2;
  };
  runPointsCount = LenAll / (runLen / abs(tatamiOffset)) +1;




  for (int n = Curves->Count-1; n >= 0; --n){


    aCurve = (oneCurve*) Curves->Items[n];
    writeOnePolygon("aCurve.scr", aCurve);
    v1 = (Vertex *) aCurve->First();
    v2 = (Vertex *) aCurve->Last();
    LenAll = 0;
    Vertex *v = v1;

    vp1 =  (Vertex *) aCurve->First();
    for(int i = 0;i < aCurve->Count-1;++i){
          vp2 = (Vertex *) aCurve->Items[i+1];
          LenAll += Distance(vp1->po,vp2->po);
          vp1 = vp2;
    };



    //  int i = LenAll / (runLen / tatamiOffset) +1;
    //  Len = LenAll / i;
      Len = LenAll / runPointsCount;


    newRunList->Add(new Vertex(v1->po, 0, -1, -1));
    Vertex *Data1 = v1, *lastData = v1;
    Vertex *Data2;
    P1.x = PR.x = Data1->po.x;
    P1.y = PR.y = Data1->po.y;
    int lastVerIndex = 0;
    for(int i=0;i<aCurve->Count-1;++i){
      Data2 = (Vertex *)aCurve->Items[i+1];
      Data1->nextVer = Data2;
      Data2->prevVer = Data1;
      P2 = Data2->po;
      a = Len-rdist;
      rdist += Distance(P1, P2);
      ang1 = getAngle(P1, P2);
      while( rdist > Len+5)
      { PR.x = P1.x + a * cos(ang1);
        PR.y = P1.y + a * sin(ang1);
          if (sharpCorners){
            for(int j = lastVerIndex + 1 ; j<i+1; j++){
               Vertex *Pdata1 = (Vertex *)aCurve->Items[j-1];
               Vertex *Pdata2 = (Vertex *)aCurve->Items[j];
               Vertex *Pdata3 = (Vertex *)aCurve->Items[j+1];
               double dotP = GetAngleDotProduct(Pdata1->po, Pdata2->po, Pdata3->po);
               if(dotP<0.707){
                  v = new Vertex(Pdata2->po, 0, -1, -1);
                  v->igoneInMakeRun = true;
                  newRunList->Add(v);
                  lastVerIndex = j+1;
               }
            }
          }

        newRunList->Add(new Vertex(PR, 0, -1, -1));
        a += Len;
        rdist -= Len;
        lastData = Data1;
        if (rdist < Len+5)
          lastVerIndex = i;
      }
      P1 = P2;
      Data1 = Data2;

    }

    aCurve->DeleteAll();
    int newInterval = interval;
    if (newInterval != abs(tatamiOffset)){
      aCurve->Add(newRunList->First());
      newRunList->Items[0] = NULL;
    }

    for (int n = 0; n < newRunList->Count; ++n){
      if (newRunList->Items[n] != NULL){
         Vertex *vp = (Vertex*) newRunList->Items[n];

         if (vp->igoneInMakeRun){
           aCurve->Add(newRunList->Items[n]);
           newRunList->Items[n] = NULL;
           continue;
         }

       }
       if(newInterval == abs(tatamiOffset)){
         aCurve->Add(newRunList->Items[n]);
         newRunList->Items[n] = NULL;
       }
       if(tatamiOffset<0){
         --newInterval;
         if (newInterval == 0)
           newInterval = 3;
       }else{
          ++newInterval;
         if (newInterval > tatamiOffset)
           newInterval = 1;
       }
    }

     --interval;
     if (interval < 1)
       interval = abs(tatamiOffset);

    if (newRunList->Last() != NULL){
      aCurve->Add(newRunList->Last());
      newRunList->Items[newRunList->Count-1] = NULL;
    }
    for (int n = 0; n < newRunList->Count; ++n)
      if (newRunList->Items[n] != NULL)
        delete (Vertex*) newRunList->Items[n];
    newRunList->Clear();
  }

  delete newRunList;

}

void makeRunningBetweenTwoVertexes_random(TList *Curves, int runLen, int tatamiOffset, bool sharpCorners)
{
  oneCurve *newRunList = new oneCurve();
  int interval = tatamiOffset;
  int runPointsCount;
  oneCurve *aCurve;
  Vertex *vp1,*vp2;
  Vertex *v1, *v2;
  double a, ang1,ang2,dotAngle;
  double Len = 0;
  double rdist = 0;
  double LenAll = 0;
  TPoint P1, P2, PR;
  TPoint P3, P4;



  aCurve = (oneCurve*) Curves->Items[ Curves->Count/2];
  vp1 =  (Vertex *) aCurve->First();
  for(int i = 0;i < aCurve->Count-1;++i){
          vp2 = (Vertex *) aCurve->Items[i+1];
          LenAll += Distance(vp1->po,vp2->po);
          vp1 = vp2;
  };
  runPointsCount = LenAll / (runLen / abs(tatamiOffset)) +1;




  for (int n = Curves->Count-1; n >= 0; --n){


    aCurve = (oneCurve*) Curves->Items[n];
    writeOnePolygon("aCurve.scr", aCurve);
    v1 = (Vertex *) aCurve->First();
    v2 = (Vertex *) aCurve->Last();
    LenAll = 0;
    Vertex *v = v1;

    vp1 =  (Vertex *) aCurve->First();
    for(int i = 0;i < aCurve->Count-1;++i){
          vp2 = (Vertex *) aCurve->Items[i+1];
          LenAll += Distance(vp1->po,vp2->po);
          vp1 = vp2;
    };



    //  int i = LenAll / (runLen / tatamiOffset) +1;
    //  Len = LenAll / i;
      Len = LenAll / runPointsCount;


    newRunList->Add(new Vertex(v1->po, 0, -1, -1));
    Vertex *Data1 = v1, *lastData = v1;
    Vertex *Data2;
    P1.x = PR.x = Data1->po.x;
    P1.y = PR.y = Data1->po.y;
    int lastVerIndex = 0;
    for(int i=0;i<aCurve->Count-1;++i){
      Data2 = (Vertex *)aCurve->Items[i+1];
      Data1->nextVer = Data2;
      Data2->prevVer = Data1;
      P2 = Data2->po;
      a = Len-rdist;
      rdist += Distance(P1, P2);
      ang1 = getAngle(P1, P2);
      while( rdist > Len+5)
      { PR.x = P1.x + a * cos(ang1);
        PR.y = P1.y + a * sin(ang1);
          if (sharpCorners){
            for(int j = lastVerIndex + 1 ; j<i+1; j++){
               Vertex *Pdata1 = (Vertex *)aCurve->Items[j-1];
               Vertex *Pdata2 = (Vertex *)aCurve->Items[j];
               Vertex *Pdata3 = (Vertex *)aCurve->Items[j+1];
               double dotP = GetAngleDotProduct(Pdata1->po, Pdata2->po, Pdata3->po);
               if(dotP<0.707){
                  v = new Vertex(Pdata2->po, 0, -1, -1);
                  v->igoneInMakeRun = true;
                  newRunList->Add(v);
                  lastVerIndex = j+1;
               }
            }
          }

        newRunList->Add(new Vertex(PR, 0, -1, -1));
        a += Len;
        rdist -= Len;
        lastData = Data1;
        if (rdist < Len+5)
          lastVerIndex = i;
      }
      P1 = P2;
      Data1 = Data2;

    }

    aCurve->DeleteAll();

    aCurve->Add(newRunList->First());
    newRunList->Items[0] = NULL;
    int aa = random(10) + 1;
    aCurve->Add(newRunList->Items[aa]);
    newRunList->Items[aa] = NULL;
    int newInterval = interval;
    for (int n = aa; n < newRunList->Count; ++n){
      if(n == aa){
       newInterval = interval+1;

      }
      if (newRunList->Items[n] != NULL){
         Vertex *vp = (Vertex*) newRunList->Items[n];

         if (vp->igoneInMakeRun){
           aCurve->Add(newRunList->Items[n]);
           newRunList->Items[n] = NULL;
           continue;
         }

       }
       if(newInterval == abs(tatamiOffset)){
         aCurve->Add(newRunList->Items[n]);
         newRunList->Items[n] = NULL;
       }
       if(tatamiOffset<0){
         --newInterval;
         if (newInterval == 0)
           newInterval = abs(tatamiOffset);
       }else{
          ++newInterval;
         if (newInterval > tatamiOffset)
           newInterval = 1;
       }
    }

    // --interval;
     //if (interval < 1)
       //interval = abs(tatamiOffset);

    if (newRunList->Last() != NULL){
      aCurve->Add(newRunList->Last());
      newRunList->Items[newRunList->Count-1] = NULL;
    }
    for (int n = 0; n < newRunList->Count; ++n)
      if (newRunList->Items[n] != NULL)
        delete (Vertex*) newRunList->Items[n];
    newRunList->Clear();
  }

  delete newRunList;

}

void fileterJoinedCurve_STartEnd(TList *Curves, int runLen, int tatamiOffset, bool hasAverageLen){
  double AverageLen;
  double AllLen = 0;
  oneCurve *newRunList = new oneCurve();
  int interval = 3;
  int runPointsCount;
  Vertex *vp1,*vp2;
  Vertex *v1, *v2;
  double a, ang1,ang2,dotAngle;
  double Len = 0;
  double rdist = 0;
  double LenAll = 0;
  TPoint P1, P2, PR;
  TPoint P3, P4;


  for(int i = 0; i < Curves->Count; ++i){
    oneCurve *aCurve = (oneCurve*) Curves->Items[i];
    writeOnePolygon("check.scr", aCurve);
    aCurve->calculateLength();
    AllLen +=  aCurve->length;
  }

  AverageLen = AllLen/(Curves->Count);
  runPointsCount = AverageLen/(runLen/abs(tatamiOffset))+1;

  for (int n = Curves->Count-1; n >= 0; --n){

    oneCurve *aCurve = (oneCurve*) Curves->Items[n];
    writeOnePolygon("aCurve.scr", aCurve);
    v1 = (Vertex *) aCurve->First();
    v2 = (Vertex *) aCurve->Last();
    LenAll = 0;
    Vertex *v = v1;

    if(hasAverageLen){
      Len = aCurve->length / runPointsCount;
    }else{
      Len = aCurve->length / (aCurve->length / ( runLen / abs(tatamiOffset)) +1);
    }


    newRunList->Add(new Vertex(v1->po, 0, -1, -1));
    Vertex *Data1 = v1, *lastData = v1;
    Vertex *Data2;
    P1.x = PR.x = Data1->po.x;
    P1.y = PR.y = Data1->po.y;
    int lastVerIndex = 0;
    for(int i=0;i<aCurve->Count-1;++i){
      Data2 = (Vertex *)aCurve->Items[i+1];
      Data1->nextVer = Data2;
      Data2->prevVer = Data1;
      P2 = Data2->po;
      a = Len-rdist;
      rdist += Distance(P1, P2);
      ang1 = getAngle(P1, P2);
      while( rdist > Len+5)
      { PR.x = P1.x + a * cos(ang1);
        PR.y = P1.y + a * sin(ang1);
            for(int j = lastVerIndex + 1 ; j<i+1; j++){
               Vertex *Pdata1 = (Vertex *)aCurve->Items[j-1];
               Vertex *Pdata2 = (Vertex *)aCurve->Items[j];
               Vertex *Pdata3 = (Vertex *)aCurve->Items[j+1];
               double dotP = GetAngleDotProduct(Pdata1->po, Pdata2->po, Pdata3->po);
               if(dotP<0.707){
                  v = new Vertex(Pdata2->po, 0, -1, -1);
                  v->igoneInMakeRun = true;
                  newRunList->Add(v);
                  lastVerIndex = j+1;
               }
            }
        newRunList->Add(new Vertex(PR, 0, -1, -1));
        a += Len;
        rdist -= Len;
        lastData = Data1;
        if (rdist < Len+5)
          lastVerIndex = i;
      }
      P1 = P2;
      Data1 = Data2;

    }


    aCurve->DeleteAll();
    int newInterval = interval;
    if (newInterval != abs(tatamiOffset)){
      aCurve->Add(newRunList->First());
      newRunList->Items[0] = NULL;
    }

    for (int n = 0; n < newRunList->Count; ++n){
      if (newRunList->Items[n] != NULL){
         Vertex *vp = (Vertex*) newRunList->Items[n];

         if (vp->igoneInMakeRun){
           aCurve->Add(newRunList->Items[n]);
           newRunList->Items[n] = NULL;
           continue;
         }

       }
       if(newInterval == abs(tatamiOffset)){
         aCurve->Add(newRunList->Items[n]);
         newRunList->Items[n] = NULL;
       }
       if(tatamiOffset<0){
         --newInterval;
         if (newInterval == 0)
           newInterval = 3;
       }else{
          ++newInterval;
         if (newInterval > tatamiOffset)
           newInterval = 1;
       }
    }

     --interval;
     if (interval < 1)
       interval = abs(tatamiOffset);

    if (newRunList->Last() != NULL){
      aCurve->Add(newRunList->Last());
      newRunList->Items[newRunList->Count-1] = NULL;
    }
    for (int n = 0; n < newRunList->Count; ++n)
      if (newRunList->Items[n] != NULL)
        delete (Vertex*) newRunList->Items[n];
    newRunList->Clear();

    writeOnePolygon("aCurve2.scr", aCurve);
  }
  delete newRunList;
  writePolygon("Curves4.scr", Curves);
  
}


void fileterJoinedCurve_ForRandom(TList *Curves, int runLen){
  double AverageLen;
  double AllLen = 0;
  oneCurve *newRunList = new oneCurve();
  int interval = 10;
  int runPointsCount;
  Vertex *vp1,*vp2;
  Vertex *v1, *v2;
  double a, ang1,ang2,dotAngle;
  double Len = 0;
  double rdist = 0;
  double LenAll = 0;
  TPoint P1, P2, PR;
  TPoint P3, P4;


  for(int i = 0; i < Curves->Count; ++i){
    oneCurve *aCurve = (oneCurve*) Curves->Items[i];
    writeOnePolygon("check.scr", aCurve);
    aCurve->calculateLength();
    AllLen +=  aCurve->length;
  }

  AverageLen = AllLen/(Curves->Count);
  runPointsCount = AverageLen/(runLen/10)+1;

  for (int n = Curves->Count-1; n >= 0; --n){

    oneCurve *aCurve = (oneCurve*) Curves->Items[n];
    v1 = (Vertex *) aCurve->First();
    v2 = (Vertex *) aCurve->Last();
    LenAll = 0;
    Vertex *v = v1;

    Len = aCurve->length / (aCurve->length / ( runLen /10) +1);


    newRunList->Add(new Vertex(v1->po, 0, -1, -1));
    Vertex *Data1 = v1, *lastData = v1;
    Vertex *Data2;
    P1.x = PR.x = Data1->po.x;
    P1.y = PR.y = Data1->po.y;
    int lastVerIndex = 0;
    for(int i=0;i<aCurve->Count-1;++i){
      Data2 = (Vertex *)aCurve->Items[i+1];
      Data1->nextVer = Data2;
      Data2->prevVer = Data1;
      P2 = Data2->po;
      a = Len-rdist;
      rdist += Distance(P1, P2);
      ang1 = getAngle(P1, P2);
      while( rdist > Len+5)
      { PR.x = P1.x + a * cos(ang1);
        PR.y = P1.y + a * sin(ang1);
            for(int j = lastVerIndex + 1 ; j<i+1; j++){
               Vertex *Pdata1 = (Vertex *)aCurve->Items[j-1];
               Vertex *Pdata2 = (Vertex *)aCurve->Items[j];
               Vertex *Pdata3 = (Vertex *)aCurve->Items[j+1];
               double dotP = GetAngleDotProduct(Pdata1->po, Pdata2->po, Pdata3->po);
               if(dotP<0.707){
                  v = new Vertex(Pdata2->po, 0, -1, -1);
                  v->igoneInMakeRun = true;
                  newRunList->Add(v);
                  lastVerIndex = j+1;
               }
            }
        newRunList->Add(new Vertex(PR, 0, -1, -1));
        a += Len;
        rdist -= Len;
        lastData = Data1;
        if (rdist < Len+5)
          lastVerIndex = i;
      }
      P1 = P2;
      Data1 = Data2;

    }


    aCurve->DeleteAll();


    aCurve->Add(newRunList->First());
    newRunList->Items[0] = NULL;
    //srand(1001);
    int aa = random(10) + 1;
    aCurve->Add(newRunList->Items[aa]);
    newRunList->Items[aa] = NULL;
    int newInterval = interval;
    for (int n = aa; n < newRunList->Count; ++n){

      if(n == aa){
       newInterval = interval+1;

      }
      if (newRunList->Items[n] != NULL){
         Vertex *vp = (Vertex*) newRunList->Items[n];

         if (vp->igoneInMakeRun){
           aCurve->Add(newRunList->Items[n]);
           newRunList->Items[n] = NULL;
           continue;
         }

       }
       if(newInterval == 10){
         aCurve->Add(newRunList->Items[n]);
         newRunList->Items[n] = NULL;
       }
        ++newInterval;
        if (newInterval > 10)
        newInterval = 1;

    }

     //--interval;
     //if (interval < 1)
       //interval = abs(tatamiOffset);

    if (newRunList->Last() != NULL){
      aCurve->Add(newRunList->Last());
      newRunList->Items[newRunList->Count-1] = NULL;
    }
    for (int n = 0; n < newRunList->Count; ++n)
      if (newRunList->Items[n] != NULL)
        delete (Vertex*) newRunList->Items[n];
    newRunList->Clear();

  }
  delete newRunList;

  writePolygon("Curves8.scr", Curves);

}
void filterCurve_StartEnds(TList *Curves, int minDist){
   for(int j = 1;j<Curves->Count/2;++j){
     oneCurve *nextCurve = (oneCurve*) Curves->Items[j];
     for(int i = 0 ;i < nextCurve->Count/2;++i){
       Vertex *p = (Vertex *)nextCurve->Items[i];
         oneCurve *aCurve = (oneCurve*) Curves->Items[0];
         for(int m = 0; m < aCurve->Count/2; ++m){
           Vertex *p1 = (Vertex *)aCurve->Items[m];
           Vertex *p2 = (Vertex *)aCurve->Items[m+1];
           double dotp1 = GetAngleDotProduct(p1->po,p2->po,p->po);
           double dotp2 = GetAngleDotProduct(p2->po,p1->po,p->po);

           if(dotp1 <= 0 || dotp2 <= 0 ){
             double distline = GetDistLinePoint(p1->po,p2->po,p->po);
             if( GetDistLinePoint(p1->po,p2->po,p->po)< minDist){
                delete (Vertex*) nextCurve->Items[i];
                nextCurve->Items[i] = NULL;
             }
           }
         }
     }
     nextCurve->Pack();
   }

   for(int j =Curves->Count/2 ;j<Curves->Count-1;++j){
     oneCurve *nextCurve = (oneCurve*) Curves->Items[j];
     for(int i = 0 ;i < nextCurve->Count/2;++i){
       Vertex *p = (Vertex *)nextCurve->Items[i];
         oneCurve *aCurve = (oneCurve*) Curves->Last();
         for(int m = 0; m < aCurve->Count/2; ++m){
           Vertex *p1 = (Vertex *)aCurve->Items[m];
           Vertex *p2 = (Vertex *)aCurve->Items[m+1];
           double dotp1 = GetAngleDotProduct(p1->po,p2->po,p->po);
           double dotp2 = GetAngleDotProduct(p2->po,p1->po,p->po);

           if(dotp1 <= 0 || dotp2 <= 0 ){
             double distline = GetDistLinePoint(p1->po,p2->po,p->po);
             if( GetDistLinePoint(p1->po,p2->po,p->po)< minDist){
                delete (Vertex*) nextCurve->Items[i];
                nextCurve->Items[i] = NULL;
             }
           }

         }

     }

     nextCurve->Pack();
   }

   for(int j = 1;j<Curves->Count/2;++j){
    oneCurve *nextCurve = (oneCurve*) Curves->Items[j];
     for(int i = nextCurve->Count/2 ;i < nextCurve->Count; ++i){
         Vertex *p = (Vertex *)nextCurve->Items[i];
         oneCurve *aCurve = (oneCurve*) Curves->Items[0];
         for(int m = aCurve->Count/2 ; m < aCurve->Count-1; ++m){
           Vertex *p1 = (Vertex *)aCurve->Items[m];
           Vertex *p2 = (Vertex *)aCurve->Items[m+1];
           double dotp1 = GetAngleDotProduct(p1->po,p2->po,p->po);
           double dotp2 = GetAngleDotProduct(p2->po,p1->po,p->po);

           if(dotp1 <= 0 || dotp2 <= 0 ){
             double distline = GetDistLinePoint(p1->po,p2->po,p->po);
             if( GetDistLinePoint(p1->po,p2->po,p->po)< minDist){
                delete (Vertex*) nextCurve->Items[i];
                nextCurve->Items[i] = NULL;
             }
           }  

         }

     }

     nextCurve->Pack();
     writeOnePolygon("nextCurve.scr",nextCurve);

   }


   for(int j = Curves->Count / 2; j < Curves->Count-1; ++j){
    oneCurve *nextCurve = (oneCurve*) Curves->Items[j];
    writeOnePolygon("nextCurve.scr",nextCurve);
     for(int i = nextCurve->Count-1; i > nextCurve->Count/2; --i){
         Vertex *p = (Vertex *)nextCurve->Items[i];
         oneCurve *aCurve = (oneCurve*) Curves->Last();
         int acurveCount = aCurve->Count;
         for(int m = aCurve->Count-1; m > aCurve->Count/2; --m){
           Vertex *p1 = (Vertex *)aCurve->Items[m];
           Vertex *p2 = (Vertex *)aCurve->Items[m-1];
           double dotp1 = GetAngleDotProduct(p1->po,p2->po,p->po);
           double dotp2 = GetAngleDotProduct(p2->po,p1->po,p->po);

           if(dotp1 <= 0 || dotp2 <= 0 ){
             double distline = GetDistLinePoint(p1->po,p2->po,p->po);
             if( GetDistLinePoint(p1->po,p2->po,p->po)< minDist){
                delete (Vertex *) nextCurve->Items[i];
                nextCurve->Items[i] = NULL;
             }
           }

         }

     }
     nextCurve->Pack();
     writeOnePolygon("nextCurve.scr",nextCurve);
   }

}
void makeRunningWithPoly(TList *Polygons, TList *curveList, int Density, int RunLen,int tatamiOffset,int OffsetMeothode){

  oneCurve *leftList = new oneCurve();
  oneCurve *rightList = new oneCurve();

  TPoint po;

  int curveCount;

  oneCurve *poly = (oneCurve*) Polygons->First();
  Vertex *v = (Vertex *) poly->First();
  Vertex *vL = (Vertex *) poly->Last();
  Vertex *mv = (Vertex *) poly->Items[poly->Count/2];

  if (!samePoint(v->po, vL->po)){
    poly->Add(new Vertex(v->po, 0, -1, -1 ));
  }

  //rightList->Add(v);
  int maxDist = 0, Dist;
  for(int i = 0;i < poly->Count/2;++i){
    Vertex *P1 = (Vertex *)poly->Items[i];
    Vertex *P2 = (Vertex *)poly->Items[poly->Count-i-1];
    leftList->Add(P1);//   //new Vertex(P1->po, 0, -1, -1));
    rightList->Add(P2);//  //new Vertex(P2->po, 0, -1, -1));
    Dist = Distance(P1->po, P2->po);
    if (Dist > maxDist)
      maxDist = Dist;
  }
  if ( (poly->Count % 2) != 0){
    leftList->Add(poly->Items[poly->Count/2]);
    rightList->Add(poly->Items[poly->Count/2]);
  }


  curveCount = max(2, maxDist / Density * 2);



  writeOnePolygon("LeftList.scr", leftList);
  writeOnePolygon("RightList.scr", rightList);

  oneCurve *newCurve = new oneCurve();
  curveList->Add(newCurve);
  for (int i = 0; i < leftList->Count; ++i){
    Vertex *P1 = (Vertex *)leftList->Items[i];
    newCurve->Add(new Vertex(P1->po, 0));
  }
  for(int j = 1; j < curveCount-1; ++j){
    newCurve = new oneCurve();
    curveList->Add(newCurve);
    for(int i = 0; i < leftList->Count; ++i){
      Vertex *p1 = (Vertex *)leftList->Items[i];
      Vertex *p2 = (Vertex *)rightList->Items[i];
      po.x = p1->po.x + (p2->po.x - p1->po.x) *  j / (curveCount - 1);
      po.y = p1->po.y + (p2->po.y - p1->po.y) *  j / (curveCount - 1);
      newCurve->Add(new Vertex(po, 0));

    }
  }

  newCurve = new oneCurve();
  curveList->Add(newCurve);
  for (int i = 0; i < rightList->Count; ++i){
    Vertex *P1 = (Vertex *)rightList->Items[i];
    newCurve->Add(new Vertex(P1->po, 0));
  }


  writePolygon("curveList2.scr", curveList);


  if(OffsetMeothode == 0){
     fileterJoinedCurve_STartEnd(curveList, RunLen, tatamiOffset,true);
  }else if(OffsetMeothode == 1){
     fileterJoinedCurve_STartEnd(curveList, RunLen, tatamiOffset,false);
  }else if(OffsetMeothode == 2){
     fileterJoinedCurve_ForRandom(curveList, RunLen);
  }
  //fileterJoinedCurve_STartEnd(curveList, RunLen, tatamiOffset,hasAverageLen);

  for (int i = 0; i <curveList->Count; ++i){
    newCurve = (oneCurve*) curveList->Items[i];
    newCurve->offsetIndex = i;
    if ( (i % 2) != 0)
      newCurve->reverse();
  }

  delete leftList;
  delete rightList;

}


void makeRunningWithOpenPoly(TList *Polygons, TList *curveList, int Density, int RunLen,int tatamiOffset,int OffsetMeothode){


  oneCurve *leftList = (oneCurve*) Polygons->First();
  oneCurve *rightList = (oneCurve*) Polygons->Items[1];
  TPoint po;

  int curveCount;
  //rightList->Add(v);
  int maxDist = 0, Dist;
  for(int i = 0;i < leftList->Count;++i){
    Vertex *P1 = (Vertex *)leftList->Items[i];
    Vertex *P2 = (Vertex *)rightList->Items[i];
    Dist = Distance(P1->po, P2->po);
    if (Dist > maxDist)
      maxDist = Dist;
  }


  curveCount = max(2, maxDist / Density * 2);






  writeOnePolygon("LeftList.scr", leftList);
  writeOnePolygon("RightList.scr", rightList);

  oneCurve *newCurve = new oneCurve();
  curveList->Add(newCurve);
  for (int i = 0; i < leftList->Count; ++i){
    Vertex *P1 = (Vertex *)leftList->Items[i];
    newCurve->Add(new Vertex(P1->po, 0));
  }
  for(int j = 1; j < curveCount-1; ++j){
    newCurve = new oneCurve();
    curveList->Add(newCurve);
    for(int i = 0; i < leftList->Count; ++i){
      Vertex *p1 = (Vertex *)leftList->Items[i];
      Vertex *p2 = (Vertex *)rightList->Items[i];
      po.x = p1->po.x + (p2->po.x - p1->po.x) *  j / (curveCount - 1);
      po.y = p1->po.y + (p2->po.y - p1->po.y) *  j / (curveCount - 1);
      newCurve->Add(new Vertex(po, 0));

    }
  }

  newCurve = new oneCurve();
  curveList->Add(newCurve);
  for (int i = 0; i < rightList->Count; ++i){
    Vertex *P1 = (Vertex *)rightList->Items[i];
    newCurve->Add(new Vertex(P1->po, 0));
  }


  writePolygon("curveList2.scr", curveList);


  if(OffsetMeothode == 0){
     fileterJoinedCurve_STartEnd(curveList, RunLen, tatamiOffset,true);
  }else if(OffsetMeothode == 1){
     fileterJoinedCurve_STartEnd(curveList, RunLen, tatamiOffset,false);
  }else if(OffsetMeothode == 2){
     fileterJoinedCurve_ForRandom(curveList, RunLen);
  }
  //fileterJoinedCurve_STartEnd(curveList, RunLen, tatamiOffset,hasAverageLen);

  for (int i = 0; i <curveList->Count; ++i){
    newCurve = (oneCurve*) curveList->Items[i];
    newCurve->offsetIndex = i;
    if ( (i % 2) != 0)
      newCurve->reverse();
  }

  //delete leftList;
  //delete rightList;

}

double getDistFromPointToLine_1006(TPoint LP1, TPoint LP2, TPoint P){
  double ux = LP2.x - LP1.x;
  double uy = LP2.y - LP1.y;
  double vx = P.x - LP1.x;
  double vy = P.y - LP1.y;
  double wx = P.x - LP2.x;
  double wy = P.y - LP2.y;
  double umv = ux * vx + uy * vy;
  double umw = ux * wx + uy * wy;
  if( umv * umv > 0 ){
  //not on line
    if(umv > 0){
      //after endpoint
      return sqrt(wx * wx + wy * wy);
    }else{
      //before startpoint
      return sqrt(vx * vx + vy * vy);
    }
  }else{
    //online
    return abs(ux * vy - uy * vx)/sqrt(ux * ux + uy * uy);
  }
}

double getDistFromPointToLine(TPoint LP1, TPoint LP2, TPoint P){
   TPoint P3,gp;
   double ang2 = getAngle(LP1,LP2);
   P3.x = P.x + 1000*cos(M_PI_2-ang2);
   P3.y = P.y + 1000*sin(M_PI_2-ang2);
   bool showInter = GetIntersection(gp,LP1,LP2,P,P3,true);
   return Distance(gp,P);
}

int getDistFromPointToLineType(TPoint LP1, TPoint LP2, TPoint P){
  double ux = LP2.x - LP1.x;
  double uy = LP2.y - LP1.y;
  double vx = P.x - LP1.x;
  double vy = P.y - LP1.y;
  double wx = P.x - LP2.x;
  double wy = P.y - LP2.y;
  double umv = ux * vx + uy * vy;
  double umw = ux * wx + uy * wy;
  if( umv * umv > 0 ){
  //not on line
    if(umv > 0){
      //after endpoint
      return 1;
    }else{
      //before startpoint
      return 2;
    }
  }else{
    //online
    return 3;
  }
}
void makeRunFromInitPointToPolygon(TList *Polygons,TList *allObjGroups,Vertex *initVer,int initType){
   oneCurve *newRunList = new oneCurve();
   oneCurve *poly = (oneCurve*) Polygons->First();
   if(initType == 1){
     TList *firstGroup = (TList*) allObjGroups->First();
     oneCurve *firstGroupFirstCurve = (oneCurve*) firstGroup->First();
     Vertex *fVer = (Vertex *) firstGroupFirstCurve->First();
     if (fVer->PolyIndex != 0){
       cout << "Can't Make Run from Start !\n";
       return;
     }
     makeRunOnMainPolygonEdge(poly, initVer, fVer->PolyVertex, newRunList);
     writeOnePolygon("newRunList1.scr", newRunList);
   }else{
     TList *lastGroup = (TList*) allObjGroups->Last();
     oneCurve *lastGrouplastCurve = (oneCurve*) lastGroup->Last();
     Vertex *lVer = (Vertex *) lastGrouplastCurve->Last();
     if (lVer->PolyIndex != 0){
       cout << "Can't Make Run from Start !\n";
       return;
     }
     makeRunOnMainPolygonEdge(poly, lVer->PolyVertex, initVer, newRunList);
     writeOnePolygon("newRunList2.scr", newRunList);
   }





   FreeOnePoly(newRunList);
}

oneCurve *correctEndsForNearPoints(TList *Curves, int mindist)
{
  writePolygon("curves_3.scr", Curves);
  Vertex *ver;

   oneCurve *joinedCurve = new oneCurve();
   TList *leftPointsList = new TList();
   TList *rightPointsList = new TList();
   int safeDist = mindist + 50;

   for (int i = 0; i < Curves->Count; ++i){
      oneCurve *aCurve = (oneCurve*) Curves->Items[i];
      if (i == 0)
        leftPointsList->Add(aCurve->First());
      if ( (i % 2) == 0 )
        rightPointsList->Add(aCurve->Last());
      else
        leftPointsList->Add(aCurve->Last());
      for (int j = (i == 0)? 0 : 1; j < aCurve->Count; ++j){
        joinedCurve->Add(aCurve->Items[j]);
      }
   }

   writeOnePolygon("joinedCurve.scr", joinedCurve);
   writePointsList("leftPointsList.scr", leftPointsList);
   writePointsList("rightPointsList.scr", rightPointsList);

    int v0Ndx;
    int vpNdx;
    int vnNdx;

   for (int ii = leftPointsList->Count/2; ii >0 ; --ii ){
     for (int jj = leftPointsList->Count/2; jj >0 ; --jj ){
        if (ii == jj) continue;
        Vertex *v0 = (Vertex*) leftPointsList->Items[jj];


        Vertex *ver = (Vertex*) leftPointsList->Items[ii];
        int Dist = Distance(ver->po, v0->po);
        if (Dist < mindist){
           //jj = ii;
           v0Ndx = joinedCurve->IndexOf(v0);
           vpNdx = v0Ndx-1;
           vnNdx = v0Ndx+1;
           Vertex *vp = (Vertex*) joinedCurve->Items[vpNdx];
           Vertex *vn = (Vertex*) joinedCurve->Items[vnNdx];
           while(Distance(ver->po, vp->po) < mindist){
                joinedCurve->Items[vpNdx] = NULL;
                --vpNdx;
                --v0Ndx;
                vp = (Vertex*) joinedCurve->Items[vpNdx];
           }
           while(Distance(ver->po, vn->po) < mindist){
                joinedCurve->Items[vnNdx] = NULL;
                ++vnNdx;
                vn = (Vertex*) joinedCurve->Items[vnNdx];
           }
           joinedCurve->Pack();

           vp = (Vertex*) joinedCurve->Items[v0Ndx-1];
           if (samePoint(ver->po, v0->po)){
              double ang = getAngle(v0->po, vp->po);
              v0->po.x = v0->po.x + safeDist * cos(ang);
              v0->po.y = v0->po.y + safeDist * sin(ang);
              vnNdx = v0Ndx + 1;
              while(true){
                Vertex *vn = (Vertex*) joinedCurve->Items[vnNdx];
                if (Distance(v0->po, vn->po) < safeDist){
                   joinedCurve->Delete(vnNdx);
                }
                else break;
              }
              vpNdx = v0Ndx - 1;
              while(true){
                Vertex *vp = (Vertex*) joinedCurve->Items[vpNdx];
                if (Distance(v0->po, vp->po) < safeDist){
                   joinedCurve->Delete(vpNdx);
                   --vpNdx;
                }
                else break;
              }
           }
           else{
             TPoint p;
             double ang = getAngle(v0->po, vp->po);
             int x = ver->po.x * cos(-ang) - ver->po.y * sin(-ang);
             int y = (v0->po.x * sin(-ang) + v0->po.y * cos(-ang));
             p.x = x * cos(ang) - y * sin(ang);
             p.y = x * sin(ang) + y * cos(ang);

             int dist_ver_intpo = Distance(ver->po, p);
             int dist_intpo_circle = sqrt(safeDist*safeDist - dist_ver_intpo * dist_ver_intpo);

             double dotP1 = GetAngleDotProduct(p, v0->po, vp->po);
             int finalDist = 0;
             if (dotP1 < 0) // intpo is located between v0 and vp
               finalDist = Distance(v0->po, p) + dist_intpo_circle;
             else  //intpo is located behind v0
               finalDist = dist_intpo_circle - Distance(v0->po, p);

             ang = getAngle(v0->po, vp->po);
             v0->po.x = v0->po.x + finalDist * cos(ang);
             v0->po.y = v0->po.y + finalDist * sin(ang);

              vnNdx = v0Ndx + 1;
              while(true){
                Vertex *vn = (Vertex*) joinedCurve->Items[vnNdx];
                if (Distance(v0->po, vn->po) < safeDist){
                   joinedCurve->Delete(vnNdx);
                }
                else break;
              }
              vpNdx = v0Ndx - 1;
              while(true){
                Vertex *vp = (Vertex*) joinedCurve->Items[vpNdx];
                if (Distance(v0->po, vp->po) < safeDist){
                   joinedCurve->Items[vpNdx] =NULL;
                   --vpNdx;
                }
                else break;
              }
              joinedCurve->Pack();
           }
        }
     }
   }



   for (int ii = leftPointsList->Count/2; ii < leftPointsList->Count-1; ++ii){
     for (int jj = leftPointsList->Count/2; jj < leftPointsList->Count-1; ++jj){
        if (ii == jj) continue;
        Vertex *ver = (Vertex*) leftPointsList->Items[ii];
        Vertex *v0 = (Vertex*) leftPointsList->Items[jj];
        int Dist = Distance(ver->po, v0->po);
        if (Dist < mindist){
           int v0Ndx = joinedCurve->IndexOf(v0);
           int vpNdx = v0Ndx-1;
           int vnNdx = v0Ndx+1;
           Vertex *vp = (Vertex*) joinedCurve->Items[vpNdx];
           Vertex *vn = (Vertex*) joinedCurve->Items[vnNdx];
           while(Distance(ver->po, vp->po) < mindist){
                joinedCurve->Items[vpNdx] = NULL;
                --vpNdx;
                --v0Ndx;
                vp = (Vertex*) joinedCurve->Items[vpNdx];
           }
           while(Distance(ver->po, vn->po) < mindist){
                joinedCurve->Items[vnNdx] = NULL;
                ++vnNdx;
                vn = (Vertex*) joinedCurve->Items[vnNdx];
           }
           joinedCurve->Pack();

           vp = (Vertex*) joinedCurve->Items[v0Ndx-1];
           if (samePoint(ver->po, v0->po)){
              double ang = getAngle(v0->po, vp->po);
              v0->po.x = v0->po.x + safeDist * cos(ang);
              v0->po.y = v0->po.y + safeDist * sin(ang);
              vnNdx = v0Ndx + 1;
              while(true){
                Vertex *vn = (Vertex*) joinedCurve->Items[vnNdx];
                if (Distance(v0->po, vn->po) < safeDist){
                   joinedCurve->Delete(vnNdx);
                }
                else break;
              }
              vpNdx = v0Ndx - 1;
              while(true){
                Vertex *vp = (Vertex*) joinedCurve->Items[vpNdx];
                if (Distance(v0->po, vp->po) < safeDist){
                   joinedCurve->Delete(vpNdx);
                   --vpNdx;
                }
                else break;
              }
           }
           else{
             TPoint p;
             double ang = getAngle(v0->po, vp->po);
             int x = ver->po.x * cos(-ang) - ver->po.y * sin(-ang);
             int y = (v0->po.x * sin(-ang) + v0->po.y * cos(-ang));
             p.x = x * cos(ang) - y * sin(ang);
             p.y = x * sin(ang) + y * cos(ang);

             int dist_ver_intpo = Distance(ver->po, p);
             int dist_intpo_circle = sqrt(safeDist*safeDist - dist_ver_intpo * dist_ver_intpo);

             double dotP1 = GetAngleDotProduct(p, v0->po, vp->po);
             int finalDist = 0;
             if (dotP1 < 0) // intpo is located between v0 and vp
               finalDist = Distance(v0->po, p) + dist_intpo_circle;
             else  //intpo is located behind v0
               finalDist = dist_intpo_circle - Distance(v0->po, p);

             ang = getAngle(v0->po, vp->po);
             v0->po.x = v0->po.x + finalDist * cos(ang);
             v0->po.y = v0->po.y + finalDist * sin(ang);

              vnNdx = v0Ndx + 1;
              while(true){
                Vertex *vn = (Vertex*) joinedCurve->Items[vnNdx];
                if (Distance(v0->po, vn->po) < safeDist){
                   joinedCurve->Delete(vnNdx);
                }
                else break;
              }
              vpNdx = v0Ndx - 1;
              while(true){
                Vertex *vp = (Vertex*) joinedCurve->Items[vpNdx];
                if (Distance(v0->po, vp->po) < safeDist){
                   joinedCurve->Items[vpNdx] =NULL;
                   --vpNdx;
                }
                else break;
              }
              joinedCurve->Pack();
           }
        }
     }
   }















   writeOnePolygon("joinedCurve-Left.scr", joinedCurve);




   for (int ii = rightPointsList->Count/2; ii >0 ; --ii ){
     for (int jj = rightPointsList->Count/2; jj >0 ; --jj ){
        if (ii == jj) continue;
        Vertex *v0 = (Vertex*) rightPointsList->Items[jj];


        Vertex *ver = (Vertex*) rightPointsList->Items[ii];
        int Dist = Distance(ver->po, v0->po);
        if (Dist < mindist){
           v0Ndx = joinedCurve->IndexOf(v0);
           vpNdx = v0Ndx-1;
           vnNdx = v0Ndx+1;
           Vertex *vp = (Vertex*) joinedCurve->Items[vpNdx];
           Vertex *vn = (Vertex*) joinedCurve->Items[vnNdx];
           while(Distance(ver->po, vp->po) < mindist){
                joinedCurve->Items[vpNdx] = NULL;
                --vpNdx;
                --v0Ndx;
                vp = (Vertex*) joinedCurve->Items[vpNdx];
           }
           while(Distance(ver->po, vn->po) < mindist){
                joinedCurve->Items[vnNdx] = NULL;
                ++vnNdx;
                vn = (Vertex*) joinedCurve->Items[vnNdx];
           }
           joinedCurve->Pack();

           vp = (Vertex*) joinedCurve->Items[v0Ndx-1];
           if (samePoint(ver->po, v0->po)){
              double ang = getAngle(v0->po, vp->po);
              v0->po.x = v0->po.x + safeDist * cos(ang);
              v0->po.y = v0->po.y + safeDist * sin(ang);
              vnNdx = v0Ndx + 1;
              while(true){
                Vertex *vn = (Vertex*) joinedCurve->Items[vnNdx];
                if (Distance(v0->po, vn->po) < safeDist){
                   joinedCurve->Delete(vnNdx);
                }
                else break;
              }
              vpNdx = v0Ndx - 1;
              while(true){
                Vertex *vp = (Vertex*) joinedCurve->Items[vpNdx];
                if (Distance(v0->po, vp->po) < safeDist){
                   joinedCurve->Delete(vpNdx);
                   --vpNdx;
                }
                else break;
              }
           }
           else{
             TPoint p;
             double ang = getAngle(v0->po, vp->po);
             int x = ver->po.x * cos(-ang) - ver->po.y * sin(-ang);
             int y = (v0->po.x * sin(-ang) + v0->po.y * cos(-ang));
             p.x = x * cos(ang) - y * sin(ang);
             p.y = x * sin(ang) + y * cos(ang);

             int dist_ver_intpo = Distance(ver->po, p);
             int dist_intpo_circle = sqrt(safeDist*safeDist - dist_ver_intpo * dist_ver_intpo);

             double dotP1 = GetAngleDotProduct(p, v0->po, vp->po);
             int finalDist = 0;
             if (dotP1 < 0) // intpo is located between v0 and vp
               finalDist = Distance(v0->po, p) + dist_intpo_circle;
             else  //intpo is located behind v0
               finalDist = dist_intpo_circle - Distance(v0->po, p);

             ang = getAngle(v0->po, vp->po);
             v0->po.x = v0->po.x + finalDist * cos(ang);
             v0->po.y = v0->po.y + finalDist * sin(ang);

              vnNdx = v0Ndx + 1;
              while(true){
                Vertex *vn = (Vertex*) joinedCurve->Items[vnNdx];
                if (Distance(v0->po, vn->po) < safeDist){
                   joinedCurve->Delete(vnNdx);
                }
                else break;
              }
              vpNdx = v0Ndx - 1;
              while(true){
                Vertex *vp = (Vertex*) joinedCurve->Items[vpNdx];
                if (Distance(v0->po, vp->po) < safeDist){
                   joinedCurve->Items[vpNdx] =NULL;
                   --vpNdx;
                }
                else break;
              }
              joinedCurve->Pack();
           }
        }
     }
   }



   for (int ii = rightPointsList->Count/2; ii < rightPointsList->Count-1; ++ii){
     for (int jj = rightPointsList->Count/2; jj < rightPointsList->Count-1; ++jj){
        if (ii == jj) continue;
        Vertex *ver = (Vertex*) rightPointsList->Items[ii];
        Vertex *v0 = (Vertex*) rightPointsList->Items[jj];
        int Dist = Distance(ver->po, v0->po);
        if (Dist < mindist){
           //j = i;
           int v0Ndx = joinedCurve->IndexOf(v0);
           int vpNdx = v0Ndx-1;
           int vnNdx = v0Ndx+1;
           Vertex *vp = (Vertex*) joinedCurve->Items[vpNdx];
           Vertex *vn = (Vertex*) joinedCurve->Items[vnNdx];
           while(Distance(ver->po, vp->po) < mindist){
                joinedCurve->Items[vpNdx] = NULL;
                --vpNdx;
                --v0Ndx;
                vp = (Vertex*) joinedCurve->Items[vpNdx];
           }
           while(Distance(ver->po, vn->po) < mindist){
                joinedCurve->Items[vnNdx] = NULL;
                ++vnNdx;
                vn = (Vertex*) joinedCurve->Items[vnNdx];
           }
           joinedCurve->Pack();

           vp = (Vertex*) joinedCurve->Items[v0Ndx-1];
           if (samePoint(ver->po, v0->po)){
              double ang = getAngle(v0->po, vp->po);
              v0->po.x = v0->po.x + safeDist * cos(ang);
              v0->po.y = v0->po.y + safeDist * sin(ang);
              vnNdx = v0Ndx + 1;
              while(true){
                Vertex *vn = (Vertex*) joinedCurve->Items[vnNdx];
                if (Distance(v0->po, vn->po) < safeDist){
                   joinedCurve->Delete(vnNdx);
                }
                else break;
              }
              vpNdx = v0Ndx - 1;
              while(true){
                Vertex *vp = (Vertex*) joinedCurve->Items[vpNdx];
                if (Distance(v0->po, vp->po) < safeDist){
                   joinedCurve->Delete(vpNdx);
                   --vpNdx;
                }
                else break;
              }
           }
           else{
             TPoint p;
             double ang = getAngle(v0->po, vp->po);
             int x = ver->po.x * cos(-ang) - ver->po.y * sin(-ang);
             int y = (v0->po.x * sin(-ang) + v0->po.y * cos(-ang));
             p.x = x * cos(ang) - y * sin(ang);
             p.y = x * sin(ang) + y * cos(ang);

             int dist_ver_intpo = Distance(ver->po, p);
             int dist_intpo_circle = sqrt(safeDist*safeDist - dist_ver_intpo * dist_ver_intpo);

             double dotP1 = GetAngleDotProduct(p, v0->po, vp->po);
             int finalDist = 0;
             if (dotP1 < 0) // intpo is located between v0 and vp
               finalDist = Distance(v0->po, p) + dist_intpo_circle;
             else  //intpo is located behind v0
               finalDist = dist_intpo_circle - Distance(v0->po, p);

             ang = getAngle(v0->po, vp->po);
             v0->po.x = v0->po.x + finalDist * cos(ang);
             v0->po.y = v0->po.y + finalDist * sin(ang);

              vnNdx = v0Ndx + 1;
              while(true){
                Vertex *vn = (Vertex*) joinedCurve->Items[vnNdx];
                if (Distance(v0->po, vn->po) < safeDist){
                   joinedCurve->Delete(vnNdx);
                }
                else break;
              }
              vpNdx = v0Ndx - 1;
              while(true){
                Vertex *vp = (Vertex*) joinedCurve->Items[vpNdx];
                if (Distance(v0->po, vp->po) < safeDist){
                   joinedCurve->Items[vpNdx] =NULL;
                   --vpNdx;
                }
                else break;
              }
              joinedCurve->Pack();
           }
        }
     }
   }


   writeOnePolygon("joinedCurve-All.scr", joinedCurve);


   delete leftPointsList;
   delete rightPointsList;


   return joinedCurve;
}


int main_2022_10_10_joinedCurve(int argc, char* argv[])     //(int argc, char* argv[])
{


   Vertex *ver = NULL;

   TPoint startPoint, endPoint;



   //int density = 2000;     //This is ok
   String PolyFile = "Polys\\P17.scr";
   //String CurveFile = "Curves\\C17.scr";

   int density = 1000;     //This is ok
   //String PolyFile = "Polys\\P_20.scr";

   int runLength = 10000;
   int mindist = 1000;
   int tatamiOffset = 10;



   int rectMargin = 20000;
   int initialRunLen = 4000;
   int OffsetMeothode = 2;  //0---hasAverageLen == true ,1---hasAverageLen == false ,2---freedom
   bool sharpCorners = false;



   TList* Curves = new TList();
   TList* Polygons = new TList();
   TList *newCurves = new TList();

   if (!FileExists(PolyFile)){
       cout << PolyFile.c_str() << " does not exist!\n";
       int a;
       cin >> a;
       return(0);
   }

   ReadFromFile_2(PolyFile, Polygons, true);

   if (Polygons->Count == 0){
       cout << " Polygons is empty!\n";
       int a;
       cin >> a;
       return(0);
   }

   for (int i = 0; i < Polygons->Count; ++i)
     GetPolygonDirection((oneCurve*) Polygons->Items[i]);
   correctPolygonDirections(Polygons);

   writePolygon("AllPolygons.scr", Polygons);

   makeRunningWithPoly(Polygons, Curves, density, runLength, tatamiOffset,OffsetMeothode);
   //filterCurve_StartEnds(Curves,density*0.2);
   writePolygon("Curves1.scr", Curves);

   writePolygon("curves_2.scr", Curves);

   oneCurve *joinedCurve = correctEndsForNearPoints(Curves, mindist);

   delete joinedCurve;

   writePolygon("Curves.scr", Curves);

   FreePolygon(Polygons);
   FreePolygon(Curves);

   return 0;

}


//main
int main_2022_09_22_forOffsetPolygons_and_oneCurve(int argc, char* argv[])     //_2022_09_22_forOffsetPolygons_and_oneCurve(int argc, char* argv[])
{


   Vertex *ver = NULL;

   TPoint startPoint, endPoint;

   //main1();

   //int offsetDist = 1500;
   //String PolyFile = "Polys\\PJ-1.scr";
   //String CurveFile = "Curves\\CJ-1.scr";
   //int rectMargin = 20000;

   //int offsetDist = 200;
   //int offsetDist = 1500;
   //String PolyFile = "Polys\\P13.scr";
   //String CurveFile = "Curves\\C13.scr";
   //int rectMargin = 20000;

   //int offsetDist = 1200;
   //String PolyFile = "Polys\\Poly_4.scr";
   //String CurveFile = "Curves\\Curve_5.scr";

   //int offsetDist = 400;
   //String PolyFile = "Polys\\Poly_3.scr";
   //String CurveFile = "Curves\\Curve_11.scr";


   //int offsetDist = 500;
   //String PolyFile = "Polys\\Poly_2.scr";
   //String CurveFile = "Curves\\C2.scr";

   //int offsetDist =1500; // check_Fix_Offset_NewCurves is not removing the wrong curve in extraNewCurves
   //String PolyFile = "Polys\\P4.scr";
   //String CurveFile = "Curves\\C2.scr";


   //int offsetDist = 500;
   //String PolyFile = "Polys\\P4.scr";
   //String CurveFile = "Curves\\C2.scr";


   //int offsetDist = 1500;     //This is ok
   //String PolyFile = "Polys\\P4.scr";
   //String CurveFile = "Curves\\C5.scr";

   //int offsetDist = 500;     //This is ok
   //String PolyFile = "Polys\\P5.scr";
   //String CurveFile = "Curves\\C5.scr";

   //int offsetDist = 1500;  // missing curve in extraNewCurves  <<<<************************
   //String PolyFile = "Polys\\P4.scr";
   //String CurveFile = "Curves\\Curve_j.scr";


   //int offsetDist = 500;
   //String PolyFile = "Polys\\P2.scr";
   //String CurveFile = "Curves\\C2.scr";


   //int offsetDist = 1500;       //this is ok
   //String PolyFile = "Polys\\P1.scr";
   //String CurveFile = "Curves\\C1-3.scr";

   //int offsetDist = 1500;     //This is ok
   //String PolyFile = "Polys\\P3.scr";
   //String CurveFile = "Curves\\C3.scr";

   //int offsetDist = 700;   //This is ok
   //String PolyFile = "Polys\\P4.scr";
   //String CurveFile = "Curves\\C4.scr";

   //int offsetDist = 1500;   //This is ok
   //String PolyFile = "Polys\\P6.scr";
   //String CurveFile = "Curves\\C6.scr";



   //int offsetDist =  200;   //This is ok
   //String PolyFile = "Polys\\P6.scr";
   //String CurveFile = "Curves\\C6-1.scr";

   //int offsetDist = 1500;   //This is ok
   //String PolyFile = "Polys\\P7.scr";
   //String CurveFile = "Curves\\C7.scr";

   //int offsetDist = 1500;
   //String PolyFile = "Polys\\P7.scr";
   //String CurveFile = "Curves\\C7-1.scr";

   //int offsetDist = 500;   //This is ok
   //String PolyFile = "Polys\\P7.scr";
   //String CurveFile = "Curves\\C7-2.scr";

   //int offsetDist = 1500;   //This is ok
   //String PolyFile = "Polys\\P8.scr";
   //String CurveFile = "Curves\\C8.scr";

   //int offsetDist = 1500;   //This is ok
   //String PolyFile = "Polys\\p9.scr";
   //String CurveFile = "Curves\\C9.scr";

   //int offsetDist = 500;   //This is ok
   //String PolyFile = "Polys\\p10.scr";
   //String CurveFile = "Curves\\C10-1.scr";

   //int offsetDist = 1500;
   //String PolyFile = "Polys\\p11.scr";
   //String CurveFile = "Curves\\C11.scr";


   //int offsetDist = 600;
   //String PolyFile = "Polys\\P12.scr";
   //String CurveFile = "Curves\\C12.scr";


   //int offsetDist = 1500;
   //String PolyFile = "Polys\\P12-1.scr";
   //String CurveFile = "Curves\\C12-1.scr";


   //int offsetDist = 1500;
   //String PolyFile = "Polys\\P14.scr";
   //String CurveFile = "Curves\\C14.scr";

   //int offsetDist = 1200;
   //String PolyFile = "Polys\\P15.scr";
   //String CurveFile = "Curves\\C15.scr";


   //int offsetDist = 300;
   //String PolyFile = "Polys\\P16.scr";
   //String CurveFile = "Curves\\C16.scr";


   //int offsetDist = 800;
   //String PolyFile = "Polys\\P18.scr";
   //String CurveFile = "Curves\\C18.scr";


   //int offsetDist = 500;
   //String PolyFile = "Polys\\P20.scr";
   //String CurveFile = "Curves\\C20.scr";


   int offsetDist = 1000;
   String PolyFile = "Polys\\P21.scr";
   String CurveFile = "Curves\\C22.scr";



   //int offsetDist = 400;     //This is ok
   //String PolyFile = "Polys\\P17.scr";
   //String CurveFile = "Curves\\C17.scr";


   //int offsetDist = 1000;     //This is ok
   //String PolyFile = "Polys\\P21.scr";
   //String CurveFile = "Curves\\C21.scr";




   int rectMargin = 20000;
   int tatamiOffset = 10;
   int initialRunLen = 4000;
   int OffsetMeothode = 3;
   bool sharpCorners = false;


   if (tatamiOffset == 0)
     tatamiOffset = 1;




   TList* Curves = new TList();
   TList* Polygons = new TList();
   TList *newCurves = new TList();
   TList *extraNewCurves = new TList();


   if (!FileExists(PolyFile)){
       cout << PolyFile.c_str() << " does not exist!\n";
       int a;
       cin >> a;
       return(0);
   }
   if (!FileExists(CurveFile)){
       cout << CurveFile.c_str() << " does not exist!\n";
       int a;
       cin >> a;
       return(0);
   }

   ReadFromFile_2(PolyFile, Polygons, true);
   ReadFromFile_2(CurveFile, Curves, false);

   if (Polygons->Count == 0){
       cout << " Polygons is empty!\n";
       int a;
       cin >> a;
       return(0);
   }
   if (Curves->Count == 0){
       cout << " Curves is empty!\n";
       int a;
       cin >> a;
       return(0);
   }

   for (int i = 0; i < Polygons->Count; ++i)
     GetPolygonDirection((oneCurve*) Polygons->Items[i]);
   correctPolygonDirections(Polygons);


   fixSelfCuttingCurve_3((oneCurve*)Curves->First(), NULL);//, NULL, false);
   filterCurves((oneCurve*)Curves->First(), abs(offsetDist));
   extendCurve(Curves);



   getNewBoundRect(Polygons,rectMargin,Curves);
   do{
     if (! getCurveAndRectIntersection(Polygons, (oneCurve *)Curves->Last()))    break;
     if ( ! offsetCurve_3(Curves, (oneCurve *) Curves->Last(), offsetDist, extraNewCurves))
       break;
     writeOnePolygon("LastCurve.scr", (oneCurve *) Curves->Last());
   }while(true);


   //if(false)
   do{
     if (! offsetCurve_3(Curves, (oneCurve *) Curves->First(), -offsetDist, extraNewCurves)) break;
     if (! getCurveAndRectIntersection(Polygons, (oneCurve *)Curves->First()))
       break;
   }while(true);

   writePolygon("curves.scr", Curves);
   //writePolygon("curves_divided.scr", Curves, true);
   if(OffsetMeothode == 0){
     makeRunningBetweenTwoVertexes_before(Curves, initialRunLen, tatamiOffset, sharpCorners);
   }else if(OffsetMeothode == 1){
     makeRunningBetweenTwoVertexes_after(Curves, initialRunLen, tatamiOffset, sharpCorners);
   //}else if(OffsetMeothode == 2){
     //makeRunningBetweenTwoVertexes(Curves, initialRunLen, tatamiOffset, sharpCorners);    //the same result with OffsetMeothode == 0;
   }else if(OffsetMeothode == 3){
     makeRunningBetweenTwoVertexes_random(Curves, initialRunLen, tatamiOffset, sharpCorners);          //add random 2022-10-10
   }

   writePolygon("curves_2.scr", Curves);
   for(int i = 0;i<Curves->Count;++i){
     getCurveAndPolygonIntersection(Polygons, (oneCurve *)Curves->Items[i], newCurves);
   };
   writePolygon("curves_divided3.scr", newCurves, true);

   //writePolygon("extraNewCurves.scr", extraNewCurves);
   writePolygon("AllnewCurves.scr", newCurves);
   //writePolygon("AllnewCurves_divided.scr", newCurves);
   for (int i = 0; i < extraNewCurves->Count; ++i){
      oneCurve *holePoly = (oneCurve*) extraNewCurves->Items[i];
      GetPolygonDirection(holePoly);
      Curves->Add(holePoly);
      int curIndex = Curves->Count-1;
      for (int j = curIndex; j < Curves->Count; ++j){
        oneCurve *Poly = (oneCurve*) Curves->Items[j];
        getClosed_Curve_AndPolygonIntersection(Polygons, Poly, newCurves);
        if (!offset_Closed_Curve(Curves, Poly, offsetDist, extraNewCurves))
          break;
      }
   }


   writePolygon("AllCurves.scr", Curves);
   setPolygonsNextPrevVertexes(Polygons);
   writePolygon("AllnewCurves.scr", newCurves);
   setCurvesNextPrevCurves(newCurves, Polygons);

   //writeInfoForPolygon("Polygons_Info.scr", Polygons);
   //writeInfoForCurve("Curves_Info.scr", newCurves);

   //Setting Polygon Indexes inside Verte3xes for Curves
   for (int i = 0; i < Polygons->Count;  ++i){
     oneCurve *poly = (oneCurve *) Polygons->Items[i];
     for (int j = 0; j < poly->Count; ++j){
        ver = (Vertex *) poly->Items[j];
        if (ver->curveVertex == NULL)
          continue;
        ver->curveVertex->PolyVerIndex = j;
     }
   }

   extraNewCurves->Clear() ;
   for (int n = newCurves->Count-1 ; n >= 0; --n)
   {
      oneCurve *Poly = (oneCurve*) newCurves->Items[n];
      if ( Poly->NotConnectedToBoundry){ // (Poly->startPolyIndex == -1) || (Poly->endPolyIndex == -1) ){
        extraNewCurves->Insert(0, Poly);
        newCurves->Remove(Poly);
      }
   }


   writePolygon("AllnewCurves.scr", newCurves);
   writePolygon("extraNewCurves.scr", extraNewCurves);


   //writeInfoForPolygon("Polygons_Info.scr", Polygons);
   //writeInfoForCurve("Curves_Info.scr", newCurves);
   //writeInfoForCurve("extraCurves_Info.scr", extraNewCurves);


   TList *newCurvesCopy = new TList();
   for (int i = 0; i < newCurves->Count; ++i)
     newCurvesCopy->Add(newCurves->Items[i]);

   TList *allObjGroups = new TList();
   oneCurve *Poly;

   while(newCurves->Count > 0){
     bool goForward = true;
     for (int i = 0; i < newCurves->Count; ++i){
       Poly = (oneCurve *) newCurves->Items[i];
       ver = (Vertex*)Poly->First();
       if (ver->PolyIndex != 0){
         ver = (Vertex*)Poly->Last();
         if (ver->PolyIndex == 0)
           goForward = false;
       }
       else{
         goForward = true;
         break;
       }
     }
     newCurves->Remove(Poly);

     TList *oneGroup = new TList();
     oneGroup->Add(Poly);
     Poly->visited = true;
     //writeOnePolygon("Poly.scr", Poly);
     allObjGroups->Add(oneGroup);

     traverseOneGroup(newCurves, oneGroup, Poly, goForward /*Forward*/);
     //write_allObjGroups_connected("allObjGroups.scr", allObjGroups);
     traverseOneGroup(newCurves, oneGroup, Poly, !goForward);
     //write_allObjGroups_connected("allObjGroups.scr", allObjGroups);
     //reverseOneGroup(oneGroup);

   }

   //for (int i = 0; i < newCurves->Count; ++i){
   //  writeInfoOfCurve_LeftRightLists("Curve_Connection_" + IntToStr(i) + ".scr", (oneCurve *)newCurves->Items[i] );
   //}


   //Sort from Biggest to smallest
   for (int i = 0; i < allObjGroups->Count-1; ++i)
     for (int j = i+1; j < allObjGroups->Count; ++j)
       if ( ((TList*) allObjGroups->Items[i])->Count < ((TList*) allObjGroups->Items[j])->Count)
         allObjGroups->Exchange(i, j);

  /*   cout << "Object Groups Count: \n";
   for (int i = 0; i < allObjGroups->Count-1; ++i)
     cout << IntToStr(((TList*) allObjGroups->Items[i])->Count).c_str() << "\n";
   */


   for (int i = 0; i < allObjGroups->Count; ++i){
     TList *oneGroup = (TList*) allObjGroups->Items[i];
     //write_oneGroup("Group_" + IntToStr(i) + ".scr", oneGroup);
   }



   write_allObjGroups_connected("allObjGroups_beforeJOIN.scr", allObjGroups);

   /*for (int i = 0; i < allObjGroups->Count-1; ++i){
     TList *oneGroup = (TList*) allObjGroups->Items[i];
     for (int j = 0; j < oneGroup->Count; ++j){
       oneCurve * aCurve = (oneCurve*) oneGroup->Items[j];
       writeInfoOfCurve_LeftRightLists("Curve_Conn_" +  IntToStr(i) + "_" + IntToStr(j) +  "_.scr", aCurve );
     }
   }*/


   JoinGroups(Polygons, allObjGroups);
   clearZeroLenGroups(allObjGroups);

   write_allObjGroups_connected("allObjGroups_afterJOIN.scr", allObjGroups);

   //ssssssssssssssssssssssssssssssss
   //one curve in the group has a problem with ConnectedNext and ConnectedPrev (are equal, while should not)


   /*for (int i = 0; i < allObjGroups->Count-1; ++i){
     TList *oneGroup = (TList*) allObjGroups->Items[i];
     for (int j = 0; j < oneGroup->Count; ++j){
       oneCurve * aCurve = (oneCurve*) oneGroup->Items[j];
       writeInfoOfCurve_LeftRightLists("Curve_Conn_" +  IntToStr(i) + "_" + IntToStr(j) +  "_.scr", aCurve );
     }
   }
   */


   InsertaGroupWhereStartEndAreNotOnFirstPolygonAndCloseToAnotherGroup(Polygons, allObjGroups);
   write_allObjGroups_connected("allObjGroups_afterInsert_1.scr", allObjGroups);

   InsertinnerGroupsToOutterGroups(Polygons, allObjGroups);

   write_allObjGroups_connected("allObjGroups_afterInsert_2.scr", allObjGroups);

   if (Join_Stupid_Groups(Polygons, allObjGroups))
      InsertaGroupWhereStartEndAreNotOnFirstPolygonAndCloseToAnotherGroup(Polygons, allObjGroups);

   write_allObjGroups_connected("allObjGroups_afterInsert_3.scr", allObjGroups);
   clearZeroLenGroups(allObjGroups);

   Join_Groups_where_Start_End_Is_Located_On_oneHand_Of_a_Curve(allObjGroups);
   clearZeroLenGroups(allObjGroups);
   write_allObjGroups_connected("allObjGroups_afterInsert_4.scr", allObjGroups);

   Join_Final_Good_Groups(Polygons, allObjGroups);
   clearZeroLenGroups(allObjGroups);
   write_allObjGroups_connected("allObjGroups_afterInsert_5.scr", allObjGroups);


   for (int i = 0; i < allObjGroups->Count; ++i)  
     delete ((TList *) allObjGroups->Items[i]);
   delete allObjGroups;

   FreePolygon(Curves);
   FreePolygon(Polygons);
   FreePolygon(newCurves);
   //delete newCurves;
   FreePolygon(newCurvesCopy);
   FreePolygon(extraNewCurves);

   return 0;
}

//---------------------------------------------------------------------------


int main_2022_10_11_onePoly_spiral(int argc, char* argv[])
//int main(int argc, char* argv[])
{
  String PolyFile = "Polys\\P17.scr";
  //String PolyFile = "Polys\\P2.scr";

  TList* Polygons = new TList();



  if (!FileExists(PolyFile)){
    cout << PolyFile.c_str() << " does not exist!\n";
    int a;
    cin >> a;
    return(0);
  }

  ReadFromFile_2(PolyFile, Polygons, true);

  if (Polygons->Count == 0){
    cout << " Polygons is empty!\n";
    int a;
    cin >> a;
    return(0);
  }

  for (int i = 0; i < Polygons->Count; ++i)
    GetPolygonDirection((oneCurve*) Polygons->Items[i]);
  correctPolygonDirections(Polygons);

  writePolygon("AllPolygons.scr", Polygons);
  TList *curveList = new TList();
  oneCurve *poly1 = (oneCurve*) Polygons->First();
  oneCurve *poly2 = new oneCurve();

  Vertex *vf, *vl;
  vf = (Vertex *)poly1->First();
  vl = (Vertex *)poly1->Last();
  if (!samePoint(vf->po,vl->po)){
    poly1->Add(new Vertex(vf->po,0,-1,-1));
  }


  int minX = 0;
  int minY = 0;
  int maxX = 0;
  int maxY = 0;
  TPoint cen, newCenter = Point(0,0);
  double RotateAngle = 0 ;
  double scaleX = 0.5;
  double scaleY = 0;
  int spacing = 8000;
  int step = spacing/2;

  writeOnePolygon("poly.scr", poly1);

  for(int i = 0; i< poly1->Count; ++i){
    Vertex *ver = (Vertex *)poly1->Items[i];
    if(i == 0){
       minX = ver->po.x;
       minY = ver->po.y;
       maxX = ver->po.x;
       maxY = ver->po.y;
    }
    if(minX > ver->po.x){
      minX = ver->po.x;
    }
    if(minY > ver ->po.y){
      minY = ver->po.y;
    }
    if(maxX < ver->po.x){
      maxX = ver->po.x;
    }
    if(maxY < ver->po.y){
      maxY = ver->po.y;
    }
  };

  cen.x = (maxX-minX)/2 + minX;
  cen.y = (maxY-minY)/2 + minY;

  newCenter.x += cen.x;
  newCenter.y += cen.y;


 for(int i = 0; i < poly1->Count; ++i){
    Vertex *ver = (Vertex *)poly1->Items[i];
    Vertex *newVer = new Vertex(ver->po, 0, -1, -1);
    //newVer->po.x = (newVer->po.x-cen.x)*scaleX+cen.x+(newCenter.x-cen.x);
    //newVer->po.y = (newVer->po.y-cen.y)*scaleY+cen.y+(newCenter.y-cen.y);
    TPoint p;
    newVer->po.x = (newVer->po.x-cen.x)*scaleX;
    newVer->po.y = (newVer->po.y-cen.y)*scaleY;
    if (RotateAngle != 0){
      p.x = newVer->po.x * cos(RotateAngle) - newVer->po.y * sin(RotateAngle);
      p.y = newVer->po.x * sin(RotateAngle) + newVer->po.y * cos(RotateAngle);
      newVer->po = p;
    }

    newVer->po.x += cen.x+(newCenter.x-cen.x);
    newVer->po.y += cen.y+(newCenter.y-cen.y);


    poly2->Add(newVer);
  }
  writeOnePolygon("newPoly.scr", poly2);

  TList *allLines = new TList();
  for(int i = 0; i < poly1->Count; ++i){
    Vertex *P1 = (Vertex *)poly1->Items[i];
    Vertex *P2 = (Vertex *)poly2->Items[i];
    oneLine *aLine = new oneLine(P1->po, P2->po, Distance(P1->po, P2->po));
    aLine->dxy = Point(aLine->p2.x - aLine->p1.x, aLine->p2.y - aLine->p1.y);
    allLines->Add(aLine);
  }
  writeLines("allLines.scr",allLines);

  int longestL = 0;
  for(int i = 0; i < allLines->Count; ++i){
      oneLine *aLine = (oneLine *)allLines->Items[i];
      if(aLine->len > longestL){
        longestL = aLine->len;
      }
  }
  int stepCount = longestL/step+1;

  for(int i = 0; i <= stepCount; ++i ){
      oneLine *aLine = (oneLine *)allLines->Items[i];
      aLine->stepLen = aLine->len / stepCount;
      aLine->oneStepXY.x = aLine->dxy.x / stepCount;
      aLine->oneStepXY.y = aLine->dxy.y / stepCount;
  }
  oneCurve *newCurve = new oneCurve();
  int count =allLines->Count-1;
  for (int rev = 0; rev < stepCount; ++rev){
    for (int i = 0; i < allLines->Count; ++i){
      oneLine *aLine = (oneLine *)allLines->Items[i];
      int dx = aLine->p2.x - aLine->p1.x;
      int dy = aLine->p2.y - aLine->p1.y;
      TPoint p;

      if (rev > 0){
        p.x = aLine->p1.x + dx * ((float)rev / stepCount);
        p.y = aLine->p1.y + dy * ((float)rev / stepCount);
      }
      else
        p = aLine->p1;

      float sc = ((float)i / count)/stepCount;
      p.x = p.x + aLine->dxy.x * sc;
      p.y = p.y + aLine->dxy.y * sc;

      Vertex *ver = new Vertex();
      ver->po = p;
      newCurve->Add(ver);
    }
  }

  writeOnePolygon("newCurve.scr" , newCurve);

  deleteLines(allLines);

  FreePolygon(Polygons);
  FreeOnePoly(poly2);
  return 0;
}


main_2022_10_11_twoPoly_spiral(int argc, char* argv[])
//main(int argc, char* argv[])
{
  //String PolyFile = "Polys\\2Polys.scr";

  String PolyFile = "Polys\\2Polys-3.scr";

  //String PolyFile = "Polys\\2Polys-4.scr";

  //String PolyFile = "Polys\\2Polys-5.scr";

  //String PolyFile = "Polys\\2Polys-6.scr";

  //String PolyFile = "Polys\\2Polys-7.scr";

  //String PolyFile = "Polys\\2Polys-8.scr";

  //String PolyFile = "Polys\\2Polys-9.scr";

  //String PolyFile = "Polys\\2Polys-test.scr";

  TList* Polygons = new TList();



  if (!FileExists(PolyFile)){
    cout << PolyFile.c_str() << " does not exist!\n";
    int a;
    cin >> a;
    return(0);
  }

  ReadFromFile_2(PolyFile, Polygons, true);

  if (Polygons->Count < 2){
    cout << " Polygons is less than 2!\n";
    int a;
    cin >> a;
    return(0);
  }

  for (int i = 0; i < Polygons->Count; ++i)
    GetPolygonDirection((oneCurve*) Polygons->Items[i]);
  makeAllPolygonDirectionsSame(Polygons);
  writePolygon("AllPolygons.scr", Polygons);


  oneCurve *poly1 = (oneCurve*) Polygons->First();
  oneCurve *poly2 = (oneCurve*) Polygons->Items[1];
  /*Vertex *vf, *vl;
  vf = (Vertex *)poly1->First();
  vl = (Vertex *)poly1->Last();
  if (!samePoint(vf->po,vl->po)){
    poly1->Add(new Vertex(vf->po,0,-1,-1));
  }
  vf = (Vertex *)poly2->First();
  vl = (Vertex *)poly2->Last();
  if (!samePoint(vf->po,vl->po)){
    poly2->Add(new Vertex(vf->po,0,-1,-1));
  }
 */
  writeOnePolygon("poly1.scr" , poly1);
  writeOnePolygon("poly2.scr" , poly2);
  int poly1len = 0,poly2len = 0;

  int runLen = 4000;
  int spacing = 4000;
  int step = spacing/2;
  Vertex *v1, *v2;


  oneCurve *newRunList  = new oneCurve();
  double Len;
  TPoint P1,P2,PR;
  int runCount = 0;
  for(int i = 0; i < poly1->Count-1; ++i){
     Vertex *v1 = (Vertex *)poly1->Items[i];
     Vertex *v2 = (Vertex *)poly1->Items[i+1];
      poly1len += Distance(v1->po,v2->po);
  }
  for(int i = 0; i < poly2->Count-1; ++i){
     Vertex *v1 = (Vertex *)poly2->Items[i];
     Vertex *v2 = (Vertex *)poly2->Items[i+1];
      poly2len += Distance(v1->po,v2->po);
  }

  if(poly1len > poly2len){
    runCount = poly1len/runLen;
  }else{
    runCount = poly2len/runLen;
  }


  for(int i = 0; i < Polygons->Count; ++i){
    int polylen = 0;;
    oneCurve *poly = (oneCurve*) Polygons->Items[i];
    for(int i = 0; i < poly->Count-1; ++i){
     Vertex *v1 = (Vertex *)poly->Items[i];
     Vertex *v2 = (Vertex *)poly->Items[i+1];
      polylen += Distance(v1->po,v2->po);
    }
    v1 = (Vertex *) poly->First();
    v2 = (Vertex *) poly->Last();
    Vertex *v = v1;
    Len = polylen/runCount;
    newRunList->Add(new Vertex(v1->po, 0, -1, -1));
    Vertex *Data1 = v1, *lastData = v1;
    Vertex *Data2;
    P1.x = PR.x = Data1->po.x;
    P1.y = PR.y = Data1->po.y;
    int lastVerIndex = 0;
    double a;
    double rdist = 0;
    double ang1;
    for(int i=0;i<poly->Count-1;++i){
      Data2 = (Vertex *)poly->Items[i+1];
      Data1->nextVer = Data2;
      Data2->prevVer = Data1;
      P2 = Data2->po;
      a = Len-rdist;
      rdist += Distance(P1, P2);
      ang1 = getAngle(P1, P2);
      while( rdist > Len+5)
      { PR.x = P1.x + a * cos(ang1);
        PR.y = P1.y + a * sin(ang1);
        newRunList->Add(new Vertex(PR, 0, -1, -1));
        a += Len;
        rdist -= Len;
        lastData = Data1;
        if (rdist < Len+5)
          lastVerIndex = i;
      }
      P1 = P2;
      Data1 = Data2;

    }
    poly->DeleteAll();
    for(int j = 0; j < newRunList->Count; ++j){
      poly->Add(newRunList->Items[j]);
    }
    newRunList->Clear();

  }
   writePolygon("AllPolygons.scr", Polygons);
  poly1 = (oneCurve*) Polygons->First();
  poly2 = (oneCurve*) Polygons->Items[1];
  TList *allLines = new TList();
  for(int i = 0; i < poly1->Count; ++i){
    Vertex *P1 = (Vertex *)poly1->Items[i];
    Vertex *P2 = (Vertex *)poly2->Items[i];
    oneLine *aLine = new oneLine(P1->po, P2->po, Distance(P1->po, P2->po));
    aLine->dxy = Point(aLine->p2.x - aLine->p1.x, aLine->p2.y - aLine->p1.y);
    allLines->Add(aLine);
  }
  writeLines("allLines.scr",allLines);

  int longestL = 0;

  for(int i = 0; i < allLines->Count; ++i){
      oneLine *aLine = (oneLine *)allLines->Items[i];
      if(aLine->len > longestL){
        longestL = aLine->len;
      }
  }
  int stepCount = longestL/step+1;
  for(int i = 0; i <= stepCount; ++i ){
      oneLine *aLine = (oneLine *)allLines->Items[i];
      aLine->stepLen = aLine->len / stepCount;
  }


  oneCurve *newCurve1 = new oneCurve();

  for (int rev = 0; rev < stepCount; ++rev){
    for (int i = 0; i < allLines->Count; ++i){
      oneLine *aLine = (oneLine *)allLines->Items[i];
      int dx = aLine->p2.x - aLine->p1.x;
      int dy = aLine->p2.y - aLine->p1.y;
      TPoint p;

      if (rev > 0){
        p.x = aLine->p1.x + dx * ((float)rev / stepCount);
        p.y = aLine->p1.y + dy * ((float)rev / stepCount);
      }
      else {
        p = aLine->p1;
      }
      float sc = ((float)i / (allLines->Count-1))/stepCount;
      p.x = p.x + aLine->dxy.x * sc;
      p.y = p.y + aLine->dxy.y * sc;

      Vertex *ver = new Vertex();
      ver->po = p;
      newCurve1->Add(ver);
    }
  }

  writeOnePolygon("newCurve.scr" , newCurve1);

  delete newRunList;
  deleteLines(allLines);

}


main_2022_10_11_ComntourTatami_UsingTwoCurves(int argc, char* argv[])     //(int argc, char* argv[])
//int main(int argc, char* argv[])
{


   Vertex *ver = NULL;

   //int density = 2000;     //This is ok
   String PolyFile = "Polys\\2OpenPoly-1.scr";
   //String CurveFile = "Curves\\C17.scr";

   int density = 3000;     //This is ok
   //String PolyFile = "Polys\\P_20.scr";

   int runLength = 2000;
   int mindist = 1000;
   int tatamiOffset = 10;
   
   int OffsetMeothode = 2;  //0---hasAverageLen == true ,1---hasAverageLen == false ,2---freedom
   bool sharpCorners = false;


   TList* Curves = new TList();
   TList* Polygons = new TList();
   TList *newCurves = new TList();

   if (!FileExists(PolyFile)){
       cout << PolyFile.c_str() << " does not exist!\n";
       int a;
       cin >> a;
       return(0);
   }

   ReadFromFile_2(PolyFile, Polygons, true);

   if (Polygons->Count == 0){
       cout << " Polygons is empty!\n";
       int a;
       cin >> a;
       return(0);
   }

   for (int i = 0; i < Polygons->Count; ++i)
     GetPolygonDirection((oneCurve*) Polygons->Items[i]);

   writePolygon("AllPolygons.scr", Polygons);

  oneCurve *poly1 = (oneCurve*) Polygons->First();
  oneCurve *poly2 = (oneCurve*) Polygons->Items[1];
  writeOnePolygon("poly1.scr" , poly1);
  writeOnePolygon("poly2.scr" , poly2);
  int poly1len = 0,poly2len = 0;


  Vertex *v1, *v2;


  oneCurve *newRunList  = new oneCurve();
  double Len;
  TPoint P1,P2,PR;
  int runCount = 0;
  for(int i = 0; i < poly1->Count-1; ++i){
     Vertex *v1 = (Vertex *)poly1->Items[i];
     Vertex *v2 = (Vertex *)poly1->Items[i+1];
      poly1len += Distance(v1->po,v2->po);
  }
  for(int i = 0; i < poly2->Count-1; ++i){
     Vertex *v1 = (Vertex *)poly2->Items[i];
     Vertex *v2 = (Vertex *)poly2->Items[i+1];
      poly2len += Distance(v1->po,v2->po);
  }

  if(poly1len > poly2len){
    runCount = poly1len/runLength;
  }else{
    runCount = poly2len/runLength;
  }


  for(int i = 0; i < Polygons->Count; ++i){
    int polylen = 0;;
    oneCurve *poly = (oneCurve*) Polygons->Items[i];
    for(int i = 0; i < poly->Count-1; ++i){
     Vertex *v1 = (Vertex *)poly->Items[i];
     Vertex *v2 = (Vertex *)poly->Items[i+1];
      polylen += Distance(v1->po,v2->po);
    }
    v1 = (Vertex *) poly->First();
    v2 = (Vertex *) poly->Last();
    Vertex *v = v1;
    Len = polylen/runCount;
    newRunList->Add(new Vertex(v1->po, 0, -1, -1));
    Vertex *Data1 = v1, *lastData = v1;
    Vertex *Data2;
    P1.x = PR.x = Data1->po.x;
    P1.y = PR.y = Data1->po.y;
    int lastVerIndex = 0;
    double a;
    double rdist = 0;
    double ang1;
    for(int i=0;i<poly->Count-1;++i){
      Data2 = (Vertex *)poly->Items[i+1];
      Data1->nextVer = Data2;
      Data2->prevVer = Data1;
      P2 = Data2->po;
      a = Len-rdist;
      rdist += Distance(P1, P2);
      ang1 = getAngle(P1, P2);
      while( rdist > Len+5)
      { PR.x = P1.x + a * cos(ang1);
        PR.y = P1.y + a * sin(ang1);
        newRunList->Add(new Vertex(PR, 0, -1, -1));
        a += Len;
        rdist -= Len;
        lastData = Data1;
        if (rdist < Len+5)
          lastVerIndex = i;
      }
      P1 = P2;
      Data1 = Data2;

    }
    poly->DeleteAll();
    for(int j = 0; j < newRunList->Count; ++j){
      poly->Add(newRunList->Items[j]);
    }
    newRunList->Clear();

  }
   writePolygon("AllPolygons.scr", Polygons);

   makeRunningWithOpenPoly(Polygons, Curves, density, runLength, tatamiOffset,OffsetMeothode);
   //filterCurve_StartEnds(Curves,density*0.2);
   writePolygon("Curves1.scr", Curves);

   writePolygon("curves_2.scr", Curves);

   oneCurve *joinedCurve = correctEndsForNearPoints(Curves, mindist);

   delete joinedCurve;

   writePolygon("Curves.scr", Curves);

   FreePolygon(Polygons);
   FreePolygon(Curves);

   return 0;

}

TList *addCircleNeighbours(TList *Polygons , TList *Circles, oneCircle *aCircle, int rc[6][2])
{

  int newR, newC;
  for (int i = 0; i < 6; ++i){
     newR = aCircle->Row + rc[i][0];
     if ( (newR < 0) || (newR >= Circles->Count)){
       aCircle->isAtEdge = true;
       aCircle->connections->Add(NULL);
       //aCircle->neighboursStatus = 1;
       continue;
     }
     TList *newColList = (TList*) Circles->Items[newR];
     newC = aCircle->Col + rc[i][1];
     if ((newC < 0) || (newC >=  newColList->Count)){
       aCircle->isAtEdge = true;
       aCircle->connections->Add(NULL);
       //aCircle->neighboursStatus = 1;
       continue;
     }
     if (newColList->Items[newC] != NULL){
        aCircle->connections->Add(newColList->Items[newC]);
        aCircle->Neighborhood->Add(newColList->Items[newC]);
        //aCircle->neighboursStatus = 0;

     }
     else{
       aCircle->connections->Add(NULL);
       aCircle->isAtEdge = true;
       //aCircle->neighboursStatus = 1;
      }
  }
}


void traverseOneCircle(TList *Polygons,TList *AllPaths, TList *aPath, oneCircle *aCircle)
{
  int a = 0,b = 0;
  bool found = false;
  oneCircle *lastVisited = NULL;
  oneCircle *nextCircle = NULL;
  //if (aCircle->po.x == 416023 && aCircle->po.y == 317303)
     //cout << aCircle->po.x << "," << aCircle->po.y << "\n";
  int start = 0;
  for(int i = 0; i < aCircle->connections->Count; ++i){
    if (aCircle->connections->Items[i] == NULL){
        start = i;
        cout << aCircle->po.x << "," << aCircle->po.y << "\n";
        break;
    }
    else if (aPath->Count > 1) {
       oneCircle *checkCircle = (oneCircle*)aCircle->connections->Items[i];
       if ( checkCircle == (oneCircle *)aPath->Items[aPath->Count-2]){
         start = i;
         cout << aCircle->po.x << "," << aCircle->po.y << "\n";
         break;
       }
       //cout << checkCircle->po.x << "," << checkCircle->po.y << "\n";
    }
  }
  /*if(!aCircle->hasAnyFreeConnection()){
    for(int i = 0 ; i < 6 ; i++){
      if (aCircle->connections->Items[i] == NULL) continue;
       nextCircle = (oneCircle*)aCircle->connections->Items[i];
       if(nextCircle->visited){
          break;
       }
    }
  }  */
  int c = 0;
  for (int i = 0; i < 6; ++i){

     ++start;
     if (start >= 6)
        start = 0;

     if (aCircle->connections->Items[start] == NULL) continue;

     nextCircle = (oneCircle*)aCircle->connections->Items[start];
     if(nextCircle->visited == true){
        ++c;
     }
     if(aPath->Count>2){
       if(aPath->IndexOf(nextCircle) == 0){
         return;
       }
     }
     if (nextCircle->visited ) continue;
     if (nextCircle->isAtEdge == false)continue;
     bool isAvailableInFormerPaths = false;
     for (int n = 0; n < AllPaths->Count; ++n){
       TList *pPath = (TList*) AllPaths->Items[n];
       if (pPath == aPath) continue;
       if (pPath->IndexOf(nextCircle) != -1){
         nextCircle = NULL;
         isAvailableInFormerPaths = true;
         break;
       }
     }
     if (isAvailableInFormerPaths) continue;
     break;
  }

  if(c>1 && !aCircle->hasAnyFreeConnection()){
     for(int i = 0 ; i < 6 ; i++){
      if (aCircle->connections->Items[i] == NULL) continue;
       nextCircle = (oneCircle*)aCircle->connections->Items[i];
       if(nextCircle->visited ){
          break;
       }
    }
  }
  /*int acheck = 0;
  for ( int i = 0; i < 6 ; i++ ){
    if(aCircle->connections->Items[i] == NULL) continue;
    oneCircle *ac = (oneCircle*)aCircle->connections->Items[i];
    if(ac->visited){
      ++acheck;
    }
  }
  if(acheck >2) return;  */
  /*if(!aCircle->hasAnyFreeConnection()){
    for(int i = 0 ; i < 6 ; i++){
      if (aCircle->connections->Items[i] == NULL) continue;
       nextCircle = (oneCircle*)aCircle->connections->Items[i];
       if(nextCircle->visited){
          break;
       }
    }
  }
  */

  writePaths("test.scr", AllPaths);
  if ( nextCircle == NULL) return;


  else if (nextCircle->visited){
    int ndx = aPath->IndexOf(nextCircle);
    if (ndx <= 0){
         bool checkshow = false;
         for(int i = aPath->Count-1; i>=0; --i){
           oneCircle *checkCircle = (oneCircle *) aPath->Items[i];
           for(int j = 0 ; j < 6 ; j++){
               if(checkCircle->connections->Items[j] == NULL) continue;
               oneCircle *checkcon = (oneCircle *)checkCircle->connections->Items[j];
               if(checkcon->visited == false && checkcon->isAtEdge == true){
                     checkshow = true;
                     break;
               }
           }
         }
         if(checkshow == false) return;
         if(checkshow == true){
           for (int m = 0; m < aPath->Count/2; ++m)
             aPath->Exchange(m, aPath->Count-1-m);
           nextCircle = (oneCircle*)aPath->Last();
           traverseOneCircle(Polygons,AllPaths, aPath, nextCircle);
         }
    }else if ( ndx == aPath->Count-2){
       bool hasAnotherWay = false;
       for (int i = aPath->Count-2; i >=0; --i){
         oneCircle *checkCircle = (oneCircle*)aPath->Items[i];
         if (checkCircle->hasAnyFreeConnection()){
           hasAnotherWay = true;
           nextCircle = checkCircle;
           aCircle = (oneCircle*)aPath->Items[i+1];
           TList *newPath = new TList();
           AllPaths->Add(newPath);
           for (int j = aPath->Count-1; j > i; --j){
             newPath->Add(aPath->Last());
             aPath->Delete(aPath->Count-1);
             //nextCircle = aCircle;
           }
           nextCircle->connections->Items[ nextCircle->connections->IndexOf(aCircle)] = NULL;
           aCircle->connections->Items[ aCircle->connections->IndexOf(nextCircle)] = NULL;
           break;
         }

       }
       if (!hasAnotherWay)
          return;
       else
          traverseOneCircle(Polygons,AllPaths, aPath, nextCircle);
       /*

       //if (nextCircle->po.x == 413773 && nextCircle->po.y == 321200 ){
         //return;
       //}else{


       bool show = false;
       for(int i = 0; i <  aPath->Count; ++i){
            oneCircle *checkCircle = (oneCircle*)aPath->Items[i];
            if(checkCircle->hasAnyFreeConnection()){
            }

       }
       nextCircle->connections->Items[ nextCircle->connections->IndexOf(aCircle)] = NULL;
       aCircle->connections->Items[ aCircle->connections->IndexOf(nextCircle)] = NULL;
       //aPath->Remove(aCircle);
       aPath->Delete(aPath->IndexOf(aCircle));
       aCircle->visited = false;
       traverseOneCircle(Polygons,AllPaths, aPath, nextCircle);
       //}else{
         //return;
       //}
       */
    }else{
      oneCircle *lastCircle = (oneCircle *) aPath->Items[ndx-1];
      if (lastCircle->hasAnyFreeConnection()){
        TList *newPath = new TList();
        AllPaths->Add(newPath);
        for (int i = aPath->Count-1; i >= ndx; --i){
          newPath->Add(aPath->Items[i]);
          aPath->Delete(i);
        }
        oneCircle *lastCircle = (oneCircle *) aPath->Last();
        lastCircle->connections->Items[ lastCircle->connections->IndexOf(nextCircle)] = NULL;
        traverseOneCircle(Polygons, AllPaths, aPath, lastCircle);
      }
      else{
        aCircle->connections->Items[ aCircle->connections->IndexOf(nextCircle)] = NULL;
        nextCircle->connections->Items[ nextCircle->connections->IndexOf(aCircle)] = NULL;
        //aPath->Remove(aCircle);
        aPath->Delete(aPath->IndexOf(aCircle));
        nextCircle = (oneCircle *)aPath->Last();
        nextCircle->connections->Items[ nextCircle->connections->IndexOf(aCircle)] = NULL;
        traverseOneCircle(Polygons, AllPaths, aPath, nextCircle);
      }
    }
  }
  else if (nextCircle != NULL){
    if(nextCircle->isAtEdge){
       aPath->Add(nextCircle);
       nextCircle->visited = true;

       traverseOneCircle(Polygons, AllPaths, aPath, nextCircle);
     }
  }

}



void detectCirclesAndNeighboursIntersectWithPolygons(TList *Circles, TList *Polygons)
{
  TPoint intNewpo;
  for(int n = 0 ; n < Circles->Count ; ++n){
        if(Circles->Items[n] == NULL) continue;
        oneCircle *aCircle = (oneCircle *)Circles->Items[n];
        for (int i = 0; i < 6; ++i){
          if (aCircle->connections->Items[i] == NULL) continue;
          oneCircle *c1 = (oneCircle *)aCircle->connections->Items[i];
          bool breakForLoop = false;
          for(int j = 0 ; j < Polygons->Count ; j++){
            if (breakForLoop) break;
            oneCurve *poly = (oneCurve*) Polygons->Items[j];
            Vertex *v1 = (Vertex *)poly->Last();
            for(int m = 0 ; m < poly->Count ; m++){
              Vertex *v2 = (Vertex *)poly->Items[m];
              if(GetIntersection(intNewpo,v1->po,v2->po,aCircle->po,c1->po,false)){
                aCircle->isAtEdge = true;
                c1->isAtEdge = true;
                aCircle->connections->Items[i] = NULL;
                aCircle->neighboursStatus = 1;
                c1->connections->Items[ c1->connections->IndexOf(aCircle) ] = NULL;
                breakForLoop = true;
                break;
              }
             v1 = v2;
            }
          }
        }
  }

  oneCircle *c1, *c2;
  for(int n = 0 ; n < Circles->Count ; ++n){
    oneCircle *aCircle = (oneCircle *)Circles->Items[n];
    if (aCircle->isAtEdge) continue;
    for (int i = 0; i < 6; ++i){
      c1 = (oneCircle *)aCircle->connections->Items[i];
      if (i < 5)
        c2 = (oneCircle *)aCircle->connections->Items[i+1];
      else
        c2 = (oneCircle *)aCircle->connections->First();
      if ( (c1->connections->IndexOf(c2) == -1) || (c2->connections->IndexOf(c1) == -1) ){
        aCircle->isAtEdge = true;
        break;
      }
    }
  }

}

//int main_2022_10_12(int argc, char* argv[])
int main_2022_10_14_JiaQi(int argc, char* argv[])
{
  //String PolyFile = "Polys\\2Polys-6.scr";
  String PolyFile = "Polys\\P8.scr";

  TList* Polygons = new TList();



  if (!FileExists(PolyFile)){
    cout << PolyFile.c_str() << " does not exist!\n";
    int a;
    cin >> a;
    return(0);
  }

  ReadFromFile_2(PolyFile, Polygons, true);

  if (Polygons->Count < 2){
    cout << " Polygons is less than 2!\n";
    int a;
    cin >> a;
    return(0);
  }

  //for (int i = 0; i < Polygons->Count; ++i)
  //  GetPolygonDirection((oneCurve*) Polygons->Items[i]);
  //makeAllPolygonDirectionsSame(Polygons);
  writePolygon("AllPolygons.scr", Polygons);


  oneCurve *poly1 = (oneCurve*) Polygons->First();
  int minX = 0;
  int minY = 0;
  int maxX = 0;
  int maxY = 0;
  for(int i = 0; i< poly1->Count; ++i){
    Vertex *ver = (Vertex *)poly1->Items[i];
    if(i == 0){
       minX = ver->po.x;
       minY = ver->po.y;
       maxX = ver->po.x;
       maxY = ver->po.y;
    }
    if(minX > ver->po.x){
      minX = ver->po.x;
    }
    if(minY > ver ->po.y){
      minY = ver->po.y;
    }
    if(maxX < ver->po.x){
      maxX = ver->po.x;
    }
    if(maxY < ver->po.y){
      maxY = ver->po.y;
    }
  };

  int circleAllLenX = maxX - minX;
  int circleAllLenY = maxY - minY;
  TPoint p1;
  int Radius = 2000;
  int dx = Radius *3;// 5000;
  int dy = dx * sqrt(3)/2;
  TList *Circles = new TList();
  for(int j = 0;j < circleAllLenY/dy+1; ++j ){
     TList *CircleCol = new TList();
     for(int i = 0; i < circleAllLenX/dx+1 ; ++i){
       if(j % 2 == 0){
         p1.x = minX + Radius + i * dx;
         p1.y = minY + Radius + j * dy;
       }else{
         p1.x = minX + Radius + i * dx + dx / 2;
         p1.y = minY + Radius + j * dy;
       }

       if (PointIn_Polygons(p1, Polygons))
          CircleCol->Add(new oneCircle(p1, Radius, j, i));
       else
          CircleCol->Add(NULL);

     }
     Circles->Add(CircleCol);
  }
  int rcEven[6][2] = { {1, -1} , {1, 0}, {0, -1}, {0, 1}, {-1, -1} , {-1, 0} }; // 0, 2, 4, 6
  int rcOdd[6][2] = { {1, 0} , {1, 1}, {0, -1}, {0, 1}, {-1, 0} , {-1, 1} }; // 1, 3, 5,

  for(int i = 0; i< Circles->Count; ++i){
     TList *aColList = (TList *)Circles->Items[i];
     for(int j = 0; j< aColList->Count; ++j){
         oneCircle *aCircle = (oneCircle *)aColList->Items[j];
         if(aCircle != NULL) {
            aCircle->connections = new TList();
            aCircle->Neighborhood = new TList();
            addCircleNeighbours(Polygons , Circles, aCircle, ((aCircle->Row %2) == 0)? rcEven : rcOdd);
          //  TList *findNList = findNeighbour(Circles, i, j);
         }
     }
  }



  writeCircles("circle3.scr",Circles);
/*
    TList *newCircles = new TList();
    for(int i = 0; i< Circles->Count; ++i){
      TList *aColList = (TList *)Circles->Items[i];
      aColList->Pack();
      for (int j = 0; j < aColList->Count; ++j){
         newCircles->Add(aColList->Items[j]);
      }
      aColList->Clear;
      delete aColList;
    }
    delete Circles;
*/


    TList *AllConnect = new TList();
    for(int i = 0; i< Circles->Count; ++i){
      TList *aColList = (TList *)Circles->Items[i];
      for(int j = 0; j< aColList->Count; ++j){
         oneCircle *aCircle = (oneCircle *)aColList->Items[j];
         if(i == 0){
           AllConnect->Add(aCircle);
         }else if(i == Circles->Count-1){
           aCircle = (oneCircle *)aColList->Items[aColList->Count-1-j];
           AllConnect->Add(aCircle);
         }else {
            if(j == aColList->Count-1){
               AllConnect->Add(aCircle);
            }

         }
      }
    }
    for(int i = Circles->Count-1; i>=0 ; i--){
      TList *aColList = (TList *)Circles->Items[i];
      for(int j = 0; j< aColList->Count; ++j){
         oneCircle *aCircle = (oneCircle *)aColList->Items[j];
         if(j == 0){
           AllConnect->Add(aCircle);
         }
      }
    }

    writeCircles_copy("circle5.scr",AllConnect);
     TList *AllConnectList = new TList();
     for(int j = 0; j< AllConnect->Count-2; j = j+2){
         oneCircle *aCircle = (oneCircle *)AllConnect->Items[j];
         TList *connectionsList =  aCircle->connections;
         TList *newConnect = new TList();
         for(int m = 0; m < connectionsList->Count; ++ m){
             oneCircle *cCircle = (oneCircle *)connectionsList->Items[m];
             if(cCircle->isAtEdge == false){
                newConnect->Add(cCircle);
             }
         }
         if(newConnect->Count <= 0) continue;
         int aa = random(newConnect->Count);

         oneCircle *bCircle = (oneCircle *)newConnect->Items[aa];
         bCircle->isAtEdge = true;
         AllConnectList->Add(bCircle);

     }
   writeCircles_copy("circle7.scr",AllConnectList);
  while(true){
    TList *AllConnectList2 = new TList();

    for(int j = 0; j< AllConnectList->Count; j = j+1){
         oneCircle *aCircle = (oneCircle *)AllConnectList->Items[j];
         if(aCircle->connections==NULL) continue;
         TList *connectionsList =  aCircle->connections;
         TList *newConnect = new TList();
         for(int m = 0; m < connectionsList->Count; ++ m){
             oneCircle *cCircle = (oneCircle *)connectionsList->Items[m];
             if(cCircle->isAtEdge == false){
                newConnect->Add(cCircle);
             }
         }
         if(newConnect->Count <= 0) continue;
         int aa = random(newConnect->Count);

         oneCircle *bCircle = (oneCircle *)newConnect->Items[aa];
         bCircle->isAtEdge = true;
         AllConnectList2->Add(bCircle);


    }
    AllConnectList->Clear();
    AllConnectList =  AllConnectList2;
    writeCircles_copy("circle6.scr",AllConnectList2);

    if(AllConnectList2->Count==0)
            break;
  }

  writeCircles("circle4.scr",Circles);

  //writeCircles_copy("circle6.scr",AllConnectList2);
  /*
  for(int j = 0;j < circleAllLenY/dy+1; ++j ){
     for(int i = 0; i < circleAllLenX/dx+1 ; ++i){
       if(j % 2 == 0){
         p1.x = minX + Radius + i * dx;
         p1.y = minY + Radius + j * dy;
       }else{
         p1.x = minX + Radius + i * dx + dx / 2;
         p1.y = minY + Radius + j * dy;
       }

       if (PointIn_Polygons(p1, Polygons))
       //if( minX + Radius + i * dx - dx / 2 < maxX && minY+Radius+j*(ang*Dis)<maxY){
          Circles->Add(new oneCircle(p1, Radius, j, i));
       //}

     }
  }

  writeCircles("circle.scr",Circles);
  TList *newCon = new TList();
  for(int i = 0; i < Circles->Count; ++i){
    oneCircle *aCircle = (oneCircle *)Circles->Items[i];
    TList *newList = new TList();
    for(int j = 0; j < Circles->Count; ++j){
       if(j == i) continue;
       oneCircle *bCircle = (oneCircle *)Circles->Items[j];
       int cDist = Distance(aCircle->po,bCircle->po);
       if(cDist <= dx+10 ){
           newList->Add(bCircle);
       }
    }
    aCircle->connections = newList;
    if(newList->Count < 6){
        newCon->Add(new oneCircle(aCircle->po,Radius));
    }
  }
  writeCircles("circle2.scr",newCon);
   */


  /*TList *Lines = new TList();
  for(int i = 0; i < newCon->Count-1; ++i){
      oneCircle *aCircle = (oneCircle *)Circles->Items[i];
      oneCircle *bCircle = (oneCircle *)Circles->Items[i+1];
      oneLine *newLine = new oneLine(aCircle->po,bCircle->po,Distance(aCircle->po,bCircle->po));
      Lines->Add(newLine);
      
  }
  writeLines("lines.scr",Lines);
  deleteLines(Lines);

  for(int i = 0; i<newCon->Count; ++i){
     oneCircle *aCircle = (oneCircle *)newCon->Items[i];
     delete aCircle;
  }
  delete newCon;
  */
  delete AllConnect;
  for(int i = 0; i< Circles->Count; ++i){
     TList *CircleCol = (TList *)Circles->Items[i];
     for(int j = 0; j< CircleCol->Count; ++j){
         if (CircleCol->Items[j] == NULL) continue;
         oneCircle *aCircle = (oneCircle *)CircleCol->Items[j];
         delete aCircle->connections;
         delete aCircle;
     }
     delete CircleCol;

  }
  delete Circles;



}



int main(int argc, char* argv[])
//int main_2022_10_15(int argc, char* argv[])
{
  //String PolyFile = "Polys\\2Polys-6.scr";
  //String PolyFile = "Polys\\P8.scr";


  String PolyFile = "Polys\\p1.scr";
  TList* Polygons = new TList();
  TPoint p1;

  int Radius = 1000;
  int dx = Radius *3;// 5000;
  int dy = dx * sqrt(3)/2;



  if (!FileExists(PolyFile)){
    cout << PolyFile.c_str() << " does not exist!\n";
    int a;
    cin >> a;
    return(0);
  }

  ReadFromFile_2(PolyFile, Polygons, true);

  //for (int i = 0; i < Polygons->Count; ++i)
  //  GetPolygonDirection((oneCurve*) Polygons->Items[i]);
  //makeAllPolygonDirectionsSame(Polygons);
  writePolygon("AllPolygons.scr", Polygons);


  oneCurve *poly1 = (oneCurve*) Polygons->First();
  int minX = 0;
  int minY = 0;
  int maxX = 0;
  int maxY = 0;
  for(int i = 0; i< poly1->Count; ++i){
    Vertex *ver = (Vertex *)poly1->Items[i];
    if(i == 0){
       minX = ver->po.x;
       minY = ver->po.y;
       maxX = ver->po.x;
       maxY = ver->po.y;
    }
    if(minX > ver->po.x){
      minX = ver->po.x;
    }
    if(minY > ver ->po.y){
      minY = ver->po.y;
    }
    if(maxX < ver->po.x){
      maxX = ver->po.x;
    }
    if(maxY < ver->po.y){
      maxY = ver->po.y;
    }
  };


  int dxx = ((maxX - minX) / dx) * dx;
  minX = minX + ((maxX - minX) - dxx ) / 2 - Radius;

  int dyy = ((maxY - minY) / dy) * dy;
  minY = minY + ((maxY - minY) - dyy ) / 2 - Radius;


  int circleAllLenX = maxX - minX;
  int circleAllLenY = maxY - minY;

  TList *Circles = new TList();
  for(int j = 0;j < circleAllLenY/dy+1; ++j ){
     TList *CircleCol = new TList();
     for(int i = 0; i < circleAllLenX/dx+1 ; ++i){
       if(j % 2 == 0){
         p1.x = minX + Radius + i * dx;
         p1.y = minY + Radius + j * dy;
       }else{
         p1.x = minX + Radius + i * dx + dx / 2;
         p1.y = minY + Radius + j * dy;
       }

       if (PointIn_Polygons(p1, Polygons))
          CircleCol->Add(new oneCircle(p1, Radius, j, i));
       else
          CircleCol->Add(NULL);

     }
     Circles->Add(CircleCol);
  }
  //int rcEven[6][2] = { {1, -1} , {1, 0}, {0, -1}, {0, 1}, {-1, -1} , {-1, 0} }; // 0, 2, 4, 6
  //int rcOdd[6][2] = { {1, 0} , {1, 1}, {0, -1}, {0, 1}, {-1, 0} , {-1, 1} }; // 1, 3, 5,

  int rcEven[6][2] = { {-1, 0} , {0, 1}, {1, 0}, {1, -1}, {0, -1} , {-1, -1} }; // 0, 2, 4, 6
  int rcOdd[6][2] = { {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {0, -1}, {-1, 0}  }; // 1, 3, 5,

  for(int i = 0; i< Circles->Count; ++i){
     TList *aColList = (TList *)Circles->Items[i];
     for(int j = 0; j< aColList->Count; ++j){
         oneCircle *aCircle = (oneCircle *)aColList->Items[j];
         if(aCircle != NULL) {
            aCircle->connections = new TList();
            aCircle->Neighborhood = new TList();
            addCircleNeighbours(Polygons, Circles, aCircle, ((aCircle->Row %2) == 0)? rcEven : rcOdd);
          //  TList *findNList = findNeighbour(Circles, i, j);
         }
     }

  }


    TList *newCircles = new TList();
    for(int i = 0; i< Circles->Count; ++i){
      TList *aColList = (TList *)Circles->Items[i];
      aColList->Pack();
      for (int j = 0; j < aColList->Count; ++j){
         newCircles->Add(aColList->Items[j]);
      }
      aColList->Clear();
      delete aColList;
    }
    delete Circles;

  writeCircles_copy("circle2.scr",newCircles);
  detectCirclesAndNeighboursIntersectWithPolygons(newCircles, Polygons);
  writeCircles_copy("circle3.scr",newCircles);


    TList *Paths = new TList();
    writeCircles_copy("newCircles.scr",newCircles);
    for (int i = 0; i < newCircles->Count; ++i){
       oneCircle *aCircle = (oneCircle *)newCircles->Items[i];
       if (aCircle->visited || !aCircle->isAtEdge) continue;
       if (!aCircle->hasANullConnectio()) continue;
       TList *aPath = new TList();
       Paths->Add(aPath);
       aPath->Add(aCircle);
       aCircle->visited = true;
       traverseOneCircle(Polygons,Paths, aPath, aCircle);
       writePaths("Paths.scr", Paths);
    }


  writePaths("Paths_1.scr", Paths);

  for(int i = 0; i <  Paths->Count; ++i){
     TList *aPath = (TList *)Paths->Items[i];
     for (int j = 0; j < aPath->Count; ++j){
        oneCircle *c1 = (oneCircle *)aPath->Items[j];
        c1->groupIndex = i;
     }
  }



  for(int i = 0; i <  Paths->Count; ++i){
     TList *aPath = (TList *)Paths->Items[i];
     if (aPath->Count < 3) continue;
     oneCircle *c1 = (oneCircle *)aPath->Last();
     for (int j = 0; j < aPath->Count;++j){
       oneCircle *c2 = (oneCircle *)aPath->Items[j];
       if(j == 0 && c1->connections->IndexOf(c2) == -1 && c2->connections->IndexOf(c1) == -1) break;
       //if (c1->connections->IndexOf(c2) != -1) continue;
       for (int n= 0; n < c1->connections->Count; ++n){
          if(c1->connections->Items[n] == NULL) continue;
          oneCircle *c3 = (oneCircle *) c1->connections->Items[n];
          if (c3 == c2) continue;
          if (c3->groupIndex == -1) continue;
          if (c3->groupIndex == c1->groupIndex) continue;
          for (int m = 0; m < c2->connections->Count; ++m){
            //if (c3->groupIndex == c1->groupIndex) continue;
            if(c2->connections->Items[m] == NULL) continue;
            oneCircle *c4 = (oneCircle*) c2->connections->Items[m];
            if (c4 == c1) continue;
            if (c4->groupIndex == -1) continue;
            if (c4->groupIndex == c1->groupIndex) continue;
            if (c3 == c4) continue;
            if (c3 == c1) continue;
            if (c3->groupIndex != c4->groupIndex) continue;
            if (c3->connections->IndexOf(c4) == -1) continue;

            TList *bPath = (TList *)Paths->Items[ c3->groupIndex ];
            if(aPath == bPath) continue;
            if(bPath->Count < 3) continue;
            int c3Index = bPath->IndexOf(c3);
            int c4Index = bPath->IndexOf(c4);
            int c1Index = aPath->IndexOf(c1);
            int c2Index = aPath->IndexOf(c2);
            int kIndex = aPath->Count;
            if (c3Index > c4Index){
              if(c1Index < c2Index){
                  int startIndex = c2Index;
                  for (int k = 0 ; k < kIndex; ++k){
                    bPath->Insert(c4Index, aPath->Items[startIndex]);
                    -- startIndex;
                    if(startIndex == -1 ){
                      startIndex = kIndex-1;
                    }
                  }
                }else{
                   int startIndex = c1Index;
                   for (int k = 0 ; k < kIndex; ++k){
                    bPath->Insert(c3Index, aPath->Items[startIndex]);
                    ++ startIndex;
                    if(startIndex == aPath->Count){
                      startIndex = 0;
                    }
                  }
                }
            }else{
                if(c1Index < c2Index){
                  int startIndex = c2Index;
                  for (int k = 0 ; k < kIndex; ++k){
                    bPath->Insert(c3Index+1, aPath->Items[startIndex]);
                    -- startIndex;
                    if(startIndex == -1){
                      startIndex = kIndex-1;
                    }
                  }
                }else{
                   int startIndex = c1Index;
                   for (int k = 0 ; k < kIndex; ++k){
                    bPath->Insert(c4Index+1, aPath->Items[startIndex]);
                    ++ startIndex;
                    if(startIndex == aPath->Count){
                      startIndex = 0;
                    }
                  }
                }
            }
            aPath->Clear();
            n =  c1->connections->Count;
            break;
          }
       }
       c1 = c2;
       if (aPath->Count == 0) break;
     }
     Paths->Pack();
     writePaths("Paths_3.scr", Paths);
  }

  writePaths("Paths_3.scr", Paths);


  /*for(int i = 0; i <  Paths->Count; ++i){
     int num = -1;
     TList *aPath = (TList *)Paths->Items[i];
     oneCircle *c1 = (oneCircle *)aPath->First();
     oneCircle *c2 = (oneCircle *)aPath->Last();
     for(int j = 0; j < Paths->Count; ++j){
        TList *bPath = (TList *)Paths->Items[j];
        if(bPath == aPath)continue;
        oneCircle *c3 = (oneCircle *)bPath->Last();
        for(int z = 0; z < bPath->Count; ++z){
           oneCircle *c4 = (oneCircle *)bPath->Items[z];
           if((c3->connections->IndexOf(c1) >-1) && (c4->connections->IndexOf(c2) > -1) && (c3->connections->IndexOf(c4) > -1) && (c4->connections->IndexOf(c3) > -1)){
             // num = j;
              //cout << "this point is connection:" << num << "\n"  ;
              int indexnum =  bPath->IndexOf(c3);
              //cout << "this point is index:" << indexnum << "\n"  ;
              for(int m = 0; m < aPath->Count; ++m){
                 oneCircle *insertCircle = (oneCircle *)aPath->Items[m];
                 int indexX = indexnum + m;
                  bPath->Insert(indexX,insertCircle);
              }
           }
           c3 = c4;
        }
     }
  }
  writePaths("Paths2.scr", Paths);    */



    for(int i = 0; i < newCircles->Count; ++i){
         oneCircle *aCircle = (oneCircle *)newCircles->Items[i];
         aCircle->connections->Pack();
         aCircle->visited = false;
    }



    TList *AllPathsCircles = new TList();
    for(int i = 0; i < Paths->Count; ++i){
      TList *aPath = (TList *)Paths->Items[i];
      for(int j = 0; j < aPath->Count; ++j){
         oneCircle *aCircle = (oneCircle *)aPath->Items[j];
         aCircle->visited = true;
         for (int n = 0; n < aCircle->connections->Count; ++n){
            if ( ((oneCircle *) aCircle->connections->Items[n])->isAtEdge)
              aCircle->connections->Items[n] = NULL;

         }
         aCircle->connections->Pack();
         if (aCircle->connections->Count != 0)
           AllPathsCircles->Add(aCircle);
      }
    }
    writePathsChildren("AllPathsCircles.scr",AllPathsCircles);


    TList *remainingCircles = new TList();
    for (int i = 0; i < newCircles->Count; ++i){
       oneCircle *aCircle = (oneCircle *)newCircles->Items[i];
       if (aCircle->visited == true) continue;
       for (int j = aCircle->connections->Count-1; j >= 0; --j){
         oneCircle *aCC = (oneCircle *) aCircle->connections->Items[j];
         if ( (AllPathsCircles->IndexOf(aCC) != -1) || (aCC->isAtEdge)        )
              aCircle->connections->Remove(aCircle->connections->Items[j]);
          }
          if (aCircle->connections->Count != 0){
            remainingCircles->Add(aCircle);
            aCircle->visited = false;
          }
          else
            aCircle->visited = true;



       //}
    }
    writePathsChildren("remainingCircles.scr",remainingCircles);

    for(int i = 0; i< AllPathsCircles->Count; ++i){
      oneCircle *aCircle = (oneCircle *)AllPathsCircles->Items[i];
      for (int j = 0; j < aCircle->connections->Count; ++j){
        oneCircle *aC = (oneCircle *)aCircle->connections->Items[j];
        if (remainingCircles->IndexOf(aC) == -1)
          aCircle->connections->Items[j] = NULL;
      }
      aCircle->connections->Pack();
      if (aCircle->connections->Count == 0)
         AllPathsCircles->Items[i] = NULL;

    }
    AllPathsCircles->Pack();

    
    TList *lastLayerCircles = new TList();
    while (remainingCircles->Count != 0){
      for(int j = 0; j< AllPathsCircles->Count; j += random(3)+2){
         oneCircle *aCircle = (oneCircle *)AllPathsCircles->Items[j];

         if ( remainingCircles->IndexOf(aCircle) != -1 ) continue;


         for ( int i = 0; i < aCircle->connections->Count; ++i){
           oneCircle *aC = (oneCircle *) aCircle->connections->Items[i];
           if ( remainingCircles->IndexOf(aC) == -1 )
             aCircle->connections->Items[i] = NULL;
         }
         aCircle->connections->Pack();
         if (aCircle->connections->Count == 0){
            AllPathsCircles->Items[j] = NULL;
            continue;
         }
         int aa = random(aCircle->connections->Count);
         oneCircle *bCircle = (oneCircle *)aCircle->connections->Items[aa];
         aCircle->children->Add(bCircle);
         lastLayerCircles->Add(bCircle);
         remainingCircles->Remove(bCircle);
         //bCircle->connections->Remove(aCircle);
         aCircle->connections->Remove(bCircle);
         if (aCircle->connections->Count == 0)
           AllPathsCircles->Items[j] = NULL;
      }

      AllPathsCircles->Pack();
      for (int i = 0; i < lastLayerCircles->Count; ++i){
        AllPathsCircles->Add(lastLayerCircles->Items[i]);
      }
      lastLayerCircles->Clear();
    }

   /*

    for(int i = 0; i < AllPathsCircles->Count; ++i){
       oneCircle *aCircle = (oneCircle *)AllPathsCircles->Items[i];
       for (int j = aCircle->connections->Count-1; j >=0; --j)
         if (AllPathsCircles->IndexOf(aCircle->connections->Items[j]) != -1 )
           aCircle->connections->Remove(aCircle->connections->Items[j]);
    }

    for(int j = 0; j< AllPathsCircles->Count; j += 2){
         oneCircle *aCircle = (oneCircle *)AllPathsCircles->Items[j];
         if(aCircle->connections->Count <= 0) continue;
         int aa = random(aCircle->connections->Count);
         oneCircle *bCircle = (oneCircle *)aCircle->connections->Items[aa];
         bCircle->visited = true;
         aCircle->children->Add(bCircle);
     }
  */
   writePathsChildrenEddie("AllPaths.scr", Paths);


   /*for(int i = 0; i < AllPaths->Count; ++i){
       TList *aPath = (TList *)AllPaths->Items[i];
       int count = aPath->Count;
       for(int j = 0; j < count ; ++j){
          oneCircle *cCircle = (oneCircle *)aPath->Items[j];
          TList *connectionsList =  cCircle->connections;
          TList *newConnect = new TList();
          for(int m = 0; m < connectionsList->Count; ++ m){
             if(connectionsList->Items[m] == NULL) continue;
             oneCircle *cCircle = (oneCircle *)connectionsList->Items[m];
             if(!cCircle->isAtEdge && !cCircle->visited){
                newConnect->Add(cCircle);
             }
         }
         if(newConnect->Count <= 0) continue;
         int aa = random(newConnect->Count);
         oneCircle *bCircle = (oneCircle *)newConnect->Items[aa];
         bCircle->isAtEdge = true;
         TList *bPath = new TList();
         bPath->Add(bCircle);
         aPath->rem
         break;
       }

   }
   writePaths("AllPath2.scr",AllPaths);
    */

  delete AllPathsCircles;
  delete remainingCircles;
  for(int i = 0; i< newCircles->Count; ++i){
     oneCircle *aCircle = (oneCircle *)newCircles->Items[i];
     delete aCircle;
  }
  delete newCircles;
  for (int i = 0; i < Paths->Count; ++i){
     delete (TList*) Paths->Items[i];
  }
  delete Paths;


}


