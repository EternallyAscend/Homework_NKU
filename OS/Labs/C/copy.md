# 操作系统第二次实验报告

<p align="right">2020.10.16 Fri.</p>

安装GCC

```Shell
sudo apt-get install build-essential
```

md5sum校验

```shell
md5sum fileName
```

C语言文件

```C
#define BUF_SIZE 64
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void help() {
	printf("-------- Help of copy command --------\n");
	printf("copy -h\n");
	printf("copy originFile copyName\n");
	printf("copy originFile copyName -v verifyMethod\n");
	printf("  |- The verifyMethod includes md5.\n");
}

int main(int argc, char* argv[]) {
	int needHelp = 1;
	int verifyMethod = 0;
	int targetFile = 0;

	int firstFile = 0;
	int verifyPosition = 0;

	char* method;
	char* inputFile;
	char* outputFile;

	int cursor = 1;
	for (; cursor < argc; cursor ++) {
		// printf("%s\n", argv[cursor]);
    
		if (verifyPosition) {
			method = argv[cursor];
			verifyPosition = 0;
			verifyMethod = 1;
			continue;
		}
    
		if (0 == strcmp(argv[cursor], "-h")) {
			needHelp = 2;
			continue;
		}
    
		else if (0 == strcmp(argv[cursor], "-v")) {
			verifyPosition = 1;
			continue;
		}
    
		if (firstFile) {
			outputFile = argv[cursor];
			targetFile = 1;
			firstFile = 0;
			needHelp = 0;
			continue;
		}
    
		else {
			if (!targetFile) {
				inputFile = argv[cursor];
				firstFile = 1;
				continue;
			}
		}
	}
  
	if (needHelp) {
		if (2 == needHelp) {
			help();
			exit(4);
		}
		else {
			printf("Wrong command.\n");
			help();
			exit(5);
		}
	}
	
	if (verifyMethod) {
		printf("Method: %s.\n", method);
	}

	if (targetFile) {
		int inputStream;
		int outputStream;
		int item;
		char buffer[BUF_SIZE];
    
		if ((inputStream = open(inputFile, O_RDONLY)) < 0) {
			printf("Input: %s\nOutput: %s\n", inputFile, outputFile);
			printf("File open failed.\n");
			exit(2);	
		}
    
		else {
			if (verifyMethod) {
			    char* str;
				str = (char*)malloc(sizeof(char) * 128);
				strcpy(str, "md5sum ");
				strcat(str, (const char*)inputFile);
				// puts(str);
				system(str);
			}
		}

		if ((outputStream = open(outputFile, O_RDONLY)) >= 0) {
			printf("Wrong - Target file already exists.\n");
			exit(3);
		}
    
		if ((outputStream = open(outputFile, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR)) < 0){
			printf("Input: %s\nOutput: %s\n", inputFile, outputFile);
			printf("File write failed.\n");
			exit(3);	
		}

		while(1) {
        item = read(inputStream, buffer, BUF_SIZE);
			if (item <= 0) {
    	        break;
        	}
			write(outputStream, buffer, item);
		}
    
    if (verifyMethod) {
			char* str;
			str = (char*)malloc(sizeof(char) * 128);
			strcpy(str, "md5sum ");
			strcat(str, (const char*)outputFile);
			// puts(str);
			system(str);
		}
    
		close(outputStream);
		close(inputStream);
		exit(0);
	}
	exit(0);
}

```

