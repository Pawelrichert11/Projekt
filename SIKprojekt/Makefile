CXX = g++
CXXFLAGS = -std=c++11 -I. -lstdc++ -lm -D_GLIBCXX_USE_CXX11_ABI=0

router: Router.o RoutingTable.o Receiver.o Sender.o Connection.o
	$(CXX) $(CXXFLAGS) -o Router Router.o

Router.o: Router.cpp Tools.hpp
	$(CXX) $(CXXFLAGS) -c Router.cpp

RoutingTable.o: RoutingTable.cpp  RoutingTable.hpp Tools.hpp
	$(CXX) $(CXXFLAGS) -c RoutingTable.cpp

Connection.o: Connection.hpp Connection.cpp Tools.hpp
	$(CXX) $(CXXFLAGS) -c Connection.cpp

Sender.o: Sender.hpp Sender.cpp Tools.hpp
	$(CXX) $(CXXFLAGS) -c Sender.cpp

Receiver.o: Receiver.hpp Receiver.cpp Tools.hpp
	$(CXX) $(CXXFLAGS) -c Receiver.cpp

clean:
	$(RM) *.o

distclean:
	$(RM) router *.0
.PHONY: clean
