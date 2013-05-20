#include "words.h"
#include "string.h"
#include <stdio.h>
//#include <stdlib.h>

static const char* ONES[] = {
  "zero",
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine",
};

static const char* TENS[] = {
  "",
  "ten",
  "twenty",
  "thirty",
  "forty",
  "fifty"
};

// Offset by one using an empty string to make modular arithmetic easier
static const char* TEENS[] = {
  "",
  "eleven",
  "twelve",
  "thirteen",
  "fourteen",
  "fifteen",
  "sixteen",
  "seventeen",
  "eighteen",
  "nineteen"
};

// Save ourselves a deref, we need zero a lot.
static const char* ZERO = "zero";
static const char* HUNDRED = "hundred";
static const char* HOURS = "hours";
static const char* HYPHEN = "-";
static const char* SPACE = " ";

int format_number(int num, char* buf, size_t max_len) {
  if (num < 10) {
    // 1-10 become "zero one" to "zero nine"
    strncat(buf, ZERO, max_len);
    max_len -= 4;
    strncat(buf, SPACE, max_len);
    max_len -= 1;
    strncat(buf, ONES[num], max_len);

    return strlen(ONES[num]) + 5;

  } else if (num == 10) {
    // 10 becomes "ten"
    strncat(buf, TENS[1], max_len);
    return strlen(TENS[1]);

  } else if (num < 20) {
    // 11-19 become "eleven" to "nineteen"
    strncat(buf, TEENS[num - 10], max_len);
    return strlen(TEENS[num - 10]);

  } else {
    // How many tens?
    int tens_idx = num / 10;
    int ones_idx = num % 10;
    int copied = 0;

    strncat(buf, TENS[tens_idx], max_len);
    copied += strlen(TENS[tens_idx]);
    max_len -= copied;

    strncat(buf, "\n", max_len);
    copied += 1;
    max_len -= 1;

    strncat(buf, ONES[ones_idx], max_len);
    return copied += strlen(ONES[ones_idx]);
  }
}

int format_hour(int hour, char* buf, size_t max_len) {
  return format_number(hour, buf, max_len);  
}

int format_minutes(int minutes, char* buf, size_t max_len) {
  if (minutes == 0) {
    strncat(buf, HUNDRED, max_len);
    return strlen(HUNDRED);
  } else {
    return format_number(minutes, buf, max_len);
  }
}

void format_time(int hour, int minutes, char* buf, size_t size) {
//  size_t remaining = size;
  size -= format_hour(hour, buf, size);
  strncat(buf, "\n", 1);
  size -= 1;
  size -= format_minutes(minutes, buf, size);
  strncat(buf, "\n", 1);
  size -= 1;
  strncat(buf, HOURS, size);
}

// int main(int argc, char const *argv[])
// {
//   char* text;
//   text = (char*) malloc(sizeof(char) * 64); 
//   format_time(21, 49, text, 64);
//   printf("%s\n", text);
//   return 0;
// }