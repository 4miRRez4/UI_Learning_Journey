#include <cstdio>

bool send_query(int x, int y) {
	printf("? %d %d\n", x, y);
	fflush(stdout);
	string response;
	cin >> response;
	return response[0] == 'Y';
}

int find_y() {
  int first = 0;
  int last = 10001;
  while (first <= last) {
    int mid = (first + last) >> 1;
    if (send_query(0, mid)) {
      first = mid;
    } else {
      last = mid;
    }
  }
  return first;
}

int find_x(int y) {
  int first = 0;
  int last = 1001;
  while (first <= last) {
    int mid = (first+last) >> 1;

    if (send_query(mid, y)){
      first = mid;
    }else
      last = mid;
  }
  return first;
}

int main() {
  int square_side = 2 * find_x(0);
  int tri_hei = find_y()-square_side;
  int tri_base = 2*find_x(square_side);
  int area = square_side*square_side + 1/2 *tri_base * tri_hei;
  printf("! %d\n", area);
}