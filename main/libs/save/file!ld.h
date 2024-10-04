#ifndef LD_SAVE_FILE_H
#define LD_SAVE_FILE_H

char * ReadFromFile(const char * wotPath, const char * fileName, u64 whatFileLine);
void WriteToFile(int num_args, const char * wotPath, const char * fileName, u64 whatFileLine, ...);

#endif /* LD_SAVE_FILE_H */
