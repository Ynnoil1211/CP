// Arup Guha
// 3/10/2024
// Solution to 2023/4 NAQ Problem D: Garden of Thorns

import java.util.*;

public class D_Garden {

	public static int w;
	public static int h;
	
	public static void main(String[] args) {

		// Get basic information.
		Scanner stdin = new Scanner(System.in);
		int n = stdin.nextInt();
		int r = stdin.nextInt();
		w = stdin.nextInt();
		h = stdin.nextInt();
		
		// Add in the contribution of each circle.
		double res = 0;
		for (int i=0; i<n; i++) {
			int x = stdin.nextInt();
			int y = stdin.nextInt();
			int v = stdin.nextInt();
			double area = getArea(x, y, r);
			res += v*area/(w*h);
		}
		
		// Ta da!
		System.out.printf("%.15f\n",res);
	}
	
	public static double getArea(int x, int y, int r) {
	
		// Whole circle
		if (x>=r && y>=r && w-x>=r && h-y>=r) return Math.PI*r*r;
		
		// Whole rectangle
		if (r*r >= x*x+y*y && r*r >= (w-x)*(w-x)+y*y && r*r >= (w-x)*(w-x)+(h-y)*(h-y) && r*r >= x*x+(h-y)*(h-y))
			return w*h;
			
		ArrayList<double[]> pts = new ArrayList<double[]>();
		
		double res = 0;
		
		// Look up. If it's a triangle, add it.
		if (h-y < r) {
			double dx = Math.sqrt(r*r - (h-y)*(h-y));
			double x1 = Math.max(0, x-dx);
			double x2 = Math.min(w, x+dx);
			pts.add(new double[]{x2,h});
			pts.add(new double[]{x1,h});
			res += (x2-x1)*(h-y)*.5;
		}
		
		// Look left. Same here.
		if (x < r) {
			double dy = Math.sqrt(r*r - x*x);
			double y1 = Math.max(0, y-dy);
			double y2 = Math.min(h, y+dy);
			pts.add(new double[]{0, y2});
			pts.add(new double[]{0, y1});
			res += (y2-y1)*x*.5;
		}
		
		// Look down. And here.
		if (y < r) {
			double dx = Math.sqrt(r*r - y*y);
			double x1 = Math.max(0, x-dx);
			double x2 = Math.min(w, x+dx);
			pts.add(new double[]{x1,0});
			pts.add(new double[]{x2,0});
			res += (x2-x1)*y*.5;
		}
		
		// Look right. And here.
		if (w-x < r) {
			double dy = Math.sqrt(r*r - (w-x)*(w-x));
			double y1 = Math.max(0, y-dy);
			double y2 = Math.min(h, y+dy);
			pts.add(new double[]{w, y1});
			pts.add(new double[]{w, y2});
			res += (y2-y1)*(w-x)*.5;
		}
		
		/*** Some sectors aren't included ***/
		// Now, look between triangles for sectors.
		for (int i=1; i<pts.size(); i+=2) {
			
			// Get the two angles from center.
			double a1 = Math.atan2(y-pts.get(i)[1], x-pts.get(i)[0]);
			int idx = (i+1)%pts.size();
			double a2 = Math.atan2(y-pts.get(idx)[1], x-pts.get(idx)[0]);
			
			// Screens out duplicate points.
			if (Math.abs(a1-a2) < 1e-9) continue;
			
			// Fix angle, if necessary.
			if (a2 < a1) a2 += 2*Math.PI;
			
			// Add sector area.
			res += (a2-a1)*r*r*.5;
		}
		
		return res;
	}
}
