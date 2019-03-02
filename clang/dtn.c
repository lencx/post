/*
* 除基数(进制)取余，即每次将整数部分除以基数，余数为该位权上的数，
* 而商继续除以基数，余数又为上一个位权上的数，这个步骤一直持续下去，
* 直到商为0为止，最后读数时候，从最后一个余数读起，一直到最前面的一个余数。
*/
#include <stdio.h>

int main() {
  int base, num, i, rem, digit, temp, count = 0; // 声明变量
  // 声明数据类型为字符的数组，用于存储进制转换后的各位上的数值
  char a[100]; // https://stackoverflow.com/questions/44266586/what-does-char-word100-mean-in-c

  printf("请输入一个十进制数:\n");
  scanf("%d", &num);

  printf("请输入要转换的基数:\n");
  scanf("%d", &base);

  temp = num; // 赋值
  do { // do-while循环
    // printf("*************************\n");
    rem = temp % base; // 取余
    // printf("rem:=> %d\n", rem);
    digit = '0' + rem; // 数字转ASCII
    // printf("digit:=> %c\n", digit);
    // printf("ASCII: [9]=> %d\n", '9'); // 57
    if(digit > '9') { // 如果大于ASCII 9则加7,即10-A,11-B, ..., 15-F
      digit = digit + 7; // [0-9]: 48-57 && [A-E]: 65-70
    }
    a[count] = digit; // 数组赋值
    count++; // 自增，数组索引
    temp = temp / base; //
    printf("temp:=> %d\n", temp);
  } while(temp != 0); // 循环执行的条件，temp不等于0

  printf("十进制数%d转换为基数是%d的结果是: ", num, base);

  for(i = count - 1; i >= 0; --i) {// for循环，从数组中反向取出之前存储的数值
    printf("%c", a[i]); // %c，数组a中存储的是字符
  }
  printf(".\n");
  printf("%c\n", '0'+0);
  printf("%c\n", '0'+1);
  printf("%c\n", '0'+10);
  return 0;
}