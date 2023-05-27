#include <bits/stdc++.h>
using namespace std;

class Algorithm1
{
public:
	static vector<Dcel *> algorithm1(vector<pair<double, double>> vecx, bool is_first_polygon);
};

vector<Dcel *> Algorithm1::algorithm1(vector<pair<double, double>> vecx, bool is_first_polygon = false)
{

	vector<Dcel *> final_ans;
	/// Read in clockwise order the vertices vi and store them in a Dcel P - v1, v2 . . vn 
	Dcel *P = new Dcel();
	P->create_dcel(vecx);

	/// L0 <- {v1} ; m <- 1 

	long long m = 1;
	///While n > 3 do (Begin MP1) 
	long long n = P->get_size();
	while (n >= 3)
	{
		/// fun(P);
		/// cout<<"Above P\n";
		Dcel *L = new Dcel();

		vector<pair<double, double>> temp;
		temp.push_back(P->get(0)->get_coordinates());
		L->create_dcel(temp);

		/*v1 <- Last[Lm-1] v2<-Next[P,v1]*/
		Vertex *v1 = L->get_last();
		Vertex *v2 = P->next_element(v1);

		Vertex *v_1 = L->get_last();
		Vertex *v_2 = P->next_element(v_1);
		/// Lm <-{v1 v2}
		/// i<-2
		/// vi+1 <- Next(P, vi)
		L->append(v_2);
		long long i = 2;
		Vertex *v_3 = P->next_element(v_2);

		while (1)
		{
			if (L->get_size() >= n || AuxiliaryClass::get_angle(v_1, v_2, v_3) > 180 || AuxiliaryClass::get_angle(v_2, v_3, v1) > 180 || AuxiliaryClass::get_angle(v_3, v1, v2) > 180)
				break;
			L->append(v_3);

			Vertex *temp_v_1 = P->next_element(v_1);
			Vertex *temp_v_2 = P->next_element(v_2);
			Vertex *temp_v_3 = P->next_element(v_3);
			v_1 = temp_v_1;
			v_2 = temp_v_2;
			v_3 = temp_v_3;
		}
		if (!L->compare_dcel(P))
		{
			vector<pair<double, double>> notches = AuxiliaryClass::obtain_notches(P, L);
			while (notches.size() > 0)
			{
				vector<pair<double, double>> rectangle = AuxiliaryClass::get_smallest_rectangle(L);
				bool backward = false;
				pair<double, double> v;
				while (!backward and notches.size() > 0)
				{
					v = notches[0];
					if (!AuxiliaryClass::inside_rectangle(rectangle, v))
					{
						notches.erase(notches.begin());
					}
					else if (L->get_size() == 2)
					{
						notches.erase(notches.begin());
					}
					else
						break;
				}
				if (notches.size() > 0)
				{
					if (AuxiliaryClass::inside_cyclical_list(L, v))
					{
						AuxiliaryClass::removal_edges(L, v1, v);
						notches.erase(notches.begin());
						backward = true;
					}
					else
					{
						notches.erase(notches.begin());
					}
				}
			}
		}
		if (L->get_last() != v2)
		{

			final_ans.push_back(L);

			if (is_first_polygon)
			{
				return final_ans;
			}

			P->add_edge_partition(L->get_last());
			n = n + 2 - L->get_size();
		}
		else
		{
			P->add_edge_partition(L->get_last());
			n = n + 2 - L->get_size();
		}
		m = m + 1;
	}
	return final_ans;
}
