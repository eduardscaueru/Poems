// SCAUERU EDUARD 313CD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/task_helper.h"

// Functii pentru a verifica daca o litera este mare sau mica
int up(char c)
{
	if(c >= 65 && c <= 90) return 1;
	return 0;
}

int low(char c)
{
	if(c >= 97 && c <= 122) return 1;
	return 0;
}

void uppercase(char *poem)
{
	int i, l = strlen(poem);

	if(low(poem[0]))
	{
		poem[0] = poem[0] - 32;
	}
	for(i = 1; i < l; i++)
	{
		if(poem[i-1] == '\n' && low(poem[i]))
		{
			poem[i] = poem[i] - 32;
		}
		else
		{
			if(up(poem[i]) && poem[i-1] != '\n')
			{
				poem[i] = poem[i] + 32;
			}
		}
	}
	return;
}

void trimming(char *poem)
{
	int i, l = strlen(poem), j, k;

	for(i = 0; i < l; i++)
	{
		if(strchr(".,;!?:", poem[i]))
		{
			memset(poem + i, ' ', 1);
		}
	}
	for(i = 0; i < l; i++)
	{
		k = i;
		while(poem[k] == ' ' && poem[k+1] == ' ')
		{
			memmove(&poem[k], &poem[k+1], l - k);
		    l--;
		    i--;
		    k++;
		}
	}
	for(i = 0; i < l; i++)
	{
		if(poem[i] == ' ' && (poem[i+1] == '\n' || poem[i-1] == '\n'))
		{
			memmove(&poem[i], &poem[i+1], l - i);
			l--;
		}
	}
	if(poem[strlen(poem) - 1] == ' ')
	{
		poem[strlen(poem) - 1] = '\0';
	}
	return;
}

void silly(char *poem, float chance)
{
	float rnd;
	int i, l = strlen(poem);

	for(i = 0; i < l; i++)
	{
		if((up(poem[i]) == 1) || (low(poem[i]) == 1))
		{
			rnd = rand() % 100 / 99.0;
			if(chance > rnd)
			{
				if(up(poem[i]))
				{
					poem[i] = poem[i] + 32;
				}
				else if(low(poem[i]))
				{
					poem[i] = poem[i] - 32;
				}
			}
		}
	}
	return;
}

// Functie pentru a lua ultimul cuvant din vers
void get_word(char *w, char *verse)
{
	int i, k;
	char *wcpy = malloc(30), *separators = malloc(15);

	strcpy(separators, " .,-;:!?");
	wcpy[0] = '\0';
	i = strlen(verse) - 1;
	while(strchr(separators, verse[i]))
	{
		i--;
	}
	k = 0;
	while(up(verse[i]) == 1 || low(verse[i]) == 1)
	{
		wcpy[k++] = verse[i];
		i--;
	}	
	for(i = 0; i < k; i++)
	{
		w[i] = wcpy[k - i - 1];
	}
	w[k] = '\0';
}

// Functie pentru a verifica daca 2 cuvinte rimeaza
int match(char *w1, char *w2)
{
	int l1 = strlen(w1), l2 = strlen(w2);
	char c1, c2;

	if(up(w1[l1 - 1]) == 1)
	{
		c1 = w1[l1 - 1] + 32;
	}
	else
	{
		c1 = w1[l1 - 1];
	}
	if(up(w2[l2 - 1]) == 1)
	{
		c2 = w2[l2 - 1] + 32;
	}
	else
	{
		c2 = w2[l2 - 1];
	}
	if(c1 == c2)
	{
		return 1;
	}
	return 0;
}

// Functie care gaseste sinonimul cel mai mic lexicografic care rimeaza
void corect_synonym(char *synonym, char **word_list, char *w, int n)
{
	int i;

	synonym[0] = '\0';
	for(i = 0; i < n; i++)
	{
		if(match(w, word_list[i]))
		{
			if(synonym[0] == '\0')
			{
				strcpy(synonym, word_list[i]);
			}
			if(strcmp(synonym, word_list[i]) > 0)
			{
				strcpy(synonym, word_list[i]);
			}
		}
	}
	return;
}

