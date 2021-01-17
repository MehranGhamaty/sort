/*
An implementation of the tail unix program.
*/

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

bool isnewline(char c) {
	return c == '\n';
}

void readend(std::ifstream &is, int blocksize, int nlinestoread) {
	int numlinesread = 0;
	
	is.seekg(0, is.end);
	int len = is.tellg();
	int offset = len > blocksize ? -blocksize : -len;
	int toread = len > blocksize ? blocksize : len;

	char buffer[blocksize];

	int adj = 0;

	while(numlinesread < nlinestoread) {
		//this line is a problem
		is.seekg(offset, is.end);
		is.read(buffer, toread);	

		for(int i = toread-1; i >= 0; --i) {
			if(isnewline(buffer[i])) {
				++numlinesread;
				if(numlinesread == nlinestoread+1) {
					adj = i+1;
					break;
				}
			}

		}

		if(offset == -len or numlinesread == nlinestoread+1) {
			break;
		}

		offset -= blocksize;
		if(offset >= -len) {
			offset = -len;
			break;
		}
	}

	is.seekg(offset + adj, is.end);
	do {
		is.read(buffer, toread);
		std::cout << buffer << std::flush;
	} while(!is.eof());
	

}

int main(int argc, char *argv[]) {
	
	if(argc < 3) {
		std::cerr << "Usage: tail numlines filename" << std::endl;
	}
	int blocksize = 1024;
	int nlinestoread = atoi(argv[1]);
	std::string filename = std::string(argv[2]);
	std::ifstream is(filename, std::ifstream::binary);
	if(is) {readend(is, blocksize, nlinestoread);}
}
