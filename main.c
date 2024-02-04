#include <stdio.h>
#include <locale.h>
#include "Program.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	startTest();
	return 0;
}