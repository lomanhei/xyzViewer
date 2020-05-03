# xyzViewer
Utilize the power of HTML5 and PlotlyJS to build a lightweight molecular dynamics viewer.

## Introduction
This is a samll application for visualize the [xyz](https://en.wikipedia.org/wiki/XYZ_file_format) file. You may download an example xyz file [here](https://lomanhei.github.io/xyzViewer/example.xyz).

This application will generate a standalone html file for the animation with just the standard gcc compiler and without further dependence. The motivation of creating this project, is because the software VMD(a xyz file viewer) was not compatible with the Mac OS X 10.15 when it released. Therefore this project is launched as an alternative.

## Demo:
[Click Here](https://lomanhei.github.io/xyzViewer/example.html)

## Guideline:
1. Download the C header file, [xyzViewer.h](https://lomanhei.github.io/xyzViewer/xyzViewer.h)
2. Include the header file in your C source code, and call the API:
```c
// Here is an example
// The xyzViewer.h will use both stdlib.h and math.h. Please include them.

#includes <stdio.h>
#includes <stdlib.h>
#includes <math.h>
#includes "xyzViewer.h"

int main( ) {

// Here, the first arguement "example.xyz" is the path to your xyz file;
// the second arguement "example.html" is the path of your output file.
 xyzViewer( "example.xyz", "example.html" );
 return 0;
 
}

```



