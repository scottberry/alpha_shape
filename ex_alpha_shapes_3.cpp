#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Alpha_shape_3.h>
#include <fstream>
#include <iterator>
#include <list>
#include <cassert>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Gt;
typedef CGAL::Alpha_shape_vertex_base_3<Gt>          Vb;
typedef CGAL::Alpha_shape_cell_base_3<Gt>            Fb;
typedef CGAL::Triangulation_data_structure_3<Vb,Fb>  Tds;
typedef CGAL::Delaunay_triangulation_3<Gt,Tds>       Triangulation_3;
typedef CGAL::Alpha_shape_3<Triangulation_3>         Alpha_shape_3;
typedef Gt::Point_3                                  Point;
typedef Alpha_shape_3::Alpha_iterator                Alpha_iterator;
typedef Alpha_shape_3::Vertex_handle                 Vertex_handle;

int main()
{
  /*
  std::list<Point> lp;
  //read input
  std::ifstream is("./data/bunny_1000");
  int n;
  is >> n;
  std::cout << "Reading " << n << " points " << std::endl;
  Point p;
  for( ; n>0 ; n--)    {
    is >> p;
    lp.push_back(p);
  }
  */

  // construct vertices
  std::list<Point> lp;
  for (auto iit = input.begin(); iit != input.end(); ++iit) {
    Point p(std::get<0>(*iit), std::get<1>(*iit), std::get<2>(*iit));
    lp.push_back(p);
  }

  // compute alpha shape
  Alpha_shape_3 as(lp.begin(),lp.end());
  std::cout << "Alpha shape computed in REGULARIZED mode by default"
        << std::endl;

  // find optimal alpha value
  Alpha_iterator opt = as.find_optimal_alpha(1);
  std::cout << "Optimal alpha value to get one connected component is "
        <<  *opt    << std::endl;
  as.set_alpha(*opt);
  assert(as.number_of_solid_components() == 1);

  // print output vertices
  std::vector<Vertex_handle> vertices;
  //std::ostream_iterator<Vb> out_it (std::cout,", ");
  as.get_alpha_shape_vertices(std::back_inserter(vertices), Alpha_shape_3::REGULAR);
  std::cout << "Nr. vertices: " << vertices.size() << std::endl;
  for (auto oit = vertices.begin(); oit != vertices.end(); ++oit) {
    auto p = (**oit).point();
    output.push_back(std::make_tuple(p.x(), p.y(), p.z()));
    /*
    std::cout << "("
      << p.x() <<","
      << p.y() <<","
      << p.z() <<","
      ")" << std::endl;
      */
  }

  auto funct(std::vector< std::tuple<d,d,d> > const &input,
    std::vector< std::tuple<double,double,double> > &output)
  return 0;
}
