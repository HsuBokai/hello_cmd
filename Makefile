all:
	gcc -c `pkg-config --cflags --libs glib-2.0` my_crypto.c
	gcc main.c utils.c   `pkg-config --libs glib-2.0`  -lgcrypt -o main
clean:
	rm main *.o
