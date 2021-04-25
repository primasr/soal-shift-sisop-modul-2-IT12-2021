#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <stdio.h>
#include <wait.h>
#include <string.h>

char data[20] = "Download Success", temp;
int count, key = 5;	

void caesar_cipher_encryption()
{

      for(count = 0; data[count] != '\0'; count++)
      {
            temp = data[count];
            if(temp >= 'a' && temp <= 'z')
            {
                  temp = temp + key;
                  if(temp > 'z')
                  {
                        temp = temp - 'z' + 'a' - 1;
                  }
                  data[count] = temp;
            }
            else if(temp >= 'A' && temp <= 'Z')
            {
                  temp = temp + key;
                  if(temp > 'Z')
                  {
                        temp = temp - 'Z' + 'A' - 1;
                  }
                  data[count] = temp;
            }
      }
}

int main(int argc, char const *argv[]){

	// jika input ketika execute file tidak sesuai, berarti exit failure
	if (argc != 2) {
		printf("Input with ./exe -x or ./exe -z \n");
		exit(EXIT_FAILURE);
	}

	// input kurang benar
	if (strcmp(argv[1],"-x") != 0 && strcmp(argv[1],"-z") != 0) {
		printf("Please input with -x or -z\n");
		exit(EXIT_FAILURE);
	}

    // declare variable
    pid_t pid, sid;     
    int status;    
    pid_t cid,cid_2,cid_3,cid_4;
    pid = fork();   

    // jika fork gagal
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    // jika fork berhasil
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // file permission
    umask(0);

    // set unique id
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

	// program mode pertama
    if(strcmp(argv[1],"-z") == 0){
    	FILE *fk;
    	fk = fopen("killer.sh", "w+");

    	char *isiFile = 
    	"#!/bin/bash\n"
    	"# pkill untuk menghentikan semua program\n"
    	"/usr/bin/pkill -9 -s \"%d\"\n"
    	"# remove file killer.sh setelah di eksekusi\n"
    	"/bin/rm killer.sh";

    	fprintf(fk, isiFile, sid);

    	fclose(fk);
    }

    // program mode kedua
    if(strcmp(argv[1],"-x") == 0){
    	FILE *fk;
    	fk = fopen("killer.sh", "w+");

    	char *isiFile = 
    	"#!/bin/bash\n"
    	"# kill untuk menghentikan program utama, tapi sisanya jalan\n"
    	"/usr/bin/kill -9 \"%d\"\n"
    	"# remove file killer.sh setelah di eksekusi\n"
    	"/bin/rm killer.sh";

    	fprintf(fk, isiFile, getpid());

    	fclose(fk);
    }  

    pid = fork();

    //chmod file killer agar executable
    if (pid == 0) {
    	char *argv3[] = {"chmod","777","killer.sh",NULL};
    	execv("/bin/chmod", argv3);
    }
    while(wait(&status) != pid);

    //close file descriptor standar
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1) {

       
      char tanggal[100], link[100], namaFile[100], final[100]; 
	    time_t rawDate, rawDate_2;
	    struct tm *localDate, *localDate_2;
	    int ukuran;

        rawDate = time(NULL);
        localDate = localtime(&rawDate);

        strftime(tanggal, 100, "%Y-%m-%d %H:%M:%S", localDate);

        cid = fork();

        if (cid < 0) {
        	exit(EXIT_FAILURE);
        }

        if (cid == 0) {
        	char *argv2[] = {"mkdir","-p",tanggal,NULL};
        	execv("/bin/mkdir", argv2);
        } else {
        	while(wait(&status) > 0);

        	cid_2 = fork();

        	if (cid_2 < 0) {
        		exit(EXIT_FAILURE);
        	}

        	if (cid_2 == 0) {
        		int i = 0;
        		while (i < 10){
        			cid_3 = fork();

        			if (cid_3 < 0) {
		        		exit(EXIT_FAILURE);
		        	}

		        	if (cid_3 == 0) {
		        		rawDate_2 = time(NULL);
		        		localDate_2 = localtime(&rawDate_2);
		        		ukuran = (rawDate_2 % 1000) + 50;		        				        		

		        		sprintf(link, "https://picsum.photos/%d" , ukuran);
		        		strftime(namaFile, sizeof(namaFile), "%Y-%m-%d_%H:%M:%S", localDate_2);
		        		sprintf(final, "%s/%s", tanggal, namaFile);

		        		char *argvv[] = {"wget","--no-check-certificate", "-q", "-O", final, link, NULL};
		        		execv("/usr/bin/wget", argvv);
		        	}

        			i++;
        			sleep(5);
        		}

        		while(wait(&status) > 0);

        		chdir(tanggal);   

        		caesar_cipher_encryption();

        		char pesan[100];

        		strcpy(pesan, data);

        		FILE * myfp;
        		myfp = fopen("status.txt", "w+");
        		fputs(pesan, myfp);
        		fclose(myfp);

        		chdir("../");

        		while(wait(&status) > 0);

        		cid_4 = fork();

        		if (cid_4 == 0){
        			char file[100];
        			sprintf(file, "%s.zip", tanggal);
        			char *argvvv[] = {"zip","-r",file,tanggal,NULL};
        			execv("/usr/bin/zip",argvvv);
        		}

        		while(wait(&status) > 0);
        		
        		char *argvvvv[] = {"rm","-r",tanggal,NULL};
        		execv("/bin/rm",argvvvv);
        	}

        }

        sleep(40);
        

    }
        
}
