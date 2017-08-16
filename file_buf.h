#ifndef FILE_BUF_H
#define FILE_BUF_H

#include <stdlib.h>
// an in memory file representation
typedef struct {
	char *path;
	char *data;
	size_t size;
} FileBuf;


FileBuf *fileBufNew(const char *path); 
int fileBufLoad(FileBuf *fBuf);
void fileBufDelete(FileBuf *fbuf);
#endif
