#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>


/******************************************************************************/
/*** Macros                                                                 ***/
/******************************************************************************/
#define NR_OF_OPTIONS          10


/******************************************************************************/
/*** Global data                                                            ***/
/******************************************************************************/
static struct option_t {
	char  *name;
	char  *description;
} option[NR_OF_OPTIONS] = {
	{ "B4",  "Remote Control" },
	{ "B21", "DA Prot" },
	{ "B22", "DA Jitt" },
	{ "B10", "Sequence Control" },
	{ "B6",  "Coher" },
	{ "B33", "ITU 033" },
	{ "B8",  "Phone Test" },
	{ "B23", "Coded" },
	{ "B9",  "3G Tests" },
	{ "U81", "DAI tests REL99 with CMU" }
};


/******************************************************************************/
/*** Static functions                                                       ***/
/******************************************************************************/
static int get_serialnr(char *optarg, unsigned long *serialnr)
{
	char  *endptr;

	/* Retrieve the number before the slash */
	serialnr[0] = strtoul(optarg, &endptr, 10);

	/* Done if nothing follows */
	if (*endptr == '\0')
		return 0;

	/* Bail with an error if anything else than a slash follows */
	if (*endptr != '/')
		goto err_serialnr;

	/* Bail with an error if nothing follows the slash */
	endptr++;
	if (*endptr == '\0')
		goto err_serialnr;

	/* Retrieve the number following the slash */
	serialnr[1] = strtoul(endptr, &endptr, 10);

	/* Bail with an error if anything follows */
	if (*endptr != '\0')
		goto err_serialnr;

	return 0;

err_serialnr:
	fprintf(stderr, "Invalid serial number '%s'\n", optarg);
	return -1;
}


/*****************************************************************************/
/*** Functions                                                             ***/
/*****************************************************************************/
int main(int argc, char* argv[])
{
	int            result = EXIT_SUCCESS;
	int            arg;
	unsigned long  serialnr[2] = { 0, 0 };

	/* Process the command line arguments */
	while ((arg = getopt(argc, argv, "hs:")) != -1) {
		switch (arg) {
		case 's':
			if (get_serialnr(optarg, serialnr))
				return EXIT_FAILURE;
			break;

		default:
			result = EXIT_FAILURE;
		case 'h':
			fprintf(stderr, "Usage:\n");
			fprintf(stderr, "%s -s serialnr\n", basename(argv[0]));
			return result;
		}
	}
	argc -= optind;
	argv += optind;

	if (argc) {
		fprintf(stderr, "Stdin not supported\n");
		result = EXIT_FAILURE;
		goto err_arg;
	}

	if (serialnr[0] && serialnr[1]) {
		fprintf(stdout, "Option keys for UPL with serial number %lu/%.3lu:\n", serialnr[0], serialnr[1]);
	}

err_arg:
	return result;
}
