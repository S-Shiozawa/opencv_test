
capture:capture.cpp
	g++  -o capture capture.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`

dist:undistort.cpp
	g++ undistort.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`-o dist

Calb:cameraCalibration.cpp
	g++ -Wall cameraCalibration.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`-o Calb

dst_save:dst_save.cpp
	g++ -Wall dst_save.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`-o dst_save


docap:doublecap.cpp
	g++ -O3 -o docap doublecap.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`	

docap_shuter:docap_shuter.cpp
	g++ -O3 -o docap_shuter docap_shuter.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`	

docap2:doublecap2.cpp
	g++ -std=c++11  -o docap2 doublecap2.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv` -lpthread	


fps:fps.cpp
	g++  -o fps fps.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`	

stereocalib_dst:stereocalib_dst.cpp
	g++  -o stereocalib_dst stereocalib_dst.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`	

stereocalib_conf:stereocalib_conf.cpp
	g++  -o stereocalib_conf stereocalib_conf.cpp -I /usr/include/opencv2 `pkg-config --cflags opencv` `pkg-config --libs opencv`	

HSV:HSV.cpp
	g++  -o HSV HSV.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`	
	
imagelist:imagelist_creator.cpp
	g++  -o imagelist imagelist_creator.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`	
	
clean:
	rm -f capture dist dst_save

#ls *.png | awk '{ printf "mv %s %02d.png\n", $0, NR-1}' | sh  #リネイム



