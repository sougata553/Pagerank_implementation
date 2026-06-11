#include <bits/stdc++.h>
#include "C:\\Users\\arkak\\OneDrive - iitkgp.ac.in\\Desktop\\PAGE_RANK\\includes\\matrixhelpers.h"
#include "C:\\Users\\arkak\\OneDrive - iitkgp.ac.in\\Desktop\\PAGE_RANK\\includes\\pagerank.h"

using namespace std;

int main() {
    int numpages, links;
    double damping = 0.85, tolerance = 1e-6;
    int iters = 100;
    
    string input_file = "../data/var_grph.txt"; //input graph file
    string output_file = "../results/var_res.txt"; //output PageRank file

    // Build adjacency matrix from file
    vector<vector<double>> M = build_tx_mat(input_file, numpages, links);

    // cout << "Initial adjacency (transition) matrix:\n";
    // for (auto &row : M) {
    //     for (auto &x : row) cout << x << " ";
    //     cout << "\n";
    // }

    // Normalize to build probability matrix
    build_prob_cum(M);

    // cout << "\nColumn-normalized probability matrix:\n";
    // for (auto &row : M) {
    //     for (auto &x : row) cout << fixed << setprecision(3) << x << " ";
    //     cout << "\n";
    // }

    // Build Google matrix
    vector<vector<double>> G = google_mat(M, damping);

    // cout << "\nGoogle matrix (with damping = " << damping << "):\n";
    // for (auto &row : G) {
    //     for (auto &x : row) cout << fixed << setprecision(3) << x << " ";
    //     cout << "\n";
    // }

    // Compute PageRank
    vector<double> ranks = computePageRank(G, tolerance, iters);

    // Write PageRank values to output file
    writePageRankToFile(ranks, output_file);

    cout << "\nPageRank calculation done. Results saved to " << output_file << endl;
    //display
    cout<<"\nPagerank vector as follows"<<endl;
    for(int i=0;i<ranks.size();i++){
        cout<<"rank of page "<<i<<": "<<ranks[i]<<endl;
    }
    double ker=0;
    for(int i=0;i<ranks.size();i++){
        ker+=ranks[i];
    }
    cout<<"Converging value is : "<<ker<<endl;

    return 0;
}
