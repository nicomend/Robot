/*
 * GridCell.h
 */

#ifndef GridCell_H_
#define GridCell_H_
#include "limits.h"
using namespace std;

class GridCell {
public:
	int row;
	int col;

	GridCell();
	GridCell(int row, int col);

	void operator()(int col, int row) {
		this->col = col;
		this->row = row;
	}
	bool operator<(const GridCell& point) const {
		return (row * INT_MAX + col < point.row * INT_MAX + point.col);
	}
	void operator=(const GridCell& point) {
		this->col = point.col;
		this->row = point.row;
	}
	bool operator==(const GridCell& point) const {
		return (this->col == point.col && this->row == point.row);
	}
	bool operator!=(const GridCell& point) const {
		return (this->col != point.col || this->row != point.row);
	}

	virtual ~GridCell();
};

#endif /* GridCell_H_ */