// Functie pentru a inlocui cuvantul cu sinonimul cu care rimeaza
void replace_word(char *poem, char *word, char *fword)
{
	int ll;
	char *new_poem = malloc(4010), *start;

	start = strstr(poem, word);
	ll = strlen(poem) - strlen(start);
	strcpy(new_poem, poem);
	memmove(start + strlen(fword), start + strlen(word), strlen(start + strlen(word)) + 1);
	strncpy(start, fword, strlen(fword));
	new_poem[ll] = '\0';
	strcat(new_poem, start);
	strcpy(poem, new_poem);

	free(new_poem);
	return;
}

void rhimy(char *poem, char *rhyme)
{
	int i, l = strlen(poem), nr = 0, n, lmin;
	char *w1 = malloc(30), *w2 = malloc(30), *w3 = malloc(30), *w4 = malloc(30)	, *verse = malloc(200), *new_poem = malloc(4010), **word_list, *synonym = malloc(30);

	strcpy(new_poem, poem);
	verse = strtok(new_poem, "\n");
	nr = 0;
	while(verse != NULL)
	{
		nr++;
		if(nr == 1)
		{
			w1[0] = '\0';
			get_word(w1, verse);
		}
		if(nr == 2)
		{
			w2[0] = '\0';
			get_word(w2, verse);
		}
		if(nr == 3)
		{
			w3[0] = '\0';
			get_word(w3, verse);
		}
		if(nr == 4)
		{
			w4[0] = '\0';
			get_word(w4, verse);
			nr = 0;
			if(strcmp(rhyme, "imperecheata") == 0)
			{
				if(!match(w1, w2))
				{
					get_synonym(w1, &n, &word_list);
					if(n > 0)
					{
						corect_synonym(synonym, word_list, w2, n);
						if(synonym[0] != '\0')
						{
							replace_word(poem, w1, synonym);
						}
					}
					else
					{
						get_synonym(w2, &n, &word_list);
						if(n > 0)
						{
							corect_synonym(synonym, word_list, w1, n);
							if(synonym[0] != '\0')
							{
								replace_word(poem, w2, synonym);
							}	
						}
					}
				}
				if(!match(w3, w4))
				{
					get_synonym(w3, &n, &word_list);
					if(n > 0)
					{
						corect_synonym(synonym, word_list, w4, n);
						if(synonym[0] != '\0')
						{
							replace_word(poem, w3, synonym);
						}	
					}
					else
					{
						get_synonym(w4, &n, &word_list);
						if(n > 0)
						{
							corect_synonym(synonym, word_list, w3, n);
							if(synonym[0] != '\0')
							{
								replace_word(poem, w4, synonym);
							}	
						}
					}
				}
			}
			else
			{
				if(strcmp(rhyme, "incrucisata") == 0)
				{
					if(!match(w1, w3))
					{
						get_synonym(w1, &n, &word_list);
						if(n > 0)
						{
							corect_synonym(synonym, word_list, w3, n);
							if(synonym[0] != '\0')
							{
								replace_word(poem, w1, synonym);
							}	
						}
						else
						{
							get_synonym(w3, &n, &word_list);
							if(n > 0)
							{
								corect_synonym(synonym, word_list, w1, n);
								if(synonym[0] != '\0')
								{
									replace_word(poem, w3, synonym);
								}	
							}
						}
					}
					if(!match(w2, w4))
					{
						get_synonym(w2, &n, &word_list);
						if(n > 0)
						{
							corect_synonym(synonym, word_list, w4, n);
							if(synonym[0] != '\0')
							{
								replace_word(poem, w2, synonym);
							}	
						}
						else
						{
							get_synonym(w4, &n, &word_list);
							if(n > 0)
							{
								corect_synonym(synonym, word_list, w2, n);
								if(synonym[0] != '\0')
								{
									replace_word(poem, w4, synonym);

								}	
							}
						}
					}
				}
				else
				{
					if(strcmp(rhyme, "imbratisata") == 0)
					{
						if(!match(w1, w4))
						{
							get_synonym(w1, &n, &word_list);
							if(n > 0)
							{
								corect_synonym(synonym, word_list, w4, n);
								if(synonym[0] != '\0')
								{
									replace_word(poem, w1, synonym);
								}	
							}
							else
							{
								get_synonym(w4, &n, &word_list);
								if(n > 0)
								{
									corect_synonym(synonym, word_list, w1, n);
									if(synonym[0] != '\0')
									{
										replace_word(poem, w4, synonym);
									}	
								}
							}
						}
						if(!match(w2, w3))
						{
							get_synonym(w2, &n, &word_list);
							if(n > 0)
							{
								corect_synonym(synonym, word_list, w3, n);
								if(synonym[0] != '\0')
								{
									replace_word(poem, w2, synonym);
								}	
							}
							else
							{
								get_synonym(w3, &n, &word_list);
								if(n > 0)
								{
									corect_synonym(synonym, word_list, w2, n);
									if(synonym[0] != '\0')
									{
										replace_word(poem, w3, synonym);
									}	
								}
							}
						}
					}
				}
			}
		}
		verse = strtok(NULL, "\n");
	}

	free(synonym);
	free(w1);
	free(w2);
	free(w3);
	free(w4);
	free(new_poem);
	return;
}

