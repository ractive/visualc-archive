#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

void usage() {
	cerr << "Usage: tail #lines filename\n";
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		usage();
		return 1;
	}

	// Number of lines to output
	const unsigned n = atoi(argv[1]);
	char * filename = argv[2];

	ifstream ifs(filename);
	if (!ifs) {
		cerr << "Cannot open file '" << filename << "'\n";
		return 1;
	}

	noskipws(ifs);
	ifs.seekg(0, ios_base::end);
	streampos length = ifs.tellg();

	size_t lf_found = 0;
	const size_t buf_size = 4096;
	streamoff bytes_read = 0;
	std::vector<char> buf(buf_size);

	// Read data in blocks of buf_size size from the back of
	// the file until n + 1 linefeeds have been found.
	while(lf_found < n + 1) {
		streamoff seek_to = bytes_read + buf_size;
		streamsize read_no = buf_size;

		if (seek_to > length) {
			// Reached the beginning of the file
			ifs.seekg(0);
			read_no = length - bytes_read;
		}
		else {
			ifs.seekg(-seek_to, ios_base::end);
		}
		
		ifs.read(&buf[0], read_no);
		streamsize read_g = ifs.gcount();
		bytes_read += read_g;
		lf_found += count(buf.begin(), buf.begin() + read_g, '\n');

		if (seek_to > length) {
			// Reached the beginning of the file
			break;
		}
	}

	istream_iterator<char> eof;

	// Reposition the filepointer so that it points to
	// the 
	if (lf_found >= n + 1) {
		// How many \n to skip before starting the output
		size_t skip_lf = lf_found - n - 1;
		// Position the file pointer
		ifs.clear();
		ifs.seekg(-bytes_read, ios_base::end);
		istream_iterator<char> f(ifs);
		if (bytes_read <= length) {
			// Skip the first line that does not belong to the n lines
			find(f, eof, '\n');
		}
		for(size_t i = 0; i < skip_lf; ++i) {
			find(f, eof, '\n');
		}
	}
	else {
		ifs.seekg(0);
	}

	istream_iterator<char> f(ifs);
	copy(f, eof, ostream_iterator<char>(cout));
}
