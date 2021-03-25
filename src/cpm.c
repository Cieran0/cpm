#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#include <curl/curl.h>
 
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}
 
int download(char *pkg, char *pkgname)
{
  CURL *curl_handle;
  FILE *pkgfile; 
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */ 
  curl_handle = curl_easy_init();
 
  /* set URL to get here */ 
  curl_easy_setopt(curl_handle, CURLOPT_URL, pkg);
 
  /* Switch on full protocol/debug output while testing  
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
  */
 
  /* disable progress meter, set to 0L to enable it */
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 0L);
 
  /* send all data to this function  */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
 
  /* open the file */ 
  pkgfile = fopen(pkgname, "wb");
  if(pkgfile) {
 
    /* write the page body to this file handle */ 
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pkgfile);
 
    /* get it! */ 
    curl_easy_perform(curl_handle);
 
    /* close the header file */ 
    fclose(pkgfile);
  }
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
 
  curl_global_cleanup();
 
  return 0;
}

int main() 
{
    char *url = "https://curl.se/libcurl/c/url2file.html";
    char *file = "../based.txt";

    download(url , file);

    return 0;
}
