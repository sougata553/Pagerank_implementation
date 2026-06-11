#include <bits/stdc++.h>
#include "C:\Users\arkak\OneDrive - iitkgp.ac.in\Desktop\PAGE_RANK\includes\matrixhelpers.h"
#include "C:\Users\arkak\OneDrive - iitkgp.ac.in\Desktop\PAGE_RANK\includes\pagerank.h"
using namespace std;

void build_prob_cum(vector<vector<double>> &M){
    int dim=M.size();
    for(int j=0;j<dim;j++){
        double colsum=0.0;
        for (int i=0;i<dim;i++){
            colsum+=M[i][j];
        }
        if(colsum==0.0){
            //dangling node handling
            for(int i=0;i<dim;i++){
                M[i][j]=1.0/dim;
            }
        } else {
            for (int i=0;i<dim;i++){
                M[i][j]/=colsum;
            }
        }
    }
}

vector<double> matVec(vector<vector<double>> &mat, vector<double> &vec){
    int rows=mat.size();
    int cols=vec.size();
    vector<double> res(rows,0.0);
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            res[i]+=mat[i][j]*vec[j];
        }
    }
    return res;
}

double L1_norm(vector<double> &a, vector<double> &b){
    int n=a.size();
    double res=0;
    for(int i=0;i<n;i++){
        res+=abs(a[i]-b[i]);
    }
    return res;
}