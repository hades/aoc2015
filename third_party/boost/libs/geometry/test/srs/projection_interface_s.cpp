// Boost.Geometry
// Unit Test

// Copyright (c) 2017-2022, Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <geometry_test_common.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/srs/epsg.hpp>
#include <boost/geometry/srs/esri.hpp>
#include <boost/geometry/srs/iau2000.hpp>
#include <boost/geometry/srs/projection.hpp>

#include "check_geometry.hpp"

int test_main(int, char*[])
{
    using namespace boost::geometry;
    using namespace boost::geometry::model;
    using namespace boost::geometry::srs;

    typedef point<double, 2, cs::geographic<degree> > point_ll;
    typedef point<double, 2, cs::cartesian> point_xy;

    {
        using namespace boost::geometry::srs::spar;

        point_ll pt_ll(1, 1);
        point_ll pt_ll2(0, 0);
        point_xy pt_xy(0, 0);

        projection<parameters<proj_tmerc, ellps_wgs84, units_m> > prj;

        prj.forward(pt_ll, pt_xy);
        test::check_geometry(pt_xy, "POINT(111308.33561309829 110591.34223734379)", 0.001);

        prj.inverse(pt_xy, pt_ll2);
        test::check_geometry(pt_ll2, "POINT(1 1)", 0.001);
    }

    {
        using namespace boost::geometry::srs::spar;

        projection<parameters<proj_tmerc> > prj1;
        projection<parameters<proj_tmerc, ellps_wgs84> > prj2;
        projection<parameters<proj_tmerc, ellps_wgs84, datum_wgs84> > prj3;
        projection<parameters<proj_tmerc, ellps_wgs84, x_0<>, y_0<> > > prj4
            = parameters<proj_tmerc, ellps_wgs84, x_0<>, y_0<> >(
                proj_tmerc(), ellps_wgs84(), x_0<>(0), y_0<>(0));

        typedef spheroid<double> sph;
        typedef ellps<sph> ell;
        typedef proj_tmerc prj;
        projection<parameters<ell, prj> > prj5
            = parameters<ell, prj>(ell(sph(1000, 999)));
    }

    {
        point_ll pt_ll(1, 1);
        point_ll pt_ll2(0, 0);
        point_xy pt_xy(0, 0);

        projection<static_epsg<2000> > prj;

        prj.forward(pt_ll, pt_xy);
        test::check_geometry(pt_xy, "POINT(9523653.0229229201 246619.70872460317)", 0.001);

        prj.inverse(pt_xy, pt_ll2);
        // TODO: investigate this wierd result
        test::check_geometry(pt_ll2, "POINT(0.99999999979234933 0.99999999988133992)", 0.001);

        projection<static_esri<37001> > prj2;
        projection<static_iau2000<19900> > prj3;
    }

    // compile-time errors
    {
        //point_ll pt_ll(1, 1);
        //point_xy pt_xy(0, 0);

        //projection<spar::parameters<int> > prj1;
        //projection<int> prj2;

        projection<spar::parameters<spar::proj_bacon> > prj3;
        //prj3.inverse(pt_xy, pt_ll);
    }

    return 0;
}
