#include"Quantilization.h"

t88Res img88DCT_Q(Mat mtx,Mat Q)
{
  vector<Mat> blocks,orig;
  t88Res ret;
  Mat temp,res;
  for(int i=0;i<mtx.rows/8;i++)
    for(int j=0;j<mtx.cols/8;j++)
      {
        temp=mtx(Range(0+i*8,8+i*8),Range(0+j*8,8+j*8));
        orig.push_back(temp);
        res=img2D_DCT_Q(temp,Q);
        blocks.push_back(res);
        //outfile<<temp<<endl;
      }
  ret.orig=orig;
  ret.DCT=blocks;
  return ret;
}

Mat img2D_DCT_Q(Mat mtx,Mat Q)
{
  assert(mtx.rows==Q.rows&&mtx.cols==Q.cols);
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
          res.at<double>(u,v)=sqrt(2.0/N)*sqrt(2.0/M)*Pu*Pv*Sum_2D_DCT(mtx,u,v,N,M)/Q.at<double>(u,v);
        }
    }
  return res;
}
i88Res img88Inverse_DCT_Q(vector<Mat> vmtx, int rows, int cols,int coefficient)
{
   Mat res(rows,cols,CV_8U);
   res.setTo(0);
  vector<Mat> inv;
  i88Res ret;
  for(unsigned int i=0;i<vmtx.size();i++)
    {
        Mat temp(8,8,CV_8U);
        temp=imgInverse_2D_DCT(vmtx[i],coefficient);
        inv.push_back(temp);
    }
  ret.blocks=inv;
  for(int i=0;i<rows/8;i++)
    for(int j=0;j<cols/8;j++)
      {
        Mat subarray(res,Range(i*8,8+i*8),Range(j*8,8+j*8));
        inv[i*rows/8+j].copyTo(subarray);
      }
  ret.res=res;
  return ret;
}

