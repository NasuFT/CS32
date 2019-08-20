#include <stdio.h>

int main() {
	printf("|   pid|    cpu|stat|                     name| hexdump|\n");
	printf("+------+-------+----+-------------------------+--------+\n");

	for(int i = 0; i < 1000; i++) {
		int pid;
		float cpu;
		char stat;
		char name[25];
		int hexdump;

		scanf("%d\t%s\t%c\t%f\t%x", &pid, name, &stat, &cpu, &hexdump);
		printf("|%6d|%.5f|%4c|%25s|%8d|\n", pid, cpu, stat, name, hexdump);

	}
}
