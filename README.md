| 6. what specifically going to do for the back-end of the project? What we’re specifically supposed to make an extremely 
lower-level multifunction program which abstracts from reversible gates via hardware abstraction
(which are sets of routines in software that emulate some platform-specific details,
giving programs direct access to the hardware resources, they often allow programmers to write device-independent,
high performance applications by providing standard operating system (OS) calls to hardware)
as to be able to manipulate the NAND cells to reverse (them) to any given (previous) state through
wireless remote controlling. So hence, in essence, it's obviously not traditional data recovery that we're doing here
but rather, it's (as was phrased in a single article about 2 of the topics that we’ll be covering with doing this project)
“data recovery in the digital forensic sense”, most of all, this said exact 
VMT’s supposed to be compatible with LITERALLY ANY & EVERYTHING (NAND) flash memory, like SSDs, USBs, etc.

## nandtool usage
nandtool basically times between reads and finds anomalies for you(TM). And you just grab the data.

You run nandtool like this: `sudo ./nandtool -dev /dev/sdb -d deg_report.txt -a cells.txt`

Options:

* -dev [devpath] : specify the device path of the NAND usb
* -d [file] : Output degenerancy report to file
* -a [file] : Output cells values (as is) to a file (binary, hex, each is a byte)
* -e [numb] : Set how many cells we analyze, default it's 4096.

All options are evaluated and run as they are given, so you can use the -e option to analyze 16320 cells for degenerancy and 32220 cells for raw output.

The generated data (for degeneration) is in the format `cell_no::degeneration factor (newline)`. An example file here:
```c
1::1.0
2::1.6
3::2.0
...
```
And so on, check for EOF when reading file, nandtool does not give you clues where it ends, nandtool does what it wants.
