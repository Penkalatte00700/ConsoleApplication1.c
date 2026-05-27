#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void Append(char** text, int num_lines) {
	char input[100];
	printf("Enter text to append: ");
	fgets(input, sizeof(input), stdin);
	int input_length = strlen(input);

	if (input_length > 0 && input[input_length - 1] == '\n') {
		input[input_length - 1] = '\0';
		input_length--;
	}

	int cur_line = num_lines - 1;
	int cur_len = strlen(text[cur_line]);

	char* new_line = realloc(text[cur_line], (cur_len + input_length + 1) * sizeof(char));

	if (new_line == NULL) {
		printf("Error allocation\n");
		return;
	}

	text[cur_line] = new_line;

	for (int i = 0; i < input_length; i++) {
		text[cur_line][cur_len + i] = input[i];
	}

	text[cur_line][cur_len + input_length] = '\0';

	printf("input len %d\n", input_length);
}

char** StartNewLine(char** text, int* num_l_ptr, int* line_capacity_ptr) {
	if (*num_l_ptr >= *line_capacity_ptr) {
		int new_capacity = (*line_capacity_ptr) * 2;
		char** new_text = realloc(text, new_capacity * sizeof(char*));
		if (new_text == NULL) {
			printf("Error allocation\n");
			return text;
		}
		text = new_text;
		*line_capacity_ptr = new_capacity;
	}

	text[*num_l_ptr] = malloc(1 * sizeof(char));

	if (text[*num_l_ptr] == NULL) {
		printf("Error allocation\n");
		return text;
	}

	text[*num_l_ptr][0] = '\0';
	(*num_l_ptr)++;

	printf("New line is started\n");
	return text;
}

void SaveToFile(char** text, int num_lines) {
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
		return;
	}

	for (int i = 0; i < num_lines; i++) {
		fputs(text[i], file);
		if (i < num_lines - 1) {
			fputc('\n', file);
		}
	}



	fclose(file);

	printf("Text has been saved without errors\n");

}

char** LoadFromFile(char** text, int* num_l_ptr, int* line_capacity_ptr) {
	char filename[100];
	char line[100];

	printf("Enter filename to load: ");
	fgets(filename, sizeof(filename), stdin);

	int filename_length = strlen(filename);
	if (filename_length > 0 && filename[filename_length - 1] == '\n') {
		filename[filename_length - 1] = '\0';
	}

	FILE* file = fopen(filename, "r");

	if (file == NULL)
	{
		printf("Error opening file\n");
		return text;
	}

	for (int i = 0; i < *num_l_ptr; i++) {
		free(text[i]);
	}

	int new_n_lines = 0;
	while (fgets(line, sizeof(line), file) != NULL) {
		int line_lenght = strlen(line);

		if (line_lenght > 0 && line[line_lenght - 1] == '\n') {
			line[line_lenght - 1] = '\0';
			line_lenght--;
		}
		if (new_n_lines >= *line_capacity_ptr) {
			int new_capacity = (*line_capacity_ptr) * 2;
			char** new_text = realloc(text, new_capacity * sizeof(char*));
			if (new_text == NULL) {
				printf("Error allocation\n");
				fclose(file);
				*num_l_ptr = new_n_lines;
				return text;
			}
			text = new_text;
			*line_capacity_ptr = new_capacity;
		}
		text[new_n_lines] = malloc((line_lenght + 1) * sizeof(char));

		if (text[new_n_lines] == NULL) {
			printf("Error allocation\n");
			fclose(file);
			*num_l_ptr = new_n_lines;
			return text;
		}
		strcpy(text[new_n_lines], line);
		new_n_lines++;
	}

	fclose(file);

	if (new_n_lines == 0) {
		text[0] = malloc(1 * sizeof(char));
		text[0][0] = '\0';
		new_n_lines = 1;
	}

	*num_l_ptr = new_n_lines;


	printf("Text has been loaded without errors\n");
	return text;
}


void Insert(char** text, int num_lines) {
	char text_to_insert[100];
	int line_index;
	int index;

	printf("Enter index to insert: ");
	scanf("%d %d", &line_index, &index);
	getchar();

	if (line_index < 0 || line_index >= num_lines) {
		printf("Invalid line index\n");
		return;
	}

	int line_len = strlen(text[line_index]);

	if (index < 0 || index > line_len) {
		printf("Invalid index\n");
		return;
	}





	printf("Enter text to insert: ");
	fgets(text_to_insert, sizeof(text_to_insert), stdin);

	int tti_len = strlen(text_to_insert);

	if (tti_len > 0 && text_to_insert[tti_len - 1] == '\n') {
		text_to_insert[tti_len - 1] = '\0';
		tti_len--;
	}


	char* new_line = realloc(text[line_index], (line_len + tti_len + 1) * sizeof(char));

	if (new_line == NULL) {
		printf("Error allocation\n");
		return;
	}

	text[line_index] = new_line;

	for (int i = line_len; i >= index; i--) {
		text[line_index][i + tti_len] = text[line_index][i];
	}

	for (int i = 0; i < tti_len; i++) {
		text[line_index][index + i] = text_to_insert[i];
	}

	printf("Inserted successfully\n");

}

void Search(char** text, int num_lines) {
	char querry[100];

	printf("Enter text to search: ");
	fgets(querry, sizeof(querry), stdin);

	int querry_len = strlen(querry);

	if (querry_len > 0 && querry[querry_len - 1] == '\n') {
		querry[querry_len - 1] = '\0';
		querry_len--;
	}

	if (querry_len == 0) {
		printf("Empty querry\n");
		return;
	}


	int found = 0;
	for (int line = 0; line < num_lines; line++) {
		char* result = strstr(text[line], querry);
		while (result != NULL) {
			int index = result - text[line];
			printf("Found at position %d %d\n", line, index);
			found = 1;
			result = strstr(result + 1, querry);
		}
	}
	if (found == 0) {
		printf("Didn't found anything\n");
	}

}

void PrintText(char** text, int num_lines) {
	for (int i = 0; i < num_lines; i++) {
		printf("%s\n", text[i]);
	}
}


int main() {
	char** lines = malloc(10 * sizeof(char*));
	int num_lines = 1;
	int line_capacity = 10;


	if (lines == NULL) {
		printf("Error allocation\n");
		return 1;
	}


	lines[0] = malloc(1 * sizeof(char));

	if (lines[0] == NULL) {
		printf("Error allocation\n");
		return 1;
	}

	lines[0][0] = '\0';
	while (1) {
		printf("Choose the command \n");
		printf("1 - Append text\n");
		printf("2 - Start new line\n");
		printf("3 - Save to file\n");
		printf("4 - Load from file\n");
		printf("5 - Print text\n");
		printf("6 - Insert text\n");
		printf("7 - Search text\n");
		printf("0 - Exit\n");

		int command;

		scanf("%d", &command);
		getchar();



		switch (command) {
		case 1: {
			Append(lines, num_lines);
			break;
		}
		case 2:
			lines = StartNewLine(lines, &num_lines, &line_capacity);
			break;
		case 3: {
			SaveToFile(lines, num_lines);
			break;
		}
		case 4: {
			lines = LoadFromFile(lines, &num_lines, &line_capacity);
			break;
		}
		case 5:
			PrintText(lines, num_lines);
			break;
		case 6: {

			Insert(lines, num_lines);
			break;
		}
		case 7: {
			Search(lines, num_lines);
			break;
		}

		case 0:
			printf("Exit\n");

			for (int i = 0; i < num_lines; i++) {
				free(lines[i]);
			}
			free(lines);
			return 0;

		default:
			printf("Unknown command\n");
			break;
		}

	}
}