#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>

// Declare fungsi 

void makeFotoDir(){
    char *argv[] = {"mkdir", "-p", "Pyoto", NULL};
    execv("/bin/mkdir", argv);    
}

void makeMusikDir(){
    char *argv[] = {"mkdir", "-p", "Musyik", NULL};
    execv("/bin/mkdir", argv);    
}

void makeFilmDir(){
    char *argv[] = {"mkdir", "-p", "Fylm", NULL};
    execv("/bin/mkdir", argv);    
}

void delFotoMusikfilmDir(){
    char *argv[] = {"rm", "-r", "Pyoto", "Fylm", "Musyik", NULL};
    execv("/bin/rm", argv);
}

void getFoto() {
    char *argv[] = {"wget","--no-check-certificate", "-q", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Foto_for_Stevany.zip", NULL};
    execv("/usr/bin/wget", argv);
}

void getMusik() {
    char *argv[] = {"wget","--no-check-certificate", "-q", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musik_for_Stevany.zip", NULL};                    
    execv("/usr/bin/wget", argv);
}

void getFilm() {
    char *argv[] = {"wget","--no-check-certificate", "-q", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Film_for_Stevany.zip", NULL};                    
    execv("/usr/bin/wget", argv);
}

void unzipFoto() {
    char *argv[] = {"unzip", "-q", "Foto_for_Stevany.zip", NULL};
    execv("/usr/bin/unzip", argv);
}

void unzipMusik() {
    char *argv[] = {"unzip", "-q", "Musik_for_Stevany.zip", NULL};
    execv("/usr/bin/unzip", argv);
}

void unzipFilm() {
    char *argv[] = {"unzip", "-q", "Film_for_Stevany.zip", NULL};
    execv("/usr/bin/unzip", argv);
}

void MoveRenameFoto() {
    char *argv[] = {"mv", "FOTO", "Pyoto", NULL};
    execv("/bin/mv", argv); 
}

void MoveRenameMusik() {
    char *argv[] = {"mv", "MUSIK", "Musyik", NULL};
    execv("/bin/mv", argv); 
}

void MoveRenameFilm() {
    char *argv[] = {"mv", "FILM", "Fylm", NULL};
    execv("/bin/mv", argv);  
}

void zipAllDir() {
    char *argv[] = {"zip", "-r", "Lopyu_Stevany.zip", "Pyoto", "Musyik", "Fylm", NULL};
    execv("/usr/bin/zip", argv);
}

void deleteAnotherDir() {
    char *argv[] = {"rm", "-r", "FILM", "FOTO", "MUSIK", "Pyoto", "Fylm", "Musyik", NULL};
    execv("/bin/rm", argv);
}

int main(){

    // declare variable
    pid_t pid, sid;     
    char tanggal[100]; 
    time_t rawDate;
    struct tm *localDate;
    int status;
    pid_t cid = fork();
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

    //close file descriptor standar
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1) {

        //trigger untuk sudo date
        rawDate = time(NULL);
        localDate = localtime(&rawDate);
        strftime(tanggal, 50, "%Y-%m-%d %H:%M:%S", localDate);
        if(strcmp(tanggal,"2021-04-09 16:22:00") == 0){

            if (cid == 0) {
                makeFotoDir();
            }
            else 
            {
            // membuat folder
                cid = fork();
                if (cid == 0) {
                    makeMusikDir();                    
                }
                while(wait(NULL) != cid);

                cid = fork();
                if (cid == 0) {                    
                    makeFilmDir();            
                }
                while(wait(NULL) != cid);

            // download file dari Google drive
                cid = fork();
                if (cid == 0) {
                    getFoto();                    
                }
                while(wait(NULL) != cid);

                cid = fork();
                if (cid == 0) {
                    getMusik();
                }
                while(wait(NULL) != cid);

                cid = fork();
                if (cid == 0) {
                    getFilm();
                }
                while(wait(NULL) != cid);

            // unzip file yang telah di download
                cid = fork();
                if (cid == 0) {
                    unzipFoto();
                }
                while(wait(NULL) != cid);

                cid = fork();
                if (cid == 0) {
                    unzipMusik();
                }
                while(wait(NULL) != cid);

                cid = fork();
                if (cid == 0) {
                    unzipFilm();
                }
                while(wait(NULL) != cid);

            // delete folder yang sudah ada
                cid = fork();
                if (cid == 0) {
                    delFotoMusikfilmDir();
                }
                while(wait(NULL) != cid);


            // pindahkan dan rename file
                cid = fork();
                if (cid == 0) {
                    MoveRenameFoto();
                }
                while(wait(NULL) != cid);

                cid = fork();
                if (cid == 0) {
                    MoveRenameMusik();
                }
                while(wait(NULL) != cid);

                cid = fork();
                if (cid == 0) {
                    MoveRenameFilm();
                }
                while(wait(NULL) != cid);

            }            

            break;

        }
        
    }

    while (1) {

        //trigger date
        rawDate = time(NULL);
        localDate = localtime(&rawDate);
        strftime(tanggal, 50, "%Y-%m-%d %H:%M:%S", localDate);
        if(strcmp(tanggal,"2021-04-09 22:22:00") == 0){

            cid = fork();
            if (cid == 0) {
                zipAllDir();
            }
            else{

                // tunggu proses diatas selesai, baru hapus semua
                while ((wait(&status)) > 0);

                cid = fork();
                if (cid == 0) {
                    deleteAnotherDir();
                }
                while(wait(NULL) != cid);

            }

            break;

        }
    
    }
  

}
