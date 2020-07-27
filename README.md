Description
===========
The vintage Rhode &amp; Schwarz UPL Audio Analyzer features a number of code-activated options:
* B4  - Remote Control
* B21 - DA Prot
* B22 - DA Jitt
* B10 - Sequence Control
* B6  - Coher
* B33 - ITU 033
* B8  - Phone Test
* B23 - Coded
* B9  - 3G Tests
* U81 - DAI tests REL99 with CMU (UPL16 only)

This project contains the source code to generate the keys required to activate these options.

Building
========
Build the project with:<br>
$ make

Usage
=====
keygen -s serialnr

Example
=======
	$ ./x86_64-linux-gnu/keygen -s 100694/6
	Option keys for UPL with serial number 100694/006:
	Option 0 key: 35303 (B4 - Remote Control)
	Option 1 key: 65040 (B21 - DA Prot)
	Option 2 key: 18424 (B22 - DA Jitt)
	Option 3 key: 36387 (B10 - Sequence Control)
	Option 4 key: 45464 (B6 - Coher)
	Option 5 key: 36590 (B33 - ITU 033)
	Option 6 key: 45058 (B8 - Phone Test)
	Option 7 key: 36314 (B23 - Coded)
	Option 8 key: 46698 (B9 - 3G Tests)
	Option 9 key: 49418 (U81 - DAI tests REL99 with CMU)

Important note
==============
UPL serial numbers are formatted like XXXXXX/YYY. If a serial number on the plaque is formatted like XXXXXX, the YYY part can be found in the type number. If the type number is 1078.2008K16, the value for YYY in that case is 016 (or just 16).
This has been tested with 6 instruments found on eBay, half of which had an XXXXXX-formatted serial number. So far all generated keys matched with the keys on the license plagues.
