#pragma once
#include <vector>
#include <string>

using namespace std;

//build the cumulative columnwise probability matrix
void build_prob_cum(vector<vector<double>> &M);

//matrix_vector_mult
vector<double> matVec(vector<vector<double>> &mat, vector<double> &vec);

//build the pagerank matrix
double L1_norm(vector<double> &a, vector<double> &b);

//print matrix and vectors for debugging

void printmat(vector<vector<double>>);
void printvec(vector<vector<double>>);

//save results in csv





