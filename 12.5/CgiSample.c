#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZEOFINBUF 2048
char InputBuffer[SIZEOFINBUF];

/*Specifically decoding and processing data
increase code based on the need */
int DecodeAndProcessData(char *input);    

int main(int argc, char*argv[])
{
	int   ContentLength;   /*data length*/
	int   x;
	int   i;
	char   *p;
	char   *pRequestMethod;     /*   METHOD attribute value  */

	printf("Content-type:text/html\n\n");     /*output from stdout£¬reply web server the return information style*/
	printf("<p>hello test</p>");

	/*get METHOD attribute value from the environment varible of "REQUEST_METHOD"*/
	pRequestMethod = getenv("REQUEST_METHOD");
	if(pRequestMethod==NULL)
	{
		printf("<p>request = null</p>");
		return   0;
	}
	if (strcasecmp(pRequestMethod,"POST")==0)
	{
		printf("<p>OK the method is POST!\n</p>");
		p = getenv("CONTENT_LENGTH")//get data length from environment varible of "CONTENT_LENGTH"
		if (p!=NULL)
		{
			ContentLength = atoi(p);
		}
		else
		{
			ContentLength = 0;
		}
		if (ContentLength > sizeof(InputBuffer)-1)   {
			ContentLength = sizeof (InputBuffer) - 1;
		}

		i   =   0;
		while (i < ContentLength)
		{                        
			x  = fgetc(stdin); //get Form data from stdin
			if (x==EOF)
				break;
			InputBuffer[i++] = x;
		}
		InputBuffer[i] = '\0';
		ContentLength   =   i;
		DecodeAndProcessData(InputBuffer);//Specifically decoding and processing data
	}
	else if (strcasecmp(pRequestMethod,"GET")==0)
	{
		printf("<p>OK the method is GET!\n</p>");
		p = getenv("QUERY_STRING");     //get Form data from environment varible of "QUERY_STRING"
		if   (p!=NULL)
		{
			strncpy(InputBuffer,p,sizeof(InputBuffer));
			DecodeAndProcessData(InputBuffer);    //Specifically decoding and processing data
		}
	}
	printf("<HEAD><TITLE>Submitted OK</TITLE></HEAD>\n");//output return information from stdout
	printf("<BODY>The information you supplied has been accepted.</BODY>\n");

	return   0;
}


int DecodeAndProcessData(char *input)    //Specifically decoding and processing data
{
	// add specific operations here
	printf("Rcv Data : %s", input);
	return 0;
}


