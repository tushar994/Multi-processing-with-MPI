#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <iomanip> 
#include <map>
#include <iterator>
#include <mpi.h>


using namespace std;

int three =0;
int four=0;

int printer(vector <int> p){
    for(int i=0;i<p.size();i++){
        cout<<p[i]<<" ";
    }
    cout<<"\n";
    return 0;
}

int dfs(vector <vector <int> > x, int start, int current, vector <int> cur){
    
    cur.push_back(current);

    if(cur.size()>4){
        return 0;
    }
    for(int i=0;i<x[current].size();i++){
        
        if(x[current][i]==start){
            if(cur.size()==3){
                three++;

            }
            else if(cur.size()==4){
                four++;
            }
        }
        else if(x[current][i]>start){


            int flag = 1;
            for(int j=0;j<cur.size();j++){
                if(x[current][i]==cur[j]){

                    flag = 0;
                    break;
                }
            }
            if(flag==1){
                dfs(x,start,x[current][i], cur);
            }
        }
    }
    return 0;

}

int main(int argc, char ** argv){
    int rank;
    MPI_Status status;

    int n;
    int e;
    vector <vector <int> >x;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank==0){
        cin>>n;
        cin>>e;
        vector < int> emp;
        x.resize(n);
        for(int i=0;i<e;i++){
            int a,b;
            cin>>a>>b;
            a--;
            b--;
            x[a].push_back(b);
            x[b].push_back(a);
        }
        int index = 0;
        for(int i=1;i<4;i++){
            MPI_Send (&n ,1, MPI_INT, i, index, MPI_COMM_WORLD);
        }
        index++;
        for(int i=1;i<4;i++){
            index = 1;
            for(int j=0;j<n;j++){
                int a = x[j].size();
                MPI_Send (&a ,1, MPI_INT, i, index, MPI_COMM_WORLD);
                index++;
                MPI_Send( &x[j][0],a,MPI_INT, i, index, MPI_COMM_WORLD);
                index++;
            }
        }
    }
    else{
        int index = 0;
        MPI_Recv (&n, 1, MPI_INT, 0, index, MPI_COMM_WORLD, &status);

        index++;
        x.resize(n);
        for(int i=0;i<n;i++){
            int a;
            MPI_Recv (&a, 1, MPI_INT, 0, index, MPI_COMM_WORLD, &status);
            index++;
            x[i].resize(a);
            MPI_Recv (&x[i][0], a, MPI_INT, 0, index, MPI_COMM_WORLD, &status);
            index++;
        }

    }

    for(int i=rank*(n/4);i<min((rank+1*n)/4,n);i++){
        vector <int> cur;
        dfs(x,i,i, cur);
    }

    if(rank==0){
        for(int i=1;i<4;i++){
            int k,l;

            MPI_Recv (&k, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);

            MPI_Recv (&l, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
            three+=k;
            four+=l;
        }
        cout<<three/2<<" "<<four/2<<"\n";
    }
    else{

        MPI_Send (&three ,1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send (&four ,1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize(); 
    return 0;

}