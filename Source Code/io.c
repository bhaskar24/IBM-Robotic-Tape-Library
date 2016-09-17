#include<conio.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

#define r 20
#define c 5
#define tR 39

struct rtl_db
{
    unsigned long int eM[r][c];
    unsigned long int oM[r][c];

    unsigned long int inp1[10];
    unsigned long int inp2[10];

    int count;
    int n;
    int en;
    int on;
    int posi;
    int posj;
    int nIP;
    unsigned long int id1;
    unsigned long int id2;
    unsigned long int id3;
    unsigned long int bc;
    unsigned long int cBc;
    int x;
    int maxId;
    int status;
    int status1;
}db;

struct rtl_Tdb
{
    unsigned long int eTm[tR][c];
    unsigned long int oTm[tR][c];
}Tdb;
void updateIO()
{
    int i;
    for(i=0;i<10;i++)
    {
        db.inp1[i]=1000000000;
    }
}
void initialize(FILE *fDb,FILE *fDb2) //initialize the RTL at present odd temp DB
{
    int i,j;
    updateIO();
    fDb=fopen("oDb.txt","w+");     //show oddTempDb
    if(fDb==NULL)
    {
       printf("Error in opening the RTL DATABASE\n");
    }

    fDb2=fopen("eDb.txt","w+");
    if(fDb2==NULL)
    {
        printf("Error in opening the RTL DATABASE\n");
    }
    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            if(i%2==0 || i==0)
            {
                Tdb.oTm[i][j]=1000000000;
            }
            else Tdb.oTm[i][j]=0;
        }
    }
    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            if(i%2==0 || i==0)
            {
                Tdb.eTm[i][j]=1000000000;
            }
            else Tdb.eTm[i][j]=0;
        }
    }

    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            if(j==0 && i==0)
                fprintf(fDb,"%d",Tdb.eTm[i][j]);
            else fprintf(fDb," %d",Tdb.eTm[i][j]);
        }
    }
    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            if(j==0 && i==0)
                fprintf(fDb2," %d",Tdb.eTm[i][j]);
            else
                fprintf(fDb2," %d",Tdb.eTm[i][j]);
        }
    }

    fclose(fDb2);
    fclose(fDb);
    db.en=0;
    db.on=0;
    db.n=db.en+db.on;    //oTempDB INITIALIZATION START
    db.id1=000;
    db.id2=000;
    db.id3=000;
    db.maxId=000;
}

void cpyRTL(FILE *fDb,FILE *fDb2)
{
    int i,j,tmp;

    fDb=fopen("oDb.txt","r+");
    if(fDb==NULL)
    {
        printf("Error in Opening the RTL Database");
    }

    fDb2=fopen("eDb.txt","r+");
    if(fDb2==NULL)
    {
        printf("Error in Opening the RTL Database");
    }

    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            fscanf(fDb,"%d",&Tdb.oTm[i][j]);
        }
    }

    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            fscanf(fDb2,"%d",&Tdb.eTm[i][j]);
        }
    }
    for(i=0;i<20;i++)
    {
        tmp=i*2;
        for(j=0;j<5;j++)
        {
            {
                db.oM[i][j]=Tdb.oTm[tmp][j];
            }
        }
    }
    for(i=0;i<20;i++)
    {
        tmp=i*2;
        for(j=0;j<5;j++)
        {
            {
                db.eM[i][j]=Tdb.eTm[tmp][j];
            }
        }
    }
    fclose(fDb);
    fclose(fDb2);

}
void showRTL(FILE *fDb,FILE *fDb2)
{
    int i,j,x=-1,k;
    char rtl[20]={"Robotic Tape Library"};

    cpyRTL(fDb,fDb2);
    for(i=0;i<164;i++)//main RTL VISUAL
    {
        if(i>=70&&i<=89)
         {
           x=x++;
           printf("%c",rtl[x]);
         }
         else
            printf("-");
    }
    printf("\n\n\n");
    for(i=0;i<20;i++)
    {
        printf("\t");
        for(j=0;j<5;j++)
        {
            if(j==4)
            {
                printf("| %d  ",db.oM[i][j]);
                printf("\t\t");
                for(k=0;k<5;k++)
                {
                    if(k==0)
                       {
                          printf(" %d ",db.eM[i][j]);
                       }
                    else
                          printf("| %d ",db.eM[i][j]);
                }

            }
            else if(j==0)
                    {
                        printf(" %d ",db.oM[i][j]);

                    }
                    else
                        printf("| %d ",db.oM[i][j]);

        }
        printf("\n");
    }
        printf("\n\n");
  for(i=0;i<164;i++)
    {
            printf("-");
    }
}

