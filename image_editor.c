//#Copyright 311CA_EftenieAndrei-Vlad_Tema3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//struct imagine
struct image {
    char type[5];
    int column, line;
    int vmax;
    int **matrix;
};

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    else {
        return b;
    }
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

int clamp(int x) {
    if(x < 0)
    {
        return 0;
    }
    if(x > 255)
    {
        return 255;
    }
    return x;
}

int main()
{
    //alocare dinamica struct imagine
    struct image *photo;
    photo = malloc(sizeof(struct image));
    photo->matrix = NULL;
    char command[500];

    char *word;
    char *token;

    int **select;
    select = NULL;

    int x, y, x1, y1, x2, y2;

    while(fgets(command, 500, stdin) != NULL)
    { 
        word = strtok(command, " ");
        if(strcmp(word, "LOAD") == 0)//LOAD
        {
            word = strtok(NULL, " ");//fisier
			int l = strlen(word);
			if(word[l - 1] == '\n')
				word[l - 1] = '\0';
            FILE *f;
            f = fopen(word, "r");//deschid fisier
            if(f == NULL)//daca fisier nu exista
            {
                printf("Failed to load %s\n", word);

                //eliberarea memoriei matricei anterioare, daca a existat
                if(photo->matrix != NULL)
                {
                    for(int i = 0; i < photo->line; i++)
                    {
                        free(photo->matrix[i]);
                    }
                    free(photo->matrix);
                }
                photo->matrix = NULL;
                //eliberarea memoriei matricei select, daca a existat
                if(select != NULL)
                {
                    for(int i = 0; i < y; i++)
                    {
                        free(select[i]);
                    }
                    free(select);
                }
                select = NULL;
            }else//daca fisier exista
            {   
                //eliberarea memoriei matricei anterioare, daca a existat
                if(photo->matrix != NULL)
                {
                    for(int i = 0; i < photo->line; i++)
                    {
                        free(photo->matrix[i]);
                    }
                    free(photo->matrix);
                }
                photo->matrix = NULL;
                //eliberarea memoriei matricei select, daca a existat
                if(select != NULL)
                {
                    for(int i = 0; i < y; i++)
                    {
                        free(select[i]);
                    }
                    free(select);
                }
                select = NULL;
                printf("Loaded %s\n", word);

                char line[48000];
                fgets(line, 48000, f);

                token = strtok(line, "\n");
                strcpy(photo->type, token);
                
                fscanf(f, "%d %d", &photo->column, &photo->line);
                fscanf(f, "%d", &photo->vmax);
                if(strcmp(photo->type, "P2") == 0 )//grayscale ascii
                {
                    x = photo->column;
                    y = photo->line;
                    x1 = 0;
                    y1 = 0;
                    x2 = x;
                    y2 = y;
                    photo->matrix = (int**)malloc(photo->line * sizeof(int*));
                    for(int i = 0; i < photo->line; i++)//aloc matrix
                        {
                            photo->matrix[i] = (int*)malloc(photo->column * sizeof(int));
                        }
                    select = (int**)malloc(y * sizeof(int*));
                    for(int i = 0; i < y; i++)//aloc select
                    {
                        select[i] = (int*)malloc(x * sizeof(int));
                    }
                    for(int i = 0; i < photo->line; i++)//citesc matrix
                    {
                        for(int j = 0; j < photo->column; j++)
                        {
                            fscanf(f, "%d", &photo->matrix[i][j]);
                        }
                    }
                    for(int i = 0; i < y; i++)//completez select
                    {
                        for(int j = 0; j < x; j++)
                        {
                            select[i][j] = photo->matrix[i][j];
                        }
                    }
                }else if(strcmp(photo->type, "P5") == 0)//grayscale binar
                {
                    x = photo->column;
                    y = photo->line;
                    x1 = 0;
                    y1 = 0;
                    x2 = x;
                    y2 = y;
                    fseek(f, 1, SEEK_CUR);
                    photo->matrix = (int**)malloc(photo->line * sizeof(int*));
                    for(int i = 0; i < photo->line; i++)//aloc matrix
                    {
                        photo->matrix[i] = (int*)malloc(photo->column * sizeof(int));
                    }
                    select = (int**)malloc(y * sizeof(int*));
                    for(int i = 0; i < y; i++)//aloc select
                    {
                        select[i] = (int*)malloc(x * sizeof(int));
                    }

                    unsigned char element;
                    for(int i = 0; i < photo->line; i++)//citesc matrix
                    {
                        for(int j = 0; j < photo->column; j++)
                        {
                            fread(&element, sizeof(unsigned char), 1, f);
                            photo->matrix[i][j] = (int)element;
                        }
                    }
                    for(int i = 0; i < y; i++)//completez select
                    {
                        for(int j = 0; j < x; j++)
                        {
                            select[i][j] = photo->matrix[i][j];
                        }
                    }
                }else if(strcmp(photo->type, "P3") == 0)//rgb ascii
                {
                    x = photo->column;
                    y = photo->line;
                    x1 = 0;
                    y1 = 0;
                    x2 = x;
                    y2 = y;
                    photo->matrix = (int**)malloc(photo->line * sizeof(int*));
                    for(int i = 0; i < photo->line; i++)//aloc matrix
                    {
                        photo->matrix[i] = (int*)calloc(3 * photo->column, sizeof(int));
                    }
                    select = (int**)malloc(y * sizeof(int*));
                    for(int i = 0; i < y; i++)//aloc select
                    {
                        select[i] = (int*)calloc(3 * x, sizeof(int));
                    }
                    for(int i = 0; i < photo->line; i++)//citesc matrix
                    {
                        for(int j = 0; j < 3 * photo->column; j++)
                        {
                            fscanf(f, "%d", &photo->matrix[i][j]);
                        }
                    }
                    for(int i = 0; i < photo->line; i++)//completez select
                    {
                        for(int j = 0; j < 3 * photo->column; j++)
                        {
                            select[i][j] = photo->matrix[i][j];
                        }
                    }
                }else if(strcmp(photo->type, "P6") == 0)//rgb binar
                {
					x = photo->column;
                    y = photo->line;
                    x1 = 0;
                    y1 = 0;
                    x2 = x;
                    y2 = y;
                    photo->matrix = malloc(photo->line * sizeof(int*));
                    for(int i = 0; i < photo->line; i++)//aloc matrix
                    {
                        photo->matrix[i] = malloc(3 * photo->column * sizeof(int));
                    }
                    select = malloc(y * sizeof(int*));
                    for(int i = 0; i < y; i++)//aloc select
                    {
                        select[i] = malloc((3 * x) * sizeof(int));
                    }
                    unsigned char element;
                    fseek(f, 1, SEEK_CUR);
                    for(int i = 0; i < photo->line; i++)//citesc matrix
                    {
                        for(int j = 0; j < 3 * photo->column; j++)
                        {
                            fread(&element, sizeof(unsigned char), 1, f);
                            photo->matrix[i][j] = (int)element;
                        }
                    }
                    for(int i = 0; i < photo->line; i++)//completez select
                    {
                        for(int j = 0; j < 3 * photo->column; j++)
                        {
                            select[i][j] = photo->matrix[i][j];
                        }
                    }
                }
				fclose(f);
            }
        }else if(strcmp(word, "SELECT") == 0)
        {
            word = strtok(NULL, " ");
            if(strncmp(word, "ALL", 3) == 0)//SELECT ALL
            {./moss.sh -l c dennis.c dragan.c eftenie.c
                if(photo->matrix == NULL)
                {
                    printf("No image loaded\n");
                    continue;
                }else
                {
                    printf("Selected ALL\n");

                    if(select != NULL)//dealocarea memoriei pentru select, daca am mai dat un select inainte
                    {
                        {
                            for(int i = 0; i < y; i++)
                            {
                                free(select[i]);
                            }
                            free(select);
                        }
                    }
                    select = NULL;

                    x = photo->column;
                    y = photo->line;

                    if(strcmp(photo->type, "P2") == 0 || strcmp(photo->type, "P5") == 0)
                    {
                        select = (int**)malloc(y * sizeof(int*));//alocarea memoriei pentru select
                        for(int i = 0; i < y; i++)
                        {
                            select[i] = (int*)malloc(x * sizeof(int));
                        }

                        for(int i = 0; i < y; i++)//retinerea lui select
                        {
                            for(int j = 0; j < x; j++)
                            {
                                select[i][j] = photo->matrix[i][j];
                            }
                        }

                    }else if(strcmp(photo->type, "P3") == 0 || strcmp(photo->type, "P6") == 0)
                    {
                        select = (int**)malloc(y * sizeof(int*));//alocarea memoriei pentru select
                        for(int i = 0; i < y; i++)   
                        {
                            select[i] = (int*)malloc((3 * x) * sizeof(int));
                        }

                        for(int i = 0; i < y; i++)//retinerea lui select
                        {
                            for(int j = 0; j < 3 * x; j++)
                            {
                                select[i][j] = photo->matrix[i][j];
                            }
                        }
                    }
                }
            }else//SELECT
            {
                int xmin, xmax, ymin, ymax, l, ok = 1;
				if(photo->matrix == NULL) {
					printf("No image loaded\n");
					continue;
				}
				if (word == NULL) {
					printf("Invalid command\n");
					continue;
				}
				l = strlen(word);
				for (int i = 0; i < l; i++)
					if(word[i] < '0' || word[i] > '9') {
						if(i == 0 && word[i] == '-')
							continue;
						printf("Invalid command\n");
						ok = 0;
						break;
					}
				if(ok == 0) {
					continue;
				}
                x1 = atoi(word);
                word = strtok(NULL, " ");
				if (word == NULL) {
					printf("Invalid command\n");
					continue;
				}
				l = strlen(word);
				for (int i = 0; i < l; i++)
					if(word[i] < '0' || word[i] > '9') {
						if(i == 0 && word[i] == '-')
							continue;
						printf("Invalid command\n");
						ok = 0;
						break;
					}
				if(ok == 0) {
					continue;
				}
                y1 = atoi(word);
                word = strtok(NULL, " ");
				if (word == NULL) {
					printf("Invalid command\n");
					continue;
				}
				l = strlen(word);
				for (int i = 0; i < l; i++)
					if(word[i] < '0' || word[i] > '9') {
						if(i == 0 && word[i] == '-')
							continue;
						printf("Invalid command\n");
						ok = 0;
						break;
					}
				if(ok == 0) {
					continue;
				}
                x2 = atoi(word);
                word = strtok(NULL, "\n");
				if (word == NULL) {
					printf("Invalid command\n");
					continue;
				}
				l = strlen(word);
				for (int i = 0; i < l; i++)
					if(word[i] < '0' || word[i] > '9') {
						if(i == 0 && word[i] == '-')
							continue;
						printf("Invalid command\n");
						ok = 0;
						break;
					}
				if(ok == 0) {
					continue;
				}
                y2 = atoi(word);

            	if(x1 < 0 || x1 > photo->column || y1 < 0 || y1 > photo->line || x2 < 0 || x2 > photo->column || y2 < 0 || y2 > photo->line || x1 == x2 || y1 == y2)
                {
                    printf("Invalid set of coordinates\n");
                    continue;
                }else  
                {
                   
                    if(select != NULL)//dealocarea memoriei pentru select, daca am mai dat un select inainte
                    { 
                        for(int i = 0; i < y; i++)
                        {
                            free(select[i]);
                        }
                        free(select);
                    }
                    select = NULL;

                    xmin = min(x1, x2);
                    xmax = max(x1, x2);
                    ymin = min(y1, y2);
                    ymax = max(y1, y2);
            
                    x = xmax - xmin;
                    y = ymax - ymin;

					x1 = xmin;
					x2 = xmax;
					y1 = ymin;
					y2 = ymax;

                    printf("Selected %d %d %d %d\n", xmin, ymin, xmax, ymax);

                    if(strcmp(photo->type, "P2") == 0 || strcmp(photo->type, "P5") == 0)
                    {
                        select = (int**)malloc(y * sizeof(int*));//alocarea memoriei pentru select
                        for(int i = 0; i < y; i++)
                        {
                            select[i] = (int*)malloc(x * sizeof(int));
                        }

                        for(int i = 0, k = ymin; i < y && k < ymax; i++, k++)//retinerea lui select
                        {
                            for(int j = 0, l = xmin; j < x && l < xmax; j++, l++)
                            {
                                select[i][j] = photo->matrix[k][l];
                            }
                        }

                    }else if(strcmp(photo->type, "P3") == 0 || strcmp(photo->type, "P6") == 0)
                    {
                        select = (int**)malloc(y * sizeof(int*));//alocarea memoriei pentru select
                        for(int i = 0; i < y; i++)   
                        {
                            select[i] = (int*)malloc((3 * x) * sizeof(int));
                        }

                        for(int i = 0, k = ymin; i < y && k < ymax; i++, k++)//retinerea lui select
                        {
                            for(int j = 0, l = 3 * xmin; j < 3 * x && l < 3 * xmax; j++, l++)
                            {
                                select[i][j] = photo->matrix[k][l];
                            }
                        }
                    }
                }
            }
        }else if(strcmp(word, "CROP\n") == 0)
        {
            if(photo->matrix == NULL)
            {
                printf("No image loaded\n");
                continue;
            }else
            {
                printf("Image cropped\n");
                for(int i = 0; i < photo->line; i++)
                {
                    free(photo->matrix[i]);
                }
                free(photo->matrix);
                photo->matrix = NULL;
            }

            photo->column = x;
            photo->line = y;

            if(strcmp(photo->type, "P2") == 0 || strcmp(photo->type, "P5") == 0)
            {
                photo->matrix = (int**)malloc(photo->line * sizeof(int*));
                for(int i = 0; i < photo->line; i++)
                {
                    photo->matrix[i] = (int*)malloc(photo->column * sizeof(int));
                }
                for(int i = 0; i < photo->line; i++)
                {
                    for(int j = 0; j < photo->column; j++)
                    {
                        photo->matrix[i][j] = select[i][j];
                    }
                }
            }
            if(strcmp(photo->type, "P3") == 0 || strcmp(photo->type, "P6") == 0)
            {
                photo->matrix = (int**)malloc(y * sizeof(int*));
                for(int i = 0; i < y; i++)
                {
                    photo->matrix[i] = (int*)malloc((3 * x) * sizeof(int));
                }
                for(int i = 0; i < y; i++)
                {
                    for(int j = 0; j < 3 * x; j++)
                    {
                        photo->matrix[i][j] = select[i][j];
                    }
                }
            }
        }else if(strncmp(word, "HISTOGRAM", 9) == 0)
        {
            int X, Y, bin, ok = 1, l;
			if(photo->matrix == NULL){
				printf("No image loaded\n");
				continue;
			}
            word = strtok(NULL, " ");
			if (word == NULL) {
					printf("Invalid command\n");
					continue;
			}
			l = strlen(word);
			for (int i = 0; i < l; i++)
				if(word[i] < '0' || word[i] > '9') {
					if(i == 0 && word[i] == '-')
						continue;
					printf("Invalid command\n");
					ok = 0;
					break;
				}
			if(ok == 0) {
				continue;
			}
            X = atoi(word);
            word = strtok(NULL, " ");
			if (word == NULL) {
				printf("Invalid command\n");
				continue;
			}
			l = strlen(word);
			if (word[l - 1] == '\n') {
				word[l - 1] = '\0';
				l--;
			}
			for (int i = 0; i < l; i++)
				if(word[i] < '0' || word[i] > '9') {
					if(i == 0 && word[i] == '-')
						continue;
					printf("Invalid command\n");
					ok = 0;
					break;
				}
			if(ok == 0) {
				continue;
			}
            Y =  atoi(word);
			word = strtok(NULL, " ");
			if (word != NULL) {
				printf("Invalid command\n");
				continue;
			}

            if(strcmp(photo->type, "P3") == 0 || strcmp(photo->type, "P6") == 0)
            {
                printf("Black and white image needed\n");
                continue;
            }else
            {
                int *vector;
                vector = (int*)calloc(photo->vmax, sizeof(int));
                for(int i = 0; i < photo->line; i++)      
                {
                    for(int j = 0; j < photo->column; j++)
                    {
                        vector[photo->matrix[i][j]]++;
                    }
                }
                bin = 256 / Y;
                int *sum;
                sum = (int*)calloc(Y, sizeof(int));
                for(int i = 0; i < Y; i++)
                {
                    for(int j = i * bin; j < (i + 1) * bin; j++)
                    {
                        sum[i] += vector[j];
                    }
                }
                int max = -1;
                for(int i = 0; i < Y; i++)
                {
                    if(sum[i] > max)
                    {
                        max = sum[i];
                    }
                }
                int star;
                for(int i = 0; i < Y; i++)
                {
                    star = sum[i] * X / max;
                    printf("%d\t|\t", star);
                    for(int j = 0; j < star; j++)
                    {
                        printf("*");
                    }
                    printf("\n");
                }
                free(sum);
                free(vector);
            }
        }else if(strcmp(word, "EQUALIZE\n") == 0)
        {
            if(photo->matrix == NULL)
            {
                printf("No image loaded\n");
                continue;
            }else if(strcmp(photo->type, "P3") == 0 || strcmp(photo->type, "P6") == 0)
            {
                printf("Black and white image needed\n");
                continue;
            }else
            {
                printf("Equalize done\n");
                int *vector;
                vector = (int*)calloc(photo->vmax, sizeof(int));
                for(int i = 0; i < photo->line; i++)      
                {
                    for(int j = 0; j < photo->column; j++)
                    {
                        vector[photo->matrix[i][j]]++;
                    }
                }
                int sum;
                for(int i = 0; i < photo->line; i++)
                {
                    for(int j = 0; j < photo->column; j++)
                    {
                        sum = 0;
                        for(int k = 0; k <= photo->matrix[i][j]; k++)
                        {
                            sum += vector[k];
                        }
                        double val = (double)255 * (double)sum / (double)(photo->line * photo->column);
                        photo->matrix[i][j] = round(val);
                    }
                }
				if(strcmp(photo->type, "P2") == 0 || strcmp(photo->type, "P5") == 0)
                {
                    for(int i = 0, k = y1; i < y && k < y2; i++, k++)//retinerea lui select
                    {
                        for(int j = 0, l = x1; j < x && l < x2; j++, l++)
                        {
                            select[i][j] = photo->matrix[k][l];
                        }
                    }
                }else if(strcmp(photo->type, "P3") == 0 || strcmp(photo->type, "P6") == 0)
                {
                    for(int i = 0, k = y1; i < y && k < y2; i++, k++)//retinerea lui select
                    {
                        for(int j = 0, l = 3 * x1; j < 3 * x && l < 3 * x2; j++, l++)
                        {
                            select[i][j] = photo->matrix[k][l];
                        }
                    }
                }
                free(vector);
            }  
        }else if(strncmp(word, "APPLY", 5) == 0)
        {
            word = strtok(NULL, "\n");
            if(photo->matrix == NULL)
            {
                printf("No image loaded\n");
                continue;
            }else if(word == NULL){
				printf("Invalid command\n");
			}else if(strcmp(photo->type, "P2") == 0 || strcmp(photo->type, "P5") == 0){
                printf("Easy, Charlie Chaplin\n");
                continue;
            }else if(strcmp(word, "EDGE") == 0)
            {
                printf("APPLY EDGE done\n");

                int **aux;
                aux = (int**)malloc(photo->line * sizeof(int*));//alloc auxul
                for(int i = 0; i < photo->line; i++)
                {
                    aux[i] = (int*)calloc(3 * photo->column, sizeof(int));
                }
                int sum;
                int c1, c2, d1, d2;
                c1 = x1;
                c2 = x2;
                d1 = y1;
                d2 = y2;
                if(x1 == 0)
                {
                    c1++;
                }
                if(y1 == 0)
                {
                    d1++;
                }
                if(x2 == photo->column)
                {
                    c2--;
                }
                if(y2 == photo->line)
                {
                    d2--;
                }
                for(int i = d1; i < d2; i++)
                {
                    for(int j = 3 * c1; j < 3 * c2; j++)
                    {
                        sum =  photo->matrix[i - 1][j - 3] + photo->matrix[i - 1][j] + photo->matrix[i - 1][j + 3] + photo->matrix[i][j - 3] + photo->matrix[i][j + 3] + photo->matrix[i + 1][j - 3] + photo->matrix[i + 1][j] + photo->matrix[i + 1][j + 3];
                        aux[i][j] = clamp(8 * photo->matrix[i][j] - sum);
					}
                }
                for(int i = d1; i < d2; i++)
                {
                    for(int j = 3 * c1; j < 3 * c2; j++)
                    {
                        photo->matrix[i][j] = aux[i][j];
                    }
                }
                for(int i = 0; i < photo->line; i++)//dealloc auxul
                {
                    free(aux[i]);
                }
                free(aux);

            }else if(strcmp(word, "SHARPEN") == 0)
            {
                printf("APPLY SHARPEN done\n");

                int **aux;
                aux = (int**)malloc(photo->line * sizeof(int*));
                for(int i = 0; i < photo->line; i++)//alloc auxul
                {
                    aux[i] = (int*)calloc(3 * photo->column, sizeof(int));
                }

                int sum;
                int c1, c2, d1, d2;
                c1 = x1;
                c2 = x2;
                d1 = y1;
                d2 = y2;
                if(x1 == 0)
                {
                    c1++;
                }
                if(y1 == 0)
                {
                    d1++;
                }
                if(x2 == photo->column)
                {
                    c2--;
                }
                if(y2 == photo->line)
                {
                    d2--;
                }
                for(int i = d1; i < d2; i++)
                {
                    for(int j = 3 * c1; j < 3 * c2; j++)
                    {
                        sum =  photo->matrix[i - 1][j] + photo->matrix[i][j - 3] + photo->matrix[i][j + 3] + photo->matrix[i + 1][j];
                        aux[i][j] = clamp(5 * photo->matrix[i][j] - sum);
                    }
                }
                for(int i = d1; i < d2; i++)
                {
                    for(int j = 3 * c1; j < 3 * c2; j++)
                    {
                        photo->matrix[i][j] = aux[i][j];
                    }
                }
                for(int i = 0; i < photo->line; i++)//dealloc auxul
                {
                    free(aux[i]);
                }
                free(aux);
            }else if(strcmp(word, "BLUR") == 0)
            {
                printf("APPLY BLUR done\n");

                int **aux;
                aux = (int**)malloc(photo->line * sizeof(int*));
                for(int i = 0; i < photo->line; i++)//alloc auxul
                {
                    aux[i] = (int*)calloc(3 * photo->column, sizeof(int));
                }

                int sum;
                int c1, c2, d1, d2;
                c1 = x1;
                c2 = x2;
                d1 = y1;
                d2 = y2;
                if(x1 == 0)
                {
                    c1++;
                }
                if(y1 == 0)
                {
                    d1++;
                }
                if(x2 == photo->column)
                {
                    c2--;
                }
                if(y2 == photo->line)
                {
                    d2--;
                }
                for(int i = d1; i < d2; i++)
                {
                    for(int j = 3 * c1; j < 3 * c2; j++)
                    {
                        sum =  photo->matrix[i - 1][j - 3] + photo->matrix[i - 1][j] + photo->matrix[i - 1][j + 3] + photo->matrix[i][j - 3] + photo->matrix[i][j] + photo->matrix[i][j + 3] + photo->matrix[i + 1][j - 3] + photo->matrix[i + 1][j] + photo->matrix[i + 1][j + 3];
                        aux[i][j] = clamp(sum / 9);
                    }
                }
                for(int i = d1; i < d2; i++)
                {
                    for(int j = 3 * c1; j < 3 * c2; j++)
                    {
                        photo->matrix[i][j] = aux[i][j];
                    }
                }
                for(int i = 0; i < photo->line; i++)//dealloc auxul
                {
                    free(aux[i]);
                }
                free(aux);
            }else if(strcmp(word, "GAUSSIAN_BLUR") == 0)
            {
                printf("APPLY GAUSSIAN_BLUR done\n");

                int **aux;
                aux = (int**)malloc(photo->line * sizeof(int*));
                for(int i = 0; i < photo->line; i++)//alloc auxul
                {
                    aux[i] = (int*)calloc(3 * photo->column, sizeof(int));
                }
                int sum;
                int c1, c2, d1, d2;
                c1 = x1;
                c2 = x2;
                d1 = y1;
                d2 = y2;
                if(x1 == 0)
                {
                    c1++;
                }
                if(y1 == 0)
                {
                    d1++;
                }
                if(x2 == photo->column)
                {
                    c2--;
                }
                if(y2 == photo->line)
                {
                    d2--;
                }
                for(int i = d1; i < d2; i++)
                {
                    for(int j = 3 * c1; j < 3 * c2; j++)
                    {
                        sum =  photo->matrix[i - 1][j - 3] + 2 * photo->matrix[i - 1][j] + photo->matrix[i - 1][j + 3] + 2 * photo->matrix[i][j - 3] + 4 * photo->matrix[i][j] + 2 * photo->matrix[i][j + 3] + photo->matrix[i + 1][j - 3] + 2 * photo->matrix[i + 1][j] + photo->matrix[i + 1][j + 3];
                        aux[i][j] = clamp(sum / 16);
                    }
                }
                for(int i = d1; i < d2; i++)
                {
                    for(int j = 3 * c1; j < 3 * c2; j++)
                    {
                        photo->matrix[i][j] = aux[i][j];
                    }
                }
                for(int i = 0; i < photo->line; i++)//dealloc auxul
                {
                    free(aux[i]);
                }
                free(aux);
            }else
            {
                printf("APPLY parameter invalid\n");
                continue;
            }
        }else if(strcmp(word, "SAVE") == 0)
        {
            if(photo->matrix == NULL)
            {
                printf("No image loaded\n");
                continue;
            }else
            {
                word = strtok(NULL, " ");
                int l = strlen(word);
                if(word[l - 1] == '\n')
                    word[l - 1] = '\0';
                printf("Saved %s\n", word);
                char *condition;
                condition = strtok(NULL, " ");
                if(condition == NULL)
                {
                    FILE *f;
                    f = fopen(word, "w");
                    if(strcmp(photo->type, "P2") == 0 || strcmp(photo->type, "P5") == 0)
                    {
                        fprintf(f, "P5\n");
                        fprintf(f, "%d %d\n%d\n", photo->column, photo->line, photo->vmax);
                        for(int i = 0; i < photo->line; i++)
                        {
                            for(int j = 0; j < photo->column; j++)
                            {
                                fwrite(&photo->matrix[i][j], sizeof(unsigned char), 1, f);
                            }
                        }
                       
                    }
                    if(strcmp(photo->type, "P3") == 0 || strcmp(photo->type, "P6") == 0)
                    {
                        fprintf(f, "P6\n");
                        fprintf(f, "%d %d\n%d\n", photo->column, photo->line, photo->vmax);
                        for(int i = 0; i < photo->line; i++)
                        {
                            for(int j = 0; j < 3 * photo->column; j++)
                            {
                                fwrite(&photo->matrix[i][j], sizeof(unsigned char), 1, f);
                            }
                        }
                    }
                    fclose(f);
                }else if(strcmp(condition, "ascii\n") == 0)
                { 
                    FILE *f;
                    f = fopen(word, "w");
                    if(strcmp(photo->type, "P2") == 0 || strcmp(photo->type, "P5") == 0)
                    {
                        fprintf(f, "P2\n");
                        fprintf(f, "%d %d\n%d\n", photo->column, photo->line, photo->vmax);
                        for(int i = 0; i < photo->line; i++)
                        {
                            for(int j = 0; j < photo->column; j++)
                            {
                                fprintf(f, "%d ", photo->matrix[i][j]);
                            }
                            fprintf(f, "\n");
                        } 
                    }
                    if(strcmp(photo->type, "P3") == 0 || strcmp(photo->type, "P6") == 0)
                    {
                        fprintf(f, "P3\n");
                        fprintf(f, "%d %d\n%d\n", photo->column, photo->line, photo->vmax);
                        for(int i = 0; i < photo->line; i++)
                        {
                            for(int j = 0; j < 3 * photo->column; j++)
                            {
                                fprintf(f, "%d ", photo->matrix[i][j]);
                            }
                            fprintf(f, "\n");
                        }
                    }
                    fclose(f);
                }
            }
            

            
        }else if(strncmp(word, "EXIT", 4) == 0)
        {
			if(photo->matrix == NULL)
			{
				printf("No image loaded\n");
				break;
			}
            if(photo->matrix != NULL)//eliberare memorie matrice
            {
                for(int i = 0; i < photo->line; i++)
                {
                    free(photo->matrix[i]);
                }
                free(photo->matrix);   
            }
            
            if(select != NULL)//eliberare memorie select
            {
                for(int i = 0; i < y; i++)
                {
                    free(select[i]);
                }
                free(select);
            }
			free(photo);//eliberare memorie struct imagine
            break;
        }else if(strcmp(word, "PRINT\n") == 0)
        {
            if(photo->matrix == NULL)
            {
                printf("NO IMAGE\n");
                continue;
            }else
            {
                if(strcmp(photo->type, "P2") == 0 || strcmp(photo->type, "P5") == 0)
                {
                    for(int i = 0; i < photo->line; i++)//afisare matrice
                    {
                        for(int j = 0; j < photo->column; j++)
                        {
                            printf("%d ", photo->matrix[i][j]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                    for(int i = 0; i < y; i++)//afisare select
                    {
                        for(int j = 0; j < x; j++)
                        {
                            printf("%d ", select[i][j]);
                        }
                        printf("\n");
                    }
                }
                if(strcmp(photo->type, "P3") == 0 || strcmp(photo->type, "P6") == 0)
                {
                    for(int i = 0; i < photo->line; i++)//afisare matrice
                    {
                        for(int j = 0; j < 3 * photo->column; j++)
                        {
                            printf("%d ", photo->matrix[i][j]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                    for(int i = 0; i < y; i++)//afisare select
                    {
                        for(int j = 0; j < 3 * x; j++)
                        {
                            printf("%d ", select[i][j]);
                        }
                        printf("\n");
                    } 
                }
            }
        }else
		{
			printf("Invalid command\n");
			continue;
		}
    }
    return 0;
}