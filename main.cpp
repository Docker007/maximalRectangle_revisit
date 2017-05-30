#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

namespace std {
    std::ostream & operator<<(std::ostream & os, const std::vector<int> & vec) {
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(os, " "));
	os << std::endl;
	return os;
    }
}

class solution {
public:
    int maximalRectangle(const std::vector<std::string> & matrix) {
	size_t nrow = matrix.size(), ncol = matrix[0].size();
	std::vector<std::vector<int>> rowleft(nrow, std::vector<int>(ncol)), rowright(nrow, std::vector<int>(ncol)), colleft(nrow, std::vector<int>(ncol)), colright(nrow, std::vector<int>(ncol));
	
	for (int j = 0; j < ncol; j++) {
	    rowleft[0][j] = -1;
	    rowright[nrow-1][j] = nrow;
	}
	for (int i = 0; i < nrow; i++) {
	    colleft[i][0] = -1;
	    colright[i][ncol-1] = ncol;
	}
	
	for (int j = 0; j < ncol; j++) {
	    for (int i = 1; i < nrow; i++) {
		if (matrix[i][j] == '0')
		    rowleft[i][j] = i;
		else {
		    int p = i-1;
		    while (p >=0 && matrix[p][j] == '1')
			p = rowleft[p][j];
		    rowleft[i][j] = p;
		}
	    }
	    
	    for (int i = nrow-2; i >= 0; i--) {
		if (matrix[i][j] == '0')
		    rowright[i][j] = i;
		else {
		    int p = i+1;
		    while (p < nrow && matrix[p][j] == '1')
			p = rowright[p][j];
		    rowright[i][j] = p;
		}
	    }
	}

	for (int i = 0; i < nrow; i++) {
	    for (int j = 1; j < ncol; j++) {
		if (matrix[i][j] == '0')
		    colleft[i][j] = j;
		else {
		    int p = j-1;
		    while (p >= 0 && matrix[i][p] == '1')
			p = colleft[i][p];
		    colleft[i][j] = p;
		}
	    }

	    for (int j = ncol-2; j >= 0; j--) {
		if (matrix[i][j] == '0')
		    colright[i][j] = j;
		else {
		    int p = j+1;
		    while (p < ncol && matrix[i][p] == '1')
			p = colright[i][p];
		    colright[i][j] = p;
		}
	    }
	}

	for (int i = 0; i < nrow; i++)
	    for (int j = ncol-2; j >= 0; j--)
		rowleft[i][j] = std::max(rowleft[i][j], rowleft[i][j+1]);
	for (int j = 0; j < ncol; j++)
	    for (int i = nrow-2; i >= 0; i--)
		colleft[i][j] = std::max(colleft[i][j], colleft[i+1][j]);

	for (int i = 0; i < nrow; i++)
	    for (int j = 1; j < ncol; j++)
		rowright[i][j] = std::min(rowright[i][j], rowright[i][j-1]);
	for (int j = 0; j < ncol; j++)
	    for (int i = nrow-2; i >= 0; i--)
		colright[i][j] = std::min(colright[i][j], colright[i][j-1]);
	
	std::cout << "rowleft" << std::endl;
	std::copy(rowleft.begin(), rowleft.end(), std::ostream_iterator<std::vector<int>>(std::cout, ""));
	std::cout << "rowright" << std::endl;
	std::copy(rowright.begin(), rowright.end(), std::ostream_iterator<std::vector<int>>(std::cout, ""));
	std::cout << "colleft" << std::endl;
	std::copy(colleft.begin(), colleft.end(), std::ostream_iterator<std::vector<int>>(std::cout, ""));
	std::cout << "colright" << std::endl;
	std::copy(colright.begin(), colright.end(), std::ostream_iterator<std::vector<int>>(std::cout, ""));
	
	int maxarea = 0;
	for (int i = 0; i < nrow; i++) {
	    for (int j = 0; j < ncol; j++) {
		if (matrix[i][j] == '1') {
		    std::cout << "i = " << i << ", j = " << j << ": "
			      << rowleft[i][j] << ", " << rowright[i][j] << "; " << colleft[i][j] << ", " << colright[i][j]
			      << " -> " << (rowright[i][j]-rowleft[i][j]-1)*(colright[i][j]-colleft[i][j]-1) << std::endl; 
		    maxarea = std::max(maxarea, (rowright[i][j]-rowleft[i][j]-1)*(colright[i][j]-colleft[i][j]-1));
		}
	    }
	}

	return maxarea;
    }
};

int main() {
    std::vector<std::string> matrix{
	"10100",
	    "10111",
	    "11111",
	    "10010"
    };

    solution soln;
    int mArea = soln.maximalRectangle(matrix);
    std::cout << "The area of the largest rectangle is:\n"
	      << mArea << std::endl;
}
