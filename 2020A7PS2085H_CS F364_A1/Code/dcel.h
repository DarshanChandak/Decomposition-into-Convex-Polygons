#include <bits/stdc++.h>

using namespace std;

/// class prototyping

class Vertex;
class Edge;
class Face;
class Dcel;

/// global counter
long long ver_count = 1;
long long edge_count = 1;
long long face_count = 1;

class Dcel
{
public:
    /// Collection of vertices, edges, faces
    vector<Vertex *> vertices;
    vector<Edge *> edges;
    vector<Face *> faces;

public:
    /// Populating Dcel
    Dcel *create_dcel(vector<pair<double, double>> initial_vertices);
    /// Get last element
    Vertex *get_last();
    /// Get next element
    Vertex *next_element(Vertex *vertex);
    /// Get next element
    Vertex *prev_element(Vertex *vertex);
    /// get element specified at position i
    Vertex *get(long long i);
    /// append element in the list
    Vertex *append(Vertex *append_vertex);
    /// compare dcel with 'this' class
    bool compare_dcel(Dcel *dcel);
    /// removes the vertex, from the list, rest stays connected
    void remove_vertex(Vertex *vertex);
    /// get size
    long long get_size();
    /// get elements
    vector<Vertex *> get_elements();
    /// replace a cyclical list with other
    void replace(Dcel *dcel2);
    /// add edge and partition
    void add_edge_partition(Vertex *vertex);

    /// set vertices
    void set_Vertices(vector<Vertex *> vertices);
    /// set vertices
    void set_Edges(vector<Edge *> edges);
    /// set vertices
    void set_Faces(vector<Face *> faces);

    /// get vertices
    vector<Vertex *> get_Vertices();
    /// get vertices
    vector<Edge *> get_Edges();
    /// get vertices
    vector<Face *> get_Faces();
};

class Vertex
{
private:
    /// Vertex ID
    long long id;

    /// Co-ordinates
    double x_coordinate, y_coordinate;

    /// Pointer to an edge having vertex with this ID as an origin point
    Edge *incident_edge;

public:
    /// Constructor
    Vertex(long long id, double x, double y, Edge *incidentEdge);

    /// get incident edge
    Edge *get_incidentEdge();

    /// set incident edge
    void set_incidentEdge(Edge *edge);

    pair<double, double> get_coordinates();
};

class Edge
{
private:
    /// Edge ID
    long long id;

    /// Origin vertex
    Vertex *origin_vertex;

    /// Destination Vertex
    Vertex *destination_vertex;

    /// Pointer to twin edge, REMOVE
    Edge *twin;

    /// Pointer to left face : with respect to an observer facing the edge’s direction
    Face *left_face;

    /// Pointer to right face : with respect to an observer facing the edge’s direction
    Face *right_face;

    /// Pointer to next edge
    Edge *next_edge;

    /// Pointer to prev edge
    Edge *prev_edge;

public:
    /// Constructor
    Edge(long long id, Vertex *origin_vertex, Vertex *destination_vertex,
         Edge *twin, Face *left_face, Face *right_face, Edge *next_edge, Edge *prev_edge);
    /// get left face
    Face *get_leftFace();
    /// set left face
    void set_leftFace(Face *face);
    /// get nex edge
    Edge *get_nextEdge();
    /// set next edge
    void set_nextEdge(Edge *edge);
};

class Face
{
private:
    /// Face ID
    long long id;

    /// Edge to which this is incident edge
    Edge *edge;

public:
    Face(long long id, Edge *edge);

    /// get edge
    Edge *get_edge();
    /// set edge
    void set_edge(Edge *edge);
};

/*------------------------------------------------------------------------------------------------*/

void Dcel::set_Vertices(vector<Vertex *> vertices)
{
    this->vertices = vertices;
}

void Dcel::set_Edges(vector<Edge *> edges)
{
    this->edges = edges;
}

void Dcel::set_Faces(vector<Face *> faces)
{
    this->faces = faces;
}

Edge *Vertex::get_incidentEdge()
{
    return incident_edge;
}

pair<double, double> Vertex::get_coordinates()
{
    return make_pair(this->x_coordinate, this->y_coordinate);
}

void Vertex::set_incidentEdge(Edge *edge)
{
    this->incident_edge = edge;
}

Edge *Edge::get_nextEdge()
{
    return this->next_edge;
}

void Edge::set_nextEdge(Edge *edge)
{
    this->next_edge = edge;
}

Face *Edge::get_leftFace()
{
    return this->left_face;
}

void Edge::set_leftFace(Face *face)
{
    this->left_face = face;
}

Edge *Face::get_edge()
{
    return this->edge;
}

void Face::set_edge(Edge *edge)
{
    this->edge = edge;
}

vector<Vertex *> Dcel::get_Vertices()
{
    return this->vertices;
}

vector<Edge *> Dcel::get_Edges()
{
    return this->edges;
}

