// Group Details:
// 1. Abhinav Verma 2020A7PS1093H
// 2. Anupam Singh 2020A7PS0203H
// 3. Darshan Chandak 2020A7PS2085H
// 4. Sahil Bhore 2020A7PS2065H

#include <bits/stdc++.h>
#include <chrono>
#include <ctime>
#include "dcel.h"
#include "auxiliary_class.h"
#include "algo1.h"
#include "merging.h"
#include "VDP.h"

using namespace std;

int main()
{
    auto start_algo1 = chrono::system_clock::now();
    ifstream input_file;
    input_file.open("input.txt");
    long long size_polygon;
    input_file >> size_polygon;
    vector<pair<double, double>> vecx;
    double temp1;
    double temp2;
    for (long long i = 0; i < size_polygon; i++)
    {
        input_file >> temp1;
        input_file >> temp2;
        vecx.push_back({temp1, temp2});
    }
    input_file.close();
    set<vector<Dcel *>> set_vecy = VertexDecomposition::vertex_decomposition(vecx);
    vector<Dcel *> vecy = *set_vecy.begin();
    auto end_vdp = chrono::system_clock::now();
    auto start_merging = chrono::system_clock::now();
    Merging::merging(vecy, vecx);
    ofstream output_file;
    output_file.open("output.txt");
    for (long long i = 0; i < vecy.size(); i++)
    {
        vector<Vertex *> vecz = vecy[i]->get_Vertices();
        output_file << vecz.size() << "\n";
        for (long long j = 0; j < vecz.size(); j++)
        {
            output_file << vecz[j]->get_coordinates().first << " " << vecz[j]->get_coordinates().second << "\n";
        }
    }
    output_file.close();
    for (long long i = 0; i < vecy.size(); i++)
    {
        vector<Vertex *> vecz = vecy[i]->get_Vertices();
        cout << "Polygon No: " << i + 1 << " No of vertices: " << vecz.size() << "\n\n";
        for (long long j = 0; j < vecz.size(); j++)
        {
            cout << vecz[j]->get_coordinates().first << " " << vecz[j]->get_coordinates().second << "\n";
        }
        cout << "\n";
    }
    auto end_merging = chrono::system_clock::now();
    chrono::duration<double> elapsed_time_algo1_vdp = end_vdp - start_algo1;
    chrono::duration<double> elapsed_time_merging = end_merging - start_merging;
    cout << "Elapsed Time in Decomposition: " << elapsed_time_algo1_vdp.count() << "s" << endl;
    cout << "Elapsed Time in Merging: " << elapsed_time_merging.count() << "s" << endl;
    cout << "Total Elapsed Time: " << elapsed_time_algo1_vdp.count() + elapsed_time_merging.count() << "s" << endl;
}