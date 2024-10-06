#ifndef LD_SAVE_FILE_H
#define LD_SAVE_FILE_H

//MAIN I/O Handlers
char * ReadFromFile(const char * wotPath, const char * fileName, u64 whatFileLine, u32 cacheCode);
void WriteToFile(const char * wotPath, const char * fileName, u64 whatFileLine, const char * argSequence, ...);

//Main dialogue handlers
void ShowDialogueMsg(const char * whatTopic, u64 startLine, u64 followUpLines, u32 cacheCode, bool showTopic);
char * GetDialogueMsg(u64 startLine, u32 returnMany, FILE * fThisFile);

//Helper function
void SeekToCached(FILE * thisFile, u32 contentLine);

#endif /* LD_SAVE_FILE_H */
