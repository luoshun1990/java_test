javac hello.java
#可查看描述符,想查看描述符时，打开即可
#javap -p -s hello.class

gcc -I/usr/lib/jvm/java-1.7.0-openjdk-amd64/include/ -o caller caller.c -L /usr/lib/jvm/java-7-openjdk-amd64/jre/lib/amd64/server -ljvm

LD_LIBRARY_PATH=/usr/lib/jvm/java-7-openjdk-amd64/jre/lib/amd64/server ./caller




