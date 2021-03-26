#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include <curl/curl.h>

#define repoUrl "https://raw.githubusercontent.com/Cieran0/cpm-repo/main/";
#define bin "/bin/"
#define chmod "chmod 755 "

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  	size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  	return written;
}
 
int download(char *pkg)
{
	CURL *curl_handle;
	FILE *file; 
 
	char url[100] = repoUrl;
	strcat(url,pkg);
	char location[100] = bin;
	strcat(location,pkg);
	char perms[100] = chmod;
	strcat(perms,location);

  	curl_global_init(CURL_GLOBAL_ALL);
 
  	/* init the curl session */ 
  	curl_handle = curl_easy_init();
 
  	/* set URL to get here */ 
  	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
 
  	/* Switch on full protocol/debug output while testing  
  	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
  	*/
 
  	/* disable progress meter, set to 0L to enable it */
  	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 0L);
 
  	/* send all data to this function  */ 
  	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
 
  	/* open the file */ 
  	file = fopen(location, "wb");
  	if(file) {
 
    	/* write the page body to this file handle */ 
    	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, file);
 
    	/* get it! */ 
    	curl_easy_perform(curl_handle);
 
    	/* close the header file */ 
    	fclose(file);
  	}
 
  	/* cleanup curl stuff */ 
  	curl_easy_cleanup(curl_handle);
 
  	curl_global_cleanup();
 		
	system(perms);

  	return 0;
}

int main(int argc, char *argsv[]) 
{

	if (getuid()) {printf("%s", "You must run as root");}
	else 
	{

    	if(strncmp("install",argsv[1],7) == 0)
    	{
    	    download(argsv[2]);
    	}
    	else if(strncmp("update",argsv[1],6) == 0)
    	{
			printf("\n k gaymer \n");
    	}
    	else {printf("gay"); }
	}
    return 0;
}
