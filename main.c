/******************************************************************************/
/* Macros                                                                     */
/******************************************************************************/
#define NR_OF_OPTIONS          10


/******************************************************************************/
/* Global Data                                                                */
/******************************************************************************/
static struct option_t {
	char  *name;
	char  *description;
} option[NR_OF_OPTIONS] = {
	{ "B4",      "Remote Control" },
	{ "B21",     "DA Prot" },
	{ "B22",     "DA Jitt" },
	{ "B10",     "Sequence Control" },
	{ "B6",      "Coher" },
	{ "B33",     "ITU 033" },
	{ "B8",      "Phone Test" },
	{ "B23",     "Coded" },
	{ "B9",      "3G Tests" },
	{ "Unknown", "Is accepted, but doesn’t enable an option" }
};
