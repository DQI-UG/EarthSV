#include "Manuals.h"

#include <stdio.h>
#include <stdlib.h>

void displayHelp() {
	FILE *f;
	char helpFileLine[256];

	f = fopen("help/SVTestReadme.md", "r");
	if (f == NULL) {
		fprintf(stderr, "readme file missing");
		exit(1);
	}
	while (fgets(helpFileLine, sizeof(helpFileLine), f)) {
		printf("%s", helpFileLine);
	}
	printf("\n");
	fclose(f);
	exit(1);
}
