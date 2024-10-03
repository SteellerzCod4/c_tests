#include <stdio.h>


double add_func(double array[], int len){
	float total_sum = 0;
	for (int i = 0; i < len; ++i){
		total_sum += array[i];
	}
	return total_sum;
}

void print_array(double array[], int len){
	for (int i = 0; i < len; ++i){
		printf("%.2lf ", array[i]);
	}
}


int main(void){
	int n;
	printf("Input number of digits:\n");
	scanf(" %d", &n);
	double digits[n];

	printf("Input %d digits below:\n", n);
	for (int i = 0; i < n; i++){
		scanf(" %lf", &digits[i]);
	}
	
	print_array(digits, n);

	double total = add_func(digits, n);
	printf("total sum is equal to %.2lf", total);
	return 0;
}