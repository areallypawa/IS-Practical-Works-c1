#include "Header_createArrayOfNames.h"
#include "Header_deafult.h"

void createArrayOfNames(std::string *Arr, Profile *p) {
	for (int i = 0; i < N; i++) {
		if ((p->fullName) != "") {
			*Arr = p->fullName;
			p += 1;
			Arr += 1;
		}
	}
}