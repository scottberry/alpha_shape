#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Alpha_shape_3.h>
#include <iterator>
#include <list>
#include <cassert>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Gt;
typedef CGAL::Alpha_shape_vertex_base_3<Gt>          Vb;
typedef CGAL::Alpha_shape_cell_base_3<Gt>            Fb;
typedef CGAL::Triangulation_data_structure_3<Vb,Fb>  Tds;
typedef CGAL::Delaunay_triangulation_3<Gt,Tds>       Triangulation_3;
typedef CGAL::Alpha_shape_3<Triangulation_3>         Alpha_shape_3;
typedef Gt::Point_3                                  Point;
typedef Alpha_shape_3::Vertex_handle                 Vertex_handle;
typedef std::vector< std::tuple<double,double,double> > Tuple_list;

namespace py = pybind11;

Tuple_list filter_vertices(Tuple_list const &input, double alpha)
{
  /* Read input from a list of 3-tuples */
  std::list<Point> lp;
  for (auto iit = input.begin(); iit != input.end(); ++iit) {
    Point p(std::get<0>(*iit), std::get<1>(*iit), std::get<2>(*iit));
    lp.push_back(p);
  }

  // Compute alpha shape
  Alpha_shape_3 as(lp.begin(),lp.end(),alpha,Alpha_shape_3::REGULARIZED);

  // Get vertices from alpha shape
  std::vector<Vertex_handle> vertices;
  as.get_alpha_shape_vertices(
    std::back_inserter(vertices),
    Alpha_shape_3::REGULAR
  );

  // Get coordinates of vertices and store in output
  Tuple_list output;
  for (auto oit = vertices.begin(); oit != vertices.end(); ++oit) {
    auto p = (**oit).point();
    output.push_back(std::make_tuple(p.x(), p.y(), p.z()));
  }

  return output;
}

PYBIND11_MODULE(alpha_shape, m) {
    m.doc() = "CGAL Alpha_Shape_3 minimal interface";
    m.def("filter_vertices", &filter_vertices, "A function which filters a list of vertices depending on whether they form part of the alpha_shape");
}
