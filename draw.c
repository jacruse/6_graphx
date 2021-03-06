#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "math.h"

struct matrix * generate_person() {
  struct matrix * ret = new_matrix(4, 20);

  //head
  add_circle( ret, 0, 20, 0, 10, 100); 

  //neck
  add_curve( ret, 5, 11.3397459622,
	     5, 9.3397459622,
	     5, 9.3397459622,
	     7, 9.3397459622,
	     100, BEZIER );
  add_curve( ret, -5, 11.3397459622,
	     -5, 9.3397459622,
	     -5, 9.3397459622,
	     -7, 9.3397459622,
	     100, BEZIER );
  add_curve( ret, 7, 9.3397459622,
	     0, 7.5,
	     0, 7.5,
	     -7, 9.3397459622,
	     100, BEZIER );

  //arms
  add_curve( ret, 7, 9.3397459622,
	     22, 9.3397459622,
	     22, 5,
	     37, 5,
	     100, BEZIER );
  add_curve( ret, -7, 9.3397459622,
	     -22, 9.3397459622,
	     -22, 5,
	     -37, 5,
	     100, BEZIER );

  add_curve( ret, 37, 5,
	     42, 5,
	     42, -5,
	     37, -5,
	     100, BEZIER );
  add_curve( ret, -37, 5,
	     -42, 5,
	     -42, -5,
	     -37, -5,
	     100, BEZIER );

  add_curve( ret, 17, -0.6602540378,
	     27, -0.6602540378,
	     27, -5,
	     37, -5,
	     100, BEZIER );
  add_curve( ret, -17, -0.6602540378,
	     -27, -0.6602540378,
	     -27, -5,
	     -37, -5,
	     100, BEZIER );  
  

  //body
  add_curve( ret, 17, -0.6602540378,
	     14.5, -0.6602540378,
	     16, -35.6602540378,
	     17, -35.6602540378,
	     100, BEZIER );
  add_curve( ret, -17, -0.6602540378,
	     -14.5, -0.6602540378,
	     -16, -35.6602540378,
	     -17, -35.6602540378,
	     100, BEZIER );
  add_curve( ret, -17, -35.6602540378,
	     0, -40,
	     0, -40,
	     17, -35.6602540378,
	     100, BEZIER );

  
  //legs
  add_curve( ret, 17, -35.6602540378,
	     17, -58,
	     18.5, -69,
	     20, -80.6602540378,
	     100, BEZIER );
  add_curve( ret, -17, -35.6602540378,
	     -17, -58,
	     -15.5, -69,
	     -14, -80.6602540378,
	     100, BEZIER );

  add_curve( ret, 4.5, -50.6602540378,
	     4.5, -65,
	     6, -73,
	     7.5, -80.6602540378,
	     100, BEZIER );
  add_curve( ret, -4.5, -50.6602540378,
	     -4.5, -65,
	     -3, -73,
	     -1.5, -80.6602540378,
	     100, BEZIER );
  add_curve( ret, -4.5, -50.6602540378,
	     0, -51.5,
	     0, -51.5,
	     4.5, -50.6602540378,
	     100, BEZIER );

  //shoes
  add_curve( ret, -14, -80.6602540378,
	     -7.75, -82,
	     -7.75, -82,
	     -1.5, -80.6602540378,
	     100, BEZIER ); 
  add_curve( ret, 20, -80.6602540378,
	     13.75, -82,
	     13.75, -82,
	     7.5, -80.6602540378,
	     100, BEZIER );

  add_curve( ret, -14, -80.6602540378,
	     -18.5, -83.6602540378,
	     -21, -95.6602540378,
	     -21, -95.6602540378,
	     100, BEZIER );
  add_curve( ret, 7.5, -80.6602540378,
	     3, -83.6602540378,
	     0.5, -95.6602540378,
	     0.5, -95.6602540378,
	     100, BEZIER );
  
  add_curve( ret, -1.5, -80.6602540378,
	     -3, -92.6602540378,
	     -3, -92.6602540378,
	     -21, -95.6602540378,
	     100, BEZIER );
  add_curve( ret, 20, -80.6602540378,
	     18.5, -92.6602540378,
	     18.5, -92.6602540378,
	     0.5, -95.6602540378,
	     100, BEZIER );
  

  return ret;
}

void add_person( struct matrix * edges,
		 double x, double y, double z,
		 double theta , double scale) {

  int i;
  struct matrix * perp = generate_person();
  struct matrix * t = make_rotZ( theta );

  //print_matrix(perp);

  matrix_mult( make_scale( scale, scale, 1 ), t);
  matrix_mult( make_translate( x, y, z), t);

  matrix_mult( t, perp);

  for (i = 0; i < perp->lastcol; i++) {
    add_point(edges, perp->m[0][i], perp->m[1][i], perp->m[2][i]);
  }

}



  
/*======== void add_box() ==========
  Inputs:   struct matrix * edges
            double x
	    double y
	    double z
	    double width
	    double height
	    double depth
  Returns: 

  add the points for a rectagular prism whose 
  upper-left corner is (x, y, z) with width, 
  height and depth dimensions.
  ====================*/
