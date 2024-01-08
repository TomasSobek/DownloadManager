#include "file_transfer.h"

#include <stdio.h>
#include <curl/curl.h>

int upload_file(const char *file_path, const char *remote_url, const char *username, const char *password) {
    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();

    if (curl) {
        // set FTP URL
        curl_easy_setopt(curl, CURLOPT_URL, remote_url);

        // enable ftp upload
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        // set local file path
        curl_easy_setopt(curl, CURLOPT_READDATA, fopen(file_path, "rb"));

        // set ftp username and password
        curl_easy_setopt(curl, CURLOPT_USERPWD, username);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "Upload failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Failed to initialize libcurl.\n");
        return 1;
    }

    return (res == CURLE_OK) ? 0 : 1;
}

int download_file(const char *remote_url, const char *file_path, const char *username, const char *password) {
    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();

    if (curl) {
        // set ftp url
        curl_easy_setopt(curl, CURLOPT_URL, remote_url);

        // enable ftp download
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fopen(file_path, "wb"));

        // set ftp username and password
        curl_easy_setopt(curl, CURLOPT_USERPWD, username);

        // perform download
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "Download failed: %s.\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Failed to initialize libcurl.\n");
        return 1;
    }

    return (res == CURLE_OK) ? 0 : 1;
}
