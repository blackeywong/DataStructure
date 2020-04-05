#pragma once
#ifndef _IMAGECOMPONENT_H
#define _IMAGECOMPONENT_H
#include "arrayQueue.h"
#include <string>
#include <sstream>
#include <iostream>
#include "../DS8/position.h"

const int NEIBOURS = 4;

template<unsigned SIZE>
class ImageComponent {
public:
	ImageComponent();
	ImageComponent(const std::string& pixel_str);
	virtual ~ImageComponent();
	void labelComponent();
	void showImage();

protected:
	position offset[NEIBOURS];
	int** pixel;
};


template<unsigned SIZE>
ImageComponent<SIZE>::ImageComponent() {
	offset[0].row = 0; offset[0].col = 1;
	offset[1].row = 1; offset[1].col = 0;
	offset[2].row = 0; offset[2].col = -1;
	offset[3].row = -1; offset[3].col = 0;

	pixel = new int* [SIZE + 2];
	for (int i = 0; i < SIZE + 2; i++) {
		pixel[i] = new int[SIZE + 2];
	}

	for (int i = 0; i < SIZE + 2; i++) {
		pixel[0][i] = pixel[SIZE + 1][i] = 0;
		pixel[i][0] = pixel[i][SIZE + 1] = 0;
	}

}

template<unsigned SIZE>
ImageComponent<SIZE>::ImageComponent(const std::string& pixel_str) :ImageComponent() {
	std::istringstream iss(pixel_str);
	std::string s;
	for (int i = 1; i <= SIZE; ++i) {
		for (int j = 1; j <= SIZE; ++j) {
			if (iss >> s) {
				pixel[i][j] = stoi(s);
			}
			else
				pixel[i][j] = 0;
		}
	}
}

template<unsigned SIZE>
ImageComponent<SIZE>::~ImageComponent() {
	for (int i = 0; i < SIZE + 2; i++) {
		delete[] pixel[i];
	}
	delete[] pixel;
	pixel = nullptr;
}

template<unsigned SIZE>
void ImageComponent<SIZE>::showImage() {
	std::cout << "Result:" << std::endl;
	for (int r = 1; r <= SIZE; ++r) {
		for (int c = 1; c <= SIZE; ++c) {
			std::cout << pixel[r][c] << " ";
		}
		std::cout << std::endl;
	}
}

template<unsigned SIZE>
void ImageComponent<SIZE>::labelComponent() {
	int option = 0;

	arrayQueue<position> q;
	position here, nbr;
	int id = 1;

	for(int r = 1;r<=SIZE;++r) {
		for (int c = 1; c <= SIZE; ++c) {
			if (pixel[r][c] == 1) {
				pixel[r][c] = ++id;
				here.row = r;
				here.col = c;

				while(true){
					for (int i = 0; i < NEIBOURS; ++i) {
						nbr = here + offset[i];
						if (pixel[nbr.row][nbr.col] == 1) {
							pixel[nbr.row][nbr.col] = id;
							q.push(nbr);
						}
					}

					if (q.empty())
						break;

					here = q.front();
					q.pop();
				}
			}

		}
	} 
}

#endif