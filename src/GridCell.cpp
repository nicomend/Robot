/*
 * GridCell.cpp
 *
 *  Created on: Jun 3, 2016
 *      Author: colman
 */
#include "GridCell.h"
GridCell::GridCell() {
	this->col = 0;
	this->row = 0;
}

GridCell::GridCell(int row, int col) {
	this->col = col;
	this->row = row;
}

GridCell::~GridCell() {
}

