#include<iostream>
#include<omp.h>
#include"timer4300.cpp"
using namespace std;
long power(long a, long b){
    long p=1;
    for(int i=0;i<b;++i){
        p*=a;
        p%=17;
    }
}
void addSeqNP(int* x, int* y, int* z, long lengths){
  for(long i=0;i<lengths;++i){
    z[i]=power(x[i],y[i]);
  }
}

void addSeq(int *x, int* y, int* z, long lengths){

long nThreads;
#pragma omp parallel
{
    if(omp_get_thread_num()==0){
      nThreads=omp_get_num_threads();
    }
}
//nThreads=2;
    cout<<"Number of threads is "<<nThreads<<endl;
    cout<<"Number of terms is "<<lengths<<endl;
#pragma omp parallel num_threads(nThreads)
{


  long helper=omp_get_thread_num();
  while(helper<lengths){
    z[helper]=power(x[helper],y[helper]);
    helper+=nThreads;
  }
}

}

int main(){
  Timer4300 myT;
  cout<<"Hi"<<endl;
  int *x, *y, *z;
  long len=100000;
  x=new int[len];
  y=new int[len];
  z=new int[len];
  for(long i=0;i<len;++i){
    x[i]=7;
    y[i]=50000;
  }
  myT.start();
  addSeq(x,y,z,len);
  myT.end();
  cout<<"Total time is "<<myT.getTime()<<endl;;

  myT.start();
  addSeqNP(x,y,z,len);
  myT.end();
  cout<<"Total time (non-parallel) is "<<myT.getTime()<<endl;
  /*for(int i=0;i<len;++i){
    cout<<z[i]<<" ";
  }*/

  cout<<endl;
  return 0;
}