void friendly(char *poem)
{
	char *word, *cpy = malloc(4010), *fword = malloc(30), *separators = malloc(50), *start, *aux;
	int i, l = strlen(poem), k, newlen, ll;

	strcpy(separators, ".,;!?: \n");
	strcpy(cpy, poem);
	word = strtok(cpy, separators);
	while(word)
	{
		get_friendly_word(word, &fword);
		if(fword != NULL)
		{
			newlen = strlen(poem) - strlen(word) + strlen(fword) + 1;
			char *new_poem = malloc(4010);

			start = strstr(poem, word);
			while(up(start[strlen(word)]) || low(start[strlen(word)]))
			{
				start = strstr(start + 1, word);
			}
			ll = strlen(poem) - strlen(start);
			strcpy(new_poem, poem);
			memmove(start + strlen(fword), start + strlen(word), strlen(start + strlen(word)) + 1);
			strncpy(start, fword, strlen(fword));
			new_poem[ll] = '\0';
			strcat(new_poem, start);
			strcpy(poem, new_poem);

			free(new_poem);
 		}
		word = strtok(NULL, separators);
	}
	free(fword);
	free(cpy);
	free(separators);
	return;
}

void print(char *poem)
{
	if(poem[strlen(poem) - 1] == '\n')
	{
		poem[strlen(poem) - 1] = '\0';
	}
	printf("%s\n\n", poem);
	return;
}

int main(void)
{
	char *task = malloc(510 * sizeof(char)), *poem = malloc(4010 * sizeof(char));

	srand(42);
	do
	{
		fgets(task, 510, stdin);

		if(strstr(task, "load"))
		{
			char *path = malloc(510 * sizeof(char));
			strcpy(path, strchr(task, ' ') + 1);
			path = strtok(path, "\n");
			load_file(path, poem);

			free(path);
		}
		else
		{
			if(strstr(task, "uppercase"))
			{
				uppercase(poem);
			}
			else
			{
				if(strstr(task, "trimming"))
				{
					trimming(poem);
				}
				else
				{
					if(strstr(task, "make_it_silly"))
					{
						char *ch = malloc(10 * sizeof(char));
						float chance;

						strcpy(ch, strchr(task, ' ') + 1);
						ch = strtok(ch, "\n");
						chance = atof(ch);
						silly(poem, chance);

						free(ch);
					}
					else
					{
						if(strstr(task, "make_it_friendlier"))
						{
							friendly(poem);
						}
						else
						{
							if(strstr(task, "make_it_rhyme"))
							{
								char *rhyme = malloc(15 * sizeof(char));

								strcpy(rhyme, strchr(task, ' ') + 1);
								rhyme = strtok(rhyme, "\n");
								rhimy(poem, rhyme);

								free(rhyme);
							}
							else
							{
								if(strstr(task, "print"))
								{
									print(poem);
								}
								else
								{
									break;
								}
							}
						}
					}
				}
			}
		}
	}while(1);

	free(task);
	free(poem);

	return 0;
}