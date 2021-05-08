# Laporan Resmi
## _Soal Shift Modul 2_

Kelompok IT 12 yang beranggotakan:

- Prima Secondary Ramadhan  (05311940000001)
- Shavica Ihya Qurata Ayun L . (05311940000013)
- Sri Puspita Dewi (05311940000045)

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

## Soal 3

### 3.A
Ranora harus membuat sebuah program C yang dimana setiap 40 detik membuat sebuah direktori dengan nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss].

```...``` menunjukkan program lainnya. Ini merupakan potongan program yang menjelaskan soal 3.A

```sh
    ...
    char tanggal[100], link[100], namaFile[100], final[100]; 
    time_t rawDate, rawDate_2;
    struct tm *localDate, *localDate_2;
    int ukuran;

    rawDate = time(NULL);
    localDate = localtime(&rawDate);

    strftime(tanggal, 100, "%Y-%m-%d %H:%M:%S", localDate);
    ...
    if (cid == 0) {
    	char *argv2[] = {"mkdir","-p",tanggal,NULL};
    	execv("/bin/mkdir", argv2);
    } else {
        ...
    }
```

### 3.B
Setiap direktori yang sudah dibuat diisi dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.

Dilakukan loop sebanyak 10x menggunakan ```while``` disini
Lalu, diakhir while ditambahkan ```sleep(5)``` yang menunjukkan bahwa dilakukan download gambar tiap 5 detik
```sh
...
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
...
```

### 3.C
Setelah direktori telah terisi dengan 10 gambar, program tersebut akan membuat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Caesar Cipher adalah Teknik enkripsi sederhana yang dimana dapat melakukan enkripsi string sesuai dengan shift/key yang kita tentukan. Misal huruf “A” akan dienkripsi dengan shift 4 maka akan menjadi “E”. Karena Ranora orangnya perfeksionis dan rapi, dia ingin setelah file tersebut dibuat, direktori akan di zip dan direktori akan didelete, sehingga menyisakan hanya file zip saja.

Potongan codingan untuk Caesar Chiper
```sh
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
```

Potongan kodingan di main program
Jika pesan sudah di enkripsi, maka pesan tersebut akan dimasukkan ke status.txt

```sh
...
	chdir(tanggal);   

	caesar_cipher_encryption();

	char pesan[100];

	strcpy(pesan, data);

	FILE * myfp;
	myfp = fopen("status.txt", "w+");
	fputs(pesan, myfp);
	fclose(myfp);

	chdir("../");
...
```

Lalu diakhir program, folder tersebut akan di zip dan folder tadi akan dihapus
```sh
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
```

### 3.D
Untuk mempermudah pengendalian program, pembimbing magang Ranora ingin program tersebut akan men-generate sebuah program “Killer” yang executable, dimana program tersebut akan menterminasi semua proses program yang sedang berjalan dan akan menghapus dirinya sendiri setelah program dijalankan. Karena Ranora menyukai sesuatu hal yang baru, maka Ranora memiliki ide untuk program “Killer” yang dibuat nantinya harus merupakan program bash.

Berikut merupakan potongan program agar bisa meng-execute program ```killer.sh``` yang telah dibuat
Untuk pembuatan program ```killer.sh``` nya, ada pada nomor ```3.E``` dibawah
```sh
    pid = fork();

    //chmod file killer agar executable
    if (pid == 0) {
    	char *argv3[] = {"chmod","777","killer.sh",NULL};
    	execv("/bin/chmod", argv3);
    }
    while(wait(&status) != pid);
```

### 3.E
Pembimbing magang Ranora juga ingin nantinya program utama yang dibuat Ranora dapat dijalankan di dalam dua mode. Untuk mengaktifkan mode pertama, program harus dijalankan dsdengan argumen -z, dan Ketika dijalankan dalam mode pertama, program utama akan langsung menghentikan semua operasinya Ketika program Killer dijalankan. Sedangkan untuk mengaktifkan mode kedua, program harus dijalankan dengan argumen -x, dan Ketika dijalankan dalam mode kedua, program utama akan berhenti namun membiarkan proses di setiap direktori yang masih berjalan hingga selesai (Direktori yang sudah dibuat akan mendownload gambar sampai selesai dan membuat file txt, lalu zip dan delete direktori).

Potongan codingan dibawah, untuk mengecek apakah input ketika execute file nya sudah sesuai yang kita inginkan apa belum. Yaitu, mode 1 ```-z``` atau mode 2 ```-x```
```sh
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
```

Lalu program dibawah, untuk membuat file ```killer.sh``` sesuai dengan mode yang ada
Ketika kita membuat file tersebut, kita sekaligus memasukkan command didalam filenya untuk menghentikan proses yang ada

```sh
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
```
