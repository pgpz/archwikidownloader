#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    return fwrite(ptr, size, nmemb, stream);
}

int main(void) {
  CURL *curl;
  FILE *fp;
  CURLcode res;
  const char *outfilename = "wiki.html";
  char url[256];
  printf("enter arch wiki url: ");
  fgets(url, sizeof(url), stdin);
  url[strcspn(url, "\n")] = 0;


  curl = curl_easy_init();
  if (curl)
  {
    fp = fopen(outfilename, "wb");
    if (fp == NULL) {
      fprintf(stderr, "failed to read %s D:\n", outfilename);
      return 1;
    }
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept-Language: en-US,en;q=0.9");
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; rv:89.0) Gecko/20100101 Firefox/89.0");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);
    fclose(fp);
  } else {
    fprintf(stderr, "failed to curl D:\n");
    return 1;
  }
  char buffer[256];
  fp = fopen(outfilename, "r");
  if (fp)
  {
    while (fscanf(fp, "%255s", buffer) != EOF) {
      printf("%s\n", buffer);
    }





    printf("saved to wiki.html in your directory(open it inside of browser/whatever u use to browse files, but make sure it accepts .html.)\n");
    return 0;
  }
}
