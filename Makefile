all:
	g++ -I common_dump -I general_io_file_func -I list -I tree/include tree/src/*.cpp list/*.cpp common_dump/*.cpp general_io_file_func/*.cpp -g -o tree.out