// A program that manipulates and create binary trees, and to read and write from files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LENGTH 1000

const char *yes_input [6] = {"yes", "y", "absolutely", "correct", "aye", "yeah"};
const int yes_input_length = 6;
const char *no_input [6] = {"no", "n", "nope", "incorrect", "nah", "wrong"};
const int no_input_length = 6;

struct node{
	char *object;
	char *question;
	struct node *yes_ptr;
	struct node *no_ptr;
};

//convert str to lowercase in-place, return str
char *strlower(char *str){
	unsigned char *c = (unsigned char *)str;
	while(*c){
		*c = tolower(*c);
		c++;
	}
	return str;
}

/* compares yes and no strings with different inputs, eg:
yesOrNoString("y", "yes") returns 1,
yesOrNoString("ASDF", "yes") returns 0 */
int yesOrNoString(char *input_string, char *yesorno){
	int i;
    char *input_string_copy = malloc(strlen(input_string)+1);
    strcpy(input_string_copy, input_string);
    input_string = input_string_copy;
    
	if(strcmp(yesorno, "yes")==0){
		for(i=0; i<yes_input_length; i++){
			if(strcmp(strlower(input_string), yes_input[i])==0){
				free(input_string);
				return 1;
			}
		}
   	}
	else if(strcmp(yesorno, "no")==0){
		for(i=0; i<no_input_length; i++){
			if(strcmp(strlower(input_string), no_input[i])==0){
				free(input_string);
				return 1;
			}
		}
	}
	else
		printf("Please answer only yes or no to the question.\n");

	free(input_string);	
	return 0;
}

/* adds '?' to question in-place if it is absent, returns question. eg:
adjust_question("is it a pangolin") returns "is it a pangolin?"
adjust_question("is it a dog?") returns "is it a dog?"
*/
char *adjust_question(char *question){
	int length = strlen(question);
	if(length > 0 && question[length-1]=='?')
		return question;
	else
		return strcat(question, "?");
}

/* adds a/an/the to answer in-place if it is absent, returns answer. eg:
adjust_answer("dog") returns "a/an/the dog"
adjust_answer("a dog") returns "a dog"
pointer to the answer should point to memory with enough spare space to add a/an/the to the string*/
char *adjust_answer(char *answer){
	char article[20];
	sscanf(answer, "%s", article);
	if(strcmp(article, "a") == 0 || strcmp(article, "an") == 0 || strcmp(article, "the") == 0){
		return answer;
	}
	else{
		char *set_article = "a/an/the ";
		char source[strlen(set_article)+strlen(answer)];
		strcpy(source, answer);
		strcpy(answer, set_article);
		strcat(answer, source);
		return answer;
	}
}

//Prints all the nodes in the tree with indenting
void treePrint(struct node *ptr, int depth){
	int i;
	if(ptr==NULL){
		return;
	}
	else{
		for(i=0; i<depth; i++ ){
			putchar(' ');
		}

		if(ptr->question!=NULL){
			printf("question: %s\n", ptr->question);
			treePrint(ptr->yes_ptr, depth+1);
			treePrint(ptr->no_ptr, depth+1);
		}
		else{
			printf("object: %s\n", ptr->object);
		}
	}
}

//prints all nodes in the tree into output file
void treeWrite(struct node *ptr, FILE *output_file){
	if(ptr==NULL){
		return;
	}
	else{
		if(ptr->question!=NULL){
			fprintf(output_file, "question: %s\n", ptr->question);
			treeWrite(ptr->yes_ptr, output_file);
			treeWrite(ptr->no_ptr, output_file);
		}
		else{
			fprintf(output_file, "object: %s\n", ptr->object);
		}
	}
}

/* function reads the tree of the game from input_file
if it reads an object, it has no children;
if it reads a question, it has at least one child, yes or no pointers */
struct node *treeRead(FILE *input_file){

	char *line = malloc(1000*sizeof(char));
	fgets(line, 1000, input_file);
	if (line == NULL)
		return NULL;
	else{
		struct node *ptr = malloc(sizeof(struct node));
		if(ptr ==NULL)
			fprintf(stderr, "Malloc error!\n");
		if(strncmp("question:", strlower(line), 9) == 0){
			char *this_question = malloc(1000*sizeof(char));
			strcpy(this_question, line+10);
			strtok(this_question, "\n");
			ptr->question = this_question;
			ptr->yes_ptr = treeRead(input_file);
			ptr->no_ptr = treeRead(input_file);
			ptr->object = NULL;
			free(line);
		}
		else if(strncmp("object:", strlower(line), 7)==0){
			char *this_object = malloc(1000*sizeof(char));
			strcpy(this_object, line+8);
			strtok(this_object, "\n");
			ptr->object = this_object;
			ptr->question = NULL;
			ptr-> yes_ptr = ptr->no_ptr = NULL;
			free(line);
		}
		return ptr;
	}
}

//free all nodes of tree
void freeTree(struct node *ptr){
	if(ptr!=NULL){
		freeTree(ptr->yes_ptr);
		free(ptr->question);
		free(ptr->object);
		freeTree(ptr->no_ptr);
		free(ptr);
	}
}

/*
1. Starting with a tree of at least 1 object, iterate through it
until either:
- We guess the correct object
- We exhaust the tree, in which case we ask the user for a new question and object
2. If we guessed correctly, return the original tree, otherwise return a new
tree with the new question and object
*/
struct node *game(struct node *tree){
	
