#ifndef SEMESTRALNAPRACAUDSP_CONSOLE_H
#define SEMESTRALNAPRACAUDSP_CONSOLE_H

void console_main(void);

// basic console functions
void receiver_mode(void);
void sender_mode(void);
void huffman_mode(void);
void execute_command(const char *command);

// linux commands functions
void ls_command(void);
void mkdir_command(void);
void rmdir_command(void);

#endif //SEMESTRALNAPRACAUDSP_CONSOLE_H
