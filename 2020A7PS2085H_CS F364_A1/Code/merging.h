#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

/// Merging Process
class Merging
{
public:
    /// The partitioning algorithms discussed earlier generate effective partitions, but as with other partitioning algorithms, these partitions may occasionally include unnecessary diagonals. This means that two convex polygons sharing a diagonal may be combined to create a single polygon. To address this issue, we have created a merging procedure that can be employed following any partitioning process that results in unnecessary diagonals.
    static void merging(vector<Dcel *> dcels, vector<pair<double, double>> vecx);
};
double clockwise_angle_merging(pair<double, double> v1, pair<double, double> v2, pair<double, double> v3)
{
    pair<double, double> v1v2(v2.first - v1.first, v2.second - v1.second);
    pair<double, double> v3v2(v2.first - v3.first, v2.second - v3.second);

    double dot_product = v1v2.first * v3v2.first + v1v2.second * v3v2.second;
    double cross_product = v1v2.first * v3v2.second - v1v2.second * v3v2.first;

    if (dot_product == 0 && cross_product == 0)
    {
        return -1000;
    }

    double angle = atan2(cross_product, dot_product);
    double angle_degrees = angle * 180 / M_PI;
    return angle_degrees;
}
double get_angle_merging(pair<double, double> a, pair<double, double> b, pair<double, double> c)
{
    double cangle = clockwise_angle(a, b, c);
    if (cangle == -1000)
        return 180;
    if (cangle < 0)
    {
        cangle += 360;
    }
    return cangle;
}
void Merging::merging(vector<Dcel *> dcels, vector<pair<double, double>> vecx)

/// NP <- m + 1

/// LDP[i] <- true, LUP[i] <- i; i = 1; . . . ; NP.

/// For j = 1 to m do

///(v(s), v(t)) <- LLE[j]

/// If (|LPv(s)|>2 and |LPv(t)|>2) or (|LPv(s)|>2 and v(t) is convex) or (|LPv(t)|>2 and v(s) is convex) or (v(s) is convex  and v(t) is convex) then

/// j2 <- v(t), i(2) <- v(s), j(3) <- Next[P(j); v(t)], i(1) <- Previous[P(j), v(s)]

/// Find in LPv(t) the only pair (u, v(s)) containing v(s)

/// j(1) <- Previous[P(u), v(t)]; i(3) <-  Next[P(u), v(s)]

/// If ang{(i(1), i(2), i(3), (j(1), j(2), j(3)} <= 180 degree then

/// NP <- NP + 1

/// Write as NPth polygon the polygon obtained merging the polygons with indices LUP[j] and LUP[u]

/// LDP[j]<- false; LDP[u] <- false;LDP[NP] <- true

/// LUP[j] <- NP; LUP[u] <- NP

/// For h = 1 to NP-1 do

/// If LUP[h] = j or LUP[h] = u then

/// LUP[h] <- NP.

{

    vector<pair<pair<double, double>, pair<double, double>>> LLE;
    vector<Dcel *> POLYGON;

    vector<long long> LUP;
    map<pair<double, double>, vector<pair<long long, pair<double, double>>>> LP;
    for (long long i = 0; i < dcels.size(); i++)
    {
        POLYGON.push_back(dcels[i]);
        LLE.push_back({dcels[i]->get_Vertices()[dcels[i]->get_Vertices().size() - 1]->get_coordinates(), dcels[i]->get_Vertices()[0]->get_coordinates()});

        LUP.push_back(i);

        for (long long i = 0; i < vecx.size(); i++)
        {
            for (long long j = 0; j < dcels.size(); j++)
            {
                for (long long k = 0; k < dcels[j]->get_Vertices().size(); k++)
                {
                    if (dcels[j]->get_Vertices()[k]->get_coordinates() == vecx[i])
                    {
                        pair<double, double> next_element = dcels[j]->next_element(dcels[j]->get_Vertices()[k])->get_coordinates();
                        if (next_element != vecx[(i + 1) % vecx.size()])
                        {
                            LP[vecx[i]].push_back({j, next_element});
                        }
                    }
                }
            }
        }
    }

    long long NP = dcels.size();
    map<long long, bool> LDP;
    int dig = NP - 2;
    for (long long j = 0; j < dcels.size(); j++)
    {
        pair<pair<double, double>, pair<double, double>> pr = LLE[j];
        pair<double, double> prev_VT, VT, next_VT, prev_VS, VS, next_VS;
        VT = pr.second;
        VS = pr.first;
        for (long long i = 0; i < vecx.size(); i++)
        {
            if (vecx[i] == VT)
            {
                next_VT = vecx[(i + 1) % vecx.size()];
                prev_VT = vecx[(i - 1 + vecx.size()) % vecx.size()];
            }
            if (vecx[i] == VS)
            {
                next_VS = vecx[(i + 1) % vecx.size()];
                prev_VS = vecx[(i - 1 + vecx.size()) % vecx.size()];
            }
        }
        if ((LP[pr.first].size() > 2 && LP[pr.second].size() > 2) ||
            (LP[pr.first].size() > 2 && get_angle_merging(prev_VT, VT, next_VT) <= 180) ||
            (LP[pr.second].size() > 2 && get_angle_merging(prev_VS, VS, next_VS) <= 180) ||
            (get_angle_merging(prev_VS, VS, next_VS) <= 180 && get_angle_merging(prev_VT, VT, next_VT) <= 180))
        {
            Vertex *J2 = POLYGON[j]->get(0);
            Vertex *I2 = POLYGON[j]->get(POLYGON[j]->get_size() - 1);
            Vertex *J3 = POLYGON[j]->next_element(J2);
            Vertex *I1 = POLYGON[j]->get(POLYGON[j]->get_size() - 2);
            long long u = -1;
            for (long long k = 0; k < LP[POLYGON[j]->get(0)->get_coordinates()].size(); k++)
            {
                if (LP[POLYGON[j]->get(0)->get_coordinates()][k].second == POLYGON[j]->get(POLYGON[j]->get_size() - 1)->get_coordinates())
                {
                    u = LP[POLYGON[j]->get(0)->get_coordinates()][k].first;
                    Vertex *J1 = POLYGON[u]->prev_element(POLYGON[j]->get(0));
                    Vertex *I3 = POLYGON[u]->next_element(POLYGON[j]->get(POLYGON[j]->get_size() - 1));
                    if (AuxiliaryClass::get_angle(I1, I2, I3) <= 180 && AuxiliaryClass::get_angle(J1, J2, J3) <= 180)
                    {
                        NP = NP + 1;
                        LDP[j] = true;
                        LDP[u] = true;
                        LDP[NP] = false;
                        LUP[j] = NP;
                        LUP[u] = NP;
                        for (long long h = 0; h < LUP.size(); h++)
                        {
                            if (LUP[h] == j || LUP[h] == u)
                            {
                                LUP[h] = NP;
                            }
                        }
                    }
                }
            }
        }
    }
    ofstream output_file_merging;
    output_file_merging.open("output_merging.txt");
    for (long long i = 0; i < LUP.size(); i++)
    {
        for (long long j = i + 1; j < LUP.size(); j++)
        {
            if (LUP[i] == LUP[j])
            {
                cout << i + 1 << " " << j + 1 << "\n";
            }
        }
    }
    for (long long i = 0; i < LUP.size(); i++)
    {
        output_file_merging << i + 1 << " " << LUP[i] << "\n";
    }

    output_file_merging.close();

    return;
}