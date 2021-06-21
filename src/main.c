#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "commandline.h"
#include "version.h"

int main(int argc, char *argv[]) {
	int choice;
	while (1) {
		static struct option long_options[] = {
			{"version", no_argument, 0, 'v'},
			{"help", no_argument, 0, 'h'},
			{"database", required_argument, 0, 'd'},
			{"time", required_argument, 0, 't'},
			{"level", required_argument, 0, 'l'},
			{"mode", required_argument, 0, 'm'},
			{0, 0, 0, 0}
		};

		int option_index = 0;

		/* Argument parameters:
			no_argument: " "
			required_argument: ":"
			optional_argument: "::" */
		choice = getopt_long(argc, argv, "vhd:t:m:l:", long_options, &option_index);

		if (choice == -1)
			break;

		switch (choice) {
		case 'v':
			printf("Connect4Engine Version %s\n", VERSION);
			return EXIT_SUCCESS;

		case 'h':
			// TODO
			printf("HELP MENU UNDER CONSTRUCTION\n");
			return EXIT_SUCCESS;

		case '?':
			return EXIT_FAILURE;

		default:
			return EXIT_FAILURE;
		}
	}

	/* Deal with non-option arguments here */
	for (; optind < argc; ++optind) {
		printf("%s\n", argv[optind]);
	}

	cmd_run();

	return 0;
}
