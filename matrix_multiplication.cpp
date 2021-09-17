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

vector <vector <int> > mat_add(vector < vector <int> > x, vector < vector <int> > y){
    vector < vector <int> > ans;
    vector <int> emp;
    for(int i=0;i<std::max(x.size(),y.size());i++){
        ans.push_back(emp);
        for(int j=0;j<std::max(x[i].size(),y[i].size());j++){
            ans[i].push_back(0);
            if(j<x[i].size()){
                ans[i][j]+=x[i][j];
            }
            if(j<y[i].size()){
                ans[i][j]+=y[i][j];
            }
        }
    }
    return ans;
}

int mat_display(vector < vector <int> > a){
    "displaying new \n";
    for(int i=0;i<a.size();i++){
        for(int j=0;j<a[i].size();j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}

vector <vector <int> > mat_multiply(vector <vector <int> > x, vector <vector <int> > y){
    vector < vector <int> > ans;
    vector <int> emp;
    
    
    if(x.size()==1 && x[0].size()==1){

        ans.push_back(emp);
        ans[0].push_back(x[0][0]*y[0][0]);

        return ans;
    }
    else{
        vector < vector  <int>  > a,b,c,d,e,f,g,h;

        for(int i=0;i<x.size()/2;i++){
            a.push_back(emp);
            for(int j=0;j<std::max(1,(int)x[i].size()/2);j++){
                a[a.size()-1].push_back(x[i][j]);
            }
        }

        for(int i=0;i<x.size()/2;i++){
            b.push_back(emp);
            for(int j=std::max(1,(int)x[i].size()/2);j<x[i].size();j++){
                b[b.size()-1].push_back(x[i][j]);
            }
        }

        for(int i=x.size()/2;i<x.size();i++){
            c.push_back(emp);
            for(int j=0;j<std::max(1,(int)x[i].size()/2);j++){
                c[c.size()-1].push_back(x[i][j]);
            }
        }

        for(int i=x.size()/2;i<x.size();i++){
            d.push_back(emp);
            for(int j=std::max(1,(int)x[i].size()/2);j<x[i].size();j++){
                d[d.size()-1].push_back(x[i][j]);
            }
        }


        for(int i=0;i<y.size()/2;i++){
            e.push_back(emp);
            for(int j=0;j<std::max(1,(int)y[i].size()/2);j++){
                e[e.size()-1].push_back(y[i][j]);
            }
        }
        for(int i=0;i<y.size()/2;i++){
            f.push_back(emp);
            for(int j=std::max(1,(int)y[i].size()/2);j<y[i].size();j++){
                f[f.size()-1].push_back(y[i][j]);
            }
        }
        for(int i=y.size()/2;i<y.size();i++){
            g.push_back(emp);
            for(int j=0;j<std::max(1,(int)y[i].size()/2);j++){
                g[g.size()-1].push_back(y[i][j]);
            }
        }
        for(int i=y.size()/2;i<y.size();i++){
            h.push_back(emp);
            for(int j=std::max(1,(int)y[i].size()/2);j<y[i].size();j++){
                h[h.size()-1].push_back(y[i][j]);
            }
        }


        vector < vector <int> > c1,c2,c3,c4;
        c1 = mat_add(mat_multiply(a,e),mat_multiply(b,g));
        c2 = mat_add(mat_multiply(a,f),mat_multiply(b,h));
        c3 = mat_add(mat_multiply(c,e),mat_multiply(d,g));
        c4 = mat_add(mat_multiply(c,f),mat_multiply(d,h));



        for(int i=0;i<std::max(c1.size(),c2.size());i++){
            ans.push_back(emp);
            if(i<c1.size()){
                for(int j=0;j<c1[i].size();j++){
                    ans[i].push_back(c1[i][j]);
                }
            }
            if(i<c2.size()){
                for(int j=0;j<c2[i].size();j++){
                    ans[i].push_back(c2[i][j]);
                }
            }
        }
        for(int i=0;i<c3.size();i++){
            ans.push_back(emp);
            for(int j=0;j<c3[i].size();j++){
                ans[i+c1.size()].push_back(c3[i][j]);
            }
            for(int j=0;j<c4[i].size();j++){
                ans[i+c1.size()].push_back(c4[i][j]);
            }
        }
        return ans;
    }
}






int main(int argc, char ** argv){
    int rank;
    MPI_Status status;

    
    int n;
    vector <vector <int> >x,y;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank==0){
        cin>>n;
        vector < int> emp;
        for(int i=0;i<n;i++){
            x.push_back(emp);
            for(int j=0;j<n;j++){
                int a;
                cin>>a;
                x[i].push_back(a);
            }
        }
        for(int i=0;i<n;i++){
            y.push_back(emp);
            for(int j=0;j<n;j++){
                int a;
                cin>>a;
                y[i].push_back(a);
            }
        }
        for(int i=1;i<4;i++){
            MPI_Send (&n ,1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    else
        MPI_Recv (&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);


    if(n==1){
        if(rank==0){
            cout<<x[0][0]*y[0][0]<<"\n";
        }

    }
    else{
        if(rank==0){
            int index = 1;
            for(int i=0;i<n;i++){
                MPI_Send (&x[i][0] , n, MPI_INT, 1, index, MPI_COMM_WORLD);
                index++;
            }
            for(int i=0;i<n;i++){
                MPI_Send (&y[i][0] , n, MPI_INT, 1, index, MPI_COMM_WORLD);
                index++;
            }
        }
        if(rank==1){
            int index = 1;
            vector <int> emp;
            for(int i=0;i<n;i++){
                x.push_back(emp);
                x[i].resize(n);
                MPI_Recv (&x[i][0], n, MPI_INT, 0, index, MPI_COMM_WORLD, &status);
                index++;
            }
            for(int i=0;i<n;i++){
                y.push_back(emp);
                y[i].resize(n);
                MPI_Recv (&y[i][0], n, MPI_INT, 0, index, MPI_COMM_WORLD, &status);
                index++;
            }
        }
        if (rank <=1) { 
            int index = 1;
            vector <int> emp;
            for(int i=n/2*(rank);i<n/2*(rank+1);i++){
                MPI_Send (&x[i][0] , n/2, MPI_INT, rank+2, index, MPI_COMM_WORLD);
                index++;
            }
            for(int i=n/2*(rank);i<n/2*(rank+1);i++){
                MPI_Send(&x[i][0] +n/2, n/2, MPI_INT, rank+2, index, MPI_COMM_WORLD);
                index++;
            }
            for(int i=0;i<n/2;i++){
                MPI_Send (&y[i][0] + n/2 , n/2, MPI_INT, rank+2, index, MPI_COMM_WORLD);
                index++;
            }
            for(int i=n/2;i<n;i++){
                MPI_Send(&y[i][0] +n/2, n/2, MPI_INT, rank+2, index, MPI_COMM_WORLD);
                index++;
            }
            vector < vector <int> > a,b,e,g;
            for(int i=n/2*(rank);i<n/2*(rank+1);i++){
                a.push_back(emp);
                for(int j=0;j<n/2;j++){
                    a[a.size()-1].push_back(x[i][j]);
                }
            }
            for(int i=n/2*(rank);i<n/2*(rank+1);i++){
                b.push_back(emp);
                for(int j=n/2;j<n;j++){
                    b[b.size()-1].push_back(x[i][j]);
                }
            }
            for(int i=0;i<n/2;i++){
                e.push_back(emp);
                for(int j=0;j<n/2;j++){
                    e[i].push_back(y[i][j]);
                }
            }
            for(int i=n/2;i<n;i++){
                g.push_back(emp);
                for(int j=0;j<n/2;j++){
                    g[g.size()-1].push_back(y[i][j]);
                }
            }

            vector < vector <int> > c1 = mat_add(mat_multiply(a,e),mat_multiply(b,g));
            vector <vector <int> > c2;
            for(int i=0;i<n/2;i++){
                c2.push_back(emp);
                c2[i].resize(n/2);
                MPI_Recv (&c2[i][0], n/2, MPI_INT, rank+2, i, MPI_COMM_WORLD, &status);

            }
            for(int i=0;i<c2.size();i++){
                for(int j=0;j<c2.size();j++){
                    c1[i].push_back(c2[i][j]);
                }
            }
            if(rank == 1){
                for(int i=0;i<n/2;i++){
                    MPI_Send (&c1[i][0], n, MPI_INT, 0, i+2*n+1, MPI_COMM_WORLD);
                }
            }
            if (rank == 0){
                vector < vector <int> >  c3;
                for(int i=0;i<n/2;i++){
                    c3.push_back(emp);
                    c3[i].resize(n);
                    MPI_Recv (&c3[i][0], n, MPI_INT, 1, i+2*n+1, MPI_COMM_WORLD, &status);
                }
                for(int i=0;i<n/2;i++){
                    c1.push_back(c3[i]);
                }
                mat_display(c1);
            }
        }
        else if (rank >1) { 
            int index = 1;
            vector <int> emp;

            vector < vector <int> > a,b,e,g;
            a.resize(n/2);

            for(int i=0;i<n/2;i++){

                a[i].resize(n/2);
                MPI_Recv(&a[i][0], n/2, MPI_INT, rank-2, index, MPI_COMM_WORLD, &status);
                index++;
            }

            b.resize(n/2);
            for(int i=0;i<n/2;i++){

                b[i].resize(n/2);
                MPI_Recv(&b[i][0], n/2, MPI_INT, rank-2, index, MPI_COMM_WORLD, &status);
                index++;
            }

            e.resize(n/2);
            for(int i=0;i<n/2;i++){

                e[i].resize(n/2);
                MPI_Recv(&e[i][0], n/2, MPI_INT, rank-2, index, MPI_COMM_WORLD, &status);
                index++;
            }

            g.resize(n/2);
            for(int i=0;i<n/2;i++){

                g[i].resize(n/2);
                MPI_Recv(&g[i][0], n/2, MPI_INT, rank-2, index, MPI_COMM_WORLD, &status);
                index++;
            }
            
            vector < vector <int> > c1 = mat_add(mat_multiply(a,e),mat_multiply(b,g));
            
            for(int i=0;i<c1.size();i++){
                MPI_Send(&c1[i][0], n/2, MPI_INT, rank-2, i, MPI_COMM_WORLD);
            }
        }
        
        
    }

    MPI_Finalize(); 
    return 0;

}