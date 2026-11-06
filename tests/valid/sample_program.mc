// Sample program from the manual (Section 5.5), with comments added
int x;
int y;
bool flag;

x = 10;
y = 0;
flag = true;

/* sum x + (x-1) + ... + 1 */
while (x > 0) {
    y = y + x;
    x = x - 1;
}

if (flag == true) {
    print y;
} else {
    print x;
}