vector<Face *> Dcel::get_Faces()
{
    return this->faces;
}

/*------------------------------------------------------------------------------------------------*/

long long Dcel::get_size()
{
    return this->vertices.size();
}

vector<Vertex *> Dcel::get_elements()
{
    return this->vertices;
}

void Dcel::replace(Dcel *dcel2)
{
    this->vertices = dcel2->get_Vertices();
    this->edges = dcel2->get_Edges();
    this->faces = dcel2->get_Faces();
}

Dcel *Dcel::create_dcel(vector<pair<double, double>> initial_vertices)
{

    /// Dcel *dcel = new Dcel();

    if (initial_vertices.size() == 1)
    {
        Vertex *vertex1 = new Vertex(ver_count++, initial_vertices[0].first, initial_vertices[0].second, NULL);
        Edge *inc_edge = new Edge(edge_count++, vertex1, vertex1, NULL, NULL, NULL, NULL, NULL);
        Face *face = new Face(face_count++, inc_edge);
        vertex1->set_incidentEdge(inc_edge);
        face->set_edge(inc_edge);
        inc_edge->set_leftFace(face);
        inc_edge->set_nextEdge(inc_edge);
        this->vertices.push_back(vertex1);
        this->edges.push_back(inc_edge);
        this->faces.push_back(face);

        return this;
    }

    else if (initial_vertices.size() == 2)
    {
        Vertex *vertex1 = new Vertex(ver_count++, initial_vertices[0].first, initial_vertices[0].second, NULL);
        Vertex *vertex2 = new Vertex(ver_count++, initial_vertices[1].first, initial_vertices[1].second, NULL);
        Edge *inc_edge = new Edge(edge_count++, vertex1, vertex2, NULL, NULL, NULL, NULL, NULL);
        Face *face = new Face(face_count++, inc_edge);
        vertex1->set_incidentEdge(inc_edge);
        face->set_edge(inc_edge);
        inc_edge->set_leftFace(face);
        this->vertices.push_back(vertex1);
        this->edges.push_back(inc_edge);
        this->faces.push_back(face);
        Edge *inc_edge1 = new Edge(edge_count++, vertex2, vertex1, NULL, NULL, NULL, NULL, NULL);
        Face *face1 = new Face(face_count++, inc_edge1);
        vertex2->set_incidentEdge(inc_edge1);
        face1->set_edge(inc_edge1);
        inc_edge1->set_leftFace(face1);
        this->vertices.push_back(vertex2);
        this->edges.push_back(inc_edge1);
        this->faces.push_back(face1);
        inc_edge->set_nextEdge(inc_edge1);
        inc_edge1->set_nextEdge(inc_edge);
        return this;
    }

    for (long long i = 0; i < initial_vertices.size() - 1; i++)
    {
        if (i > 1)
        {
            Edge *prev = edges[i - 2];
            Edge *next = edges[i - 1];
            prev->set_nextEdge(next);
        }
        Vertex *vertex1 = new Vertex(ver_count++, initial_vertices[i].first, initial_vertices[i].second, NULL);
        Vertex *vertex2 = new Vertex(ver_count++, initial_vertices[i + 1].first, initial_vertices[i + 1].second, NULL);
        Edge *inc_edge = new Edge(edge_count++, vertex1, vertex2, NULL, NULL, NULL, NULL, NULL);
        Face *face = new Face(face_count++, inc_edge);
        vertex1->set_incidentEdge(inc_edge);
        face->set_edge(inc_edge);
        inc_edge->set_leftFace(face);
        this->vertices.push_back(vertex1);
        this->edges.push_back(inc_edge);
        this->faces.push_back(face);
    }
    Vertex *last_vertex = new Vertex(ver_count++, initial_vertices[initial_vertices.size() - 1].first, initial_vertices[initial_vertices.size() - 1].second, NULL);
    Vertex *first_vertex = vertices[0];
    Edge *inc_edge = new Edge(edge_count++, last_vertex, first_vertex, NULL, NULL, NULL, NULL, NULL);
    Face *face = new Face(face_count++, inc_edge);
    last_vertex->set_incidentEdge(inc_edge);
    face->set_edge(inc_edge);
    inc_edge->set_leftFace(face);
    inc_edge->set_nextEdge(edges[0]);
    this->vertices.push_back(last_vertex);
    this->edges.push_back(inc_edge);
    this->faces.push_back(face);

    return this;
}

Vertex *Dcel::get_last()
{
    return this->vertices[this->vertices.size() - 1];
}
Vertex *Dcel::next_element(Vertex *vertex)
{
    for (long long i = 0; i < this->vertices.size(); i++)
    {
        if (this->vertices[i]->get_coordinates() == vertex->get_coordinates())
        {
            if (i + 1 < this->vertices.size())
            {
                return this->vertices[i + 1];
            }
            else
            {
                return this->vertices[0];
            }
        }
    }
}
Vertex *Dcel::prev_element(Vertex *vertex)
{
    for (long long i = 0; i < this->vertices.size(); i++)
    {
        if (this->vertices[i]->get_coordinates() == vertex->get_coordinates())
        {
            if (i - 1 >= 0)
            {
                return this->vertices[i - 1];
            }
            else
            {
                return this->vertices[this->vertices.size() - 1];
            }
        }
    }
}
Vertex *Dcel::get(long long i)
{
    return this->vertices[i % (this->vertices.size())];
}

