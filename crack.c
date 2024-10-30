#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    char *hash = md5(plaintext, strlen(plaintext));

    // Open the hash file
    FILE *file1 = fopen(hashFilename,"r");

    //validation 
    int found = 0;

    // Loop through the hash file, one line at a time.
    //allocating the memory so it lives out of the loope
    char *str = (char *) malloc(HASH_LEN+1);

    while( fgets(str,HASH_LEN+1,file1)){

        //trimming the new line character
        char *nl = strchr(str,'\n');
        if(nl) *nl = '\0';

        // Attempt to match the hash from the file to the
        // hash of the plaintext.

        // If there is a match, you'll return the hash.
        // If not, return NULL.

        if (strcmp(hash,str) == 0){
            found = 1;
            break;
        }

    }

    // Before returning, do any needed cleanup:
    
    //   Close files?
    fclose(file1);
    //   Free memory?
    free(hash);

    // Modify this line so it returns the hash
    // that was found, or NULL if not found.
    if (found){
        return str;
    }
    else 
        return NULL;
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // These two lines exist for testing. When you have
    // tryWord working, it should display the hash for "hello",
    // which is 5d41402abc4b2a76b9719d911017c592.
    // Then you can remove these two lines and complete the rest
    // of the main function below.

    //char *found = tryWord("hello", "hashes00.txt");
    //printf("%s %s\n", found, "hello");


    // Open the dictionary file for reading.
    FILE *file2 = fopen(argv[1],"r");

    // count for how many hasehes were cracked.
    int count = 0;

    // For each dictionary word, pass it to tryWord, which
    // will attempt to match it against the hashes in the hash_file.
    
    char *word = (char *) malloc(HASH_LEN+1);

    while (fgets(word,HASH_LEN+1,file2) != NULL){
        

        //trimming the new line character
        char *nl = strchr(word,'\n');
        if(nl) *nl = '\0';

        char *found = tryWord(word,argv[2]);
    
        // If we got a match, display the hash and the word. For example:
        //   5d41402abc4b2a76b9719d911017c592 hello
        if (found){
            count+=1;
            printf("%s %s\n",found,word);
        }

    }
    
    // Close the dictionary file.
    fclose(file2);

    // Display the number of hashes that were cracked.
    printf("%d Hashes cracked!!\n",count);
    // Free up any malloc'd memory?
    free(word);
}