void add_box( struct matrix * edges,
              double x, double y, double z,
              double width, double height, double depth ) {
  //upper left front corner lines
  add_edge(edges, x, y, z, x + width, y, z);
  add_edge(edges, x, y, z, x, y - height, z);
  add_edge(edges, x, y, z, x, y, z + depth);

  //lower right front corner lines
  add_edge(edges, x + width, y - height, z, x, y - height, z);  
  add_edge(edges, x + width, y - height, z, x + width, y, z);  
  add_edge(edges, x + width, y - height, z, x + width, y - height, z + depth);

  //lower left back corner lines
  add_edge(edges, x, y - height, z + depth, x, y - height, z);
  add_edge(edges, x, y - height, z + depth, x, y, z + depth);
  add_edge(edges, x, y - height, z + depth, x + width, y - height, z + depth);

  //upper right back corner lines
  add_edge(edges, x + width, y, z + depth, x + width, y, z);
  add_edge(edges, x + width, y, z + depth, x + width, y - height, z + depth);
  add_edge(edges, x + width, y, z + depth, x, y, z + depth);

}

/*======== void add_sphere() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double cz
	    double r
      int step  
  Returns: 

  adds all the points for a sphere with center 
  (cx, cy, cz) and radius r.

  should call generate_sphere to create the
  necessary points
  ====================*/
void add_sphere( struct matrix * edges, 
                 double cx, double cy, double cz,
                 double r, int step ) {
  int i;
  struct matrix * spher = generate_sphere(cx, cy, cz, r, step);

  for (i = 0; i < spher->lastcol; i++) {
    add_edge(edges, spher->m[0][i], spher->m[1][i], spher->m[2][i], spher->m[0][i] + 1.0, spher->m[1][i], spher->m[2][i]);
  }
  
}

/*======== void generate_sphere() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double cz
	    double r
	    double step  
  Returns: Generates all the points along the surface 
           of a sphere with center (cx, cy, cz) and
	   radius r.
	   Returns a matrix of those points
  ====================*/
struct matrix * generate_sphere(double cx, double cy, double cz,
                                double r, int step ) {
  struct matrix * ret = new_matrix(4, 20);
  struct matrix * mult;
  
  int i;
  double t;

  add_circle(ret, cx, 0, 0, r, step);
  t = (double)1/step;

  for (i = 1; i <= step; i++) {
     
    mult = make_rotX(t * M_PI);
    matrix_mult(mult, ret);
    
    add_circle(ret, cx, 0, 0, r, step);
  }

  matrix_mult( make_translate(0, cy, cz), ret );
    
    
  return ret;
}

/*======== void add_torus() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double cz
	    double r1
	    double r2
	    double step  
  Returns: 

  adds all the points required to make a torus
  with center (cx, cy, cz) and radii r1 and r2.

  should call generate_torus to create the
  necessary points
  ====================*/
void add_torus( struct matrix * edges, 
                double cx, double cy, double cz,
                double r1, double r2, int step ) {
  int i;
  struct matrix * tur = generate_torus(cx, cy, cz, r1, r2, step);

  for (i = 0; i < tur->lastcol; i++) {
    add_edge(edges, tur->m[0][i], tur->m[1][i], tur->m[2][i], tur->m[0][i] + 1.0, tur->m[1][i], tur->m[2][i]);
  }
  
}

/*======== void generate_torus() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double cz
	    double r
	    double step  
  Returns: Generates all the points along the surface 
           of a torus with center (cx, cy, cz) and
	   radii r1 and r2.
	   Returns a matrix of those points
  ====================*/
struct matrix * generate_torus( double cx, double cy, double cz,
                                double r1, double r2, int step ) {
  struct matrix * ret = new_matrix(4, 20);
  struct matrix * mult;
  
  int i;
  double t;

  add_circle(ret, r2, cy, 0, r1, step);
  t = (double)1/step;

  for (i = 1; i <= step; i++) {
     
    mult = make_rotY(t * 2 * M_PI);
    matrix_mult(mult, ret);
    
    add_circle(ret, r2, cy, 0, r1, step);
  }

  matrix_mult( make_translate( cx, 0, cz ), ret );
    
    
  return ret;
}

/*======== void add_circle() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double r
	    double step  
  Returns: 

  Adds the circle at (cx, cy) with radius r to edges
  ====================*/
