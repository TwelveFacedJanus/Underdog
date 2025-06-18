
xcode:
	cmake -G Xcode -S . -B Build
makefile:
	mkdir -p Build && cd Build && cmake ..
