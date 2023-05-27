#include <bits/stdc++.h>
using namespace std;

using namespace std;

/// Vertex Dependency Process
class VertexDecomposition
{
public:
	static set<vector<Dcel *>> vertex_decomposition(vector<pair<double, double>> vecx);
};
set<vector<Dcel *>> VertexDecomposition::vertex_decomposition(vector<pair<double, double>> vecx)
{
	/// OS <- Phi ; CARD <- Infinite ; s <- 1
	set<vector<Dcel *>> OS;
	long long CARD = INT_MAX;
	long long s = 1;

	/// While s <= n do
	while (s <= vecx.size())
	{
		/// Decompose the polygon into convex polygons using v(s) as initial vertex
		vector<Dcel *> DS = Algorithm1::algorithm1(vecx);

		/// If |D(s)| = CARD then OS <- OS U D(s)
		if (DS.size() == CARD)
		{
			OS.insert(DS);
		}

		/// else if |D(s)| < CARD then OS <- {D(s)}; CARD <- |D(s)|
		else if (DS.size() < CARD)
		{
			OS.clear();
			OS.insert(DS);
			CARD = DS.size();
		}

		/// s <- s + 1;
		s = s + 1;
		Dcel *PrevPS = DS[0];

		/// NewFirstPolygon <- false
		bool NewFirstPolygon = false;

		/// While not NewFirstPolygon and s <= n do
		while (!NewFirstPolygon and s <= vecx.size())
		{
			vecx.push_back(vecx[0]);
			vecx.erase(vecx.begin());

			/// Generate P(s)
			vector<Dcel *> PS = Algorithm1::algorithm1(vecx, true);
			/// If P(s) !=  P(s-1) then NewFirstPolygon <- true
			NewFirstPolygon = !(PS[0]->compare_dcel(PrevPS));

			/// else s <- s + 1
			if (!NewFirstPolygon)
			{
				s = s + 1;
				PrevPS = PS[0];
			}
		}
	}
	return OS;
}
