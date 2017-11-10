#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max_line_length=100;

void processFile(FILE *, char **);

void processFile(FILE *fp, char **lines, int num_lines) {
    int scores[num_lines];
    char **names = (char **)malloc(sizeof(char*)*num_lines+1);
    int counter=0;
    while( !feof(fp) ) {
        lines[counter] = (char *)malloc(max_line_length);
        fgets(lines[counter],max_line_length-1,fp);
        if( lines[counter][0] == '\0' ) {
            continue;
        }
        names[counter] = (char*)malloc(sizeof(char)*max_line_length); 
        names[counter] = strtok(lines[counter], ",");
        char *token = strtok(NULL, ",");
        int value = atoi(token);
        scores[counter] = value;
        counter++;
    }

    int sum=0;

    int max_idx=-1;
    int max_score=-1;

    int min_idx=-1;
    int min_score=101;

    for( int i=0; i<num_lines; ++i ) {
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

    free(lines);
    free(names);

    float average=(float)sum / (float)num_lines;
    printf("The average score is: %f\n", average);
    printf("%s got the highest score with a %i\n",names[max_idx],scores[max_idx]);
    printf("%s got the lowest score with a %i\n",names[min_idx],scores[min_idx]);

    return;
}

int main(void) {
    int num_lines;
    char *num_of_students;
    char **lines;
    FILE *fp;
    int i;

    num_of_students = (char*)malloc(sizeof(char)*max_line_length);
    fp = fopen("students.csv", "r");
    if( fp == NULL ) {
        printf("You screwed up");
        return 1;
    }
    fgets(num_of_students,max_line_length-1,fp);
    num_lines = atoi(num_of_students);
    lines = (char **)malloc(sizeof(char*)*num_lines+1);
    processFile(fp, lines, num_lines);

    fclose(fp);
    free(lines);

    return 0;
}