void Dcel::remove_vertex(Vertex *vertex)
{

    long long n = this->vertices.size();
    long long i = 0;
    while (this->vertices[i]->get_coordinates() != vertex->get_coordinates())
    {
        i++;
    }
    Vertex *prev_ver;
    Edge *previous_edge;
    if (i == 0)
    {
        prev_ver = vertices[n - 1];
        previous_edge = edges[n - 1];
    }
    else
    {
        prev_ver = vertices[i - 1];
        previous_edge = edges[i - 1];
    }
    Vertex *next_ver = vertices[(i + 1) % n];
    Edge *next_edge = edges[(i + 1) % n];

    Edge *edge = new Edge(edge_count++, prev_ver, next_ver, nullptr, nullptr, nullptr, nullptr, nullptr);
    Face *face = new Face(face_count++, edge);
    edge->set_leftFace(face);
    prev_ver->set_incidentEdge(edge);
    previous_edge->set_nextEdge(edge);
    edge->set_nextEdge(next_edge);
    this->vertices.erase(this->vertices.begin() + i);
    this->edges.erase(this->edges.begin() + i);
}

Vertex *Dcel::append(Vertex *append_vertex)
{

    Vertex *prev_vertex = this->vertices[this->vertices.size() - 1];
    Vertex *next_vertex = this->vertices[0];

    Edge *edge = new Edge(edge_count++, prev_vertex, append_vertex, nullptr, nullptr, nullptr, nullptr, nullptr);
    Face *face = new Face(face_count++, edge);

    edge->set_leftFace(face);

    Edge *edge2 = new Edge(edge_count++, append_vertex, next_vertex, nullptr, nullptr, nullptr, nullptr, nullptr);
    Face *face2 = new Face(face_count++, edge2);

    edge2->set_leftFace(face2);

    prev_vertex->set_incidentEdge(edge);
    append_vertex->set_incidentEdge(edge2);

    edge->set_nextEdge(edge2);
    edge2->set_nextEdge(this->vertices[0]->get_incidentEdge());

    this->vertices.insert(this->vertices.begin() + this->vertices.size(), append_vertex);

    this->edges.erase(this->edges.begin() + this->edges.size() - 1);

    this->edges.insert(this->edges.begin() + this->edges.size(), edge);

    this->edges.insert(this->edges.begin() + this->edges.size(), edge2);

    return nullptr;
}

bool Dcel::compare_dcel(Dcel *dcel)
{
    if (dcel->get_Vertices().size() != this->vertices.size())
        return false;

    for (long long i = 0; i < dcel->get_Vertices().size(); i++)
    {
        if (dcel->get_Vertices()[i]->get_coordinates() == this->vertices[i]->get_coordinates())
        {
        }
        else
        {
            return false;
        }
    }
    return true;
}

void fun(Dcel *dcel)
{
    map<pair<double, double>, long long> mp;
}
void Dcel::add_edge_partition(Vertex *vertex)
{

    vector<Vertex *> vecx = this->get_Vertices();
    vector<Vertex *> vecy;
    vector<Vertex *> vecz;

    bool flag = false;
    for (long long i = 0; i < vecx.size(); i++)
    {
        if (vecx[i]->get_coordinates() == vertex->get_coordinates())
        {
            flag = true;
        }
        if (!flag)
        {
            vecy.push_back(vecx[i]);
        }
        else
        {
            vecz.push_back(vecx[i]);
        }
    }
    /// this->remove_vertex(vecy[0]);
    this->append(vecy[0]);
    for (long long i = 0; i < vecy.size(); i++)
    {
        this->remove_vertex(vecy[i]);
    }
}

Face::Face(long long id, Edge *edge)
{
    this->id = id;
    this->edge = edge;
}

Vertex::Vertex(long long id, double x, double y, Edge *incident_edge)
{

    this->id = id;
    this->x_coordinate = x;
    this->y_coordinate = y;
    this->incident_edge = incident_edge;
}

Edge::Edge(long long id, Vertex *origin_vertex, Vertex *destination_vertex,
           Edge *twin, Face *left_face, Face *right_face, Edge *next_edge, Edge *prev_edge)
{
    this->id = id;
    this->origin_vertex = origin_vertex;
    this->destination_vertex = destination_vertex;
    this->twin = twin;
    this->left_face = left_face;
    this->right_face = right_face;
    this->next_edge = next_edge;
    this->prev_edge = prev_edge;
}
