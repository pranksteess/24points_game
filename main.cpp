using namespace std;
#include <stdio.h> 
#include <iostream>
#include <string.h>
#include <string>
#include <set>
#define forT        for(t2=t1;t2<3;t2++)t[t2]=t[t2+1];
#define GetNum(n)    {if(t1>0 && t[t1-1]==t[t1])continue;n=t[t1];forT}
#define isTrue        if(23.9999<total && total<24.0001)
#define argment        n1,GetSym(sym1),n2,GetSym(sym2),n3,GetSym(sym3),n4
#define fsym(s)        for(int s=0;s<4;s++)
#define tct            total=dcount
//sym1的运算级不大于sym2的运算级
#define NG(sym1,sym2)   (!(((sym1==2)||(sym1==3))&&((sym2==0)||(sym2==1)))) 
//sym1与sym2只能是如下匹配: (+, +-*/), (-,*/), (*, */)
#define LEV_NOT(sym1,sym2)  ((sym1-sym2<1)&&(!((sym1==sym2)&&(sym1==1||sym1==3))))
//sym1和sym2属同级运算
#define EQ(sym1,sym2)   (sym1<2&&sym2<2||sym1>1&&sym2>1)
//sym1和sym2属不同级运算
#define NEQ(sym1,sym2)   (!EQ(sym1,sym2))
int SearchCount=0, same;
set<string> args;
char format[11][21] ={
 "((%d%c%d)%c%d)%c%d\n",
 "(%d%c(%d%c%d))%c%d\n",
 "%d%c((%d%c%d)%c%d)\n",
 "%d%c(%d%c(%d%c%d))\n",
 "(%d%c%d)%c(%d%c%d)\n",
 "%d%c%d%c%d%c%d\n",
 "(%d%c%d)%c%d%c%d\n",
 "%d%c(%d%c%d)%c%d\n",
 "%d%c%d%c(%d%c%d)\n",
 "(%d%c%d%c%d)%c%d\n",
 "%d%c(%d%c%d%c%d)\n",
};
char GetSym(int symbol){ 
 switch(symbol){ 
  case 0: return '+'; 
  case 1: return '-'; 
  case 2: return '*'; 
  default: return '/'; 
 } 
} 
void pt(int index, int n1,int sym1,int n2,int sym2,int n3,int sym3,int n4){
 if((sym1==sym2)&&(sym2==sym3)){
  if(same&&(sym1==0||sym1==2))
   return;
  if(sym1==0||sym1==2){//全为+或*时，只取递减的那一组
   if(n1>=n2&&n2>=n3&&n3>=n4){
    same = 1;
    char demo[20];
    sprintf(demo, format[5], n1, GetSym(sym1), n2, GetSym(sym2), n3, GetSym(sym3), n4);
    args.insert(string(demo));
    return;
   }
  }
 } 
 if(1){
  char* tmp_format = NULL;
  switch(index){
   case 0:
    if(NG(sym3,sym2)&&NG(sym2,sym1)){
     if(EQ(sym2,sym3))//使最后两个数有序
      if(n3<n4)
       return;
     if(EQ(sym1,sym2))//使前两个数有序
      if(n2<n3)
       return;
     tmp_format = format[5];
    }
    else if(NG(sym3,sym2))
     tmp_format = format[6];//"(%d%c%d)%c%d%c%d\n";
    else if(NG(sym2,sym1))
     tmp_format = format[9];//"(%d%c%d%c%d)%c%d\n";
    break;
   case 1:
    if(NG(sym3,sym1)&&LEV_NOT(sym1,sym2)){
     if(EQ(sym1,sym2))
      if(n1<n2)
       return;
     if(EQ(sym2,sym3))
      if(n3<n4)
       return;
     tmp_format = format[5];
    }
    else if(NG(sym3,sym1))
      tmp_format = format[7];//"%d%c(%d%c%d)%c%d\n";
    else if(LEV_NOT(sym1,sym2))
     tmp_format = format[9];//"(%d%c%d%c%d)%c%d\n";
    break;
   case 2:
    if(LEV_NOT(sym1,sym3)&&NG(sym3,sym2)){
     if(EQ(sym1,sym2))
      if(n1<n2)
       return;
     if(EQ(sym2,sym3))
      if(n3<n4)
       return;
     tmp_format = format[5];
    }
    else if(LEV_NOT(sym1,sym3))
     tmp_format = format[7];//"%d%c(%d%c%d)%c%d\n";
    else if(NG(sym3,sym2))
      tmp_format = format[10];//"%d%c(%d%c%d%c%d)\n";
    break;
   case 3:
    if(LEV_NOT(sym1,sym2)&&LEV_NOT(sym2,sym3)){
     if(EQ(sym1,sym2))
      if(n1<n2)
       return;
     if(EQ(sym2,sym3))
      if(n2<n3)
       return;
     tmp_format = format[5];
    }
    else if(LEV_NOT(sym1,sym2))
      tmp_format = format[8];//"%d%c%d%c(%d%c%d)\n";
    else if(LEV_NOT(sym2,sym3))
      tmp_format = format[10];//"%d%c(%d%c%d%c%d)\n";
    break;
   case 4:
    if(NG(sym2,sym1)&&LEV_NOT(sym2,sym3)){
     if(EQ(sym1,sym2))
      if(n1<n2)
       return;
     if(EQ(sym2,sym3))
      if(n3<n4)
       return;
     tmp_format = format[5];
    }
    else if(NG(sym2,sym1))
      tmp_format = format[8];//"%d%c%d%c(%d%c%d)\n";
    else if(LEV_NOT(sym2,sym3))
     tmp_format = format[6];//"(%d%c%d)%c%d%c%d\n";
    break;
  }
  if(!tmp_format)
   tmp_format = format[index];
  if((tmp_format == (char*)&format[0])
   ||(tmp_format == (char*)&format[1])
   ||(tmp_format == (char*)&format[2])
   ||(tmp_format == (char*)&format[3])
   ||(tmp_format == (char*)&format[4])
   ||(tmp_format == (char*)&format[5])
   ||((tmp_format == (char*)&format[6])&&(NEQ(sym2,sym3)||(sym2==sym3&&n3>=n4)))//剔除(1+3)*2*3的情况
   ||(tmp_format == (char*)&format[7])
   //各种剔除，剔除的啥我也记不清了。。。
   ||((tmp_format == (char*)&format[8])&&(NEQ(sym1,sym2)||(sym1==0||sym1==2)&&n1>=n2))
   ||((tmp_format == (char*)&format[9])&&(NEQ(sym1,sym2)||(sym1==sym2&&(sym1==0||(sym1==2))&&n2>=n3&&n1>=n2)))
   ||((tmp_format == (char*)&format[10])&&(NEQ(sym3,sym2)||(sym2==sym3&&n3>=n4)||((sym2==0||sym2==2)&&n2>=n3)))
  ){
   char* ch = strchr(tmp_format, '(');
   char* hc = strchr(tmp_format, ')');
   char* rch = strrchr(tmp_format, '(');

   int i,j,len=strlen(tmp_format),k=len;
   for(i=0;tmp_format[i]!='('&&tmp_format[i]!='\0';i++);//顺序找"("
   for(j=len-1;tmp_format[j]!='('&&j>=0;j--);//逆序找"("
   if(i!=len)
    for(k=i+1;tmp_format[k]!=')'&&tmp_format[k]!='\0';k++);//顺序找")"

   if(len==i){

    if(n2==n3&&sym1==1&&sym2==0&&(sym3==0||sym3==1))//剔除3+4-4+21的情况，21+3-4+4合法
     return;
    if(n4==n3&&sym2==1&&sym3==0)//剔除4*6+3-3的情况，4*6-3+3合法
     return;

    //防止8+4*3+4出现冗余,只使4*3+8+4合法
    if(sym2==2&&n2*n3<n4)
      return;
    else if(sym3==2&&n2<n3*n4)
      return;
    else if(sym2==3&&n2/n3<n4)
      return;
    else if(sym3==3&&n2<n3/n4)
      return;
   }
   else if(i==j&&k-i==7){
    if(i==4){
     if(sym2==0&&n2+n3<n4)
      return;
     else if(sym2==1&&n2-n3<n4)
      return;
     else if(sym2==2&&n2*n3<n4)
      return;
     else if(sym2==3&&n2/n3<n4)
      return;
    }
    else if(i==8){
     if(sym3==0&&n2<n3+n4)
      return;
     else if(sym3==1&&n2<n3-n4)
      return;
     else if(sym3==2&&n2<n3*n4)
      return;
     else if(sym3==3&&n2<n3/n4)
      return;
    }
   }
   char demo[20];
   sprintf(demo, tmp_format, argment);
   args.insert(string(demo));
  }
 }
}
double dcount(double num1,double num2,int symbol){
 switch(symbol){ 
  case 0: if(num1>=num2)return num1+num2;else return -1e10; //剔除被加数小于加数的情况
  case 1: if(1)return num1-num2;else return -1e10; 
  case 2: if(num1>=num2)return num1*num2;else return -1e10; //剔除被乘数小于乘数的情况
  default:if((num2<-0.0001 || 0.0001<num2))
     return num1/num2;else return -1e10; 
 } 
} 
int main(int argc, char* argv[]){
 int z1;
 int m[4],n1,n2,n3,n4; 
 printf("Input 4 Numbers(a,b,c,d):\n"); 
 scanf("%d,%d,%d,%d",&m[0],&m[1],&m[2],&m[3]); 
 for(n2=0;n2<3;n2++)for(n1=2;n1>=n2;n1--)
  if(m[n1]>m[n1+1])n3=m[n1+1],m[n1+1]=m[n1],m[n1]=n3;
 for(z1=0;z1<24;z1++){
  int z2=z1 % 6,t1=z1/6,t2,t[4]={m[0],m[1],m[2],m[3]};
  GetNum(n1)t1=z2/2;z2%=2;GetNum(n2)t1=z2;GetNum(n3)n4=t[0];
  fsym(sym1)fsym(sym2)fsym(sym3){ 
   double total,total2=dcount(n3,n4,sym3);
   tct(n1,n2,sym1);tct(total,n3,sym2);tct(total,n4,sym3); 
   isTrue{
    pt(0, n1,sym1,n2,sym2,n3,sym3,n4);
   }
   tct(n2,n3,sym2);tct(n1,total,sym1);tct(total,n4,sym3); 
   isTrue{
    pt(1, n1,sym1,n2,sym2,n3,sym3,n4);
   }
   tct(n2,n3,sym2);tct(total,n4,sym3);tct(n1,total,sym1); 
   isTrue{
    pt(2, n1,sym1,n2,sym2,n3,sym3,n4);
   }
   tct(n3,n4,sym3);tct(n2,total,sym2);tct(n1,total,sym1); 
   isTrue{
    pt(3, n1,sym1,n2,sym2,n3,sym3,n4);
   }
   tct(n1,n2,sym1);tct(total,total2,sym2); 
   isTrue{
    pt(4, n1,sym1,n2,sym2,n3,sym3,n4);
   }
  }
 }
 set<string>::iterator ptr=args.begin();
 for(;ptr!=args.end();ptr++)
  cout<<*ptr;
 printf("Total=%d\n",args.size());
 return 0;
}
