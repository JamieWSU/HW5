#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max_line_length=100;

//this prototype did not match your function requirements, I also changed the type so I can return an error count
int processFile(FILE *, char **, int);

int  processFile(FILE *fp, char **lines, int num_lines) {
    int scores[num_lines];
    char **names = (char **)malloc(sizeof(char*)*num_lines+1);
    int counter=0;
// this has been added to track how many students are missing a score or have something wrong with the values in the file
    int error_count = 0;

    while( !feof(fp) ) {
        lines[counter] = (char *)malloc(max_line_length);
	fgets(lines[counter],max_line_length-1,fp);
        if( lines[counter][0] == '\0' ) {
		continue;
        }
        names[counter] = (char*)malloc(sizeof(char)*max_line_length); 
        names[counter] = strtok(lines[counter], ",");
	char *token = strtok(NULL, ",");
	if (token == NULL)
	{
	     /* this increases the error count when strtok retuns a null so the proff will 
		know if there was an error on the file given.*/
	     error_count++;
	     // this will cause the array to write over the top of the last record that was partially completed.
	     counter--;
	}
        // this is to protect against token coming back as null and was why the program was segfaulting.
	else {
	    int value = atoi(token);
	    scores[counter] = value;
	}
        counter++;
    }
    
    int sum=0;

    int max_idx=-1;
    int max_score=-1;

    int min_idx=-1;
    int min_score=101;

    // I subtracted num_lines and the error_count values, so the number of lines checked is updated
    for( int i=0; i<num_lines - error_count; ++i ) {
        sum+=scores[i];

        if( scores[i] > max_score ) {
            max_score = scores[i];
            max_idx = i;
	}
        if( scores[i] < min_score ) {
            min_score = scores[i];
            min_idx = i;
        }
    }

    //I removed the free (lines); to get rid of the double free error
    free(names);

    float average=(float)sum / (float)num_lines;
    printf("The average score is: %f\n", average);
    printf("%s got the highest score with a %i\n",names[max_idx],scores[max_idx]);
    printf("%s got the lowest score with a %i\n",names[min_idx],scores[min_idx]);
    
    return (error_count);
}

int main(void) {
    int num_lines;
    char *num_of_students;
    char **lines;
    FILE *fp;
    int error_count;
    // the int i wasn't being used

    num_of_students = (char*)malloc(sizeof(char)*max_line_length);
    fp = fopen("students.csv", "r");
    if( fp == NULL ) {
        printf("You screwed up");
        return 1;
    }
    fgets(num_of_students,max_line_length-1,fp);
    num_lines = atoi(num_of_students);
    lines = (char **)malloc(sizeof(char*)*num_lines+1);
    error_count = processFile(fp, lines, num_lines);
    /* This print satement was added so the user could know how many error where found in the file.
       I would change the int error count to an array or struct so I could also return the line 
       where the errors occured in the file and what the error may have been.*/
    printf("There was %d error or errors resutling from the source file.\n", error_count);

    fclose(fp);
    free(lines);

    return 0;
}
