/*
 * The code below is meant to detect whether the Red Ruby
 * is present. The starategy implemented by the code is not very effective. 
 * Study the code so that you understand what the strategy is and how 
 * it is implemented. Then design and implement a better startegy.
 * 
 * */



#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "camera_x11.h"

//using namespace std;

int main() {
	
	 if (start_camera() != 0) {
        printf("Failed to start camera\n");
        return 1;
    }
   
  // make 1000 runs  
  for (int countrun = 0; countrun < 10000; countrun++) {
	take_picture();
	display_picture();
	int totRed = 0;
	int totGreen = 0;
	int totBlue = 0;
	int totInt = 0;
	double redness = 0.0;
	double greenness = 0.0;
	double blueness = 0.0;
    // for all pixels in latest image
    for (int row = 0 ; row < 480 ; row++) {	
		for (int col = 0; col < 640; col++) {
			uchar r, g ,b ;
			get_pixel(row, col, &r, &g ,&b);
			totRed = totRed + r;
			totGreen = totGreen + g;
			totBlue = totBlue + b;

			totInt = totInt + (r+g+b)/3;
			redness = (double)totRed/(3.0*(double)totInt);
			blueness = (double)totBlue/(3.0*(double)totInt);
			greenness = (double)totGreen/(3.0*(double)totInt);

			// if(redness > 0.3334) {
			// 	 	printf("Red Ruby detected\n");
			// 		break;

			// 	 } else {
			// 	  	printf("Red Ruby not detected\n");
			// 		break;
			// 	  }


		}
	}

	int detect_ruby() {

		int r1 = 150, r2 = 330;   // ROI rows
		int c1 = 200, c2 = 440;   // ROI cols

		int redCount = 0;
		int total = 0;

		for (int row = r1; row < r2; row++) {
			for (int col = c1; col < c2; col++) {

				uchar r, g, b;
				get_pixel(row, col, &r, &g, &b);

				if (r > 150 && r > g + 40 && r > b + 40) {
					redCount++;
				}

				total++;
			}
		}

    double ratio = (double)redCount / (double)total;

    if (ratio > 0.20) {
        return 1;   // ruby present
		Printf("Red Ruby detected\n");
	} else {
		return 0;   // ruby absent
		Printf("Red Ruby not detected\n");
    } 




	printf(" countrun: %d\n",countrun);
	printf(" Total red:%d\n",totRed);
	printf(" Total green:%d\n",totGreen);
	printf(" Total blue:%d\n",totBlue);
	printf(" Total intensity: %d\n",totInt);
	printf("  redness : %f\n", redness);
	printf("  greenness : %f\n", greenness);
	printf("  blueness : %f\n", blueness);
	//sleep1(1000); // slow down a bit to make display easier
	
  }  
  return 0;
}
