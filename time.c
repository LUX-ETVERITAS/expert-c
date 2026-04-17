#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>

int main() {
  // 测试这些类型的位
  printf("%zu\n", sizeof(time_t));
  printf("%zu\n", sizeof(long));
  printf("%zu\n", sizeof(int));
  // LONG_MAX = 7fffffffffffffff INT_MAX = 7fffffff
  printf("%ld, %d\n", LONG_MAX, INT_MAX);
  printf("%lx, %x\n", LONG_MAX, INT_MAX);
  // 因为用补码存所以MSB为0 剩下3位是111
  // time.h 是 能够表示时间的实数算术类型
  // 一般是整数
  time_t max_time = LONG_MAX;
  printf("%ld\n", max_time);
  // ctime
  // 将给定的自纪元（Epoch）以来的时间转换为本地日历时间，然后转换为文本表示
  // c23被弃用
  // ctime 在下面语句崩溃 无法正常使用
  // 对于导致字符串长度超过 25 个字符的 time_t 值（例如年份 10000）， ctime
  // 的行为是未定义的。
  char *output = ctime(&max_time);
  if (output != NULL) {
    printf("sucess %s", output);
  }
  // asctime ctime 均被弃用
  printf("strftime 会怎么样？\n");
  char s[10000];
  // 这段会直接导致崩溃
  // gmtime 返回 NULL
  // if (strftime(s, 1000, "%D", gmtime(&max_time))) {
  //  printf("%s", s);
  //}
  time_t now = time(NULL);
  double seconds = difftime(max_time, now);
  printf("%f\n", seconds);
  time_t diff = (long)seconds;
  if (strftime(s, 1000, "%D", gmtime(&diff))) {
    printf("%s", s);
  }
}
