#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <libgen.h>


/******************************************************************************/
/*** Macros                                                                 ***/
/******************************************************************************/
#define NR_OF_OPTIONS          10
#define KEY_SEED               0x5aa5


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

	/* Bail with an error if no slash follows */
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
	fprintf(stderr, "UPL serial numbers are formatted like 123456/789\n");

	return -1;
}


static inline uint16_t roll(uint16_t value, int bits)
{
	return (value << bits) |
	       (value >> (16 - bits));
}


static uint16_t calc_option(unsigned int optionnr, unsigned long *serialnr)
{
	unsigned int  count;
	uint16_t      key = KEY_SEED;

	for (count = 0; count <= optionnr; count++) {
		uint16_t  key_up;

		key <<= 1;
		key_up = key << 1;
		if ((key ^ key_up) & (1 << 14))
			key += 1;
	}

	key = roll(key, 2);
	key ^= serialnr[0];

	key = roll(key, 3);
	key ^= serialnr[1];

	key = roll(key, 4);
	key ^= (serialnr[0] >> 16);

	key = roll(key, 5);
	while (key > 0 && key < 10000)
		key <<= 1;

	return key;
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
		unsigned int  option_ndx;

		fprintf(stdout, "Option keys for UPL with serial number %lu/%.3lu:\n", serialnr[0], serialnr[1]);
		for (option_ndx = 0; option_ndx < NR_OF_OPTIONS; option_ndx++)
			fprintf(stdout, "Option %d key: %d (%s - %s)\n", option_ndx, calc_option(option_ndx, serialnr), option[option_ndx].name, option[option_ndx].description);
	}

err_arg:
	return result;
}
