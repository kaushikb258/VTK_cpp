#include <iostream>
#include <string>
#include <sstream> 
#include <fstream>
#include <math.h>

using namespace std;

void vtk_write(string filename,string title,int imax, int jmax, double* xyz, int nprim, double* prim)
{
 string cell_size_string, node_num_string; 
 int node;
 int i, j, k, n;
 stringstream s_node_num, s_cells, s_imax, s_jmax, s_kmax; 
 ofstream f;
 int kmax = 1;

 s_node_num << (imax*jmax);
 s_cells << (imax-1)*(jmax-1);
 s_imax << imax;
 s_jmax << jmax;
 s_kmax << kmax;

 f.open (filename.c_str(),ios_base::out);
 f<< "# vtk DataFile Version 2.0\n";
 f<< title<<"\n";
 f<< "ASCII\n";
 f<< "DATASET STRUCTURED_GRID\n";
 f<< "DIMENSIONS "<<"\t"<<s_imax.str()<<"\t\t"<<s_jmax.str()<<"\t\t"<<s_kmax.str()<<"\n"; 
 f<< "POINTS "<<"\t"<<s_node_num.str()<<"\t"<<"double\n";
 
 n = 0;
 for (i=0; i<imax; i++)
 {
  for (j=0; j<jmax; j++)
  {
   for (k=0; k<3; k++)
   { 
    f<<xyz[n]<<" ";
    n++;
   }
   f<<"\n";
  }
 }  

 f<< "CELL_DATA "<<"\t"<<s_cells.str()<<"\n";
 f<< "POINT_DATA "<<"\t"<<s_node_num.str()<<"\n";

 f<< "SCALARS density double \n";
 f<< "LOOKUP_TABLE default \n";
 n = 0;
 for (i=0; i<imax; i++)
 {
  for (j=0; j<jmax; j++)
  {
   f<< prim[n]<<" ";
   n += nprim;
  }
 } 
 f<<"\n";

 f<< "SCALARS u-velocity double \n";
 f<< "LOOKUP_TABLE default \n";
 n = 1;
 for (i=0; i<imax; i++)
 {
  for (j=0; j<jmax; j++)
  {
   f<< prim[n]<<" ";
   n += nprim;
  }
 } 
 f<<"\n";

 f<< "SCALARS v-velocity double \n";
 f<< "LOOKUP_TABLE default \n";
 n = 2;
 for (i=0; i<imax; i++)
 {
  for (j=0; j<jmax; j++)
  {
   f<< prim[n]<<" ";
   n += nprim;
  }
 } 
 f<<"\n";

 f<< "SCALARS pressure double \n";
 f<< "LOOKUP_TABLE default \n";
 n = 3;
 for (i=0; i<imax; i++)
 {
  for (j=0; j<jmax; j++)
  {
   f<< prim[n]<<" ";
   n += nprim;
  }
 } 

 f.close();
}



int main()
{
 string filename = "output_paraview.vtk";
 string title = "cfd2d";
 int imax = 100;
 int jmax = 50;
 double coord[imax][jmax][3];
 int i, j;
 double dx = 1.0e-3;
 double dy = 1.0e-3;
 int nprim = 4;
 double q[imax][jmax][nprim];
 double v1, v2;

 // initialize coordinates
 for (i=0; i<imax; i++)
 {
  for (j=0; j<jmax; j++)
  {
   coord[i][j][0] = ((double) (i) + 0.5)*dx; //x
   coord[i][j][1] = ((double) (j) + 0.5)*dy; //y
   coord[i][j][2] = 0.0; //z = 0 as 2D grid
  } 
 }   

 // initialize q
 for (i=0; i<imax; i++)
 {
  for (j=0; j<jmax; j++)
  {
   v1 = ((double) i)/((double) imax);
   v2 = ((double) j)/((double) jmax);
   q[i][j][0] = 1.2 + 0.2*v1 + 0.6*v2; 
   q[i][j][1] = 0.8*v1 + 0.1*v2; 
   q[i][j][2] = 0.2*v1 + 0.2*v2;
   q[i][j][3] = 2.7 + 0.8*v1 + 1.6*v2; 
  } 
 }   

 vtk_write(filename,title,imax,jmax,&coord[0][0][0],nprim,&q[0][0][0]);
 return 0;
}
