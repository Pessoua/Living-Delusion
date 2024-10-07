#ifndef LD_SAVE_FILE_H
#define LD_SAVE_FILE_H

//MAIN I/O Handlers
char * ReadFromFile(const char * wotPath, const char * fileName, u64 whatFileLine, u32 cacheCode);
void WriteToFile(const char * wotPath, const char * fileName, u64 whatFileLine, const char * argSequence, ...);

//Main dialogue handler (lang/ handler)
void ShowDialogueMsg(const char * whatTopic, u64 startLine, u64 followUpLines, u32 cacheCode, bool showTopic);

//Helper function
void SeekToCached(FILE * thisFile, u32 cacheLine);

#endif /* LD_SAVE_FILE_H */
