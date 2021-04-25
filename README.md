# Laporan Resmi
## _Soal Shift Modul 2_

Kelompok IT 12 yang beranggotakan:

- Prima Secondary Ramadhan  (05311940000001)
- Shavica
- Tata

## Soal 1

Poin-poin soal sebagai berikut:

- A). Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg
- B). Untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga :)
- C). Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload
- D).Memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan)
- E). Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany)
- F). Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip)

### Include Library
Pertama, kita include library yang dibutuhkan terlebih dahulu
```sh
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
```


### 1.A

Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg

Disini kami membuat tiga (3) method untuk melakukan tugasnya

```sh
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
```

### 1.B

Untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga :)

Disini kami membuat tiga (3) method untuk melakukan tugasnya. Untuk cara menggunakan wget dari google drive, telah disediakan pada Soal Shfit modul yang disediakan. Jadi, kita hanya perlu menggunakannya

```sh
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
```

### 1.C

Steven tidak ingin isi folder yang dibuatnya berisikan zip, sehingga perlu meng-extract-nya setelah didownload

Disini kita menggunakan tiga(3) method juga untuk melakukan proses unzip

```sh
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
```

### 1.D

Memindahkannya ke dalam folder yang telah dibuat (hanya file yang dimasukkan)

Nah, sedikit tricky disini. Kami, mengakalinya dengan melakukan beberapa proses yaitu: hapus dulu folder yang telah dibuat. Lalu, kita memindahkan folder tersebut sekaligus me-rename nya seperti folder yang ada pada sebelumnya

```sh
void delFotoMusikfilmDir(){
    char *argv[] = {"rm", "-r", "Pyoto", "Fylm", "Musyik", NULL};
    execv("/bin/rm", argv);
}
```
```sh
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
```

### 1.E

Untuk memudahkan Steven, ia ingin semua hal di atas berjalan otomatis 6 jam sebelum waktu ulang tahun Stevany)

Disini, kita menggunakan beberapa fungsi waktu(time) untuk melakukan trigger waktu ketika sudah memasuki waktu yang telah ditentukan (2021-04-09 16:21:59)


Deklarasi variabel waktu nya
```sh
    char tanggal[100]; 
    time_t rawDate;
    struct tm *localDate;
```

Penggunaan trigger waktunya ketika memasuki -6 jam sebelum jam ulang tahunnya
```sh
        //trigger untuk sudo date
        rawDate = time(NULL);
        localDate = localtime(&rawDate);
        strftime(tanggal, 50, "%Y-%m-%d %H:%M:%S", localDate);
        if(strcmp(tanggal,"2021-04-09 16:22:00") == 0){
            // task
        }
```

## 1.F

Setelah itu pada waktu ulang tahunnya Stevany, semua folder akan di zip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete(sehingga hanya menyisakan .zip)

Penggunaan trigger waktunya ketika sudah memasuki jam ulang tahunnya
```sh
        //trigger date
        rawDate = time(NULL);
        localDate = localtime(&rawDate);
        strftime(tanggal, 50, "%Y-%m-%d %H:%M:%S", localDate);
        if(strcmp(tanggal,"2021-04-09 22:22:00") == 0){
            // task
        }
```

Proses zipping semua folder yang diperlukan menjadi 1 file zip
```sh
void zipAllDir() {
    char *argv[] = {"zip", "-r", "Lopyu_Stevany.zip", "Pyoto", "Musyik", "Fylm", NULL};
    execv("/usr/bin/zip", argv);
}
```

*Tambahan, sebelum dipanggil perintah ```deleteAnotherDir``` , perlu ditambahkan ```wait``` supaya tidak terjadi race condition (di zip dulu semua, baru hapus semua filenya)
```sh
        // tunggu proses diatas selesai, baru hapus semua
        while ((wait(&status)) > 0);
```


Proses deleting semua folder yang tidak diinginkan
```sh
void deleteAnotherDir() {
    char *argv[] = {"rm", "-r", "FILM", "FOTO", "MUSIK", "Pyoto", "Fylm", "Musyik", NULL};
    execv("/bin/rm", argv);
}
```
