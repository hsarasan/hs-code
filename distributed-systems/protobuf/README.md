I struggled to build protobuf.

This is what I had done

* git clone https://github.com/protocolbuffers/protobuf.git
* git clone https://github.com/abseil/abseil-cpp.git

I built and installed protobuf & abseil-cpp and installed them

This created a protoc and installed the abseil libraries in /usr/local/lib

i created the file message.proto

generated the cc file and tried to compile producer.cpp and consumer.cpp

There started many hours of getting to link

Finally I found this command -  => pkg-config --libs --static protobuf 

Life saver ! I generated the shared libraries and linker flags to build everything

So I have added this to CMakeLists.txt

