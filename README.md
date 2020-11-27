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

You run nandtool like this: `sudo ./nandtool /dev/path outfile.txt`

/dev/path - This is the device path of your USB stick or NAND thing, use `ls /dev/sd*` to find devices. (do not use sd's with numbers after them, they are partitions not devices!!!)

outfile.txt - Basically you tell nandtool where to store the data it got (put something or nandtool will segfault)

The generated data is in the format `cell_no::degeneration factor (newline)`. An example file here:
```c
1::1.0
2::1.6
3::2.0
...
```
And so on, check for EOF when reading file, nandtool does not give you clues where it ends, nandtool does what it wants.
