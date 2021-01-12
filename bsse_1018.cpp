#include<iostream>
#include<bits/stdc++.h>
#include <fstream>
using namespace std;


    int n;
    ofstream myfile;
    ofstream myfile1;
    ofstream myfile2;

    char var[]= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};


string NumberToString (int Number ){
     ostringstream ss;
     ss << Number;
     return ss.str();
}

string worstCase (int num, int *min, int*max ){

        double tempNum =  pow(5.0, (double)(num));
        int numTC = (int)tempNum;

        string str="";


         myfile2<<"testid,";
		for(int i=0;i<num;i++) {

			myfile2<<var[i]<<",";
		}

		  myfile2<<"expected value";
		  myfile2<<endl;

        int nominal[num], minP[num], maxM[num];


        for(int i=0; i<num; i++){
            nominal[i]=(max[i]+min[i])/2;
            minP[i]=min[i]+1;
            maxM[i]=max[i]-1;
        }


        int temp [num][5];
        for(int i=0; i<num; i++){
            temp[i][0] = min[i];
            temp[i][1] = max[i];
            temp[i][2] = nominal[i];
            temp[i][3] = minP[i];
            temp[i][4] = maxM[i];
        }

        int cycle[num];
        int count[num];
        int index[num];
        int CI[num];
        for(int i=0; i<num; i++)
        {
            double a = pow(5.0,(i+1));
            double b = pow(5.0, i);
            cycle[i]=(int)a;
            count[i]=0;
            index[i]=0;
            CI[i]=(int)b;
        }

        int v[numTC][num+1];

        for(int i=0; i<numTC; i++)
            {
            v[i][0]=i+1;

            for(int j=0; j<num; j++)
                {

                v[i][j+1] = temp[j][index[j]];

                count[j]++;

                if(count[j]==cycle[j])
                    {
                    count[j]=0;
                    index[j]=0;
                    continue;
                    }


                if(count[j]%CI[j]==0)
                    {
                      index[j]++;
                    }

            }

        }

        for(int i=0; i<numTC; i++)
            {
            for(int j=0; j<=num; j++)
            {
                string s = NumberToString (v[i][j]);
                str.append(s);


                if(j==num)
                {
                    str.append("\n");
                }

                else
                {

                    str.append(",");
                }
            }

        }

        return str;
}


int main(void)
{


    cout<<"Number of parameters:"<<endl;
    cin>>n;

    int input[n][2];

    cout<<"Enter range:"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<2;j++)
        {
            cin>>input[i][j];
        }
    }

     int bvc[4*n+1][n];

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<4*n+1;j++)
            {
                bvc[j][i]=((input[i][0]+input[i][1])/2);

            }
        }

        int in=0;

        for(int i=0;i<n;i++)
        {
            bvc[in][i]=input[i][0];
            in++;
            bvc[in][i]=input[i][0]+1;
            in++;
            bvc[in][i]=input[i][1]-1;
            in++;
            bvc[in][i]=input[i][1];
            in++;
        }




        myfile.open ("bvc.csv");


        myfile<<"testid,";
		for(int i=0;i<n;i++) {

			myfile<<var[i]<<",";
		}
         myfile<<"expected value";
		myfile<<endl;

		 for(int i=0;i<4*n+1;i++)
        {
            myfile<<i+1<<",";
            for(int j=0;j<n;j++)
            {
                myfile<<bvc[i][j]<<",";
            }
                myfile<<endl;
        }

         myfile.close();



       int robust[6*n+1][n];

      for(int i=0;i<n;i++)
        {
            for(int j=0;j<6*n+1;j++)
            {
                robust[j][i]=((input[i][0]+input[i][1])/2);

            }
        }
        int in1=0;

        for(int i=0;i<n;i++)
        {
            robust[in1][i]=input[i][0]-1;
             in1++;
            robust[in1][i]=input[i][0];
             in1++;
            robust[in1][i]=input[i][0]+1;
             in1++;
            robust[in1][i]=input[i][1]-1;
             in1++;
            robust[in1][i]=input[i][1];
             in1++;
            robust[in1][i]=input[i][1]+1;
            in1++;
        }

          myfile1.open ("robust.csv");

       myfile1<<"testid,";
		for(int i=0;i<n;i++) {

			myfile1<<var[i]<<",";
		}
         myfile1<<"expected value";
		myfile1<<endl;

        for(int i=0;i<6*n+1;i++)
        {
           myfile1<<i+1<<",";
            for(int j=0;j<n;j++)
            {
                myfile1<<robust[i][j]<<",";
            }
                myfile1<<endl;
        }

          myfile1.close();


          int min[n], max[n];

          for(int j=0;j<n;j++)
            {
                min[j]=input[j][0];
                max[j]=input[j][1];
            }

            myfile2.open ("worst.csv");
            string str = worstCase(n, min, max);



            myfile2 << str;
            myfile2.close();




 return 0;
}
