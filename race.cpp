#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

class SecureFileAccess {
private:
	int fd;
	char * filename;
public:
	SecureFileAccess(char *);
	void check_and_open();
	void work();
	~SecureFileAccess();
};

SecureFileAccess::SecureFileAccess(char * fn) {
	filename = fn;
}

SecureFileAccess::~SecureFileAccess() {
	close(fd);
}

void SecureFileAccess::check_and_open() {
	if(access(filename, R_OK) == 0 ) {
		sleep(5);
		fd = open(filename, O_RDONLY);
	}
	else {
		string s = "You do not have access to this file.";
		throw s;
	}
}

void SecureFileAccess::work() {
	char buf[21];
	read(fd, buf, 20);
	buf[20]=0x00;
	cout << "Up to first 20 bytes are:"<< endl << buf << endl;
}

int main ( int argc, char * argv[]) {
	int i;
	cout << "Real ID=" << getuid() << " Effective ID=" << geteuid() <<endl;
	cout << "Printing requested files..." << endl;

	for(i=1; i < argc; i++)	{
		try {
			SecureFileAccess fileobj(argv[i]);
			fileobj.check_and_open();
			fileobj.work();
		}
		catch(string s) {
			cout << "Exiting due to error: " << s << endl;
			exit(-1);
		}
	}
}
