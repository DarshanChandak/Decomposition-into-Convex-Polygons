#include <bits/stdc++.h>
#include <cmath>
#include <cmath>
#include <utility>
#include <limits>

using namespace std;

class AuxiliaryClass
{
public:
	///denotes angle between 0 and 360 swept by counterclockwise rotation from line segment ba to bc 
	static double get_angle(Vertex *a, Vertex *b, Vertex *c);

	/// obtain notches in cyclical_list
	static vector<pair<double, double>> obtain_notches(Dcel *dcel1, Dcel *dcel2);

	/// obtain rectangle covering the cyclical_list
	static vector<pair<double, double>> get_smallest_rectangle(Dcel *dcel);

	/// checks whether inside rectangle
	static bool inside_rectangle(vector<pair<double, double>> rectangle, pair<double, double> vertex);

	/// checks whether inside Cyclical List
	static bool inside_cyclical_list(Dcel *dcel, pair<double, double> vertex);

	/// obtain set of vertices of a cyclical list, on the right side of an edge as seen in the direction of the edge
	static bool removal_edges(Dcel *dcel, Vertex *starting_vertex, pair<double, double> inside_vertex);
};
double clockwise_angle(pair<double, double> v1, pair<double, double> v2, pair<double, double> v3)
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
double AuxiliaryClass::get_angle(Vertex *a, Vertex *b, Vertex *c)
{
	double cangle = clockwise_angle(a->get_coordinates(), b->get_coordinates(), c->get_coordinates());
	if (cangle == -1000)
		return 180;
	if (cangle < 0)
	{
		cangle += 360;
	}
	return cangle;
}
vector<pair<double, double>> AuxiliaryClass::obtain_notches(Dcel *dcel1, Dcel *dcel2)
{
	long long comparison = 0;
	long long index = 0;
	vector<pair<double, double>> final_vector1;
	long long prev_index = 0;
	long long next_index = 0;
	while (comparison != dcel1->get_size())
	{

		if (index - 1 < 0)
			prev_index = index - 1 + dcel1->get_size();
		else
			prev_index = index - 1;
		next_index = (index + 1) % (dcel1->get_size());

		if (abs(180.0 - get_angle(dcel1->get(prev_index), dcel1->get(index), dcel1->get(next_index))) < 0.0000001f)
		{
		}
		else if ((get_angle(dcel1->get(prev_index), dcel1->get(index), dcel1->get(next_index))) > 180)
		{
			final_vector1.push_back(dcel1->get(index)->get_coordinates());
		}
		index++;
		comparison++;
	}
	comparison = 0;
	index = 0;
	prev_index = 0;
	next_index = 0;

	vector<pair<double, double>> final_vector;
	for (long long i = 0; i < final_vector1.size(); i++)
	{
		bool flag = false;
		for (long long j = 0; j < dcel2->get_Vertices().size(); j++)
		{
			if (final_vector1[i] == dcel2->get_Vertices()[j]->get_coordinates())
			{
				flag = true;
			}
		}
		if (!flag)
		{
			final_vector.push_back(final_vector1[i]);
		}
	}
	return final_vector;
}
vector<pair<double, double>> AuxiliaryClass::get_smallest_rectangle(Dcel *dcel)
{

	double minx = (dcel->get(0))->get_coordinates().first;
	double maxx = (dcel->get(0))->get_coordinates().first;
	double miny = (dcel->get(0))->get_coordinates().second;
	double maxy = (dcel->get(0))->get_coordinates().second;

	for (long long i = 0; i < dcel->get_size(); i++)
	{
		minx = min(minx, (dcel->get(i))->get_coordinates().first);
		maxx = max(maxx, (dcel->get(i))->get_coordinates().first);
		miny = min(miny, (dcel->get(i))->get_coordinates().second);
		maxy = max(maxy, (dcel->get(i))->get_coordinates().second);
	}
	vector<pair<double, double>> vecx;
	vecx.push_back(make_pair(minx, maxx));
	vecx.push_back(make_pair(miny, maxy));
	return vecx;
}

bool AuxiliaryClass::inside_rectangle(vector<pair<double, double>> rectangle, pair<double, double> vertex)
{

	double x = vertex.first;
	double y = vertex.second;

	if (rectangle[0].first < x && rectangle[0].second > x && rectangle[1].first < y && rectangle[1].second > y)
	{
		return true;
	}
	return false;
}

bool isVertexInsidePolygon(pair<double, double> vertex, vector<pair<double, double>> polygon)
{

	bool isInside = false;
	size_t n = polygon.size();
	for (size_t i = 0, j = n - 1; i < n; j = i++)
	{
		if (((polygon[i].second > vertex.second) != (polygon[j].second > vertex.second)) &&
			(vertex.first < (polygon[j].first - polygon[i].first) * (vertex.second - polygon[i].second) / (polygon[j].second - polygon[i].second) + polygon[i].first))
		{
			isInside = !isInside;
		}
	}
	return isInside;
}
bool AuxiliaryClass::inside_cyclical_list(Dcel *dcel, pair<double, double> vertex)
{
	vector<Vertex *> vertices = dcel->get_Vertices();
	vector<pair<double, double>> polygon;
	for (long long i = 0; i < vertices.size(); i++)
	{
		polygon.push_back(vertices[i]->get_coordinates());
	}
	return isVertexInsidePolygon(vertex, polygon);
}
bool isVectorToRightOfLine(pair<double, double> v1, pair<double, double> vn, pair<double, double> vertex)
{

	if ((vertex.first - v1.first) * (vn.second - v1.second) - (vertex.second - v1.second) * (vn.first - v1.first) >= 0)
	{
		return true;
	}

	return false;
}

bool AuxiliaryClass::removal_edges(Dcel *dcel, Vertex *starting_vertex, pair<double, double> inside_vertex)
{
	vector<Vertex *> vertices = dcel->get_Vertices();
	bool flag = false;
	for (long long i = vertices.size() - 1; i >= 0; i--)
	{
		if (isVectorToRightOfLine(starting_vertex->get_coordinates(), inside_vertex, vertices[i]->get_coordinates()))
		{
			flag = true;
			dcel->remove_vertex(vertices[i]);
		}
		else
		{
			break;
		}
	}
	return flag;
}