	struct node *original_tree = tree;
	char *input = malloc(MAX_LENGTH*sizeof(char));
	if(input == NULL)
		fprintf(stderr, "Malloc error!\n");
	
	while(1){
		if(tree->object != NULL){
			printf("is it %s?\n", tree->object);
			fgets(input, MAX_LENGTH, stdin);
			strtok(input, "\n");
			if(yesOrNoString(input, "yes") == 1){
				printf("Great! That was a piece of cake.\n");
				break;
			}
			else if(yesOrNoString(input, "no") == 1){
				struct node *new_object = malloc(sizeof(struct node));//TODO another function to insert data
				struct node *old_object = malloc(sizeof(struct node));
				if(new_object == NULL || old_object == NULL)
					fprintf(stderr, "Malloc error!\n");

				printf("Okay, you win then -- what were you thinking of?\n");
				char *objectname = malloc(MAX_LENGTH);
				fgets(objectname, MAX_LENGTH, stdin);
				strtok(objectname, "\n");
				new_object->object = adjust_answer(objectname);
				new_object->question = NULL;
				new_object->yes_ptr = new_object->no_ptr = NULL;
				
				old_object->object = tree->object;
				old_object->question = NULL;
				old_object->yes_ptr = old_object->no_ptr = NULL;

				printf("Please give me a question about %s, so I can tell the difference between %s and %s.\n",new_object->object, new_object->object, tree->object);
				char *thequestion = malloc(MAX_LENGTH);
				if(thequestion ==NULL)
					fprintf(stderr, "Malloc error!\n");
				fgets(thequestion, MAX_LENGTH, stdin);
				strtok(thequestion, "\n");
				
				tree->object = NULL;
				tree->question = adjust_question(thequestion);

				printf("What is the answer for %s?\n", new_object->object);
				fgets(input, MAX_LENGTH, stdin);
				strtok(input, "\n");
				if(yesOrNoString(input, "yes") == 1){
					tree->yes_ptr = new_object;
					tree->no_ptr = old_object;
				}
				else if(yesOrNoString(input, "no") == 1){
					tree->yes_ptr = old_object;
					tree->no_ptr = new_object;
				}
				else{
					printf("Please answer only yes or no to the question.\n");
				}
				printf("Thanks!\n");
				break;
			}
		}
		else{
			printf("%s\n", tree->question);
			fgets(input, MAX_LENGTH, stdin);
			strtok(input, "\n");
			if(yesOrNoString(input,"yes")==1){
				tree = tree -> yes_ptr;
			}
			else if(yesOrNoString(input, "no")==1){
				tree = tree->no_ptr;
			}
			else{
				printf("Please answer only yes or no to the question.\n");
			}
		}
	}

	free(input);
	return original_tree;
}

//prompt user if they wish to load or start a new game. 
//if user wishes to load a game, prompt user to enter name of file, return the original tree.
//if user wishes to start a new game, create a new tree of one object, return this tree.
struct node *gamelnit(char **argv){
	FILE *input_file;
	char *input;
	char *filename = argv[1]; //TODO initialise and/or save tree if filenames are given.
	struct node *tree;
	input = malloc(MAX_LENGTH*sizeof(char));
	if(input == NULL)
		fprintf(stderr, "Malloc error!\n");
	printf("To load the game, enter 'load'; otherwise press any key to start a new game.\n");
	fgets(input, MAX_LENGTH, stdin);
	strtok(input, "\n");
	if(strcmp(strlower(input), "load")==0){
		input_file = fopen(filename, "r");
		tree = treeRead(input_file);
		fclose(input_file);
	}
	else{
		tree = malloc(sizeof(struct node));
		if(tree == NULL)
			fprintf(stderr, "Malloc error!\n");
		tree ->object = strdup("a pangolin");
		tree ->question = NULL;
		tree ->yes_ptr = tree->no_ptr = NULL;
	}
	free(input);
	return tree;
}

int main(int argc, char **argv){
		
	struct node *tree;
	char *filename;
	char *input = malloc(MAX_LENGTH*sizeof(char));
	if(input ==NULL)
		fprintf(stderr, "Malloc error!\n");
		
	tree = gamelnit(argv);
	tree = game(tree);
	while(1){
		printf("Would you like to continue? Enter 'yes' to continue.\n");
		printf("Otherwise, enter 'save' to save the game and quit.\n");
		printf("If you wish to quit, enter 'no'.\n");
		fgets(input, MAX_LENGTH, stdin);
		strtok(input, "\n");
		if(strcmp(input, "yes")==0){
			tree = game(tree);
		}
		else if(strcmp(input, "save")==0){
			if (argv[1] == NULL) {
				printf("Please enter filename as argument to save the game.\n");
				filename = malloc(MAX_LENGTH);
				scanf("%s", filename);
			}
			else {
				filename = argv[1];
			}
			
			FILE *output_file = fopen(filename, "w+");
			treeWrite(tree, output_file);
			fclose(output_file);
			printf("Game successfully saved to %s!\n", filename);
			
			if (argv[1] == NULL)
				free(filename);

			break;
		}
		else if(strcmp(input, "no")==0){
			break;
		}
		else{
			printf("Please answer the question with yes/no/ to save.\n");
		}
	}
	free(input);
	freeTree(tree);	
	return 0;
}

#include "testing.c"
