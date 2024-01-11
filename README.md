# SeamCarving
## ESC190 - Project 2

A quick C-based tool to dynamically resize an image.

Seam carving is a content-aware image resizing technique that reduces an image by one pixel at a time. The program finds a 'seam' (a path of pixels connected from the top to the bottom with one pixel per row) and removes the seam, effectively 'carving the seam' out of the image. 

this program computes the dual-gradient "energy" of each pixel, then removes the path with the least total energy.

For more information on how the project works, see [Prof. Guerzhoy's Assignment](https://www.cs.toronto.edu/~guerzhoy/190/proj/proj2/)

## How to use:

To use, you first must convert your image file to a binary file. You can use the python script *png2bin.py* to convert the file. This script can be used in the command line as follows:
```
python png2bin.py [-b] s/m (image name) [range]
```

-b triggers output mode (takes in binary, exports png)
s for single, m for multiple
image name WITHOUT EXTENSION (only works with .png file)
range is for multiple mode, however many files you have names (eg. img1, img2, etc)


Once you have the bin files you can compile the C script, and run as follows
```
./seamcarving (filename) [range]
```
where filename is the filename (including extension)
and range is an optional parameter if you want the scirpt to carve out some number of seams in a row.
