#ifndef SEMESTRALNAPRACAUDSP_FILE_TRANSFER_H
#define SEMESTRALNAPRACAUDSP_FILE_TRANSFER_H

int upload_file(const char *file_path, const char *remote_url, const char *username, const char *password);
int download_file(const char *remote_url, const char *file_path, const char *username, const char *password);

int upload_files();
int download_files();

#endif //SEMESTRALNAPRACAUDSP_FILE_TRANSFER_H
