CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lboost_system -lboost_thread -lpthread

TARGETS = kv_server

all: $(TARGETS)

kv_server: kv_server.cpp
	$(CXX) $(CXXFLAGS) -o kv_server kv_server.cpp $(LDFLAGS)

clean:
	rm -f $(TARGETS)

