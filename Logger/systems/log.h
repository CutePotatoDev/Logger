/*
 * log.h
 *
 * Created: 2017-01-10 02:52:20
 */ 

#ifndef LOG_H_
#define LOG_H_

//Print configuration message log.
void LOG_Config(char* s);
//Print information message log.
void LOG_Info(char* s);
//Print warning message log.
void LOG_Warning(char* s);
//Print error message log.
void LOG_Error(char* s);


#endif /* LOG_H_ */