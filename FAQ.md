### What is NAND?
Basicaly a NOT AND, if AND is true, then its false, and if its false, then its true.

### How does NAND address memory/storage?
Instead of page and then by word (NOR), it uses page by then word and bit, wich adds an extra addressing layer.
They require every bit in a word to be accessed simultaneously.

### How does NAND reads data?
To read data, first the desired group is selected, like addressing the array of transistors in a NOR flash drive.
The reduction in ground wires and bit lines allows a bigger and smaller layout per chip.

### How a NAND device writes to the memory physicaly?
Well, it uses something called Tunnel Injection for saving, and Tunnel Release for erasing.

### Is vertical NAND the same as a normal NAND?
Yes, the only difference is that addressing memory is now vertical.

### Any useful resource?
* https://www.csd.uoc.gr/~hy428/reading/tn2919.pdf (Page 3,5-27) (Example assembly code on page 23)
* http://www2.lauterbach.com/pdf/nandflash.pdf (Page 7-86) (Script **.cmm** example files on pages 12,15-18,22,23,28,31,33,34,36-48,50-59)
* https://www.xeltek.com/resources/technical-articles/memory-device-types/nand-flash-programming/ (Explains the basics)