void showRTLwIO(FILE *fDb,FILE *fDb2)
{
    int i,j,x=-1,k;
    char rtl[20]={"Robotic Tape Library"};

    for(i=0;i<164;i++)
    {
        if(i>=70&&i<=89)
         {
           x=x++;
           printf("%c",rtl[x]);
         }
         else
            printf("-");
    }
    printf("\n\n\n");

    printf("\t");
    //1stack start
    x=-1;
    for(i=0;i<3;i++)
    {
        if(i==1)
        {
            printf("IO Stack   ");
        }
        else
        {
            printf("\t   ");
        }
        for(j=0;j<129;j++)
        {
            if(i==0 || i==2)
            {
                printf("-");
            }
            else
            {
                if(j==0)
                {
                    x++;
                    printf(" %d ",db.inp1[x]);
                }
                else if(j==9)
                    {
                        x++;
                        printf("| %d ",db.inp1[x]);
                    }
                    else if( j >0 && j<9)
                        {
                            x++;
                             printf("| %d ",db.inp1[x]);
                        }
                        else
                            printf("");
            }

        }
        printf("\n\t");
    }printf("\n");
    //1stack end

  /*  printf("\t");
    //2stack start
    x=-1;
    for(i=0;i<3;i++)
    {
        if(i==1)
        {
            printf("IO Stack   ");
        }
        else
        {
            printf("\t   ");
        }
        for(j=0;j<129;j++)
        {
            if(i==0 || i==2)
            {
                printf("-");
            }
            else
            {
                if(j==0)
                {
                    x++;
                    printf(" %d ",db[3].inp2[x]);
                }
                else if(j==9)
                    {
                        x++;
                        printf("| %d ",db[3].inp2[x]);
                    }
                    else if( j >0 && j<9)
                        {
                            x++;
                             printf("| %d ",db[3].inp2[x]);
                        }
                        else
                            printf("");
            }

        }
        printf("\n\t");
    }printf("\n");
*/    //2stack end

    cpyRTL(fDb,fDb2);
    for(i=0;i<20;i++)
    {
        printf("\t");
        for(j=0;j<5;j++)
        {
            if(j==4)
            {
                printf("| %d \t",db.oM[i][j]);
                printf("\t    ");
                for(k=0;k<5;k++)
                {
                    if(k==0)
                       {
                          printf(" %d ",db.eM[i][k]);
                       }
                    else
                          printf("| %d ",db.eM[i][k]);
                }

            }
            else if(j==0)
                    {
                        printf(" %d ",db.oM[i][j]);

                    }
                    else
                        printf("| %d ",db.oM[i][j]);

        }
        printf("\n");
    }
        printf("\n\n");
  for(i=0;i<164;i++)
    {
            printf("-");
    }
    printf("\n");
}
void detMax()
{
    int i,j,tmp=1000000000,tmp2=1000000000;
    for(i=0;i<20;i++)
     {
       for(j=0;j<5;j++)
         {
           if(db.oM[i][j] > tmp)
             {
               tmp=db.oM[i][j];
             }
           if(db.eM[i][j] > tmp2)
             {
               tmp2=db.eM[i][j];
             }
             if(tmp > tmp2) tmp=tmp;
             else tmp=tmp2;
         }
     }
    db.maxId=tmp;
    db.maxId=(int)db.maxId/1000000;
    if(tmp >1000000000) db.maxId=db.maxId-1000;
    else db.maxId=db.maxId-1000;
}
void checkCounter(FILE *fDb,FILE *fDb2)
{
    db.n=0,db.en=0,db.on=0,db.posi=0,db.posj=0,db.nIP=0,db.id1=000,db.id2=000,db.id3=000,db.count=0,db.x=0;;
    int i,j,tmp=0;
    cpyRTL(fDb,fDb2);

    for(i=0;i<20;i++)
    {
        for(j=0;j<5;j++)
        {
            if(db.oM[i][j]!=1000000000) db.on++;
            if(db.eM[i][j]!=1000000000) db.en++;
        }
    }
    db.n=db.on+db.en;

    for(i=0;i<20;i++)
    {
        for(j=0;j<5;j++)
        {
            if(db.on!=200)
            {
                if(db.oM[i][j]==1000000)
                {
                    db.posi=i;
                    db.posj=j;
                    break;
                }
            }
            else
                if(db.eM[i][j]==1000000)
                {
                    db.posi=i;
                    db.posj=j;
                    break;
                }
        }
    }

    for(i=0;i<10;i++)
    {
        db.inp1[i]=1000000000;
        db.inp2[i]=1000000000;
    }
    detMax();
}
void checkId1()
{
 detMax();
 db.id1=db.maxId++;
}
void delTemp() //for remove input tape bc file
{
    int st;
    //if(file_exist("tmp.txt"))
    //{
        st=remove("tmp.txt");
        if(st!=0)
        {
            printf("Unable to delete the file\n");
        }
    //}
}
void genBarcode()
{
    int i=1,nt=db.count;
    char xBC[14];
    FILE *tmp;
    while(nt!=0)
    {
        printf("Enter the Catridge Barcode\n");
        scanf("%d",&db.bc);
        if(i==1)
        {
            itoa(db.bc,xBC,10);
            strcat(xBC,".txt");
            db.cBc=db.bc;
        }
        tmp=fopen(xBC,"a+");
        if(tmp==NULL) printf("Error in openning the tmp file\n");
        fprintf(tmp,"%d ",db.bc);
        fclose(tmp);
        nt--;
    }
}
int retBC()
{
    FILE *tmp;
    unsigned long int tBC,j;
    char xBC[14];
    int i;

    itoa(db.cBc,xBC,10);
    strcat(xBC,".txt");

    tmp=fopen(xBC,"a+");
    if(tmp==NULL) printf("Unable to find your Catridge\n");

    for(i=0;i<10;i++)
    {
      if(i==db.count)
       {
         fscanf(tmp,"%d",&tBC);
       }
      fscanf(tmp,"%d",&j);
    }
    fclose(tmp);
    return tBC;
}
void saveCValue(FILE *fDb,FILE *fDb2)
{
    int i,j;
    fDb=fopen("oDb.txt","r+");     //show oddTempDb
    if(fDb==NULL)
    {
       printf("Error in opening the RTL DATABASE\n");
    }

    fDb2=fopen("eDb.txt","r+");
    if(fDb2==NULL)
    {
        printf("Error in opening the RTL DATABASE\n");
    }
    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            if(j==0 && i==0)
                fprintf(fDb,"%d",Tdb.oTm[i][j]);
            else fprintf(fDb," %d",Tdb.oTm[i][j]);
        }
    }
    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            if(j==0 && i==0)
                fprintf(fDb2," %d",Tdb.eTm[i][j]);
            else
                fprintf(fDb2," %d",Tdb.eTm[i][j]);
        }
    }
    fclose(fDb2);
    fclose(fDb);
       //oTempDB INITIALIZATION START
    cpyRTL(fDb,fDb2);
}
void cpyStackVal()
{
    int nt,i,l=-1;
    FILE *tmp;
    FILE *fDb,*fDb2;
    char xBC[14];
    nt=10;
         itoa(db.cBc,xBC,10);
         strcat(xBC,".txt");
        tmp=fopen(xBC,"r+");
        if(tmp==NULL) printf("Error in copying the file");

          for(i=0;i<10;i++)
            {
              fscanf(tmp,"%d",&db.inp1[i]);
            }
       fclose(tmp);
}
void checkStatus()
{
    int i,j;
    FILE *fDb,*fDb2;

    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            if(i%2!=0 && i!=0)
            {
               if(Tdb.oTm[i-1][j]!=1000000000 && Tdb.oTm[i+1][j]!=1000000000)
                {
                   Tdb.oTm[i][j]=1;
                }
                else
                    Tdb.oTm[i][j]=0;
            }
        }
    }

    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            if(i%2!=0 && i!=0)
            {
               if(Tdb.eTm[i-1][j]!=1000000000 && Tdb.eTm[i+1][j]!=1000000000)
                {
                   Tdb.eTm[i][j]=1;
                }
                else
                    Tdb.eTm[i][j]=0;
            }
        }
    }

    fDb=fopen("oDb.txt","r+");     //show oddTempDb
    if(fDb==NULL)
    {
       printf("Error in opening the RTL DATABASE\n");
    }

    fDb2=fopen("eDb.txt","r+");
    if(fDb2==NULL)
    {
        printf("Error in opening the RTL DATABASE\n");
    }

        for(i=0;i<39;i++)
        {
            for(j=0;j<5;j++)
            {
                if(j==0 && i==0)
                    fprintf(fDb,"%d",Tdb.eTm[i][j]);
                else fprintf(fDb," %d",Tdb.eTm[i][j]);
            }
        }
    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            if(j==0 && i==0)
                fprintf(fDb2," %d",Tdb.eTm[i][j]);
            else
                fprintf(fDb2," %d",Tdb.eTm[i][j]);
        }
    }

    fclose(fDb2);
    fclose(fDb);    //oTempDB INITIALIZATION START
    //cpyRTL(fDb,fDb2);
}
void detPos()
{
  int i,j,k;
  if(db.on!=100)
   {
    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
          if(i ==0 || i%2==0)
           {
             if(Tdb.oTm[i][j]==1000000000)
               {
                 db.posi=i;
                 db.posj=j;
                 if(j==4) break;
               }
           }
        }
    }
   }
   else
    {
      for(i=0;i<39;i++)
       {
          for(j=0;j<5;j++)
          {
            if(i ==0 || i%2==0)
             {
                if(i ==0 || i%2==0)
                 {
                   if(Tdb.eTm[i][j]==1000000000)
                    {
                      db.posi=i;
                      db.posj=j;
                      if(j==4) break;
                     }
                 }
             }
          }
        }
     }
}
void saveTmM()
{
    int i,j,tmp;

    for(i=0;i<20;i++)
    {
        tmp=i*2;
        for(j=0;j<5;j++)
        {
            {
                db.oM[i][j]=Tdb.oTm[tmp][j];
            }
        }
    }
    for(i=0;i<20;i++)
    {
        tmp=i*2;
        for(j=0;j<5;j++)
        {
            {
                db.eM[i][j]=Tdb.eTm[tmp][j];
            }
        }
    }
}
void feedTape(FILE *fDb,FILE *fDb2)
{
    int i,j,k,tmpC,l=-1;
    if(db.n==200)
    {
        printf("RTL is Full.No Further Operation is performed\n");
    }
    else
        {
            printf("Enter number of Tape you want to feed\n");
            scanf("%d",&db.nIP);
            while(db.nIP%10!=0)
            {
                printf("Enter only in multiples of 10\n");
                scanf("%d",&db.nIP);
            }

            k=db.nIP/10;
            db.count=10;
            genBarcode();
            cpyStackVal();
            while(db.count!=0 && k!=0)
                {
                    if(db.on!=100)
                       {
                            tmpC=db.count;
                            while(db.count!=0)
                            {
                                if(tmpC==10)
                                {
                                  for(i=9;i>=0;i--)
                                    {
                                       if(db.on!=100)
                                        {
                                            detPos();
                                            Tdb.oTm[db.posi][db.posj]=db.inp1[i];
                                            db.inp1[i]=1000000000;
                                            checkStatus();
                                            saveCValue(fDb,fDb2);
                                            //Sleep(2000);
                                            showRTLwIO(fDb,fDb2);
                                            db.on++;
                                            db.n=db.en+db.on;
                                            getch();
                                            db.count--;
                                            //db.x--;
                                        }
                                        else if(db.en!=100)
                                        {
                                            detPos();
                                            Tdb.eTm[db.posi][db.posj]=db.inp1[i];
                                            db.inp1[i]=1000000000;
                                            checkStatus();
                                            saveCValue(fDb,fDb2);
                                            Sleep(2000);
                                            showRTLwIO(fDb,fDb2);
                                            db.en++;
                                            db.n=db.en+db.on;
                                            //getch();
                                            db.count--;
                                            db.x--;
                                        }
                                    }
                                    //delTemp();
                                }
                            }
                       }
                    else if(db.on==100)
                    {
                            tmpC=db.count;
                            while(db.count!=0)
                            {
                                if(tmpC==10)
                                {
                                  for(i=9;i>=0;i--)
                                    {
                                        if(db.en!=100)
                                        {
                                            detPos();
                                            Tdb.eTm[db.posi][db.posj]=db.inp1[i];
                                            db.inp1[i]=1000000000;
                                            checkStatus();
                                            saveCValue(fDb,fDb2);
                                            Sleep(2000);
                                            showRTLwIO(fDb,fDb2);
                                            //getch();
                                            db.en++;
                                            db.n=db.en+db.on;
                                            db.count--;
                                            db.x--;
                                        }
                                        else if(db.on!=100)
                                        {
                                            detPos();
                                            Tdb.oTm[db.posi][db.posj]=db.inp1[i];
                                            db.inp1[i]=1000000000;
                                            checkStatus();
                                            saveCValue(fDb,fDb2);
                                            Sleep(2000);
                                            showRTLwIO(fDb,fDb2);
                                            //getch();
                                            db.on++;
                                            db.n=db.en+db.on;
                                            db.count--;
                                            db.x--;
                                        }

                                    }
                                    //delTemp();
                                }

                        }
                    }
                    if(k!=0)
                    {
                     k--;
                    }
                    if(k!=0)
                    {
                     db.count=10;
                     genBarcode();
                     cpyStackVal();
                    }
                }
           //}
        }
}

