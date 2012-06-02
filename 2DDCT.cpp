
#include"2DDCT.h"

Mat img2D_DCT(Mat mtx)
{
  int N=mtx.rows;
  int M=mtx.cols;
  Mat res(mtx.rows,mtx.cols,CV_64F);
  double Pu,Pv;
  for(int u=0;u<N;u++)
    {
      for(int v=0;v<M;v++)
        {
          if(u==0)  Pu=1.0/sqrt(2.0);
          else  Pu=1.0;
          if(v==0)  Pv=1.0/sqrt(2.0);
          else Pv=1.0;
          res.at<double>(u,v)=sqrt(2.0/N)*sqrt(2.0/M)*Pu*Pv*Sum_2D_DCT(mtx,u,v,N,M);
        }
    }
  return res;
}

double Sum_2D_DCT(Mat mtx, int u, int v, int N, int M)
{
  double sum=0;
  for(int i=0;i<N;i++)
    for(int j=0;j<M;j++)
      {
        sum+=mtx.at<uchar>(i,j)*cos(PI*(2.0*i+1.0)*u/(2.0*N))*cos(PI*(2.0*j+1.0)*v/(2.0*M));
      }
  return sum;
}

Mat imgInverse_2D_DCT(Mat mtxD,int coefficient)
{
  Mat mtx;
  if(coefficient==0)
    {
      mtx=mtxD.clone();
    }
  else if(coefficient!=0)
    {
        mtx=Mat(mtxD.rows,mtxD.cols,CV_64F);
        for(int i=0;i<mtxD.rows;i++)
          for(int j=0;j<mtxD.cols;j++)
            {
              if(i<mtxD.rows/sqrt(coefficient)&&j<mtxD.cols/sqrt(coefficient))
                {
                  mtx.at<double>(i,j)=mtxD.at<double>(i,j);
                }
              else
                {
                  mtx.at<double>(i,j)=0;
                }
            }
    }
  int N=mtx.rows;
  int M=mtx.cols;
   Mat res(mtx.rows,mtx.cols,CV_8U);
   double calc;
   for(int i=0;i<N;i++)
     for(int j=0;j<M;j++)
       {
         calc=sqrt(2.0/N)*sqrt(2.0/M)*Sum_Inverse_2D_DCT(mtx,i,j,N,M);
         if(calc>255)
           calc=255;
         else if(calc<0)
           calc=0;
         res.at<uchar>(i,j)=calc;
       }
   return res;
}

double Sum_Inverse_2D_DCT(Mat mtx, int i, int j, int N, int M)
{
  double sum=0;
  double Pu,Pv;
  for(int u=0;u<N;u++)
    for(int v=0;v<M;v++)
      {
        if(u==0)  Pu=1.0/sqrt(2.0);
        else  Pu=1.0;
        if(v==0)  Pv=1.0/sqrt(2.0);
        else Pv=1.0;
        sum+=Pu*Pv*mtx.at<double>(u,v)*cos(PI*(2.0*i+1.0)*u/(2.0*N))*cos(PI*(2.0*j+1.0)*v/(2.0*M));
      }
  return sum;
}

vector<Mat> img88DCT(Mat mtx)
{
  vector<Mat> blocks;
  Mat temp,res;
  for(int i=0;i<mtx.rows/8;i++)
    for(int j=0;j<mtx.cols/8;j++)
      {
        temp=mtx(Range(0+i*8,8+i*8),Range(0+j*8,8+j*8));
        res=img2D_DCT(temp);
        blocks.push_back(res);
        //outfile<<temp<<endl;
      }
  return blocks;
}

Mat img88Inverse_DCT(vector<Mat> vmtx, int rows, int cols,int coefficient)
{
   Mat res(rows,cols,CV_8U);
   res.setTo(0);
  vector<Mat> inv;
  for(unsigned int i=0;i<vmtx.size();i++)
    {
        Mat temp(8,8,CV_8U);
        temp=imgInverse_2D_DCT(vmtx[i],coefficient);
        inv.push_back(temp);
    }
  for(int i=0;i<rows/8;i++)
    for(int j=0;j<cols/8;j++)
      {
        Mat subarray(res,Range(i*8,8+i*8),Range(j*8,8+j*8));
        inv[i*rows/8+j].copyTo(subarray);
      }
  return res;
}
