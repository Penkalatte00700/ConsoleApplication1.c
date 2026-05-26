#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main() {
	char text[100];
	int size = 0;

	text[0] = '\0';
	while (1) {
		printf("Choose the command \n");
		printf("1 - Append text\n");
		printf("2 - Start new line\n");
		printf("3 - Save to file\n");
		printf("4 - Load from file\n");
		printf("5 - Print text\n");
		printf("6 - Insert search\n");
		printf("7 - Search text\n");
		printf("0 - Exit\n");

		int command;

		scanf("%d", &command);
		getchar();



		switch (command) {
		case 1: {
			char input[100];
			printf("Enter text to append: ");
			fgets(input, sizeof(input), stdin);
			int input_length = strlen(input);

			if (input_length > 0 && input[input_length - 1] == '\n') {
				input[input_length - 1] = '\0';
				input_length--;
			}

			if (size + input_length >= 100) {
				printf("Not enough memory for this operation\n");
				break;
			}

			for (int i = 0; i < input_length; i++) {
				text[size + i] = input[i];
			}
			size = size + input_length;
			text[size] = '\0';

			printf("input len %d\n", input_length);
			break;
		}
		case 2:
			if (size + 1 >= 100) {
				printf("Not enough memory\n");
				break;
			}

			text[size] = '\n';
			size++;
			text[size] = '\0';

			printf("New line is started\n");

			break;
		case 3: {
			char filename[100];

			printf("Enter filename to save: ");
			fgets(filename, sizeof(filename), stdin);

			int filename_length = strlen(filename);

			if (filename_length > 0 && filename[filename_length - 1] == '\n') {
				filename[filename_length - 1] = '\0';
			}



			FILE* file = fopen(filename, "w");

			if (file == NULL) {
				printf("Error opening file\n");
				break;
			}

			fputs(text, file);
			fclose(file);

			printf("Text has been saved without errors\n");

			break;
		}
		case 4: {
			char filename[100];


			printf("Enter filename to load: ");
			fgets(filename, sizeof(filename), stdin);

			int filename_length = strlen(filename);
			if (filename_length > 0 && filename[filename_length - 1] == '\n') {
				filename[filename_length - 1] = '\0';
			}

			FILE* file = fopen(filename, "r");

			if (file == NULL)
			{
				printf("Error opening file");
				break;
			}

			if (fgets(text, 100, file) != NULL) {
				size = strlen(text);
			}
			else {
				text[0] = '\0';
				size = 0;
			}

			fclose(file);


			printf("Text has been loaded without errors\n");
			break;
		}
		case 5:
			printf("%s\n", text);
			break;
		case 6:
			
			break;
		case 7: {
			char querry[100];

			printf("Enter text to search: ");
			fgets(querry, sizeof(querry), stdin);

			int querry_len = strlen(querry);
			if (querry_len > 0 && querry[querry_len - 1] == '\n') {
				querry[querry_len - 1] = '\0';
			}

			char* result = strstr(text, querry);

			if (result != NULL) {
				int index = result - text;
				printf("Found at position %d\n", index);
			}
			else {
				printf("Didn't found anything\n");
			}

			break;
		}

		case 0:
			printf("Exit\n");
			return 0;

		default:
			printf("Unknown command\n");
			break;
		}

	}
}