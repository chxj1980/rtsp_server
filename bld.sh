make clean
make
arm-buildroot-linux-uclibcgnueabi-strip ./bin/rtsp_server.mod
cp -f ./bin/rtsp_server.mod /root/Desktop/davinci/dm3730/dvsdk4_03/filesystem/dm3730rootfs-guowang/dm3730rootfs/opt/app1
