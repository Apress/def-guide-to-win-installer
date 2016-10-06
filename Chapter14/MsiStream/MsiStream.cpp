// MsiStream.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	PMSIHANDLE hDatabase;
	PMSIHANDLE hView;
	PMSIHANDLE hRecord;
	UINT res	= MsiOpenDatabase ("trynotepad.msi", MSIDBOPEN_READONLY, &hDatabase);
	char Query []  = "SELECT * FROM Binary WHERE Name='DefBannerBitmap'"; 
	res = MsiDatabaseOpenView(hDatabase, Query, &hView);
	if (ERROR_SUCCESS !=res)
	   return 1;
	res = MsiViewExecute(hView, NULL);  
	if (ERROR_SUCCESS == res)
		res = MsiViewFetch(hView, &hRecord);
	if (ERROR_SUCCESS ==res )
	{
		char bname [100] = {0};
		DWORD bnamelen = 100;
		// Name shows up in field 1 of record, assumed to be <100
		res = MsiRecordGetString (hRecord, 1, bname, &bnamelen);
		char FileName [] = "bitmap.bmp"; 
		char Stream [2048] = {0};
		BOOL stillok = TRUE;
		HANDLE hFile = CreateFile(FileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		if (INVALID_HANDLE_VALUE ==hFile  )
			res = -1;
		else
		{
			DWORD lenwritten=0, len=0;
			do
			{	
				len=sizeof(Stream);
				res = MsiRecordReadStream(hRecord, 2, Stream, &len); 
				if ((ERROR_SUCCESS == res) && (len > 0))
				{
					res = WriteFile(hFile, Stream, len, &lenwritten, NULL);
					stillok = (res==1);
				}
				else
				if (ERROR_SUCCESS !=res )
					stillok = FALSE;
			} 
			while (stillok == TRUE && (len > 0));
			CloseHandle(hFile);
			}
		MsiViewClose(hView);
		MsiCloseHandle(hRecord);
	}
	MsiCloseHandle(hView);

	// List streams
	char QueryStreams [] = "Select `Name`, `Data` from _Streams";
	res = MsiDatabaseOpenView(hDatabase, QueryStreams, &hView);
	if (ERROR_SUCCESS !=res)
	   return 1;
	res = MsiViewExecute(hView, NULL);  
	if (ERROR_SUCCESS ==res)
		res = MsiViewFetch(hView, &hRecord);
	if (ERROR_SUCCESS ==res)
	{
		char Field1 [100] = {0};
		char bstream [4096] = {0};
		DWORD fieldlen1 = 0;
		DWORD fieldlen2 = 0;
		do 
		{
			fieldlen1=100;
			res = MsiRecordGetString (hRecord, 1, Field1, &fieldlen1);
			do 
			{
			fieldlen2=4096;
			res = MsiRecordReadStream (hRecord, 2, bstream, &fieldlen2);
			// This is where to use the data in bstream
			}
			while (fieldlen2 > 0 && ERROR_SUCCESS==res);
			res= MsiViewFetch (hView, &hRecord);
		}
		while ( ERROR_SUCCESS == res );
		MsiCloseHandle(hRecord);
		MsiViewClose(hView);
	}
	MsiCloseHandle(hDatabase);
	return 0;
}

