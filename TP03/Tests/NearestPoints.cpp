#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

using namespace std;

const double MAX_DOUBLE = numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
	this->dmin = dmin;
	this->p1 = p1;
	this->p2 = p2;
}

Result::Result() {
	this->dmin = MAX_DOUBLE;
	this->p1 = Point(0,0);
	this->p2 = Point(0,0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right)
{
	sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(vector<Point> &v, int left, int right)
{
	sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {
	Result res;

	int size = vp.size();

	for(int i = 0; i < size; i++){
	    for(int j = i + 1; j < size; j++){

	        double dist = (vp.at(i)).distance(vp.at(j));

	        if(dist < res.dmin){
	            res.p1 = vp.at(i);
	            res.p2 = vp.at(j);
	            res.dmin = dist;
	        }
	    }
	}

	return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	Result res;
	sortByX(vp, 0, vp.size()-1);

    int size = vp.size();

    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){

            double dist = (vp.at(i)).distance(vp.at(j));

            if(dist < res.dmin){
                res.p1 = vp.at(i);
                res.p2 = vp.at(j);
                res.dmin = dist;
            }
        }
    }

	return res;
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res)
{


    for(int i = left; i < (right + 1); i++){
        for(int j = i + 1; j < (right + 1); j++){

            double dist = (vp.at(i)).distance(vp.at(j));

            if (abs(vp.at(i).y - vp.at(j).y) > res.dmin)
                break;

            else if(dist < res.dmin){
                res.p1 = vp.at(i);
                res.p2 = vp.at(j);
                res.dmin = dist;
            }
        }
    }
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {

    Result res;

    // Base case of two points
	if(right - left == 1){
	    res.p1 = vp.at(left);
	    res.p2 = vp.at(right);
	    res.dmin = (vp.at(left)).distance(vp.at(right));
	    return res;
	}

	// Base case of a single point: no solution, so distance is MAX_DOUBLE
	if(right - left == 0){
        res.p1 = vp.at(left);
        res.p2 = vp.at(right);
	    res.dmin = MAX_DOUBLE;
	    return res;
	}

	// Divide in halves (left and right) and solve them recursively.
    int middle_index = (left + right) / 2;
    Result minLeft, minRight;

    if(numThreads > 1){
        thread t([&vp, &minLeft, left, middle_index, numThreads]{
            minLeft = np_DC(vp, left, middle_index, numThreads/2);
        });
        minRight = np_DC(vp, middle_index + 1, right, numThreads/2);
        t.join();
    }

    else {
        minLeft = np_DC(vp, left, middle_index, numThreads);
        minRight = np_DC(vp, middle_index + 1, right, numThreads);
    }


    // Select the best solution from left and right
    if (minLeft.dmin < minRight.dmin)
        res = minLeft;
    else
        res = minRight;

    int right_index = middle_index, left_index = middle_index;

	// Determine the strip area around middle point
	while(right_index < right && (abs(vp.at(middle_index).x - vp.at(right_index).x) < res.dmin)){
        right_index++;
	}

    while(left_index > left && (abs(vp.at(middle_index).x - vp.at(left_index).x) < res.dmin)){
        left_index--;
    }

	// Order points in strip area by Y coordinate
	sortByY(vp, left_index, right_index);

	// Calculate nearest points in strip area (using npByY function)
	npByY(vp, left_index, right_index, res);

	// Reorder points in strip area back by X coordinate
	sortByX(vp, left_index, right_index);

	return res;
}


/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num)
{
	numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, 1);
}


/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, numThreads);
}
