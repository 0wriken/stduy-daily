tar -xf jpegsrc.v8b.tar.gz 
cd jpeg-8b
CC=arm-linux-gcc ./configure --prefix=${PWD}/libjepg/ --host=arm-linux
echo "config done"
make -j8; make install 
