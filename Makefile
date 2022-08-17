as=/usr/bin/as
cc=/usr/bin/g++
ld=/usr/bin/ld

sources=main.cpp
basic_source=ortam_yurutucu_v00.cpp
objects=$(sources:.cpp=.o)
basic_objects=$(basic_source:.cpp=.o)

app=$(sources:.cpp=)
src_headers=
basic_app=$(basic_source:.cpp=)
cppflags=-std=c++11
gtkcflags=`pkg-config --cflags --libs gtk+-2.0`
mysqlcflags=$(mysql_config --cflags --libs)
wxflags=`wx-config --cxxflags --libs std,media`
ccwxflags=`wx-config --cxxflags`
ldwxflags=`wx-config --libs std,media`


basic_app:
	$(cc) -c $(basic_source) $(sources) $(wxflags) $(cppflags) $(ccwxflags)
	$(cc)  -o $(basic_app) $(objects) $(basic_objects) $(ldwxflags)
clean:
	rm $(basic_app)
