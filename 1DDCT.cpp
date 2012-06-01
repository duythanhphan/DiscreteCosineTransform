
#include "1DDCT.h"


Mat img1D_DCT(Mat mtx)
{

  Mat res(mtx.rows,mtx.cols,CV_64F);
  Mat middle(mtx.rows,mtx.cols,CV_64F);

  //First-Row-Then-Column

  int N=mtx.cols;
  double calc;
  for(int i=0;i<mtx.rows;i++)
    {

      for(int u=0;u<N;u++)
        {
          if(u==0)
            {
              calc=sqrt(2.0/N)/sqrt(2.0)*DCT_sum_row(mtx,i,u,N);
//              if(calc>255)
//                calc=255;
//              else if(calc<0)
//                calc=0;
              middle.at<double>(i,u)=calc;
            }
          else if(u>0)
            {
              calc=sqrt(2.0/N)*DCT_sum_row(mtx,i,u,N);
//              if(calc>255)
//                calc=255;
//              else if(calc<0)
//                calc=0;
              middle.at<double>(i,u)=calc;
            }
        }
    }
//  ofstream outfile;
//  outfile.open("Origin.log",ios::out);
//  outfile<<mtx;
//  outfile.close();
//  outfile.open("1Dmiddle.log",ios::out);
//  outfile<<middle;
  N=middle.rows;
  for(int i=0;i<middle.cols;i++)
    {
      for(int u=0;u<N;u++)
        {
          if(u==0)
            {
              calc=sqrt(2.0/N)/sqrt(2.0)*DCT_sum_col(middle,i,u,N);
              res.at<double>(u,i)=calc;
            }
          else if(u>0)
            {
              calc=sqrt(2.0/N)*DCT_sum_col(middle,i,u,N);
              res.at<double>(u,i)=calc;
            }
        }
    }
//  outfile.close();
//  outfile.open("1Dres.log",ios::out);
//  outfile<<res;
  return res;
}

double DCT_sum_row(Mat mtx,int i,int u, int N)
{
  double sum=0;
  for(int x=0;x<N;x++)
    {
      sum+=(double)(mtx.at<uchar>(i,x))*cos(PI*(2.0*x+1.0)*u/(2.0*N));
    }
  return sum;
}


double DCT_sum_col(Mat mtx,int i,int u, int N)
{
  double sum=0;
  for(int x=0;x<N;x++)
    {
      sum+=(double)(mtx.at<double>(x,i))*cos(PI*(2.0*x+1.0)*u/(2.0*N));
    }
  return sum;
}

 Mat imgInverse_1D_DCT(Mat mtx)
 {
   Mat res(mtx.rows,mtx.cols,CV_8U);
   Mat middle(mtx.rows,mtx.cols,CV_64F);
   //First-Column-Then-Row
   int N;
   double calc;
   N=mtx.rows;
   for(int i=0;i<mtx.cols;i++)
     {
       for(int x=0;x<N;x++)
         {
           calc=sqrt(2.0/N)*iDCT_sum_col(mtx,i,x,N);
           middle.at<double>(x,i)=calc;
         }
     }

//   ofstream outfile;
//   outfile.open("i1Dmiddle.log",ios::out);
//   outfile<<middle;
   N=mtx.cols;
   for(int i=0;i<mtx.rows;i++)
     {
       for(int x=0;x<N;x++)
         {
           calc=sqrt(2.0/N)*iDCT_sum_row(middle,i,x,N);
           if(calc>255)
             calc=255;
           else if(calc<0)
             calc=0;
           res.at<uchar>(i,x)=calc;
         }
     }
//   outfile.close();
//   outfile.open("i1Dres.log",ios::out);
//   outfile<<res;
   return res;
 }

 double iDCT_sum_row(Mat mtx, int i, int x, int N)
 {
   double sum=0;
   sum+=1.0/sqrt(2)*mtx.at<double>(i,0);
   for(int u=1;u<N;u++)
     {
       sum+=mtx.at<double>(i,u)*cos(PI*(2.0*x+1.0)*u/(2.0*N));
     }
   return sum;
 }

 double iDCT_sum_col(Mat mtx, int i, int x, int N)
 {
   double sum=0;
   sum+=1.0/sqrt(2)*mtx.at<double>(0,i);
   for(int u=1;u<N;u++)
     {
       sum+=mtx.at<double>(u,i)*cos(PI*(2.0*x+1.0)*u/(2.0*N));
     }
   return sum;
 }