void saveBC(int x,int serNo,int tTape)
{
   FILE *tmp1;

   if(db.count==10)  db.count=0;
   tmp1=fopen("tmp1.txt","w+");
   if(tmp1==NULL){ printf("Unable perform Unload Operation\n"); getch();}

   fprintf(tmp1,"%d%.3d%.3d%.3d ",x,serNo,tTape,db.count+1);
   fclose(tmp1);
}
void loadBC()
{
    FILE *tmp1;
    unsigned long int d;
    tmp1=fopen("tmp1.txt","r+");
    if(tmp1==NULL){ printf("Unable perform Unload Operation\n"); getch();}

    fscanf(tmp1,"%d",&db.bc);
    fclose(tmp1);
}
void unloadPos()
{
    int i,j;
    db.status=0;
    db.status1=0;
    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            if(Tdb.oTm[i][j]==retBC())
            {
                db.status++;
                db.posi=i;
                db.posj=j;
            }
        }
    }
    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            if(Tdb.eTm[i][j]==retBC())
            {
                db.status1++;
                db.posi=i;
                db.posj=j;
            }
        }
    }
}

void unloadStat()
{
    int i,j;
    db.status=0;
    db.status1=0;
    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            if(Tdb.oTm[i][j]==retBC())
            {
                db.status++;
                db.posi=i;
                db.posj=j;
            }
        }
    }
    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            if(Tdb.eTm[i][j]==retBC())
            {
                db.status1++;
                db.posi=i;
                db.posj=j;
            }
        }
    }
}
void detPosC()
{
    int i,j;
    db.status=0;
    db.status1=0;
    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            if(i==0 || i%2==0)
            {
                printf("%d\n",retBC());
                if(db.oM[i][j]==retBC())
                {
                    db.status++;
                    db.posi++;
                    db.posj++;
                }
            }
        }
    }
    for(i=0;i<39;i++)
    {
        for(j=0;j<5;j++)
        {
            if(i==0 || i%2==0)
            {
                if(Tdb.oTm[i][j]==retBC())
                {
                    db.status1++;
                    db.posi++;
                    db.posj++;
                }
            }
        }
    }

}
void unLoad(FILE *fDb,FILE *fDb2)
{
    int i,j,tTape,serNo,x,x1,k=0;
    db.status=0;db.status1=0;
    char xBC[14];
    FILE *tmp1;
    printf("Enter the Serial of Your First Catridge on which you want to perform IO Operation\n");
    scanf("%d",&db.bc);
    db.cBc=db.bc;
    printf("\n");

    db.count=-1;
    for(i=0;i<10;i++)
     {
        db.count++;
        unloadPos();
        if(db.status==1)
        {
          Tdb.oTm[db.posi][db.posj]=1000000000;
          checkStatus(); //check Status of temp matrix
          saveCValue(fDb,fDb2); //save all value in temp matrix
          db.inp1[i]=retBC();
          Sleep(2000);
          showRTLwIO(fDb,fDb2);
          db.on--;
        }
     }
    if(i==10)
    {
        updateIO();
        itoa(db.cBc,xBC,10);
        strcat(xBC,".txt");
        remove(xBC);
    }
    db.count=-1;
    for(i=0;i<10;i++)
     {
        db.count++;
        unloadPos();
        if(db.status1==1)
        {
          Tdb.eTm[db.posi][db.posj]=1000000000;
          checkStatus(); //check Status of temp matrix
          saveCValue(fDb,fDb2); //save all value in temp matrix
          db.inp1[i]=retBC();
          Sleep(2000);
          showRTLwIO(fDb,fDb2);
          db.en--;
        }
     }
    if(i==10)
    {
        updateIO();
        itoa(db.cBc,xBC,10);
        strcat(xBC,".txt");
        remove(xBC);
    }
}
void dp()
{
    int i,j,tTape,serNo,x,x1,k=0;
    db.status=0;db.status1=0;
    FILE *fDb,*fDb2;
    char xBC[14];
    FILE *tmp1;
    db.bc=db.inp1[0];
    db.cBc=db.bc;
    printf("\n");

    db.count=-1;
    for(i=0;i<10;i++)
     {
        db.count++;
        unloadPos();
        if(db.status==1)
        {
          Tdb.oTm[db.posi][db.posj]=1000000000;
          checkStatus(); //check Status of temp matrix
          saveCValue(fDb,fDb2); //save all value in temp matrix
          db.inp1[i]=retBC();
          Sleep(2000);
          showRTLwIO(fDb,fDb2);
          db.on--;
        }
     }
    if(i==10)
    {
        updateIO();
        itoa(db.cBc,xBC,10);
        strcat(xBC,".txt");
        remove(xBC);
    }
    db.count=-1;
    for(i=0;i<10;i++)
     {
        db.count++;
        unloadPos();
        if(db.status1==1)
        {
          Tdb.eTm[db.posi][db.posj]=1000000000;
          checkStatus(); //check Status of temp matrix
          saveCValue(fDb,fDb2); //save all value in temp matrix
          db.inp1[i]=retBC();
          Sleep(2000);
          showRTLwIO(fDb,fDb2);
          db.en--;
        }
     }
    if(i==10)
    {
        updateIO();
        itoa(db.cBc,xBC,10);
        strcat(xBC,".txt");
        remove(xBC);
    }
}
void driveProcess()
{
    int i,j;
    char xBC[14];
    char a[3];
    FILE *tmp,*fDb,*fDb2;
    printf("Enter the Serial of Your First Catridge on which you want to Processing\n");
    scanf("%d",&db.bc);

    db.cBc=db.bc;
    itoa(db.cBc,xBC,10);
    strcat(xBC,".txt");

    tmp=fopen(xBC,"a+");
    if(tmp==NULL) printf("Unable to find your Catridge\n");

    for(i=0;i<10;i++)
    {
        showRTLwIO(fDb,fDb2);
        fscanf(tmp,"%d",&db.inp1[i]);
        Sleep(2000);
        showRTLwIO(fDb,fDb2);
    }
    fclose(tmp);

    printf("\t\t\t\t\t\t\tAre You Want to perform UNLOAD OPERATION ON THIS SLOT\n");
    printf("\t\t\t\t\t\t\t\t\t\t");
    scanf("%s",a);
    if(strcmp(a,"Yes")==0)
    {
        dp();
    }
    else
    {
        for(i=9;i>=0;i--)
        {
            showRTLwIO(fDb,fDb2);
            db.inp1[i]=1000000000;
            Sleep(2000);
            showRTLwIO(fDb,fDb2);
        }
    }
}
int main()
{
    FILE *fDb,*fDb2;
    int ch;
    checkCounter(fDb,fDb2);
    while(1)
    {
        printf("\n1.Show Present State of RTL\n");
        printf("2.Show IO Stack\n");
        printf("3.Feed Catridges\n");
        printf("4.Drive Prosessing\n");
        printf("5.Unload Catridges\n");
        printf("6.Reset RTL\n");
        printf("7.Close\n\n");
        printf("Enter the choice\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:showRTL(fDb,fDb2);
                    break;
            case 2:showRTLwIO(fDb,fDb2);
                    break;
            case 3:feedTape(fDb,fDb2);
                    break;
            case 4:driveProcess();
                    break;
            case 5:unLoad(fDb,fDb2);
                    break;
            case 6:initialize(fDb,fDb2);
                    break;
            case 7:exit(0);
                    break;
            default:printf("Wrong choice\n");
                    break;
        }
    }
    return 0;
}
