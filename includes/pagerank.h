#pragma once
#include <vector>
#include <string>

using namespace std;

//build the graph first (in_matrix adj)
vector<vector<double>>build_tx_mat(const string &filename, int &numpages, int &links);

//build the google_matrix
vector<vector<double>>google_mat(vector<vector<double>> &M, double damping);

//build the pagerank matrix
vector<double> computePageRank(vector<vector<double>> &G, double tolerance, int iters);

//save results in csv
void writePageRankToFile(const vector<double> &PR, const string &filename);