#include "evafox.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
char* cLook;
char str[100];
int index = 0;
const double PI = 3.14;

void initialize() {
	memset(str, 0, sizeof(str));
	index = 0;
}

int main() {	
	puts("Welcome to EvaFox Console v0.0.1\n");
	puts("Press Ctrl+C to exit.\n");

	while (TRUE) {
		fputs("EvaFox>", stdout);
		
		initialize();

		fgets(str, 100, stdin);
		if (isalnum(str[0]) || str[0] == '(') {
			double result = expression();
			printf("%.2f\n", result);
		}
		else {
			puts("No has ingresado nada.");
		}
	}
	
	return 0;
}

/*
 expression = term {('+'|'-') term}
*/
double expression() {
	double ter = term();
	while (str[index] == '+' || str[index] == '-') {
		switch (str[index]) {
		case '+':
			index++; // eat '+'
			ter += term();
			break;
		case '-':
			index++; // eat '-'
			ter -= term();
			break;
		}
	}
	return ter;
}

/*
 term = factor {('*'|'/') factor}
*/
double term() {
	double fac = factor();
	while (str[index] == '*' || str[index] == '/') {
		switch (str[index]) {
		case '*':
			index++;
			fac *= factor();
			break;
		case '/':
			index++;
			fac /= factor();
			break;
		}
	}
	return fac;
}

/*
 factor = number
*/
double factor() {
	double number = 0.00;
	if (str[index] == '(') {
		index++; // match and eat '('
		number = expression();
		index++; // match and eat ')'
	}else if (str[index] >= '0' && str[index] <= '9') {
		number = (double)str[index++] - '0';
	}else {
		printf("Parse error: unexpecter character '%c'.\n", str[index]);
		exit(1);
	}
	return number;
}