void add_circle( struct matrix * edges, 
                 double cx, double cy, double cz,
                 double r, int step ) { 
  double x0, y0, x1, y1, t;
  int i;
  x0 = r + cx;
  y0 = cy;

  for (i=1; i<=step; i++) {
    t = (double)i/step;
    x1 = r * cos(2 * M_PI * t) + cx;
    y1 = r * sin(2 * M_PI * t) + cy;

    add_edge(edges, x0, y0, cz, x1, y1, cz);
    x0 = x1;
    y0 = y1;
  }
}

/*======== void add_curve() ==========
Inputs:   struct matrix *points
         double x0
         double y0
         double x1
         double y1
         double x2
         double y2
         double x3
         double y3
         double step
         int type  
Returns: 

Adds the curve bounded by the 4 points passsed as parameters
of type specified in type (see matrix.h for curve type constants)
to the matrix points
====================*/
void add_curve( struct matrix *edges, 
                double x0, double y0, 
                double x1, double y1, 
                double x2, double y2, 
                double x3, double y3, 
                int step, int type ) {

  double t, x, y;
  struct matrix *xcoefs;
  struct matrix *ycoefs;
  int i;
  
  xcoefs = generate_curve_coefs(x0, x1, x2, x3, type);
  ycoefs = generate_curve_coefs(y0, y1, y2, y3, type);

  /* print_matrix(xcoefs); */
  /* printf("\n"); */
  /* print_matrix(ycoefs); */

  for (i=1; i<=step; i++) {

    t = (double)i/step;
    x = xcoefs->m[0][0] *t*t*t + xcoefs->m[1][0] *t*t+
      xcoefs->m[2][0] *t + xcoefs->m[3][0];
    y = ycoefs->m[0][0] *t*t*t + ycoefs->m[1][0] *t*t+
      ycoefs->m[2][0] *t + ycoefs->m[3][0];
    
    add_edge(edges, x0, y0, 0, x, y, 0);
    x0 = x;
    y0 = y;
  }
  
  free_matrix(xcoefs);
  free_matrix(ycoefs);
}


/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {

  if ( points->lastcol == points->cols )
    grow_matrix( points, points->lastcol + 100 );
  
  points->m[0][ points->lastcol ] = x;
  points->m[1][ points->lastcol ] = y;
  points->m[2][ points->lastcol ] = z;
  points->m[3][ points->lastcol ] = 1;
  points->lastcol++;
} //end add_point

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  add_point( points, x0, y0, z0 );
  add_point( points, x1, y1, z1 );
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {

 if ( points->lastcol < 2 ) {
   printf("Need at least 2 points to draw a line!\n");
   return;
 }
 
 int point;
 for (point=0; point < points->lastcol-1; point+=2)
   draw_line( points->m[0][point],
	      points->m[1][point],
	      points->m[0][point+1],
	      points->m[1][point+1],
	      s, c);	       
}// end draw_lines









void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  
  int x, y, d, A, B;
  //swap points if going right -> left
  int xt, yt;
  if (x0 > x1) {
    xt = x0;
    yt = y0;
    x0 = x1;
    y0 = y1;
    x1 = xt;
    y1 = yt;
  }
  
  x = x0;
  y = y0;
  A = 2 * (y1 - y0);
  B = -2 * (x1 - x0);  

  //octants 1 and 8
  if ( abs(x1 - x0) >= abs(y1 - y0) ) {

    //octant 1    
    if ( A > 0 ) {
      
      d = A + B/2;      
      while ( x < x1 ) {
	plot( s, c, x, y );
	if ( d > 0 ) {
	  y+= 1;
	  d+= B;
	}
	x++;
	d+= A;
      } //end octant 1 while
      plot( s, c, x1, y1 );
    } //end octant 1

    //octant 8
    else {
      d = A - B/2;
      
      while ( x < x1 ) {
	//printf("(%d, %d)\n", x, y);
	plot( s, c, x, y );
	if ( d < 0 ) {
	  y-= 1;
	  d-= B;
	}
	x++;
	d+= A;
      } //end octant 8 while
      plot( s, c, x1, y1 );
    } //end octant 8
  }//end octants 1 and 8

  //octants 2 and 7
  else {
    
    //octant 2    
    if ( A > 0 ) {
      d = A/2 + B;      

      while ( y < y1 ) {
	plot( s, c, x, y );
	if ( d < 0 ) {
	  x+= 1;
	  d+= A;
	}
	y++;
	d+= B;
      } //end octant 2 while
      plot( s, c, x1, y1 );
    } //end octant 2

    //octant 7
    else {
      d = A/2 - B;
      
      while ( y > y1 ) {
	plot( s, c, x, y );
	if ( d > 0 ) {
	  x+= 1;
	  d+= A;
	}
	y--;
	d-= B;
      } //end octant 7 while
      plot( s, c, x1, y1 );
    } //end octant 7   
  }//end octants 2 and 7  
} //end draw_line
