/***
 * 2D Convolution Operation
 * 12/2/2024
 * Written in C
 * Musa Jalis 
 ***/

#include <stdlib.h>
#include <stdio.h>

int* matrix_generator(int width, int height) {
	int size = width * height;
	int* arr = (int*) malloc(size * sizeof(int));
	if (arr == NULL) {
		return 0;
	}
	for (int i = 0; i < size; i++) {
		arr[i] = 1;
	}
	return arr;
}

int* _2d_conv_operation(int* matrix, int* kernel, int matrix_width, int matrix_height, int kernel_size, int stride, int padding) {
	if (kernel_size > matrix_width) {
		return 0;
	}
	if (kernel_size > matrix_height) {
		return 0;
	}
	int* feature = matrix_generator(((matrix_width / kernel_size) * (matrix_width - (kernel_size - 1))), ((matrix_width / kernel_size) * (matrix_width - (kernel_size - 1))));
	int* matrix_p;

	if (padding > 0) {
		matrix_p = matrix_generator(matrix_width + (padding * 2), matrix_height + (padding * 2));
		
		for (int i = 0; i < (matrix_height + (padding * 2)); i++) {
			for (int j = 0; j < (matrix_width + (padding * 2)); j++) {
				if ((i - padding) < 0 || i > (matrix_height + padding - 1)) {
					matrix_p[(i * (matrix_width + (padding * 2))) + j] = 0;
				} else if ((j - padding) < 0 || j > (matrix_width + padding - 1)) {
					matrix_p[(i * (matrix_width + (padding * 2))) + j] = 0;
				} else {
					matrix_p[(i * (matrix_width + (padding * 2))) + j] = matrix[((i - padding) * matrix_width) + (j - padding)];
				}
			}
		}
	}
	int* matrix_;
	if (padding > 0) {
		matrix_ = matrix_p;
	} else {
		matrix_ = matrix;
	}

	for (int i = 0; i < ((matrix_height + (padding * 2)) - (kernel_size - 1)); i += stride) {
		for (int j = 0; j < ((matrix_width + (padding * 2)) - (kernel_size - 1)); j += stride) {
			for (int k = 0; k < kernel_size; k++) {
				for (int l = 0; l < kernel_size; l++) {
					feature[((i / stride) * (((matrix_width + (padding * 2)) / stride) - (kernel_size - 1))) + j] += 
						kernel[(k * kernel_size) + l] * matrix_[((i * (matrix_width + (padding * 2))) + j) + ((k * (matrix_width + (padding * 2))) + l)];
				}
			}
		}
	}
	if (padding > 0) {
		free(matrix_p);
	}
	return feature;
}

int main() {
	int matrix_width = 10;
	int matrix_height = 10;
	int kernel_size = 2;
	int stride = 1;
	int padding = 1;

	int* matrix = matrix_generator(matrix_width, matrix_height);
	int* kernel = matrix_generator(kernel_size, kernel_size);

	int* feature = _2d_conv_operation(matrix, kernel, matrix_width, matrix_height, kernel_size, stride, padding);
	printf("Feature matrix memory address: %p\n", feature);

	free(matrix);
	free(kernel);
	free(feature);
	return 0;
}

