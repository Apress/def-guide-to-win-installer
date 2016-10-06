#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <sfc.h>

PROTECTED_FILE_DATA aFile = {0};
FILE *stream;

int main(int argc, char* argv[])
{
    BOOL res = true;
	long i=0;

	stream = fopen( "sfcfiles.txt", "w" );
	while (res)
	{	
		res = SfcGetNextProtectedFile (NULL, &aFile) ;
		if (res)
			fprintf(stream, "%S\n", aFile.FileName);
	}
	fclose (stream);
	return 0;
}

