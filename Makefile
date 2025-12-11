build: main/main.c
	/opt/esp-idf/tools/idf.py build

flash:
	/opt/esp-idf/tools/idf.py -p /dev/ttyACM0 flash

clean:
	/opt/esp-idf/tools/idf.py clean

audio: FORCE
	sudo mount -o uid=1000,gid=1000 /dev/disk/by-id/usb-Mass_Storage_Device_121220160204-0:0-part1 /mnt/card
	rsync -hr --info=progress2 --delete audio/. /mnt/card
	sudo umount /mnt/card

matt-audio: FORCE
	sudo mount -o uid=1000,gid=1000 /dev/disk/by-id/usb-Mass_Storage_Device_121220160204-0:0-part1 /mnt/card
	rsync -hr --info=progress2 --delete matt-audio/. /mnt/card
	sudo umount /mnt/card


FORCE:

all: build flash
